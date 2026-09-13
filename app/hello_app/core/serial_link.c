/****************************************************************************
 * FOCUS AIoT - 上位机串口链路 (core/serial_link.c)
 *
 * 负责人: 万思源
 * 说明: 见 core/serial_link.h (协议与背景)。
 *
 * 设备直接读写标准输入输出 (USB CDC 串口): 写图/写报告用 stdout,
 * 读识别结果用 stdin。NuttShell 在 hello_app 运行期间处于等待状态,
 * 因此 stdin 可被本模块独占读取。
 ****************************************************************************/

#include <nuttx/config.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <poll.h>

#include "serial_link.h"

/* 等待上位机结果的超时 (模型含冷启动, 给足余量) */
#define SERIAL_RESULT_TIMEOUT_MS  30000
/* 读结果时的单次缓冲 */
#define SERIAL_RD_CHUNK           512
/* 单帧最大重传次数 (丢字节时上位机会请求重发) */
#define SERIAL_MAX_ATTEMPT        4

/* ------------------------------------------------------------------ */
/* Base64 编码 (RFC 4648; 本模块自包含, 不依赖 perception 内部实现)     */
/* ------------------------------------------------------------------ */

static size_t b64_encoded_len(size_t n)
{
  return 4 * ((n + 2) / 3);
}

static size_t b64_encode(const uint8_t *src, size_t len, char *dst, size_t cap)
{
  static const char tbl[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
  size_t out = b64_encoded_len(len);
  size_t i;
  size_t j = 0;

  if (src == NULL || dst == NULL || cap < out + 1)
    {
      return 0;
    }

  for (i = 0; i + 3 <= len; i += 3)
    {
      uint32_t v = ((uint32_t)src[i] << 16) |
                   ((uint32_t)src[i + 1] << 8) |
                    (uint32_t)src[i + 2];

      dst[j++] = tbl[(v >> 18) & 63];
      dst[j++] = tbl[(v >> 12) & 63];
      dst[j++] = tbl[(v >> 6) & 63];
      dst[j++] = tbl[v & 63];
    }

  if (len - i == 1)
    {
      uint32_t v = (uint32_t)src[i] << 16;
      dst[j++] = tbl[(v >> 18) & 63];
      dst[j++] = tbl[(v >> 12) & 63];
      dst[j++] = '=';
      dst[j++] = '=';
    }
  else if (len - i == 2)
    {
      uint32_t v = ((uint32_t)src[i] << 16) | ((uint32_t)src[i + 1] << 8);
      dst[j++] = tbl[(v >> 18) & 63];
      dst[j++] = tbl[(v >> 12) & 63];
      dst[j++] = tbl[(v >> 6) & 63];
      dst[j++] = '=';
    }

  dst[j] = '\0';
  return j;
}

/* ------------------------------------------------------------------ */
/* 校验: 16 位累加和 (够用 —— 主要抓"丢字节", 不是防恶意篡改)            */
/* ------------------------------------------------------------------ */

static uint16_t sum16(const char *data, size_t len)
{
  uint32_t s = 0;

  while (len-- > 0)
    {
      s += (uint8_t)(*data++);
    }

  return (uint16_t)(s & 0xffff);
}

/* ------------------------------------------------------------------ */
/* 底层读写                                                            */
/* ------------------------------------------------------------------ */

/* 分块写 stdout, 每块后让出。
 * 一次性灌入 30KB+ 会长时间占用串口输出路径, 与 WiFi 那次同理 ——
 * 实测真机在这种情况下仍会崩 (CPU1 IDLE / 非法 VADDR), 故改为小块 + 让出,
 * 让出时间既给串口驱动排空, 也给其它就绪任务调度机会。 */
#define SERIAL_TX_CHUNK    256
#define SERIAL_TX_GAP_US   2000

static int write_all(const char *data, size_t len)
{
  size_t sent = 0;

  while (sent < len)
    {
      size_t chunk = len - sent;
      ssize_t w;

      if (chunk > SERIAL_TX_CHUNK)
        {
          chunk = SERIAL_TX_CHUNK;
        }

      w = write(STDOUT_FILENO, data + sent, chunk);
      if (w <= 0)
        {
          if (w < 0 && errno == EINTR)
            {
              continue;
            }
          return -1;
        }

      sent += (size_t)w;

      if (sent < len)
        {
          usleep(SERIAL_TX_GAP_US);
        }
    }

  return 0;
}

/* 读一行 (以 \n 结尾, 去掉 \r\n), 带总超时。返回 0=成功, -1=超时/出错 */
static int read_line(char *buf, size_t cap, int timeout_ms)
{
  size_t used = 0;
  int    waited = 0;

  while (used + 1 < cap)
    {
      struct pollfd pfd;
      char    ch;
      ssize_t r;

      pfd.fd = STDIN_FILENO;
      pfd.events = POLLIN;
      if (poll(&pfd, 1, 200) <= 0)
        {
          waited += 200;
          if (waited >= timeout_ms)
            {
              return -1;
            }
          continue;
        }

      r = read(STDIN_FILENO, &ch, 1);
      if (r <= 0)
        {
          if (r < 0 && errno == EINTR)
            {
              continue;
            }
          return -1;
        }

      if (ch == '\n')
        {
          break;
        }
      if (ch != '\r')
        {
          buf[used++] = ch;
        }
    }

  buf[used] = '\0';
  return 0;
}

/* ------------------------------------------------------------------ */
/* 对外接口                                                            */
/* ------------------------------------------------------------------ */

int serial_detect(const uint8_t *jpeg, size_t jpeg_len,
                  char *result, size_t cap)
{
  char  *b64;
  size_t b64_cap;
  size_t b64_len;
  char   hdr[64];
  char   line[128];
  size_t   used = 0;
  size_t   want = 0;
  uint16_t want_sum = 0;
  int      attempt;

  if (jpeg == NULL || jpeg_len == 0 || result == NULL || cap == 0)
    {
      return -1;
    }

  b64_cap = b64_encoded_len(jpeg_len) + 1;
  b64 = malloc(b64_cap);
  if (b64 == NULL)
    {
      return -1;
    }

  b64_len = b64_encode(jpeg, jpeg_len, b64, b64_cap);
  if (b64_len == 0)
    {
      free(b64);
      return -1;
    }

  /* 发送 + 接收, 带重传:
   *   设备 → 电脑: ###IMG <len> <sum>\n<base64>\n###ENDIMG
   *   电脑 → 设备: ###AGAIN              (图或结果校验失败, 请求重发)
   *   电脑 → 设备: ###RESULT <len> <sum>\n<json>\n###ENDRESULT
   * 串口控制台是为日志设计的, 大块传输会丢字节, 故两端都校验并重传。 */
  for (attempt = 0; attempt < SERIAL_MAX_ATTEMPT; attempt++)
    {
      snprintf(hdr, sizeof(hdr), "\n###IMG %u %u\n",
               (unsigned)b64_len, (unsigned)sum16(b64, b64_len));
      if (write_all(hdr, strlen(hdr)) < 0 ||
          write_all(b64, b64_len) < 0 ||
          write_all("\n###ENDIMG\n", 11) < 0)
        {
          free(b64);
          return -1;
        }

      /* 等待 ###RESULT 或 ###AGAIN */
      for (;;)
        {
          if (read_line(line, sizeof(line), SERIAL_RESULT_TIMEOUT_MS) < 0)
            {
              free(b64);
              return -1;
            }

          if (strncmp(line, "###AGAIN", 8) == 0)
            {
              printf("[serial] 上位机请求重传图片 (第 %d 次)\n", attempt + 1);
              break;                       /* 重新发图 */
            }

          if (strncmp(line, "###RESULT ", 10) == 0)
            {
              unsigned w = 0;
              unsigned s = 0;

              if (sscanf(line + 10, "%u %u", &w, &s) != 2 || w == 0 || w >= cap)
                {
                  free(b64);
                  return -1;
                }

              want     = (size_t)w;
              want_sum = (uint16_t)s;
              goto got_header;
            }

          /* 其余行是上位机/系统日志, 忽略 */
        }
    }

  free(b64);
  return -1;                                   /* 重传次数用尽 */

got_header:

  /* 读结果正文并校验; 校验失败则请求重发整帧 */
  {
    for (attempt = 0; attempt < SERIAL_MAX_ATTEMPT; attempt++)
      {
        used = 0;
        while (used < want)
          {
            ssize_t r = read(STDIN_FILENO, result + used, want - used);

            if (r <= 0)
              {
                if (r < 0 && errno == EINTR)
                  {
                    continue;
                  }
                free(b64);
                return -1;
              }
            used += (size_t)r;
          }

        result[used] = '\0';

        if (sum16(result, used) == want_sum)
          {
            (void)write_all("###OK\n", 6);   /* 告诉上位机可以进入下一帧 */
            free(b64);
            return 0;
          }

        printf("[serial] 结果校验失败, 请求重发 (第 %d 次)\n", attempt + 1);
        if (write_all("###AGAIN\n", 9) < 0)
          {
            free(b64);
            return -1;
          }

        /* 等上位机重发 ###RESULT */
        for (;;)
          {
            if (read_line(line, sizeof(line), SERIAL_RESULT_TIMEOUT_MS) < 0)
              {
                free(b64);
                return -1;
              }
            if (strncmp(line, "###RESULT ", 10) == 0)
              {
                unsigned w = 0;
                unsigned s = 0;

                if (sscanf(line + 10, "%u %u", &w, &s) != 2 ||
                    w == 0 || w >= cap)
                  {
                    free(b64);
                    return -1;
                  }
                want     = (size_t)w;
                want_sum = (uint16_t)s;
                break;
              }
          }
      }
  }

  free(b64);
  return -1;
}

int serial_send_report(const char *json)
{
  char hdr[64];
  size_t len;

  if (json == NULL)
    {
      return -1;
    }

  len = strlen(json);
  snprintf(hdr, sizeof(hdr), "\n###REPORT %u %u\n",
           (unsigned)len, (unsigned)sum16(json, len));

  if (write_all(hdr, strlen(hdr)) < 0 ||
      write_all(json, len) < 0 ||
      write_all("\n###ENDREPORT\n", 14) < 0)
    {
      return -1;
    }

  return 0;
}
