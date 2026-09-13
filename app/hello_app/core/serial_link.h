/****************************************************************************
 * FOCUS AIoT - 上位机串口链路 (core/serial_link.h)
 *
 * 负责人: 万思源
 *
 * 用途: 设备与电脑之间**走 USB 串口**传图与回传识别结果, 完全绕开 WiFi。
 *
 * 背景: 设备经 WiFi 发送较大请求体时会触发 openvela ESP32-S3 SMP 移植的
 *       WiFi 驱动崩溃 (崩溃栈在 esf_buf_alloc_dynamic)。改用 USB 串口后
 *       不经过 WiFi 发送路径, 从根本上规避该问题。
 *
 * 协议 (行文本, 便于与串口日志共存):
 *   设备 → 电脑:  \n###IMG <base64长度>\n<base64>\n###ENDIMG\n
 *   电脑 → 设备:  \n###RESULT <json长度>\n<json>\n###ENDRESULT\n
 *   设备 → 电脑:  \n###REPORT <json长度>\n<json>\n###ENDREPORT\n
 *
 * 电脑侧由 tools/serial_bridge.py 实现 (读串口 → 调视觉模型 → 回写)。
 ****************************************************************************/

#ifndef FOCUS_AIOT_CORE_SERIAL_LINK_H
#define FOCUS_AIOT_CORE_SERIAL_LINK_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* 把一张 JPEG 经串口发给上位机, 等待并读回识别结果 (OpenAI 兼容信封 JSON)。
 * jpeg     : JPEG 数据
 * jpeg_len : 长度
 * result   : 输出缓冲 (存上位机回传的 JSON)
 * cap      : 输出缓冲容量
 * 返回: 0=成功, -1=失败/超时 */
int serial_detect(const uint8_t *jpeg, size_t jpeg_len,
                  char *result, size_t cap);

/* 把一局学习统计经串口发给上位机 (由上位机转投服务器生成报告)。
 * json: 统计 JSON (见 ui/mimo.c 的请求体格式)
 * 返回: 0=成功, -1=失败 */
int serial_send_report(const char *json);

#ifdef __cplusplus
}
#endif

#endif /* FOCUS_AIOT_CORE_SERIAL_LINK_H */
