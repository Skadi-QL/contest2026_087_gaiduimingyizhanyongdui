/****************************************************************************
 * FOCUS AIoT - RGB565 → JPEG 编码 (core/rgb565_jpeg.c)
 *
 * 摄像头输出 RGB565, 云端 MiMo 识图需要 JPEG。
 * 本模块: RGB565 → RGB888 → TinyJPEG (Baseline JPEG) 编码。
 *
 * 基于 TinyJPEG (https://github.com/serge-rgb/TinyJPEG), public domain。
 ****************************************************************************/

#define TJE_IMPLEMENTATION
#include "../third_party/tiny_jpeg.h"

#include "rgb565_jpeg.h"

#include <stdlib.h>
#include <string.h>

/* ---- JPEG 输出收集 (内存回调) ---- */
typedef struct
{
  uint8_t *buf;    /* 输出缓冲区 */
  size_t   cap;    /* 容量 */
  size_t   used;   /* 已写字节 */
  int      overflowed;  /* 输出超出容量 (会截断, 上层需扩大缓冲) */
} jpeg_sink_t;

/* 上传图降采样倍数 (1=原图, 2=320x240→160x120)。调大可显著减小 WiFi
 * 发送量 (base64 请求体), 但识别精度下降; 1 时请求体可达 100KB+。 */
#ifndef RGB565_JPEG_DOWNSCALE
#  define RGB565_JPEG_DOWNSCALE 2
#endif

/* RGB888 转换暂存缓冲: 一次分配反复使用 (见 rgb565_to_jpeg 注释) */
static uint8_t *g_rgb_scratch;
static int      g_rgb_scratch_px;

static void jpeg_write_cb(void *context, void *data, int size)
{
  jpeg_sink_t *sink = (jpeg_sink_t *)context;

  if (sink->used + (size_t)size <= sink->cap)
    {
      memcpy(sink->buf + sink->used, data, (size_t)size);
      sink->used += (size_t)size;
    }
  else
    {
      /* 溢出: 丢弃并标记。静默截断会丢 JPEG 的 EOI 标记, 云端解码 400。 */
      sink->overflowed = 1;
    }
}

/****************************************************************************
 * Name: rgb565_to_jpeg
 ****************************************************************************/
int rgb565_to_jpeg(const uint8_t *rgb565, int width, int height,
                   uint8_t *jpeg_out, size_t *jpeg_size)
{
  uint8_t *rgb;
  jpeg_sink_t sink;
  int ok;
  int n;
  int i;
  int out_w;
  int out_h;

  if (rgb565 == NULL || jpeg_out == NULL || jpeg_size == NULL ||
      width <= 0 || height <= 0)
    {
      return -1;
    }

  /* 降采样: 设备经 WiFi 上传 base64 图, 320x240 JPEG 常有 60~90KB,
   * base64 后 80~120KB —— 过大会把 WiFi 发送路径压垮 (真机实测
   * StoreProhibited 崩溃)。默认 2 倍降到 160x120, 请求体缩到 ~25KB。
   * 必须能整除且结果为 8 的倍数 (JPEG MCU 尺寸)。 */
  out_w = width  / RGB565_JPEG_DOWNSCALE;
  out_h = height / RGB565_JPEG_DOWNSCALE;
  if (out_w < 8 || out_h < 8 || (out_w & 7) != 0 || (out_h & 7) != 0)
    {
      return -1;
    }

  /* RGB565 → RGB888 (3 通道, TinyJPEG 需要)。
   * 缓冲一次性分配并复用 (不每帧 malloc/free): 每帧上百 KB 的分配/释放
   * 会造成堆碎片, 严重时分配器会复用 CPU1 IDLE 栈所在的堆块, 导致崩溃。 */
  n = out_w * out_h;
  if (g_rgb_scratch == NULL || g_rgb_scratch_px < n)
    {
      free(g_rgb_scratch);
      g_rgb_scratch = malloc((size_t)n * 3);
      if (g_rgb_scratch == NULL)
        {
          g_rgb_scratch_px = 0;
          return -1;
        }
      g_rgb_scratch_px = n;
    }
  rgb = g_rgb_scratch;

  /* 按 RGB565_JPEG_DOWNSCALE 块取样 (取每块左上角像素, 够用且快) */
  for (i = 0; i < n; i++)
    {
      int ox = i % out_w;
      int oy = i / out_w;
      size_t si = ((size_t)oy * RGB565_JPEG_DOWNSCALE * width +
                   (size_t)ox * RGB565_JPEG_DOWNSCALE);
      uint16_t p = (uint16_t)(rgb565[si * 2]) |
                   (uint16_t)(rgb565[si * 2 + 1]) << 8;
      uint8_t r5 = (uint8_t)((p >> 11) & 0x1F);
      uint8_t g6 = (uint8_t)((p >> 5) & 0x3F);
      uint8_t b5 = (uint8_t)(p & 0x1F);

      rgb[i * 3]     = (uint8_t)((r5 << 3) | (r5 >> 2));   /* R */
      rgb[i * 3 + 1] = (uint8_t)((g6 << 2) | (g6 >> 4));   /* G */
      rgb[i * 3 + 2] = (uint8_t)((b5 << 3) | (b5 >> 2));   /* B */
    }

  /* TinyJPEG 编码 (quality 2)。
   * 注意: 细节多的帧输出可能 > out_w*out_h, 调用方缓冲必须给足,
   * 否则截断丢 EOI 标记, 服务端解码 400。 */
  sink.buf        = jpeg_out;
  sink.cap        = *jpeg_size;
  sink.used       = 0;
  sink.overflowed = 0;

  ok = tje_encode_with_func(jpeg_write_cb, &sink, 2,
                            out_w, out_h, 3, rgb);

  /* 不 free: g_rgb_scratch 复用 (见上) */

  if (!ok || sink.overflowed)
    {
      return -1;
    }

  *jpeg_size = sink.used;
  return 0;
}
