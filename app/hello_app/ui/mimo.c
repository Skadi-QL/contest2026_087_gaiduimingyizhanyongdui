#include "../api/error.h"
#include "../api/mimo.h"
#include "../api/wifi.h"

#include <stdio.h>
#include <string.h>

/* 学习报告上传端点: 设备把本局统计 POST 给中继, 中继调 MiMo 生成建议
 * 并存入网页报告 (/report 页查看)。设备屏只显示"请看网页", 长文本留给网页。
 * 与 perception.c 的识图 endpoint 同一个中继, 鉴权 token 也相同
 * (wifi_set_http_auth 已设)。 */
#ifndef REPORT_API_URL
#  define REPORT_API_URL "http://106.15.192.201:8060/report"
#endif

static void local_advice(const session_stats_t *stats, char *output,
                         size_t output_size)
{
  unsigned long effective_minutes =
      (unsigned long)(stats->effective_duration_sec / 60U);
  if (stats->current_mode == 0)
    {
      snprintf(output, output_size,
               "严格模式下你坚持了 %lu 分钟，下次减少分心次数会更好！",
               effective_minutes);
    }
  else
    {
      snprintf(output, output_size,
               "你今天有效学习了 %lu 分钟，已经很棒了！继续加油！",
               effective_minutes);
    }
}

/**
 * 把本局学习统计上传给中继, 由中继调 MiMo 生成建议并存入网页报告。
 * 浏览器访问 <中继>/report 查看完整报告 (含建议正文)。
 *
 * 设备屏 240x240 建议区最多显示约 36 个汉字, 装不下完整建议, 因此屏上
 * 只提示"完整报告请见网页", 这里不解析响应。advice_out 仍填本地兜底
 * 文案, 供将来想在屏上显示一句话时使用。
 */
int mimo_get_advice(session_stats_t *stats,
                    uint8_t distraction_by_type[4],
                    char *advice_out, size_t max_len)
{
  char request[512];
  char response[512];

  if (advice_out == NULL || max_len == 0) return FOCUS_ERR_PARAM;
  advice_out[0] = '\0';
  if (stats == NULL || distraction_by_type == NULL)
    {
      snprintf(advice_out, max_len, "学习已完成，请稍后查看详细建议。");
      return 0;
    }

  if (wifi_is_connected())
    {
      snprintf(request, sizeof(request),
               "{\"total_min\":%lu,\"effective_min\":%lu,"
               "\"distractions\":[%u,%u,%u,%u],\"focus_score\":%u,"
               "\"mode\":\"%s\"}",
               (unsigned long)(stats->total_duration_sec / 60U),
               (unsigned long)(stats->effective_duration_sec / 60U),
               distraction_by_type[0], distraction_by_type[1],
               distraction_by_type[2], distraction_by_type[3],
               stats->focus_score,
               stats->current_mode == 0 ? "strict" : "gentle");

      /* 响应仅供中继记账, 设备不解析 (建议正文在网页上) */
      (void)wifi_http_post(REPORT_API_URL, request,
                           response, sizeof(response));
    }

  local_advice(stats, advice_out, max_len);
  return 0;
}
