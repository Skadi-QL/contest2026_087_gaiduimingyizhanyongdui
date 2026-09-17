/****************************************************************************
 * FOCUS AIoT - 真实 WiFi 驱动 (hardware/wifi_esp32.c)
 *
 * 负责人: 张沐泽
 * 职责: STA 连接、连接状态/RSSI 查询、HTTP POST (lwIP POSIX socket)。
 *
 * 说明:
 *   - HTTP POST 基于 lwIP 的 POSIX socket API, 超时 3s + 重试 1 次 (≤6s)。
 *   - 连接/状态/RSSI 走 netdev wireless ioctl (wlan0)。
 *   - 板子镜像内置 wapi 命令, 也可在启动脚本里先 wapi connect 联网,
 *     本驱动的 wifi_http_post 只依赖已联网的 wlan0。
 ****************************************************************************/

#include "../api/wifi.h"
#include "../api/error.h"
#include "wifi_send_all.h"

#include <nuttx/config.h>

#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <netdb.h>
#include <nuttx/net/ioctl.h>
#include <nuttx/wireless/wireless.h>
#include <wireless/wapi.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define WIFI_IFNAME    "wlan0"
/* MiMo 识图: 上传 base64 图 + 云端推理可能 >20s (推理吃满 token),
 * 放宽到 60s 避免响应稍慢就误判超时 */
#define HTTP_TIMEOUT_SEC  60

/* 请求体分块发送: 每块字节数 / 块间让出微秒 (见 wifi_http_post 注释)。
 * 80KB 一次 send 会耗尽 WiFi TX 帧缓冲并导致 HPWORK 崩溃。 */
#define HTTP_SEND_CHUNK   2048
#define HTTP_SEND_GAP_US  2000

/* 本连接的 TCP 发送缓冲。帧体约 205KB, 是系统默认(CONFIG_NET_SEND_BUFSIZE)
 * 的十几倍; 给足缓冲可以减少 send 阻塞轮次。上限仍受全局配置约束。
 */
#define HTTP_SNDBUF_SIZE  32768

static int http_write_chunk(void *ctx, const char *data, size_t length)
{
  return (int)send(*(int *)ctx, data, length, 0);
}

static void http_pause_tx(void *ctx)
{
  (void)ctx;
  usleep(HTTP_SEND_GAP_US);
}

/* HTTP 请求鉴权 Key (Authorization: Bearer), wifi_set_http_auth 设置 */
static char g_http_api_key[80];

/****************************************************************************
 * Name: wifi_set_http_auth
 *
 * 设置 HTTP 请求的 API Key (Authorization: Bearer <key>)。
 * 供云端鉴权接口 (如 MiMo) 使用; NULL 清除。
 ****************************************************************************/
void wifi_set_http_auth(const char *api_key)
{
  if (api_key != NULL)
    {
      strlcpy(g_http_api_key, api_key, sizeof(g_http_api_key));
    }
  else
    {
      g_http_api_key[0] = '\0';
    }
}

/****************************************************************************
 * Name: wifi_connect
 *
 * 用 wireless ioctl 连 WPA2-PSK。若板子已用 wapi 连过网, 可直接返回成功。
 * ⚠️ 上板核验: 若 esp32s3 wifi 驱动不支持 SIOCSIWENCODEEXT, 改用 wapi。
 ****************************************************************************/
int wifi_connect(const char *ssid, const char *password)
{
  struct iwreq iwr;
  struct iw_encode_ext *ext;
  char ext_buf[sizeof(struct iw_encode_ext) + 64];
  int sock;

  if (ssid == NULL || password == NULL)
    {
      return FOCUS_ERR_PARAM;
    }

  if (wifi_is_connected())
    {
      return FOCUS_OK;
    }

  sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock < 0)
    {
      return FOCUS_ERR_NET_DISCONN;
    }

  /* 1. 先设密码: 驱动 esp_wifi_sta_password 从 u.encoding.pointer
   *    读 struct iw_encode_ext (key/key_len/alg)。 */
  ext = (struct iw_encode_ext *)ext_buf;
  memset(ext, 0, sizeof(*ext));
  ext->alg     = IW_ENCODE_ALG_CCMP;
  ext->key_len = (uint16_t)strlen(password);
  memcpy(ext->key, password, ext->key_len);

  memset(&iwr, 0, sizeof(iwr));
  strlcpy(iwr.ifr_name, WIFI_IFNAME, IFNAMSIZ);
  iwr.u.encoding.pointer = ext;
  iwr.u.encoding.length  = (uint16_t)(sizeof(*ext) + ext->key_len);
  if (ioctl(sock, SIOCSIWENCODEEXT, (unsigned long)&iwr) < 0)
    {
      close(sock);
      return FOCUS_ERR_NET_DISCONN;
    }

  /* 2. 再设 SSID: IW_ESSID_ON 触发驱动 ops->connect()。
   *    顺序必须密码在前 (SSID 时即连接)。 */
  memset(&iwr, 0, sizeof(iwr));
  strlcpy(iwr.ifr_name, WIFI_IFNAME, IFNAMSIZ);
  iwr.u.essid.flags   = IW_ESSID_ON;
  iwr.u.essid.length  = (uint16_t)strlen(ssid);
  iwr.u.essid.pointer = (FAR char *)ssid;
  if (ioctl(sock, SIOCSIWESSID, (unsigned long)&iwr) < 0)
    {
      close(sock);
      return FOCUS_ERR_NET_DISCONN;
    }

  close(sock);
  return FOCUS_OK;
}

/****************************************************************************
 * Name: wifi_is_connected
 *
 * 通过 wlan0 的 IFF_UP + IFF_RUNNING 判断是否已联网。
 ****************************************************************************/
bool wifi_is_connected(void)
{
  struct ifreq ifr;
  int sock = socket(AF_INET, SOCK_DGRAM, 0);

  if (sock < 0)
    {
      return false;
    }

  memset(&ifr, 0, sizeof(ifr));
  strncpy(ifr.ifr_name, WIFI_IFNAME, IFNAMSIZ);
  if (ioctl(sock, SIOCGIFFLAGS, (unsigned long)&ifr) < 0)
    {
      close(sock);
      return false;
    }

  close(sock);
  return (ifr.ifr_flags & IFF_UP) && (ifr.ifr_flags & IFF_RUNNING);
}

/****************************************************************************
 * Name: wifi_get_rssi
 *
 * 通过 wireless ioctl SIOCGIWSTATS 取信号强度 (dBm)。
 ****************************************************************************/
int wifi_get_rssi(void)
{
  struct iwreq iwr;
  int sock = socket(AF_INET, SOCK_DGRAM, 0);

  if (sock < 0)
    {
      return 0;
    }

  memset(&iwr, 0, sizeof(iwr));
  strncpy(iwr.ifr_name, WIFI_IFNAME, IFNAMSIZ);
  if (ioctl(sock, SIOCGIWSTATS, (unsigned long)&iwr) < 0)
    {
      close(sock);
      return 0;
    }

  close(sock);
  return (int)iwr.u.qual.level;
}

/****************************************************************************
 * Name: parse_url
 *
 * 从 "http://host[:port]/path" 解析出 host/port/path。
 ****************************************************************************/
static int parse_url(const char *url, char *host, size_t hostlen,
                     uint16_t *port, char *path, size_t pathlen)
{
  const char *p;
  const char *host_start;
  const char *path_start;
  const char *colon;
  size_t host_len;

  if (strncmp(url, "http://", 7) != 0)
    {
      return -1;
    }
  p = url + 7;

  host_start = p;
  path_start = strchr(p, '/');
  if (path_start == NULL)
    {
      path_start = p + strlen(p);
    }

  host_len = (size_t)(path_start - host_start);
  if (host_len == 0 || host_len >= hostlen)
    {
      return -1;
    }

  colon = memchr(host_start, ':', host_len);
  if (colon != NULL)
    {
      *port = (uint16_t)atoi(colon + 1);
      host_len = (size_t)(colon - host_start);
    }
  else
    {
      *port = 80;
    }

  memcpy(host, host_start, host_len);
  host[host_len] = '\0';

  snprintf(path, pathlen, "%s", path_start);

  return 0;
}

/****************************************************************************
 * 长连接 (HTTP keep-alive)
 *
 * 感知每 ~5s 上传一帧, 帧体(原始 RGB565, 320x240) base64 后约 205KB。
 * 若每帧都 socket/connect/send/close:
 *   - 205KB 是 TCP 发送缓冲(CONFIG_NET_SEND_BUFSIZE)的十几倍;
 *   - 连接建立的速率又远快于 TIME_WAIT 回收;
 * 两者叠加, 约 10 帧后 nuttx 的 TCP/IOB 池见底, connect 直接失败 →
 * FOCUS_ERR_NET_DISCONN(-20)。
 *
 * 因此整局复用同一条 TCP 连接: 请求带 Connection: keep-alive, 响应按
 * Content-Length 读满即返回 (keep-alive 下对端不会关连接, 不能再沿用
 * "读到对端关闭"来定界)。任何一步出错就丢弃连接, 下次调用重建。
 *
 * 线程约定: wifi_http_post 只从主循环调用(感知 / 报告上报), 单线程,
 * 故这些静态量无需加锁。
 ****************************************************************************/

static int      g_http_sock = -1;
static char     g_http_host[64];
static uint16_t g_http_port;

static void http_conn_drop(void)
{
  if (g_http_sock >= 0)
    {
      close(g_http_sock);
      g_http_sock = -1;
    }

  g_http_host[0] = '\0';
  g_http_port = 0;
}

/* 取一条到 host:port 的可用连接; 已有同目标的连接就直接复用。
 * 失败返回 -1 (由调用方决定是否重试)。 */
static int http_conn_get(const char *host, uint16_t port)
{
  struct sockaddr_in addr;
  struct timeval tv;
  struct hostent *he;
  int sndbuf = HTTP_SNDBUF_SIZE;
  int sock;

  if (g_http_sock >= 0 && g_http_port == port &&
      strcmp(g_http_host, host) == 0)
    {
      return g_http_sock;
    }

  http_conn_drop();

  he = gethostbyname(host);
  if (he == NULL)
    {
      return -1;
    }

  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0)
    {
      return -1;
    }

  tv.tv_sec = HTTP_TIMEOUT_SEC;
  tv.tv_usec = 0;
  if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0 ||
      setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv)) < 0 ||
      setsockopt(sock, SOL_SOCKET, SO_SNDBUF, &sndbuf, sizeof(sndbuf)) < 0)
    {
      printf("[wifi] HTTP socket configuration failed errno=%d\n", errno);
      close(sock);
      return -1;
    }

  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  memcpy(&addr.sin_addr, he->h_addr, he->h_length);

  if (connect(sock, (FAR struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
      close(sock);
      return -1;
    }

  g_http_sock = sock;
  snprintf(g_http_host, sizeof(g_http_host), "%s", host);
  g_http_port = port;
  return sock;
}

/* 服务端是否要求用完即关 (Connection: close)。 */
static bool http_wants_close(const char *resp)
{
  return strstr(resp, "Connection: close") != NULL ||
         strstr(resp, "connection: close") != NULL;
}

/****************************************************************************
 * 读一个完整 HTTP 响应 (响应头 + 响应体) 到 resp。
 *
 * keep-alive 下不能靠"读到对端关闭"定界, 必须按 Content-Length 读满。
 * 返回: >0 = 写入 resp 的字节数; 0 = 对端已关闭; <0 = 出错/头不完整。
 ****************************************************************************/
static int http_read_response(int sock, char *resp, size_t maxlen)
{
  char hdr[1024];
  size_t hlen = 0;
  size_t hdr_bytes;
  size_t body_have;
  size_t body_need = (size_t)-1;   /* (size_t)-1 = 未知, 退化为读到关闭 */
  size_t n;
  char *head_end;
  const char *cl;
  int r;

  /* 1. 读响应头 */
  while (hlen < sizeof(hdr) - 1)
    {
      r = recv(sock, hdr + hlen, (sizeof(hdr) - 1) - hlen, 0);
      if (r <= 0)
        {
          return (hlen > 0) ? -1 : r;
        }

      hlen += (size_t)r;
      hdr[hlen] = '\0';
      if (strstr(hdr, "\r\n\r\n") != NULL)
        {
          break;
        }
    }

  head_end = strstr(hdr, "\r\n\r\n");
  if (head_end == NULL)
    {
      return -1;                   /* 头不完整或超长 */
    }

  hdr_bytes = (size_t)(head_end - hdr) + 4;

  /* 2. 解析 Content-Length */
  cl = strstr(hdr, "Content-Length:");
  if (cl == NULL)
    {
      cl = strstr(hdr, "content-length:");
    }

  if (cl != NULL)
    {
      body_need = (size_t)atoi(cl + strlen("Content-Length:"));
    }

  /* 3. 头部搬进 resp (调用方按 \r\n\r\n 跳过头部, 保持原有约定) */
  if (hdr_bytes >= maxlen)
    {
      return -1;
    }

  memcpy(resp, hdr, hdr_bytes);
  n = hdr_bytes;

  body_have = hlen - hdr_bytes;
  if (body_have > maxlen - 1 - n)
    {
      return -1;                   /* 装不下就必须丢弃连接, 见调用方 */
    }

  if (body_have > 0)
    {
      memcpy(resp + n, hdr + hdr_bytes, body_have);
      n += body_have;
    }

  /* 4. 按 Content-Length 补满剩余响应体 */
  while (n < maxlen - 1)
    {
      if (body_need != (size_t)-1 && (n - hdr_bytes) >= body_need)
        {
          break;
        }

      r = recv(sock, resp + n, maxlen - 1 - n, 0);
      if (r <= 0)
        {
          break;
        }

      n += (size_t)r;
    }

  resp[n] = '\0';
  return (int)n;
}

/****************************************************************************
 * Name: wifi_http_post
 *
 * HTTP POST (阻塞, 复用长连接)。超时 HTTP_TIMEOUT_SEC, 失败重连重发 1 次。
 * 返回: 0=成功, FOCUS_ERR_NET_DISCONN=连接失败, FOCUS_ERR_TIMEOUT=超时。
 ****************************************************************************/
int wifi_http_post(const char *url, const char *body,
                   char *resp, size_t maxlen)
{
  char host[64];
  char path[256];
  char req[2048];
  uint16_t port;
  int attempt;

  if (url == NULL || body == NULL || resp == NULL || maxlen == 0)
    {
      return FOCUS_ERR_PARAM;
    }

  if (parse_url(url, host, sizeof(host), &port, path, sizeof(path)) < 0)
    {
      return FOCUS_ERR_PARAM;
    }

  for (attempt = 0; attempt < 2; attempt++)
    {
      int sock;
      int req_len;
      int n;

      /* 复用长连接: 目标没变就直接拿已建好的 socket, 只有断开/换目标才重连 */
      sock = http_conn_get(host, port);
      if (sock < 0)
        {
          http_conn_drop();
          if (attempt == 0)
            {
              continue;
            }
          return FOCUS_ERR_NET_DISCONN;
        }

      {
        char auth_hdr[160] = "";
        if (g_http_api_key[0] != '\0')
          {
            snprintf(auth_hdr, sizeof(auth_hdr),
                     "Authorization: Bearer %s\r\n", g_http_api_key);
          }

        /* 请求头 (固定小缓冲) 与请求体 (base64 图片, 可达上百 KB) 分开发送,
         * 避免大 body 塞不进栈上 req[] 返回 FOCUS_ERR_PARAM */
        req_len = snprintf(req, sizeof(req),
                           "POST %s HTTP/1.1\r\n"
                           "Host: %s\r\n"
                           "Content-Type: application/json\r\n"
                           "%s"
                           "Content-Length: %d\r\n"
                           "Connection: keep-alive\r\n\r\n",
                           path, host, auth_hdr, (int)strlen(body));
        if (req_len < 0 || (size_t)req_len >= sizeof(req))
          {
            http_conn_drop();
            return FOCUS_ERR_PARAM;
          }

        if (wifi_send_all(&sock, req, (size_t)req_len, HTTP_SEND_CHUNK,
                          http_write_chunk, http_pause_tx) < 0 ||
            wifi_send_all(&sock, body, strlen(body), HTTP_SEND_CHUNK,
                          http_write_chunk, http_pause_tx) < 0)
          {
            int send_errno = errno;
            http_conn_drop();
            if (send_errno == EAGAIN || send_errno == EWOULDBLOCK)
              {
                return FOCUS_ERR_TIMEOUT;
              }
            if (attempt == 0)
              {
                continue;
              }
            return FOCUS_ERR_NET_DISCONN;
          }

      }

      /* 按 Content-Length 读满整个响应 (keep-alive 下对端不会关连接) */
      n = http_read_response(sock, resp, maxlen);
      if (n > 0)
        {
          /* 服务端可能主动要求关闭 (例如空闲超时), 那就别留着这条连接 */
          if (http_wants_close(resp))
            {
              http_conn_drop();
            }
          return FOCUS_OK;
        }

      /* 连接已不可用: 丢弃后重连重发一次 */
      http_conn_drop();
      if (attempt == 0)
        {
          continue;
        }

      return (n == 0) ? FOCUS_ERR_NET_DISCONN : FOCUS_ERR_TIMEOUT;
    }

  return FOCUS_ERR_TIMEOUT;
}

/****************************************************************************
 * Name: 独立测试 (编译时 -DTEST_WIFI)
 ****************************************************************************/
#ifdef TEST_WIFI
int main(void)
{
  char resp[4096];
  int ret;

  ret = wifi_connect("SSID", "PASSWORD");
  printf("wifi_connect=%d connected=%d rssi=%d dBm\n",
         ret, wifi_is_connected(), wifi_get_rssi());

  ret = wifi_http_post("http://httpbin.org/post",
                       "{\"test\":1}", resp, sizeof(resp));
  printf("HTTP POST=%d\n%s\n", ret, resp);
  return 0;
}
#endif
