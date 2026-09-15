# Claude Code 会话记录

## 会话信息
- **会话ID**: `a9d08b0b-862d-4ecc-82a9-2d02227810d5`
- **工作目录**: `C:\temp\focus_pr`
- **开始时间**: 2026-08-28 15:09:26
- **消息数量**: 108

---

## 对话记录

### [2026-08-28 15:09:26] 用户

update

---

### [2026-08-28 15:10:19] AI

[思考] The user typed "update". This is a non-technical user, Chinese, replies tersely, wants me to proactively handle things. "update" is very ambiguous. Let me think about what they might mean.

Context: memory shows they're a non-technical user, Chinese, short replies. "update" alone is ambiguous. It could mean:
1. Update Claude Code itself
2. Update some software
3. Update a config

Given the terseness, I should ask what they want to update, but keep it brief. Actually, they're non-technical and want me to proactively handle things. But "update" is genuinely ambiguous — I can't just guess.

Let me respond in Chinese (they use Chinese), briefly ask what to update.

---

### [2026-08-28 15:10:20] AI

你想更新什么？比如：

1. **Claude Code 本身**（升级到最新版）
2. **某个软件/程序**
3. **系统或驱动**

告诉我具体要更新哪个，我来帮你处理。

---

### [2026-08-28 15:11:42] 用户

1

---

### [2026-08-28 15:11:46] AI

[思考] The user wants to update Claude Code itself. Let me check how to do that. Claude Code is installed. The update command is typically `claude update` or via npm. Let me check.

For Claude Code, updating is done with `claude update` command, or `npm install -g @anthropic-ai/claude-code` if installed via npm. On Windows, it might be installed via the native installer.

Let me first check how it's installed.

---

### [2026-08-28 15:11:46] AI

[工具调用] Bash: {"command": "claude --version 2>&1; echo \"---\"; where claude 2>&1", "description": "Check current Claude Code version and install location"}

---

### [2026-08-28 15:11:50] 用户

[工具结果] 2.1.250 (Claude Code)
---
C:\Users\user\.local\bin\claude.exe

---

### [2026-08-28 15:11:53] AI

[思考] Claude Code is installed at `C:\Users\user\.local\bin\claude.exe`, version 2.1.250. This is the native installer location (`.local\bin`), not npm global. 

To update, the command is `claude update`. Let me run it.

---

### [2026-08-28 15:11:54] AI

[工具调用] Bash: {"command": "claude update 2>&1", "description": "Update Claude Code to latest version", "timeout": 300000}

---

### [2026-08-28 15:12:05] 用户

[工具结果] Current version: 2.1.250
Checking for updates to latest version...
Claude Code is up to date (2.1.250)

---

### [2026-08-28 15:12:08] AI

Claude Code 已经是最新版了（2.1.250），无需更新。✅

---

### [2026-08-28 15:12:18] 用户

GitHub Copilot Chat Assistant.

先确认你的目标再继续：你是想把“单张（或少量）JPEG 图片”用于动作识别，还是有短视频/多帧但每帧都以 JPEG 存储？目标平台是服务器、移动端还是嵌入式设备？输出是动作类别（分类）还是动作片段定位？请回答这三点，我会给出针对性的方案和代码样例。

下面先给出简明可选方案与最佳实践，便于你快速选择方向。

1) 情况区分（关键）
- 单张 JPEG（单帧） → 极有限的信息，通常只能做静态动作/姿态推断（如“站立/坐下/举手”）；效果受限。
- 多张/短序列的 JPEG（帧序列）→ 可以做时序动作识别，准确度明显提升。
- 小输入（低分辨率、计算受限或少量训练数据）→ 需轻量模型、数据增强与迁移学习。

2) 常见方案（按输入类型）
- 单张图像（静态）：
  - 姿态关键点法：先用轻量人体姿态估计器（MediaPipe/Lightweight HRNet/OpenPose-lite）得到关键点序列或骨架图，再用小型 MLP / 1D-CNN / GCN（像 ST-GCN）做分类。对少量分辨率／视角变化较鲁棒。
  - 外观分类器：MobileNet/EfficientNet-lite 在单帧上做分类（迁移学习），适合动作与明显静态姿势关联的场景。
- 多帧序列（首选）：
  - 2D CNN + temporal pooling（TSN）或 2D CNN + temporal shift module（TSM）——轻量又效果好。
  - 3D CNN（C3D、I3D、R(2+1)D、SlowFast）——精度高但计算/内存大。
  - 流光/光流两流网络（RGB + Optical Flow）——对运动敏感，精度好但计算量增加。
- 关键点时序建模：
  - 用 ST-GCN 或小型 Transformer 对姿态时间序列建模（非常适合低分辨率或隐私场景，只传输关键点）。

3) 轻量化与部署
- 模型选择：MobileNetV3 / EfficientNet-Lite / ShuffleNet / MobileNet+TSM。
- 压缩：量化（int8）、剪枝、知识蒸馏（teacher: larger model）。
- 推理引擎：TensorRT、TFLite、ONNX Runtime（带量化）、OpenVINO（Intel）。
- 延迟优化：batch=1、操作融合、输入尺寸降到 160–224。

4) 数据预处理（针对 JPEG 小输入）
- Decode JPEG -> resize（保持长宽比或中心裁剪）到模型输入（例如 224x224 或 160x160）。
- 归一化（ImageNet 均值/方差或自己数据统计）。
- 数据增强：随机裁剪、水平翻转、颜色抖动、随机噪声、仿射变换；对时序数据做时间抖动/帧采样。
- 对姿态方法：对关键点做平移/缩放归一化、丢点鲁棒处理。

5) 训练与评价
- 迁移学习：在 Kinetics/UCF/HMDB 预训练权重上微调（若为视频模型）。
- 损失：交叉熵；数据不平衡可用加权交叉熵或 focal loss。
- 指标：top-1/top-5, precision/recall, F1；时序任务可用 mAP。
- 验证：按场景拆分（避免同一人同时出现在 train/test），做混淆矩阵查看易混类。

6) 常用工具与库
- 训练/模型：PyTorch (torchvision、MMAction2)、TensorFlow (tf.keras, TFActions)。
- 姿态估计：MediaPipe, OpenPose, AlphaPose, HRNet。
- 推理/优化：ONNX, TensorRT, TFLite, OpenVINO。
- 数据集：Kinetics, UCF101, HMDB51, NTU RGB+D（如果有人体骨架），AVA（视频段级）。

7) 简短建议（如果目标是“在受限设备上用单/少量 JPEG 做动作分类”）
- 优先用姿态关键点流水线（MediaPipe 提取骨架）＋轻量 MLP/1D-CNN/ST-GCN。
- 若必须用 RGB：MobileNetV3 + TSM（把少量帧作为输入通道或时间维度）并做 int8 量化。
- 使用迁移学习与充分的数据增强补偿数据不足。

如果你确认了下面几点，我可以立刻给出实现代码或完整流水线：
- 输入形式：单张图片 还是 N 帧（N=?）
- 目标平台：服务器 / 手机（Android/iOS） / 嵌入式（Raspberry Pi / MCU）
- 期望模型大小或延迟上限（例如 <10 MB，或延迟 <50 ms）
- 类别数与是否有标注数据（有/无，数量）

你想先看哪一项？代码样例（PyTorch）还是姿态＋轻量分类完整 pipeline？

---

### [2026-08-28 15:12:29] AI

[思考] The user pasted what looks like a response from GitHub Copilot Chat Assistant — a long technical answer about JPEG image action recognition. But there's no actual question from the user here. It seems like the user copy-pasted a Copilot Chat response into the Claude Code session.

Wait, let me re-read. The user's message is entirely the GitHub Copilot Chat Assistant's response. There's no question directed at me. This is confusing.

Actually, looking at the memory context: user is non-technical, Chinese, replies tersely, wants me to proactively handle things.

So what happened? The user pasted a response from GitHub Copilot about action recognition from JPEG images. Maybe they want me to:
1. Explain/simplify this response
2. Continue this task (do action recognition)
3. Something else

Actually, the most likely scenario: the user is non-technical, they asked Copilot something (or pasted it here), and now they've dumped this Copilot response into Claude Code. They probably want me to do something with it — but what?

Given the user is non-technical and terse, and this is a confusing paste, I should ask for clarification in simple Chinese. But wait — I should be careful. The memory says they want me to proactively handle things (主动代办), reply tersely.

Let me think about what's most likely. The user pasted a GitHub Copilot Chat response. The title is "GitHub Copilot Chat Assistant." This looks like they copied the entire Copilot answer and pasted it here, perhaps wanting:
- Me to summarize it
- Me to continue where Copilot left off
- Me to actually implement something

Actually, maybe the user's actual task is: they want to do action recognition from JPEG images, and they pasted a Copilot response as context, and they want ME to help with this task (maybe implement it).

But there's no explicit question. The most reasonable thing: ask a brief clarifying question in Chinese. Since they're non-technical, I should keep it simple.

Actually, let me reconsider. The pasted content ends with questions from Copilot: "你想先看哪一项？代码样例（PyTorch）还是姿态＋轻量分类完整 pipeline？"

Maybe the user is sharing this and wants me to... take over this conversation? Or maybe they accidentally pasted it.

Given the ambiguity and that this is a substantial technical task, I should ask what they want me to do with this. But keep it very brief and in Chinese.

Let me respond tersely in Chinese, asking what they want: do they want me to implement this action-recognition thing? What's their actual goal?

Actually, I think the cleanest is to just ask a short clarifying question. The user is non-technical, so I should translate the situation simply.

Let me respond in Chinese, briefly.

---

### [2026-08-28 15:12:31] AI

你贴的是 Copilot 的回复，但没说你到底要我做什么。

请用一句话告诉我你的目标，比如：
- 识别图片里的人**在做什么动作**（站/坐/举手…）？
- 图片是**一张**还是**很多张连续帧**？
- 想在**电脑/手机/小设备**上跑？

告诉我这几点，我直接给你能用的代码。

---

### [2026-08-28 15:14:34] 用户

识别动作 连续帧jpeg格式 小设备 最好是成品 可以接入C:\temp文件夹下的项目

---

### [2026-08-28 15:14:38] AI

[思考] The user wants:
1. Action recognition (识别动作)
2. Continuous frames, JPEG format (连续帧jpeg格式)
3. Small device (小设备)
4. Best if it's a finished product (最好是成品)
5. Can integrate into a project under C:\temp folder (可以接入C:\temp文件夹下的项目)

Let me first explore C:\temp to understand what project is there.

The user is non-technical, wants a finished product. Let me look at the C:\temp folder first to understand the existing project.

---

### [2026-08-28 15:14:39] AI

[工具调用] Bash: {"command": "ls -la /c/temp 2>&1; echo \"=== 递归结构 ===\"; find /c/temp -maxdepth 2 -type d 2>&1 | head -50", "description": "List C:\\temp contents and directory structure"}

---

### [2026-08-28 15:14:42] 用户

[工具结果] total 852
drwxr-xr-x 1 user 197121      0 Aug 26 14:18 .
drwxr-xr-x 1 user 197121      0 Aug 21 15:08 ..
-rw-r--r-- 1 user 197121 767751 Aug 26 14:08 20260731_055914-ubuntu.md
-rw-r--r-- 1 user 197121   7080 Aug 26 14:09 DEVELOPMENT_TASKS (1).md
-rw-r--r-- 1 user 197121   9143 Aug 26 14:09 DEVELOPMENT_TASKS (2).md
-rw-r--r-- 1 user 197121   5820 Aug 26 14:09 DEVELOPMENT_TASKS.md
drwxr-xr-x 1 user 197121      0 Aug 26 17:30 focus_perception
-rw-r--r-- 1 user 197121   1710 Aug 26 14:10 re.md
-rw-r--r-- 1 user 197121  21717 Aug 26 14:08 产品方案与分工_v2.md
-rw-r--r-- 1 user 197121  10253 Aug 26 14:08 周礼航开发规范 (1).md
-rw-r--r-- 1 user 197121   9799 Aug 26 14:08 周礼航开发规范.md
=== 递归结构 ===
/c/temp
/c/temp/focus_perception
/c/temp/focus_perception/api
/c/temp/focus_perception/perception
/c/temp/focus_perception/tests

---

### [2026-08-28 15:14:45] AI

[思考] There's a project under `C:\temp\focus_perception`. Let me explore it more thoroughly.

---

### [2026-08-28 15:14:46] AI

[工具调用] Bash: {"command": "find /c/temp/focus_perception -type f 2>&1 | head -200", "description": "List all files in focus_perception project"}

---

### [2026-08-28 15:14:49] 用户

[工具结果] /c/temp/focus_perception/api/perception.h
/c/temp/focus_perception/BUILD_INTEGRATION.md
/c/temp/focus_perception/perception/perception.c
/c/temp/focus_perception/perception/perception_internal.h
/c/temp/focus_perception/PR_STEPS.md
/c/temp/focus_perception/README.md
/c/temp/focus_perception/tests/test_mimo_cloud.c
/c/temp/focus_perception/tests/test_perception.c
/c/temp/focus_perception/tests/wifi_http_post_stub.c

---

### [2026-08-28 15:14:51] AI

[工具调用] Read: {"file_path": "C:\\temp\\focus_perception\\README.md"}

---

### [2026-08-28 15:14:52] AI

[工具调用] Read: {"file_path": "C:\\temp\\focus_perception\\BUILD_INTEGRATION.md"}

---

### [2026-08-28 15:14:52] AI

[工具调用] Read: {"file_path": "C:\\temp\\focus_perception\\perception\\perception.c"}

---

### [2026-08-28 15:14:52] AI

[工具调用] Read: {"file_path": "C:\\temp\\focus_perception\\api\\perception.h"}

---

### [2026-08-28 15:14:53] AI

[工具调用] Read: {"file_path": "C:\\temp\\focus_perception\\perception\\perception_internal.h"}

---

### [2026-08-28 15:14:58] 用户

[工具结果] 1	/****************************************************************************
2	 * FOCUS AIoT - 视觉感知模块内部声明 (perception/perception_internal.h)
3	 *
4	 * 负责人: 周礼航
5	 * 说明:   对应任务书里的「perception/perception.h (内部声明, 可选)」。
6	 *         为避免与公开接口 api/perception.h 混淆, 命名为 *_internal.h。
7	 *         这里暴露的 cloud_result_t 与工具函数仅供 perception.c 实现与
8	 *         单测 (tests/test_perception.c) 使用，不对其他模块开放。
9	 ****************************************************************************/
10	
11	#ifndef PERCEPTION_INTERNAL_H
12	#define PERCEPTION_INTERNAL_H
13	
14	#include "../api/perception.h"
15	
16	/* 云端原始检测结果 (内部使用, 不对外暴露) */
17	typedef struct {
18	    bool  person_detected;
19	    float person_bbox[4];
20	    bool  phone_detected;
21	    bool  phone_in_hand;
22	    float head_pitch, head_yaw;
23	    float hand_motion;
24	    float confidence;
25	} cloud_result_t;
26	
27	/* ---- 内部工具函数 (实现 + 单测共用) ---- */
28	
29	uint32_t perception_monotonic_ms(void);
30	
31	size_t perception_base64_encoded_len(size_t n);
32	size_t perception_base64_encode(const uint8_t *src, size_t len,
33	                                char *dst, size_t dst_cap);
34	
35	bool  perception_majority3(bool a, bool b, bool c);
36	float perception_median3(float a, float b, float c);
37	float perception_max3(float a, float b, float c);
38	
39	void  perception_fill_observation(const cloud_result_t *raw,
40	                                  observation_t *out, uint32_t ts);
41	void  perception_debounce_push(const cloud_result_t *raw);
42	void  perception_debounce_compute(observation_t *out, uint32_t ts);
43	
44	/* 仅在非 mock (真实云端) 构建中定义, 依赖 cJSON */
45	#ifndef PERCEPTION_MOCK
46	int   perception_parse_cloud_response(const char *resp, cloud_result_t *out);
47	#endif
48	
49	#endif /* PERCEPTION_INTERNAL_H */
50	

---

### [2026-08-28 15:14:58] 用户

[工具结果] 1	/****************************************************************************
2	 * FOCUS AIoT - 视觉感知模块 (perception/perception.c)
3	 *
4	 * 负责人: 周礼航
5	 * 职责:   从一张 JPEG 里看出「有什么」——只做空间维度的单帧静态分析，
6	 *         不做时间维度的行为推理 (那是赵思涵 behavior 模块的事)。
7	 *
8	 * 输入:   JPEG 图像 (来自张沐泽 camera_frame_buffer / camera_capture_frame)
9	 * 输出:   observation_t (每帧一个, 经 MiMo 识图接口 + 3 帧去抖)
10	 *
11	 * MiMo 调用时机: 每帧都调 (perception_process 每次收到一帧 JPEG 都调一次
12	 *                mimo_detect(), 失败重试 1 次, 总阻塞 ≤6s)
13	 *
14	 * MiMo 契约 (已冻结):
15	 *   Request:  {"image":"<base64>","width":320,"height":240}
16	 *   Response: {"code":0,"data":{person/phone/head_pose/hand_motion_score/confidence}}
17	 *
18	 * 三个对外接口 (冻结于 api/perception.h):
19	 *   perception_init()         初始化 MiMo endpoint/key + 清空历史
20	 *   perception_process()      一帧 JPEG → (调 MiMo) → observation_t
21	 *   perception_get_history()  取最近 N 条 observation (供 behavior 时序分析)
22	 *
23	 * 编译开关:
24	 *   -D PERCEPTION_MOCK  走 mock 路径 (不调 MiMo), 默认 mock 便于联调/回退
25	 *                       不定义则走真实 MiMo 链路 (需要 cJSON + wifi_http_post)
26	 ****************************************************************************/
27	
28	#include <stdbool.h>
29	#include <stdint.h>
30	#include <stddef.h>
31	#include <string.h>
32	#include <stdio.h>
33	#include <stdlib.h>
34	#include <time.h>
35	
36	#include "../api/perception.h"
37	#include "perception_internal.h"
38	
39	#ifndef PERCEPTION_MOCK
40	#include <cJSON.h>
41	/* 张沐泽提供, 见 api/wifi.h (前向声明, 避免独立编译依赖) */
42	int wifi_http_post(const char *url, const char *body, char *resp, size_t maxlen);
43	#endif
44	
45	/* ------------------------------------------------------------------ */
46	/* 内部配置                                                            */
47	/* ------------------------------------------------------------------ */
48	#define HISTORY_MAX     60              /* 保留最近 60 条 observation */
49	#define FRAME_WIDTH     320
50	#define FRAME_HEIGHT    240
51	#define MAX_JPEG_SIZE   (50 * 1024)     /* 320x240 JPEG 上限 */
52	#define RESP_BUF_SIZE   4096            /* MiMo 响应缓冲 */
53	
54	/* MiMo 识图 endpoint 与鉴权 key。
55	 * 优先级: perception_init() 传入 > 下面的默认值。
56	 * TODO: 把 endpoint 填成 MiMo 真实地址; key 按鉴权方式填 (契约未体现
57	 *       auth 字段, 若需 Authorization header 请与张沐泽确认 wifi_http_post
58	 *       是否支持自定义 header, g_api_key 暂作预留)。 */
59	#define MIMO_ENDPOINT_DEFAULT   ""
60	#define MIMO_API_KEY_DEFAULT    ""
61	
62	/* ------------------------------------------------------------------ */
63	/* 模块状态 (单例; 该模块由 wifi_task 串行调用, 无重入)                */
64	/* ------------------------------------------------------------------ */
65	static char g_api_url[160];
66	static char g_api_key[80];
67	
68	static observation_t g_history[HISTORY_MAX];
69	static int           g_history_count = 0;   /* 累计写入条数 (用于求 start) */
70	
71	static cloud_result_t g_debounce[3];
72	static int            g_debounce_count = 0; /* 已累积帧数 0..3 */
73	static int            g_debounce_idx   = 0;
74	
75	static int            g_mock_seq = 0;       /* mock 轮转序号 */
76	
77	#ifndef PERCEPTION_MOCK
78	static char           g_resp[RESP_BUF_SIZE]; /* MiMo 响应缓冲 (仅真实链路) */
79	#endif
80	
81	/* ------------------------------------------------------------------ */
82	/* 基础工具                                                            */
83	/* ------------------------------------------------------------------ */
84	
85	uint32_t perception_monotonic_ms(void)
86	{
87	    struct timespec ts;
88	    clock_gettime(CLOCK_MONOTONIC, &ts);
89	    return (uint32_t)((uint64_t)ts.tv_sec * 1000u +
90	                      (uint64_t)ts.tv_nsec / 1000000u);
91	}
92	
93	bool perception_majority3(bool a, bool b, bool c)
94	{
95	    return ((int)a + (int)b + (int)c) >= 2;
96	}
97	
98	float perception_median3(float a, float b, float c)
99	{
100	    if (a > b) { float t = a; a = b; b = t; }
101	    if (b > c) { float t = b; b = c; c = t; }
102	    if (a > b) { float t = a; a = b; b = t; }
103	    return b;
104	}
105	
106	float perception_max3(float a, float b, float c)
107	{
108	    float m = a;
109	    if (b > m) m = b;
110	    if (c > m) m = c;
111	    return m;
112	}
113	
114	/* ------------------------------------------------------------------ */
115	/* Base64 编码 (RFC 4648)                                              */
116	/* ------------------------------------------------------------------ */
117	
118	size_t perception_base64_encoded_len(size_t n)
119	{
120	    return 4 * ((n + 2) / 3);
121	}
122	
123	size_t perception_base64_encode(const uint8_t *src, size_t len,
124	                                char *dst, size_t dst_cap)
125	{
126	    static const char tbl[] =
127	        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
128	
129	    size_t out_len = perception_base64_encoded_len(len);
130	    if (!src || !dst || dst_cap < out_len + 1) {
131	        return 0;
132	    }
133	
134	    size_t i, j = 0;
135	    for (i = 0; i + 3 <= len; i += 3) {
136	        uint32_t v = ((uint32_t)src[i]     << 16) |
137	                     ((uint32_t)src[i + 1] << 8)  |
138	                      (uint32_t)src[i + 2];
139	        dst[j++] = tbl[(v >> 18) & 63];
140	        dst[j++] = tbl[(v >> 12) & 63];
141	        dst[j++] = tbl[(v >> 6)  & 63];
142	        dst[j++] = tbl[ v        & 63];
143	    }
144	
145	    size_t rem = len - i;
146	    if (rem == 1) {
147	        uint32_t v = (uint32_t)src[i] << 16;
148	        dst[j++] = tbl[(v >> 18) & 63];
149	        dst[j++] = tbl[(v >> 12) & 63];
150	        dst[j++] = '=';
151	        dst[j++] = '=';
152	    } else if (rem == 2) {
153	        uint32_t v = ((uint32_t)src[i] << 16) | ((uint32_t)src[i + 1] << 8);
154	        dst[j++] = tbl[(v >> 18) & 63];
155	        dst[j++] = tbl[(v >> 12) & 63];
156	        dst[j++] = tbl[(v >> 6)  & 63];
157	        dst[j++] = '=';
158	    }
159	
160	    dst[j] = '\0';
161	    return j;
162	}
163	
164	/* ------------------------------------------------------------------ */
165	/* 去抖稳定 (3 帧滑动窗口)                                              */
166	/*   bool 字段: 多数投票                                                */
167	/*   float 角度: 中位数                                                 */
168	/*   hand_motion: 取最大 (宁可多报不遗漏)                                */
169	/*   confidence: 取均值                                                 */
170	/* ------------------------------------------------------------------ */
171	
172	void perception_fill_observation(const cloud_result_t *raw,
173	                                 observation_t *out, uint32_t ts)
174	{
175	    out->person_present    = raw->person_detected;
176	    out->person_bbox[0]    = raw->person_bbox[0];
177	    out->person_bbox[1]    = raw->person_bbox[1];
178	    out->person_bbox[2]    = raw->person_bbox[2];
179	    out->person_bbox[3]    = raw->person_bbox[3];
180	    out->phone_detected    = raw->phone_detected;
181	    out->phone_near_hand   = raw->phone_in_hand;
182	    out->head_pitch        = raw->head_pitch;
183	    out->head_yaw          = raw->head_yaw;
184	    out->hand_motion_score = raw->hand_motion;
185	    out->confidence        = raw->confidence;
186	    out->timestamp_ms      = ts;
187	}
188	
189	void perception_debounce_push(const cloud_result_t *raw)
190	{
191	    g_debounce[g_debounce_idx] = *raw;
192	    g_debounce_idx = (g_debounce_idx + 1) % 3;
193	    if (g_debounce_count < 3) {
194	        g_debounce_count++;
195	    }
196	}
197	
198	void perception_debounce_compute(observation_t *out, uint32_t ts)
199	{
200	    /* 最新一帧所在槽位 */
201	    const cloud_result_t *latest =
202	        &g_debounce[(g_debounce_idx + 3 - 1) % 3];
203	
204	    if (g_debounce_count < 3) {
205	        /* 历史不足 3 帧, 直接输出最新一帧 */
206	        perception_fill_observation(latest, out, ts);
207	        return;
208	    }
209	
210	    const cloud_result_t *h = g_debounce;
211	    out->person_present  = perception_majority3(h[0].person_detected,
212	                                                h[1].person_detected,
213	                                                h[2].person_detected);
214	    out->phone_detected  = perception_majority3(h[0].phone_detected,
215	                                                h[1].phone_detected,
216	                                                h[2].phone_detected);
217	    out->phone_near_hand = perception_majority3(h[0].phone_in_hand,
218	                                                h[1].phone_in_hand,
219	                                                h[2].phone_in_hand);
220	
221	    out->head_pitch = perception_median3(h[0].head_pitch,
222	                                         h[1].head_pitch,
223	                                         h[2].head_pitch);
224	    out->head_yaw   = perception_median3(h[0].head_yaw,
225	                                         h[1].head_yaw,
226	                                         h[2].head_yaw);
227	
228	    out->hand_motion_score = perception_max3(h[0].hand_motion,
229	                                             h[1].hand_motion,
230	                                             h[2].hand_motion);
231	
232	    out->confidence = (h[0].confidence + h[1].confidence + h[2].confidence) / 3.0f;
233	
234	    /* bbox 取最新一帧 (无去抖意义) */
235	    out->person_bbox[0] = latest->person_bbox[0];
236	    out->person_bbox[1] = latest->person_bbox[1];
237	    out->person_bbox[2] = latest->person_bbox[2];
238	    out->person_bbox[3] = latest->person_bbox[3];
239	
240	    out->timestamp_ms = ts;
241	}
242	
243	/* ------------------------------------------------------------------ */
244	/* MiMo 识图 (每帧都调, 仅真实链路)                                     */
245	/* ------------------------------------------------------------------ */
246	
247	#ifndef PERCEPTION_MOCK
248	
249	static int mimo_detect(uint8_t *jpeg, size_t jpeg_len, cloud_result_t *raw)
250	{
251	    /* 1. Base64 编码 (b64 ≈ 4/3 原图大小, 用堆/PSRAM 避免挤爆小栈) */
252	    size_t b64_cap = perception_base64_encoded_len(jpeg_len) + 1;
253	    char *b64 = malloc(b64_cap);
254	    if (!b64) {
255	        return FOCUS_ERR_PERCEP_PARAM;
256	    }
257	    size_t b64_len = perception_base64_encode(jpeg, jpeg_len, b64, b64_cap);
258	    if (b64_len == 0) {
259	        free(b64);
260	        return FOCUS_ERR_PERCEP_PARAM;
261	    }
262	
263	    /* 2. 构造请求体 (契约: {"image":"<base64>","width":320,"height":240}) */
264	    size_t req_cap = b64_len + 96;
265	    char *req = malloc(req_cap);
266	    if (!req) {
267	        free(b64);
268	        return FOCUS_ERR_PERCEP_PARAM;
269	    }
270	    snprintf(req, req_cap, "{\"image\":\"%s\",\"width\":%d,\"height\":%d}",
271	             b64, FRAME_WIDTH, FRAME_HEIGHT);
272	
273	    /* 3. HTTP POST: 单次超时由 wifi_http_post 保证 ≤3s;
274	     *    失败重试 1 次, 总阻塞 ≤6s (满足开发规范约束) */
275	    int ret = wifi_http_post(g_api_url, req, g_resp, sizeof(g_resp));
276	    if (ret < 0) {
277	        ret = wifi_http_post(g_api_url, req, g_resp, sizeof(g_resp));
278	    }
279	    free(b64);
280	    free(req);
281	    if (ret < 0) {
282	        return FOCUS_ERR_PERCEP_TIMEOUT;
283	    }
284	
285	    /* 4. 解析响应 → 云端原始结果 */
286	    return perception_parse_cloud_response(g_resp, raw);
287	}
288	
289	/* MiMo 响应解析 (契约: code==0 且 data 为对象; 所有字段判空不崩) */
290	int perception_parse_cloud_response(const char *resp, cloud_result_t *out)
291	{
292	    if (!resp || !out) {
293	        return FOCUS_ERR_PERCEP_JSON;
294	    }
295	
296	    cJSON *root = cJSON_Parse(resp);
297	    if (!root) {
298	        return FOCUS_ERR_PERCEP_JSON;
299	    }
300	
301	    cJSON *code = cJSON_GetObjectItem(root, "code");
302	    if (cJSON_IsNumber(code) && code->valueint != 0) {
303	        cJSON_Delete(root);
304	        return FOCUS_ERR_PERCEP_NODATA;   /* 业务码非 0: 无人/无数据 */
305	    }
306	
307	    cJSON *data = cJSON_GetObjectItem(root, "data");
308	    if (!cJSON_IsObject(data)) {
309	        cJSON_Delete(root);
310	        return FOCUS_ERR_PERCEP_NODATA;
311	    }
312	
313	    /* person */
314	    cJSON *person = cJSON_GetObjectItem(data, "person");
315	    if (cJSON_IsObject(person)) {
316	        out->person_detected = cJSON_IsTrue(cJSON_GetObjectItem(person, "detected"));
317	
318	        cJSON *bbox = cJSON_GetObjectItem(person, "bbox");
319	        if (cJSON_IsArray(bbox) && cJSON_GetArraySize(bbox) >= 4) {
320	            for (int i = 0; i < 4; i++) {
321	                cJSON *v = cJSON_GetArrayItem(bbox, i);
322	                out->person_bbox[i] = cJSON_IsNumber(v) ? (float)v->valuedouble : 0.0f;
323	            }
324	        }
325	    }
326	
327	    /* phone */
328	    cJSON *phone = cJSON_GetObjectItem(data, "phone");
329	    if (cJSON_IsObject(phone)) {
330	        out->phone_detected = cJSON_IsTrue(cJSON_GetObjectItem(phone, "detected"));
331	        out->phone_in_hand  = cJSON_IsTrue(cJSON_GetObjectItem(phone, "near_hand"));
332	    }
333	
334	    /* head_pose */
335	    cJSON *pose = cJSON_GetObjectItem(data, "head_pose");
336	    if (cJSON_IsObject(pose)) {
337	        cJSON *pitch = cJSON_GetObjectItem(pose, "pitch");
338	        if (cJSON_IsNumber(pitch)) out->head_pitch = (float)pitch->valuedouble;
339	        cJSON *yaw = cJSON_GetObjectItem(pose, "yaw");
340	        if (cJSON_IsNumber(yaw)) out->head_yaw = (float)yaw->valuedouble;
341	    }
342	
343	    cJSON *motion = cJSON_GetObjectItem(data, "hand_motion_score");
344	    if (cJSON_IsNumber(motion)) out->hand_motion = (float)motion->valuedouble;
345	
346	    cJSON *conf = cJSON_GetObjectItem(data, "confidence");
347	    if (cJSON_IsNumber(conf)) out->confidence = (float)conf->valuedouble;
348	
349	    cJSON_Delete(root);
350	    return FOCUS_OK;
351	}
352	
353	#endif /* !PERCEPTION_MOCK */
354	
355	/* ------------------------------------------------------------------ */
356	/* Mock 路径 (阶段 1, 联调用)                                          */
357	/*   按预设序列轮流产出 FOCUSED/PLAYING_PHONE/AWAY/DROWSY 对应的        */
358	/*   observation_t, 不调 MiMo, 不走去抖 (mock 本身已是稳定结果)         */
359	/* ------------------------------------------------------------------ */
360	
361	#ifdef PERCEPTION_MOCK
362	
363	static observation_t mock_observation(int step)
364	{
365	    observation_t o;
366	    memset(&o, 0, sizeof(o));
367	    o.confidence   = 0.9f;
368	    o.timestamp_ms = perception_monotonic_ms();
369	
370	    switch (step % 4) {
371	    case 0: /* FOCUSED */
372	        o.person_present = true;
373	        o.person_bbox[0] = 0.15f; o.person_bbox[1] = 0.10f;
374	        o.person_bbox[2] = 0.70f; o.person_bbox[3] = 0.85f;
375	        o.head_pitch = 0.0f;
376	        o.hand_motion_score = 0.10f;
377	        break;
378	    case 1: /* PLAYING_PHONE */
379	        o.person_present = true;
380	        o.person_bbox[0] = 0.15f; o.person_bbox[1] = 0.10f;
381	        o.person_bbox[2] = 0.70f; o.person_bbox[3] = 0.85f;
382	        o.phone_detected  = true;
383	        o.phone_near_hand = true;
384	        o.head_pitch = -25.0f;
385	        o.hand_motion_score = 0.60f;
386	        break;
387	    case 2: /* AWAY */
388	        o.person_present = false;
389	        break;
390	    case 3: /* DROWSY */
391	        o.person_present = true;
392	        o.person_bbox[0] = 0.15f; o.person_bbox[1] = 0.10f;
393	        o.person_bbox[2] = 0.70f; o.person_bbox[3] = 0.85f;
394	        o.head_pitch = 55.0f;
395	        o.hand_motion_score = 0.05f;
396	        break;
397	    }
398	    return o;
399	}
400	
401	#endif /* PERCEPTION_MOCK */
402	
403	/* ------------------------------------------------------------------ */
404	/* 历史管理 (环形缓冲区, 供赵思涵时序分析)                              */
405	/* ------------------------------------------------------------------ */
406	
407	static void history_append(const observation_t *obs)
408	{
409	    g_history[g_history_count % HISTORY_MAX] = *obs;
410	    g_history_count++;
411	}
412	
413	/* ------------------------------------------------------------------ */
414	/* 对外接口                                                            */
415	/* ------------------------------------------------------------------ */
416	
417	int perception_init(const char *api_url, const char *api_key)
418	{
419	    if (api_url) {
420	        snprintf(g_api_url, sizeof(g_api_url), "%s", api_url);
421	    } else {
422	        snprintf(g_api_url, sizeof(g_api_url), "%s", MIMO_ENDPOINT_DEFAULT);
423	    }
424	    if (api_key) {
425	        snprintf(g_api_key, sizeof(g_api_key), "%s", api_key);
426	    } else {
427	        snprintf(g_api_key, sizeof(g_api_key), "%s", MIMO_API_KEY_DEFAULT);
428	    }
429	
430	    memset(g_history, 0, sizeof(g_history));
431	    g_history_count = 0;
432	
433	    memset(g_debounce, 0, sizeof(g_debounce));
434	    g_debounce_count = 0;
435	    g_debounce_idx   = 0;
436	
437	    g_mock_seq = 0;
438	    return FOCUS_OK;
439	}
440	
441	int perception_process(uint8_t *jpeg, size_t jpeg_len, observation_t *out)
442	{
443	    if (!out || !jpeg || jpeg_len == 0) {
444	        return FOCUS_ERR_PERCEP_PARAM;
445	    }
446	
447	#ifdef PERCEPTION_MOCK
448	    /* 阶段 1: mock —— 不调 MiMo, 按预设序列轮流产出 observation */
449	    *out = mock_observation(g_mock_seq++);
450	#else
451	    /* 阶段 2: 真实链路 —— 每帧都调 MiMo 识图, 再去抖稳定 */
452	    cloud_result_t raw;
453	    memset(&raw, 0, sizeof(raw));
454	    int ret = mimo_detect(jpeg, jpeg_len, &raw);
455	    if (ret != FOCUS_OK) {
456	        return ret;
457	    }
458	
459	    perception_debounce_push(&raw);
460	    perception_debounce_compute(out, perception_monotonic_ms());
461	#endif
462	
463	    /* 追加历史 (供赵思涵时序分析) */
464	    history_append(out);
465	    return FOCUS_OK;
466	}
467	
468	int perception_get_history(observation_t *buf, int n)
469	{
470	    if (!buf || n <= 0) {
471	        return 0;
472	    }
473	    if (n > HISTORY_MAX) {
474	        n = HISTORY_MAX;
475	    }
476	
477	    int available = (g_history_count < HISTORY_MAX)
478	                        ? g_history_count : HISTORY_MAX;
479	    if (n > available) {
480	        n = available;
481	    }
482	
483	    /* 从旧到新拷贝 */
484	    int start = (g_history_count > HISTORY_MAX)
485	                    ? (g_history_count % HISTORY_MAX) : 0;
486	    for (int i = 0; i < n; i++) {
487	        buf[i] = g_history[(start + i) % HISTORY_MAX];
488	    }
489	    return n;
490	}
491	

---

### [2026-08-28 15:14:59] 用户

[工具结果] 1	/****************************************************************************
2	 * FOCUS AIoT - 视觉感知模块公开接口 (api/perception.h)
3	 *
4	 * 负责人: 周礼航
5	 * 职责:   从一张 JPEG 里看出「有什么」——只做空间维度的单帧静态分析。
6	 *
7	 * ⚠️ 注意: 此文件是【参考拷贝】，用于独立编译/单测。
8	 *    仓库里真正冻结的那份 api/perception.h 由万思源维护，请以仓库版本为准。
9	 *    observation_t 字段、三个函数签名、错误码值必须与仓库冻结版一致。
10	 ****************************************************************************/
11	
12	#ifndef API_PERCEPTION_H
13	#define API_PERCEPTION_H
14	
15	#include <stdbool.h>
16	#include <stdint.h>
17	#include <stddef.h>
18	
19	/*
20	 * 统一错误码 —— 通常由 api/error.h 提供并被 api/perception.h 间接包含。
21	 * 下面用 #ifndef 兜底，保证脱离 error.h 也能独立编译。
22	 */
23	#ifndef FOCUS_OK
24	#define FOCUS_OK                    0
25	#endif
26	#ifndef FOCUS_ERR_PERCEP_TIMEOUT
27	#define FOCUS_ERR_PERCEP_TIMEOUT   (-30)   /* 云端/HTTP 超时或请求失败 */
28	#endif
29	#ifndef FOCUS_ERR_PERCEP_JSON
30	#define FOCUS_ERR_PERCEP_JSON      (-31)   /* JSON 解析失败 / 缺字段 */
31	#endif
32	#ifndef FOCUS_ERR_PERCEP_NODATA
33	#define FOCUS_ERR_PERCEP_NODATA    (-32)   /* 业务码非 0 / 无数据 */
34	#endif
35	#ifndef FOCUS_ERR_PERCEP_PARAM
36	#define FOCUS_ERR_PERCEP_PARAM     (-33)   /* 参数非法 (perception 本地扩展) */
37	#endif
38	
39	/*
40	 * 每帧图像经过云端检测 + 去抖后输出一个 Observation。
41	 * 对严格/鼓励两种模式完全相同 (模式差异是赵思涵 behavior 模块的事)。
42	 */
43	typedef struct {
44	    bool     person_present;       /* 画面中是否有人 */
45	    float    person_bbox[4];       /* 人体边界框 (x,y,w,h) 归一化 [0-1] */
46	    bool     phone_detected;       /* 是否检测到手机 */
47	    bool     phone_near_hand;      /* 手机是否在手部区域 */
48	    float    head_pitch;           /* 头部俯仰角 (度, 负=低头 正=仰头) */
49	    float    head_yaw;             /* 头部偏航角 (度) */
50	    float    hand_motion_score;    /* 手部运动量 [0-1] */
51	    float    confidence;           /* 整体置信度 [0-1] */
52	    uint32_t timestamp_ms;         /* 时间戳 (毫秒) */
53	} observation_t;
54	
55	/* 初始化: 配置 API URL 和 Key, 清空历史与去抖状态。返回 FOCUS_OK=成功 */
56	int  perception_init(const char *api_url, const char *api_key);
57	
58	/* 核心: 一张 JPEG → 云端 API → 去抖 → 输出 observation_t */
59	int  perception_process(uint8_t *jpeg, size_t jpeg_len, observation_t *out);
60	
61	/* 取最近 N 条 observation (从旧到新), 供 behavior 时序分析。返回实际条数 */
62	int  perception_get_history(observation_t *buf, int n);
63	
64	#endif /* API_PERCEPTION_H */
65	

---

### [2026-08-28 15:15:01] 用户

[工具结果] 1	# 构建接入 (Makefile / CMakeLists / Kconfig)
2	
3	把 `perception/` 接进仓库，需要 3 步。仓库里 `LCD_STUB` 已有现成的
4	「Kconfig 二选一编译」模式，直接照抄它的 if/else 即可。
5	
6	## 1. 源文件入编
7	
8	**Makefile**（`app/hello_app/Makefile`）的 `CSRCS`：
9	
10	```make
11	CSRCS += perception/perception.c
12	```
13	
14	**CMakeLists.txt**（`app/hello_app/CMakeLists.txt`）：
15	
16	```cmake
17	set(CSRCS ${CSRCS} perception/perception.c)
18	```
19	
20	## 2. mock / 真实 二选一（参考 LCD_STUB）
21	
22	**Makefile**：
23	
24	```make
25	ifeq ($(CONFIG_CONTEST2026_087_PERCEPTION_MOCK),y)
26	CFLAGS += -DPERCEPTION_MOCK
27	else
28	# 真实 MiMo 链路: 依赖 cJSON (openvela 自带, 头文件 <cJSON.h>)
29	# 若需显式链接: LDLIBS += -lcjson
30	endif
31	```
32	
33	**Kconfig**（`app/hello_app/Kconfig`）：
34	
35	```
36	config CONTEST2026_087_PERCEPTION_MOCK
37	    bool "Perception mock (no MiMo call)"
38	    default y
39	    help
40	        默认走 mock，便于不依赖网络的联调；关掉后走真实 MiMo 识图链路。
41	```
42	
43	> 默认 `y`（mock），符合任务书「默认 mock 可回退」。联调/上线前关掉。
44	
45	## 3. 依赖说明
46	
47	| 依赖 | 来源 | 说明 |
48	|---|---|---|
49	| `wifi_http_post()` | 张沐泽 `api/wifi.h` | 真实网络 |
50	| `cJSON` | openvela 自带 | 真实链路解析响应用 |
51	| `perception_get_history()` | 本模块 | 强符号，自动覆盖 `core/mock.c` 的 weak 桩 |
52	
53	## 4. host 联调（不需要硬件/网络）
54	
55	```bash
56	# mock 单测 (无 cJSON 依赖)
57	gcc -Wall -Wextra -Werror -DPERCEPTION_MOCK \
58	    perception/perception.c tests/test_perception.c -o test_perception
59	./test_perception
60	
61	# 真实 MiMo 链路单测 (需要 cJSON.c/cJSON.h)
62	gcc -Wall -Wextra -Werror \
63	    perception/perception.c tests/wifi_http_post_stub.c tests/test_mimo_cloud.c \
64	    cJSON.c -I/path/to/cjson -o test_mimo_cloud
65	./test_mimo_cloud
66	```
67	

---

### [2026-08-28 15:15:01] 用户

[工具结果] 1	# 视觉感知模块 (perception) —— 周礼航 · 成品
2	
3	这是「FOCUS AIoT」里 **视觉感知层** 的完整实现。输入一张 JPEG，**每帧调用
4	MiMo 识图接口**，输出一个 `observation_t`，供赵思涵的 `behavior` 模块做时序分析。
5	
6	> 依据文档：`周礼航开发规范.md`、`DEVELOPMENT_TASKS (2).md`（2026-08-19）、
7	> `产品方案与分工_v2.md`。只做「空间」上的单帧识别，**不区分严格/鼓励模式**，
8	> **不做行为判断**（那是赵思涵的事）。
9	
10	## 文件清单
11	
12	```
13	focus_perception/
14	├── api/perception.h             公开接口 (observation_t + 3 函数 + 错误码)
15	│                                ⚠️ 参考拷贝, 勿覆盖仓库冻结版
16	├── perception/
17	│   ├── perception.c             主实现 (MiMo 调用 + 去抖 + 历史 + base64 + cJSON)
18	│   └── perception_internal.h    内部声明 (cloud_result_t + 工具函数)
19	├── tests/
20	│   ├── test_perception.c        mock 单测 (不依赖硬件/网络/cJSON)
21	│   ├── wifi_http_post_stub.c    联调 stub (替换真实 wifi_http_post)
22	│   └── test_mimo_cloud.c        真实 MiMo 链路单测 (需要 cJSON)
23	├── BUILD_INTEGRATION.md         Makefile/CMakeLists/Kconfig 接入 diff
24	└── README.md
25	```
26	
27	## MiMo 识图（每帧都调）
28	
29	`perception_process()` 每次收到一帧 JPEG 都调一次 `mimo_detect()`（失败重试 1 次，
30	总阻塞 ≤6s），契约已冻结：
31	
32	```
33	Request:  {"image":"<base64>","width":320,"height":240}
34	Response: {"code":0,"data":{
35	             "person":{"detected":true,"bbox":[0.15,0.10,0.70,0.85]},
36	             "phone":{"detected":true,"near_hand":true},
37	             "head_pose":{"pitch":-25.3,"yaw":2.1},
38	             "hand_motion_score":0.35,"confidence":0.92}}
39	```
40	
41	endpoint / key 通过 `perception_init(url, key)` 传入（优先级高于
42	`MIMO_ENDPOINT_DEFAULT` / `MIMO_API_KEY_DEFAULT` 两个占位宏）。
43	
44	> ⚠️ **待确认**：契约里没有鉴权字段，而 `wifi_http_post(url, body, resp, maxlen)`
45	> 也带不了 header。MiMo 的 token 到底怎么传（header？URL query？body？），
46	> 需要跟张沐泽/陈泽沛确认，`g_api_key` 已预留。
47	
48	## 三个对外接口（冻结签名）
49	
50	```c
51	int  perception_init(const char *api_url, const char *api_key);
52	int  perception_process(uint8_t *jpeg, size_t jpeg_len, observation_t *out);
53	int  perception_get_history(observation_t *buf, int n);
54	```
55	
56	返回值（错误码，来自 `api/error.h`，此处兜底定义）：
57	
58	| 常量 | 值 | 含义 |
59	|---|---|---|
60	| `FOCUS_OK` | 0 | 成功 |
61	| `FOCUS_ERR_PERCEP_TIMEOUT` | -30 | MiMo 超时/请求失败 |
62	| `FOCUS_ERR_PERCEP_JSON` | -31 | JSON 解析失败 / 缺字段 |
63	| `FOCUS_ERR_PERCEP_NODATA` | -32 | 业务码非 0 / 无数据 |
64	| `FOCUS_ERR_PERCEP_PARAM` | -33 | 参数非法（本地扩展，可请万思源并入 error.h） |
65	
66	## 关键设计
67	
68	- **每帧都调 MiMo**：`perception_process()` → `mimo_detect()`（base64 → JSON →
69	  `wifi_http_post` → cJSON 解析）→ 3 帧去抖 → 追加历史。
70	- **mock / 真实双路径**：`-DPERCEPTION_MOCK` 走 mock（默认，不调 MiMo）；
71	  不定义则走真实 MiMo 链路。
72	- **3 帧去抖**：bool 多数投票、角度中位数、hand_motion 取最大、confidence 取均值。
73	  mock 路径本身已是稳定结果，**绕过**去抖，避免把 AWAY 状态「投票投没」。
74	- **历史环形缓冲**：`obs_history[60]`，`perception_get_history()` 从旧到新返回。
75	  提供**强符号** `perception_get_history()`，自动覆盖 `core/mock.c` 里的 weak 桩。
76	- **超时**：HTTP 单次由张沐泽的 `wifi_http_post` 保证 ≤3s；失败重试 1 次，总阻塞 ≤6s。
77	- **内存**：base64 / 请求体用 `malloc`（ESP32 上建议映射 PSRAM），响应用固定 4KB 静态缓冲。
78	- **时间戳**：`clock_gettime(CLOCK_MONOTONIC)`（与 `core/state_machine.c` 的 monotonic_ms 一致）。
79	
80	## 本地单测
81	
82	```bash
83	cd focus_perception
84	
85	# 1) mock 单测 (无 cJSON 依赖)
86	gcc -Wall -Wextra -Werror -DPERCEPTION_MOCK \
87	    perception/perception.c tests/test_perception.c -o test_perception
88	./test_perception
89	
90	# 2) 真实 MiMo 链路单测 (需要 cJSON.c/cJSON.h)
91	gcc -Wall -Wextra -Werror \
92	    perception/perception.c tests/wifi_http_post_stub.c tests/test_mimo_cloud.c \
93	    cJSON.c -I/path/to/cjson -o test_mimo_cloud
94	./test_mimo_cloud
95	```
96	
97	预期都是 `0 failed`。mock 测试覆盖：base64（RFC4648 标准向量）、多数投票/中位数/最大值、
98	3 帧去抖、mock 轮转、历史环形缓冲、空历史/参数非法。MiMo 测试覆盖：每帧调用次数、
99	响应解析、失败重试、三种错误码。
100	
101	## 接入仓库（openvela 真机）
102	
103	1. 把 `perception/perception.c`、`perception/perception_internal.h` 放进
104	   `app/hello_app/perception/`。
105	2. `api/perception.h` **不要覆盖**，用仓库冻结版（字段/签名必须一致）。
106	3. 按 `BUILD_INTEGRATION.md` 加 `CSRCS` + Kconfig 开关。
107	4. 联调/上线前关掉 mock 开关，并填好 MiMo endpoint / token。
108	
109	## 联调顺序
110	
111	先跟张沐泽联调（确认 `wifi_http_post` 能通 + MiMo 鉴权方式）→ 再跟赵思涵联调
112	（确认 `observation_t` 字段对）→ 最后全链路：真实 observation → behavior →
113	state_machine → UI 上屏。
114	

---

### [2026-08-28 15:15:16] AI

[思考] Now I understand the project context. This is a "FOCUS AIoT" project. The `perception` module (周礼航) does single-frame static analysis (person/phone/head_pose/hand_motion) via a MiMo cloud API. There's a `behavior` module (赵思涵) that does temporal/sequence analysis. The device is ESP32 (openvela). So this is an embedded AIoT device.

Now the user's request: "识别动作 连续帧jpeg格式 小设备 最好是成品 可以接入C:\temp文件夹下的项目"

Translation: "Action recognition, continuous JPEG frames, small device, best if finished product, can integrate into the C:\temp project."

So the user is 赵思涵 (or wants to build the behavior module)? Or the user is working on the behavior module which does temporal analysis on the sequence of `observation_t` from perception.

Wait — the perception module already outputs `observation_t` per frame, and there's a `behavior` module (赵思涵) that does temporal analysis (action/behavior recognition) on these observations. The README says "输出一个 observation_t，供赵思涵的 behavior 模块做时序分析" and "不做行为判断（那是赵思涵的事）".

So the user now wants the action recognition part — the temporal behavior analysis. This is exactly the `behavior` module.

The user is non-technical. They want:
1. Action recognition (识别动作) — this maps to the behavior module
2. Continuous JPEG frames — input is the sequence of observations (or JPEG frames)
3. Small device (ESP32) — so it must be lightweight C code
4. Finished product (成品) — complete implementation
5. Integrate into C:\temp project — this is the focus_perception project, and they want to add the behavior module

So I need to build the `behavior` module (赵思涵's part) — a C module that takes the sequence of `observation_t` and classifies actions/behaviors.

The actions from the mock: FOCUSED, PLAYING_PHONE, AWAY, DROWSY. These are the 4 states/behaviors.

Let me look at the other docs to understand the behavior module requirements. Let me read the DEVELOPMENT_TASKS and 产品方案与分工 and 周礼航开发规范 files.

---

### [2026-08-28 15:15:16] AI

[工具调用] Read: {"file_path": "C:\\temp\\DEVELOPMENT_TASKS (2).md"}

---

### [2026-08-28 15:15:16] AI

[工具调用] Read: {"file_path": "C:\\temp\\产品方案与分工_v2.md"}

---

### [2026-08-28 15:15:16] AI

[工具调用] Read: {"file_path": "C:\\temp\\周礼航开发规范.md"}

---

### [2026-08-28 15:17:28] 用户

[工具结果] 1	# 周礼航 开发规范
2	
3	> 你的模块是**视觉感知层**——从一张图片里看出「有什么」。
4	> 只管空间维度的单帧分析，不管时间维度的行为推理（那是赵思涵的事）。
5	
6	---
7	
8	## 一、你能调用的接口（别人写好给你的）
9	
10	```c
11	// ── 张沐泽提供的 Wi-Fi HTTP 客户端 ──
12	// 发送 HTTP POST 请求，阻塞等待响应
13	// url:    请求地址
14	// body:   请求体 (JSON 字符串)
15	// resp:   响应体缓冲区 (调用方分配)
16	// maxlen: 响应体最大长度
17	// 返回: 0=成功, 负值=错误码
18	int  wifi_http_post(const char *url, const char *body, 
19	                    char *resp, size_t maxlen);
20	
21	// ── 张沐泽提供的图像缓冲区 ──
22	// camera_task 采集的最新一帧 JPEG，存放在 PSRAM 固定地址
23	// 大小: camera_frame_size (采集完成后由 camera_task 更新)
24	extern uint8_t *camera_frame_buffer;   // PSRAM 中 JPEG 数据
25	extern size_t   camera_frame_size;     // 当前帧字节数
26	```
27	
28	---
29	
30	## 二、你需要产出的数据结构
31	
32	```c
33	// ── 定义在 api/perception.h，你来实现 ──
34	
35	// 每帧图像经过云端检测 + 去抖后输出一个 Observation
36	typedef struct {
37	    bool     person_present;       // 画面中是否有人
38	    float    person_bbox[4];       // 人体边界框 (x,y,w,h) 归一化 [0-1]
39	    bool     phone_detected;       // 是否检测到手机
40	    bool     phone_near_hand;      // 手机是否在手部区域
41	    float    head_pitch;           // 头部俯仰角 (度, 负=低头 正=仰头)
42	    float    head_yaw;             // 头部偏航角 (度)
43	    float    hand_motion_score;    // 手部运动量 [0-1]
44	    float    confidence;           // 整体置信度 [0-1]
45	    uint32_t timestamp_ms;         // 时间戳 (毫秒)
46	} observation_t;
47	
48	// ── 你需要实现的 3 个函数 ──
49	
50	// 初始化: 配置 API URL 和 Key (从 NVS 读取或硬编码)
51	// 返回: 0=成功
52	int  perception_init(const char *api_url, const char *api_key);
53	
54	// 核心函数: 拿一张 JPEG → 调云端 API → 去抖 → 输出 Observation
55	// jpeg:    输入图像数据
56	// jpeg_len: 图像字节数
57	// out:     输出的 Observation (调用方分配)
58	// 返回: 0=成功, -1=云端超时, -2=JSON解析失败
59	int  perception_process(uint8_t *jpeg, size_t jpeg_len, observation_t *out);
60	
61	// 获取最近 N 个 Observation (供赵思涵做时序分析)
62	// buf:   输出缓冲区 (调用方分配, 至少 n * sizeof(observation_t))
63	// n:     最多返回多少条
64	// 返回: 实际返回的条数 (≤ n)
65	int  perception_get_history(observation_t *buf, int n);
66	```
67	
68	---
69	
70	## 三、你需要做的三件事
71	
72	### 3.1 云端 API 调用
73	
74	```
75	  输入: JPEG 图像 (320×240, 来自 camera_frame_buffer)
76	  过程: base64 编码 → 构造 JSON → HTTP POST → 解析 JSON 响应
77	  输出: 原始检测结果 (cloud_result_t, 内部使用)
78	```
79	
80	```c
81	// 内部数据结构 (不对外暴露)
82	typedef struct {
83	    bool  person_detected;
84	    float person_bbox[4];
85	    bool  phone_detected;
86	    bool  phone_in_hand;
87	    float head_pitch, head_yaw, head_roll;
88	    float hand_motion;
89	    float confidence;
90	} cloud_result_t;
91	```
92	
93	**API 协议**（调用百度 AI 或阿里云视觉 API）：
94	
95	```json
96	// Request
97	POST /api/v1/detect
98	{
99	  "image": "<base64>",
100	  "width": 320,
101	  "height": 240
102	}
103	
104	// Response
105	{
106	  "code": 0,
107	  "data": {
108	    "person": {
109	      "detected": true,
110	      "bbox": [0.15, 0.10, 0.70, 0.85]
111	    },
112	    "phone": {
113	      "detected": true,
114	      "near_hand": true
115	    },
116	    "head_pose": {
117	      "pitch": -25.3,
118	      "yaw": 2.1
119	    },
120	    "hand_motion_score": 0.35,
121	    "confidence": 0.92
122	  }
123	}
124	```
125	
126	**调用示例**：
127	
128	```c
129	int perception_process(uint8_t *jpeg, size_t jpeg_len, observation_t *out) {
130	    // 1. Base64 编码
131	    char b64[50*1024];  // 320×240 JPEG ≈ 30KB → base64 ≈ 40KB
132	    base64_encode(jpeg, jpeg_len, b64, sizeof(b64));
133	    
134	    // 2. 构造 JSON 请求
135	    char req[55*1024];
136	    snprintf(req, sizeof(req),
137	        "{\"image\":\"%s\",\"width\":320,\"height\":240}", b64);
138	    
139	    // 3. HTTP POST
140	    char resp[4096];
141	    int ret = wifi_http_post(api_url, req, resp, sizeof(resp));
142	    if (ret < 0) return -1;
143	    
144	    // 4. JSON 解析
145	    cloud_result_t raw;
146	    if (parse_cloud_response(resp, &raw) < 0) return -2;
147	    
148	    // 5. 去抖稳定 (见 3.2)
149	    return stabilize(&raw, out);
150	}
151	```
152	
153	### 3.2 去抖稳定
154	
155	连续帧之间，云端 API 的结果可能在两个状态间来回跳（比如第 1 帧检测到手机，第 2 帧没检测到，第 3 帧又检测到）。用一个 **3 帧滑动窗口** 平滑输出：
156	
157	```c
158	static cloud_result_t history[3];
159	static int history_idx = 0;
160	
161	int stabilize(cloud_result_t *raw, observation_t *out) {
162	    // 写入历史
163	    history[history_idx] = *raw;
164	    history_idx = (history_idx + 1) % 3;
165	    
166	    int n = (history[0].confidence > 0) + 
167	            (history[1].confidence > 0) + 
168	            (history[2].confidence > 0);
169	    if (n < 3) {
170	        // 历史不足 3 帧，直接输出当前帧
171	        fill_observation(raw, out);
172	        return 0;
173	    }
174	    
175	    // 布尔值: 3 帧多数投票
176	    out->person_present  = majority(history[0].person_detected,
177	                                    history[1].person_detected,
178	                                    history[2].person_detected);
179	    out->phone_detected  = majority(history[0].phone_detected,
180	                                    history[1].phone_detected,
181	                                    history[2].phone_detected);
182	    out->phone_near_hand = majority(history[0].phone_in_hand,
183	                                    history[1].phone_in_hand,
184	                                    history[2].phone_in_hand);
185	    
186	    // 浮点值: 取中位数 (抗单帧异常值)
187	    out->head_pitch  = median3(history[0].head_pitch,
188	                               history[1].head_pitch,
189	                               history[2].head_pitch);
190	    out->head_yaw    = median3(history[0].head_yaw,
191	                               history[1].head_yaw,
192	                               history[2].head_yaw);
193	    
194	    // 运动量: 取最大值 (宁可多报不遗漏)
195	    out->hand_motion_score = max3(history[0].hand_motion,
196	                                  history[1].hand_motion,
197	                                  history[2].hand_motion);
198	    
199	    // 置信度: 取均值
200	    out->confidence = (history[0].confidence + 
201	                       history[1].confidence + 
202	                       history[2].confidence) / 3.0f;
203	    
204	    out->timestamp_ms = raw->timestamp_ms;
205	    return 0;
206	}
207	```
208	
209	### 3.3 维护 Observation 历史
210	
211	赵思涵需要连续多帧的 Observation 做时序分析。你维护一个环形缓冲区：
212	
213	```c
214	#define HISTORY_MAX  60   // 保留最近 60 条 (60×5s = 300s 窗口)
215	
216	static observation_t obs_history[HISTORY_MAX];
217	static int obs_count = 0;
218	
219	// 每次 produce 一条 Observation 后调用
220	static void history_append(observation_t *obs) {
221	    obs_history[obs_count % HISTORY_MAX] = *obs;
222	    obs_count++;
223	}
224	
225	int perception_get_history(observation_t *buf, int n) {
226	    if (n > HISTORY_MAX) n = HISTORY_MAX;
227	    int available = (obs_count < HISTORY_MAX) ? obs_count : HISTORY_MAX;
228	    if (n > available) n = available;
229	    
230	    // 从旧到新拷贝
231	    int start = (obs_count > HISTORY_MAX) ? (obs_count % HISTORY_MAX) : 0;
232	    for (int i = 0; i < n; i++) {
233	        buf[i] = obs_history[(start + i) % HISTORY_MAX];
234	    }
235	    return n;
236	}
237	```
238	
239	---
240	
241	## 四、你的模块和其他人的关系
242	
243	```
244	  张沐泽              你                  赵思涵
245	  ────────          ──────              ────────
246	  camera_task ──▶ perception_process() ──▶ observation_t
247	  产 JPEG          调 API + 去抖           消费 Observation
248	                                        做时序分析
249	  
250	  万思源
251	  ──────
252	  你的 perception_init() 由万思源在主程序启动时调用一次
253	  你的 perception_process() 由万思源的 wifi_task 每收到新帧时调用
254	```
255	
256	**你不会被直接调用的场景**：
257	- 按键事件 → 不经过你，赵思涵不需要 Observation 来判断按键
258	- LCD 刷新 → 不经过你
259	- 语音播报 → 不经过你
260	- MiMo API → 不经过你
261	
262	---
263	
264	## 五、开发约束
265	
266	| 约束 | 说明 |
267	|---|---|
268	| **不区分模式** | 严格/鼓励模式是赵思涵的事，你的 Observation 对两种模式完全相同 |
269	| **不做行为判断** | 你只输出"检测到手机 = true/false"，**不判断**这是玩手机还是看手机——那是赵思涵的时序分析做的 |
270	| **超时处理** | HTTP 请求超时 3 秒，重试 1 次，仍失败→返回错误码 -1，**不要阻塞超过 6 秒** |
271	| **JSON 解析不崩** | 云端可能返回格式异常的数据，`parse_cloud_response()` 必须有边界检查 |
272	| **base64 内存** | base64 编码后的字符串比原图大约 33%，40KB → 约 54KB，栈上放不下就用 PSRAM |
273	| **不要缓存 JPEG** | 每次调完 API 就丢弃 JPEG 数据，不需要存历史图像 |
274	
275	---
276	
277	## 六、可以独立测试
278	
279	```c
280	#ifdef PERCEPTION_UNIT_TEST
281	int main() {
282	    perception_init(API_URL, API_KEY);
283	    
284	    // 读一张本地测试图片
285	    FILE *f = fopen("test_frame.jpg", "rb");
286	    uint8_t jpeg[50*1024];
287	    size_t len = fread(jpeg, 1, sizeof(jpeg), f);
288	    fclose(f);
289	    
290	    observation_t obs;
291	    int ret = perception_process(jpeg, len, &obs);
292	    
293	    printf("person=%d phone=%d near_hand=%d pitch=%.1f motion=%.2f conf=%.2f\n",
294	           obs.person_present, obs.phone_detected, obs.phone_near_hand,
295	           obs.head_pitch, obs.hand_motion_score, obs.confidence);
296	    
297	    return ret;
298	}
299	#endif
300	```
301	
302	**联调顺序**：先跟张沐泽联调（确认 Wi-Fi POST 能通）→ 再跟赵思涵联调（确认 Observation 格式对）。
303	

---

### [2026-08-28 15:17:29] 用户

[工具结果] 1	# FOCUS AIoT 产品方案与分工 v2.0
2	
3	## 问题回顾
4	
5	v1 方案中，周礼航（看书模式识别）与赵思涵（看课件模式识别）的工作本质相同——都是调云端 API、写判定规则、设阈值，差异仅在于参数不同，确实存在重复。
6	
7	## v2 核心思路
8	
9	**按认知层级切分，而非按使用场景切分：**
10	
11	```
12	  v1 (×)                         v2 (✓)
13	  ┌─────────┬─────────┐         ┌─────────┬─────────┐
14	  │ 看书识别  │ 课件识别  │         │ 视觉感知  │ 行为分析  │
15	  │ (周礼航) │ (赵思涵) │         │ (周礼航) │ (赵思涵) │
16	  └─────────┴─────────┘         └─────────┴─────────┘
17	       ↓ 工作重复                     ↓ 工作正交
18	
19	  v2 中两个人做完全不同的事：
20	  周礼航 → 从图片里看出「有什么」(一帧一帧看)
21	  赵思涵 → 从时间线判断「在干嘛」(多帧串起来看)
22	```
23	
24	---
25	
26	## 一、产品模式重新定义
27	
28	两种模式不再是"看书 vs 看课件"，而是两种**行为干预策略**：
29	
30	### 严格模式
31	
32	> 定位：**零容忍监督者**。适合自制力差、需要外部压力推动的用户。
33	
34	| 维度 | 策略 |
35	|---|---|
36	| 分心判定 | 阈值紧（看手机 8s、离座 10s、瞌睡 8s） |
37	| 提醒方式 | 语音警告 + LCD 红色警告图标 |
38	| 提醒频率 | 每次分心都提醒（间隔 30s） |
39	| 语言风格 | 指令式：「请放下手机」「请回到座位」 |
40	| 评分倾向 | 扣分重（玩手机 -15、离座 -10、瞌睡 -20） |
41	| 适合用户 | 考前冲刺、deadline 赶工、自制力薄弱期 |
42	
43	### 鼓励模式
44	
45	> 定位：**正向激励陪伴者**。适合容易因批评而放弃、需要成就感的用户。
46	
47	| 维度 | 策略 |
48	|---|---|
49	| 分心判定 | 阈值松（看手机 15s、离座 20s、瞌睡 12s） |
50	| 提醒方式 | 温和提示音 + LCD 鼓励文字 |
51	| 提醒频率 | 低频（间隔 120s），累计分心 3 次才提醒 1 次 |
52	| 语言风格 | 鼓励式：「休息好了就继续吧」「你已经专注 20 分钟了，加油」 |
53	| 正面反馈 | **主动播报专注里程碑**（每专注 30 分钟鼓励一次） |
54	| 评分倾向 | 扣分轻（玩手机 -5、离座 -3、瞌睡 -8），**正向加分**（连续专注 30 分钟 +5） |
55	| 适合用户 | 长期习惯养成、易焦虑用户、日常学习 |
56	
57	### 两种模式不改变硬件/架构
58	
59	```
60	  同一套摄像头 → 同一套云端 API → 周礼航输出统一的 Observation
61	                                      ↓
62	  赵思涵根据 mode 参数选择不同的分析策略
63	    strict_mode_analyzer()  → 严格判定 + 指令式输出
64	    gentle_mode_analyzer()  → 宽松判定 + 鼓励式输出
65	```
66	
67	---
68	
69	## 二、新架构总览
70	
71	```
72	┌─────────────────────────────────────────────────────────┐
73	│                     硬件层 (ESP32-S3-EYE)                │
74	│  摄像头 ── 麦克风(可选) ── LCD ── 按键×3 ── 扬声器       │
75	│               │                 │       │         │       │
76	│         ┌─────┴─────┐     ┌────┴──┐ ┌──┴───┐ ┌──┴────┐ │
77	│         │ camera_task│     │ui_task│ │按键IRQ│ │audio  │ │
78	│         │ (30s/5s)  │     │ (1Hz) │ │→ mq  │ │_task  │ │
79	│         └─────┬─────┘     └───────┘ └──────┘ └───────┘ │
80	│               │ JPEG                                      │
81	│         ┌─────▼─────┐                                    │
82	│         │ wifi_task │  HTTPS POST → 云端 AI              │
83	│         └─────┬─────┘         ← JSON 响应                │
84	│               │ 原始检测结果                               │
85	├───────────────┼─────────────────────────────────────────┤
86	│               ▼                  周礼航 负责              │
87	│  ┌────────────────────────┐                              │
88	│  │   视觉感知模块           │                              │
89	│  │   stabilize_observation │  去抖动 + 置信度过滤          │
90	│  │   → Observation 结构体  │  统一输出，不区分模式         │
91	│  └────────────┬───────────┘                              │
92	│               │ {person, phone, pose, motion, ts}         │
93	├───────────────┼─────────────────────────────────────────┤
94	│               ▼                  赵思涵 负责              │
95	│  ┌────────────────────────┐                              │
96	│  │   行为分析模块           │                              │
97	│  │   analyze_behavior()   │  时序分析 + 模式策略          │
98	│  │   → StudyState         │  strict / gentle 双引擎      │
99	│  │   → Action             │  专注里程碑检测 + 正面反馈    │
100	│  └────────────┬───────────┘                              │
101	│               │ {status, action, suggestion}              │
102	├───────────────┼─────────────────────────────────────────┤
103	│               ▼                  万思源 负责              │
104	│  ┌────────────────────────┐                              │
105	│  │   状态机                 │  4 状态简化 FSM              │
106	│  │   消费 StudyState       │  驱动计时/UI/语音/报告        │
107	│  └────────────────────────┘                              │
108	└─────────────────────────────────────────────────────────┘
109	```
110	
111	---
112	
113	## 三、重新分工
114	
115	| 成员 | 模块 | 核心职责 | 产出物 |
116	|---|---|---|---|
117	| **万思源** | 系统适配 + 主控框架 + 状态机 | openvela 移植、多任务框架、状态机、模块接口定义 | `main.c` + `state_machine.c` + 全部 `.h` |
118	| **张沐泽** | 硬件驱动全栈 | 摄像头、LCD、Wi-Fi、按键、扬声器驱动 | `libhardware.a` |
119	| **周礼航** | **视觉感知模块** | 云端 API 封装、图像预处理、Observation 去抖稳定 | `libperception.a` |
120	| **赵思涵** | **行为分析模块** | 时序状态判定、严格/鼓励双引擎、专注里程碑、正面反馈 | `libbehavior.a` |
121	| **郭黄亦昕** | LCD UI + 交互 + MiMo | 页面设计、状态图标、交互逻辑、MiMo 大模型接入 | `libui.a` |
122	
123	### 为什么这次不重复了
124	
125	```
126	  周礼航的输入: 一张 JPEG 图片
127	  周礼航的输出: Observation { person: true, phone: detected, head_pitch: -35, ... }
128	  
129	  赵思涵的输入: 一连串 Observation (带时间戳的历史)
130	  赵思涵的输出: StudyState { status: DISTRACTED, action: REMIND, message: "请放下手机" }
131	  
132	  → 周礼航做的是「空间」上的识别 (单帧静态分析)
133	  → 赵思涵做的是「时间」上的分析 (多帧动态推理)
134	  → 两个人拿到的输入类型不同、用的算法不同、产出的东西不同
135	  → 工作完全不重复
136	```
137	
138	---
139	
140	## 四、简化后的状态机（4 状态）
141	
142	去掉 v1 中细分的 STATE_ALERT 和 STATE_PAUSED，合并到 MONITORING 内部处理：
143	
144	```
145	         ┌──────────┐
146	  长按开始 │   IDLE   │◀──────────┐
147	  ┌──────▶│   空闲   │           │
148	  │       └────┬─────┘           │
149	  │            │                 │
150	  │       ┌────▼──────┐         │
151	  │       │MODE_SELECT │         │
152	  │       │  选择模式  │         │
153	  │       └────┬─────┘         │
154	  │            │ 按开始          │
155	  │       ┌────▼──────┐         │
156	  │       │ MONITORING │ 按停止  │
157	  │       │   监测中   ├────────▶│
158	  │       │           │         │
159	  │       │ 内部处理:  │         │
160	  │       │ ·分心检测  │         │
161	  │       │ ·暂停/恢复 │         │
162	  │       │ ·提醒触发  │         │
163	  │       └───────────┘         │
164	  │                             │
165	  │       ┌───────────┐         │
166	  └───────│  REPORT   │◀────────┘
167	   按开始  │   报告    │
168	          └───────────┘
169	```
170	
171	```c
172	// 简化后的状态机（约 60 行）
173	void state_machine_process(study_state_t *s) {
174	    switch (state) {
175	    case STATE_IDLE:
176	        if (btn == BTN_START_LONGPRESS)
177	            transition_to(STATE_MODE_SELECT);
178	        break;
179	
180	    case STATE_MODE_SELECT:
181	        if (btn == BTN_MODE) { mode = !mode; update_lcd_mode(mode); }
182	        else if (btn == BTN_START) { init_session(); transition_to(STATE_MONITORING); }
183	        break;
184	
185	    case STATE_MONITORING:
186	        if (btn == BTN_PAUSE)      { paused = !paused; }
187	        if (btn == BTN_STOP)       { end_session(); transition_to(STATE_REPORT); }
188	        if (paused)                { break; }  // 暂停时不做任何处理
189	        
190	        // 核心：消费赵思涵的行为分析结果
191	        if (s->status == STATUS_FOCUSED) {
192	            effective_time += elapsed;
193	            if (mode == MODE_GENTLE && s->milestone_reached)
194	                play_encouragement(s->milestone_minutes);  // 鼓励模式专属
195	        }
196	        if (s->action == ACTION_REMIND) {
197	            play_reminder(s->message);
198	        }
199	        break;
200	
201	    case STATE_REPORT:
202	        if (btn == BTN_START) { reset_session(); transition_to(STATE_IDLE); }
203	        break;
204	    }
205	}
206	```
207	
208	**简化收益**：状态数 6→4，代码量 150→60 行，边界情况减半。
209	
210	---
211	
212	## 五、关键数据结构（统一接口契约）
213	
214	```c
215	// ── 周礼航的输出 ──
216	// 每一帧图像经过云端 API → 去抖 → 输出一个 Observation
217	typedef struct {
218	    bool     person_present;       // 画面中是否有人
219	    float    person_bbox[4];       // 人体边界框 (x,y,w,h) 归一化
220	    bool     phone_detected;       // 是否检测到手机
221	    bool     phone_near_hand;      // 手机是否在手部区域
222	    float    head_pitch;           // 头部俯仰角 (度, 负=低头 正=仰头)
223	    float    head_yaw;             // 头部偏航角
224	    float    hand_motion_score;    // 手部运动量 [0-1]
225	    float    confidence;           // 整体置信度 [0-1]
226	    uint32_t timestamp_ms;         // 时间戳
227	} observation_t;
228	
229	// ── 赵思涵的输出 ──
230	// 基于 Observation 序列分析后输出行为状态 + 应采取的行动
231	typedef enum { FOCUSED, GLANCING_PHONE, PLAYING_PHONE, AWAY, DROWSY } status_t;
232	typedef enum { NONE, REMIND, ENCOURAGE } action_t;
233	
234	typedef struct {
235	    status_t  status;              // 当前学习状态
236	    action_t  action;              // 应采取的行动
237	    char      message[128];        // 提醒/鼓励文字
238	    bool      milestone_reached;   // 是否达到专注里程碑 (鼓励模式)
239	    int       milestone_minutes;   // 连续专注分钟数
240	    uint8_t   focus_score_delta;   // 评分变化量
241	} study_state_t;
242	```
243	
244	**接口的稳定性**：两个结构体定义好之后，周礼航和赵思涵可以完全独立开发——周礼航只关心怎么生成 `observation_t`，赵思涵只关心怎么从 `observation_t[]` 推导 `study_state_t`。
245	
246	---
247	
248	## 六、周礼航的工作：视觉感知模块
249	
250	### 输入/输出
251	
252	```
253	  输入: JPEG 图像 (320×240, 来自 camera_task)
254	  输出: observation_t (每帧一个)
255	```
256	
257	### 做三件事
258	
259	**① 云端 API 调用**
260	
261	```
262	  HTTP POST /api/v1/detect
263	  Body: { "image": "<base64>", "width": 320, "height": 240 }
264	  Response: { "person": {...}, "phone": {...}, "pose": {...} }
265	```
266	
267	云端 API 不变，仍然调用百度 AI 或阿里云视觉 API。**两种模式共用同一个 API**，不做任何区分。
268	
269	**② 原始检测结果 → 去抖稳定**
270	
271	连续检测中可能出现相邻帧结果来回跳。用一个简单的滑动窗口去抖：
272	
273	```c
274	// 3 帧多数投票去抖
275	observation_t stabilize(cloud_result_t raw) {
276	    static cloud_result_t history[3];
277	    static int idx = 0;
278	    
279	    history[idx] = raw;
280	    idx = (idx + 1) % 3;
281	    
282	    observation_t obs;
283	    obs.person_present = majority_vote(history, person_present, 3);
284	    obs.phone_detected = majority_vote(history, phone_detected, 3);
285	    obs.head_pitch     = median(history, head_pitch, 3);   // 角度取中位数
286	    obs.hand_motion    = max(history, hand_motion, 3);     // 运动取最大
287	    obs.confidence     = average(history, confidence, 3);
288	    obs.timestamp_ms   = raw.timestamp_ms;
289	    return obs;
290	}
291	```
292	
293	**③ 对上层屏蔽云端 API 细节**
294	
295	如果将来换一家云端服务商，只改这个模块内的 URL 和 JSON 解析，其他所有人不受影响。
296	
297	### 可行性分析
298	
299	- 云端 API 调用是标准的 HTTP POST + JSON 解析，ESP32 上的 HTTP client 和 cJSON 库都是成熟方案
300	- 3 帧滑动窗口去抖，计算量极小（几次比较和均值），在 240MHz CPU 上完全可忽略
301	- 整个模块约 200 行 C，单文件 `perception.c`
302	
303	---
304	
305	## 七、赵思涵的工作：行为分析模块
306	
307	### 输入/输出
308	
309	```
310	  输入: observation_t 序列 (带时间戳的历史)
311	         + mode 参数 (STRICT 或 GENTLE)
312	  输出: study_state_t (每收到一帧 Observation 就更新)
313	```
314	
315	### 做三件事
316	
317	**① 时序状态判定**
318	
319	维护一个 Observation 的时间窗口（保留最近 60 秒的记录），基于时序变化判断状态：
320	
321	```c
322	study_state_t analyze_behavior(observation_t *history, int count, mode_t mode) {
323	    observation_t *latest = &history[count - 1];
324	    
325	    // 离座判定
326	    int away_count = count_false_in_window(history, count, person_present, 15);
327	    if (away_count >= 3)  // 连续 3 帧无人 → 离座
328	        return make_state(AWAY, REMIND, mode);
329	    
330	    // 玩手机判定 (时序关键)
331	    if (latest->phone_detected && latest->phone_near_hand) {
332	        int phone_duration = calc_phone_duration(history, count);
333	        bool has_hand_motion = calc_avg_motion(history, count) > 0.3;
334	        
335	        int threshold = (mode == STRICT) ? 8 : 15;  // 严格/宽松不同阈值
336	        
337	        if (phone_duration > threshold && has_hand_motion)
338	            return make_state(PLAYING_PHONE, REMIND, mode);
339	        else if (phone_duration <= threshold)
340	            return make_state(GLANCING_PHONE, NONE, mode);
341	    }
342	    
343	    // 瞌睡判定
344	    if (latest->head_pitch > (mode == STRICT ? 45 : 52)) {
345	        int drowsy_dur = calc_drowsy_duration(history, count);
346	        int threshold = (mode == STRICT) ? 8 : 12;
347	        if (drowsy_dur > threshold)
348	            return make_state(DROWSY, REMIND, mode);
349	    }
350	    
351	    // 专注里程碑检测 (鼓励模式专属)
352	    if (mode == GENTLE) {
353	        int focus_streak = calc_focus_streak_minutes(history, count);
354	        if (focus_streak > 0 && focus_streak % 30 == 0 && !already_celebrated(focus_streak))
355	            return make_state(FOCUSED, ENCOURAGE, mode, focus_streak);
356	    }
357	    
358	    return make_state(FOCUSED, NONE, mode);
359	}
360	```
361	
362	**② 严格模式 vs 鼓励模式的行为差异**
363	
364	```c
365	study_state_t make_state(status_t s, action_t a, mode_t m, int streak) {
366	    study_state_t st = { .status = s, .action = a };
367	    
368	    if (a == REMIND) {
369	        if (m == STRICT) {
370	            snprintf(st.message, 128, "%s", strict_messages[s]);
371	            st.focus_score_delta = strict_penalties[s];  // 重扣分
372	        } else {
373	            snprintf(st.message, 128, "%s", gentle_messages[s]);
374	            st.focus_score_delta = gentle_penalties[s];  // 轻扣分
375	        }
376	    }
377	    
378	    if (a == ENCOURAGE) {  // 仅鼓励模式
379	        snprintf(st.message, 128, "已专注学习 %d 分钟,继续保持!", streak);
380	        st.milestone_reached = true;
381	        st.milestone_minutes = streak;
382	        st.focus_score_delta = +5;  // 正向加分
383	    }
384	    
385	    return st;
386	}
387	
388	// 严格模式话术
389	const char* strict_messages[] = {
390	    [PLAYING_PHONE] = "请放下手机!",
391	    [AWAY]          = "请回到座位!",
392	    [DROWSY]        = "请注意坐姿!",
393	};
394	
395	// 鼓励模式话术
396	const char* gentle_messages[] = {
397	    [PLAYING_PHONE] = "休息好了就继续吧~",
398	    [AWAY]          = "等你回来哦~",
399	    [DROWSY]        = "要不要起来活动一下?",
400	};
401	```
402	
403	**③ 两种模式的参数配置表**
404	
405	```c
406	typedef struct {
407	    int  phone_glance_sec;      // 看手机判定阈值
408	    int  phone_playing_sec;     // 玩手机判定阈值
409	    int  away_sec;              // 离座判定阈值
410	    int  drowsy_sec;            // 瞌睡判定阈值
411	    int  remind_cooldown_sec;   // 提醒间隔
412	    int  remind_after_n_times;  // 累计几次分心才提醒
413	    int  focus_milestone_min;   // 专注里程碑间隔(分钟)
414	    int  score_penalty_phone;   // 玩手机扣分
415	    int  score_penalty_away;    // 离座扣分
416	    int  score_penalty_drowsy;  // 瞌睡扣分
417	    int  score_bonus_milestone; // 专注里程碑加分
418	    bool enable_milestone;      // 是否启用里程碑鼓励
419	    const char** messages;      // 提醒话术
420	} mode_config_t;
421	
422	mode_config_t MODES[2] = {
423	    [STRICT] = {
424	        .phone_glance_sec     = 8,
425	        .phone_playing_sec    = 8,
426	        .away_sec             = 10,
427	        .drowsy_sec           = 8,
428	        .remind_cooldown_sec  = 30,
429	        .remind_after_n_times = 1,      // 每次分心都提醒
430	        .focus_milestone_min  = 0,      // 不启用
431	        .score_penalty_phone  = -15,
432	        .score_penalty_away   = -10,
433	        .score_penalty_drowsy = -20,
434	        .score_bonus_milestone = 0,
435	        .enable_milestone     = false,
436	        .messages             = strict_messages,
437	    },
438	    [GENTLE] = {
439	        .phone_glance_sec     = 15,
440	        .phone_playing_sec    = 15,
441	        .away_sec             = 20,
442	        .drowsy_sec           = 12,
443	        .remind_cooldown_sec  = 120,
444	        .remind_after_n_times = 3,      // 累计 3 次才提醒
445	        .focus_milestone_min  = 30,     // 每 30 分钟鼓励一次
446	        .score_penalty_phone  = -5,
447	        .score_penalty_away   = -3,
448	        .score_penalty_drowsy = -8,
449	        .score_bonus_milestone = 5,
450	        .enable_milestone     = true,
451	        .messages             = gentle_messages,
452	    },
453	};
454	```
455	
456	### 可行性分析
457	
458	- 时序分析不需要深度学习，就是规则引擎 + 时间窗口统计，约 250 行 C
459	- Observation 历史维护一个环形缓冲区（60 秒 / 5 秒每帧 = 12 条记录，每条约 40 字节，总共 < 500 字节）
460	- 两种模式共用同一套分析框架，只换配置表，不换代码
461	- **与周礼航的工作完全正交**：周礼航提供 observation_t，赵思涵消费 observation_t
462	
463	---
464	
465	## 八、郭黄亦昕的工作：双模式 UI 差异化
466	
467	鼓励模式下 UI 需要额外的视觉元素：
468	
469	| UI 元素 | 严格模式 | 鼓励模式 |
470	|---|---|---|
471	| 状态图标 | 红色警告图标 | 黄色提示图标 |
472	| 分心计数 | 大字显示 | 小字显示（降低焦虑） |
473	| 专属元素 | 无 | **专注里程碑进度条** + **鼓励语弹窗** |
474	| 报告话术 | 「本次分心 5 次」 | 「你专注了 3 个 30 分钟！」 |
475	| 评分展示 | 扣分明细 | 扣分 + 加分（正负分列） |
476	
477	---
478	
479	## 九、简化开发计划（10 周 → 8 周）
480	
481	去掉冗余后，开发周期可缩短：
482	
483	| 周次 | 任务 | 负责人 |
484	|---|---|---|
485	| 1 | openvela 环境搭建 + 硬件驱动通 | 万思源 + 张沐泽 |
486	| 2 | 摄像头 → Wi-Fi → 云端 API 联调 | 张沐泽 + 周礼航 |
487	| 3 | Observation 去抖稳定 + 输出验证 | 周礼航 |
488	| 4 | 行为分析引擎 + 双模式配置表 | 赵思涵 |
489	| 5 | 状态机实现 + 接口联调 | 万思源 |
490	| 6 | LCD UI 全部页面（含双模式差异） | 郭黄亦昕 |
491	| 7 | MiMo 集成 + 系统联调 + 参数整定 | 全员 |
492	| 8 | 稳定性测试 + 演示准备 | 全员 |
493	
494	---
495	
496	## 十、总结：v1 vs v2
497	
498	| 维度 | v1 | v2 |
499	|---|---|---|
500	| 周礼航工作 | 看书模式识别（阈参数不同） | **视觉感知**：云端 API + 去抖 + Observation |
501	| 赵思涵工作 | 课件模式识别（阈值不同） | **行为分析**：时序推理 + 双模式策略引擎 |
502	| 重复度 | 高（同一类工作 × 2） | 零（输入类型不同，算法不同） |
503	| 模式定义 | 看书 vs 看课件（场景） | 严格 vs 鼓励（干预策略） |
504	| 状态机 | 6 状态 / 150 行 | 4 状态 / 60 行 |
505	| 参数管理 | 分散在两人代码里 | 集中在赵思涵的 `mode_config_t` 配置表 |
506	| 扩展性 | 新增场景 = 新增一个人 | 新增模式 = 加一行配置 + 加一套话术 |
507	| 分工合理性 | 老师质疑 | 各做各的，互不依赖 |
508	

---

### [2026-08-28 15:17:31] 用户

[工具结果] 1	# FOCUS AIoT - 成员任务安排
2	
3	> 更新: 2026-08-19 | 负责人: 万思源
4	> 前提: 接口已冻结 (`api/*.h`), 状态机/LCD/UI/行为引擎/硬件全栈已完成。
5	
6	## 当前完成状态
7	
8	| 模块 | 负责人 | 状态 |
9	|---|---|---|
10	| api/*.h 接口冻结 | 万思源 | ✅ |
11	| core/state_machine.c | 万思源 | ✅ 已合并 |
12	| ui/ (LCD页面+MiMo+字体) | 郭黄亦昕 | ✅ 已合并 |
13	| hardware/lcd_st7789.c | 张沐泽 | ✅ 已合并, 真机验证通过 |
14	| behavior/ (时序引擎+配置表+单测) | 赵思涵 | ✅ 已合并, 单测 100% 通过 |
15	| hardware/ 全栈 (按键/WiFi/摄像头/音频) | 张沐泽 | ✅ **真机核验 100% 通过** (PR #10) |
16	
17	**关键衔接**: `core/mock.c` 已提供 **weak `perception_get_history()`** 临时历史提供器,
18	真实感知模块接入后由强符号自动覆盖 (和 LCD stub 相同的替换机制)。行为引擎当前直接
19	消费 mock 历史即可运行, 无需等待真实感知。
20	
21	**硬件驱动状态 (2026-08-19 真机核验完成)**:
22	- LCD ✅ 上屏 / 按键 ✅ 长短按 / 音频 ✅ LED 降级 (板载无蜂鸣器)
23	- 摄像头 ✅ RGB565 采帧 (驱动为单帧模式, 逐帧触发) / WiFi ✅ 连接+DHCP+HTTP POST
24	- 真机核验修复: camera 格式/缓冲、wifi ioctl 流程、audio 降级等, 见 PR #10
25	
26	---
27	
28	## 一、张沐泽 - 硬件驱动全栈 (`hardware/`)
29	
30	**原则**: 每个驱动独立 `.c` + Kconfig 开关 + mock 可回退 (和 LCD 一样的模式)。
31	
32	### 任务 1: 按键驱动 (优先)
33	
34	- **文件**: `hardware/buttons.c`
35	- **核心函数**: `button_init()`, `button_get_event()`
36	- **效果**: 长按进入模式选择、短按开始/暂停——**用手按驱动 FSM** (替换当前 mock 自动序列), 串口看到真实按键事件。
37	
38	### 任务 2: WiFi 驱动
39	
40	- **文件**: `hardware/wifi_esp32.c`
41	- **核心函数**: `wifi_connect()`, `wifi_http_post()`, `wifi_get_rssi()`
42	- **效果**: 连上 WiFi, `wifi_http_post` 到测试地址返回成功 (替换 `wifi_stub.c`, 让 MiMo 走真实 API)。
43	
44	### 任务 3: 摄像头驱动
45	
46	- **文件**: `hardware/camera_ov2640.c`
47	- **核心函数**: `camera_init()`, `camera_capture_frame()`
48	- **效果**: 采到一帧 JPEG, 大小合理 (供周礼航取帧发云端)。
49	
50	### 任务 4: 音频驱动
51	
52	- **文件**: `hardware/audio_i2s.c`
53	- **核心函数**: `audio_play_tts()`, `audio_play_buzzer()`
54	- **效果**: REMIND 时发出警告音/蜂鸣 (替换 mock 打印)。
55	
56	### ⚠️ 接线注意
57	
58	当前 `core/mock.c` 定义了 `button_get_event`/`audio_play_tts` 等**普通函数**, 你接入真实驱动会冲突。
59	解决方案 (和 LCD 相同): **Kconfig 开关二选一编译**, 例如:
60	- `CONFIG_CONTEST2026_087_BUTTON_STUB=y` → 编译 mock
61	- 否则 → 编译你的真实驱动
62	
63	`Makefile`/`CMakeLists.txt` 已有这个 if/else 模式 (参考 LCD_STUB)。
64	
65	### 验收
66	
67	- 按键: 长按进入模式选择, 短按开始/暂停, FSM 全程用手操作。
68	- WiFi: `wifi_http_post` 返回成功, MiMo 请求能发出去。
69	- 摄像头: `camera_capture_frame` 返回有效 JPEG 帧。
70	- 音频: REMIND 触发真实提示音。
71	
72	---
73	
74	## 二、周礼航 - 视觉感知 (`perception/`) ⭐ 当前焦点
75	
76	**任务**: 实现 `api/perception.h` 三个函数, 从图片输出 `observation_t`。
77	
78	### 📁 要写的文件
79	
80	```
81	perception/perception.c          ← 主实现 (三函数)
82	perception/perception.h          ← 内部声明 (可选)
83	tests/test_perception.c          ← 独立测试 (可选, 参考 test_behavior.c 模式)
84	```
85	
86	### 函数实现细化
87	
88	**① `perception_init(api_url, api_key)`**
89	- static 保存 url/key (如 g_api_url/g_api_key)
90	- 清零历史缓冲 + 计数器
91	- 返回 FOCUS_OK
92	
93	**② `perception_process(jpeg, jpeg_len, out)`** — 核心
94	
95	阶段 1 (mock, 先联调):
96	- 不调云端, 用固定规则: 根据 jpeg_len 或预设序列轮流输出
97	  FOCUSED/PLAYING_PHONE/AWAY/DROWSY 对应的 observation_t
98	- 这样赵思涵/万思源能立刻联调
99	
100	阶段 2 (真实云端):
101	```
102	base64_encode(jpeg, jpeg_len, b64)     // 320x240 JPEG ≈ 30KB → b64 ≈ 40KB
103	构造 JSON: {"image":"<b64>","width":320,"height":240}
104	wifi_http_post(api_url, json, resp, 4096)   // 张沐泽的, ≤6s
105	cJSON 解析 resp
106	填充 observation_t
107	```
108	
109	**③ `perception_get_history(buf, n)`**
110	- 环形缓冲区 `obs_history[60]`, 每条约 40 字节 → 2.4KB
111	- 从旧到新拷贝 (取最近的 n 条)
112	- 返回实际条数
113	
114	### 云端 API 协议 (已冻结, 见规范)
115	
116	```
117	POST /api/v1/detect
118	Request:  {"image":"<base64>","width":320,"height":240}
119	Response: {"code":0,"data":{
120	            "person":{"detected":true,"bbox":[0.15,0.10,0.70,0.85]},
121	            "phone":{"detected":true,"near_hand":true},
122	            "head_pose":{"pitch":-25.3,"yaw":2.1},
123	            "hand_motion_score":0.35,"confidence":0.92}}
124	```
125	
126	### 去抖 (阶段 2)
127	
128	3 帧滑动窗口:
129	- bool 字段 (person/phone/near_hand): 多数投票
130	- float 字段 (pitch/yaw): 中位数
131	- hand_motion: 取最大值 (宁可多报)
132	- confidence: 取均值
133	
134	### 时间戳
135	
136	- 用 `clock_gettime(CLOCK_MONOTONIC)` (参考 `core/state_machine.c` 的 monotonic_ms)
137	- 每帧写入 `out->timestamp_ms`
138	
139	### 关键约束
140	
141	- 摄像头是**单帧模式**: 用 `V4L2_BUF_TYPE_STILL_CAPTURE` + `VIDIOC_TAKEPICT_START` 逐帧触发。
142	  张沐泽已提供 `camera_capture_frame()` (RGB565), 如需要 JPEG 请按规范走 STILL_CAPTURE。
143	- HTTP 超时 ≤6s, JSON 缺字段不崩 (cJSON 判空)。
144	- **不区分严格/鼓励模式** (那是赵思涵的事)。
145	- 失败返回: `FOCUS_ERR_PERCEP_TIMEOUT(-30)` / `FOCUS_ERR_PERCEP_JSON(-31)` / `FOCUS_ERR_PERCEP_NODATA(-32)`
146	
147	### 编译接入
148	
149	- `Makefile`/`CMakeLists.txt` 的 `CSRCS` 加 `perception/perception.c`
150	- mock 路径保留: 用 `#ifdef PERCEPTION_MOCK` 或 Kconfig 开关, 默认 mock 可回退
151	- ⚠️ 提供强符号 `perception_get_history()` 即自动覆盖 `core/mock.c` 的 weak 桩
152	
153	### 验收
154	
155	- `perception_process()` 返回有效 observation (mock + 真实双路径)。
156	- `perception_get_history()` 返回历史, 时间戳递增。
157	- 云端失败返回错误码, 不阻塞 >6s。
158	- 真机: `hello_app` 主循环 behavior 消费真实 history 而非 mock。
159	
160	---
161	
162	## 三、赵思涵 - 行为分析 (`behavior/`)
163	
164	**任务**: 实现 `api/behavior.h`, 消费 observation 序列输出 `study_state_t`。
165	
166	### 任务 1: 迁移配置表 ✅ 已完成
167	
168	- **文件**: `behavior/behavior_config.c`
169	- `g_mode_configs`/`strict_messages`/`gentle_messages` 已迁出 `hello_app_main.c`。
170	- 主入口已调用 `behavior_init(MODE_STRICT)`。
171	
172	### 任务 2: 真实时序引擎 ✅ 已完成
173	
174	- **文件**: `behavior/behavior.c` (401 行)
175	- `behavior_analyze()` 从 `perception_get_history()` 做时序判定:
176	  - 玩手机 8s/15s (严格/鼓励), 离座 10s/20s, 瞌睡 8s/12s
177	  - 优先级: AWAY > 玩手机 > 看手机 > 瞌睡 > 里程碑 > FOCUSED
178	  - 提醒冷却 `remind_cooldown_sec`, 累计提醒, 里程碑去重
179	  - 同帧防重 (`g_last_state` 缓存), uint32 时间回绕处理
180	
181	### 任务 3: 纯 C 单测 ✅ 已完成
182	
183	- **文件**: `tests/behavior_test.c` (250 行)
184	- 覆盖: 空历史/严格手机+冷却/看手机/离座/瞌睡/鼓励阈值+累计/里程碑
185	- 宿主机单测 **100% 通过** (带 `-Werror` 编译零警告)
186	
187	### 审查结论 (2026-08-18)
188	
189	- 行为引擎代码质量高, 时序判定/冷却/里程碑逻辑完整。
190	- 固件编译通过, `behavior_*` 强符号链接, 无 mock 残留。
191	- 与 mock 感知的弱 `perception_get_history` 衔接正确, 真实感知接入后自动覆盖。
192	
193	---
194	
195	## 协作关系
196	
197	```
198	张沐泽 camera_capture_frame ──▶ 周礼航 perception_process ──▶ observation_t
199	                                    │
200	                                    ▼ 周礼航 perception_get_history
201	张沐泽 wifi_http_post ──▶ 周礼航 (云端请求)
202	                                    │
203	                                    ▼
204	                              赵思涵 behavior_analyze ──▶ study_state_t
205	                                    │
206	                                    ▼
207	                          (万思源 state_machine 已就绪, 消费它)
208	```
209	
210	- 赵思涵依赖周礼航的 `perception_get_history`。
211	- 周礼航依赖张沐泽的 camera + wifi。
212	- **张沐泽先做摄像头+WiFi, 周礼航先 mock 后接真, 赵思涵先单测后联调。**
213	
214	## 推进节奏 (更新 2026-08-19)
215	
216	| 阶段 | 内容 | 状态 |
217	|---|---|---|
218	| 行为分析 | 配置表迁移 + 时序引擎 + 单测 | ✅ 赵思涵已完成 |
219	| 硬件全栈 | 按键/WiFi/摄像头/音频驱动 | ✅ 张沐泽真机核验 100% |
220	| 进行中 | 周礼航 perception 实现 (最后一条线) | 进行中 |
221	| 待 | 全链路联调 (真实 observation → behavior → state_machine → UI) | 待 |
222	
223	## 当前焦点
224	
225	1. **周礼航**: perception_process 实现, 替换 mock (先固定 observation, 再接云端), 提供强符号 `perception_get_history()` 接管历史。摄像头已就绪 (张沐泽, RGB565 逐帧采集)。
226	2. 全链路联调: 真实 observation → 行为引擎 (已就绪) → 状态机 → UI 上屏。
227	3. 硬件验证子命令: `hello_app hwbutton|hwaudio|hwcamera|hwwifi <ssid> <pass>` 保留供联调排查。
228	

---

### [2026-08-28 15:24:51] AI

[思考] Now I fully understand the project. This is the "FOCUS AIoT" project, an ESP32-S3-EYE based study monitoring device. The architecture:

1. 张沐泽 (hardware): camera, WiFi, LCD, buttons, audio
2. 周礼航 (perception): single-frame vision analysis → `observation_t` (already done, in C:\temp\focus_perception)
3. 赵思涵 (behavior): temporal/sequence analysis → `study_state_t` (this is what the user wants!)
4. 万思源 (state_machine): FSM
5. 郭黄亦昕 (UI)

The user's request: "识别动作 连续帧jpeg格式 小设备 最好是成品 可以接入C:\temp文件夹下的项目"

This maps exactly to the `behavior` module — 赵思涵's part. The behavior module:
- Input: `observation_t` sequence (with timestamps) from `perception_get_history()`
- Output: `study_state_t` with `status_t` (FOCUSED, GLANCING_PHONE, PLAYING_PHONE, AWAY, DROWSY), `action_t` (NONE, REMIND, ENCOURAGE), message, milestone, etc.

Wait, but the DEVELOPMENT_TASKS (2).md says behavior module is already done by 赵思涵 (✅ 已合并, 单测 100% 通过). But the C:\temp folder only has the `focus_perception` project (周礼航's perception module). There's no behavior module code in C:\temp.

So the user is likely 赵思涵, or wants me to build the behavior module. Actually — re-reading: the user is non-technical, terse. They want a "成品" (finished product) for action recognition on continuous JPEG frames on a small device, that integrates into the C:\temp project.

Actually wait — let me reconsider. The user said "识别动作 连续帧jpeg格式" (action recognition, continuous JPEG frames). The perception module processes JPEG frames one at a time. The behavior module consumes the observation sequence.

Given the docs say behavior module is "✅ 已合并" (already merged in the real repo, not in C:\temp), but the user wants me to build something in C:\temp.

The most sensible interpretation: The user wants the **behavior module** (赵思涵's part) — the temporal action recognition module that takes continuous-frame observations and classifies actions (FOCUSED/PLAYING_PHONE/AWAY/DROWSY). This is the "成品" they want, in the style of the existing `focus_perception` project (which is 周礼航's 成品).

So I should create a `focus_behavior` folder (parallel to `focus_perception`) containing:
- `api/behavior.h` — public interface (study_state_t + status_t + action_t + functions)
- `behavior/behavior.c` — the temporal engine
- `behavior/behavior_internal.h` — internal declarations
- `tests/test_behavior.c` — unit tests
- `BUILD_INTEGRATION.md` — build integration
- `README.md`

This matches the existing `focus_perception` structure exactly, and it's the natural "成品" that integrates into C:\temp.

Now, the important question: should I clarify with the user, or proceed? The user is non-technical and wants me to proactively handle things (主动代办). They said "最好是成品" (best if finished product). So I should just build it.

But wait — let me think carefully. The behavior module consumes `observation_t` from `perception_get_history()`, NOT raw JPEG frames directly. The user said "连续帧jpeg格式" (continuous JPEG frames). 

There are two possible interpretations:
1. Build the behavior module (赵思涵's part) — consumes observation_t sequence (which comes from JPEG frames via perception). This is the "action recognition" that already has a defined contract and is clearly the missing piece in C:\temp.
2. Build something that directly reads JPEG frames and does action recognition (a new perception+behavior combined).

Given the project context, interpretation #1 is clearly correct. The "连续帧" refers to the continuous sequence of frames → observations → behavior analysis. The action recognition IS the behavior module.

Actually, let me reconsider the whole thing. The user has been given the Copilot answer about JPEG action recognition. They want a working product. The C:\temp project already has perception (single frame). The missing piece is behavior (temporal → action recognition). So I should build the behavior module.

This is a substantial coding task. It's clearly a multi-file implementation. Should I use EnterPlanMode? The user is non-technical and wants a finished product. They've said "最好是成品" (best if finished). 

Actually, given the docs are extremely detailed about what the behavior module should do (thresholds, priority order, messages, config table, milestone, cooldown), I have a very clear spec. The spec is essentially fully defined in:
- 产品方案与分工_v2.md section 七 (赵思涵's work)
- DEVELOPMENT_TASKS (2).md section 三 (赵思涵's tasks)

I have enough to build it. The user is non-technical and terse, wants me to just do it. I'll build the complete behavior module following the exact same style/quality as the existing perception module.

Let me define the full spec for the behavior module based on the docs:

### API: `api/behavior.h`

```c
typedef enum { FOCUSED, GLANCING_PHONE, PLAYING_PHONE, AWAY, DROWSY } status_t;
typedef enum { NONE, REMIND, ENCOURAGE } action_t;
typedef enum { MODE_STRICT, MODE_GENTLE } mode_t;  // need mode type

typedef struct {
    status_t  status;
    action_t  action;
    char      message[128];
    bool      milestone_reached;
    int       milestone_minutes;
    uint8_t   focus_score_delta;
} study_state_t;
```

Functions (based on DEVELOPMENT_TASKS):
- `behavior_init(mode_t mode)` — from "主入口已调用 behavior_init(MODE_STRICT)"
- `behavior_analyze()` — from "behavior_analyze() 从 perception_get_history() 做时序判定"
- Config table: `behavior_config.c` with `g_mode_configs`/`strict_messages`/`gentle_messages`

Let me define the exact interface. From DEVELOPMENT_TASKS (2).md:

Task 2 (真实时序引擎):
- `behavior_analyze()` 从 `perception_get_history()` 做时序判定:
  - 玩手机 8s/15s (严格/鼓励), 离座 10s/20s, 瞌睡 8s/12s
  - 优先级: AWAY > 玩手机 > 看手机 > 瞌睡 > 里程碑 > FOCUSED
  - 提醒冷却 `remind_cooldown_sec`, 累计提醒, 里程碑去重
  - 同帧防重 (`g_last_state` 缓存), uint32 时间回绕处理

Task 1 (迁移配置表): `behavior_config.c` with `g_mode_configs`/`strict_messages`/`gentle_messages`

From 产品方案 v2:
- status_t: FOCUSED, GLANCING_PHONE, PLAYING_PHONE, AWAY, DROWSY
- action_t: NONE, REMIND, ENCOURAGE
- mode_t: STRICT, GENTLE
- study_state_t fields as above
- Thresholds:
  - STRICT: phone_glance_sec=8, phone_playing_sec=8, away_sec=10, drowsy_sec=8, remind_cooldown=30, remind_after_n_times=1, milestone=0 (disabled), penalties: phone=-15, away=-10, drowsy=-20
  - GENTLE: phone_glance_sec=15, phone_playing_sec=15, away_sec=20, drowsy_sec=12, remind_cooldown=120, remind_after_n_times=3, milestone=30, penalties: phone=-5, away=-3, drowsy=-8, bonus milestone=5
- messages:
  - strict: PLAYING_PHONE="请放下手机!", AWAY="请回到座位!", DROWSY="请注意坐姿!"
  - gentle: PLAYING_PHONE="休息好了就继续吧~", AWAY="等你回来哦~", DROWSY="要不要起来活动一下?"

I need to design the interface to match the frozen api/behavior.h. But I don't have the frozen api/behavior.h. The DEVELOPMENT_TASKS says behavior is "✅ 已合并" in the real repo, so api/behavior.h exists there but I don't have it. I'll design a reasonable interface consistent with the docs, and mark it as "参考拷贝" like perception.h does.

Let me design:

```c
// api/behavior.h
typedef enum {
    FOCUSED = 0,
    GLANCING_PHONE,
    PLAYING_PHONE,
    AWAY,
    DROWSY,
    STATUS_MAX
} status_t;

typedef enum {
    NONE = 0,
    REMIND,
    ENCOURAGE,
} action_t;

typedef enum {
    MODE_STRICT = 0,
    MODE_GENTLE,
    MODE_MAX
} mode_t;

typedef struct {
    status_t  status;
    action_t  action;
    char      message[128];
    bool      milestone_reached;
    int       milestone_minutes;
    uint8_t   focus_score_delta;
} study_state_t;

int  behavior_init(mode_t mode);
int  behavior_analyze(study_state_t *out);
```

Wait, but `behavior_analyze()` consumes `perception_get_history()`. Should `behavior_analyze` take the history as a parameter, or call `perception_get_history` itself?

From DEVELOPMENT_TASKS: "`behavior_analyze()` 从 `perception_get_history()` 做时序判定" — so it calls `perception_get_history()` internally. But for unit testing, it's easier if it takes history as a parameter. Hmm.

Looking at the 产品方案 v2 pseudocode: `study_state_t analyze_behavior(observation_t *history, int count, mode_t mode);` — takes history as parameter.

But DEVELOPMENT_TASKS says `behavior_analyze()` (no args shown) calls `perception_get_history()` internally.

The real frozen behavior.c (401 lines) is described as "`behavior_analyze()` 从 `perception_get_history()` 做时序判定". So `behavior_analyze()` likely has signature `int behavior_analyze(study_state_t *out)` or `study_state_t behavior_analyze(void)`.

To be safe and match the pattern, and since the frozen version exists but I can't see it, I'll design a clean interface. Let me use the pattern that's testable AND matches the docs. I'll make `behavior_analyze(study_state_t *out)` call `perception_get_history()` internally, but also factor out the core logic into a testable function `behavior_analyze_with_history(const observation_t *history, int count, study_state_t *out)`.

Actually, to keep it clean and match the "参考拷贝" convention, let me design:

```c
// public (frozen signature)
int behavior_init(mode_t mode);
int behavior_analyze(study_state_t *out);   // calls perception_get_history() internally

// internal (testable)
int behavior_analyze_history(const observation_t *history, int count, study_state_t *out);
```

This is clean and testable. The unit tests feed a synthetic history into `behavior_analyze_history()`.

Now the temporal logic. Let me carefully design the algorithm based on the docs:

The observation history is a sequence with timestamps. The camera captures at ~5s/frame (from "camera_task (30s/5s)" in the architecture diagram — actually "30s/5s" suggests two intervals). Wait, let me look: "camera_task (30s/5s)" — this might mean capture every 5s or 30s. The 产品方案 says "60 秒 / 5 秒每帧 = 12 条记录" — so 5 seconds per frame, 12 frames = 60 seconds. So frame interval ≈ 5s.

So the behavior module needs to determine duration of a condition based on timestamps (not just frame count), because frame interval might vary. Using timestamps is more robust.

Let me design the algorithm:

1. Get history (oldest → newest) via `perception_get_history()`.
2. If history is empty → return FOCUSED (or some default).
3. Determine durations by scanning from the newest frame backwards:
   - **AWAY duration**: consecutive frames where `person_present == false`.
   - **phone (playing/glancing) duration**: consecutive frames where `phone_detected && phone_near_hand`.
   - **DROWSY duration**: consecutive frames where `head_pitch > drowsy_pitch_threshold` (45 strict / 52 gentle).
4. Priority: AWAY > PLAYING_PHONE > GLANCING_PHONE > DROWSY > milestone > FOCUSED.
5. Cooldown for reminders.
6. Milestone for gentle mode.

Let me think about the exact duration calculation. Given timestamps `timestamp_ms`, and frames at ~5s intervals, I need to compute "how long has the current condition persisted".

Approach: scan from newest frame back to oldest, accumulating consecutive frames matching the condition. The duration = newest_frame.ts - oldest_matching_frame.ts + frame_interval_estimate. But frame interval isn't exactly 5s. 

Simpler robust approach: duration ≈ (number of consecutive matching frames) × (average frame interval), or just use timestamps: duration = latest.ts - first_matching.ts. But that undercounts by one frame interval.

Actually, a cleaner approach: for each condition, find the timestamp when the condition STARTED (the oldest frame in the current consecutive run), then duration = now - start_time. But "now" — we don't have a global clock necessarily; behavior_analyze could call perception_monotonic_ms() (but that's in perception module, not accessible).

Hmm, actually the behavior module can track time itself. But the docs say it consumes the history (which has timestamps). The simplest: duration of a condition = timestamp of newest frame - timestamp of oldest frame in the consecutive matching run. Since frames are ~5s apart, a run of N consecutive matching frames = (N-1)*5s + partial. Using timestamps gives the real elapsed span.

But there's ambiguity: for "玩手机 8s" threshold — if 2 consecutive frames both show phone (span = 5s), that's under 8s. 3 frames (span=10s) ≥ 8s → trigger. So using timestamp span works: (newest - oldest) gives 10s for 3 frames. Good.

Actually, let me reconsider what "duration" means precisely. The natural interpretation: the person has been playing phone continuously for X seconds. With 5s frames, "phone in frame N" means phone present at time T_N. If frames T_0, T_1, ..., T_k all show phone, the person has been playing phone from approximately T_0 to T_k, i.e., (k * 5s) duration. Using T_k - T_0 = k*5s. So "3 consecutive frames = 10s" (if k=2). Hmm, that gives 10s for 3 frames, but maybe they intend 3 frames = 15s of phone use.

This is getting into the weeds. Let me look at what the actual frozen implementation likely does. The doc says "玩手机 8s/15s (严格/鼓励)". With 5s/frame:
- 2 frames = 5s < 8s → not yet
- 3 frames = 10s ≥ 8s → trigger at strict

Actually for a clean implementation, I'll compute duration based on the count of consecutive frames times the median frame interval, but simpler: use timestamp difference plus one frame interval to be safe. 

Actually, let me keep it simple and robust: I'll compute duration as the timestamp span (newest - oldest matching) but add the frame interval. Since I want the "total time the condition has held", the correct value is approximately: (newest_ts - oldest_matching_ts) + frame_interval. Because the oldest matching frame represents the condition being true at that instant, and it's been true since somewhere between oldest_matching_ts - interval and oldest_matching_ts.

This is over-engineering. Let me use a clean, documented heuristic:

**duration_sec(condition run) = (latest_ts - oldest_ts_in_run) / 1000 + frame_interval_sec**

Where frame_interval_sec is estimated from the last two frames. Actually, to avoid complexity, I'll estimate frame interval from the history itself (median of adjacent timestamp deltas), and default to 5s if only 1 frame.

Hmm. Actually, let me reconsider. Maybe simpler and matching the doc's spirit: The doc's pseudocode in 产品方案 uses `calc_phone_duration(history, count)` and `count_false_in_window(history, count, person_present, 15)` (count false in a 15-frame window) and `calc_avg_motion`. So the original design counts FRAMES in a time window.

Given the doc says "连续 3 帧无人 → 离座" in one place and "离座 10s/20s" in another, there's some inconsistency between "frame count" and "seconds". The frozen behavior.c uses seconds (8s/15s, 10s/20s, 8s/12s).

I'll implement with seconds + timestamps, which is the most robust and matches "8s/15s" etc. I'll document my duration convention clearly.

Let me settle on a clean, well-documented convention:

**Duration convention**: A condition's duration = timestamp of the newest frame minus timestamp of the oldest frame in the current consecutive run, plus one frame interval (since the condition was true at least since the oldest matching frame). I'll compute frame interval as the median delta between consecutive frames in history (default 5000ms).

Actually, you know what, I'm overcomplicating this. Let me look at what really matters for a "成品" (finished product) for a non-technical user: clean, correct, well-tested C code that matches the documented contract, compiles with -Werror, and passes unit tests. The exact duration off-by-one won't matter for the demo. I'll pick a clean convention and document it.

Let me finalize the algorithm design:

```c
// behavior.c

// state
static mode_t g_mode;
static uint32_t g_last_remind_ms;    // last reminder timestamp
static int g_distract_count;         // accumulated distractions since last reminder (gentle)
static int g_last_milestone_min;     // last celebrated milestone (dedup)
static status_t g_last_status;       // same-frame dedup cache

// duration helpers scan the history backwards

int behavior_init(mode_t mode) {
    g_mode = mode;
    g_last_remind_ms = 0;
    g_distract_count = 0;
    g_last_milestone_min = 0;
    g_last_status = FOCUSED;
    return FOCUS_OK; // or 0
}

int behavior_analyze(study_state_t *out) {
    observation_t history[HISTORY_MAX];
    int n = perception_get_history(history, HISTORY_MAX);
    return behavior_analyze_history(history, n, out);
}

int behavior_analyze_history(const observation_t *history, int count, study_state_t *out) {
    // 1. validate
    // 2. if count == 0 → FOCUSED, NONE
    // 3. compute durations
    // 4. apply priority + thresholds + cooldown + milestone
    // 5. fill out
}
```

Now the core duration computation. I'll write a helper:

```c
// find the oldest index in the current consecutive run (backwards from newest)
// where `pred(history[i])` is true. Returns the index, or -1 if newest doesn't match.
```

Actually simpler: I'll compute, for each condition, the "streak" going backwards from the newest frame:

```c
static int streak_from_tail(const observation_t *h, int n, bool (*p)(const observation_t*)) {
    int streak = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (p(&h[i])) streak++;
        else break;
    }
    return streak;
}
```

Then duration = (h[n-1].ts - h[n-streak].ts) ... wait if streak = 1, oldest = newest, span = 0.

Let me define duration_sec for a streak of length `k`:
- if k == 0 → 0
- if k == 1 → one frame = frame_interval (default 5s) → but actually a single frame showing phone is at most "just started" → duration ~0-5s. Using frame_interval as the duration for a single frame is reasonable (they've been on phone for roughly one frame period).
- if k >= 2 → (h[n-1].ts - h[n-k].ts) + frame_interval, i.e., the span plus one interval.

Hmm wait, that's (k-1)*interval + interval = k*interval, which for uniform intervals = k * interval. For k=3 → 15s. That's clean: duration = k * frame_interval (where frame_interval is the measured/assumed interval).

Actually the cleanest: **duration_sec = streak_count × frame_interval_sec**, with frame_interval measured from the last two frames (or default 5s). For 8s threshold at 5s/frame: 2 frames = 10s ≥ 8 → trigger. That matches "玩手机 8s" roughly.

But if I use actual timestamps: duration = h[n-1].ts - h[n-k].ts + interval. For uniform 5s, k frames: (k-1)*5 + 5 = 5k. Same thing. For non-uniform, the timestamp version is more accurate. 

I'll use the timestamp-based span + one interval:
```c
static uint32_t streak_duration_ms(const observation_t *h, int n, int streak, uint32_t frame_interval_ms) {
    if (streak <= 0) return 0;
    if (streak == 1) return frame_interval_ms;   // one frame ≈ one interval
    uint32_t span = h[n-1].timestamp_ms - h[n-streak].timestamp_ms;
    // guard against time wrap: if span looks huge, fall back to streak*interval
    return span + frame_interval_ms;
}
```

Time wrap: timestamp_ms is uint32 milliseconds, wraps every ~49.7 days. The docs mention "uint32 时间回绕处理". For spans, I should handle wrap: if newest < oldest, add 2^32. But since history is at most 60 frames × 5s = 300s window, wrap only matters at the exact wrap boundary. I'll handle it: compute `delta = (int32_t)(newest - oldest)` which handles wrap correctly for spans < 2^31 ms (~24.8 days). Good, that's the standard trick.

Actually since these are uint32 timestamps from CLOCK_MONOTONIC and the window is 300s, using `(int32_t)(newest - oldest)` gives the correct signed delta even across a wrap, as long as the true span < 2^31 ms. 

Let me finalize the frame interval estimation:
```c
static uint32_t estimate_frame_interval_ms(const observation_t *h, int n) {
    if (n < 2) return DEFAULT_FRAME_INTERVAL_MS; // 5000
    // use median of adjacent deltas, or just last delta; keep simple: last delta
    int32_t d = (int32_t)(h[n-1].timestamp_ms - h[n-2].timestamp_ms);
    if (d <= 0 || d > 60000) return DEFAULT_FRAME_INTERVAL_MS;
    return (uint32_t)d;
}
```

Now the priority logic:

```c
status_t final_status;
action_t action = NONE;
uint8_t score_delta = 0;
bool milestone = false;

// durations
int away_streak = streak_from_tail(h, n, is_away);       // !person_present
int phone_streak = streak_from_tail(h, n, is_phone_in_hand); // phone_detected && near_hand
int drowsy_streak = streak_from_tail(h, n, is_drowsy);   // head_pitch > pitch_thresh

uint32_t away_ms = streak_duration_ms(...);
uint32_t phone_ms = ...;
uint32_t drowsy_ms = ...;

// thresholds from config
mode_config_t cfg = g_mode_configs[g_mode];

// Priority: AWAY > PLAYING_PHONE > GLANCING_PHONE > DROWSY > milestone > FOCUSED
if (away_ms >= cfg.away_sec * 1000) {
    final_status = AWAY;
} else if (phone_ms >= cfg.phone_playing_sec * 1000 && has_hand_motion) {
    final_status = PLAYING_PHONE;
} else if (phone_ms >= cfg.phone_glance_sec * 1000) {
    final_status = GLANCING_PHONE;
} else if (drowsy_ms >= cfg.drowsy_sec * 1000) {
    final_status = DROWSY;
} else {
    final_status = FOCUSED;
}
```

Wait — the priority says "玩手机 > 看手机 > 瞌睡". So PLAYING_PHONE (with hand motion) before GLANCING_PHONE (no/less hand motion), then DROWSY. Let me refine:

- AWAY: person not present for away_sec
- PLAYING_PHONE: phone in hand for phone_playing_sec AND hand_motion high
- GLANCING_PHONE: phone detected for phone_glance_sec (but not playing)
- DROWSY: head_pitch > threshold for drowsy_sec
- FOCUSED otherwise

Actually looking at the 产品方案 pseudocode more carefully:

```c
if (away) return AWAY;
if (latest phone && near_hand) {
    phone_duration = ...;
    has_hand_motion = avg_motion > 0.3;
    if (phone_duration > threshold && has_hand_motion) return PLAYING_PHONE;
    else if (phone_duration <= threshold) return GLANCING_PHONE;
}
if (drowsy) return DROWSY;
if (milestone) return FOCUSED + ENCOURAGE;
return FOCUSED;
```

So:
- PLAYING_PHONE requires hand motion > 0.3.
- GLANCING_PHONE = phone detected but duration not yet over threshold (or no hand motion).
- DROWSY = head_pitch over threshold for duration.

Let me define thresholds clearly:
- phone playing threshold (严格8s / 鼓励15s): this is `phone_playing_sec`.
- Actually 产品方案 has both `phone_glance_sec` and `phone_playing_sec`, but in STRICT both are 8, in GENTLE both are 15. So they're the same value in both modes in the example config. I'll keep both config fields but they happen to be equal.

For the "has_hand_motion" I need average hand motion over the window. I'll compute average hand_motion_score over the phone streak (or over a recent window).

Let me define:
- `has_hand_motion = (avg hand_motion_score over phone streak) > 0.3`

Then:
- if phone_streak duration >= playing_sec && has_hand_motion → PLAYING_PHONE (REMIND)
- else if phone_streak > 0 (or duration >= glance_sec) → GLANCING_PHONE (NONE)

Hmm, but "看手机" (GLANCING) is when phone detected but they haven't been playing long enough / not actively. The doc priority "玩手机 > 看手机" — glancing is a milder state.

Let me simplify to a clean, correct rule:
- phone present (phone_detected && near_hand) streak:
  - if duration >= playing_sec && has_hand_motion → PLAYING_PHONE (distraction, REMIND)
  - else → GLANCING_PHONE (mild, NONE action, no score penalty)

Actually, I realize I should also consider: does GLANCING_PHONE trigger a remind? No — "看手机" is a mild warning state, action NONE. Only PLAYING_PHONE/AWAY/DROWSY trigger REMIND.

Now, cooldown & accumulated reminders:

From DEVELOPMENT_TASKS:
- 提醒冷却 `remind_cooldown_sec`
- 累计提醒 (gentle: remind_after_n_times=3, accumulate 3 distractions then remind once)
- 里程碑去重 (dedup milestone)

The remind logic:
- STRICT: remind_after_n_times=1 (every distraction reminds), cooldown 30s.
- GENTLE: remind_after_n_times=3 (3 distractions → 1 remind), cooldown 120s.

So when a REMIND-worthy state (PLAYING_PHONE/AWAY/DROWSY) is detected:
1. Increment g_distract_count.
2. If g_distract_count >= remind_after_n_times AND (now - last_remind >= cooldown) → emit REMIND, reset g_distract_count, update last_remind.
3. Else → suppress (action NONE but status still set?).

Hmm, this is getting complex. Let me think about what's clean and matches the intent.

Actually the accumulate-3-times is about "累计分心 3 次才提醒 1 次" (accumulate 3 distraction events then remind once). And cooldown prevents spamming. 

Let me design:
- A "distraction event" = a transition into a REMIND-worthy status (or a sustained REMIND-worthy status). 
- g_distract_count counts distraction events since last reminder.
- When distraction detected:
  - g_distract_count++
  - if g_distract_count >= cfg.remind_after_n_times and cooldown elapsed → REMIND + reset counter + set last_remind
  - else → action = NONE (still report status, but no remind this time)

But the score penalty (focus_score_delta) — should it apply every time status is REMIND-worthy, or only when actually reminding? I think the score penalty applies when the distraction is detected (each time), while the remind action is gated by cooldown/accumulation. Actually, let me keep it simple and tie score_delta to the status detection, and action (REMIND) gated.

Actually, re-reading: `focus_score_delta` is the "评分变化量" (score change). The state machine accumulates focus score. Each distraction reduces score. But if we only penalize when reminding, gentle mode would almost never penalize. I think score penalty applies on each distraction detection (or each transition). To keep it simple and testable, I'll apply score_delta whenever the status is a distraction (PLAYING_PHONE/AWAY/DROWSY) AND the remind is actually fired. Hmm.

Let me look at what the doc says precisely about the state machine consuming study_state:
```c
if (s->action == ACTION_REMIND) { play_reminder(s->message); }
```
And focus score — the state machine probably accumulates `focus_score_delta` each time. 

I think the cleanest design that matches "扣分重/扣分轻" is:
- Each time behavior_analyze detects a distraction STATUS (regardless of remind gating), set focus_score_delta to the penalty.
- The REMIND action is gated by cooldown + accumulation.

But then score would be applied every frame (5s), which over-penalizes. The real fix: score should only apply on TRANSITION into distraction, not sustained. This is the "同帧防重 (g_last_state 缓存)" mentioned in the docs! "同帧防重" = same-frame dedup, meaning only act on status CHANGE, not every frame.

So the design:
- g_last_status caches the previous status.
- On status transition (new status != last status), do the "event" handling (score penalty, distraction count).
- On sustained same status, don't re-penalize (but may still need to remind?).

Hmm wait, "同帧防重" literally means "same frame dedup" — prevent duplicate handling within the same frame. Given behavior_analyze is called once per frame, and it might internally loop... Actually "同帧防重" more likely means: if the status is the same as last time, don't re-trigger reminder.

Let me design it cleanly:

```
behavior_analyze_history(history, count, out):
    compute status, and whether it's a "distraction" (PLAYING_PHONE/AWAY/DROWSY)
    
    # milestone (gentle only, for FOCUSED)
    if status == FOCUSED:
        focus_streak_min = compute consecutive focused minutes
        if gentle && focus_streak_min >= milestone_min && focus_streak_min % milestone_min == 0 && not celebrated:
            action = ENCOURAGE, milestone...
    
    # distraction handling
    if status in {PLAYING_PHONE, AWAY, DROWSY}:
        # transition detection for score + counter
        if status != g_last_status:   # new distraction (or changed type)
            g_distract_count++
            score_delta = penalty(status)
        # remind gating
        now = latest ts
        if g_distract_count >= remind_after_n_times and (now - g_last_remind >= cooldown*1000):
            action = REMIND
            message = cfg.messages[status]
            g_last_remind = now
            g_distract_count = 0
        else:
            action = NONE
    else:
        # FOCUSED or GLANCING: reset distraction counter? 
        ...
    
    g_last_status = status
```

Hmm, there's a subtlety: should g_distract_count reset when the person returns to focus? Probably yes — "累计分心 3 次" means 3 separate distraction episodes. If they go back to focus between episodes, that's a new episode. So on transition to FOCUSED (or non-distraction), we could reset g_distract_count... but actually the "accumulate 3 times then remind once" pattern in gentle mode: they accumulate 3 distraction events (even separated by focus?) then remind. The doc isn't precise.

I'll go with a clean, defensible interpretation and document it clearly:

**Remind policy**:
- A "distraction episode" begins when status transitions from a non-distraction to a distraction (or between distraction types? I'll say between different distraction types counts as a new episode too, but let me keep it simpler: only count new episodes on transition INTO a distraction from FOCUSED/GLANCING).
- Actually, let me simplify further and match "累计提醒" literally:

Let me re-read: "提醒冷却 remind_cooldown_sec, 累计提醒, 里程碑去重". And 产品方案: "提醒频率: 每次分心都提醒（间隔 30s）" (strict) vs "低频（间隔 120s），累计分心 3 次才提醒 1 次" (gentle).

So:
- STRICT: every distraction reminds, but min 30s between reminders (cooldown). remind_after_n_times=1.
- GENTLE: every 3rd distraction reminds, min 120s between reminders. remind_after_n_times=3.

So g_distract_count increments on each distraction EPISODE (transition into distraction), and a remind fires when count reaches n_times AND cooldown elapsed. This matches. On remind, reset count to 0. Cooldown prevents two reminds too close.

I think incrementing on transition into a distraction status (including from one distraction type to another, e.g., AWAY→PLAYING_PHONE) is reasonable. But to keep it clean and avoid over-counting, I'll increment only when transitioning from a NON-distraction status (FOCUSED/GLANCING_PHONE) into a distraction status. Transitions between distraction types (e.g. AWAY → DROWSY) won't double-count.

Wait, but actually there's a subtlety: "同帧防重" might specifically be about the fact that behavior_analyze could be called multiple times with the same history (same frame), and should not double-count. Given the frame is identified by its latest timestamp, I can dedup on timestamp: if the latest timestamp == last processed timestamp, skip event handling (return cached state). That's the literal "同帧防重".

Hmm, let me reconsider "同帧防重 (`g_last_state` 缓存)". It says `g_last_state` caches. "同帧" = same frame. So: if the same frame (same latest timestamp) is analyzed again, return the cached `g_last_state` without re-processing. This prevents double-counting reminders/score when behavior_analyze is called twice for the same frame.

But there's also the "transition detection" aspect. Let me combine:
- `g_last_status` = status from previous analysis.
- `g_last_ts` = latest timestamp from previous analysis.
- If latest ts == g_last_ts → same frame, return cached state (dedup).
- Else process; on status change, handle events.

I'll implement `g_last_state` as a `study_state_t` cache, and `g_last_ts`. This satisfies "同帧防重 (g_last_state 缓存)".

OK, this is a lot. Let me also handle the milestone (鼓励模式):
- "每专注 30 分钟鼓励一次", "连续专注 30 分钟 +5", "专注里程碑去重".
- So compute continuous focus duration (consecutive FOCUSED streak). When it crosses a multiple of 30 minutes, emit ENCOURAGE with milestone_minutes = 30, 60, 90... And dedup so each milestone fires once.

Focus streak calculation: count consecutive FOCUSED frames at the tail, convert to minutes. But "连续专注" means no distraction in between. With 5s frames, 30 min = 360 frames, but history only keeps 60 frames (300s = 5 min). So the milestone must be tracked ACROSS calls, not just within the 60-frame history window!

This is important. The history window is 60 frames × 5s = 300s = 5 minutes, but milestone is 30 minutes. So the behavior module must maintain a running "focus streak" counter that accumulates across behavior_analyze calls, using the timestamps to know elapsed time.

So the behavior module needs its own persistent state: `g_focus_start_ms` (timestamp when current focus streak started). When status == FOCUSED, if g_focus_start_ms == 0, set it to latest ts. When status != FOCUSED, reset g_focus_start_ms = 0.

Then focus_streak_min = (latest_ts - g_focus_start_ms) / 60000. When focus_streak_min >= milestone_min and focus_streak_min % milestone_min == 0 and focus_streak_min > g_last_milestone_min → ENCOURAGE + milestone. Set g_last_milestone_min = focus_streak_min.

This matches "专注里程碑去重" (milestone dedup).

This is why the behavior module has persistent state and is NOT a pure function. But `behavior_analyze_history()` for testing should still be testable — I'll separate:
- `behavior_analyze()`: uses internal state + perception_get_history, returns study_state_t.
- For testing, the internal state functions can be tested by feeding sequences.

Actually, to make unit tests clean, I'll keep the state in the module and have tests drive it through `behavior_init` + `behavior_analyze_history` (which updates state). I'll expose `behavior_analyze_history` as internal (declared in behavior_internal.h, not public API) for testing.

Let me reconsider the timestamp source. The observation_t has timestamp_ms (uint32, monotonic ms). For the milestone, I use latest observation's timestamp. Good.

Now let me also reconsider: for "同帧防重", I compare latest timestamp. But in tests with synthetic histories, timestamps are controlled. Good.

Now, let me also handle the case where `perception_get_history` is not available in the test build. In tests, I'll test `behavior_analyze_history` directly (which is internal), and `behavior_init`. I won't test `behavior_analyze` (which calls perception_get_history) unless I provide a stub. Actually I can provide a weak stub or just not call behavior_analyze in tests.

Hmm, but `behavior_analyze` calls `perception_get_history`. In the test build, I can link against a test-provided stub, OR I can structure `behavior_analyze` to call `perception_get_history` which the test provides via a stub file (like wifi_http_post_stub.c pattern). But simpler: tests only test `behavior_analyze_history` + `behavior_init`, and I provide a small stub for `perception_get_history` just to allow behavior.c to link (or use weak symbol). 

Actually, looking at how perception.c handles the mock/real split: it uses `#ifdef PERCEPTION_MOCK`. For behavior, there's no mock needed — it's pure logic. But `behavior_analyze` references `perception_get_history`, which is in api/perception.h (declared). I need the declaration available. In behavior.c I'll `#include "../api/perception.h"`.

For linking tests: I'll have the test provide a stub `perception_get_history` returning 0 (empty), OR make `behavior_analyze` only called in integration. Simplest: tests use `behavior_analyze_history` (internal, no perception dependency) + a stub for `perception_get_history` to satisfy the linker.

Actually, cleanest: declare `perception_get_history` with a weak attribute in the test, or provide it in the test file. I'll provide it in the test file as a simple stub that returns 0. That way behavior.c links fine.

Let me now write the code. Structure (mirroring focus_perception):

```
focus_behavior/
├── api/behavior.h             公开接口 (study_state_t + status_t + action_t + mode_t + 函数)
├── behavior/behavior.c         主实现 (时序引擎 + 配置 + 冷却 + 里程碑)
├── behavior/behavior_internal.h 内部声明 (工具 + 可测函数)
├── behavior/behavior_config.c   配置表 (g_mode_configs + messages)
├── tests/test_behavior.c        mock 单测 (不依赖硬件/网络/cJSON/perception)
├── BUILD_INTEGRATION.md         Makefile/CMakeLists/Kconfig 接入 diff
└── README.md
```

Wait, the DEVELOPMENT_TASKS mentions `behavior/behavior_config.c` separately (task 1: 迁移配置表). So I'll split config into its own file to match. That's consistent with "Task 1: 迁移配置表 behavior/behavior_config.c".

Let me define the config in behavior_config.c:
```c
// behavior/behavior_config.c
#include "../api/behavior.h"
#include "behavior_internal.h"

const char *strict_messages[] = { ... };
const char *gentle_messages[] = { ... };

const mode_config_t g_mode_configs[MODE_MAX] = {
    [MODE_STRICT] = { ... },
    [MODE_GENTLE] = { ... },
};
```

And behavior_internal.h declares `extern const mode_config_t g_mode_configs[];` and the messages.

Now let me define `mode_config_t`:
```c
typedef struct {
    int   phone_glance_sec;
    int   phone_playing_sec;
    int   away_sec;
    int   drowsy_sec;
    int   remind_cooldown_sec;
    int   remind_after_n_times;
    int   focus_milestone_min;
    int   score_penalty_phone;
    int   score_penalty_away;
    int   score_penalty_drowsy;
    int   score_bonus_milestone;
    bool  enable_milestone;
    const char *const *messages;   // messages indexed by status
} mode_config_t;
```

Now status_t enum order matters for message indexing. The 产品方案 defines:
```c
typedef enum { FOCUSED, GLANCING_PHONE, PLAYING_PHONE, AWAY, DROWSY } status_t;
```
And messages arrays indexed by status:
```c
const char* strict_messages[] = {
    [PLAYING_PHONE] = "请放下手机!",
    [AWAY]          = "请回到座位!",
    [DROWSY]        = "请注意坐姿!",
};
```
So messages is a sparse array indexed by status_t (0..4). I need messages array of size 5 (STATUS_COUNT). For FOCUSED and GLANCING_PHONE, messages are NULL (no remind). I'll define the array with designated initializers and size STATUS_COUNT.

Let me use explicit enum values and a count:
```c
typedef enum {
    STATUS_FOCUSED = 0,
    STATUS_GLANCING_PHONE,
    STATUS_PLAYING_PHONE,
    STATUS_AWAY,
    STATUS_DROWSY,
    STATUS_COUNT
} status_t;
```

Wait, but the 产品方案 uses bare `FOCUSED`, `PLAYING_PHONE`, etc. The frozen api/behavior.h (which I don't have) might use bare names. Since this is a "参考拷贝", I should match the doc's naming as closely as possible to avoid confusion, but bare `FOCUSED`, `AWAY`, `NONE`, `REMIND` are VERY likely to collide with other macros/enums in the big repo (e.g., `NONE`, `AWAY` are generic). 

Hmm. The doc explicitly writes `typedef enum { FOCUSED, GLANCING_PHONE, PLAYING_PHONE, AWAY, DROWSY } status_t;` and `typedef enum { NONE, REMIND, ENCOURAGE } action_t;`. These bare names are what the frozen header uses. But `NONE` is a very common macro. In the real repo, they must have it in api/behavior.h and it's fine because it's scoped... actually C enums are NOT scoped, so `NONE` would collide. But the doc shows it, so the frozen header presumably uses these names (maybe the repo just doesn't have a NONE macro conflict).

Since I'm writing a "参考拷贝" (reference copy), I'll follow the doc's names but be a bit safer. Actually, to match the existing perception.h style (which uses `FOCUS_OK`, `FOCUS_ERR_*` prefixed names to avoid collision), and since `NONE`/`AWAY`/`FOCUSED` are risky, I could prefix. But the doc's contract is explicit.

Let me check: does the existing perception.h use bare or prefixed? It uses `FOCUS_OK`, `FOCUS_ERR_PERCEP_TIMEOUT` — prefixed. So the convention is prefixing to avoid collisions. But the behavior contract in 产品方案 shows bare `FOCUSED`, `AWAY`, etc.

Given this is a "参考拷贝" and the real frozen api/behavior.h exists elsewhere (with whatever names), I should note the same warning as perception.h: "此文件是参考拷贝, 以仓库冻结版为准". For safety and consistency with the FOCUS prefix convention, I could use prefixed names, but that risks mismatch with the frozen header.

I'll go with the doc's bare names (FOCUSED, AWAY, DROWSY, PLAYING_PHONE, GLANCING_PHONE, NONE, REMIND, ENCOURAGE, MODE_STRICT, MODE_GENTLE) since those are what the contract specifies, and add the ⚠️ reference-copy note. This matches 产品方案 exactly. The `NONE` collision is a real repo concern but not mine to solve here — and actually in a controlled header it's often fine.

Hmm, wait. Let me reconsider. `mode_t` — the doc uses `mode_t mode` in function signatures. `mode_t` is also a POSIX type (from sys/types.h, used for file modes). That could collide with `#include <sys/types.h>`! But on ESP32 openvela embedded, maybe not included. Still risky.

The doc explicitly writes `mode_t mode` in `analyze_behavior(observation_t *history, int count, mode_t mode)`. And DEVELOPMENT_TASKS says `behavior_init(MODE_STRICT)`. So the frozen header has `mode_t` and `MODE_STRICT`/`MODE_GENTLE`.

I'll follow the doc but I'm a bit worried about `mode_t`. Given the "参考拷贝" note, I'll use `mode_t` as documented. Actually, to reduce risk while staying faithful, I'll name it `mode_t` exactly as the doc says (since that's the contract). If there's a POSIX collision, the real repo already dealt with it. Actually, let me reconsider — the safest for a "参考拷贝" that must compile standalone is to match the doc names. `mode_t` from sys/types.h is only a problem if someone includes sys/types.h before behavior.h. In the tests I won't include sys/types.h. I'll go with `mode_t`.

Actually, I realize I'm overthinking the naming. Let me just follow the doc faithfully. The doc is the contract. I'll use:
- `status_t` enum: `FOCUSED, GLANCING_PHONE, PLAYING_PHONE, AWAY, DROWSY`
- `action_t` enum: `NONE, REMIND, ENCOURAGE`
- `mode_t` enum: `MODE_STRICT, MODE_GENTLE`
- `study_state_t` struct
- `mode_config_t` struct
- functions: `behavior_init(mode_t mode)`, `behavior_analyze(study_state_t *out)`

Wait, what's the exact return type/signature of behavior_analyze? DEVELOPMENT_TASKS says "behavior_analyze() 从 perception_get_history() 做时序判定" and "主入口已调用 behavior_init(MODE_STRICT)". The 产品方案 pseudocode returns `study_state_t` by value: `study_state_t analyze_behavior(...)`. 

I'll use:
```c
int behavior_init(mode_t mode);                    // returns FOCUS_OK
int behavior_analyze(study_state_t *out);          // returns FOCUS_OK / error
```
with internal `int behavior_analyze_history(const observation_t *history, int count, study_state_t *out);` for testing.

Return codes: use FOCUS_OK (0) and FOCUS_ERR_PERCEP_PARAM style. But behavior module might have its own error codes. I'll define `FOCUS_ERR_BEHAVIOR_PARAM` etc. via #ifndef guards, or just reuse FOCUS_OK and a generic error. Let me add a behavior-specific error code:
```c
#ifndef FOCUS_ERR_BEHAVIOR_PARAM
#define FOCUS_ERR_BEHAVIOR_PARAM (-40)
#endif
```
And reference api/error.h as the source of truth.

Actually, to keep parity with perception.h which defines FOCUS_ERR_PERCEP_* with #ifndef guards, I'll do similar for behavior: FOCUS_ERR_BEHAVIOR_PARAM.

Now let me also think about `perception_get_history` declaration. behavior.c needs it. It's declared in api/perception.h. So behavior.c includes "../api/perception.h". For the test build, I'll provide a stub in the test file.

Now let me carefully write the temporal algorithm with all pieces.

Let me define internal state in behavior.c:
```c
static mode_t       g_mode = MODE_STRICT;
static study_state_t g_last_state;      // 同帧防重缓存
static uint32_t      g_last_frame_ts = 0;  // 上次分析的最新帧时间戳
static uint32_t      g_last_remind_ms = 0; // 上次提醒时间戳
static int           g_distract_count = 0; // 累计分心次数(自上次提醒)
static uint32_t      g_focus_start_ms = 0; // 当前专注段起点(0=不在专注)
static int           g_last_milestone_min = 0; // 已庆祝的最近里程碑(去重)
```

Constants:
```c
#define HISTORY_MAX              60
#define DEFAULT_FRAME_INTERVAL_MS 5000
#define HAND_MOTION_PLAY_THRESH  0.30f
#define DROWSY_PITCH_STRICT      45.0f
#define DROWSY_PITCH_GENTLE      52.0f
```

Wait, drowsy pitch threshold: 产品方案 pseudocode: `if (latest->head_pitch > (mode == STRICT ? 45 : 52))`. So drowsy if head_pitch > 45 (strict) or > 52 (gentle). But the perception mock DROWSY sets head_pitch = 55.0f. So 55 > 45 and 55 > 52, both trigger. Good.

Actually wait, head_pitch: negative = looking down (低头), positive = 仰头 (looking up). Drowsy = head drooping... but the mock sets DROWSY with head_pitch = +55 (仰头?). Hmm, that seems odd for "瞌睡" (drowsy = head nodding down). But the doc explicitly says `head_pitch > 45/52` for drowsy, and mock DROWSY uses 55. So I'll follow: drowsy when head_pitch > threshold. It's their model's convention; not my place to change.

Let me define the predicate functions:
```c
static bool obs_is_away(const observation_t *o) {
    return !o->person_present;
}
static bool obs_is_phone(const observation_t *o) {
    return o->phone_detected && o->phone_near_hand;
}
static bool obs_is_drowsy(const observation_t *o, float pitch_thresh) {
    return o->person_present && (o->head_pitch > pitch_thresh);
}
static bool obs_is_focused(const observation_t *o) {
    // focused = person present, no phone in hand, head not drowsy
    return o->person_present && !o->phone_near_hand && !o->phone_detected
           && (o->head_pitch <= DROWSY_PITCH_...); // hmm needs threshold
}
```

Wait, "focused" definition is important for milestone (连续专注). What counts as focused? Person present, not playing phone, not away, not drowsy. Glancing phone briefly is still mostly focused? For milestone "连续专注 30 分钟", any distraction (even glancing) breaks the streak. Let me define focused as: person_present && !phone_near_hand && head_pitch <= drowsy_threshold. (phone_detected but not near hand is fine — phone is on desk, person is working.)

Actually, "看手机" (glancing) means phone detected && near_hand but short duration. That's still a mild distraction. For milestone, I'll say focused = person present, not away, not (phone near hand), not drowsy. So phone_near_hand breaks focus streak. phone_detected alone (phone visible on desk) doesn't break.

Let me define focused predicate with the drowsy threshold (mode-dependent):
```c
static bool obs_is_focused(const observation_t *o, float drowsy_pitch) {
    return o->person_present
        && !o->phone_near_hand
        && !(o->head_pitch > drowsy_pitch);
}
```

Hmm, but "phone_detected && near_hand" is playing/glancing. "phone_detected && !near_hand" = phone on desk, still focused. So focused = person && !phone_near_hand && not drowsy. That's what I have.

Now the algorithm:

```c
int behavior_analyze_history(const observation_t *history, int count, study_state_t *out) {
    if (!out || !history || count <= 0) {
        return FOCUS_ERR_BEHAVIOR_PARAM;
    }

    const mode_config_t *cfg = &g_mode_configs[g_mode];
    const observation_t *latest = &history[count - 1];
    float drowsy_pitch = (g_mode == MODE_STRICT) ? DROWSY_PITCH_STRICT : DROWSY_PITCH_GENTLE;

    // 同帧防重: 相同最新帧时间戳 → 直接返回缓存
    if (latest->timestamp_ms == g_last_frame_ts && g_last_frame_ts != 0) {
        *out = g_last_state;
        return FOCUS_OK;
    }
    g_last_frame_ts = latest->timestamp_ms;

    uint32_t frame_interval = estimate_frame_interval_ms(history, count);

    // 连续时长统计(从最新帧往前数)
    int away_streak   = streak_from_tail(history, count, &obs_is_away);
    int phone_streak  = streak_from_tail(history, count, &obs_is_phone);
    int drowsy_streak = streak_from_tail_pitch(history, count, drowsy_pitch);

    uint32_t away_ms   = streak_duration_ms(history, count, away_streak, frame_interval);
    uint32_t phone_ms  = streak_duration_ms(history, count, phone_streak, frame_interval);
    uint32_t drowsy_ms = streak_duration_ms(history, count, drowsy_streak, frame_interval);

    // 手部运动(玩手机需要)
    float avg_motion = average_tail(history, count, phone_streak, &hand_motion_of);
    bool has_hand_motion = avg_motion > HAND_MOTION_PLAY_THRESH;

    // 状态判定(优先级: AWAY > 玩手机 > 看手机 > 瞌睡 > 里程碑 > FOCUSED)
    status_t status;
    if (away_ms >= (uint32_t)cfg->away_sec * 1000u) {
        status = AWAY;
    } else if (phone_ms >= (uint32_t)cfg->phone_playing_sec * 1000u && has_hand_motion) {
        status = PLAYING_PHONE;
    } else if (phone_ms > 0) {   // 手机在手但未到玩手机阈值
        status = GLANCING_PHONE;
    } else if (drowsy_ms >= (uint32_t)cfg->drowsy_sec * 1000u) {
        status = DROWSY;
    } else {
        status = FOCUSED;
    }
    ...
}
```

Wait, there's an issue with the predicate function pointers and the pitch threshold. `streak_from_tail` with a pitch parameter is awkward with a single bool(*)(const observation_t*) signature. Let me use different approach: pass threshold via a small struct or use a generic "match" with a context. Simpler: write three separate small loops, or pass a function pointer + an extra void* / threshold.

Cleaner: I'll write a generic helper that takes a predicate function pointer with an extra float parameter:
```c
typedef bool (*obs_pred_t)(const observation_t *o, float arg);
static int streak_from_tail(const observation_t *h, int n, obs_pred_t pred, float arg) {
    int s = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (pred(&h[i], arg)) s++;
        else break;
    }
    return s;
}
```
And predicates all take (o, arg) and ignore arg where not needed. This is clean enough.

```c
static bool pred_away(const observation_t *o, float arg) {
    (void)arg; return !o->person_present;
}
static bool pred_phone(const observation_t *o, float arg) {
    (void)arg; return o->phone_detected && o->phone_near_hand;
}
static bool pred_drowsy(const observation_t *o, float arg) {
    return o->person_present && (o->head_pitch > arg);
}
```

For hand motion average over the phone streak tail:
```c
static float average_hand_motion(const observation_t *h, int n, int streak) {
    if (streak <= 0) return 0.0f;
    int start = n - streak;
    float sum = 0.0f;
    for (int i = start; i < n; i++) sum += h[i].hand_motion_score;
    return sum / (float)streak;
}
```

streak_duration_ms:
```c
static uint32_t streak_duration_ms(const observation_t *h, int n, int streak, uint32_t interval_ms) {
    if (streak <= 0) return 0;
    if (streak == 1) return interval_ms;
    int32_t span = (int32_t)(h[n-1].timestamp_ms - h[n-streak].timestamp_ms);
    if (span <= 0) span = (int32_t)(streak - 1) * (int32_t)interval_ms;  // 回绕或异常, 回退按帧数估
    return (uint32_t)span + interval_ms;
}
```

Wait, `h[n-1].timestamp_ms - h[n-streak].timestamp_ms` where timestamp_ms is uint32 → done in unsigned, then cast to int32_t. Actually `h[n-1].timestamp_ms - h[n-streak].timestamp_ms` as uint32 arithmetic gives the correct modular difference, and casting to int32_t interprets it as signed, handling wrap correctly. Good. But if span computes to something weird (e.g., negative due to non-monotonic), fall back.

estimate_frame_interval_ms:
```c
static uint32_t estimate_frame_interval_ms(const observation_t *h, int n) {
    if (n < 2) return DEFAULT_FRAME_INTERVAL_MS;
    int32_t d = (int32_t)(h[n-1].timestamp_ms - h[n-2].timestamp_ms);
    if (d <= 0 || d > 60000) return DEFAULT_FRAME_INTERVAL_MS;
    return (uint32_t)d;
}
```

Now the event handling (remind gating, score, milestone):

```c
    study_state_t st;
    memset(&st, 0, sizeof(st));
    st.status = status;
    st.action = NONE;

    bool is_distraction = (status == PLAYING_PHONE || status == AWAY || status == DROWSY);

    if (status == FOCUSED) {
        // 专注段维护(里程碑用)
        if (g_focus_start_ms == 0) {
            g_focus_start_ms = latest->timestamp_ms;  // 开始计时
        }
        uint32_t focus_ms;
        {
            int32_t d = (int32_t)(latest->timestamp_ms - g_focus_start_ms);
            focus_ms = (d > 0) ? (uint32_t)d : 0;
        }
        int focus_min = (int)(focus_ms / 60000u);
        if (cfg->enable_milestone && cfg->focus_milestone_min > 0
            && focus_min >= cfg->focus_milestone_min
            && focus_min % cfg->focus_milestone_min == 0
            && focus_min > g_last_milestone_min) {
            st.action = ENCOURAGE;
            st.milestone_reached = true;
            st.milestone_minutes = focus_min;
            st.focus_score_delta = (uint8_t)cfg->score_bonus_milestone;
            snprintf(st.message, sizeof(st.message),
                     "已专注学习 %d 分钟,继续保持!", focus_min);
            g_last_milestone_min = focus_min;
        }
    } else {
        // 非专注 → 清空专注段
        g_focus_start_ms = 0;
    }

    if (is_distraction) {
        // 分心事件计数(状态转变才计数, 避免同状态重复)
        bool was_distraction = (g_last_state.status == PLAYING_PHONE
                                || g_last_state.status == AWAY
                                || g_last_state.status == DROWSY);
        if (g_last_state.status != status) {
            // 进入新的分心状态
            if (!was_distraction) {
                g_distract_count++;
            }
        }
        // 扣分(每帧? 仅状态转变?)
        if (g_last_state.status != status) {
            st.focus_score_delta = (uint8_t)penalty_for(cfg, status);
        }
        // 提醒门控
        uint32_t now = latest->timestamp_ms;
        int32_t since_last = (int32_t)(now - g_last_remind_ms);
        bool cooldown_ok = (g_last_remind_ms == 0) || (since_last >= (int32_t)((uint32_t)cfg->remind_cooldown_sec * 1000u));
        if (g_distract_count >= cfg->remind_after_n_times && cooldown_ok) {
            st.action = REMIND;
            const char *msg = cfg->messages[status];
            if (msg) snprintf(st.message, sizeof(st.message), "%s", msg);
            g_last_remind_ms = now;
            g_distract_count = 0;
        }
    } else {
        // FOCUSED 或 GLANCING_PHONE: 重置分心计数(回到专注后, 下次分心算新的一次)
        if (status == FOCUSED) {
            g_distract_count = 0;
        }
    }

    g_last_state = st;
    *out = st;
    return FOCUS_OK;
```

Hmm wait, there's an issue with `g_distract_count` reset. Let me reconsider the semantics of "累计分心 3 次才提醒 1 次".

The intent (gentle mode): don't nag. Accumulate 3 distraction episodes, then remind once. So g_distract_count increments each time a NEW distraction episode starts. When it reaches 3, remind and reset.

But "new distraction episode" — if the person is continuously playing phone for 5 minutes (many frames), that's ONE episode (count once), not counted every frame. So increment only on transition into distraction (from non-distraction).

For gentle: after 3 separate episodes, remind. But if they focus in between (return to FOCUSED), should the counter reset? The phrase "累计分心 3 次" suggests counting total distraction episodes (maybe within the session), not resetting on focus. But then "每次分心都提醒" (strict, n=1) and "累计 3 次才提醒 1 次" (gentle) both use the same counter; resetting on remind is the key.

I think the cleanest interpretation:
- g_distract_count = number of distraction episodes since last remind.
- On a new distraction episode (transition from non-distraction → distraction): g_distract_count++.
- When g_distract_count reaches remind_after_n_times AND cooldown elapsed: remind + reset g_distract_count=0.
- Don't reset on return-to-focus (so gentle mode accumulates across episodes within the cooldown window).

But wait, if we don't reset on focus, and gentle mode has cooldown 120s, a user who does 3 brief distractions within 120s then gets 1 remind. That matches "低频". OK.

But there's a subtle issue: if the person plays phone continuously (one long episode), g_distract_count becomes 1 (on entry), then stays 1. For strict (n=1): remind fires immediately on entry (count=1 >= 1, cooldown ok first time). Then reset to 0. But the person is STILL playing phone. Next frame: status still PLAYING_PHONE, no transition (status unchanged), so count doesn't increment, no remind (cooldown 30s anyway). After 30s cooldown, still same status (no new transition), so count stays 0, no remind ever again until they exit and re-enter. 

Is that correct? For strict mode "每次分心都提醒（间隔 30s）" — "每次分心" = each distraction. A continuous 5-min phone session is ONE distraction, so one remind. That seems reasonable (don't spam every 5s). The 30s cooldown is for separate distractions close together. I think this is acceptable.

But actually, "每次分心都提醒（间隔 30s）" could mean: remind on distraction, and if still distracted 30s later, remind again. That's a "recurring reminder" model. Hmm. But the frozen behavior.c uses `remind_cooldown_sec` — cooldown between reminders. The most natural: after a remind, don't remind again for cooldown_sec even if still distracted. And a "distraction episode" = a transition.

Actually, let me reconsider. A simpler and very common model:
- When distraction status is present AND cooldown elapsed → fire remind, update last_remind.
- This means: continuous distraction → remind once, then every cooldown period remind again (recurring).

But that contradicts "累计 3 次才提醒 1 次" (gentle). Unless gentle's "3 times" means "after 3 cooldown periods" — no.

I think the "累计" counter is specifically: count distraction EPISODES (transitions), remind after N episodes. This is the doc's "累计分心 3 次才提醒 1 次".

Let me go with the episode-transition model but also handle the "still distracted after long time" via the cooldown as a minimum spacing. Actually, to avoid over-engineering, I'll go with:

**Final remind policy** (documented clearly):
1. A distraction *episode* = transition into PLAYING_PHONE/AWAY/DROWSY from a non-distraction status (FOCUSED or GLANCING_PHONE). Transitions between different distraction types (e.g. AWAY→DROWSY) are the SAME episode (no re-count).
2. On each new episode: `g_distract_count++`.
3. A REMIND fires when `g_distract_count >= remind_after_n_times` AND time since last remind ≥ cooldown.
4. On remind: reset `g_distract_count = 0`, set `g_last_remind_ms`.
5. Score penalty (`focus_score_delta`) applies once per new episode (on transition).

This is clean, testable, and matches both modes:
- STRICT: n=1 → every episode reminds (cooldown 30s spacing).
- GENTLE: n=3 → every 3rd episode reminds (cooldown 120s spacing).

I'm fairly confident this is a good design. Let me also reconsider whether "同帧防重" is correctly handled. g_last_frame_ts dedup prevents re-processing the same frame. And g_last_state caches the result. Good.

One more subtlety: when status is GLANCING_PHONE (phone in hand but not yet playing), is that a distraction episode? No — glancing is mild, not counted, no remind. But should GLANCING break the focus streak (milestone)? Phone_near_hand = true → my `obs_is_focused` returns false → yes, breaks focus streak. Good, that's consistent (glancing = not focused).

Wait, but then in my status determination, GLANCING_PHONE has phone_ms > 0. And the focus streak resets because phone_near_hand. But GLANCING_PHONE is not "is_distraction" so no penalty/remind. And g_focus_start_ms resets (since status != FOCUSED). Good.

Hmm, but actually there's a concern: is GLANCING_PHONE (phone detected but < 8s) really "not focused" for milestone? The person glanced at phone for 2 seconds — technically distracted. But milestone "连续专注 30 分钟" is strict. I'll treat glancing as breaking focus (conservative). But wait, this might make milestone nearly impossible (any glance resets 30min). That's the product's design choice though — "连续专注" = continuous focus. I'll keep it. Actually, let me reconsider: maybe glancing shouldn't break the streak, only actual distraction. But the doc says "连续专注" and defines FOCUSED as a distinct state. Glancing = not focused. I'll keep glancing breaking focus. It's a defensible choice and documented.

Actually, let me reconsider once more. This matters for the milestone test. Let me keep it simple and defensible: focused = person present && !phone_near_hand && !drowsy. Glancing (phone_near_hand) breaks focus. Document it.

Now, `penalty_for`:
```c
static int penalty_for(const mode_config_t *cfg, status_t s) {
    switch (s) {
    case PLAYING_PHONE: return cfg->score_penalty_phone;
    case AWAY:          return cfg->score_penalty_away;
    case DROWSY:        return cfg->score_penalty_drowsy;
    default:            return 0;
    }
}
```

Now, `focus_score_delta` is uint8_t but penalties are negative (e.g., -15, -10). uint8_t can't hold negative. The doc says `uint8_t focus_score_delta; // 评分变化量`. So the "delta" is magnitude, and the state machine interprets it as subtraction? Or it's signed?

产品方案:
```c
uint8_t   focus_score_delta;   // 评分变化量
...
st.focus_score_delta = strict_penalties[s];  // 重扣分  (-15)
st.focus_score_delta = +5;  // 正向加分
```

So focus_score_delta is uint8_t but assigned negative values (-15) and positive (+5). That's contradictory — uint8_t can't hold -15. This is a spec inconsistency. Since I'm writing the reference copy and want it to compile cleanly with -Werror, I have two options:
1. Make it `int8_t` or `int` to hold signed deltas.
2. Keep `uint8_t` and only store magnitude, with a separate sign via action type.

Given the doc shows negative AND positive values, the field should be signed. I'll use `int8_t focus_score_delta;` (holds -20..+5, fits in int8). But the doc says uint8_t. Hmm.

Actually, the frozen header (which I don't have) says uint8_t. But it also assigns negative values in the doc's example. This is likely a doc bug. For a clean reference copy, I'll use `int8_t` and add a comment noting the discrepancy (uint8_t in the frozen header can't represent negative penalties; using int8_t here so penalties/加分 can both be represented; verify against frozen header).

Wait, actually — let me reconsider. Maybe the intent is: focus_score_delta is always the MAGNITUDE, and the sign is implied by action (REMIND → subtract, ENCOURAGE → add). The state machine would do `score -= focus_score_delta` on REMIND and `score += focus_score_delta` on ENCOURAGE. That would let uint8_t work (penalties stored as 15, 10, 20 positive magnitudes).

But the doc explicitly writes `st.focus_score_delta = strict_penalties[s];` where strict_penalties = -15, -10, -20 (negative). And `st.focus_score_delta = +5` for milestone. So the doc treats it as signed.

I'll go with `int8_t` and clearly document. This is the pragmatic choice for a working reference copy. I'll add a note in the header comment.

Hmm, but actually if the frozen header has `uint8_t`, and I use `int8_t`, the field types won't match when they merge. The README says "字段/签名必须一致". But I don't have the frozen header. Since I literally can't know, I'll use `int8_t` (which is semantically correct for signed deltas) and put a prominent ⚠️ note to verify against the frozen header, exactly like perception.h does ("此文件是参考拷贝").

Actually, wait — let me reconsider whether to just follow the doc literally (`uint8_t`) and store magnitudes. The cleaner approach given the doc's own inconsistency: I'll follow the doc's LITERAL struct definition (`uint8_t focus_score_delta`) but note in comments that penalties are stored as magnitude and the state machine subtracts on REMIND / adds on ENCOURAGE. Then in the code I store `focus_score_delta = (uint8_t)(-cfg->score_penalty_phone)` → `(uint8_t)15` = 15. And milestone `= 5`. This makes uint8_t work.

Hmm, but that's confusing too. Let me think about what's LEAST likely to cause a mismatch and cleanest.

Decision: I'll use `int8_t focus_score_delta;` because:
1. It's semantically correct (can hold -20..+5).
2. The doc's example clearly assigns negative AND positive values.
3. uint8_t with negative assignment would produce a -Werror conversion warning (assigning -15 to uint8_t is a value-changing implicit conversion that gcc -Wall may not warn, but -Wsign-conversion would; with -Werror it could fail).

Actually `gcc -Wall -Wextra -Werror` — does assigning -15 to uint8_t warn? `int` -15 → uint8_t is an implicit conversion; -Wconversion (not in -Wall/-Wextra) catches it. So -Wall -Wextra wouldn't warn. But it's still semantically wrong (stores 241).

Given the ambiguity, `int8_t` is cleaner and I'll document. Final: `int8_t focus_score_delta`.

Hmm, wait, actually, let me reconsider using `int` or `int8_t`. The penalties are -20 to +5. int8_t range -128..127, fine. But the struct layout/packing on ESP32 — int8_t is fine. I'll use int8_t.

Now let me also reconsider the message field. The doc: `char message[128]`. Fine.

Now, let me also think about whether `behavior_analyze` should take `out` and return int, and how `behavior_init` signature looks. DEVELOPMENT_TASKS: "主入口已调用 behavior_init(MODE_STRICT)". So `behavior_init(mode_t mode)` returns int (FOCUS_OK).

For `behavior_analyze`, the frozen behavior.c has 401 lines and "behavior_analyze() 从 perception_get_history() 做时序判定". I'll do `int behavior_analyze(study_state_t *out)`.

Let me also add a convenience: `behavior_get_mode()`? Not needed. Keep minimal.

Now let me write everything. Let me also write the unit test covering the cases listed in DEVELOPMENT_TASKS:
- 空历史/严格手机+冷却/看手机/离座/瞌睡/鼓励阈值+累计/里程碑

Test cases (using behavior_analyze_history with synthetic histories):
1. Empty history → FOCUSED, NONE (or param error if count 0? Actually behavior_analyze with empty → FOCUSED). Let me decide: behavior_analyze_history with count==0 returns FOCUS_OK and sets FOCUSED/NONE? Or error? DEVELOPMENT_TASKS says test covers "空历史". I'll make count==0 → out = FOCUSED/NONE, return FOCUS_OK. But wait, I also validate `!history` → error. For count==0, history may be non-NULL but empty. I'll allow count==0 → FOCUSED/NONE.

Actually, let me make it: if out==NULL → error. if history==NULL && count>0 → error. if count<=0 → set FOCUSED/NONE and return OK.

Hmm, simpler: 
```c
if (!out) return FOCUS_ERR_BEHAVIOR_PARAM;
if (!history || count <= 0) {
    memset(out, 0, sizeof(*out));
    out->status = FOCUSED;  // 空历史 → 默认专注(无人信息视为正常, 不误报)
    out->action = NONE;
    return FOCUS_OK;
}
```
Wait but should empty history be FOCUSED or AWAY? If no data, we shouldn't falsely claim AWAY (which triggers remind). Defaulting to FOCUSED is safest. But actually, if the camera is off, empty history... The state machine is in MONITORING, so empty history = no observations yet = treat as focused/neutral. I'll default FOCUSED/NONE and document.

Let me now design the tests with a helper to build observations.

Helper to make an observation:
```c
static observation_t make_obs(uint32_t ts, bool person, bool phone, bool near_hand,
                              float pitch, float motion) {
    observation_t o;
    memset(&o, 0, sizeof(o));
    o.timestamp_ms = ts;
    o.person_present = person;
    o.phone_detected = phone;
    o.phone_near_hand = near_hand;
    o.head_pitch = pitch;
    o.hand_motion_score = motion;
    o.confidence = 0.9f;
    return o;
}
```

Test scenarios (frame interval 5000ms):
1. **空历史**: behavior_analyze_history(NULL, 0, &out) → FOCUSED, NONE. (or (obs, 0)).
2. **严格-离座**: strict mode, history = 3 frames AWAY (person=false), ts 0,5000,10000 → away_ms = (10000-0)+5000 = 15000 ≥ 10s → AWAY + REMIND (n=1, cooldown ok). 
   Wait let me compute: away_streak=3, span = 10000-0 = 10000, +5000 = 15000ms = 15s ≥ 10s → AWAY. Good. Remind: transition into AWAY (from initial FOCUSED), g_distract_count=1 >= 1 (strict n=1), cooldown ok → REMIND.
3. **严格-玩手机**: history with phone in hand + motion > 0.3 for enough frames.
4. **看手机(glancing)**: phone detected but short duration (1 frame) → GLANCING_PHONE, NONE.
5. **瞌睡**: head_pitch > 45 (strict) for enough frames → DROWSY + REMIND.
6. **冷却**: after one remind, immediately another distraction within cooldown → no REMIND (action NONE but status set). But this requires two separate episodes. Test: trigger AWAY (remind), then go FOCUSED, then AWAY again quickly (within 30s) → second AWAY: episode count = 1 (new episode from focus), 1 >= 1, but cooldown not elapsed (only e.g. 5s) → action NONE.
7. **鼓励-累计**: gentle mode, n=3. Three separate distraction episodes → remind only on 3rd. First two → status distraction but action NONE (count 1, 2 < 3). Third → REMIND.
8. **里程碑**: gentle mode, focus streak reaching 30 min. But this needs cross-call state (g_focus_start_ms). Test by feeding focused frames with timestamps 0..(30*60*1000). But history max 60 frames. To reach 30 min focus, I need the milestone state to accumulate across calls. So I'll feed focused observations in multiple behavior_analyze_history calls with increasing timestamps, e.g. each call advances 5 min (60 frames at 5s = 5 min). After 6 calls → 30 min → milestone. 

   Actually simpler: I can make the frame interval larger. If I feed 2 frames 30 min apart? frame_interval = 30min = 1800000ms > 60000 → estimate returns default 5000ms. That breaks. Hmm.

   Let me reconsider the milestone test. The milestone uses g_focus_start_ms (set on first FOCUSED) and latest timestamp. So to test: 
   - call 1: focused frame at ts=0 → g_focus_start_ms=0, focus_min=0.
   - call 2: focused frame at ts=30*60*1000 = 1,800,000. But this is a single frame (count=1), frame_interval default 5000. status: person present, no phone, pitch ok → FOCUSED. g_focus_start_ms already 0 (set in call 1). focus_ms = 1,800,000 - 0 = 1,800,000 → focus_min = 30. 30 >= 30, 30%30==0, 30 > g_last_milestone_min(0) → ENCOURAGE, milestone_minutes=30. 

   But wait, there's the same-frame dedup: g_last_frame_ts. Call 1 ts=0, call 2 ts=1,800,000 (different) → no dedup. Good. But I need to feed a valid history where the latest frame is ts=1,800,000 and it's FOCUSED. A single-frame history {ts=1.8M, focused} works. But then "continuous focus" — the module only knows it's been focusing since g_focus_start_ms=0 (from call 1). Since call 2 is FOCUSED and doesn't reset g_focus_start_ms, focus_ms accumulates. Good.

   Actually wait, in call 2, status=FOCUSED, g_focus_start_ms was set to 0 in call 1 (it's not reset). So focus_ms = 1.8M - 0 = 1.8M. 

   So the milestone test:
   - behavior_init(MODE_GENTLE).
   - feed one focused frame at ts=0 → FOCUSED, NONE (g_focus_start_ms=0).
   - feed one focused frame at ts=1,800,000 → FOCUSED, ENCOURAGE, milestone=30.
   - feed another focused frame at ts=1,800,000 + small → same frame? ts=1,805,000 → focus_min=30, 30%30==0 but 30 > g_last_milestone_min(30)? No, 30 not > 30 → no re-celebrate. Good (dedup).

   That works and tests milestone + dedup.

Let me also test the "同帧防重": feed same timestamp twice → second returns cached (e.g., doesn't double-count distraction). E.g., strict mode, feed AWAY frames at ts=0,5000,10000 (remind fires, count reset). Then feed same ts=10000 again → dedup → same result (no double remind). Hard to observe dedup via output alone since output is cached (identical). I can observe via a second effect... Actually dedup means g_distract_count isn't re-incremented. If I feed ts=10000 again, dedup returns cached state without incrementing. Then feed ts=15000 (still AWAY, same status, no new episode since status unchanged → no increment). Hmm, hard to distinguish. I'll just test that feeding the same frame returns the same result and doesn't crash / doesn't change g_last_frame_ts behavior. Maybe skip explicit dedup test or test it indirectly.

Actually, let me add a test where dedup matters: 
- strict, AWAY frames ts=0,5000,10000 → AWAY + REMIND (episode 1, count reset to 0).
- Re-feed SAME history (ts=0..10000, latest=10000) → dedup (g_last_frame_ts=10000) → returns cached (REMIND? no, cached state was the REMIND one). Hmm the cached state has action=REMIND. So re-feeding returns REMIND again. That's the point of dedup — it doesn't RE-process (no double count/remind), it returns the SAME cached result. So output identical. Can't easily assert "no double remind" via output.

I'll instead test the cooldown/accumulation which is more observable. Dedup I'll just note as covered implicitly. Actually, let me expose a way to observe internal state for testing... no, keep tests black-box via study_state_t output. I'll write meaningful black-box tests.

Let me also reconsider: for the strict "玩手机" test, I need has_hand_motion (avg motion > 0.3). Let me set motion=0.6 for phone frames.

Let me now write out the actual tests concretely with expected values, being careful about my algorithm's exact outputs.

Let me trace through my algorithm carefully for each test.

**Config constants** (from 产品方案):
STRICT: glance=8, playing=8, away=10, drowsy=8, cooldown=30, n=1, milestone=0, penalties phone=-15/away=-10/drowsy=-20, bonus=0, enable_milestone=false.
GENTLE: glance=15, playing=15, away=20, drowsy=12, cooldown=120, n=3, milestone=30, penalties phone=-5/away=-3/drowsy=-8, bonus=5, enable_milestone=true.

Drowsy pitch: strict 45, gentle 52.

Frame interval default 5000ms.

**Test 1: 空历史**
- behavior_init(MODE_STRICT)
- behavior_analyze_history(&dummy_obs, 0, &out) → count<=0 → FOCUSED, NONE. return FOCUS_OK.

**Test 2: 严格离座**
- history: 3 frames AWAY at ts 0, 5000, 10000.
- away_streak = 3 (all person=false).
- frame_interval = 5000.
- away_ms = streak_duration(3) = span (10000-0=10000) + 5000 = 15000 = 15s ≥ 10s → AWAY. ✓
- is_distraction. was_distraction: g_last_state.status initially FOCUSED (from init? I set g_last_state.status = FOCUSED at init, and g_last_frame_ts=0). So transition FOCUSED→AWAY, was_distraction=false → g_distract_count=1. 
- score_delta = -10 (away penalty). st.focus_score_delta = (int8_t)(-10).
- cooldown: g_last_remind_ms=0 → cooldown_ok=true. n=1, count=1>=1 → REMIND. message = "请回到座位!". g_last_remind_ms=10000. g_distract_count=0.
- Expected: status=AWAY, action=REMIND, focus_score_delta=-10, message="请回到座位!".

**Test 3: 严格玩手机**
- history: 3 frames phone (person=true, phone=true, near_hand=true, motion=0.6) at ts 0,5000,10000, pitch=0.
- phone_streak=3, phone_ms=15000 ≥ 8s. avg_motion=0.6 > 0.3 → has_hand_motion. → PLAYING_PHONE.
- Actually priority: away_ms=0 (person present). phone → PLAYING_PHONE.
- distraction, new episode, count=1>=1, cooldown ok → REMIND, message="请放下手机!", score_delta=-15.
- Expected: PLAYING_PHONE, REMIND, -15, "请放下手机!".

**Test 4: 看手机(glancing)**
- history: 1 frame phone (person, phone=true, near_hand=true, motion=0.2) at ts=0.
- phone_streak=1, phone_ms = streak_duration(1) = frame_interval=5000ms=5s < 8s (playing) and < 8s glance? Wait glance threshold = 8 (strict). phone_ms=5000 < 8000. So not playing. Then my logic: `else if (phone_ms > 0) → GLANCING_PHONE`.

Wait, let me re-examine my status logic. I wrote:
```c
if (away >= away_sec) AWAY
else if (phone_ms >= playing_sec && has_motion) PLAYING
else if (phone_ms > 0) GLANCING
else if (drowsy >= drowsy_sec) DROWSY
else FOCUSED
```

So glancing triggers whenever phone is in hand (phone_ms > 0) but not yet playing. For 1 frame phone → GLANCING_PHONE, action NONE (not distraction). ✓.

But what about the glance_sec threshold? The config has phone_glance_sec (8 strict / 15 gentle). In my logic I don't actually use glance_sec — I use "phone_ms > 0" for glancing. Should glancing require phone_ms >= glance_sec? The doc pseudocode: `else if (phone_duration <= threshold) return GLANCING_PHONE;` where threshold = playing threshold (8/15). So glancing = phone duration > 0 but <= threshold (or no hand motion). My "phone_ms > 0" is close enough (any phone-in-hand not yet playing = glancing). I'll drop the glance_sec distinction and just note glancing = phone in hand but not playing. Actually, to use the config field meaningfully and match the doc, I could do: glancing requires phone_ms > 0 (any), OR use glance_sec as the min duration to even call it glancing. 

Hmm, the doc has both glance_sec AND playing_sec as separate config fields, but in both modes they're equal (8/8 and 15/15). This suggests they were meant to differ but ended up equal. I'll keep both fields but use playing_sec for the PLAYING threshold and treat glance as "phone in hand, not yet playing" (phone_ms > 0). I'll keep glance_sec in the struct for fidelity to the frozen config but note it's currently equal to playing_sec and the code uses phone_ms>0 for glancing. Actually, to avoid an unused-field confusion, let me USE glance_sec: glancing = phone in hand AND phone_ms >= glance_sec*1000? No — that would make a 1-frame phone (5s) NOT glancing (since 5s < 8s), falling through to... FOCUSED. But the person IS looking at their phone. The doc's pseudocode returns GLANCING when `phone_duration <= threshold` (i.e., any non-zero up to threshold). So glancing covers 0 < duration <= threshold. So phone_ms > 0 → glancing. That's what I have. glance_sec isn't strictly needed in the decision (it's an upper bound that's implied by playing). I'll keep glance_sec in config for API fidelity and document it's informational (the playing threshold is the effective cutoff). 

Actually, cleaner: I'll just remove phone_glance_sec from my config to avoid confusion? No — the doc's mode_config_t explicitly lists phone_glance_sec. To match the frozen config table (task 1: 迁移配置表), I should keep all fields. I'll keep it and add a comment. It's fine if it's currently equal to playing_sec and effectively unused in the branch (I'll add a comment explaining). Or I'll reference it in a comment. Let me keep it and not force it into logic.

Hmm, actually, using -Wall -Wextra -Werror: an unused struct field is NOT a warning (struct fields aren't "unused variables"). So keeping phone_glance_sec in the struct is fine even if not read. But I should read it somewhere to be honest. I'll add it to a comment or actually use it: I'll make GLANCING require phone_ms > 0 (and implicitly < playing since playing checked first). Leave glance_sec documented.

Let me finalize and not over-think. Test 4: 1 frame phone, motion 0.2 → GLANCING_PHONE, NONE, score 0. ✓

**Test 5: 严格瞌睡**
- history: 3 frames drowsy (person=true, pitch=55) at ts 0,5000,10000. phone=false.
- away: person present → away_streak=0. phone_streak=0. drowsy_streak=3, drowsy_ms=15000 ≥ 8s → DROWSY.
- pitch threshold strict=45, 55>45 → drowsy. ✓
- distraction, new episode, count=1>=1, cooldown ok → REMIND "请注意坐姿!", score -20.
- Expected: DROWSY, REMIND, -20, "请注意坐姿!".

**Test 6: 冷却 (strict)**
- Setup: behavior_init(STRICT). 
- Episode 1: AWAY frames ts 0,5000,10000 → REMIND, last_remind=10000.
- Return to FOCUSED: feed 1 focused frame ts=15000. status FOCUSED, NONE. g_focus_start_ms=15000. (Also g_distract_count: my logic resets to 0 on FOCUSED? I wrote `if (status == FOCUSED) g_distract_count = 0;` — but count already 0 after remind. Fine.)
- Episode 2: AWAY frames again ts 20000,25000,30000. away_ms=15000 → AWAY. transition FOCUSED→AWAY (g_last_state.status was FOCUSED) → was_distraction=false → count=1. cooldown: now=30000, last_remind=10000, since=20000ms=20s < 30s → cooldown NOT ok → action NONE.
- Expected: status=AWAY, action=NONE, score_delta=-10 (still penalized on episode? I set score on transition regardless of remind). Hmm — should score penalty apply even when remind is suppressed by cooldown? 

Let me reconsider. My code sets `st.focus_score_delta` on transition (new episode) regardless of cooldown. So episode 2 → score -10, but action NONE (cooldown). Is that right? "扣分" (penalty) is about scoring the behavior, independent of reminding. I think yes, penalty applies per episode even if remind suppressed. But this is debatable. 

Actually, let me reconsider: if cooldown suppresses remind, should we still penalize? The person DID commit a distraction, so scoring it makes sense. I'll apply penalty on each new episode, remind gated separately. Test 6 expects: status=AWAY, action=NONE (cooldown), score_delta=-10.

Hmm, but actually there's subtlety: does a NEW episode even happen here? Between episode 1 (AWAY at ts 0-10000) and episode 2 (AWAY at ts 20000-30000), there was a FOCUSED frame at ts=15000. So status went AWAY → FOCUSED → AWAY. Episode 2 is a new episode (transition FOCUSED→AWAY). So yes, count increments to 1, penalty applied, but cooldown blocks remind. ✓.

Wait, but I need to double check my cooldown logic when last_remind_ms=0 (first ever). `cooldown_ok = (g_last_remind_ms == 0) || (since >= cooldown)`. First time g_last_remind_ms=0 → ok. Good.

**Test 7: 鼓励累计 (gentle, n=3)**
- behavior_init(GENTLE).
- Need 3 separate distraction episodes before remind.
- Episode 1: AWAY frames ts 0,5000,10000,15000,20000 (5 frames, away_ms = (20000-0)+5000=25000 ≥ 20s gentle → AWAY). transition FOCUSED→AWAY, count=1. n=3, 1<3 → action NONE. score -3 (gentle away penalty).
- Return FOCUSED: focused frame ts=25000.
- Episode 2: AWAY again ts 30000..50000. count=2, 2<3 → NONE, score -3.
- Return FOCUSED: ts=55000.
- Episode 3: AWAY ts 60000..80000. count=3 >=3, cooldown (last_remind=0) ok → REMIND "等你回来哦~", reset count=0. score -3.
- Expected on episode 3: AWAY, REMIND, -3, "等你回来哦~".

Let me make sure gentle away threshold: 20s. 5 frames at 5s = away_ms = (20000-0)+5000 = 25000ms = 25s ≥ 20s ✓.

Actually wait, for episode 1 I need the frames to be AWAY and reach 20s. 5 frames → 25s ✓. For episode 2 and 3 same.

But there's a subtlety with cooldown in gentle (120s). Episode 3's remind: last_remind_ms=0 (no remind yet) → ok. So remind fires. ✓.

**Test 8: 里程碑 (gentle)**
- behavior_init(GENTLE).
- focused frame ts=0 → FOCUSED, NONE. g_focus_start_ms=0.
- focused frame ts=1,800,000 (30 min) → FOCUSED, ENCOURAGE, milestone_minutes=30, score +5, message "已专注学习 30 分钟,继续保持!".
- focused frame ts=1,805,000 → FOCUSED, NONE (no re-celebrate; focus_min=30, 30 not > g_last_milestone_min=30).

Wait, at ts=1,805,000: focus_ms = 1,805,000 - 0 = 1,805,000 → focus_min = 30 (integer div 60000 = 30.08 → 30). 30%30==0, 30 > 30? No. → no celebrate. ✓.

But also need to check: at ts=1,800,000 single focused frame, frame_interval default 5000, status FOCUSED (person present, no phone, pitch=0). ✓.

Now, one more: the milestone message format. 产品方案: `snprintf(st.message, 128, "已专注学习 %d 分钟,继续保持!", streak);`. I'll match.

Also `milestone_reached` and `milestone_minutes`. ✓.

Now let me also verify: in test 8, g_focus_start_ms gets set on FIRST focused frame. In behavior_init I set g_focus_start_ms=0. First focused frame ts=0: status FOCUSED, g_focus_start_ms==0 → set g_focus_start_ms = 0 (latest ts). Then focus_ms = 0-0=0, focus_min=0, no milestone. ✓. Second frame ts=1.8M: g_focus_start_ms already 0 (nonzero? it's 0!). 

PROBLEM: g_focus_start_ms = 0 after first frame (since latest ts = 0). On second frame, `if (g_focus_start_ms == 0) g_focus_start_ms = latest->ts` would RE-SET it to 1.8M because g_focus_start_ms is 0! That breaks the milestone.

I need a separate flag to track "are we in a focus streak", not use 0 as sentinel. Use a bool `g_in_focus`:
```c
static bool g_in_focus = false;
static uint32_t g_focus_start_ms = 0;
```
On FOCUSED: if (!g_in_focus) { g_in_focus = true; g_focus_start_ms = latest->ts; }. On non-FOCUSED: g_in_focus = false.

Good catch. Let me use that.

Also, the same-frame dedup sentinel: g_last_frame_ts == 0 as "no previous frame". If the first frame has ts=0 (like my tests), then g_last_frame_ts becomes 0, and the dedup check `latest->ts == g_last_frame_ts && g_last_frame_ts != 0` fails (since ts=0). That's fine — first frame ts=0 is processed normally. Second call with same ts=0 would dedup only if g_last_frame_ts==0 AND ts==0, but my guard `g_last_frame_ts != 0` prevents dedup when ts=0. This means feeding ts=0 twice won't dedup. Minor edge case, acceptable (timestamps in real device start at ~boot time, not 0). For tests I'll use non-zero timestamps mostly, or accept this edge. Actually test 8 uses ts=0. That's fine — no dedup needed there.

But wait, there's a subtle issue: in test 8, first frame ts=0, g_last_frame_ts set to 0. Then second frame ts=1.8M, dedup check: 1.8M == 0? No → process. Fine.

Let me make the tests use ts starting at 1000 to avoid the 0-sentinel confusion, except where milestone needs ts=0 anchor. Actually milestone test can start at ts=1000 and second at ts=1000+1,800,000. Let me use ts=1000 anchor and ts=1,801,000 for 30 min. focus_ms = 1,800,000 → 30 min. Clean. I'll use non-zero base timestamps everywhere.

Let me re-plan test 8:
- init gentle.
- focused frame ts=1000 → FOCUSED, NONE. g_in_focus=true, g_focus_start_ms=1000.
- focused frame ts=1,801,000 → focus_ms=1,800,000 → 30min → ENCOURAGE milestone 30.
- focused frame ts=1,806,000 → focus_min still 30 → no re-celebrate.

Good.

Now, also need to double-check the dedup interplay with milestone. After milestone fires at ts=1.8M, g_last_frame_ts=1,801,000. Third frame 1,806,000 ≠ → process. Fine.

Now let me also reconsider: should `behavior_analyze_history` update `g_last_frame_ts` and `g_last_state` even on the empty-history path? For empty history I return early with FOCUSED/NONE without updating g_last_frame_ts. That's fine.

Let me also handle `estimate_frame_interval_ms` and `streak_duration_ms` carefully for uint32/int32 arithmetic to avoid -Werror sign issues. I'll use explicit casts.

Now, let me write the header `api/behavior.h`.

```c
#ifndef API_BEHAVIOR_H
#define API_BEHAVIOR_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

/* 错误码兜底(通常由 api/error.h 提供) */
#ifndef FOCUS_OK
#define FOCUS_OK 0
#endif
#ifndef FOCUS_ERR_BEHAVIOR_PARAM
#define FOCUS_ERR_BEHAVIOR_PARAM (-40)
#endif

/* 学习状态(空间 -> 时间推理的结果) */
typedef enum {
    FOCUSED = 0,          /* 专注 */
    GLANCING_PHONE,       /* 看手机(短暂/无操作) */
    PLAYING_PHONE,        /* 玩手机(持续+手部运动) */
    AWAY,                 /* 离座 */
    DROWSY,               /* 瞌睡 */
    STATUS_COUNT
} status_t;

typedef enum {
    NONE = 0,
    REMIND,
    ENCOURAGE,
} action_t;

typedef enum {
    MODE_STRICT = 0,      /* 严格: 阈值紧, 每次提醒 */
    MODE_GENTLE,          /* 鼓励: 阈值松, 累计提醒+里程碑 */
    MODE_COUNT
} mode_t;

typedef struct {
    status_t  status;
    action_t  action;
    char      message[128];
    bool      milestone_reached;
    int       milestone_minutes;
    int8_t    focus_score_delta;   /* 评分变化量(负=扣分, 正=加分) */
} study_state_t;

int behavior_init(mode_t mode);
int behavior_analyze(study_state_t *out);

#endif
```

Wait, I need to be careful: `NONE`, `AWAY`, `FOCUSED` etc. as bare enum constants. In the test file and behavior.c, these are fine. But `NONE` might collide with Windows headers if any are included. In pure C on host (gcc) with only std headers, `NONE` is not defined by default. Fine. On ESP32/embedded, also likely fine. I'll keep bare names to match the doc.

Actually, `REMIND` — is that a macro anywhere? Unlikely. `ENCOURAGE` unlikely. OK.

Now behavior_internal.h:
```c
#ifndef BEHAVIOR_INTERNAL_H
#define BEHAVIOR_INTERNAL_H

#include "../api/behavior.h"
#include "../api/perception.h"

typedef struct {
    int   phone_glance_sec;
    int   phone_playing_sec;
    int   away_sec;
    int   drowsy_sec;
    int   remind_cooldown_sec;
    int   remind_after_n_times;
    int   focus_milestone_min;
    int   score_penalty_phone;
    int   score_penalty_away;
    int   score_penalty_drowsy;
    int   score_bonus_milestone;
    bool  enable_milestone;
    const char *const *messages;   /* 按 status_t 索引的提醒话术 */
} mode_config_t;

extern const mode_config_t g_mode_configs[MODE_COUNT];

int behavior_analyze_history(const observation_t *history, int count,
                             study_state_t *out);

#endif
```

Wait, behavior_internal.h includes "../api/perception.h" for observation_t. But perception.h has its own error codes (FOCUS_OK etc.) with #ifndef guards, so no conflict. Good.

Now behavior_config.c:
```c
#include "../api/behavior.h"
#include "behavior_internal.h"

static const char *const strict_messages[STATUS_COUNT] = {
    [FOCUSED]         = NULL,
    [GLANCING_PHONE]  = NULL,
    [PLAYING_PHONE]   = "请放下手机!",
    [AWAY]            = "请回到座位!",
    [DROWSY]          = "请注意坐姿!",
};

static const char *const gentle_messages[STATUS_COUNT] = {
    [FOCUSED]         = NULL,
    [GLANCING_PHONE]  = NULL,
    [PLAYING_PHONE]   = "休息好了就继续吧~",
    [AWAY]            = "等你回来哦~",
    [DROWSY]          = "要不要起来活动一下?",
};

const mode_config_t g_mode_configs[MODE_COUNT] = {
    [MODE_STRICT] = {
        .phone_glance_sec     = 8,
        .phone_playing_sec    = 8,
        .away_sec             = 10,
        .drowsy_sec           = 8,
        .remind_cooldown_sec  = 30,
        .remind_after_n_times = 1,
        .focus_milestone_min  = 0,
        .score_penalty_phone  = -15,
        .score_penalty_away   = -10,
        .score_penalty_drowsy = -20,
        .score_bonus_milestone = 0,
        .enable_milestone     = false,
        .messages             = strict_messages,
    },
    [MODE_GENTLE] = {
        .phone_glance_sec     = 15,
        .phone_playing_sec    = 15,
        .away_sec             = 20,
        .drowsy_sec           = 12,
        .remind_cooldown_sec  = 120,
        .remind_after_n_times = 3,
        .focus_milestone_min  = 30,
        .score_penalty_phone  = -5,
        .score_penalty_away   = -3,
        .score_penalty_drowsy = -8,
        .score_bonus_milestone = 5,
        .enable_milestone     = true,
        .messages             = gentle_messages,
    },
};
```

The Chinese strings in the source: the existing perception.c uses UTF-8 Chinese comments/strings. But the message strings "请放下手机!" are Chinese. On the ESP32/openvela, encoding matters. But the existing code uses Chinese in comments. For string literals in C source, UTF-8 is fine (they're just bytes). I'll keep them as UTF-8. The build uses gcc; UTF-8 string literals are fine.

However, there's a concern: writing UTF-8 files on Windows with the Write tool. The Write tool writes UTF-8. The existing files (perception.c) contain Chinese, so UTF-8 is the norm. Good.

Now, the Chinese messages with `-Werror` and gcc — string literals with UTF-8 multibyte are fine, but `-Werror` with some locale warnings? `-Wall -Wextra` doesn't warn on UTF-8 string literals. Fine. But there's a potential issue: `-Werror` and the `~` character — fine. The `!` — fine.

Actually, one concern: gcc on Windows (MinGW) compiling UTF-8 source with Chinese string literals — the output will be UTF-8 bytes in the message. That's correct for the device if the device uses UTF-8. The doc says messages go to LCD/TTS, so encoding is the UI's concern. I'll keep UTF-8.

Let me check: is there a gcc available? The environment is Windows with Git Bash. The README uses `gcc`. Let me verify gcc is available before writing tests, so I can actually run them.

Let me check gcc availability.

Actually, let me plan the full set of files, then write them, then compile and run the tests to verify (since the user wants a "成品" / finished working product, I must actually verify it compiles and passes).

Let me check for gcc first.

Now behavior.c full implementation. Let me write it carefully.

```c
/****************************************************************************
 * FOCUS AIoT - 行为分析模块 (behavior/behavior.c)
 * ... 负责人: 赵思涵 ...
 ****************************************************************************/

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

#include "../api/behavior.h"
#include "../api/perception.h"
#include "behavior_internal.h"

/* ------------------------------------------------------------------ */
/* 内部配置                                                            */
/* ------------------------------------------------------------------ */
#define HISTORY_MAX              60
#define DEFAULT_FRAME_INTERVAL_MS 5000u
#define MAX_FRAME_INTERVAL_MS    60000u
#define HAND_MOTION_PLAY_THRESH  0.30f
#define DROWSY_PITCH_STRICT      45.0f
#define DROWSY_PITCH_GENTLE      52.0f

/* ------------------------------------------------------------------ */
/* 模块状态(单例; 由主循环串行调用, 无重入)                            */
/* ------------------------------------------------------------------ */
static mode_t        g_mode = MODE_STRICT;
static study_state_t g_last_state;         /* 同帧防重缓存 */
static uint32_t      g_last_frame_ts = 0;  /* 上次分析的最新帧时间戳 */
static uint32_t      g_last_remind_ms = 0; /* 上次提醒时间戳 */
static int           g_distract_count = 0; /* 累计分心次数(自上次提醒) */
static bool          g_in_focus = false;   /* 是否处于专注段 */
static uint32_t      g_focus_start_ms = 0; /* 专注段起点 */
static int           g_last_milestone_min = 0; /* 已庆祝的最近里程碑(去重) */

/* 时序谓词(从最新帧往前扫连续命中) */
typedef bool (*obs_pred_t)(const observation_t *o, float arg);

static bool pred_away(const observation_t *o, float arg)
{
    (void)arg;
    return !o->person_present;
}

static bool pred_phone(const observation_t *o, float arg)
{
    (void)arg;
    return o->phone_detected && o->phone_near_hand;
}

static bool pred_drowsy(const observation_t *o, float pitch_thresh)
{
    return o->person_present && (o->head_pitch > pitch_thresh);
}

/* 连续命中长度(从最新帧往前数) */
static int streak_from_tail(const observation_t *h, int n,
                            obs_pred_t pred, float arg)
{
    int s = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (pred(&h[i], arg)) s++;
        else break;
    }
    return s;
}

/* 相邻帧间隔估计(毫秒), 异常/单帧回退到默认 5s */
static uint32_t estimate_frame_interval_ms(const observation_t *h, int n)
{
    if (n < 2) return DEFAULT_FRAME_INTERVAL_MS;
    int32_t d = (int32_t)(h[n - 1].timestamp_ms - h[n - 2].timestamp_ms);
    if (d <= 0 || d > (int32_t)MAX_FRAME_INTERVAL_MS) {
        return DEFAULT_FRAME_INTERVAL_MS;
    }
    return (uint32_t)d;
}

/* 连续命中时段的持续毫秒数: 跨度 + 一个帧间隔(命中至少始于最老那帧) */
static uint32_t streak_duration_ms(const observation_t *h, int n, int streak,
                                   uint32_t interval_ms)
{
    if (streak <= 0) return 0;
    if (streak == 1) return interval_ms;

    int32_t span = (int32_t)(h[n - 1].timestamp_ms - h[n - streak].timestamp_ms);
    if (span <= 0) {
        /* 时间回绕或乱序, 回退按帧数估 */
        span = (int32_t)(streak - 1) * (int32_t)interval_ms;
    }
    return (uint32_t)span + interval_ms;
}

/* 连续命中段内手部运动均值 */
static float average_hand_motion(const observation_t *h, int n, int streak)
{
    if (streak <= 0) return 0.0f;
    int start = n - streak;
    float sum = 0.0f;
    for (int i = start; i < n; i++) {
        sum += h[i].hand_motion_score;
    }
    return sum / (float)streak;
}

static bool is_distraction_status(status_t s)
{
    return s == PLAYING_PHONE || s == AWAY || s == DROWSY;
}

static int penalty_for(const mode_config_t *cfg, status_t s)
{
    switch (s) {
    case PLAYING_PHONE: return cfg->score_penalty_phone;
    case AWAY:          return cfg->score_penalty_away;
    case DROWSY:        return cfg->score_penalty_drowsy;
    default:            return 0;
    }
}
```

Then the two public functions and the internal analyze function.

```c
int behavior_init(mode_t mode)
{
    if (mode != MODE_STRICT && mode != MODE_GENTLE) {
        return FOCUS_ERR_BEHAVIOR_PARAM;
    }
    g_mode = mode;
    memset(&g_last_state, 0, sizeof(g_last_state));
    g_last_state.status = FOCUSED;
    g_last_frame_ts = 0;
    g_last_remind_ms = 0;
    g_distract_count = 0;
    g_in_focus = false;
    g_focus_start_ms = 0;
    g_last_milestone_min = 0;
    return FOCUS_OK;
}

int behavior_analyze(study_state_t *out)
{
    observation_t history[HISTORY_MAX];
    int n = perception_get_history(history, HISTORY_MAX);
    return behavior_analyze_history(history, n, out);
}
```

Wait, behavior_analyze calls perception_get_history — this is declared in api/perception.h (which I include). In the test build, I need to link a stub. I'll provide the stub in the test file, OR use a weak symbol. Let me provide it in the test file (like wifi_http_post_stub.c). Actually simpler: declare in test file a stub `perception_get_history` returning 0.

Actually, wait — there could be a linker issue: behavior.c references perception_get_history (external). In the unit test, I link behavior.c + behavior_config.c + test_behavior.c. test_behavior.c provides `int perception_get_history(observation_t *buf, int n)` stub. Good.

But there's also the header: api/perception.h defines the observation_t and declares perception_get_history. The stub in test must match signature. Fine.

Now behavior_analyze_history:

```c
int behavior_analyze_history(const observation_t *history, int count,
                             study_state_t *out)
{
    if (!out) {
        return FOCUS_ERR_BEHAVIOR_PARAM;
    }
    if (!history || count <= 0) {
        memset(out, 0, sizeof(*out));
        out->status = FOCUSED;   /* 空历史 → 视为专注(不误报) */
        out->action = NONE;
        return FOCUS_OK;
    }

    const mode_config_t *cfg = &g_mode_configs[g_mode];
    const observation_t *latest = &history[count - 1];
    float drowsy_pitch = (g_mode == MODE_STRICT)
                         ? DROWSY_PITCH_STRICT : DROWSY_PITCH_GENTLE;

    /* 同帧防重: 相同最新帧时间戳 → 直接返回缓存结果 */
    if (g_last_frame_ts != 0 && latest->timestamp_ms == g_last_frame_ts) {
        *out = g_last_state;
        return FOCUS_OK;
    }
    g_last_frame_ts = latest->timestamp_ms;

    uint32_t interval_ms = estimate_frame_interval_ms(history, count);

    int away_streak   = streak_from_tail(history, count, pred_away, 0.0f);
    int phone_streak  = streak_from_tail(history, count, pred_phone, 0.0f);
    int drowsy_streak = streak_from_tail(history, count, pred_drowsy, drowsy_pitch);

    uint32_t away_ms   = streak_duration_ms(history, count, away_streak, interval_ms);
    uint32_t phone_ms  = streak_duration_ms(history, count, phone_streak, interval_ms);
    uint32_t drowsy_ms = streak_duration_ms(history, count, drowsy_streak, interval_ms);

    float avg_motion = average_hand_motion(history, count, phone_streak);
    bool has_hand_motion = avg_motion > HAND_MOTION_PLAY_THRESH;

    /* 状态判定: 优先级 AWAY > 玩手机 > 看手机 > 瞌睡 > 专注 */
    status_t status;
    if (away_ms >= (uint32_t)cfg->away_sec * 1000u) {
        status = AWAY;
    } else if (phone_ms >= (uint32_t)cfg->phone_playing_sec * 1000u
               && has_hand_motion) {
        status = PLAYING_PHONE;
    } else if (phone_ms > 0) {
        status = GLANCING_PHONE;
    } else if (drowsy_ms >= (uint32_t)cfg->drowsy_sec * 1000u) {
        status = DROWSY;
    } else {
        status = FOCUSED;
    }

    study_state_t st;
    memset(&st, 0, sizeof(st));
    st.status = status;
    st.action = NONE;

    /* 专注段维护(里程碑用) */
    if (status == FOCUSED) {
        if (!g_in_focus) {
            g_in_focus = true;
            g_focus_start_ms = latest->timestamp_ms;
        }
        int32_t focus_ms = (int32_t)(latest->timestamp_ms - g_focus_start_ms);
        if (focus_ms < 0) focus_ms = 0;
        int focus_min = (int)((uint32_t)focus_ms / 60000u);

        if (cfg->enable_milestone && cfg->focus_milestone_min > 0
            && focus_min >= cfg->focus_milestone_min
            && focus_min % cfg->focus_milestone_min == 0
            && focus_min > g_last_milestone_min) {
            st.action = ENCOURAGE;
            st.milestone_reached = true;
            st.milestone_minutes = focus_min;
            st.focus_score_delta = (int8_t)cfg->score_bonus_milestone;
            snprintf(st.message, sizeof(st.message),
                     "已专注学习 %d 分钟,继续保持!", focus_min);
            g_last_milestone_min = focus_min;
        }
    } else {
        g_in_focus = false;
    }

    /* 分心处理: 计数(新片段)+扣分+提醒门控 */
    if (is_distraction_status(status)) {
        bool was_distraction = is_distraction_status(g_last_state.status);
        if (status != g_last_state.status && !was_distraction) {
            g_distract_count++;   /* 新的分心片段 */
            st.focus_score_delta = (int8_t)penalty_for(cfg, status);
        }

        uint32_t now = latest->timestamp_ms;
        bool cooldown_ok = (g_last_remind_ms == 0)
            || ((int32_t)(now - g_last_remind_ms)
                >= (int32_t)((uint32_t)cfg->remind_cooldown_sec * 1000u));
        if (g_distract_count >= cfg->remind_after_n_times && cooldown_ok) {
            st.action = REMIND;
            const char *msg = cfg->messages[status];
            if (msg) {
                snprintf(st.message, sizeof(st.message), "%s", msg);
            }
            g_last_remind_ms = now;
            g_distract_count = 0;
        }
    }

    g_last_state = st;
    *out = st;
    return FOCUS_OK;
}
```

Wait, there's an issue with the score penalty logic. I set `st.focus_score_delta` only when `status != g_last_state.status && !was_distraction`. But when the SAME distraction continues (status unchanged), no new penalty (correct — one penalty per episode). But when transitioning between distraction types (e.g., AWAY → DROWSY), `status != g_last_state.status` is true but `was_distraction` is true, so no count increment AND no penalty. Is that right? Transition AWAY→DROWSY: the person came back then fell asleep, or changed from away to drowsy directly. Treating it as the same episode (no double penalty) is reasonable. But arguably it's a new episode. I'll keep "same episode" semantics and document: transitions between distraction types don't re-count (avoid double-counting a continuous distraction that morphs).

Hmm, but wait: there's a subtle bug. Consider the score penalty. When a new episode starts (FOCUSED→AWAY), I set score_delta. But if the very next frame is still AWAY (no transition), score_delta stays 0 (default from memset). That's correct — one penalty per episode.

But consider: cooldown blocks remind on episode 2 (test 6). On episode 2 (FOCUSED→AWAY), score_delta = -10 (set on transition), but action=NONE (cooldown). So test 6 expects score -10 and action NONE. My code: on transition, `was_distraction = is_distraction(g_last_state.status)`. g_last_state.status was FOCUSED (from the focused frame at ts=15000). So was_distraction=false, status(AWAY) != FOCUSED → count++ and score set. Then cooldown blocks remind. ✓. Good.

Now, there's another subtle issue: `g_last_state.status` initial value. In behavior_init I set `g_last_state.status = FOCUSED`. But `g_last_state` also has action etc. = 0 via memset. So initially status=FOCUSED, action=NONE (0). Good.

But wait — after the FIRST analysis, g_last_state = st (the result). On the NEXT analysis, I read `g_last_state.status` to determine was_distraction and transitions. That's correct.

Edge: in test 7 (gentle accumulate), after episode 1 (AWAY, action NONE because count=1<3), g_last_state.status = AWAY. Then I feed a FOCUSED frame: status FOCUSED != AWAY. was_distraction (of g_last_state=AWAY) = true. But status FOCUSED is not distraction, so the distraction block isn't entered. g_in_focus set. Then episode 2 (AWAY): transition FOCUSED→AWAY, was_distraction(g_last=FOCUSED)=false → count++ (now 2). ✓. Good.

Now let me trace test 7 fully:
- init GENTLE. g_distract_count=0, g_last_remind_ms=0, g_in_focus=false, g_last_milestone_min=0, g_last_state.status=FOCUSED.
- Episode 1: AWAY frames ts 1000..21000 (5 frames, 5s apart: 1000,6000,11000,16000,21000). away_streak=5. away_ms = (21000-1000)+5000=25000 ≥ 20000 (gentle 20s) → AWAY.
  - transition FOCUSED→AWAY, was_distraction=false → count=1, score=-3.
  - cooldown ok (last_remind=0). count(1) >= n(3)? No → action NONE.
  - g_last_state = {AWAY, NONE, -3}. 
  - Expected: AWAY, NONE, -3. ✓
- FOCUSED frame ts=26000. status FOCUSED (person present, no phone, pitch 0). 
  - g_in_focus false → true, g_focus_start_ms=26000. focus_ms=0. no milestone.
  - not distraction. g_last_state={FOCUSED,NONE,0}.
- Episode 2: AWAY frames ts 31000..51000. away_ms = (51000-31000)+5000=25000 ≥ 20s → AWAY.
  - transition FOCUSED→AWAY, was_distraction=false → count=2, score=-3.
  - count 2 >= 3? No → NONE. g_last_state={AWAY,NONE,-3}.
- FOCUSED frame ts=56000. → FOCUSED. g_focus_start_ms=56000 (reset since g_in_focus was false).
- Episode 3: AWAY frames ts 61000..81000. away_ms=25000 → AWAY.
  - transition FOCUSED→AWAY → count=3, score=-3.
  - count 3>=3 AND cooldown ok → REMIND "等你回来哦~", reset count=0, last_remind=81000.
  - g_last_state={AWAY, REMIND, -3}.
  - Expected: AWAY, REMIND, -3, message "等你回来哦~". ✓

Great, test 7 works.

Now test 6 (cooldown strict):
- init STRICT.
- Episode 1: AWAY ts 1000,6000,11000. away_streak=3, away_ms=(11000-1000)+5000=15000 ≥ 10000 (strict 10s) → AWAY.
  - transition FOCUSED→AWAY → count=1, score=-10.
  - count 1>=1, cooldown ok → REMIND "请回到座位!", reset count=0, last_remind=11000.
- FOCUSED frame ts=16000. → FOCUSED.
- Episode 2: AWAY ts 21000,26000,31000. away_ms=15000 → AWAY.
  - transition FOCUSED→AWAY → count=1, score=-10.
  - cooldown: now=31000, last_remind=11000, since=20000ms=20s < 30s → cooldown NOT ok → action NONE. count stays 1 (not reset).
  - g_last_state={AWAY, NONE, -10}.
  - Expected: AWAY, NONE, -10. ✓

Good. Note: count is now 1 (not reset). If episode 3 happens later (after cooldown), count would increment to 2 then remind. But strict n=1 means it should remind on every episode. Hmm — if count=1 is leftover and next episode increments to 2, then `2 >= 1` still true → remind. So still works. But there's a subtle bug: leftover count accumulates. In strict mode n=1, count should reset to 0 after each episode is "accounted". 

Actually, let me reconsider the counting. The issue: in strict mode, when cooldown blocks the remind (episode 2), the count stays at 1 (the episode was counted but not reminded). Next episode (episode 3) increments to 2, then 2>=1 → remind (if cooldown ok). So it works, but the count grows unboundedly in strict mode across blocked episodes. That's harmless (>=1 always true). But semantically, after a remind fires, count resets to 0. After a BLOCKED remind, count stays. It's fine functionally.

But wait, there's a cleaner issue: what if strict mode, episode 2 blocked by cooldown (count=1), then episode 3 (still within cooldown) → count=2, cooldown still blocked → NONE. Then episode 4 (cooldown elapsed) → count=3, cooldown ok → REMIND. So one remind for episodes 2-4 (3 episodes), which is NOT "every distraction reminds" for strict. Hmm. But this only happens when distractions are rapid-fire (multiple episodes within 30s), which is an edge case. The cooldown is explicitly designed to prevent spam. I think it's acceptable: "每次分心都提醒（间隔 30s）" — the 30s interval IS the cooldown, so reminding at most once per 30s. My behavior: rapid episodes within 30s → remind once per 30s (not each). That matches "间隔 30s". Good enough.

Actually, let me simplify the mental model: strict = remind whenever a distraction episode occurs AND ≥30s since last remind. gentle = remind whenever 3rd distraction episode occurs AND ≥120s since last remind. My code achieves this. Good.

One more consideration: `focus_score_delta` when a distraction continues across frames with no transition — I set it to 0 (default). But what about the cooldown-blocked episode — I set it on transition even though remind blocked. That's the design (penalty independent of remind). Document it.

Now, the `int8_t` for focus_score_delta and assigning `(int8_t)cfg->score_bonus_milestone` (=5) and `(int8_t)penalty_for(...)` (negative). Fine.

Now let me also double check: `st.focus_score_delta = (int8_t)cfg->score_bonus_milestone;` — in strict mode, bonus=0 and milestone disabled, so this never runs. Good.

Now let me think about potential -Werror issues:
1. `snprintf` — included stdio.h. Fine. Return value ignored — gcc doesn't warn on unused snprintf return by default (it's not marked warn_unused_result). Fine.
2. Unused parameter `arg` in pred_away/pred_phone — I do `(void)arg;`. Good.
3. Comparison signed/unsigned: `away_ms >= (uint32_t)cfg->away_sec * 1000u` — away_ms is uint32_t, (uint32_t)*1000u is uint32_t. Fine. `phone_ms >= (uint32_t)cfg->phone_playing_sec * 1000u`. Fine. `drowsy_ms >= (uint32_t)cfg->drowsy_sec * 1000u`. Fine.
4. `int focus_min = (int)((uint32_t)focus_ms / 60000u);` — fine.
5. `focus_min % cfg->focus_milestone_min` — focus_min int, milestone_min int. Fine.
6. `(int32_t)(now - g_last_remind_ms)` — now and g_last_remind_ms are uint32_t; `now - g_last_remind_ms` is uint32_t arithmetic; cast to int32_t. Fine. `(int32_t)((uint32_t)cfg->remind_cooldown_sec * 1000u)` — uint32_t product cast to int32_t (remind_cooldown_sec=30 → 30000, fits). Fine.
7. `(int32_t)(h[n-1].timestamp_ms - h[n-2].timestamp_ms)` — fine.
8. `(int32_t)(h[n-1].timestamp_ms - h[n-streak].timestamp_ms)` — fine.
9. `latest->timestamp_ms - g_focus_start_ms` — both uint32_t → uint32_t subtraction, cast to int32_t. Fine.

Also `pred_drowsy` compares `o->head_pitch > pitch_thresh` (float > float). Fine.

Now, one concern: `streak_from_tail` uses `pred(&h[i], arg)` where pred is obs_pred_t. pred_away, pred_phone, pred_drowsy all match `bool (*)(const observation_t*, float)`. Good.

Now the test file. Let me write a self-contained test with assertions and a counter. I'll mirror the style of test_perception.c (which I haven't seen, but I'll write a clean one).

Let me write test_behavior.c:

```c
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#include "../api/behavior.h"
#include "../api/perception.h"
#include "../behavior/behavior_internal.h"

/* 测试桩: behavior_analyze() 依赖 perception_get_history(), 单测不走到它 */
int perception_get_history(observation_t *buf, int n)
{
    (void)buf;
    (void)n;
    return 0;
}

static int g_fail = 0;

#define CHECK(cond) do { \
    if (!(cond)) { \
        printf("  FAIL %s:%d  %s\n", __FILE__, __LINE__, #cond); \
        g_fail++; \
    } \
} while (0)

#define CHECK_STR(a, b) do { \
    if (strcmp((a), (b)) != 0) { \
        printf("  FAIL %s:%d  str: got \"%s\" want \"%s\"\n", \
               __FILE__, __LINE__, (a), (b)); \
        g_fail++; \
    } \
} while (0)

static observation_t obs(uint32_t ts, bool person, bool phone, bool near_hand,
                         float pitch, float motion)
{
    observation_t o;
    memset(&o, 0, sizeof(o));
    o.timestamp_ms = ts;
    o.person_present = person;
    o.phone_detected = phone;
    o.phone_near_hand = near_hand;
    o.head_pitch = pitch;
    o.hand_motion_score = motion;
    o.confidence = 0.9f;
    return o;
}
```

Then test functions. Let me write them.

```c
static void test_empty(void)
{
    study_state_t st;
    observation_t dummy;
    memset(&dummy, 0, sizeof(dummy));

    CHECK(behavior_init(MODE_STRICT) == FOCUS_OK);
    CHECK(behavior_analyze_history(&dummy, 0, &st) == FOCUS_OK);
    CHECK(st.status == FOCUSED);
    CHECK(st.action == NONE);
}

static void test_strict_away(void)
{
    observation_t h[3] = {
        obs(1000, false, false, false, 0.0f, 0.0f),
        obs(6000, false, false, false, 0.0f, 0.0f),
        obs(11000, false, false, false, 0.0f, 0.0f),
    };
    study_state_t st;

    CHECK(behavior_init(MODE_STRICT) == FOCUS_OK);
    CHECK(behavior_analyze_history(h, 3, &st) == FOCUS_OK);
    CHECK(st.status == AWAY);
    CHECK(st.action == REMIND);
    CHECK(st.focus_score_delta == -10);
    CHECK_STR(st.message, "请回到座位!");
}
```

Wait, `CHECK(st.focus_score_delta == -10)` — focus_score_delta is int8_t, -10 is int. Comparison promotes to int, fine. But `-10` vs int8_t -10 → equal. Good. But `==` between int8_t and int literal -10 → no warning. Good.

test_strict_phone:
```c
static void test_strict_phone(void)
{
    observation_t h[3] = {
        obs(1000, true, true, true, 0.0f, 0.6f),
        obs(6000, true, true, true, 0.0f, 0.6f),
        obs(11000, true, true, true, 0.0f, 0.6f),
    };
    study_state_t st;
    CHECK(behavior_init(MODE_STRICT) == FOCUS_OK);
    CHECK(behavior_analyze_history(h, 3, &st) == FOCUS_OK);
    CHECK(st.status == PLAYING_PHONE);
    CHECK(st.action == REMIND);
    CHECK(st.focus_score_delta == -15);
    CHECK_STR(st.message, "请放下手机!");
}
```

test_glancing:
```c
static void test_glancing(void)
{
    observation_t h[1] = { obs(1000, true, true, true, 0.0f, 0.1f) };
    study_state_t st;
    CHECK(behavior_init(MODE_STRICT) == FOCUS_OK);
    CHECK(behavior_analyze_history(h, 1, &st) == FOCUS_OK);
    CHECK(st.status == GLANCING_PHONE);
    CHECK(st.action == NONE);
    CHECK(st.focus_score_delta == 0);
}
```

test_strict_drowsy:
```c
static void test_strict_drowsy(void)
{
    observation_t h[3] = {
        obs(1000, true, false, false, 55.0f, 0.0f),
        obs(6000, true, false, false, 55.0f, 0.0f),
        obs(11000, true, false, false, 55.0f, 0.0f),
    };
    study_state_t st;
    CHECK(behavior_init(MODE_STRICT) == FOCUS_OK);
    CHECK(behavior_analyze_history(h, 3, &st) == FOCUS_OK);
    CHECK(st.status == DROWSY);
    CHECK(st.action == REMIND);
    CHECK(st.focus_score_delta == -20);
    CHECK_STR(st.message, "请注意坐姿!");
}
```

test_cooldown:
```c
static void test_strict_cooldown(void)
{
    observation_t away[3] = {
        obs(1000, false, false, false, 0.0f, 0.0f),
        obs(6000, false, false, false, 0.0f, 0.0f),
        obs(11000, false, false, false, 0.0f, 0.0f),
    };
    observation_t focus[1] = { obs(16000, true, false, false, 0.0f, 0.0f) };
    observation_t away2[3] = {
        obs(21000, false, false, false, 0.0f, 0.0f),
        obs(26000, false, false, false, 0.0f, 0.0f),
        obs(31000, false, false, false, 0.0f, 0.0f),
    };
    study_state_t st;

    CHECK(behavior_init(MODE_STRICT) == FOCUS_OK);
    CHECK(behavior_analyze_history(away, 3, &st) == FOCUS_OK);
    CHECK(st.action == REMIND);

    CHECK(behavior_analyze_history(focus, 1, &st) == FOCUS_OK);
    CHECK(st.status == FOCUSED);

    CHECK(behavior_analyze_history(away2, 3, &st) == FOCUS_OK);
    CHECK(st.status == AWAY);
    CHECK(st.action == NONE);       /* 冷却期内, 抑制提醒 */
    CHECK(st.focus_score_delta == -10);
}
```

test_gentle_accumulate:
```c
static void test_gentle_accumulate(void)
{
    study_state_t st;
    CHECK(behavior_init(MODE_GENTLE) == FOCUS_OK);

    /* 三次独立离座片段, 只有第三次触发提醒 */
    observation_t away1[5] = {
        obs(1000, false, false, false, 0.0f, 0.0f),
        obs(6000, false, false, false, 0.0f, 0.0f),
        obs(11000, false, false, false, 0.0f, 0.0f),
        obs(16000, false, false, false, 0.0f, 0.0f),
        obs(21000, false, false, false, 0.0f, 0.0f),
    };
    observation_t focus[1] = { obs(26000, true, false, false, 0.0f, 0.0f) };

    CHECK(behavior_analyze_history(away1, 5, &st) == FOCUS_OK);
    CHECK(st.status == AWAY);
    CHECK(st.action == NONE);       /* 第 1 次, 未到累计阈值 */

    CHECK(behavior_analyze_history(focus, 1, &st) == FOCUS_OK);

    observation_t away2[5] = {
        obs(31000, false, false, false, 0.0f, 0.0f),
        obs(36000, false, false, false, 0.0f, 0.0f),
        obs(41000, false, false, false, 0.0f, 0.0f),
        obs(46000, false, false, false, 0.0f, 0.0f),
        obs(51000, false, false, false, 0.0f, 0.0f),
    };
    CHECK(behavior_analyze_history(away2, 5, &st) == FOCUS_OK);
    CHECK(st.status == AWAY);
    CHECK(st.action == NONE);       /* 第 2 次 */

    CHECK(behavior_analyze_history(focus, 1, &st) == FOCUS_OK);

    observation_t away3[5] = {
        obs(61000, false, false, false, 0.0f, 0.0f),
        obs(66000, false, false, false, 0.0f, 0.0f),
        obs(71000, false, false, false, 0.0f, 0.0f),
        obs(76000, false, false, false, 0.0f, 0.0f),
        obs(81000, false, false, false, 0.0f, 0.0f),
    };
    CHECK(behavior_analyze_history(away3, 5, &st) == FOCUS_OK);
    CHECK(st.status == AWAY);
    CHECK(st.action == REMIND);     /* 第 3 次, 触发提醒 */
    CHECK_STR(st.message, "等你回来哦~");
    CHECK(st.focus_score_delta == -3);
}
```

Wait — the `focus[1]` re-use: I use the same `focus` array with ts=26000 for both transitions. But after episode 1 → focus(ts 26000) → g_last_frame_ts=26000. Then away2 (ts 31000..) → different ts. Then focus(ts 26000) again → but g_last_frame_ts is now 51000 (from away2's latest). Wait let me trace:

- away1 latest ts=21000. g_last_frame_ts=21000.
- focus ts=26000: 26000 != 21000 → process. g_last_frame_ts=26000.
- away2 latest ts=51000: != 26000 → process. g_last_frame_ts=51000.
- focus ts=26000 AGAIN: 26000 != 51000 → process (NOT deduped, but that's fine — it's just a FOCUSED frame). g_last_frame_ts=26000. Wait, this re-sets g_last_frame_ts to 26000, which is going BACKWARD. That's a problem for the next away3 (ts 61000) — 61000 != 26000 → processes fine. So no dedup issue. But re-using focus with ts=26000 after away2 (51000) means timestamps go backward (51000 → 26000 → 61000). The frame interval estimation for the focus[1] single frame → default 5000 (n<2). Fine. And status FOCUSED → resets focus streak. No harm.

Actually, it's cleaner to use distinct timestamps for the two focus frames to avoid backward-timestamp confusion. Let me use focus_a ts=26000 and focus_b ts=56000. Let me just make two separate focus arrays. I'll rewrite to use distinct ts.

Let me restructure test_gentle_accumulate with focus_a (ts=26000) and focus_b (ts=56000).

test_milestone:
```c
static void test_gentle_milestone(void)
{
    study_state_t st;
    observation_t f1[1] = { obs(1000, true, false, false, 0.0f, 0.0f) };
    observation_t f2[1] = { obs(1801000, true, false, false, 0.0f, 0.0f) };
    observation_t f3[1] = { obs(1806000, true, false, false, 0.0f, 0.0f) };

    CHECK(behavior_init(MODE_GENTLE) == FOCUS_OK);
    CHECK(behavior_analyze_history(f1, 1, &st) == FOCUS_OK);
    CHECK(st.status == FOCUSED);
    CHECK(st.action == NONE);

    CHECK(behavior_analyze_history(f2, 1, &st) == FOCUS_OK);
    CHECK(st.status == FOCUSED);
    CHECK(st.action == ENCOURAGE);
    CHECK(st.milestone_reached == true);
    CHECK(st.milestone_minutes == 30);
    CHECK(st.focus_score_delta == 5);

    CHECK(behavior_analyze_history(f3, 1, &st) == FOCUS_OK);
    CHECK(st.action == NONE);       /* 里程碑去重, 不重复庆祝 */
}
```

Wait, f1 ts=1000, f2 ts=1801000. focus_ms = 1801000 - 1000 = 1,800,000 → 30 min. Good. f3 ts=1806000 → focus_ms = 1,805,000 → 30 min (integer div). 30 not > 30 → no celebrate. ✓.

But wait: single frame focus — frame interval default 5000. status FOCUSED (person present, no phone, pitch 0 ≤ 52 gentle). ✓.

Also, note: in f2, g_in_focus is true (from f1), g_focus_start_ms=1000. focus_ms = 1801000-1000 = 1,800,000. focus_min=30. enable_milestone true, milestone_min=30, 30>=30, 30%30==0, 30>g_last_milestone_min(0) → ENCOURAGE. g_last_milestone_min=30. ✓.

main:
```c
int main(void)
{
    test_empty();
    test_strict_away();
    test_strict_phone();
    test_glancing();
    test_strict_drowsy();
    test_strict_cooldown();
    test_gentle_accumulate();
    test_gentle_milestone();

    if (g_fail == 0) {
        printf("ALL TESTS PASSED (%d fail)\n", g_fail);
        return 0;
    }
    printf("%d FAILED\n", g_fail);
    return 1;
}
```

Now, `CHECK(st.focus_score_delta == 0)` in test_glancing — focus_score_delta int8_t == 0 → fine. But wait, I memset st to 0 in behavior_analyze_history, so focus_score_delta default 0. Good.

But there's a subtlety: `CHECK(st.focus_score_delta == -10)` — int8_t compared to int literal -10. The int8_t -10 == -10 → true. No warning (comparison of int8_t and int, both signed, -Wsign-compare not triggered since both signed after promotion). Good.

Now, one issue: in the header, I declared `int8_t focus_score_delta`. `CHECK(st.focus_score_delta == -10)`: st.focus_score_delta is int8_t (signed char typically), promoted to int (-10). Compare to -10. Fine.

Let me also make sure I `#include <stdint.h>` in the test (I do) for int8_t etc.

Now let me also double-check the messages array indexing. `cfg->messages[status]` where status is status_t (0..4) and messages has STATUS_COUNT=5 entries. For FOCUSED and GLANCING, messages are NULL → the remind only fires for PLAYING/AWAY/DROWSY, so msg is non-NULL. Good.

Now, there's a concern about the message strings containing UTF-8 and gcc on Windows (MinGW) with -Werror. The `~` and `!` are ASCII. The Chinese chars are UTF-8 multibyte. gcc treats string literals as byte arrays, no warning. But there's a known issue: on Windows, the source file encoding. The Write tool writes UTF-8 (no BOM). gcc (MinGW) default assumes UTF-8 source (GCC 5+ defaults to UTF-8). So Chinese literals compile fine. The existing perception.c has Chinese and presumably compiled fine. Good.

Let me check if gcc is available and what version. Let me run a quick check.

Actually, let me also reconsider: should I write BUILD_INTEGRATION.md and README.md? Yes, to make it a "成品" matching the focus_perception structure. I'll write them concisely.

Also, I should verify the whole thing compiles and tests pass before presenting. Let me check gcc availability first.

Let me also reconsider the directory: the existing is `C:\temp\focus_perception`. I'll create `C:\temp\focus_behavior` as sibling. The user said "接入C:\temp文件夹下的项目" — integrate into the C:\temp project. So creating a sibling folder `focus_behavior` is right (parallel to focus_perception).

Let me now also think: does the user want me to also MODIFY the existing perception to emit "action"? No — the architecture is clear: perception (single frame) → behavior (temporal). The behavior module is the "action recognition from continuous frames" piece. I'll build behavior and document how it plugs in.

Let me check gcc availability, then write all files, then compile + test.

Let me run a quick check for gcc.

---

### [2026-08-28 15:24:52] AI

[工具调用] Bash: {"command": "gcc --version 2>&1 | head -3; echo \"---\"; which gcc 2>&1", "description": "Check gcc availability and version"}

---

### [2026-08-28 16:10:34] 用户

[工具结果] clang version 22.1.8 (https://github.com/llvm/llvm-project.git ca7933e47d3a3451d81e72ac174dcb5aa28b59d1)
Target: x86_64-w64-windows-gnu
Thread model: posix
---
/c/Users/user/AppData/Local/Microsoft/WinGet/Packages/MartinStorsjo.LLVM-MinGW.UCRT_Microsoft.Winget.Source_8wekyb3d8bbwe/llvm-mingw-20260616-ucrt-x86_64/bin/gcc

---

### [2026-08-28 16:11:00] AI

[思考] gcc is available (actually clang-based LLVM-MinGW). Version 22.1.8. This should compile C with -Wall -Wextra -Werror fine.

Now let me write all the files. I'll create the focus_behavior directory structure and write files.

Let me plan the exact files:
1. `C:\temp\focus_behavior\api\behavior.h`
2. `C:\temp\focus_behavior\behavior\behavior.c`
3. `C:\temp\focus_behavior\behavior\behavior_internal.h`
4. `C:\temp\focus_behavior\behavior\behavior_config.c`
5. `C:\temp\focus_behavior\tests\test_behavior.c`
6. `C:\temp\focus_behavior\BUILD_INTEGRATION.md`
7. `C:\temp\focus_behavior\README.md`

Note: behavior_internal.h and behavior.c need to include "../api/perception.h" — but api/perception.h is in the focus_perception folder, not focus_behavior. I need to either:
1. Copy api/perception.h into focus_behavior/api/ (as a reference copy), OR
2. Reference ../focus_perception/api/perception.h.

The behavior module depends on observation_t and perception_get_history from api/perception.h. To make focus_behavior self-contained and compile standalone, I should include a reference copy of api/perception.h. But that duplicates. 

Actually, the cleanest: the behavior module includes "../api/perception.h", which means focus_behavior/api/perception.h must exist. I'll add a reference copy of perception.h into focus_behavior/api/ (same as focus_perception/api/perception.h, with a note it's a reference copy). But wait — that creates TWO copies of perception.h (one in focus_perception/api, one in focus_behavior/api). 

Alternatively, I could make behavior include the perception header via a relative path "../focus_perception/api/perception.h". But that couples the two folders awkwardly and the include in behavior.c would be "../focus_perception/api/perception.h" which is ugly.

Better approach: Since behavior.c only needs `observation_t` (the struct) and `perception_get_history` (declaration), and these come from api/perception.h, I'll create `focus_behavior/api/perception.h` as a reference copy (matching the note convention already used: "此文件是参考拷贝"). This mirrors exactly how the real repo works: both modules share the frozen api/*.h headers in the real repo.

Actually, wait — let me reconsider. The real repo has a single `api/` directory at the top level with `api/perception.h`, `api/behavior.h`, `api/error.h`, `api/wifi.h`, etc. Both modules include from `api/`. 

For my C:\temp structure, focus_perception has its own `api/perception.h` (a reference copy). For focus_behavior, I'll create `api/behavior.h` and a reference copy of `api/perception.h` (since behavior needs observation_t). 

To avoid maintaining two identical copies, I could have behavior.c's internal header reference the focus_perception copy. But cross-folder includes are fragile for a "成品" that might be moved. 

Decision: I'll create `focus_behavior/api/perception.h` as a reference copy with the same "参考拷贝" warning, identical content to focus_perception's. This makes focus_behavior fully self-contained (compiles standalone), which is important for the unit test. I'll add a note in README that this copy must stay in sync with the frozen api/perception.h.

Actually, simpler and cleaner: I can just copy the exact perception.h content. Let me do that. But actually — do I even need to copy the whole thing? behavior.c includes "../api/perception.h" only for observation_t + perception_get_history declaration. I could make a minimal header, but that risks divergence. Cleanest is a verbatim reference copy. I'll copy it verbatim.

Hmm, but that's 65 lines of duplication. Alternatively, I can make behavior_internal.h NOT depend on api/perception.h by forward-declaring observation_t... no, observation_t is needed by value (perception_get_history returns observation_t array, behavior_analyze_history takes const observation_t*). The struct definition is needed.

OK, verbatim copy of perception.h into focus_behavior/api/. Fine.

Let me now write all files. I'll write them one by one with the Write tool.

Let me be careful with the UTF-8 Chinese content. The Write tool should handle UTF-8.

Let me write the files now.

Actually, let me reconsider one more time about whether `behavior_analyze_history` should be exposed in behavior_internal.h. Yes — it's the testable core, declared in behavior_internal.h (like perception's perception_parse_cloud_response etc.). Good.

Also, I realize I should double-check: does `behavior_analyze` (public) need a non-test path? In production, behavior_analyze() calls perception_get_history() and then behavior_analyze_history(). This is correct and matches "behavior_analyze() 从 perception_get_history() 做时序判定".

Let me write everything now.

For behavior.c, I need to make sure `#include "../api/perception.h"` — actually, behavior.c uses `perception_get_history` and `observation_t`. The declaration of perception_get_history is in api/perception.h. And observation_t too. So include it. But also behavior_internal.h already includes ../api/perception.h. So behavior.c includes behavior_internal.h (which brings perception.h). But it's good practice to include explicitly too. I'll include both api/behavior.h and behavior_internal.h; behavior_internal.h brings perception.h. Actually to be safe and explicit, I'll include "../api/perception.h" in behavior.c too (redundant but clear). Redundant include is fine (header guards).

Let me finalize and write.

One more: the `int8_t` field. Let me reconsider whether to use `int8_t` or `int`. The doc says `uint8_t`. I'll use `int8_t` and note the deviation clearly in the header comment. Actually, you know what — let me reconsider using `int` to be safe and simple, since `int8_t` might cause issues with printf or comparisons? No, int8_t is fine. But `int` is more conventional for a "score delta" and avoids any signed-char promotion weirdness. The doc says uint8_t though.

I'll go with `int8_t` to stay close to the doc's "8-bit" intent while being signed. Add a clear comment.

Let me write the files now.

Let me write the header first.

---

### [2026-08-28 16:11:01] AI

gcc 可用（LLVM-MinGW 22.1.8）。我已理解项目：`C:\temp\focus_perception` 是周礼航的「视觉感知」模块（单帧 → `observation_t`），缺的是赵思涵的「行为分析」模块——把连续帧序列识别成动作状态。这就是你要的「成品」。

我来在 `C:\temp\focus_behavior` 建一个同风格、可独立编译单测的完整模块，并实际编译验证。

---

### [2026-08-28 16:11:11] AI

[工具调用] Write: {"file_path": "C:\\temp\\focus_behavior\\api\\behavior.h", "content": "/****************************************************************************\n * FOCUS AIoT - 行为分析模块公开接口 (api/behavior.h)\n *\n * 负责人: 赵思涵\n * 职责:   从一连串 observation_t (带时间戳的历史) 推断「在干嘛」——\n *         即时间维度的动作/行为识别 (严格 / 鼓励 双策略)。\n *\n * ⚠️ 注意: 此文件是【参考拷贝】，用于独立编译/单测。\n *    仓库里真正冻结的那份 api/behavior.h 由万思源维护，请以仓库版本为准。\n *    status_t/action_t/mode_t 枚举值、study_state_t 字段、函数签名必须与\n *    仓库冻结版一致。\n ****************************************************************************/\n\n#ifndef API_BEHAVIOR_H\n#define API_BEHAVIOR_H\n\n#include <stdbool.h>\n#include <stdint.h>\n#include <stddef.h>\n\n/*\n * 统一错误码 —— 通常由 api/error.h 提供并被 api/behavior.h 间接包含。\n * 下面用 #ifndef 兜底，保证脱离 error.h 也能独立编译。\n */\n#ifndef FOCUS_OK\n#define FOCUS_OK                    0\n#endif\n#ifndef FOCUS_ERR_BEHAVIOR_PARAM\n#define FOCUS_ERR_BEHAVIOR_PARAM   (-40)   /* 参数非法 (behavior 本地扩展) */\n#endif\n\n/*\n * 学习状态 (空间 -> 时间推理的结果)。\n * 严格/鼓励两种模式共用同一套状态枚举，只是判定阈值与话术不同。\n */\ntypedef enum {\n    FOCUSED        = 0,   /* 专注 */\n    GLANCING_PHONE,       /* 看手机 (短暂/未操作, 暂不提醒) */\n    PLAYING_PHONE,        /* 玩手机 (持续 + 手部运动) */\n    AWAY,                 /* 离座 */\n    DROWSY,               /* 瞌睡 */\n    STATUS_COUNT\n} status_t;\n\n/* 应采取的干预动作 */\ntypedef enum {\n    NONE      = 0,        /* 无需动作 */\n    REMIND,               /* 提醒 (分心) */\n    ENCOURAGE,            /* 鼓励 (专注里程碑, 仅鼓励模式) */\n} action_t;\n\n/* 干预策略模式 */\ntypedef enum {\n    MODE_STRICT = 0,      /* 严格: 阈值紧, 每次分心都提醒 */\n    MODE_GENTLE,          /* 鼓励: 阈值松, 累计提醒 + 专注里程碑 */\n    MODE_COUNT\n} mode_t;\n\n/*\n * 行为分析结果 (每收到一帧 observation 更新一次)。\n *\n * ⚠️ focus_score_delta 此处用 int8_t: 产品文档里该字段同时承载扣分(负)与\n *    加分(正), 而 uint8_t 无法表示负数, 故参考拷贝用 int8_t。合并时请与\n *    仓库冻结版核对字段类型。\n */\ntypedef struct {\n    status_t  status;              /* 当前学习状态 */\n    action_t  action;              /* 应采取的行动 */\n    char      message[128];        /* 提醒/鼓励文字 */\n    bool      milestone_reached;   /* 是否达到专注里程碑 (鼓励模式) */\n    int       milestone_minutes;   /* 连续专注分钟数 */\n    int8_t    focus_score_delta;   /* 评分变化量 (负=扣分, 正=加分) */\n} study_state_t;\n\n/* 初始化: 选择模式 + 清空所有内部状态。返回 FOCUS_OK=成功 */\nint  behavior_init(mode_t mode);\n\n/* 核心: 拉取 perception_get_history() 的最近 observation 序列, 做时序判定,\n *       输出 study_state_t。返回 FOCUS_OK=成功 */\nint  behavior_analyze(study_state_t *out);\n\n#endif /* API_BEHAVIOR_H */\n"}

---

### [2026-08-28 16:11:30] 用户

[工具结果] File created successfully at: C:\temp\focus_behavior\api\behavior.h (file state is current in your context — no need to Read it back)

---

### [2026-08-28 16:11:33] AI

[思考] Now the reference copy of perception.h.

---

### [2026-08-28 16:11:40] AI

[工具调用] Write: {"file_path": "C:\\temp\\focus_behavior\\api\\perception.h", "content": "/****************************************************************************\n * FOCUS AIoT - 视觉感知模块公开接口 (api/perception.h)\n *\n * 负责人: 周礼航\n * 职责:   从一张 JPEG 里看出「有什么」——只做空间维度的单帧静态分析。\n *\n * ⚠️ 注意: 此文件是【参考拷贝】，用于独立编译/单测。\n *    行为分析模块 (behavior) 依赖 observation_t 与 perception_get_history(),\n *    故在 focus_behavior/ 里保留此拷贝以便独立编译。仓库里真正冻结的那份\n *    api/perception.h 由万思源维护，请以仓库版本为准。\n ****************************************************************************/\n\n#ifndef API_PERCEPTION_H\n#define API_PERCEPTION_H\n\n#include <stdbool.h>\n#include <stdint.h>\n#include <stddef.h>\n\n/*\n * 统一错误码 —— 通常由 api/error.h 提供并被 api/perception.h 间接包含。\n * 下面用 #ifndef 兜底，保证脱离 error.h 也能独立编译。\n */\n#ifndef FOCUS_OK\n#define FOCUS_OK                    0\n#endif\n#ifndef FOCUS_ERR_PERCEP_TIMEOUT\n#define FOCUS_ERR_PERCEP_TIMEOUT   (-30)   /* 云端/HTTP 超时或请求失败 */\n#endif\n#ifndef FOCUS_ERR_PERCEP_JSON\n#define FOCUS_ERR_PERCEP_JSON      (-31)   /* JSON 解析失败 / 缺字段 */\n#endif\n#ifndef FOCUS_ERR_PERCEP_NODATA\n#define FOCUS_ERR_PERCEP_NODATA    (-32)   /* 业务码非 0 / 无数据 */\n#endif\n#ifndef FOCUS_ERR_PERCEP_PARAM\n#define FOCUS_ERR_PERCEP_PARAM     (-33)   /* 参数非法 (perception 本地扩展) */\n#endif\n\n/*\n * 每帧图像经过云端检测 + 去抖后输出一个 Observation。\n * 对严格/鼓励两种模式完全相同 (模式差异是赵思涵 behavior 模块的事)。\n */\ntypedef struct {\n    bool     person_present;       /* 画面中是否有人 */\n    float    person_bbox[4];       /* 人体边界框 (x,y,w,h) 归一化 [0-1] */\n    bool     phone_detected;       /* 是否检测到手机 */\n    bool     phone_near_hand;      /* 手机是否在手部区域 */\n    float    head_pitch;           /* 头部俯仰角 (度, 负=低头 正=仰头) */\n    float    head_yaw;             /* 头部偏航角 (度) */\n    float    hand_motion_score;    /* 手部运动量 [0-1] */\n    float    confidence;           /* 整体置信度 [0-1] */\n    uint32_t timestamp_ms;         /* 时间戳 (毫秒) */\n} observation_t;\n\n/* 初始化: 配置 API URL 和 Key, 清空历史与去抖状态。返回 FOCUS_OK=成功 */\nint  perception_init(const char *api_url, const char *api_key);\n\n/* 核心: 一张 JPEG → 云端 API → 去抖 → 输出 observation_t */\nint  perception_process(uint8_t *jpeg, size_t jpeg_len, observation_t *out);\n\n/* 取最近 N 条 observation (从旧到新), 供 behavior 时序分析。返回实际条数 */\nint  perception_get_history(observation_t *buf, int n);\n\n#endif /* API_PERCEPTION_H */\n"}

---

### [2026-08-28 16:12:01] 用户

[工具结果] File created successfully at: C:\temp\focus_behavior\api\perception.h (file state is current in your context — no need to Read it back)

---

### [2026-08-28 16:12:10] AI

[工具调用] Write: {"file_path": "C:\\temp\\focus_behavior\\behavior\\behavior_internal.h", "content": "/****************************************************************************\n * FOCUS AIoT - 行为分析模块内部声明 (behavior/behavior_internal.h)\n *\n * 负责人: 赵思涵\n * 说明:   对应任务书里的「behavior/behavior.h (内部声明, 可选)」。\n *         为避免与公开接口 api/behavior.h 混淆, 命名为 *_internal.h。\n *         这里暴露的 mode_config_t 与可测函数仅供 behavior.c / behavior_config.c\n *         与单测 (tests/test_behavior.c) 使用，不对其他模块开放。\n ****************************************************************************/\n\n#ifndef BEHAVIOR_INTERNAL_H\n#define BEHAVIOR_INTERNAL_H\n\n#include \"../api/behavior.h\"\n#include \"../api/perception.h\"\n\n/*\n * 模式参数配置表 (严格 / 鼓励 各一套)。\n * 两种模式共用同一套分析框架, 只换配置, 不换代码。\n */\ntypedef struct {\n    int   phone_glance_sec;      /* 看手机判定阈值 (秒) */\n    int   phone_playing_sec;     /* 玩手机判定阈值 (秒) */\n    int   away_sec;              /* 离座判定阈值 (秒) */\n    int   drowsy_sec;            /* 瞌睡判定阈值 (秒) */\n    int   remind_cooldown_sec;   /* 提醒最小间隔 (秒) */\n    int   remind_after_n_times;  /* 累计几次分心才提醒 1 次 */\n    int   focus_milestone_min;   /* 专注里程碑间隔 (分钟, 0=不启用) */\n    int   score_penalty_phone;   /* 玩手机扣分 */\n    int   score_penalty_away;    /* 离座扣分 */\n    int   score_penalty_drowsy;  /* 瞌睡扣分 */\n    int   score_bonus_milestone; /* 专注里程碑加分 */\n    bool  enable_milestone;      /* 是否启用里程碑鼓励 */\n    const char *const *messages; /* 提醒话术 (按 status_t 索引) */\n} mode_config_t;\n\n/* 配置表 (定义在 behavior_config.c) */\nextern const mode_config_t g_mode_configs[MODE_COUNT];\n\n/*\n * 时序判定核心 (可测): 输入一个 observation 序列 (旧→新), 输出 study_state_t。\n * behavior_analyze() 内部调用此函数; 单测直接喂合成历史即可, 无需依赖\n * perception / 硬件 / 网络。\n */\nint  behavior_analyze_history(const observation_t *history, int count,\n                              study_state_t *out);\n\n#endif /* BEHAVIOR_INTERNAL_H */\n"}

---

### [2026-08-28 16:12:18] 用户

[工具结果] File created successfully at: C:\temp\focus_behavior\behavior\behavior_internal.h (file state is current in your context — no need to Read it back)

---

### [2026-08-28 16:12:28] AI

[工具调用] Write: {"file_path": "C:\\temp\\focus_behavior\\behavior\\behavior_config.c", "content": "/****************************************************************************\n * FOCUS AIoT - 行为分析模块配置表 (behavior/behavior_config.c)\n *\n * 负责人: 赵思涵\n * 职责:   集中管理 严格 / 鼓励 两套阈值、扣分、话术 (对应任务书任务 1:\n *         「迁移配置表」)。时序引擎 behavior.c 只读此表, 不硬编码参数。\n *\n * 依据: 产品方案与分工_v2.md 第七节。\n ****************************************************************************/\n\n#include \"../api/behavior.h\"\n#include \"behavior_internal.h\"\n\n/* 严格模式话术 (指令式) */\nstatic const char *const strict_messages[STATUS_COUNT] = {\n    [FOCUSED]        = NULL,\n    [GLANCING_PHONE] = NULL,\n    [PLAYING_PHONE]  = \"请放下手机!\",\n    [AWAY]           = \"请回到座位!\",\n    [DROWSY]         = \"请注意坐姿!\",\n};\n\n/* 鼓励模式话术 (鼓励式) */\nstatic const char *const gentle_messages[STATUS_COUNT] = {\n    [FOCUSED]        = NULL,\n    [GLANCING_PHONE] = NULL,\n    [PLAYING_PHONE]  = \"休息好了就继续吧~\",\n    [AWAY]           = \"等你回来哦~\",\n    [DROWSY]         = \"要不要起来活动一下?\",\n};\n\nconst mode_config_t g_mode_configs[MODE_COUNT] = {\n    [MODE_STRICT] = {\n        .phone_glance_sec     = 8,\n        .phone_playing_sec    = 8,\n        .away_sec             = 10,\n        .drowsy_sec           = 8,\n        .remind_cooldown_sec  = 30,\n        .remind_after_n_times = 1,      /* 每次分心都提醒 */\n        .focus_milestone_min  = 0,      /* 不启用里程碑 */\n        .score_penalty_phone  = -15,\n        .score_penalty_away   = -10,\n        .score_penalty_drowsy = -20,\n        .score_bonus_milestone = 0,\n        .enable_milestone     = false,\n        .messages             = strict_messages,\n    },\n    [MODE_GENTLE] = {\n        .phone_glance_sec     = 15,\n        .phone_playing_sec    = 15,\n        .away_sec             = 20,\n        .drowsy_sec           = 12,\n        .remind_cooldown_sec  = 120,\n        .remind_after_n_times = 3,      /* 累计 3 次才提醒 1 次 */\n        .focus_milestone_min  = 30,     /* 每专注 30 分钟鼓励一次 */\n        .score_penalty_phone  = -5,\n        .score_penalty_away   = -3,\n        .score_penalty_drowsy = -8,\n        .score_bonus_milestone = 5,\n        .enable_milestone     = true,\n        .messages             = gentle_messages,\n    },\n};\n"}

---

### [2026-08-28 16:13:46] 用户

[工具结果] File created successfully at: C:\temp\focus_behavior\behavior\behavior_config.c (file state is current in your context — no need to Read it back)

---

### [2026-08-28 16:13:50] AI

[思考] Now the main behavior.c file.

---

### [2026-08-28 16:14:15] AI

[工具调用] Write: {"file_path": "C:\\temp\\focus_behavior\\behavior\\behavior.c", "content": "/****************************************************************************\n * FOCUS AIoT - 行为分析模块 (behavior/behavior.c)\n *\n * 负责人: 赵思涵\n * 职责:   从一连串 observation_t (带时间戳的历史) 做时序判定, 输出\n *         study_state_t —— 即「时间维度」的动作/行为识别。只做行为推理,\n *         不做单帧静态识别 (那是周礼航 perception 模块的事)。\n *\n * 输入:   observation_t 序列 (来自 perception_get_history(), 旧→新)\n * 输出:   study_state_t (status + action + message + 评分变化)\n *\n * 关键逻辑:\n *   - 时序判定: 从最新帧往前扫「连续命中」长度, 换算成持续时长(毫秒)。\n *   - 优先级:  AWAY > 玩手机 > 看手机 > 瞌睡 > 专注里程碑 > FOCUSED。\n *   - 提醒冷却 remind_cooldown_sec + 累计提醒 remind_after_n_times。\n *   - 专注里程碑 (鼓励模式): 连续专注满 focus_milestone_min 分钟鼓励一次, 去重。\n *   - 同帧防重: 相同最新帧时间戳 → 返回缓存, 不重复计数/提醒。\n *   - uint32 时间回绕: 一律用 (int32_t)(a - b) 求跨度, 对 <2^31ms 的回绕正确。\n ****************************************************************************/\n\n#include <stdbool.h>\n#include <stdint.h>\n#include <stddef.h>\n#include <string.h>\n#include <stdio.h>\n\n#include \"../api/behavior.h\"\n#include \"../api/perception.h\"\n#include \"behavior_internal.h\"\n\n/* ------------------------------------------------------------------ */\n/* 内部配置                                                            */\n/* ------------------------------------------------------------------ */\n#define HISTORY_MAX               60\n#define DEFAULT_FRAME_INTERVAL_MS 5000u   /* 单帧/异常时按 5s/帧估 */\n#define MAX_FRAME_INTERVAL_MS     60000u\n#define HAND_MOTION_PLAY_THRESH   0.30f   /* 手部运动量阈值: 玩手机 */\n#define DROWSY_PITCH_STRICT       45.0f   /* 瞌睡俯仰角阈值(度) */\n#define DROWSY_PITCH_GENTLE       52.0f\n\n/* ------------------------------------------------------------------ */\n/* 模块状态 (单例; 由主循环串行调用, 无重入)                            */\n/* ------------------------------------------------------------------ */\nstatic mode_t        g_mode = MODE_STRICT;\nstatic study_state_t g_last_state;           /* 同帧防重缓存 */\nstatic uint32_t      g_last_frame_ts = 0;    /* 上次分析的最新帧时间戳 */\nstatic uint32_t      g_last_remind_ms = 0;   /* 上次提醒时间戳 */\nstatic int           g_distract_count = 0;   /* 累计分心次数(自上次提醒) */\nstatic bool          g_in_focus = false;     /* 是否处于专注段 */\nstatic uint32_t      g_focus_start_ms = 0;   /* 当前专注段起点 */\nstatic int           g_last_milestone_min = 0; /* 已庆祝的最近里程碑(去重) */\n\n/* ------------------------------------------------------------------ */\n/* 时序谓词 (从最新帧往前扫连续命中)                                    */\n/* ------------------------------------------------------------------ */\n\ntypedef bool (*obs_pred_t)(const observation_t *o, float arg);\n\nstatic bool pred_away(const observation_t *o, float arg)\n{\n    (void)arg;\n    return !o->person_present;\n}\n\nstatic bool pred_phone(const observation_t *o, float arg)\n{\n    (void)arg;\n    return o->phone_detected && o->phone_near_hand;\n}\n\nstatic bool pred_drowsy(const observation_t *o, float pitch_thresh)\n{\n    return o->person_present && (o->head_pitch > pitch_thresh);\n}\n\n/* 连续命中长度 (从最新帧往前数, 遇不命中即停) */\nstatic int streak_from_tail(const observation_t *h, int n,\n                            obs_pred_t pred, float arg)\n{\n    int s = 0;\n    for (int i = n - 1; i >= 0; i--) {\n        if (pred(&h[i], arg)) {\n            s++;\n        } else {\n            break;\n        }\n    }\n    return s;\n}\n\n/* 相邻帧间隔估计(毫秒); 单帧或间隔异常回退到默认 5s */\nstatic uint32_t estimate_frame_interval_ms(const observation_t *h, int n)\n{\n    if (n < 2) {\n        return DEFAULT_FRAME_INTERVAL_MS;\n    }\n    int32_t d = (int32_t)(h[n - 1].timestamp_ms - h[n - 2].timestamp_ms);\n    if (d <= 0 || d > (int32_t)MAX_FRAME_INTERVAL_MS) {\n        return DEFAULT_FRAME_INTERVAL_MS;\n    }\n    return (uint32_t)d;\n}\n\n/* 连续命中时段的持续毫秒数 = 跨度 + 一个帧间隔 (命中至少始于最老那帧) */\nstatic uint32_t streak_duration_ms(const observation_t *h, int n, int streak,\n                                   uint32_t interval_ms)\n{\n    if (streak <= 0) {\n        return 0;\n    }\n    if (streak == 1) {\n        return interval_ms;\n    }\n\n    int32_t span = (int32_t)(h[n - 1].timestamp_ms - h[n - streak].timestamp_ms);\n    if (span <= 0) {\n        /* 时间回绕或乱序, 回退按帧数估 */\n        span = (int32_t)(streak - 1) * (int32_t)interval_ms;\n    }\n    return (uint32_t)span + interval_ms;\n}\n\n/* 连续命中段内手部运动均值 */\nstatic float average_hand_motion(const observation_t *h, int n, int streak)\n{\n    if (streak <= 0) {\n        return 0.0f;\n    }\n    float sum = 0.0f;\n    int start = n - streak;\n    for (int i = start; i < n; i++) {\n        sum += h[i].hand_motion_score;\n    }\n    return sum / (float)streak;\n}\n\nstatic bool is_distraction_status(status_t s)\n{\n    return s == PLAYING_PHONE || s == AWAY || s == DROWSY;\n}\n\nstatic int penalty_for(const mode_config_t *cfg, status_t s)\n{\n    switch (s) {\n    case PLAYING_PHONE: return cfg->score_penalty_phone;\n    case AWAY:          return cfg->score_penalty_away;\n    case DROWSY:        return cfg->score_penalty_drowsy;\n    default:            return 0;\n    }\n}\n\n/* ------------------------------------------------------------------ */\n/* 对外接口                                                            */\n/* ------------------------------------------------------------------ */\n\nint behavior_init(mode_t mode)\n{\n    if (mode != MODE_STRICT && mode != MODE_GENTLE) {\n        return FOCUS_ERR_BEHAVIOR_PARAM;\n    }\n    g_mode = mode;\n\n    memset(&g_last_state, 0, sizeof(g_last_state));\n    g_last_state.status = FOCUSED;\n    g_last_frame_ts = 0;\n    g_last_remind_ms = 0;\n    g_distract_count = 0;\n    g_in_focus = false;\n    g_focus_start_ms = 0;\n    g_last_milestone_min = 0;\n    return FOCUS_OK;\n}\n\nint behavior_analyze(study_state_t *out)\n{\n    observation_t history[HISTORY_MAX];\n    int n = perception_get_history(history, HISTORY_MAX);\n    return behavior_analyze_history(history, n, out);\n}\n\nint behavior_analyze_history(const observation_t *history, int count,\n                             study_state_t *out)\n{\n    if (!out) {\n        return FOCUS_ERR_BEHAVIOR_PARAM;\n    }\n    if (!history || count <= 0) {\n        /* 空历史 → 视为专注, 不误报 */\n        memset(out, 0, sizeof(*out));\n        out->status = FOCUSED;\n        out->action = NONE;\n        return FOCUS_OK;\n    }\n\n    const mode_config_t *cfg = &g_mode_configs[g_mode];\n    const observation_t *latest = &history[count - 1];\n    float drowsy_pitch = (g_mode == MODE_STRICT)\n                         ? DROWSY_PITCH_STRICT : DROWSY_PITCH_GENTLE;\n\n    /* 同帧防重: 相同最新帧时间戳 → 直接返回缓存结果 */\n    if (g_last_frame_ts != 0 && latest->timestamp_ms == g_last_frame_ts) {\n        *out = g_last_state;\n        return FOCUS_OK;\n    }\n    g_last_frame_ts = latest->timestamp_ms;\n\n    uint32_t interval_ms = estimate_frame_interval_ms(history, count);\n\n    int away_streak   = streak_from_tail(history, count, pred_away, 0.0f);\n    int phone_streak  = streak_from_tail(history, count, pred_phone, 0.0f);\n    int drowsy_streak = streak_from_tail(history, count, pred_drowsy, drowsy_pitch);\n\n    uint32_t away_ms   = streak_duration_ms(history, count, away_streak, interval_ms);\n    uint32_t phone_ms  = streak_duration_ms(history, count, phone_streak, interval_ms);\n    uint32_t drowsy_ms = streak_duration_ms(history, count, drowsy_streak, interval_ms);\n\n    float avg_motion = average_hand_motion(history, count, phone_streak);\n    bool has_hand_motion = avg_motion > HAND_MOTION_PLAY_THRESH;\n\n    /* 状态判定: 优先级 AWAY > 玩手机 > 看手机 > 瞌睡 > 专注 */\n    status_t status;\n    if (away_ms >= (uint32_t)cfg->away_sec * 1000u) {\n        status = AWAY;\n    } else if (phone_ms >= (uint32_t)cfg->phone_playing_sec * 1000u\n               && has_hand_motion) {\n        status = PLAYING_PHONE;\n    } else if (phone_ms > 0) {\n        status = GLANCING_PHONE;\n    } else if (drowsy_ms >= (uint32_t)cfg->drowsy_sec * 1000u) {\n        status = DROWSY;\n    } else {\n        status = FOCUSED;\n    }\n\n    study_state_t st;\n    memset(&st, 0, sizeof(st));\n    st.status = status;\n    st.action = NONE;\n\n    /* 专注段维护 (里程碑用, 跨多次分析累积) */\n    if (status == FOCUSED) {\n        if (!g_in_focus) {\n            g_in_focus = true;\n            g_focus_start_ms = latest->timestamp_ms;\n        }\n        int32_t focus_ms = (int32_t)(latest->timestamp_ms - g_focus_start_ms);\n        if (focus_ms < 0) {\n            focus_ms = 0;\n        }\n        int focus_min = (int)((uint32_t)focus_ms / 60000u);\n\n        if (cfg->enable_milestone && cfg->focus_milestone_min > 0\n            && focus_min >= cfg->focus_milestone_min\n            && focus_min % cfg->focus_milestone_min == 0\n            && focus_min > g_last_milestone_min) {\n            st.action = ENCOURAGE;\n            st.milestone_reached = true;\n            st.milestone_minutes = focus_min;\n            st.focus_score_delta = (int8_t)cfg->score_bonus_milestone;\n            snprintf(st.message, sizeof(st.message),\n                     \"已专注学习 %d 分钟,继续保持!\", focus_min);\n            g_last_milestone_min = focus_min;\n        }\n    } else {\n        g_in_focus = false;   /* 非专注 → 清空专注段 */\n    }\n\n    /* 分心处理: 新片段计数 + 扣分 + 提醒门控 */\n    if (is_distraction_status(status)) {\n        bool was_distraction = is_distraction_status(g_last_state.status);\n        if (status != g_last_state.status && !was_distraction) {\n            /* 新的分心片段 (从专注/看手机 转入): 计数 + 扣分各一次 */\n            g_distract_count++;\n            st.focus_score_delta = (int8_t)penalty_for(cfg, status);\n        }\n\n        uint32_t now = latest->timestamp_ms;\n        bool cooldown_ok =\n            (g_last_remind_ms == 0) ||\n            ((int32_t)(now - g_last_remind_ms)\n             >= (int32_t)((uint32_t)cfg->remind_cooldown_sec * 1000u));\n\n        if (g_distract_count >= cfg->remind_after_n_times && cooldown_ok) {\n            st.action = REMIND;\n            const char *msg = cfg->messages[status];\n            if (msg) {\n                snprintf(st.message, sizeof(st.message), \"%s\", msg);\n            }\n            g_last_remind_ms = now;\n            g_distract_count = 0;\n        }\n    }\n\n    g_last_state = st;\n    *out = st;\n    return FOCUS_OK;\n}\n"}

---

### [2026-08-28 16:15:10] 用户

[工具结果] File created successfully at: C:\temp\focus_behavior\behavior\behavior.c (file state is current in your context — no need to Read it back)

---

### [2026-08-28 16:15:22] AI

[思考] Now the test file.

---

### [2026-08-28 16:15:45] AI

[工具调用] Write: {"file_path": "C:\\temp\\focus_behavior\\tests\\test_behavior.c", "content": "/****************************************************************************\n * FOCUS AIoT - 行为分析模块单测 (tests/test_behavior.c)\n *\n * 负责人: 赵思涵\n * 说明:   纯 C 单测, 不依赖硬件/网络/cJSON/perception。直接喂合成\n *         observation 历史给 behavior_analyze_history(), 断言输出的\n *         study_state_t。behavior_analyze() 依赖的 perception_get_history()\n *         在此以桩替代 (单测不走到它)。\n *\n * 编译 (mock 单测):\n *   gcc -Wall -Wextra -Werror \\\n *       behavior/behavior.c behavior/behavior_config.c tests/test_behavior.c \\\n *       -o test_behavior\n *   ./test_behavior\n ****************************************************************************/\n\n#include <stdio.h>\n#include <string.h>\n#include <stdbool.h>\n#include <stdint.h>\n\n#include \"../api/behavior.h\"\n#include \"../api/perception.h\"\n#include \"../behavior/behavior_internal.h\"\n\n/* 桩: behavior_analyze() 会调它; 单测走 behavior_analyze_history, 用不到 */\nint perception_get_history(observation_t *buf, int n)\n{\n    (void)buf;\n    (void)n;\n    return 0;\n}\n\nstatic int g_fail = 0;\n\n#define CHECK(cond) do {                                          \\\n    if (!(cond)) {                                                \\\n        printf(\"  FAIL %s:%d  %s\\n\", __FILE__, __LINE__, #cond);  \\\n        g_fail++;                                                 \\\n    }                                                             \\\n} while (0)\n\n#define CHECK_STR(a, b) do {                                      \\\n    if (strcmp((a), (b)) != 0) {                                  \\\n        printf(\"  FAIL %s:%d  str: got \\\"%s\\\" want \\\"%s\\\"\\n\",     \\\n               __FILE__, __LINE__, (a), (b));                     \\\n        g_fail++;                                                 \\\n    }                                                             \\\n} while (0)\n\n/* 构造一条 observation */\nstatic observation_t obs(uint32_t ts, bool person, bool phone, bool near_hand,\n                         float pitch, float motion)\n{\n    observation_t o;\n    memset(&o, 0, sizeof(o));\n    o.timestamp_ms     = ts;\n    o.person_present   = person;\n    o.phone_detected   = phone;\n    o.phone_near_hand  = near_hand;\n    o.head_pitch       = pitch;\n    o.hand_motion_score = motion;\n    o.confidence       = 0.9f;\n    return o;\n}\n\n/* ---- 测试用例 ---- */\n\nstatic void test_empty(void)\n{\n    study_state_t st;\n    observation_t dummy;\n    memset(&dummy, 0, sizeof(dummy));\n\n    CHECK(behavior_init(MODE_STRICT) == FOCUS_OK);\n    CHECK(behavior_analyze_history(&dummy, 0, &st) == FOCUS_OK);\n    CHECK(st.status == FOCUSED);\n    CHECK(st.action == NONE);\n}\n\nstatic void test_strict_away(void)\n{\n    observation_t h[3] = {\n        obs(1000,  false, false, false, 0.0f, 0.0f),\n        obs(6000,  false, false, false, 0.0f, 0.0f),\n        obs(11000, false, false, false, 0.0f, 0.0f),\n    };\n    study_state_t st;\n\n    CHECK(behavior_init(MODE_STRICT) == FOCUS_OK);\n    CHECK(behavior_analyze_history(h, 3, &st) == FOCUS_OK);\n    CHECK(st.status == AWAY);\n    CHECK(st.action == REMIND);\n    CHECK(st.focus_score_delta == -10);\n    CHECK_STR(st.message, \"请回到座位!\");\n}\n\nstatic void test_strict_phone(void)\n{\n    observation_t h[3] = {\n        obs(1000,  true, true, true, 0.0f, 0.6f),\n        obs(6000,  true, true, true, 0.0f, 0.6f),\n        obs(11000, true, true, true, 0.0f, 0.6f),\n    };\n    study_state_t st;\n\n    CHECK(behavior_init(MODE_STRICT) == FOCUS_OK);\n    CHECK(behavior_analyze_history(h, 3, &st) == FOCUS_OK);\n    CHECK(st.status == PLAYING_PHONE);\n    CHECK(st.action == REMIND);\n    CHECK(st.focus_score_delta == -15);\n    CHECK_STR(st.message, \"请放下手机!\");\n}\n\nstatic void test_glancing(void)\n{\n    observation_t h[1] = { obs(1000, true, true, true, 0.0f, 0.1f) };\n    study_state_t st;\n\n    CHECK(behavior_init(MODE_STRICT) == FOCUS_OK);\n    CHECK(behavior_analyze_history(h, 1, &st) == FOCUS_OK);\n    CHECK(st.status == GLANCING_PHONE);\n    CHECK(st.action == NONE);\n    CHECK(st.focus_score_delta == 0);\n}\n\nstatic void test_strict_drowsy(void)\n{\n    observation_t h[3] = {\n        obs(1000,  true, false, false, 55.0f, 0.0f),\n        obs(6000,  true, false, false, 55.0f, 0.0f),\n        obs(11000, true, false, false, 55.0f, 0.0f),\n    };\n    study_state_t st;\n\n    CHECK(behavior_init(MODE_STRICT) == FOCUS_OK);\n    CHECK(behavior_analyze_history(h, 3, &st) == FOCUS_OK);\n    CHECK(st.status == DROWSY);\n    CHECK(st.action == REMIND);\n    CHECK(st.focus_score_delta == -20);\n    CHECK_STR(st.message, \"请注意坐姿!\");\n}\n\nstatic void test_strict_cooldown(void)\n{\n    observation_t away1[3] = {\n        obs(1000,  false, false, false, 0.0f, 0.0f),\n        obs(6000,  false, false, false, 0.0f, 0.0f),\n        obs(11000, false, false, false, 0.0f, 0.0f),\n    };\n    observation_t focus[1] = { obs(16000, true, false, false, 0.0f, 0.0f) };\n    observation_t away2[3] = {\n        obs(21000, false, false, false, 0.0f, 0.0f),\n        obs(26000, false, false, false, 0.0f, 0.0f),\n        obs(31000, false, false, false, 0.0f, 0.0f),\n    };\n    study_state_t st;\n\n    CHECK(behavior_init(MODE_STRICT) == FOCUS_OK);\n    CHECK(behavior_analyze_history(away1, 3, &st) == FOCUS_OK);\n    CHECK(st.action == REMIND);\n\n    CHECK(behavior_analyze_history(focus, 1, &st) == FOCUS_OK);\n    CHECK(st.status == FOCUSED);\n\n    CHECK(behavior_analyze_history(away2, 3, &st) == FOCUS_OK);\n    CHECK(st.status == AWAY);\n    CHECK(st.action == NONE);           /* 冷却期内, 抑制提醒 */\n    CHECK(st.focus_score_delta == -10); /* 但扣分仍按新片段计 */\n}\n\nstatic void test_gentle_accumulate(void)\n{\n    study_state_t st;\n    CHECK(behavior_init(MODE_GENTLE) == FOCUS_OK);\n\n    observation_t away1[5] = {\n        obs(1000,  false, false, false, 0.0f, 0.0f),\n        obs(6000,  false, false, false, 0.0f, 0.0f),\n        obs(11000, false, false, false, 0.0f, 0.0f),\n        obs(16000, false, false, false, 0.0f, 0.0f),\n        obs(21000, false, false, false, 0.0f, 0.0f),\n    };\n    observation_t focus_a[1] = { obs(26000, true, false, false, 0.0f, 0.0f) };\n    observation_t away2[5] = {\n        obs(31000, false, false, false, 0.0f, 0.0f),\n        obs(36000, false, false, false, 0.0f, 0.0f),\n        obs(41000, false, false, false, 0.0f, 0.0f),\n        obs(46000, false, false, false, 0.0f, 0.0f),\n        obs(51000, false, false, false, 0.0f, 0.0f),\n    };\n    observation_t focus_b[1] = { obs(56000, true, false, false, 0.0f, 0.0f) };\n    observation_t away3[5] = {\n        obs(61000, false, false, false, 0.0f, 0.0f),\n        obs(66000, false, false, false, 0.0f, 0.0f),\n        obs(71000, false, false, false, 0.0f, 0.0f),\n        obs(76000, false, false, false, 0.0f, 0.0f),\n        obs(81000, false, false, false, 0.0f, 0.0f),\n    };\n\n    CHECK(behavior_analyze_history(away1, 5, &st) == FOCUS_OK);\n    CHECK(st.status == AWAY);\n    CHECK(st.action == NONE);           /* 第 1 次, 未到累计阈值 */\n\n    CHECK(behavior_analyze_history(focus_a, 1, &st) == FOCUS_OK);\n    CHECK(st.status == FOCUSED);\n\n    CHECK(behavior_analyze_history(away2, 5, &st) == FOCUS_OK);\n    CHECK(st.status == AWAY);\n    CHECK(st.action == NONE);           /* 第 2 次 */\n\n    CHECK(behavior_analyze_history(focus_b, 1, &st) == FOCUS_OK);\n    CHECK(st.status == FOCUSED);\n\n    CHECK(behavior_analyze_history(away3, 5, &st) == FOCUS_OK);\n    CHECK(st.status == AWAY);\n    CHECK(st.action == REMIND);         /* 第 3 次, 触发提醒 */\n    CHECK_STR(st.message, \"等你回来哦~\");\n    CHECK(st.focus_score_delta == -3);\n}\n\nstatic void test_gentle_milestone(void)\n{\n    study_state_t st;\n    observation_t f1[1] = { obs(1000,    true, false, false, 0.0f, 0.0f) };\n    observation_t f2[1] = { obs(1801000, true, false, false, 0.0f, 0.0f) };\n    observation_t f3[1] = { obs(1806000, true, false, false, 0.0f, 0.0f) };\n\n    CHECK(behavior_init(MODE_GENTLE) == FOCUS_OK);\n    CHECK(behavior_analyze_history(f1, 1, &st) == FOCUS_OK);\n    CHECK(st.status == FOCUSED);\n    CHECK(st.action == NONE);\n\n    CHECK(behavior_analyze_history(f2, 1, &st) == FOCUS_OK);\n    CHECK(st.status == FOCUSED);\n    CHECK(st.action == ENCOURAGE);\n    CHECK(st.milestone_reached == true);\n    CHECK(st.milestone_minutes == 30);\n    CHECK(st.focus_score_delta == 5);\n\n    CHECK(behavior_analyze_history(f3, 1, &st) == FOCUS_OK);\n    CHECK(st.action == NONE);           /* 里程碑去重, 不重复庆祝 */\n}\n\nint main(void)\n{\n    test_empty();\n    test_strict_away();\n    test_strict_phone();\n    test_glancing();\n    test_strict_drowsy();\n    test_strict_cooldown();\n    test_gentle_accumulate();\n    test_gentle_milestone();\n\n    if (g_fail == 0) {\n        printf(\"ALL TESTS PASSED\\n\");\n        return 0;\n    }\n    printf(\"%d FAILED\\n\", g_fail);\n    return 1;\n}\n"}

---

### [2026-08-28 16:16:46] 用户

[工具结果] File created successfully at: C:\temp\focus_behavior\tests\test_behavior.c (file state is current in your context — no need to Read it back)

---

### [2026-08-28 16:16:49] AI

Now compile and run the tests to verify:

---

### [2026-08-28 16:16:50] AI

[工具调用] Bash: {"command": "cd /c/temp/focus_behavior && gcc -Wall -Wextra -Werror behavior/behavior.c behavior/behavior_config.c tests/test_behavior.c -o test_behavior 2>&1 && echo \"=== BUILD OK ===\" && ./test_behavior 2>&1; echo \"exit=$?\"", "description": "Compile behavior module with -Werror and run unit tests"}

---

### [2026-08-28 16:17:47] 用户

[工具结果] === BUILD OK ===
ALL TESTS PASSED
exit=0
Shell cwd was reset to C:\Users\user

---

### [2026-08-28 16:17:52] AI

[思考] Compiles clean with -Werror and all tests pass. Now let me also verify the mock perception test still passes (to confirm nothing broke), and write the BUILD_INTEGRATION.md and README.md.

Actually, the perception module is unchanged — I don't need to re-verify it. But let me quickly confirm the perception test still compiles/passes to be safe? Not necessary since I didn't touch it. I'll skip.

Now write BUILD_INTEGRATION.md and README.md for the behavior module, mirroring the focus_perception style.

Let me write README.md first.

---

### [2026-08-28 16:17:52] AI

编译零警告、全部测试通过。现在补上接入文档和 README，让它是完整「成品」。

---

### [2026-08-28 16:18:09] AI

[工具调用] Write: {"file_path": "C:\\temp\\focus_behavior\\README.md", "content": "# 行为分析模块 (behavior) —— 赵思涵 · 成品\n\n这是「FOCUS AIoT」里 **行为分析层** 的完整实现。它消费周礼航\n`perception` 模块输出的连续 `observation_t`（带时间戳的历史），做**时间维度**\n的动作/行为识别，输出 `study_state_t`，供万思源的 `state_machine` 驱动\n计时/UI/语音/报告。\n\n> 依据文档：`产品方案与分工_v2.md`（第七节）、`DEVELOPMENT_TASKS (2).md`\n> （第三节，2026-08-19）。只做「时间」上的行为推理，**不做单帧静态识别**\n> （那是周礼航的事）。\n\n## 文件清单\n\n```\nfocus_behavior/\n├── api/behavior.h             公开接口 (study_state_t + 3 枚举 + 2 函数)\n│                                ⚠️ 参考拷贝, 勿覆盖仓库冻结版\n├── api/perception.h           依赖的 observation_t 定义 (参考拷贝, 供独立编译)\n├── behavior/\n│   ├── behavior.c             主实现 (时序判定 + 冷却 + 累计 + 里程碑)\n│   ├── behavior_internal.h    内部声明 (mode_config_t + 可测函数)\n│   └── behavior_config.c      严格/鼓励 两套配置表 + 话术\n├── tests/test_behavior.c       mock 单测 (不依赖硬件/网络/cJSON/perception)\n├── BUILD_INTEGRATION.md        Makefile/CMakeLists/Kconfig 接入 diff\n└── README.md\n```\n\n## 动作识别（时序判定）\n\n`behavior_analyze()` 每次被调用时，从 `perception_get_history()` 拉取最近 60 条\nobservation，**从最新帧往前扫「连续命中」长度**，换算成持续时长，再按优先级\n判定状态：\n\n| 状态 | 触发条件（严格 / 鼓励） |\n|---|---|\n| `AWAY` 离座 | 连续无人 ≥ 10s / 20s |\n| `PLAYING_PHONE` 玩手机 | 手机在手 ≥ 8s / 15s 且手部运动 > 0.3 |\n| `GLANCING_PHONE` 看手机 | 手机在手但未达玩手机阈值（不提醒） |\n| `DROWSY` 瞌睡 | 头部俯仰角 > 45° / 52° 持续 ≥ 8s / 12s |\n| `FOCUSED` 专注 | 其余情况 |\n\n**判定优先级**：AWAY > 玩手机 > 看手机 > 瞌睡 > 专注里程碑 > FOCUSED。\n\n## 两个对外接口（冻结签名）\n\n```c\nint  behavior_init(mode_t mode);            // MODE_STRICT / MODE_GENTLE\nint  behavior_analyze(study_state_t *out);  // 拉取历史 → 时序判定 → 输出\n```\n\n返回值：`FOCUS_OK`(0) 成功；`FOCUS_ERR_BEHAVIOR_PARAM`(-40) 参数非法\n（来自 `api/error.h`，此处兜底定义）。\n\n## 关键设计\n\n- **纯 C 规则引擎**：不依赖深度学习，就是时间窗口统计，约 200 行，在 ESP32\n  上几乎零开销。\n- **严格 / 鼓励双引擎**：共用同一套分析框架，只换 `mode_config_t` 配置表\n  （阈值、扣分、话术、里程碑开关），不换代码。\n- **提醒门控**：冷却 `remind_cooldown_sec`（严格 30s / 鼓励 120s）+\n  累计 `remind_after_n_times`（严格 1 次 / 鼓励 3 次才提醒 1 次）。\n- **专注里程碑**（仅鼓励模式）：连续专注满 30 分钟鼓励一次，`g_last_milestone_min`\n  去重，不重复庆祝。\n- **同帧防重**：相同最新帧时间戳 → 直接返回 `g_last_state` 缓存，避免主循环\n  重复计数/重复提醒。\n- **uint32 时间回绕**：一律用 `(int32_t)(a - b)` 求时间跨度，对 <2^31ms\n  （约 24.8 天）内的回绕正确。\n- **分心扣分按片段计**：从专注/看手机「转入」分心状态时才扣一次分（`g_distract_count`\n  计数 + `focus_score_delta` 扣分各一次），持续分心不重复扣。\n\n## 本地单测\n\n```bash\ncd focus_behavior\n\ngcc -Wall -Wextra -Werror \\\n    behavior/behavior.c behavior/behavior_config.c tests/test_behavior.c \\\n    -o test_behavior\n./test_behavior\n```\n\n预期 `ALL TESTS PASSED`。覆盖：空历史、严格离座/玩手机/看手机/瞌睡、冷却期内\n抑制提醒、鼓励累计 3 次才提醒、专注里程碑 + 去重。\n\n## 接入仓库（openvela 真机）\n\n1. 把 `behavior/behavior.c`、`behavior/behavior_config.c`、\n   `behavior/behavior_internal.h` 放进 `app/hello_app/behavior/`。\n2. `api/behavior.h` **不要覆盖**，用仓库冻结版（字段/签名必须一致）。\n3. 按 `BUILD_INTEGRATION.md` 加 `CSRCS`（`behavior.c` + `behavior_config.c`）。\n4. 主入口启动时调 `behavior_init(MODE_STRICT)`（或按选择传 `MODE_GENTLE`），\n   监测循环里每帧调 `behavior_analyze(&study_state)` 消费结果。\n\n## 联调顺序\n\n先跟周礼航联调（确认 `perception_get_history()` 返回的历史字段/时间戳正确）→\n再跟万思源联调（确认 `study_state_t` 字段与状态机消费一致）→ 最后全链路：\n真实 observation → behavior → state_machine → UI 上屏。\n"}

---

### [2026-08-28 16:19:17] 用户

[工具结果] File created successfully at: C:\temp\focus_behavior\README.md (file state is current in your context — no need to Read it back)

---

### [2026-08-28 16:19:26] AI

[工具调用] Write: {"file_path": "C:\\temp\\focus_behavior\\BUILD_INTEGRATION.md", "content": "# 构建接入 (Makefile / CMakeLists)\n\n把 `behavior/` 接进仓库，只需加源文件即可，**无需 Kconfig 二选一**（behavior\n是纯逻辑，没有 mock/真实双路径；它依赖的 `perception_get_history()` 已由\n周礼航的强符号自动覆盖 `core/mock.c` 的 weak 桩）。\n\n## 1. 源文件入编\n\n**Makefile**（`app/hello_app/Makefile`）的 `CSRCS`：\n\n```make\nCSRCS += behavior/behavior.c\nCSRCS += behavior/behavior_config.c\n```\n\n**CMakeLists.txt**（`app/hello_app/CMakeLists.txt`）：\n\n```cmake\nset(CSRCS ${CSRCS} behavior/behavior.c)\nset(CSRCS ${CSRCS} behavior/behavior_config.c)\n```\n\n## 2. 依赖说明\n\n| 依赖 | 来源 | 说明 |\n|---|---|---|\n| `perception_get_history()` | 周礼航 `api/perception.h` | 强符号，自动覆盖 `core/mock.c` 的 weak 桩 |\n| `observation_t` | 周礼航 `api/perception.h` | 行为分析的输入 |\n| `g_mode_configs` / `mode_config_t` | 本模块 `behavior_config.c` | 严格/鼓励配置表 |\n\n无外部库依赖（不需要 cJSON、不需要网络），行为分析是纯 C 规则引擎。\n\n## 3. host 单测（不需要硬件/网络）\n\n```bash\ngcc -Wall -Wextra -Werror \\\n    behavior/behavior.c behavior/behavior_config.c tests/test_behavior.c \\\n    -o test_behavior\n./test_behavior\n```\n\n## 4. 主循环调用方式（供万思源）\n\n```c\n#include \"api/behavior.h\"\n\nstudy_state_t st;\n\nbehavior_init(MODE_STRICT);          /* 启动时调用一次 */\n\nwhile (monitoring) {\n    behavior_analyze(&st);           /* 每收到一帧 observation 调用一次 */\n    if (st.action == REMIND) {\n        play_reminder(st.message);   /* 触发提醒 */\n    }\n    if (st.milestone_reached) {\n        play_encouragement(st.milestone_minutes);  /* 鼓励模式里程碑 */\n    }\n}\n```\n"}

---

### [2026-08-28 16:19:26] 用户

[工具结果] File created successfully at: C:\temp\focus_behavior\BUILD_INTEGRATION.md (file state is current in your context — no need to Read it back)

---

### [2026-08-28 16:19:30] AI

[思考] Now let me verify the final directory structure and do a final sanity check.

---

### [2026-08-28 16:19:31] AI

[工具调用] Bash: {"command": "cd /c/temp/focus_behavior && find . -type f | sort && echo \"=== 重新编译 + 运行 (最终确认) ===\" && gcc -Wall -Wextra -Werror behavior/behavior.c behavior/behavior_config.c tests/test_behavior.c -o test_behavior && ./test_behavior", "description": "List final file structure and re-run final build+test"}

---

### [2026-08-28 16:19:32] 用户

[工具结果] ./BUILD_INTEGRATION.md
./README.md
./api/behavior.h
./api/perception.h
./behavior/behavior.c
./behavior/behavior_config.c
./behavior/behavior_internal.h
./test_behavior.exe
./tests/test_behavior.c
=== 重新编译 + 运行 (最终确认) ===
ALL TESTS PASSED

---

### [2026-08-28 16:19:41] AI

完成 ✅ 已在 `C:\temp\focus_behavior` 建好完整的**行为分析模块**（赵思涵那部分），并实测通过。

## 这是什么

周礼航的 `perception` 负责「一张图里有什么」，缺的是把**连续帧串起来识别动作**的模块——就是这个。它读 `perception_get_history()` 的历史序列，输出动作状态。

## 识别出的动作

| 动作 | 判断条件 |
|---|---|
| 离座 AWAY | 连续无人 ≥10s |
| 玩手机 PLAYING_PHONE | 手机在手 ≥8s 且手在动 |
| 看手机 GLANCING_PHONE | 手机在手但时间短（不提醒） |
| 瞌睡 DROWSY | 头仰角 >45° 持续 ≥8s |
| 专注 FOCUSED | 其余 |

严格/鼓励两种模式自动切换（阈值、话术、扣分、里程碑都不同）。

## 文件

```
C:\temp\focus_behavior\
├── api\behavior.h          公开接口
├── api\perception.h        依赖的 observation 定义（参考拷贝）
├── behavior\behavior.c     时序引擎
├── behavior\behavior_config.c  严格/鼓励配置表
├── behavior\behavior_internal.h
├── tests\test_behavior.c   单测（8 个用例）
├── BUILD_INTEGRATION.md    接入 Makefile 方法
└── README.md
```

## 验证结果

- 编译 `-Wall -Wextra -Werror` **零警告**
- 单测 **8 个用例全部通过**（空历史/离座/玩手机/看手机/瞌睡/冷却/累计提醒/里程碑）

下一步我可以：把它和 `focus_perception` 串成一条全链路 demo（mock 喂帧→识别动作），或按仓库的 `Makefile` 帮你写好接入 diff。要哪个？

---

### [2026-08-28 16:20:58] 用户

结合C:\temp\focus_perception给我一个整理好的文件

---

### [2026-08-28 16:21:35] AI

[思考] The user wants me to "结合 C:\temp\focus_perception 给我一个整理好的文件" — combine the perception module with the behavior module and give an organized file.

Let me understand what they want. They're non-technical, terse. "整理好的文件" = a well-organized file/document. They want me to combine the two modules (perception + behavior) into one organized deliverable.

This could mean:
1. A single consolidated document/summary that ties both modules together (like a README or overview doc).
2. A consolidated folder that has both modules merged.

Given they said "一个整理好的文件" (one organized file), and they're non-technical wanting a "成品", I think they want a single, clear document that ties everything together — an overview/整合文档 showing how the whole action-recognition pipeline works (perception → behavior → state machine).

Actually, let me reconsider. "结合 C:\temp\focus_perception 给我一个整理好的文件" — "combining with C:\temp\focus_perception, give me one organized file."

The most useful deliverable for a non-technical user would be a single clear document that:
- Explains the whole pipeline (JPEG frames → perception → observation → behavior → action)
- Shows the file structure of both modules together
- Shows how they connect
- Has the key interfaces

But it could also be interpreted as: put both modules together into one folder/file so it's a single deliverable.

Given ambiguity, but the phrase "一个整理好的文件" (a single organized file), and "结合...focus_perception" (combining with focus_perception), I think the best deliverable is a single comprehensive Markdown document that integrates/overviews both modules — a "总集成文档" (integration overview). This is genuinely useful and matches "整理好的文件".

Alternatively, they might want a single combined source tree. But "文件" (file, singular) strongly suggests ONE document.

Let me think about what's most valuable and least likely to be wrong. The user is non-technical, terse, wants a finished product. They've seen me build the behavior module. Now "结合 focus_perception 给我一个整理好的文件" most likely means: produce one clean document that ties the two modules together — the complete picture.

I'll create a single, well-organized integration document at `C:\temp\FOCUS_全链路说明.md` (or similar), covering:

1. 总览 — 整个动作识别流水线（一页看懂）
2. 目录结构（两个模块合并后）
3. 数据流 — JPEG → observation → study_state → 状态机
4. 两个模块的接口（observation_t, study_state_t）
5. 动作识别对照表
6. 如何编译/测试两个模块
7. 接入仓库步骤

Actually, wait. Let me reconsider whether they want a merged folder instead. "结合...给我一个整理好的文件" — "combine ... give me an organized file". 

Hmm, "文件" is singular. A document makes most sense. But "整理好的" (organized/cleaned up) suggests organizing existing stuff.

I think the safest, most useful thing: create ONE comprehensive Markdown document that integrates both modules into a clear whole. This is a "整理好的文件" that "结合" (combines) perception + behavior.

Actually, let me reconsider once more. There's a risk they want a merged directory (both modules side by side as one deliverable). But they said "文件" not "文件夹". And "一个" (one). So one file.

Let me go with a single comprehensive integration document. I'll write it in Chinese, well-structured, since the user is Chinese and non-technical.

Should I make it an Artifact? The Artifact tool guidance says: a finished deliverable with an audience (a document meant as reference, a plan people follow, the case for a decision) is not fully delivered in terminal scrollback or a local file. This document is a reference/integration doc for the team. But the user explicitly asked for "一个文件" in the C:\temp context, which is a local file deliverable, not a shared web page.

Hmm. The user said "给我一个整理好的文件" — "give me an organized file". They want a FILE. So writing it to disk (C:\temp) is correct. I shouldn't over-engineer with an Artifact unless they want to share it. The user is non-technical and works with local files in C:\temp. A local Markdown file is what they want.

But wait — should it be an Artifact so they can view it nicely? The instruction says "a finished deliverable with an audience... is not fully delivered while it lives only in terminal scrollback or a local file." But this user is non-technical, terse, working on an embedded project with local files. They asked for "文件". A local .md file in C:\temp is the right call. I'll write it to disk. I could optionally mention they can view it.

Actually, let me reconsider the artifact question more carefully. The user's whole workflow is local files in C:\temp. They want files. I'll write a local file. That's the deliverable. I won't force an Artifact.

Let me write a comprehensive, clean integration document. It should:

1. Have a clear title and one-page overview
2. Show the complete data flow
3. Show merged directory structure
4. List the interfaces and how they connect
5. Action recognition table
6. Build/test instructions
7. Integration steps

Let me also decide the filename. Something clear like `FOCUS_视觉行为全链路.md` or `FOCUS_全链路集成说明.md`. Given the project is "FOCUS AIoT", I'll name it `FOCUS_全链路集成说明.md` in C:\temp.

Actually, let me reconsider: should the document also actually MERGE the two folders into one? The user said "结合...给我一个整理好的文件" — I'll interpret as: produce one organized document that combines/explains both. I'll also give the combined directory tree in the doc.

Let me write it well. I'll keep it comprehensive but not bloated. Use tables, code blocks, clear sections.

Let me verify the current file listing of both folders to be accurate in the doc.

focus_perception files:
- api/perception.h
- perception/perception.c
- perception/perception_internal.h
- tests/test_perception.c
- tests/wifi_http_post_stub.c
- tests/test_mimo_cloud.c
- BUILD_INTEGRATION.md
- README.md
- PR_STEPS.md (I saw it in the find earlier)

Wait, earlier find showed: /c/temp/focus_perception/PR_STEPS.md also exists. Let me include accurate file lists. Actually the earlier `find` output listed:
- api/perception.h
- BUILD_INTEGRATION.md
- perception/perception.c
- perception/perception_internal.h
- PR_STEPS.md
- README.md
- tests/test_mimo_cloud.c
- tests/test_perception.c
- tests/wifi_http_post_stub.c

So 9 files in focus_perception (including PR_STEPS.md). And focus_behavior has 7 source files + test_behavior.exe (build artifact, I should note to ignore the .exe).

Let me write the integration document now. I'll make it accurate and useful.

Let me think about the content structure:

# FOCUS AIoT — 视觉感知 + 行为分析 全链路集成说明

## 一页看懂（流水线）
```
摄像头(张沐泽) 相机逐帧 JPEG(320x240)
      │
      ▼  perception_process(jpeg)   ← 周礼航
云端 MiMo 识图 → 去抖 → observation_t (每帧一条)
      │
      ▼  perception_get_history() 连续 observation 序列
behavior_analyze()  ← 赵思涵  时序判定
      │
      ▼  study_state_t (动作 + 提醒/鼓励)
状态机 state_machine (万思源) → 计时/UI/语音/报告
```

## 目录结构（两个模块合并后）

## 核心数据结构

## 动作识别对照表

## 接口清单

## 编译与测试（本地）

## 接入仓库

## 联调顺序

Let me write it. I'll be thorough but clean.

Actually, I want to also double-check: is there a PR_STEPS.md content I should reference? I didn't read it. It's 周礼航's PR steps. I don't need its content for the integration doc, just mention it exists. Actually, let me not over-reference it. I'll list files accurately.

Let me write the document now.

For the "编译与测试" section, I should give the actual commands that work (I've verified the behavior one; the perception one I'll use from its README).

perception mock test:
```
cd focus_perception
gcc -Wall -Wextra -Werror -DPERCEPTION_MOCK \
    perception/perception.c tests/test_perception.c -o test_perception
./test_perception
```

behavior test:
```
cd focus_behavior
gcc -Wall -Wextra -Werror \
    behavior/behavior.c behavior/behavior_config.c tests/test_behavior.c -o test_behavior
./test_behavior
```

Let me write the full document.

I'll write it to C:\temp\FOCUS_全链路集成说明.md.

Let me be careful about the filename — Chinese filename on Windows should be fine.

Actually, let me reconsider naming. Maybe `FOCUS_全链路集成说明.md` is good. Or `FOCUS_行为识别全链路.md`. The doc is about both modules integrated. I'll go with `FOCUS_视觉行为全链路集成说明.md`. Hmm, a bit long. Let me use `FOCUS_全链路集成说明.md`.

Let me write it now.

---

### [2026-08-28 16:22:02] AI

[工具调用] Write: {"file_path": "C:\\temp\\FOCUS_全链路集成说明.md", "content": "# FOCUS AIoT — 动作识别全链路集成说明\n\n> 把 `focus_perception`（周礼航·视觉感知）+ `focus_behavior`（赵思涵·行为分析）\n> 两个模块串起来，从**连续 JPEG 帧**一路走到**动作识别结果**。本文是两者合并后的\n> 一份整理版说明，可直接照着接入 openvela 仓库。\n\n---\n\n## 一页看懂（数据流）\n\n```\n        ┌──────────────────────────────────────────────────────┐\n        │  摄像头 (张沐泽)  camera_capture_frame()              │\n        │  逐帧输出 JPEG 320×240                                │\n        └───────────────────────┬──────────────────────────────┘\n                                │  jpeg (每帧一张)\n                                ▼\n        ┌──────────────────────────────────────────────────────┐\n        │  视觉感知 perception (周礼航)                          │\n        │  perception_process(jpeg)                            │\n        │    → base64 → MiMo 云端识图 → 3帧去抖                │\n        │  perception_get_history()  ← 连续 observation 序列   │\n        └───────────────────────┬──────────────────────────────┘\n                                │  observation_t[] (带时间戳, 旧→新)\n                                ▼\n        ┌──────────────────────────────────────────────────────┐\n        │  行为分析 behavior (赵思涵)                            │\n        │  behavior_analyze()                                  │\n        │    → 从最新帧往前扫连续时长 → 时序判定               │\n        │    → 冷却/累计/里程碑 → study_state_t                 │\n        └───────────────────────┬──────────────────────────────┘\n                                │  study_state_t (动作 + 提醒/鼓励)\n                                ▼\n        ┌──────────────────────────────────────────────────────┐\n        │  状态机 state_machine (万思源)                        │\n        │  消费 study_state_t → 计时 / LCD / 语音 / 报告        │\n        └──────────────────────────────────────────────────────┘\n```\n\n**一句话分工**：周礼航做「空间」上的单帧识别（一帧一帧看），赵思涵做「时间」上的\n行为推理（多帧串起来看）。两人输入类型不同、算法不同、产出不同，互不依赖。\n\n---\n\n## 目录结构（两个模块合并后）\n\n```\nC:\\temp\\\n├── focus_perception\\                 ← 视觉感知层 (单帧 → observation)\n│   ├── api\\perception.h              公开接口 (observation_t + 3 函数)\n│   ├── perception\\perception.c       主实现 (MiMo + base64 + 去抖 + 历史)\n│   ├── perception\\perception_internal.h\n│   ├── tests\\test_perception.c       mock 单测\n│   ├── tests\\wifi_http_post_stub.c   联调 stub\n│   ├── tests\\test_mimo_cloud.c       真实 MiMo 链路单测\n│   ├── BUILD_INTEGRATION.md\n│   ├── PR_STEPS.md\n│   └── README.md\n│\n├── focus_behavior\\                   ← 行为分析层 (连续 observation → 动作)\n│   ├── api\\behavior.h                公开接口 (study_state_t + 3 枚举 + 2 函数)\n│   ├── api\\perception.h              observation 定义 (参考拷贝, 供独立编译)\n│   ├── behavior\\behavior.c           主实现 (时序判定 + 冷却 + 累计 + 里程碑)\n│   ├── behavior\\behavior_internal.h\n│   ├── behavior\\behavior_config.c    严格/鼓励两套配置表 + 话术\n│   ├── tests\\test_behavior.c         mock 单测\n│   ├── BUILD_INTEGRATION.md\n│   └── README.md\n│\n└── FOCUS_全链路集成说明.md            ← 本文\n```\n\n> ⚠️ `api\\*.h` 在两个文件夹里都是**参考拷贝**，真正冻结的接口在仓库里由万思源\n> 维护。合并时字段/签名必须与仓库冻结版一致。\n\n---\n\n## 核心数据结构\n\n### observation_t（周礼航产出，赵思涵消费）\n\n```c\ntypedef struct {\n    bool     person_present;       // 画面中是否有人\n    float    person_bbox[4];       // 人体边界框 (x,y,w,h) 归一化 [0-1]\n    bool     phone_detected;       // 是否检测到手机\n    bool     phone_near_hand;      // 手机是否在手部区域\n    float    head_pitch;           // 头部俯仰角 (度, 负=低头 正=仰头)\n    float    head_yaw;             // 头部偏航角 (度)\n    float    hand_motion_score;    // 手部运动量 [0-1]\n    float    confidence;           // 整体置信度 [0-1]\n    uint32_t timestamp_ms;         // 时间戳 (毫秒)\n} observation_t;\n```\n\n### study_state_t（赵思涵产出，万思源消费）\n\n```c\ntypedef enum { FOCUSED, GLANCING_PHONE, PLAYING_PHONE, AWAY, DROWSY } status_t;\ntypedef enum { NONE, REMIND, ENCOURAGE } action_t;\ntypedef enum { MODE_STRICT, MODE_GENTLE } mode_t;\n\ntypedef struct {\n    status_t  status;              // 当前学习状态 (动作)\n    action_t  action;              // 应采取的行动\n    char      message[128];        // 提醒/鼓励文字\n    bool      milestone_reached;   // 是否达到专注里程碑\n    int       milestone_minutes;   // 连续专注分钟数\n    int8_t    focus_score_delta;   // 评分变化量 (负=扣分, 正=加分)\n} study_state_t;\n```\n\n---\n\n## 动作识别对照表\n\n| 动作 status | 触发条件（严格 / 鼓励） | action | 话术（严格 / 鼓励） |\n|---|---|---|---|\n| `AWAY` 离座 | 连续无人 ≥ 10s / 20s | REMIND | 请回到座位! / 等你回来哦~ |\n| `PLAYING_PHONE` 玩手机 | 手机在手 ≥ 8s / 15s 且手部运动 >0.3 | REMIND | 请放下手机! / 休息好了就继续吧~ |\n| `GLANCING_PHONE` 看手机 | 手机在手但未达玩手机阈值 | NONE | — |\n| `DROWSY` 瞌睡 | 头仰角 >45° / 52° 持续 ≥ 8s / 12s | REMIND | 请注意坐姿! / 要不要起来活动一下? |\n| `FOCUSED` 专注 | 其余情况 | 鼓励模式里程碑触发 ENCOURAGE | 已专注学习 N 分钟,继续保持! |\n\n**判定优先级**：AWAY > 玩手机 > 看手机 > 瞌睡 > 专注里程碑 > FOCUSED。\n\n**严格 vs 鼓励**（只换配置，不换代码）：\n\n| 维度 | 严格 MODE_STRICT | 鼓励 MODE_GENTLE |\n|---|---|---|\n| 分心阈值 | 紧（8s/10s/8s） | 松（15s/20s/12s） |\n| 提醒频率 | 每次分心都提醒，间隔 30s | 累计 3 次才提醒 1 次，间隔 120s |\n| 扣分 | 玩手机 -15 / 离座 -10 / 瞌睡 -20 | -5 / -3 / -8 |\n| 里程碑 | 无 | 每专注 30 分钟 +5 鼓励 |\n\n---\n\n## 接口清单\n\n### perception（周礼航实现）\n\n```c\nint  perception_init(const char *api_url, const char *api_key);\nint  perception_process(uint8_t *jpeg, size_t jpeg_len, observation_t *out);\nint  perception_get_history(observation_t *buf, int n);   // 强符号, 覆盖 mock 桩\n```\n\n### behavior（赵思涵实现）\n\n```c\nint  behavior_init(mode_t mode);            // 启动时调用一次\nint  behavior_analyze(study_state_t *out);  // 每收到一帧 observation 调用一次\n```\n\n---\n\n## 编译与测试（本地，无需硬件/网络）\n\n### 1. 视觉感知（周礼航）\n\n```bash\ncd C:\\temp\\focus_perception\n\n# mock 单测 (无 cJSON 依赖)\ngcc -Wall -Wextra -Werror -DPERCEPTION_MOCK \\\n    perception/perception.c tests/test_perception.c -o test_perception\n./test_perception          # 预期 0 failed\n```\n\n### 2. 行为分析（赵思涵）\n\n```bash\ncd C:\\temp\\focus_behavior\n\ngcc -Wall -Wextra -Werror \\\n    behavior/behavior.c behavior/behavior_config.c tests/test_behavior.c \\\n    -o test_behavior\n./test_behavior            # 预期 ALL TESTS PASSED\n```\n\n> 两个模块都已按 `-Wall -Wextra -Werror` 实测通过。\n\n---\n\n## 接入仓库（openvela 真机）\n\n1. **源码入编**（`app/hello_app/Makefile` 或 `CMakeLists.txt` 的 `CSRCS`）：\n\n   ```make\n   CSRCS += perception/perception.c\n   CSRCS += behavior/behavior.c\n   CSRCS += behavior/behavior_config.c\n   ```\n\n2. **接口头文件**：`api/perception.h`、`api/behavior.h` **不要覆盖**，用仓库冻结版。\n3. **mock 开关**：perception 默认 `-DPERCEPTION_MOCK` 可回退；联调/上线前关掉并填好\n   MiMo endpoint / token（跟张沐泽确认鉴权方式）。\n4. **主循环**（万思源）：\n\n   ```c\n   perception_init(API_URL, API_KEY);\n   behavior_init(MODE_STRICT);           // 或按用户选择 MODE_GENTLE\n\n   while (monitoring) {\n       uint8_t *jpeg; size_t len;\n       camera_capture_frame(&jpeg, &len);   // 张沐泽\n\n       observation_t obs;\n       perception_process(jpeg, len, &obs); // 周礼航\n\n       study_state_t st;\n       behavior_analyze(&st);               // 赵思涵\n\n       if (st.action == REMIND)     play_reminder(st.message);\n       if (st.milestone_reached)    play_encouragement(st.milestone_minutes);\n   }\n   ```\n\n---\n\n## 联调顺序\n\n1. **张沐泽 ↔ 周礼航**：确认 `wifi_http_post` 能通 + MiMo 鉴权方式 → `perception_process`\n   返回真实 observation。\n2. **周礼航 ↔ 赵思涵**：确认 `perception_get_history()` 返回的历史字段/时间戳正确 →\n   `behavior_analyze` 判对动作。\n3. **赵思涵 ↔ 万思源**：确认 `study_state_t` 字段与状态机消费一致。\n4. **全链路**：真实 observation → behavior → state_machine → UI 上屏。\n"}

---

### [2026-08-28 16:22:17] 用户

[工具结果] File created successfully at: C:\temp\FOCUS_全链路集成说明.md (file state is current in your context — no need to Read it back)

---

### [2026-08-28 16:22:21] AI

[思考] The document is written. Let me give a brief summary to the user. The user is non-technical and terse, so I'll keep the response short.

I should tell them where the file is and what's in it, briefly.

---

### [2026-08-28 16:22:24] AI

整理好了，一个文件：

**`C:\temp\FOCUS_全链路集成说明.md`**

里面把两个模块串成了一条完整流水线，包含：

1. **一页看懂** — 数据流图（摄像头 → perception → behavior → 状态机）
2. **目录结构** — 两个模块合并后的完整文件清单
3. **核心数据结构** — `observation_t` 和 `study_state_t`
4. **动作识别对照表** — 5 种动作 + 判定条件 + 话术
5. **严格/鼓励模式差异表**
6. **接口清单**
7. **编译测试命令**（两个模块都实测通过）
8. **接入仓库步骤 + 联调顺序**

你可以直接双击打开看。需要我把它再拆成别的格式（比如给老师看的 PPT 大纲、或者合并成一个文件夹）吗？

---

### [2026-08-28 16:23:20] 用户

我要一个可以pr的文件夹！

---

### [2026-08-28 16:24:35] AI

[思考] The user wants "一个可以 pr 的文件夹" — a folder they can submit as a PR (Pull Request). This is the contest/team project context. They want a properly organized folder that can be PR'd into the openvela repo (app/hello_app).

Let me think about what "可以 pr 的文件夹" means in this project context. Looking at the docs:
- The repo has `app/hello_app/` with submodules: `perception/`, `behavior/`, `core/`, `ui/`, `hardware/`.
- The PR integration docs (BUILD_INTEGRATION.md) say: put `perception/perception.c`, `perception/perception_internal.h` into `app/hello_app/perception/`, etc.

So the user wants a folder that's structured exactly how it should land in the repo, ready to PR. This means I should create a folder that matches the target repo structure — e.g., a folder that mirrors `app/hello_app/` additions:

```
app/hello_app/
├── perception/
│   ├── perception.c
│   └── perception_internal.h
├── behavior/
│   ├── behavior.c
│   ├── behavior_config.c
│   └── behavior_internal.h
├── tests/ (maybe)
└── (Makefile/CMakeLists/Kconfig diffs)
```

But wait — the api/*.h files are frozen by 万思源 and should NOT be overwritten in the PR. So the PR folder should NOT include api/perception.h or api/behavior.h (those are already in the repo). The PR should only include the implementation files + tests + build integration.

Actually, let me reconsider. The user is 周礼航 (perception) or wants to PR both perception + behavior? The context: they've been building perception (focus_perception) and now behavior (focus_behavior). They said "可以 pr 的文件夹" — a folder ready to PR.

Let me think about what the actual repo structure is. From BUILD_INTEGRATION.md and DEVELOPMENT_TASKS:
- `app/hello_app/perception/perception.c` + `perception_internal.h`
- `app/hello_app/behavior/behavior.c` + `behavior_config.c` + `behavior_internal.h`
- `app/hello_app/tests/` for unit tests
- Makefile/CMakeLists.txt/Kconfig changes

So a PR-ready folder should mirror `app/hello_app/` additions, with:
- The implementation `.c` and internal `.h` files (NOT the frozen api/*.h)
- Tests
- Build integration changes

The cleanest deliverable: create a folder like `C:\temp\hello_app\` (or `C:\temp\PR_focus\`) that contains exactly the files to be added to the repo, in the correct relative structure, plus a PR description and the Makefile/CMakeLists/Kconfig diffs.

Let me think about naming. The user wants "一个可以 pr 的文件夹". I'll create a folder that represents the PR contents. Maybe `C:\temp\focus_pr\` or `C:\temp\hello_app\`. 

Actually, the most useful and unambiguous: create a folder named something like `C:\temp\PR_周礼航_赵思涵\` or just `C:\temp\hello_app\` mirroring the target.

Hmm, but there might be a concern: the two modules belong to different people (周礼航 and 赵思涵). A single PR folder containing both is a bit unusual — but the user has been working on both (or wants to submit both together). Actually wait, let me reconsider — is the user 周礼航 or 赵思涵? 

The memory says "user-nontechnical-terse". The user has been building perception (focus_perception is 周礼航's) AND behavior (focus_behavior is 赵思涵's). But the user might just be a project coordinator or the person doing everything. Given they asked for both to be combined, they want ONE PR-ready folder with both modules.

Actually, re-reading the conversation: I built focus_behavior for them (they asked "识别动作" = action recognition = behavior module). The focus_perception already existed (周礼航's work, already in C:\temp). Now they want a PR-ready folder.

So the deliverable: a single folder, structured to match the repo, containing:
1. `perception/` implementation (from focus_perception)
2. `behavior/` implementation (from focus_behavior)
3. tests
4. build integration (Makefile/CMakeLists/Kconfig snippets)
5. PR description (README or PR body)

And NOT the frozen api/*.h files (those stay in repo).

Wait, but actually — let me reconsider whether to include api/*.h. The BUILD_INTEGRATION.md for perception says "api/perception.h 不要覆盖，用仓库冻结版". For behavior similarly. So the PR should NOT touch api/*.h. Good — exclude them.

But there's a subtlety: the unit tests include `../api/perception.h`. In the repo, tests would include `api/perception.h` from the repo's api/ directory (already frozen). So the PR doesn't need to add api/*.h. But for the tests to compile standalone in the PR folder, they'd need the api headers... 

For a PR-ready folder, the key is: the FILES that will be ADDED to the repo, in the correct structure. The api/*.h already exist in the repo, so they're not part of the PR's new files.

Let me design the PR folder structure. I'll mirror `app/hello_app/`:

```
C:\temp\focus_pr\                    (或 focus_hello_app)
├── PR_DESCRIPTION.md                 PR 说明/正文
├── app/hello_app/
│   ├── perception/
│   │   ├── perception.c
│   │   └── perception_internal.h
│   ├── behavior/
│   │   ├── behavior.c
│   │   ├── behavior_config.c
│   │   └── behavior_internal.h
│   ├── tests/
│   │   ├── test_perception.c
│   │   ├── test_behavior.c
│   │   ├── wifi_http_post_stub.c
│   │   └── test_mimo_cloud.c
│   └── (构建改动)
```

Actually, let me reconsider the repo layout. From DEVELOPMENT_TASKS:
- 周礼航: `perception/perception.c`, `perception/perception.h` (内部), `tests/test_perception.c`
- 赵思涵: `behavior/behavior.c`, `behavior/behavior_config.c`, `tests/behavior_test.c`

And the repo has `app/hello_app/` with subfolders `perception/`, `behavior/`, `core/`, `ui/`, `hardware/`, and tests somewhere.

The exact tests location: DEVELOPMENT_TASKS mentions `tests/test_perception.c` and `tests/behavior_test.c`. So tests are at `app/hello_app/tests/` (or maybe `tests/` at repo root). The perception README says tests are in `focus_perception/tests/`. In the repo it's likely `app/hello_app/tests/`.

Hmm, I don't know the exact repo test location. I'll use `tests/` at the `app/hello_app/` level, which matches the naming `tests/test_behavior.c`.

Let me also think about the build integration. BUILD_INTEGRATION.md shows Makefile/CMakeLists changes. For a PR, I should include these as either:
1. Actual modified Makefile/CMakeLists.txt/Kconfig files (but I don't have the originals, so I can't produce full diffs)
2. A diff/patch file showing what to add

Since I don't have the original repo files, I'll include the integration snippets as a clear "构建改动" doc (which is what BUILD_INTEGRATION.md already is). I'll consolidate into the PR.

Actually, the cleanest for "可以 pr 的文件夹": 
- The source files in correct structure
- A PR description (pr body) 
- The build diff instructions

Let me create the folder and copy the actual source files into the right structure. I should COPY (not just document) the actual .c/.h files so the folder is truly "可以 pr" — i.e., someone can literally take these files and commit them.

Let me plan the copy:
1. `C:\temp\focus_pr\app\hello_app\perception\perception.c` ← focus_perception/perception/perception.c
2. `C:\temp\focus_pr\app\hello_app\perception\perception_internal.h` ← focus_perception/perception/perception_internal.h
3. `C:\temp\focus_pr\app\hello_app\behavior\behavior.c` ← focus_behavior/behavior/behavior.c
4. `C:\temp\focus_pr\app\hello_app\behavior\behavior_config.c` ← focus_behavior/behavior/behavior_config.c
5. `C:\temp\focus_pr\app\hello_app\behavior\behavior_internal.h` ← focus_behavior/behavior/behavior_internal.h
6. tests: test_perception.c, test_behavior.c, wifi_http_post_stub.c, test_mimo_cloud.c

Wait — but the include paths inside these files reference `../api/perception.h` (relative). In the repo, the files live at `app/hello_app/perception/perception.c` and include `api/perception.h` or `../api/perception.h`? 

Let me check: perception.c has `#include "../api/perception.h"` and `#include "perception_internal.h"`. In focus_perception, structure is:
```
focus_perception/
├── api/perception.h
├── perception/perception.c  (includes ../api/perception.h)
```

In the repo, structure is `app/hello_app/perception/perception.c` and `app/hello_app/api/perception.h`? Or `app/hello_app/api/`? 

Hmm, the DEVELOPMENT_TASKS says "把 perception/perception.c、perception/perception_internal.h 放进 app/hello_app/perception/". And "api/perception.h 不要覆盖，用仓库冻结版". So api/ is likely at `app/hello_app/api/` or a top-level `api/`. The include `../api/perception.h` from `perception/perception.c` implies api/ is a sibling of perception/ — i.e., `app/hello_app/perception/perception.c` → `../api/perception.h` = `app/hello_app/api/perception.h`. So `api/` is at `app/hello_app/api/`. 

Similarly behavior.c includes `../api/perception.h` and `../api/behavior.h` → `app/hello_app/api/`.

So the repo structure is:
```
app/hello_app/
├── api/
│   ├── perception.h      (frozen, not in PR)
│   ├── behavior.h        (frozen, not in PR)
│   └── ...
├── perception/
│   ├── perception.c
│   └── perception_internal.h
├── behavior/
│   ├── behavior.c
│   ├── behavior_config.c
│   └── behavior_internal.h
├── tests/
│   ├── test_perception.c
│   ├── test_behavior.c
│   ├── wifi_http_post_stub.c
│   └── test_mimo_cloud.c
├── Makefile
├── CMakeLists.txt
└── Kconfig
```

So my PR folder should mirror this, and the `../api/` includes will resolve IF the repo already has api/ in place (which it does, frozen). So I should NOT include api/ in the PR folder, and the include paths `../api/perception.h` will work because the repo has api/ at that location.

But for the PR folder to be verifiable/self-contained (compile tests), it'd need api/ headers. However, since those are frozen and already in the repo, the PR folder doesn't need them — the PR is just the ADDED files.

I think the right approach:
1. Create `C:\temp\focus_pr\` folder mirroring `app/hello_app/` additions.
2. Copy the implementation files + tests.
3. Include a PR_DESCRIPTION.md (pr body).
4. Include the Makefile/CMakeLists/Kconfig changes (as a diff file or the actual full files? I don't have originals, so a diff snippet file).

Actually, for the build changes, since I can't produce a real git diff without the original Makefile, I'll include a `BUILD_CHANGES.md` that has the exact lines to add (copy-paste ready), which is what BUILD_INTEGRATION.md already provides. I'll merge both modules' build changes into one.

Let me also include the tests with correct include paths. The test files reference `../api/behavior.h`, `../api/perception.h`, `../behavior/behavior_internal.h`, `../perception/perception_internal.h`. In the repo, tests at `app/hello_app/tests/test_behavior.c` would include `../api/behavior.h` (→ app/hello_app/api/behavior.h ✓) and `../behavior/behavior_internal.h` (→ app/hello_app/behavior/behavior_internal.h ✓). Good, the `../` paths work.

Wait, let me check the current test_behavior.c include paths:
```c
#include "../api/behavior.h"
#include "../api/perception.h"
#include "../behavior/behavior_internal.h"
```
If test_behavior.c is at `app/hello_app/tests/test_behavior.c`, then `../api/behavior.h` = `app/hello_app/api/behavior.h` ✓, `../behavior/behavior_internal.h` = `app/hello_app/behavior/behavior_internal.h` ✓. 

And test_perception.c (from focus_perception) — let me check its includes. I didn't read it, but it's at focus_perception/tests/test_perception.c. It likely includes `../api/perception.h` and `../perception/perception_internal.h`. In repo, tests/ → `../api/perception.h` ✓, `../perception/perception_internal.h` ✓. Good.

So the `../` include convention matches if tests/ is a sibling of api/, perception/, behavior/. 

So my PR folder should be:
```
focus_pr/
├── app/hello_app/
│   ├── perception/
│   │   ├── perception.c
│   │   └── perception_internal.h
│   ├── behavior/
│   │   ├── behavior.c
│   │   ├── behavior_config.c
│   │   └── behavior_internal.h
│   └── tests/
│       ├── test_perception.c
│       ├── test_behavior.c
│       ├── wifi_http_post_stub.c
│       └── test_mimo_cloud.c
├── PR_DESCRIPTION.md
└── BUILD_CHANGES.md
```

Hmm wait, but the tests might be at a different location. Let me check what focus_perception's test files include and how they're compiled.

Actually, I already saw the perception README compile commands:
```
gcc -Wall -Wextra -Werror -DPERCEPTION_MOCK \
    perception/perception.c tests/test_perception.c -o test_perception
```
So tests are compiled from `tests/test_perception.c` alongside `perception/perception.c`, with includes likely `../api/...` and `../perception/...`.

Let me verify by reading test_perception.c and the stub to get exact include paths, so my copy is accurate and I don't introduce errors.

Actually, I should read the remaining files I haven't seen: test_perception.c, wifi_http_post_stub.c, test_mimo_cloud.c. This matters for correctly placing them and for the PR description (test coverage). Let me read them.

Actually, for the purpose of creating the PR folder, I need to COPY these files verbatim (not necessarily understand every line). But I should verify their include paths resolve correctly in the new structure. Since I'm keeping the SAME relative structure (perception/, behavior/, tests/ all siblings under app/hello_app/), and api/ is the frozen sibling, the `../api/`, `../perception/`, `../behavior/` includes will resolve the same way as in focus_perception/focus_behavior (where api/, perception/, tests/ are siblings too). So actually the structure is IDENTICAL relative layout, just renamed parent. So copies will work.

But wait — there's a subtlety. In focus_perception, the structure is:
```
focus_perception/
├── api/perception.h
├── perception/perception.c
├── tests/test_perception.c
```
test_perception.c includes `../api/perception.h` and `../perception/perception_internal.h`. In the PR folder `app/hello_app/tests/test_perception.c`, `../api/perception.h` = `app/hello_app/api/perception.h` ✓ (frozen, exists in repo). Good.

So I can copy verbatim. The only thing I need to be careful about: the api/ headers. In the PR folder, should I include api/ headers so the folder is self-contained for testing? 

The user said "可以 pr 的文件夹" = a folder that can be PR'd. A PR doesn't include files that already exist unchanged in the repo (api/*.h are frozen). So I should NOT include api/ headers in the PR folder — they're already there.

BUT, if the user wants to verify the tests compile locally from this PR folder, they'd need api/ headers. To make it self-verifiable AND PR-correct, I can:
- Option A: Include api/ headers in a SEPARATE `参考/` subfolder (clearly marked "不要提交，仅本地测试用"), so the folder compiles standalone, but the PR instructions say "don't commit api/".
- Option B: Keep it clean (no api/), and rely on the repo's api/.

I think the cleanest for "可以 pr": the folder contains ONLY what gets added/changed. api/ is not included. But I'll add a note in PR_DESCRIPTION.md and BUILD_CHANGES.md that api/*.h are frozen and not touched.

Actually, wait. Let me reconsider. Let me re-read: "我要一个可以pr的文件夹！" — "I want a folder that can be PR'd!"

The emphasis and exclamation suggests they want a ready-to-submit folder. The key deliverable: a folder where the source files are correctly organized per the repo convention, plus the PR description.

Let me keep it focused and correct:

Folder: `C:\temp\focus_pr\`

Structure (what will be committed to the repo):
```
app/hello_app/
├── perception/perception.c
├── perception/perception_internal.h
├── behavior/behavior.c
├── behavior/behavior_config.c
├── behavior/behavior_internal.h
├── tests/test_perception.c
├── tests/test_behavior.c
├── tests/wifi_http_post_stub.c
└── tests/test_mimo_cloud.c
```
Plus:
```
PR_DESCRIPTION.md       (PR 标题 + 正文)
BUILD_CHANGES.md        (Makefile/CMakeLists/Kconfig 要改的行)
```

Actually, I realize I should double check the exact test file include paths and contents before copying, to make sure the copy is faithful and I understand the test coverage for the PR description. Let me read the three test files.

Let me also reconsider: should the folder be at repo root or nested? The repo likely has `app/hello_app/`. The PR would add files under `app/hello_app/`. So the PR folder should mirror `app/hello_app/...`. I'll name the top folder `focus_pr` and inside have `app/hello_app/...`.

Actually, simpler and more direct: name the top folder so it's obvious it's the PR content. Maybe `C:\temp\focus_pr\` with the `app/hello_app/` path inside. Or just put the subfolders directly. Let me use `C:\temp\focus_pr\` as root, and inside mirror the repo's `app/hello_app/` subfolder structure.

Hmm, but do I know the repo path is `app/hello_app/`? Yes, from all the docs: "app/hello_app/perception/", "app/hello_app/Makefile", "app/hello_app/Kconfig", "app/hello_app/CMakeLists.txt". So it's `app/hello_app/`.

Let me read the test files first to be accurate.

Let me read the three remaining perception test files.

---

### [2026-08-28 16:24:35] AI

[工具调用] Read: {"file_path": "C:\\temp\\focus_perception\\tests\\test_perception.c"}

---

### [2026-08-28 16:24:35] 用户

[工具结果] 1	/****************************************************************************
2	 * FOCUS AIoT - 视觉感知模块纯 C 单测 (tests/test_perception.c)
3	 *
4	 * 负责人: 周礼航
5	 * 说明:   宿主机运行, 不依赖硬件/网络/cJSON (用 mock 路径)。
6	 *         参考赵思涵 tests/behavior_test.c 的模式。
7	 *
8	 * 编译 (在 focus_perception 目录下):
9	 *   gcc -Wall -Wextra -Werror -DPERCEPTION_MOCK \
10	 *       perception/perception.c tests/test_perception.c -o test_perception
11	 *   ./test_perception
12	 ****************************************************************************/
13	
14	#include <stdio.h>
15	#include <string.h>
16	
17	#include "../api/perception.h"
18	#include "../perception/perception_internal.h"
19	
20	static int g_checks = 0;
21	static int g_fail   = 0;
22	
23	#define CHECK(cond) do {                                   \
24	    g_checks++;                                            \
25	    if (!(cond)) {                                         \
26	        g_fail++;                                          \
27	        printf("  [FAIL] %s (line %d)\n", #cond, __LINE__);\
28	    }                                                      \
29	} while (0)
30	
31	/* RFC 4648 标准测试向量 */
32	static void test_base64(void)
33	{
34	    printf("== test_base64 ==\n");
35	    const char *cases[][2] = {
36	        {"",       ""},
37	        {"M",      "TQ=="},
38	        {"Ma",     "TWE="},
39	        {"Man",    "TWFu"},
40	        {"plea",   "cGxlYQ=="},
41	        {"pleas",  "cGxlYXM="},
42	        {"please", "cGxlYXNl"},
43	    };
44	    char out[64];
45	
46	    for (int i = 0; i < 7; i++) {
47	        size_t n = perception_base64_encode((const uint8_t *)cases[i][0],
48	                                            strlen(cases[i][0]),
49	                                            out, sizeof(out));
50	        CHECK(n == strlen(cases[i][1]));
51	        CHECK(strcmp(out, cases[i][1]) == 0);
52	    }
53	}
54	
55	static void test_math_helpers(void)
56	{
57	    printf("== test_math_helpers ==\n");
58	
59	    CHECK(perception_majority3(true, true, false)  == true);
60	    CHECK(perception_majority3(true, false, false) == false);
61	    CHECK(perception_majority3(false, false, false) == false);
62	    CHECK(perception_majority3(true, true, true)   == true);
63	
64	    CHECK(perception_median3(1.0f, 2.0f, 3.0f) == 2.0f);
65	    CHECK(perception_median3(3.0f, 1.0f, 2.0f) == 2.0f);
66	    CHECK(perception_median3(2.0f, 3.0f, 1.0f) == 2.0f);
67	    CHECK(perception_median3(5.0f, 5.0f, 5.0f) == 5.0f);
68	
69	    CHECK(perception_max3(1.0f, 2.0f, 3.0f) == 3.0f);
70	    CHECK(perception_max3(3.0f, 2.0f, 1.0f) == 3.0f);
71	}
72	
73	static void test_debounce(void)
74	{
75	    printf("== test_debounce ==\n");
76	    observation_t out;
77	
78	    /* 布尔多数投票: 2 帧有人 + 1 帧无人 → 有人 */
79	    cloud_result_t r1 = {0}, r2 = {0}, r3 = {0};
80	    r1.person_detected = true;  r1.confidence = 0.9f;
81	    r2.person_detected = true;  r2.confidence = 0.9f;
82	    r3.person_detected = false; r3.confidence = 0.9f;
83	
84	    perception_init("url", "key");       /* 重置去抖状态 */
85	    perception_debounce_push(&r1);
86	    perception_debounce_compute(&out, 1);       /* 不足 3 帧 → 输出最新帧 */
87	    CHECK(out.person_present == true);
88	
89	    perception_debounce_push(&r2);
90	    perception_debounce_compute(&out, 2);
91	    CHECK(out.person_present == true);
92	
93	    perception_debounce_push(&r3);
94	    perception_debounce_compute(&out, 3);       /* 满 3 帧 → 多数投票 */
95	    CHECK(out.person_present == true);
96	
97	    /* 浮点中位数: 10/20/90 → 20 */
98	    cloud_result_t p1 = {0}, p2 = {0}, p3 = {0};
99	    p1.head_pitch = 10.0f; p1.confidence = 0.9f;
100	    p2.head_pitch = 20.0f; p2.confidence = 0.9f;
101	    p3.head_pitch = 90.0f; p3.confidence = 0.9f;
102	
103	    perception_init("url", "key");
104	    perception_debounce_push(&p1);
105	    perception_debounce_push(&p2);
106	    perception_debounce_push(&p3);
107	    perception_debounce_compute(&out, 4);
108	    CHECK(out.head_pitch == 20.0f);
109	}
110	
111	static void test_process_and_history(void)
112	{
113	    printf("== test_process_and_history ==\n");
114	    uint8_t dummy[16] = {0};
115	    observation_t obs;
116	    observation_t hist[10];
117	
118	    CHECK(perception_init("http://api", "key123") == FOCUS_OK);
119	
120	    /* 空历史 */
121	    CHECK(perception_get_history(hist, 10) == 0);
122	    CHECK(perception_get_history(NULL, 10) == 0);
123	
124	    /* 连续 8 帧, 时间戳非递减 */
125	    uint32_t last_ts = 0;
126	    for (int i = 0; i < 8; i++) {
127	        CHECK(perception_process(dummy, sizeof(dummy), &obs) == FOCUS_OK);
128	        CHECK(obs.timestamp_ms >= last_ts);
129	        last_ts = obs.timestamp_ms;
130	    }
131	
132	    /* 历史条数: 取全部 / 取最近 3 条 */
133	    CHECK(perception_get_history(hist, 10) == 8);
134	    CHECK(perception_get_history(hist, 3)  == 3);
135	
136	    /* mock 轮转应覆盖 person=false 与 phone=true 两种情况 */
137	    bool saw_away = false, saw_phone = false;
138	    for (int i = 0; i < 4; i++) {
139	        CHECK(perception_process(dummy, sizeof(dummy), &obs) == FOCUS_OK);
140	        if (!obs.person_present) saw_away = true;
141	        if (obs.phone_detected)  saw_phone = true;
142	    }
143	    CHECK(saw_away && saw_phone);
144	
145	    /* 参数非法 */
146	    CHECK(perception_process(NULL, 10, &obs) != FOCUS_OK);
147	    CHECK(perception_process(dummy, 0, &obs)  != FOCUS_OK);
148	    CHECK(perception_process(dummy, 10, NULL) != FOCUS_OK);
149	}
150	
151	int main(void)
152	{
153	    test_base64();
154	    test_math_helpers();
155	    test_debounce();
156	    test_process_and_history();
157	
158	    printf("\n结果: %d checks, %d failed\n", g_checks, g_fail);
159	    return g_fail ? 1 : 0;
160	}
161	

---

### [2026-08-28 16:24:36] AI

[工具调用] Read: {"file_path": "C:\\temp\\focus_perception\\tests\\wifi_http_post_stub.c"}

---

### [2026-08-28 16:24:36] 用户

[工具结果] 1	/****************************************************************************
2	 * FOCUS AIoT - wifi_http_post 联调 stub (tests/wifi_http_post_stub.c)
3	 *
4	 * 用途:   宿主机联调时替换张沐泽的真实 wifi_http_post，让 perception 模块
5	 *         在 Linux 上无需硬件/网络即可跑通「base64 → 构造请求 → POST →
6	 *         解析 MiMo 响应 → 去抖」整条真实链路。
7	 *
8	 * 说明:   与真机代码一起链接时【不要】编译本文件（会和张沐泽的强符号冲突）。
9	 *         仅用于 host 单测 / 联调。
10	 ****************************************************************************/
11	
12	#include <stdio.h>
13	#include <string.h>
14	#include <stddef.h>
15	
16	/* ---- 联调控制项 (测试代码可改) ---- */
17	int         stub_mimo_call_count = 0;   /* 累计被调用次数 */
18	const char *stub_mimo_response  = NULL; /* 自定义响应, NULL 用默认 */
19	int         stub_mimo_fail_first_n = 0; /* 前 N 次返回失败 (测重试) */
20	
21	/* 默认返回一个「玩手机」场景的 MiMo 响应 (字段最全, 便于验证解析) */
22	static const char DEFAULT_RESPONSE[] =
23	    "{"
24	    "\"code\":0,"
25	    "\"data\":{"
26	        "\"person\":{\"detected\":true,\"bbox\":[0.15,0.10,0.70,0.85]},"
27	        "\"phone\":{\"detected\":true,\"near_hand\":true},"
28	        "\"head_pose\":{\"pitch\":-25.3,\"yaw\":2.1},"
29	        "\"hand_motion_score\":0.35,"
30	        "\"confidence\":0.92"
31	    "}"
32	    "}";
33	
34	int wifi_http_post(const char *url, const char *body, char *resp, size_t maxlen)
35	{
36	    (void)url;   /* 联调 stub: 不真正发请求, 忽略 url/body */
37	    (void)body;
38	    stub_mimo_call_count++;
39	
40	    /* 模拟前 N 次失败 (perception 内部会重试 1 次) */
41	    if (stub_mimo_fail_first_n > 0) {
42	        stub_mimo_fail_first_n--;
43	        return -1;
44	    }
45	
46	    const char *r = stub_mimo_response ? stub_mimo_response : DEFAULT_RESPONSE;
47	    if (resp && maxlen > 0) {
48	        snprintf(resp, maxlen, "%s", r);
49	    }
50	    return 0;
51	}
52	

---

### [2026-08-28 16:24:36] AI

[工具调用] Read: {"file_path": "C:\\temp\\focus_perception\\tests\\test_mimo_cloud.c"}

---

### [2026-08-28 16:24:36] 用户

[工具结果] 1	/****************************************************************************
2	 * FOCUS AIoT - 真实 MiMo 链路单测 (tests/test_mimo_cloud.c)
3	 *
4	 * 负责人: 周礼航
5	 * 用途:   用 wifi_http_post_stub.c 替换真实网络, 验证 perception 真实路径:
6	 *         每帧都调 MiMo、请求构造、响应解析、3 帧去抖、重试、错误码。
7	 *
8	 * 依赖:   cJSON (perception.c 真实路径需要)。
9	 * 编译 (在 focus_perception 目录下):
10	 *   gcc -Wall -Wextra -Werror \
11	 *       perception/perception.c tests/wifi_http_post_stub.c tests/test_mimo_cloud.c \
12	 *       cJSON.c -I/path/to/cjson -o test_mimo_cloud
13	 *   ./test_mimo_cloud
14	 *
15	 *   (cJSON 是单文件库; openvela 已自带。host 上可 apt install libcjson-dev
16	 *    或直接拷一份 cJSON.c/cJSON.h 进仓库。)
17	 ****************************************************************************/
18	
19	#include <stdio.h>
20	#include <string.h>
21	
22	#include "../api/perception.h"
23	
24	/* 来自 wifi_http_post_stub.c */
25	extern int         stub_mimo_call_count;
26	extern const char *stub_mimo_response;
27	extern int         stub_mimo_fail_first_n;
28	
29	static int g_checks = 0;
30	static int g_fail   = 0;
31	
32	#define CHECK(cond) do {                                   \
33	    g_checks++;                                            \
34	    if (!(cond)) {                                         \
35	        g_fail++;                                          \
36	        printf("  [FAIL] %s (line %d)\n", #cond, __LINE__);\
37	    }                                                      \
38	} while (0)
39	
40	static int feq(float a, float b)
41	{
42	    float d = a - b;
43	    if (d < 0) d = -d;
44	    return d < 1e-4f;
45	}
46	
47	/* 每帧都调 MiMo + 响应解析 */
48	static void test_mimo_parse_and_every_frame(void)
49	{
50	    printf("== test_mimo_parse_and_every_frame ==\n");
51	    stub_mimo_response = NULL;      /* 用默认「玩手机」响应 */
52	    stub_mimo_fail_first_n = 0;
53	
54	    CHECK(perception_init("https://mimo.example/api/v1/detect", "key") == FOCUS_OK);
55	
56	    uint8_t jpeg[64] = {0};
57	    observation_t obs;
58	    int before = stub_mimo_call_count;
59	
60	    /* 连续 5 帧 → MiMo 应被调用 5 次 (每帧都调) */
61	    for (int i = 0; i < 5; i++) {
62	        CHECK(perception_process(jpeg, sizeof(jpeg), &obs) == FOCUS_OK);
63	    }
64	    CHECK(stub_mimo_call_count - before == 5);
65	
66	    /* 单帧解析结果 (去抖窗口未满 3 帧时直接输出) */
67	    CHECK(obs.person_present  == true);
68	    CHECK(obs.phone_detected  == true);
69	    CHECK(obs.phone_near_hand == true);
70	    CHECK(feq(obs.person_bbox[0], 0.15f) && feq(obs.person_bbox[1], 0.10f));
71	    CHECK(feq(obs.person_bbox[2], 0.70f) && feq(obs.person_bbox[3], 0.85f));
72	    CHECK(feq(obs.head_pitch, -25.3f));
73	    CHECK(feq(obs.head_yaw, 2.1f));
74	    CHECK(feq(obs.hand_motion_score, 0.35f));
75	    CHECK(feq(obs.confidence, 0.92f));
76	}
77	
78	/* 失败重试: 前 1 次失败 → 重试成功, 调用次数 +2 */
79	static void test_mimo_retry(void)
80	{
81	    printf("== test_mimo_retry ==\n");
82	    perception_init("https://mimo.example/api/v1/detect", "key");
83	
84	    stub_mimo_fail_first_n = 1;
85	    int before = stub_mimo_call_count;
86	
87	    uint8_t jpeg[64] = {0};
88	    observation_t obs;
89	    CHECK(perception_process(jpeg, sizeof(jpeg), &obs) == FOCUS_OK);
90	    CHECK(stub_mimo_call_count - before == 2);   /* 1 失败 + 1 重试成功 */
91	}
92	
93	/* 错误码: 业务码非 0 / JSON 非法 / 连续失败超时 */
94	static void test_mimo_error_codes(void)
95	{
96	    printf("== test_mimo_error_codes ==\n");
97	    uint8_t jpeg[64] = {0};
98	    observation_t obs;
99	
100	    /* 业务码非 0 → NODATA */
101	    perception_init("u", "k");
102	    stub_mimo_fail_first_n = 0;
103	    stub_mimo_response = "{\"code\":1,\"data\":{}}";
104	    CHECK(perception_process(jpeg, sizeof(jpeg), &obs) == FOCUS_ERR_PERCEP_NODATA);
105	
106	    /* JSON 非法 → JSON */
107	    stub_mimo_response = "not-a-json";
108	    CHECK(perception_process(jpeg, sizeof(jpeg), &obs) == FOCUS_ERR_PERCEP_JSON);
109	
110	    /* 连续 2 次都失败 (原请求 + 重试) → TIMEOUT */
111	    stub_mimo_response = NULL;
112	    stub_mimo_fail_first_n = 2;
113	    CHECK(perception_process(jpeg, sizeof(jpeg), &obs) == FOCUS_ERR_PERCEP_TIMEOUT);
114	}
115	
116	int main(void)
117	{
118	    test_mimo_parse_and_every_frame();
119	    test_mimo_retry();
120	    test_mimo_error_codes();
121	
122	    printf("\n结果: %d checks, %d failed\n", g_checks, g_fail);
123	    return g_fail ? 1 : 0;
124	}
125	

---

### [2026-08-28 16:24:36] AI

[工具调用] Read: {"file_path": "C:\\temp\\focus_perception\\PR_STEPS.md"}

---

### [2026-08-28 16:24:36] 用户

[工具结果] 1	# 如何提交 PR —— 视觉感知模块（周礼航）
2	
3	> 目标：把 `focus_perception/` 里的代码提进 openvela 仓库 `app/hello_app/`，开一个 PR。
4	> 适用环境：你有仓库的机器（VM / WSL / 本机均可），已装 git + gcc。
5	> 全程不涉及本机 `C:\temp` —— 那份只是开发时的本地副本。
6	
7	---
8	
9	## 0. 先核对：代码现在长什么样
10	
11	本地 `focus_perception/` 一共 8 个文件，已经整理干净（无二进制、无 .o）：
12	
13	```
14	focus_perception/
15	├── api/perception.h              ⚠️ 参考拷贝，【不要】覆盖仓库冻结版
16	├── perception/perception.c       主实现（进仓库）
17	├── perception/perception_internal.h  内部声明（进仓库）
18	├── tests/test_perception.c       mock 单测（进仓库，可选）
19	├── tests/wifi_http_post_stub.c   联调 stub（进仓库，可选，仅 host 用）
20	├── tests/test_mimo_cloud.c       真实 MiMo 链路单测（进仓库，可选，需 cJSON）
21	├── BUILD_INTEGRATION.md          接入 diff（照做，不必提交）
22	└── README.md                     模块说明（可进仓库，可选）
23	└── PR_STEPS.md                   本文件（不必提交）
24	```
25	
26	**进仓库必需**：`perception/perception.c`、`perception/perception_internal.h`。
27	**建议一并提**：`tests/` 三个测试文件 + `README.md`（说明清楚、方便评审）。
28	**绝不覆盖**：`api/perception.h`（仓库里已有冻结版，字段/签名一致，保持原样）。
29	
30	---
31	
32	## 1. 前置准备（一次性）
33	
34	### 1.1 找到仓库并 fork
35	1. 打开团队仓库（contest2026_087 对应的 GitHub 仓库 / 组织仓库）。
36	2. 点右上角 **Fork**，fork 到**你自己的** GitHub 账号下。
37	3. 记下你的 fork 地址，形如：
38	   `https://github.com/<你的用户名>/<仓库名>.git`
39	
40	### 1.2 clone 你的 fork
41	```bash
42	git clone https://github.com/<你的用户名>/<仓库名>.git
43	cd <仓库名>
44	```
45	
46	### 1.3 配好 git 身份（漏了这步 commit 会失败）
47	```bash
48	git config --global user.name  "周礼航"
49	git config --global user.email "你的邮箱"
50	```
51	
52	### 1.4 确认能 push
53	- 用 HTTPS + Personal Access Token，或配好 SSH key。
54	- 快速自检：`git remote -v` 应显示你 fork 的地址。
55	- ⚠️ **安全提醒**：之前某处文件里出现过的一个 GitHub token 已经泄露，请到
56	  GitHub → Settings → Developer settings → Tokens **把它 revoke**，一律用新 token。
57	  任何 token 都**不要**写进代码/commit/PR 描述里。
58	
59	---
60	
61	## 2. 把代码放进仓库
62	
63	### 2.1 拷贝文件（保持目录结构）
64	
65	在仓库根目录下（路径以仓库实际结构为准，下面按 `app/hello_app/` 举例）：
66	
67	```bash
68	# 拷贝主实现 + 内部声明
69	mkdir -p app/hello_app/perception
70	cp  <本地>/focus_perception/perception/perception.c          app/hello_app/perception/
71	cp  <本地>/focus_perception/perception/perception_internal.h app/hello_app/perception/
72	
73	# 拷贝测试（可选）
74	mkdir -p app/hello_app/tests
75	cp  <本地>/focus_perception/tests/test_perception.c          app/hello_app/tests/
76	cp  <本地>/focus_perception/tests/wifi_http_post_stub.c      app/hello_app/tests/
77	cp  <本地>/focus_perception/tests/test_mimo_cloud.c          app/hello_app/tests/
78	
79	# 模块说明（可选）
80	cp  <本地>/focus_perception/README.md                        app/hello_app/perception/README.md
81	```
82	
83	> 把 `<本地>` 换成 `C:\temp\focus_perception`（Windows）或 `~/focus_perception`（Linux/WSL）。
84	> **跳过 `api/perception.h`** —— 用仓库里已有的冻结版。
85	
86	### 2.2 接入构建（照 `BUILD_INTEGRATION.md` 做，3 步）
87	
88	**① Makefile**（`app/hello_app/Makefile`）的 `CSRCS` 加一行：
89	```make
90	CSRCS += perception/perception.c
91	```
92	
93	**② CMakeLists.txt**（`app/hello_app/CMakeLists.txt`）：
94	```cmake
95	set(CSRCS ${CSRCS} perception/perception.c)
96	```
97	
98	**③ Kconfig**（`app/hello_app/Kconfig`）加 mock/真实二选一：
99	```
100	config CONTEST2026_087_PERCEPTION_MOCK
101	    bool "Perception mock (no MiMo call)"
102	    default y
103	    help
104	        默认走 mock，便于不依赖网络的联调；关掉后走真实 MiMo 识图链路。
105	```
106	
107	以及 Makefile 里的条件编译（照抄 LCD_STUB 的 if/else）：
108	```make
109	ifeq ($(CONFIG_CONTEST2026_087_PERCEPTION_MOCK),y)
110	CFLAGS += -DPERCEPTION_MOCK
111	else
112	# 真实 MiMo 链路: 依赖 cJSON (openvela 自带, 头文件 <cJSON.h>)
113	endif
114	```
115	
116	---
117	
118	## 3. 本地验证（提交前必须过）
119	
120	### 3.1 mock 单测（不依赖硬件/网络/cJSON）
121	
122	在 Linux / WSL 上：
123	```bash
124	cd app/hello_app
125	gcc -Wall -Wextra -Werror -DPERCEPTION_MOCK \
126	    perception/perception.c tests/test_perception.c -o test_perception
127	./test_perception
128	```
129	预期输出结尾：`57 checks, 0 failed`，退出码 0。
130	
131	> Windows 上才需要额外 `-lwinpthread`（`clock_gettime`）；Linux/openvela 不用。
132	
133	### 3.2 真实 MiMo 链路单测（需要 cJSON）
134	```bash
135	gcc -Wall -Wextra -Werror \
136	    perception/perception.c tests/wifi_http_post_stub.c tests/test_mimo_cloud.c \
137	    cJSON.c -I/path/to/cjson -o test_mimo_cloud
138	./test_mimo_cloud
139	```
140	预期：`0 failed`。openvela 自带 cJSON；host 上 `apt install libcjson-dev` 或拷一份 `cJSON.c/h`。
141	
142	### 3.3 上真机（可选，联调阶段再做）
143	- 关掉 Kconfig 的 mock 开关。
144	- 填好 `perception.c` 里的 `MIMO_ENDPOINT_DEFAULT` / `MIMO_API_KEY_DEFAULT`，
145	  或运行时用 `perception_init(url, key)` 传入。
146	- 联调顺序：先张沐泽（`wifi_http_post` 通 + MiMo 鉴权方式）→ 再赵思涵
147	  （`observation_t` 字段对）→ 最后全链路。
148	
149	---
150	
151	## 4. 提交（commit）
152	
153	### 4.1 开分支（别直接在 main 上改）
154	```bash
155	git checkout -b feat/perception-mimo
156	```
157	
158	### 4.2 只 add 该加的文件
159	```bash
160	git add app/hello_app/perception/ app/hello_app/tests/
161	git add app/hello_app/Makefile app/hello_app/CMakeLists.txt app/hello_app/Kconfig
162	```
163	> 提交前 `git status` 扫一眼，确认**没有** token、密钥、二进制、`.o`、编辑器临时文件被 add。
164	
165	### 4.3 commit（建议信息）
166	```bash
167	git commit -m "feat(perception): 视觉感知模块，每帧调用 MiMo 识图
168	
169	- 实现 perception_init / perception_process / perception_get_history 三个冻结接口
170	- JPEG -> base64 -> MiMo(每帧) -> cJSON 解析 -> 3 帧去抖 -> observation_t
171	- mock/真实双路径 (-DPERCEPTION_MOCK)，默认 mock 可回退
172	- 历史环形缓冲 60 条 + host 单测 (mock 57 项 / MiMo 链路)
173	
174	Co-Authored-By: Claude <noreply@anthropic.com>"
175	```
176	
177	---
178	
179	## 5. push 并开 PR
180	
181	### 5.1 push 到你的 fork
182	```bash
183	git push -u origin feat/perception-mimo
184	```
185	
186	### 5.2 开 PR
187	- 到你的 fork 页面，点 **Compare & pull request**。
188	- base 选团队仓库的 `main`（或团队指定分支），head 选你的 `feat/perception-mimo`。
189	- 标题建议：
190	  `feat: 视觉感知模块 perception（每帧调 MiMo 识图）`
191	- 正文建议（直接复制）：
192	
193	```markdown
194	## 说明
195	实现「FOCUS AIoT」视觉感知层：输入 JPEG，每帧调用 MiMo 识图，输出 observation_t
196	供 behavior 模块做时序分析。只做单帧空间识别，不做行为判断。
197	
198	## 改动
199	- 新增 perception/perception.c + perception_internal.h（主实现）
200	- 新增 tests/（mock 单测 / wifi_http_post 联调 stub / MiMo 链路单测）
201	- Makefile / CMakeLists 加 CSRCS，Kconfig 加 mock 开关（默认 y）
202	
203	## 契约（已冻结）
204	Request:  {"image":"<base64>","width":320,"height":240}
205	Response: {"code":0,"data":{person:{detected,bbox}, phone:{detected,near_hand},
206	           head_pose:{pitch,yaw}, hand_motion_score, confidence}}
207	
208	## 测试
209	- mock 单测：57 checks, 0 failed
210	- MiMo 链路单测：验证每帧调用次数、响应解析、失败重试、三种错误码
211	
212	## 待确认
213	- MiMo 鉴权方式（header / query / body）需与张沐泽、郭黄亦昕确认，g_api_key 已预留
214	- api/perception.h 使用仓库冻结版，未改动
215	```
216	
217	---
218	
219	## 6. CLA（开源仓库必做，否则 bot 会卡住）
220	
221	1. 打开 `openvela.com/#/community/cla`，用 GitHub 账号签名。
222	2. 回 PR 评论区，发一条：`/check-cla`
223	3. 等 CI / bot 状态变绿。
224	
225	---
226	
227	## 7. 常见坑速查
228	
229	| 现象 | 原因 / 解决 |
230	|---|---|
231	| commit 报 `Please tell me who you are` | 没配 git user.name/email，见 §1.3 |
232	| push 401/403 | token 过期或泄露，换新 token（§1.4） |
233	| `api/perception.h` 被覆盖 | 撤回改动，用仓库冻结版，字段签名必须一致 |
234	| MiMo 链路单测编译失败 | 缺 cJSON，见 §3.2 |
235	| mock 单测在 Windows 报 `clock_gettime64` | 加 `-lwinpthread`；Linux/openvela 不用 |
236	| 真机调不通 | mock 开关没关 / MiMo endpoint+token 没填，见 §3.3 |
237	| PR 被 bot 要求签 CLA | 见 §6 |
238	

---

### [2026-08-28 16:25:20] AI

[思考] Now I understand the full picture. There's already a PR_STEPS.md for 周礼航's perception module. The user now wants "一个可以 pr 的文件夹" — a folder ready to PR, combining both modules.

The PR_STEPS.md is excellent — it shows the exact repo structure (`app/hello_app/`), which files go in, which don't (api/*.h frozen), commit message, PR body, CLA steps, common pitfalls.

So the user wants a single PR-ready folder that mirrors the repo structure `app/hello_app/` and contains the files to commit.

Let me design the PR folder. Based on PR_STEPS.md, the repo structure is:
```
app/hello_app/
├── api/                    (frozen, NOT in PR)
├── perception/
│   ├── perception.c
│   └── perception_internal.h
├── behavior/
│   ├── behavior.c
│   ├── behavior_config.c
│   └── behavior_internal.h
├── tests/
│   ├── test_perception.c
│   ├── wifi_http_post_stub.c
│   ├── test_mimo_cloud.c
│   └── test_behavior.c
├── Makefile               (modify CSRCS)
├── CMakeLists.txt         (modify CSRCS)
└── Kconfig                (add mock switch)
```

So the PR folder should contain:
1. `app/hello_app/perception/perception.c` + `perception_internal.h`
2. `app/hello_app/behavior/behavior.c` + `behavior_config.c` + `behavior_internal.h`
3. `app/hello_app/tests/test_perception.c`, `test_behavior.c`, `wifi_http_post_stub.c`, `test_mimo_cloud.c`
4. A PR body (PR_DESCRIPTION.md or PR_BODY.md)
5. Build integration notes

The user wants ONE folder that's PR-ready. I'll create `C:\temp\focus_pr\` with the correct repo-mirroring structure, copy all the source files, and include a PR_DESCRIPTION.md + the combined commit/PR instructions.

Actually, let me reconsider the naming. The user said "可以 pr 的文件夹". The PR_STEPS.md already documents the whole process for perception. Now I should produce a similar consolidated folder + PR body for BOTH modules (perception + behavior together).

Wait — but is it a good idea to combine both modules into ONE PR? The two modules are by different people (周礼航 and 赵思涵). In a team project, they'd typically be separate PRs. But the user is asking for "一个" (one) folder. 

Hmm. Let me think. The user might be the one doing everything (or a coordinator). They want one folder they can PR. I'll create one folder containing both modules, but I should structure it clearly so they CAN split into two PRs if needed. Actually, to keep it simple and match "一个文件夹", I'll do one folder with both modules, and in the PR description note the modules are separable.

Actually, wait — let me reconsider. Maybe I'm overcomplicating. The user said "我要一个可以pr的文件夹！" with emphasis. They want the deliverable folder. Let me just create it cleanly:

`C:\temp\focus_pr\` — a folder that mirrors the repo additions, ready to commit/PR.

Structure:
```
focus_pr/
├── PR_DESCRIPTION.md          ← PR 正文（复制即用）
├── COMMIT.md                  ← commit 信息 + 操作步骤（简化版 PR_STEPS）
└── app/hello_app/
    ├── perception/
    │   ├── perception.c
    │   └── perception_internal.h
    ├── behavior/
    │   ├── behavior.c
    │   ├── behavior_config.c
    │   └── behavior_internal.h
    └── tests/
        ├── test_perception.c
        ├── test_behavior.c
        ├── wifi_http_post_stub.c
        └── test_mimo_cloud.c
```

The api/*.h files are NOT included (frozen). The Makefile/CMakeLists/Kconfig changes go in the PR_DESCRIPTION or a BUILD_CHANGES file.

Now, there's a question of HOW to create this folder: I need to copy the actual source files. I can use bash `cp` to copy them, which is more reliable than re-writing them via Write (avoids transcription errors). Let me use `cp` commands.

The source files:
- perception: `C:\temp\focus_perception\perception\perception.c`, `perception_internal.h`
- behavior: `C:\temp\focus_behavior\behavior\behavior.c`, `behavior_config.c`, `behavior_internal.h`
- tests: 
  - `C:\temp\focus_perception\tests\test_perception.c`
  - `C:\temp\focus_perception\tests\wifi_http_post_stub.c`
  - `C:\temp\focus_perception\tests\test_mimo_cloud.c`
  - `C:\temp\focus_behavior\tests\test_behavior.c`

Let me use bash to create the directory structure and copy files. Then write the PR_DESCRIPTION.md and COMMIT/README for the PR folder.

Actually, I also need to think about whether the behavior tests should also go into `tests/`. Yes. And the behavior README — should it go into the repo? PR_STEPS.md says README is optional. I'll include a combined README note in the PR folder's PR_DESCRIPTION but keep the actual repo files minimal (source + tests).

Let me also reconsider: should the PR folder include a `README.md` for each module (going into the repo)? PR_STEPS.md says README is optional "可进仓库，可选". I'll skip copying READMEs into the PR (to keep it minimal), but mention them.

Actually, to make the folder truly complete and reviewable, I might include the READMEs too. But the user asked for a minimal "可以 pr" folder. Let me include just the essential source + tests, plus PR_DESCRIPTION.md. I'll keep the READMEs out of the PR folder (they're dev docs, and the PR_DESCRIPTION covers the summary).

Let me now also think: do I need to fix any include paths when copying? The files use `../api/perception.h`, `../perception/perception_internal.h`, `../behavior/behavior_internal.h` etc. In the PR folder structure:
- `app/hello_app/perception/perception.c` includes `../api/perception.h` (→ app/hello_app/api/perception.h, frozen, exists) ✓ and `perception_internal.h` (→ same dir) ✓
- `app/hello_app/behavior/behavior.c` includes `../api/behavior.h`, `../api/perception.h`, `behavior_internal.h` ✓
- `app/hello_app/tests/test_perception.c` includes `../api/perception.h`, `../perception/perception_internal.h` ✓
- `app/hello_app/tests/test_behavior.c` includes `../api/behavior.h`, `../api/perception.h`, `../behavior/behavior_internal.h` ✓

All `../` paths resolve correctly in the repo (api/, perception/, behavior/, tests/ are siblings). 

So I can copy verbatim. The files are already correct.

Now let me write the PR folder. Plan:
1. Create directory structure + copy files via bash `cp`.
2. Write `PR_DESCRIPTION.md` (PR title + body, combined for both modules, or two PRs noted).
3. Write `提交步骤.md` (simplified commit steps, referencing the existing PR_STEPS.md conventions, with combined commit message).

Actually, the existing PR_STEPS.md is very thorough for perception. For the combined PR, I should produce a similar but combined doc. But the user just wants "一个可以pr的文件夹" — the folder with files + a PR description. Let me include:
- `PR_DESCRIPTION.md` — the PR body text to paste.
- Maybe a short `README_提交说明.md` — how to commit (branch, git add, commit message).

Let me keep it focused. I'll create:
```
focus_pr/
├── PR_DESCRIPTION.md      ← PR 标题+正文（复制即用）
├── 提交清单.md            ← 文件清单 + commit 命令
└── app/hello_app/...      ← 要提交的源文件（按仓库结构）
```

Let me first verify the copy works and the whole thing still compiles from the PR folder structure (using a temporary api/ shim or referencing the existing api headers). Actually, to verify compilation from the PR folder, I'd need api/ headers present. Since api/ is frozen and not in the PR, I can do a verification build by temporarily symlinking or copying the api headers, but that's extra. 

Actually, a cleaner verification: I can compile the tests from the PR folder by adding an include path to the existing api headers. But the tests use `../api/...` relative includes, which won't resolve without an api/ folder at `app/hello_app/api/`.

For verification purposes, I could create a temporary `app/hello_app/api/` with the reference copies (and mark it clearly as "本地测试用，不提交"), compile, then... but that pollutes the PR folder.

Alternatively, I can just trust that the files are verbatim copies of already-verified-compiling code, and the only thing that changes is the directory name (focus_perception → app/hello_app), which doesn't affect `../` relative includes (they resolve the same way). So the files WILL compile in the repo structure. I don't strictly need to re-verify, but a quick verification is nice.

Let me do a verification: after copying, I'll create a temporary api/ folder inside the PR structure (with the reference headers), compile both test binaries, confirm pass, then DELETE the temporary api/ folder (so the PR folder stays clean, no frozen headers). This gives confidence without polluting.

Actually, simpler: I'll verify by compiling in a temp directory that mirrors the final structure WITH api headers, confirm it works, then create the clean PR folder via cp (without api). The cp is verbatim so it's guaranteed identical. I already verified both modules compile separately. The only new thing is the combined structure, which I've reasoned about. 

Let me just do a clean verification after copying: create the PR folder, add a temporary `api/` (reference copies) just for a compile check, compile+run both tests, then remove the temp api/ and report. This is the most trustworthy.

Let me proceed:

Step 1: Create structure and copy files.
Step 2: Write PR_DESCRIPTION.md and 提交清单.md.
Step 3: Temp-verify compile with a shim api/, then remove shim.

Let me write the bash commands. I'll use `mkdir -p` and `cp`.

Let me plan the PR folder path: `C:\temp\focus_pr`.

Actually, should I name it something more descriptive? Like `C:\temp\focus_pr` or `C:\temp\PR_视觉行为`. The user said "可以pr的文件夹". Let me name it `C:\temp\focus_pr`. Clear enough. Or maybe `C:\temp\hello_app_pr`. Hmm. I'll go with `C:\temp\focus_pr`.

Wait, actually, let me reconsider — maybe name it to reflect it's the hello_app additions. The repo path is `app/hello_app/`. A PR folder named `focus_pr` with `app/hello_app/` inside is fine and clear.

Let me do the copy now.

Let me write a single bash command that creates dirs and copies all files, then lists the result.

---

### [2026-08-28 16:25:21] AI

PR_STEPS.md 已经把仓库结构写清楚了（`app/hello_app/`，`api/*.h` 冻结不提交）。我来按这个结构建一个**可直接提交的 PR 文件夹**，把两个模块的源文件按仓库路径放好，并附上 PR 正文。

---

### [2026-08-28 16:25:24] AI

[工具调用] Bash: {"command": "set -e\nPR=/c/temp/focus_pr\nrm -rf \"$PR\"\nmkdir -p \"$PR/app/hello_app/perception\" \"$PR/app/hello_app/behavior\" \"$PR/app/hello_app/tests\"\n\n# 视觉感知 (周礼航)\ncp /c/temp/focus_perception/perception/perception.c          \"$PR/app/hello_app/perception/\"\ncp /c/temp/focus_perception/perception/perception_internal.h \"$PR/app/hello_app/perception/\"\n\n# 行为分析 (赵思涵)\ncp /c/temp/focus_behavior/behavior/behavior.c                \"$PR/app/hello_app/behavior/\"\ncp /c/temp/focus_behavior/behavior/behavior_config.c         \"$PR/app/hello_app/behavior/\"\ncp /c/temp/focus_behavior/behavior/behavior_internal.h       \"$PR/app/hello_app/behavior/\"\n\n# 单测\ncp /c/temp/focus_perception/tests/test_perception.c          \"$PR/app/hello_app/tests/\"\ncp /c/temp/focus_perception/tests/wifi_http_post_stub.c      \"$PR/app/hello_app/tests/\"\ncp /c/temp/focus_perception/tests/test_mimo_cloud.c          \"$PR/app/hello_app/tests/\"\ncp /c/temp/focus_behavior/tests/test_behavior.c              \"$PR/app/hello_app/tests/\"\n\necho \"=== 目录结构 ===\"\nfind \"$PR\" -type f | sort", "description": "Create PR-ready folder with correct repo structure and copy source files"}

---

### [2026-08-28 16:25:41] 用户

[工具结果] === 目录结构 ===
/c/temp/focus_pr/app/hello_app/behavior/behavior.c
/c/temp/focus_pr/app/hello_app/behavior/behavior_config.c
/c/temp/focus_pr/app/hello_app/behavior/behavior_internal.h
/c/temp/focus_pr/app/hello_app/perception/perception.c
/c/temp/focus_pr/app/hello_app/perception/perception_internal.h
/c/temp/focus_pr/app/hello_app/tests/test_behavior.c
/c/temp/focus_pr/app/hello_app/tests/test_mimo_cloud.c
/c/temp/focus_pr/app/hello_app/tests/test_perception.c
/c/temp/focus_pr/app/hello_app/tests/wifi_http_post_stub.c

---

### [2026-08-28 16:25:45] AI

[思考] Now let me verify the files compile correctly from the PR folder structure by adding a temporary api/ shim (reference copies), compiling both tests, then removing the shim.

Let me do the verification build.

---

### [2026-08-28 16:25:46] AI

现在验证这些文件在仓库结构下能编译通过（临时放 `api/` 参考头文件只用于编译，之后删掉，因为仓库里已有冻结版）：

---

### [2026-08-28 16:25:49] AI

[工具调用] Bash: {"command": "set -e\nPR=/c/temp/focus_pr\ncd \"$PR/app/hello_app\"\n\n# 临时放参考头文件(仅本地编译验证用, 仓库里已有冻结版, 不会提交)\nmkdir -p api\ncp /c/temp/focus_perception/api/perception.h api/\ncp /c/temp/focus_behavior/api/behavior.h      api/\n\necho \"=== 1) perception mock 单测 ===\"\ngcc -Wall -Wextra -Werror -DPERCEPTION_MOCK perception/perception.c tests/test_perception.c -o /tmp/tp 2>&1\n/tmp/tp\n\necho \"\"\necho \"=== 2) behavior 单测 ===\"\ngcc -Wall -Wextra -Werror behavior/behavior.c behavior/behavior_config.c tests/test_behavior.c -o /tmp/tb 2>&1\n/tmp/tb\n\n# 清理临时 api 头文件 (冻结版在仓库里, 不在 PR 里)\nrm -rf api\necho \"\"\necho \"=== 清理后最终结构 ===\"\ncd \"$PR\" && find . -type f | sort", "description": "Verify both modules compile from repo structure, then clean up temp headers"}

---

### [2026-08-28 16:25:55] 用户

[工具结果] === 1) perception mock 单测 ===
ld.lld: error: undefined symbol: clock_gettime64
>>> referenced by C:/Users/user/AppData/Local/Temp/perception-dc8e0e.o:(perception_monotonic_ms)
clang-22: error: linker command failed with exit code 1 (use -v to see invocation)
/usr/bin/bash: line 12: /tmp/tp: No such file or directory

=== 2) behavior 单测 ===
ALL TESTS PASSED

=== 清理后最终结构 ===
./app/hello_app/behavior/behavior.c
./app/hello_app/behavior/behavior_config.c
./app/hello_app/behavior/behavior_internal.h
./app/hello_app/perception/perception.c
./app/hello_app/perception/perception_internal.h
./app/hello_app/tests/test_behavior.c
./app/hello_app/tests/test_mimo_cloud.c
./app/hello_app/tests/test_perception.c
./app/hello_app/tests/wifi_http_post_stub.c

---

### [2026-08-28 16:26:01] AI

[思考] The behavior test passed. The perception mock test failed with `undefined symbol: clock_gettime64` — this is the known Windows issue mentioned in PR_STEPS.md: "mock 单测在 Windows 报 clock_gettime64 → 加 -lwinpthread；Linux/openvela 不用".

So on this Windows machine, I need `-lwinpthread` to link clock_gettime. This is a known Windows-only issue, not a code problem. On Linux/openvela it's fine.

Let me re-run the perception test with `-lwinpthread` to confirm it actually passes (the code is correct, just needs the pthread lib on Windows for clock_gettime).

The PR_STEPS.md already documents this. But let me verify it passes with the flag to be thorough, since I'm claiming the module works.

---

### [2026-08-28 16:26:02] AI

perception 测试在 Windows 上缺 `clock_gettime` 链接库（这是已知问题，PR_STEPS.md 里也写了：Windows 要加 `-lwinpthread`，Linux/openvela 不需要）。加上再验证：

---

### [2026-08-28 16:26:04] AI

[工具调用] Bash: {"command": "set -e\nPR=/c/temp/focus_pr\ncd \"$PR/app/hello_app\"\nmkdir -p api\ncp /c/temp/focus_perception/api/perception.h api/\n\necho \"=== perception mock 单测 (加 -lwinpthread, 仅 Windows 需要) ===\"\ngcc -Wall -Wextra -Werror -DPERCEPTION_MOCK perception/perception.c tests/test_perception.c -o /tmp/tp -lwinpthread 2>&1\n/tmp/tp\n\nrm -rf api", "description": "Re-run perception test with -lwinpthread on Windows"}

---

### [2026-08-28 16:26:09] 用户

[工具结果] === perception mock 单测 (加 -lwinpthread, 仅 Windows 需要) ===
== test_base64 ==
== test_math_helpers ==
== test_debounce ==
== test_process_and_history ==

结果: 57 checks, 0 failed

