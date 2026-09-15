/****************************************************************************
 * FOCUS AIoT - RGB565 → JPEG 编码 (core/rgb565_jpeg.h)
 *
 * 基于 TinyJPEG (Baseline JPEG, header-only, public domain)。
 * 摄像头输出 RGB565, 云端 MiMo 需要 JPEG, 由本模块做转换。
 *
 * 返回: 0=成功, -1=失败
 ****************************************************************************/

#ifndef FOCUS_AIOT_CORE_RGB565_JPEG_H
#define FOCUS_AIOT_CORE_RGB565_JPEG_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* RGB565 → JPEG (Baseline, quality 2 足够云端识别)。
 * rgb565:  输入 RGB565 像素流 (width*height*2 字节)
 * jpeg_out: 输出 JPEG 缓冲区 (调用方分配, 建议 ≥ width*height 字节)
 * jpeg_size: 输入缓冲区容量, 输出实际 JPEG 大小
 * 返回: 0=成功 */
int rgb565_to_jpeg(const uint8_t *rgb565, int width, int height,
                   uint8_t *jpeg_out, size_t *jpeg_size);

/* 2x2 抽样降采样 RGB565 (如 320x240 -> 160x120), 返回目标帧字节数。
 * 用于「设备端不编码」方案: 全尺寸 base64 后约 205KB 会压垮 TCP 发送,
 * 降到 160x120 约 51KB。dst 需 sw/2 * sh/2 * 2 字节。 */
size_t rgb565_downsample_2x(const uint8_t *src, int sw, int sh,
                            uint8_t *dst);

#ifdef __cplusplus
}
#endif

#endif /* FOCUS_AIOT_CORE_RGB565_JPEG_H */
