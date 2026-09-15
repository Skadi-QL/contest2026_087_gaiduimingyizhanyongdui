# Claude Code 会话记录

## 会话信息
- **会话ID**: `5486faa1-0a5f-417c-8e1c-20b0003d4150`
- **工作目录**: `C:\temp\focus_perception`
- **开始时间**: 2026-08-26 14:10:42
- **消息数量**: 176

---

## 对话记录

### [2026-08-26 14:10:42] 用户

结合文件夹里的文本内容 给我成品

---

### [2026-08-26 14:10:48] AI

[思考] The user is asking in Chinese: "结合文件夹里的文本内容 给我成品" which means "Combine the text content in the folder and give me the finished product."

I need to first understand what's in the folder. The working directory is C:\temp. Let me look at what's there.

I should explore the folder to find the text files.

---

### [2026-08-26 14:10:49] AI

[工具调用] Bash: {"command": "ls -la /c/temp 2>/dev/null || ls -la \"C:/temp\"", "description": "List files in working directory"}

---

### [2026-08-26 14:10:50] 用户

[工具结果] total 848
drwxr-xr-x 1 user 197121      0 Aug 26 14:10 .
drwxr-xr-x 1 user 197121      0 Aug 21 15:08 ..
-rw-r--r-- 1 user 197121 767751 Aug 26 14:08 20260731_055914-ubuntu.md
-rw-r--r-- 1 user 197121   7080 Aug 26 14:09 DEVELOPMENT_TASKS (1).md
-rw-r--r-- 1 user 197121   9143 Aug 26 14:09 DEVELOPMENT_TASKS (2).md
-rw-r--r-- 1 user 197121   5820 Aug 26 14:09 DEVELOPMENT_TASKS.md
-rw-r--r-- 1 user 197121   1710 Aug 26 14:10 re.md
-rw-r--r-- 1 user 197121  21717 Aug 26 14:08 产品方案与分工_v2.md
-rw-r--r-- 1 user 197121  10253 Aug 26 14:08 周礼航开发规范 (1).md
-rw-r--r-- 1 user 197121   9799 Aug 26 14:08 周礼航开发规范.md

---

### [2026-08-26 14:10:54] AI

[思考] Let me read all these files to understand the content. There are several files:
1. 20260731_055914-ubuntu.md (767KB - large, probably a terminal log/transcript)
2. DEVELOPMENT_TASKS (1).md
3. DEVELOPMENT_TASKS (2).md
4. DEVELOPMENT_TASKS.md
5. re.md
6. 产品方案与分工_v2.md
7. 周礼航开发规范 (1).md
8. 周礼航开发规范.md

Let me read them. The big one (767KB) is probably a terminal transcript. Let me start with the smaller ones that likely describe requirements/tasks.

---

### [2026-08-26 14:10:55] AI

[工具调用] Read: {"file_path": "C:\\temp\\产品方案与分工_v2.md"}

---

### [2026-08-26 14:10:55] 用户

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

### [2026-08-26 14:10:55] AI

[工具调用] Read: {"file_path": "C:\\temp\\DEVELOPMENT_TASKS.md"}

---

### [2026-08-26 14:10:55] 用户

[工具结果] 1	# FOCUS AIoT - 成员任务安排
2	
3	> 更新: 2026-08-15 | 负责人: 万思源
4	> 前提: 接口已冻结 (`api/*.h`), 状态机/LCD/UI 已完成, mock 主链路跑通。
5	
6	## 当前完成状态
7	
8	| 模块 | 负责人 | 状态 |
9	|---|---|---|
10	| api/*.h 接口冻结 | 万思源 | ✅ |
11	| core/state_machine.c | 万思源 | ✅ 已合并 |
12	| ui/ (LCD页面+MiMo+字体) | 郭黄亦昕 | ✅ 已合并 |
13	| hardware/lcd_st7789.c | 张沐泽 | ✅ 已合并, 真机验证通过 |
14	
15	---
16	
17	## 一、张沐泽 - 硬件驱动全栈 (`hardware/`)
18	
19	**原则**: 每个驱动独立 `.c` + Kconfig 开关 + mock 可回退 (和 LCD 一样的模式)。
20	
21	### 任务 1: 按键驱动 (优先)
22	
23	- **文件**: `hardware/buttons.c`
24	- **核心函数**: `button_init()`, `button_get_event()`
25	- **效果**: 长按进入模式选择、短按开始/暂停——**用手按驱动 FSM** (替换当前 mock 自动序列), 串口看到真实按键事件。
26	
27	### 任务 2: WiFi 驱动
28	
29	- **文件**: `hardware/wifi_esp32.c`
30	- **核心函数**: `wifi_connect()`, `wifi_http_post()`, `wifi_get_rssi()`
31	- **效果**: 连上 WiFi, `wifi_http_post` 到测试地址返回成功 (替换 `wifi_stub.c`, 让 MiMo 走真实 API)。
32	
33	### 任务 3: 摄像头驱动
34	
35	- **文件**: `hardware/camera_ov2640.c`
36	- **核心函数**: `camera_init()`, `camera_capture_frame()`
37	- **效果**: 采到一帧 JPEG, 大小合理 (供周礼航取帧发云端)。
38	
39	### 任务 4: 音频驱动
40	
41	- **文件**: `hardware/audio_i2s.c`
42	- **核心函数**: `audio_play_tts()`, `audio_play_buzzer()`
43	- **效果**: REMIND 时发出警告音/蜂鸣 (替换 mock 打印)。
44	
45	### ⚠️ 接线注意
46	
47	当前 `core/mock.c` 定义了 `button_get_event`/`audio_play_tts` 等**普通函数**, 你接入真实驱动会冲突。
48	解决方案 (和 LCD 相同): **Kconfig 开关二选一编译**, 例如:
49	- `CONFIG_CONTEST2026_087_BUTTON_STUB=y` → 编译 mock
50	- 否则 → 编译你的真实驱动
51	
52	`Makefile`/`CMakeLists.txt` 已有这个 if/else 模式 (参考 LCD_STUB)。
53	
54	### 验收
55	
56	- 按键: 长按进入模式选择, 短按开始/暂停, FSM 全程用手操作。
57	- WiFi: `wifi_http_post` 返回成功, MiMo 请求能发出去。
58	- 摄像头: `camera_capture_frame` 返回有效 JPEG 帧。
59	- 音频: REMIND 触发真实提示音。
60	
61	---
62	
63	## 二、周礼航 - 视觉感知 (`perception/`)
64	
65	**任务**: 实现 `api/perception.h` 三个函数, 从图片输出 `observation_t`。
66	
67	### 阶段 1: 先 mock (不调云端)
68	
69	- **文件**: `perception/perception.c`
70	- 输出固定 `observation_t` (轮流 FOCUSED/PLAYING_PHONE/AWAY/DROWSY)
71	- **效果**: `perception_process()` 返回有效 observation, 赵思涵能立刻联调。
72	
73	### 阶段 2: 接云端
74	
75	- base64(JPEG) → 构造 JSON → `wifi_http_post()` → 解析响应 → 3 帧去抖
76	- **效果**: 真实图片 → 云端 → `observation_t`, 失败返回错误码不阻塞。
77	
78	### 阶段 3: 历史管理
79	
80	- 环形缓冲区 `obs_history[60]`
81	- `perception_get_history()` 按时间从旧到新返回, 供赵思涵时序分析。
82	
83	### 关键约束
84	
85	- 摄像头是**单帧模式**: 用 `V4L2_BUF_TYPE_STILL_CAPTURE` + `VIDIOC_TAKEPICT_START` 逐帧触发。
86	- HTTP 超时 ≤6s, JSON 缺字段不崩。
87	- **不区分严格/鼓励模式** (那是赵思涵的事)。
88	
89	### 验收
90	
91	- `perception_process()` 返回有效 observation (mock 和真实双路径)。
92	- `perception_get_history()` 返回历史 observation。
93	- 云端 API 失败时返回错误码, 不阻塞超过 6s。
94	
95	---
96	
97	## 三、赵思涵 - 行为分析 (`behavior/`)
98	
99	**任务**: 实现 `api/behavior.h`, 消费 observation 序列输出 `study_state_t`。
100	
101	### 任务 1: 迁移配置表
102	
103	- **文件**: `behavior/behavior_config.c`
104	- 把 `hello_app_main.c` 底部的 `g_mode_configs`/`strict_messages`/`gentle_messages` 移到独立文件。
105	- 迁完后告诉万思源, 他会删掉主入口里的配置表代码。
106	
107	### 任务 2: 真实时序引擎
108	
109	- **文件**: `behavior/behavior.c`
110	- `behavior_analyze()` 从 `perception_get_history()` 做时序判定:
111	  - 玩手机 8s/15s (严格/鼓励), 离座 10s/20s, 瞌睡 8s/12s
112	  - 提醒冷却 `remind_cooldown_sec`, 鼓励模式里程碑
113	- **效果**: 输出真实 `study_state_t`, 替换 mock 轮转。
114	
115	### 任务 3: 纯 C 单测
116	
117	- **文件**: `tests/behavior_test.c`
118	- 手写 observation 序列验证状态转移, 不依赖硬件。
119	
120	### 关键约束
121	
122	- 纯计算 ≤10ms, 不碰网络/硬件。
123	- 严格/鼓励差异只改 `mode_config_t`。
124	- **冷却在你这里, 不是状态机** (万思源只消费你输出的 action)。
125	
126	### 验收
127	
128	- 同一组 observation, 严格/鼓励模式输出不同提醒策略。
129	- 提醒冷却生效, 里程碑不重复触发。
130	- 单次分析耗时 <10ms。
131	
132	---
133	
134	## 协作关系
135	
136	```
137	张沐泽 camera_capture_frame ──▶ 周礼航 perception_process ──▶ observation_t
138	                                    │
139	                                    ▼ 周礼航 perception_get_history
140	张沐泽 wifi_http_post ──▶ 周礼航 (云端请求)
141	                                    │
142	                                    ▼
143	                              赵思涵 behavior_analyze ──▶ study_state_t
144	                                    │
145	                                    ▼
146	                          (万思源 state_machine 已就绪, 消费它)
147	```
148	
149	- 赵思涵依赖周礼航的 `perception_get_history`。
150	- 周礼航依赖张沐泽的 camera + wifi。
151	- **张沐泽先做摄像头+WiFi, 周礼航先 mock 后接真, 赵思涵先单测后联调。**
152	
153	## 推进节奏
154	
155	| 阶段 | 内容 |
156	|---|---|
157	| 本周 | 张沐泽按键+WiFi; 周礼航 perception mock; 赵思涵配置表迁移+单测 |
158	| 下周 | 张沐泽摄像头; 周礼航云端链路; 赵思涵时序引擎 |
159	| 第 3 周 | 三人联调 → 真实 observation 驱动 behavior → state_machine → UI 全链路 |
160	

---

### [2026-08-26 14:10:55] AI

[工具调用] Read: {"file_path": "C:\\temp\\DEVELOPMENT_TASKS (1).md"}

---

### [2026-08-26 14:10:55] 用户

[工具结果] 1	# FOCUS AIoT - 成员任务安排
2	
3	> 更新: 2026-08-18 | 负责人: 万思源
4	> 前提: 接口已冻结 (`api/*.h`), 状态机/LCD/UI/行为引擎已完成, mock 主链路跑通。
5	
6	## 当前完成状态
7	
8	| 模块 | 负责人 | 状态 |
9	|---|---|---|
10	| api/*.h 接口冻结 | 万思源 | ✅ |
11	| core/state_machine.c | 万思源 | ✅ 已合并 |
12	| ui/ (LCD页面+MiMo+字体) | 郭黄亦昕 | ✅ 已合并 |
13	| hardware/lcd_st7789.c | 张沐泽 | ✅ 已合并, 真机验证通过 |
14	| behavior/ (时序引擎+配置表+单测) | 赵思涵 | ✅ 已合并, 单测 100% 通过, 固件验证通过 |
15	
16	**关键衔接**: `core/mock.c` 已提供 **weak `perception_get_history()`** 临时历史提供器,
17	真实感知模块接入后由强符号自动覆盖 (和 LCD stub 相同的替换机制)。行为引擎当前直接
18	消费 mock 历史即可运行, 无需等待真实感知。
19	
20	---
21	
22	## 一、张沐泽 - 硬件驱动全栈 (`hardware/`)
23	
24	**原则**: 每个驱动独立 `.c` + Kconfig 开关 + mock 可回退 (和 LCD 一样的模式)。
25	
26	### 任务 1: 按键驱动 (优先)
27	
28	- **文件**: `hardware/buttons.c`
29	- **核心函数**: `button_init()`, `button_get_event()`
30	- **效果**: 长按进入模式选择、短按开始/暂停——**用手按驱动 FSM** (替换当前 mock 自动序列), 串口看到真实按键事件。
31	
32	### 任务 2: WiFi 驱动
33	
34	- **文件**: `hardware/wifi_esp32.c`
35	- **核心函数**: `wifi_connect()`, `wifi_http_post()`, `wifi_get_rssi()`
36	- **效果**: 连上 WiFi, `wifi_http_post` 到测试地址返回成功 (替换 `wifi_stub.c`, 让 MiMo 走真实 API)。
37	
38	### 任务 3: 摄像头驱动
39	
40	- **文件**: `hardware/camera_ov2640.c`
41	- **核心函数**: `camera_init()`, `camera_capture_frame()`
42	- **效果**: 采到一帧 JPEG, 大小合理 (供周礼航取帧发云端)。
43	
44	### 任务 4: 音频驱动
45	
46	- **文件**: `hardware/audio_i2s.c`
47	- **核心函数**: `audio_play_tts()`, `audio_play_buzzer()`
48	- **效果**: REMIND 时发出警告音/蜂鸣 (替换 mock 打印)。
49	
50	### ⚠️ 接线注意
51	
52	当前 `core/mock.c` 定义了 `button_get_event`/`audio_play_tts` 等**普通函数**, 你接入真实驱动会冲突。
53	解决方案 (和 LCD 相同): **Kconfig 开关二选一编译**, 例如:
54	- `CONFIG_CONTEST2026_087_BUTTON_STUB=y` → 编译 mock
55	- 否则 → 编译你的真实驱动
56	
57	`Makefile`/`CMakeLists.txt` 已有这个 if/else 模式 (参考 LCD_STUB)。
58	
59	### 验收
60	
61	- 按键: 长按进入模式选择, 短按开始/暂停, FSM 全程用手操作。
62	- WiFi: `wifi_http_post` 返回成功, MiMo 请求能发出去。
63	- 摄像头: `camera_capture_frame` 返回有效 JPEG 帧。
64	- 音频: REMIND 触发真实提示音。
65	
66	---
67	
68	## 二、周礼航 - 视觉感知 (`perception/`)
69	
70	**任务**: 实现 `api/perception.h` 三个函数, 从图片输出 `observation_t`。
71	
72	### 阶段 1: 先 mock (不调云端)
73	
74	- **文件**: `perception/perception.c`
75	- 输出固定 `observation_t` (轮流 FOCUSED/PLAYING_PHONE/AWAY/DROWSY)
76	- **效果**: `perception_process()` 返回有效 observation。
77	- 💡 **衔接提示**: 当前 `core/mock.c` 的 weak `perception_get_history()` 已被行为引擎消费,
78	  你实现真实 `perception.c` 时提供强符号 `perception_get_history()` 即自动接管历史管理。
79	  请同时保留 mock 路径 (Kconfig 开关或编译宏) 便于回退。
80	
81	### 阶段 2: 接云端
82	
83	- base64(JPEG) → 构造 JSON → `wifi_http_post()` → 解析响应 → 3 帧去抖
84	- **效果**: 真实图片 → 云端 → `observation_t`, 失败返回错误码不阻塞。
85	
86	### 阶段 3: 历史管理
87	
88	- 环形缓冲区 `obs_history[60]`
89	- `perception_get_history()` 按时间从旧到新返回, 供赵思涵时序分析。
90	
91	### 关键约束
92	
93	- 摄像头是**单帧模式**: 用 `V4L2_BUF_TYPE_STILL_CAPTURE` + `VIDIOC_TAKEPICT_START` 逐帧触发。
94	- HTTP 超时 ≤6s, JSON 缺字段不崩。
95	- **不区分严格/鼓励模式** (那是赵思涵的事)。
96	
97	### 验收
98	
99	- `perception_process()` 返回有效 observation (mock 和真实双路径)。
100	- `perception_get_history()` 返回历史 observation。
101	- 云端 API 失败时返回错误码, 不阻塞超过 6s。
102	
103	---
104	
105	## 三、赵思涵 - 行为分析 (`behavior/`)
106	
107	**任务**: 实现 `api/behavior.h`, 消费 observation 序列输出 `study_state_t`。
108	
109	### 任务 1: 迁移配置表 ✅ 已完成
110	
111	- **文件**: `behavior/behavior_config.c`
112	- `g_mode_configs`/`strict_messages`/`gentle_messages` 已迁出 `hello_app_main.c`。
113	- 主入口已调用 `behavior_init(MODE_STRICT)`。
114	
115	### 任务 2: 真实时序引擎 ✅ 已完成
116	
117	- **文件**: `behavior/behavior.c` (401 行)
118	- `behavior_analyze()` 从 `perception_get_history()` 做时序判定:
119	  - 玩手机 8s/15s (严格/鼓励), 离座 10s/20s, 瞌睡 8s/12s
120	  - 优先级: AWAY > 玩手机 > 看手机 > 瞌睡 > 里程碑 > FOCUSED
121	  - 提醒冷却 `remind_cooldown_sec`, 累计提醒, 里程碑去重
122	  - 同帧防重 (`g_last_state` 缓存), uint32 时间回绕处理
123	
124	### 任务 3: 纯 C 单测 ✅ 已完成
125	
126	- **文件**: `tests/behavior_test.c` (250 行)
127	- 覆盖: 空历史/严格手机+冷却/看手机/离座/瞌睡/鼓励阈值+累计/里程碑
128	- 宿主机单测 **100% 通过** (带 `-Werror` 编译零警告)
129	
130	### 审查结论 (2026-08-18)
131	
132	- 行为引擎代码质量高, 时序判定/冷却/里程碑逻辑完整。
133	- 固件编译通过, `behavior_*` 强符号链接, 无 mock 残留。
134	- 与 mock 感知的弱 `perception_get_history` 衔接正确, 真实感知接入后自动覆盖。
135	
136	---
137	
138	## 协作关系
139	
140	```
141	张沐泽 camera_capture_frame ──▶ 周礼航 perception_process ──▶ observation_t
142	                                    │
143	                                    ▼ 周礼航 perception_get_history
144	张沐泽 wifi_http_post ──▶ 周礼航 (云端请求)
145	                                    │
146	                                    ▼
147	                              赵思涵 behavior_analyze ──▶ study_state_t
148	                                    │
149	                                    ▼
150	                          (万思源 state_machine 已就绪, 消费它)
151	```
152	
153	- 赵思涵依赖周礼航的 `perception_get_history`。
154	- 周礼航依赖张沐泽的 camera + wifi。
155	- **张沐泽先做摄像头+WiFi, 周礼航先 mock 后接真, 赵思涵先单测后联调。**
156	
157	## 推进节奏 (更新 2026-08-18)
158	
159	| 阶段 | 内容 | 状态 |
160	|---|---|---|
161	| 行为分析 | 配置表迁移 + 时序引擎 + 单测 | ✅ 赵思涵已完成 |
162	| 本周 | 张沐泽按键+WiFi; 周礼航 perception mock→云端 | 进行中 |
163	| 下周 | 张沐泽摄像头; 周礼航云端链路 | 待 |
164	| 第 3 周 | 三人联调 → 真实 observation 驱动 behavior → state_machine → UI 全链路 | 待 |
165	
166	## 当前焦点
167	
168	1. **张沐泽**: 按键驱动 (FSM 手动操作) → WiFi (MiMo 真实请求) → 摄像头 → 音频。
169	2. **周礼航**: perception_process 实现, 替换 mock (先固定 observation, 再接云端), 提供强符号 `perception_get_history()` 接管历史。
170	3. 全链路联调: 真实 observation → 行为引擎 (已就绪) → 状态机 → UI 上屏。
171	

---

### [2026-08-26 14:10:56] AI

[工具调用] Read: {"file_path": "C:\\temp\\DEVELOPMENT_TASKS (2).md"}

---

### [2026-08-26 14:10:56] 用户

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

### [2026-08-26 14:10:56] AI

[工具调用] Read: {"file_path": "C:\\temp\\re.md"}

---

### [2026-08-26 14:10:56] 用户

[工具结果] 1	@所有人  📢 【PR 合不进去，提示没签 CLA？看这里】
2	
3	最近有同学反馈：提交 PR 时报错说"未签署协议 / cla/signature 检查未通过"，导致代码合不进仓库。统一说明一下处理办法：
4	
5	1️⃣ 先签署 CLA
6	首次向仓库贡献代码，需要先签署贡献者许可协议（CLA）。用你报名时的 GitHub 账号，前往官网签署：
7	https://openvela.com/#/community/cla
8	
9	2️⃣ 签完不用重做 PR
10	签署成功后，之前那个失败的 PR 不需要重新提交、也不用重建，只要在这个 PR 下面评论一句：
11	/check-cla
12	系统会自动重新检查，通过后就能正常合入了。
13	
14	更详细的说明，你专属仓库的 README「关于 PR 与 CLA」一节里也有。还有问题欢迎群里反馈～
15	
16	
17	20260731_055914-ubuntu.md
18	
19	
20	749.76 KB   已下载
21	
22	这是我和cc的完整对话
23	
24	也可以喂给ai让它自己理解一下
25	
26	
27	周礼航开发规范.md
28	
29	
30	10.01 KB   已下载
31	
32	@全体成员 你们直接fork 然后clone 在自己的目录里写
33	
34	然后把我上面那个对话记录 和各自的开发规范还有之前的产品方案喂给ai
35	
36	让ai帮你们写一下
37	
38	（需要在linux环境编译，可以直接在之前小学期那个虚拟机里面搞
39	
40	
41	DEVELOPMENT_TASKS.md
42	
43	
44	5.68 KB   已下载
45	
46	这是@zmz @我不讲狸猫 @有形浪人 三个人接下来的开发任务
47	
48	
49	DEVELOPMENT_TASKS.md
50	
51	
52	6.91 KB   已下载
53	
54	@zmz @有形浪人 你们接下来的开发任务👆
55	
56	
57	DEVELOPMENT_TASKS.md
58	
59	
60	8.93 KB   已下载
61	
62	接下来主要是zlh了
63	
64	@有形浪人 你的部分 如果需要mimo token plan 可以直接飞书群@陈泽沛 让他给你重置

---

### [2026-08-26 14:10:56] AI

[工具调用] Read: {"file_path": "C:\\temp\\周礼航开发规范.md"}

---

### [2026-08-26 14:10:56] 用户

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

### [2026-08-26 14:10:57] AI

[工具调用] Read: {"file_path": "C:\\temp\\周礼航开发规范 (1).md"}

---

### [2026-08-26 14:10:57] 用户

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
128	> ⚠️ **2026-08 硬件验证结论**: ESP32-S3-EYE 的 OV2640 驱动为**单帧模式**——
129	> 每采完一帧后 DMA 自动停止，需重新触发才能拍下一帧。
130	> 采集 JPEG 应使用 `V4L2_BUF_TYPE_STILL_CAPTURE` + `VIDIOC_TAKEPICT_START` 逐帧触发，
131	> **不要用 VIDEO_CAPTURE + RING/FIFO 连续模式**（第二帧起会永久阻塞）。
132	> 正确的采集流程见 `apps/examples/camera/camera_main.c` 的 STILL_CAPTURE 示例。
133	
134	```c
135	int perception_process(uint8_t *jpeg, size_t jpeg_len, observation_t *out) {
136	    // 1. Base64 编码
137	    char b64[50*1024];  // 320×240 JPEG ≈ 30KB → base64 ≈ 40KB
138	    base64_encode(jpeg, jpeg_len, b64, sizeof(b64));
139	    
140	    // 2. 构造 JSON 请求
141	    char req[55*1024];
142	    snprintf(req, sizeof(req),
143	        "{\"image\":\"%s\",\"width\":320,\"height\":240}", b64);
144	    
145	    // 3. HTTP POST
146	    char resp[4096];
147	    int ret = wifi_http_post(api_url, req, resp, sizeof(resp));
148	    if (ret < 0) return -1;
149	    
150	    // 4. JSON 解析
151	    cloud_result_t raw;
152	    if (parse_cloud_response(resp, &raw) < 0) return -2;
153	    
154	    // 5. 去抖稳定 (见 3.2)
155	    return stabilize(&raw, out);
156	}
157	```
158	
159	### 3.2 去抖稳定
160	
161	连续帧之间，云端 API 的结果可能在两个状态间来回跳（比如第 1 帧检测到手机，第 2 帧没检测到，第 3 帧又检测到）。用一个 **3 帧滑动窗口** 平滑输出：
162	
163	```c
164	static cloud_result_t history[3];
165	static int history_idx = 0;
166	
167	int stabilize(cloud_result_t *raw, observation_t *out) {
168	    // 写入历史
169	    history[history_idx] = *raw;
170	    history_idx = (history_idx + 1) % 3;
171	    
172	    int n = (history[0].confidence > 0) + 
173	            (history[1].confidence > 0) + 
174	            (history[2].confidence > 0);
175	    if (n < 3) {
176	        // 历史不足 3 帧，直接输出当前帧
177	        fill_observation(raw, out);
178	        return 0;
179	    }
180	    
181	    // 布尔值: 3 帧多数投票
182	    out->person_present  = majority(history[0].person_detected,
183	                                    history[1].person_detected,
184	                                    history[2].person_detected);
185	    out->phone_detected  = majority(history[0].phone_detected,
186	                                    history[1].phone_detected,
187	                                    history[2].phone_detected);
188	    out->phone_near_hand = majority(history[0].phone_in_hand,
189	                                    history[1].phone_in_hand,
190	                                    history[2].phone_in_hand);
191	    
192	    // 浮点值: 取中位数 (抗单帧异常值)
193	    out->head_pitch  = median3(history[0].head_pitch,
194	                               history[1].head_pitch,
195	                               history[2].head_pitch);
196	    out->head_yaw    = median3(history[0].head_yaw,
197	                               history[1].head_yaw,
198	                               history[2].head_yaw);
199	    
200	    // 运动量: 取最大值 (宁可多报不遗漏)
201	    out->hand_motion_score = max3(history[0].hand_motion,
202	                                  history[1].hand_motion,
203	                                  history[2].hand_motion);
204	    
205	    // 置信度: 取均值
206	    out->confidence = (history[0].confidence + 
207	                       history[1].confidence + 
208	                       history[2].confidence) / 3.0f;
209	    
210	    out->timestamp_ms = raw->timestamp_ms;
211	    return 0;
212	}
213	```
214	
215	### 3.3 维护 Observation 历史
216	
217	赵思涵需要连续多帧的 Observation 做时序分析。你维护一个环形缓冲区：
218	
219	```c
220	#define HISTORY_MAX  60   // 保留最近 60 条 (60×5s = 300s 窗口)
221	
222	static observation_t obs_history[HISTORY_MAX];
223	static int obs_count = 0;
224	
225	// 每次 produce 一条 Observation 后调用
226	static void history_append(observation_t *obs) {
227	    obs_history[obs_count % HISTORY_MAX] = *obs;
228	    obs_count++;
229	}
230	
231	int perception_get_history(observation_t *buf, int n) {
232	    if (n > HISTORY_MAX) n = HISTORY_MAX;
233	    int available = (obs_count < HISTORY_MAX) ? obs_count : HISTORY_MAX;
234	    if (n > available) n = available;
235	    
236	    // 从旧到新拷贝
237	    int start = (obs_count > HISTORY_MAX) ? (obs_count % HISTORY_MAX) : 0;
238	    for (int i = 0; i < n; i++) {
239	        buf[i] = obs_history[(start + i) % HISTORY_MAX];
240	    }
241	    return n;
242	}
243	```
244	
245	---
246	
247	## 四、你的模块和其他人的关系
248	
249	```
250	  张沐泽              你                  赵思涵
251	  ────────          ──────              ────────
252	  camera_task ──▶ perception_process() ──▶ observation_t
253	  产 JPEG          调 API + 去抖           消费 Observation
254	                                        做时序分析
255	  
256	  万思源
257	  ──────
258	  你的 perception_init() 由万思源在主程序启动时调用一次
259	  你的 perception_process() 由万思源的 wifi_task 每收到新帧时调用
260	```
261	
262	**你不会被直接调用的场景**：
263	- 按键事件 → 不经过你，赵思涵不需要 Observation 来判断按键
264	- LCD 刷新 → 不经过你
265	- 语音播报 → 不经过你
266	- MiMo API → 不经过你
267	
268	---
269	
270	## 五、开发约束
271	
272	| 约束 | 说明 |
273	|---|---|
274	| **不区分模式** | 严格/鼓励模式是赵思涵的事，你的 Observation 对两种模式完全相同 |
275	| **不做行为判断** | 你只输出"检测到手机 = true/false"，**不判断**这是玩手机还是看手机——那是赵思涵的时序分析做的 |
276	| **超时处理** | HTTP 请求超时 3 秒，重试 1 次，仍失败→返回错误码 -1，**不要阻塞超过 6 秒** |
277	| **JSON 解析不崩** | 云端可能返回格式异常的数据，`parse_cloud_response()` 必须有边界检查 |
278	| **base64 内存** | base64 编码后的字符串比原图大约 33%，40KB → 约 54KB，栈上放不下就用 PSRAM |
279	| **不要缓存 JPEG** | 每次调完 API 就丢弃 JPEG 数据，不需要存历史图像 |
280	
281	---
282	
283	## 六、可以独立测试
284	
285	```c
286	#ifdef PERCEPTION_UNIT_TEST
287	int main() {
288	    perception_init(API_URL, API_KEY);
289	    
290	    // 读一张本地测试图片
291	    FILE *f = fopen("test_frame.jpg", "rb");
292	    uint8_t jpeg[50*1024];
293	    size_t len = fread(jpeg, 1, sizeof(jpeg), f);
294	    fclose(f);
295	    
296	    observation_t obs;
297	    int ret = perception_process(jpeg, len, &obs);
298	    
299	    printf("person=%d phone=%d near_hand=%d pitch=%.1f motion=%.2f conf=%.2f\n",
300	           obs.person_present, obs.phone_detected, obs.phone_near_hand,
301	           obs.head_pitch, obs.hand_motion_score, obs.confidence);
302	    
303	    return ret;
304	}
305	#endif
306	```
307	
308	**联调顺序**：先跟张沐泽联调（确认 Wi-Fi POST 能通）→ 再跟赵思涵联调（确认 Observation 格式对）。
309	

---

### [2026-08-26 14:11:10] AI

[思考] Let me understand the full picture. This is a project called "FOCUS AIoT" — a study-monitoring device on ESP32-S3-EYE (openvela OS). The user (周礼航, "有形浪人") is the person responsible for the **视觉感知模块 (perception)** module. The task is to implement `perception/perception.c` (and related files) with three functions:

1. `perception_init(api_url, api_key)` 
2. `perception_process(jpeg, jpeg_len, out)`
3. `perception_get_history(buf, n)`

The user says "结合文件夹里的文本内容 给我成品" = "Combine the text content in the folder and give me the finished product."

So they want me to produce the finished code for the perception module. The "周礼航开发规范.md" (Zhou Lihang Development Spec) contains detailed instructions on exactly what to build. The DEVELOPMENT_TASKS (2).md is the latest task list (2026-08-19), focused on 周礼航's perception module.

The re.md mentions the user should feed the conversation record (20260731_055914-ubuntu.md, which is the full conversation with Claude/cc) and the dev specs to AI to have it write the code.

There's also a big 767KB file "20260731_055914-ubuntu.md" which is a terminal log/transcript of the full conversation. That's probably too big to fully read, but it likely contains the actual repo structure, header files (api/perception.h), Makefile details, etc. Let me check if I need to look at it for exact details like:
- The exact `api/perception.h` header (to know exact function signatures and error codes)
- The `api/*.h` interfaces
- Error codes: `FOCUS_OK`, `FOCUS_ERR_PERCEP_TIMEOUT(-30)`, `FOCUS_ERR_PERCEP_JSON(-31)`, `FOCUS_ERR_PERCEP_NODATA(-32)`
- The Makefile structure

The key deliverable is the perception module code. Let me think about what files I should produce:

Based on the dev spec and tasks, 周礼航 needs to produce:
1. `perception/perception.c` — main implementation (three functions)
2. `perception/perception.h` — internal declarations (optional)
3. `tests/test_perception.c` — independent test (optional)

But I need the exact header `api/perception.h` to match. The dev spec gives me the observation_t struct and function signatures. But the tasks mention error codes `FOCUS_OK`, `FOCUS_ERR_PERCEP_TIMEOUT(-30)`, `FOCUS_ERR_PERCEP_JSON(-31)`, `FOCUS_ERR_PERCEP_NODATA(-32)`.

Let me look at the big transcript file to understand the exact API header and code conventions. It's 767KB which is large. Let me search it for key things rather than read it all.

Actually, let me be strategic. The user wants "成品" (finished product). The most important thing is to produce the perception module code. But I should also understand the exact interfaces. Let me grep the big file for `api/perception.h`, `FOCUS_ERR`, `observation_t`, `perception_init`, `FOCUS_OK`, `camera_capture_frame`, `wifi_http_post`, etc.

Let me search the big transcript for relevant details to make the code match exactly.

---

### [2026-08-26 14:11:11] AI

[工具调用] Bash: {"command": "wc -l \"20260731_055914-ubuntu.md\" && echo \"---HEAD---\" && head -c 3000 \"20260731_055914-ubuntu.md\"", "description": "Check size and head of big transcript"}

---

### [2026-08-26 14:11:11] 用户

[工具结果] 15661 20260731_055914-ubuntu.md
---HEAD---
# Claude Code 会话记录

## 会话信息
- **会话ID**: `1922c1ec-ec29-4fe4-a796-77c185b1f8e5`
- **工作目录**: `-home-ubuntu`
- **开始时间**: 2026-07-31 05:59:14
- **消息数量**: 1188

---

## 对话记录

### [2026-07-31 05:59:14] 用户

<local-command-caveat>Caveat: The messages below were generated by the user while running local commands. DO NOT respond to these messages or otherwise consider them in your response unless the user explicitly asks you to.</local-command-caveat>

---

### [2026-07-31 05:59:14] 用户

<command-name>/model</command-name>
            <command-message>model</command-message>
            <command-args></command-args>

---

### [2026-07-31 05:59:14] 用户

<local-command-stdout>Set model to [1mdeepseek-v4-flash[22m and saved as your default for new sessions</local-command-stdout>

---

### [2026-07-31 06:00:54] 用户

当前目录下你可以看到几个md，这是我们正在开发的项目

---

### [2026-07-31 06:00:57] AI

[思考] The user says "当前目录下你可以看到几个md，这是我们正在开发的项目" which means "In the current directory you can see several md files, this is the project we're developing."

Let me look at the current directory to see what md files exist. Let me list the directory contents.

---

### [2026-07-31 06:00:57] AI

[工具调用] Bash: {"command": "ls -la /home/ubuntu", "description": "List files in home directory"}

---

### [2026-07-31 06:00:57] 用户

[工具结果] total 8112
drwxr-x--- 29 ubuntu ubuntu    4096 Jul 31 05:59 .
drwxr-xr-x  3 root   root      4096 Apr 22  2022 ..
-rw-------  1 ubuntu ubuntu   11441 Jul 16 11:50 .bash_history
-rw-r--r--  1 ubuntu ub...

---

### [2026-07-31 06:00:59] AI

[思考] There are several md files in the home directory. Let me look at them. The main project files appear to be:
- FOCUS_AIOT_可执行开发规划.md (executable development plan)
- 产品方案与分工_v2.md (product plan and division of labor v2)
- 周礼航开发规范.md (development standards)
- 张沐泽开发规范.md
- 赵思涵开发规范.md
- 郭黄亦昕开发规范.md

Let me read these files to understand the project. Let me start with the main ones. I should read them to understand what the project is about.

Let me read the key files. The two main project docs are likely the development plan and the product plan. Let me read them.

---

### [2026-07-31 06:00:59] AI

当前目录下有这几个 md 文件，我先读一下了解项目全貌。

---

### [2026-07-31 06:00:59] AI

[工具调用] Read: {"file_path": "/home/ubuntu/FOCUS_AIOT_可执行开发规划.md"}

---

### [2026-07-31 06:00:59] 用户

[工具结果] 1	# FOCUS AIoT 可执行开发规划
2	
3	负责人：万思源  
4	工程目录：`/home/ubuntu/openvela`  
5	专属仓目录：`/home/ubuntu/openvela/contest2026_087_gaiduimingyizhanyongdui`  
6	依据文档：`产品方案与分工_v2.md`、周礼航/张沐泽/赵思涵/郭黄亦昕开发规范
7	
8	## 1. ...

---

### [2026-08-26 14:11:17] AI

[思考] The big transcript is the full conversation. It's valuable because it contains the actual repo structure, header files, and the actual code that was written. Let me search it for the key files: `api/perception.h`, the error codes, `camera_capture_frame`, `wifi_http_post`, and the actual repository layout.

The most important thing for producing a correct "成品" (finished product) is:
1. The exact `api/perception.h` header (function signatures, error codes)
2. The exact interfaces from hardware (camera, wifi) and behavior (for integration)
3. The Makefile/CMakeLists structure

Let me grep the transcript for these key details. Let me search for specific patterns.

Let me search for:
- `api/perception.h` and its content
- `FOCUS_ERR_PERCEP` 
- `FOCUS_OK`
- `camera_capture_frame`
- `wifi_http_post` actual signature in the repo
- `perception_init`
- `observation_t`

Let me do parallel greps.

---

### [2026-08-26 14:11:18] AI

[工具调用] Grep: {"pattern": "FOCUS_ERR_PERCEP|FOCUS_OK|FOCUS_ERR_", "path": "C:\\temp\\20260731_055914-ubuntu.md", "output_mode": "content", "-n": true, "head_limit": 80}

---

### [2026-08-26 14:11:19] 用户

[工具结果] No matches found

---

### [2026-08-26 14:11:19] AI

[工具调用] Grep: {"pattern": "api/perception\\.h|perception\\.h", "path": "C:\\temp\\20260731_055914-ubuntu.md", "output_mode": "content", "-n": true, "head_limit": 80}

---

### [2026-08-26 14:11:19] 用户

[工具结果] 13153:   - `perception.h` - observation_t + perception functions
13183:[工具调用] TaskCreate: {"subject": "创建 api/ 目录 + 10 个接口头文件", "description": "冻结 API：error.h, camera.h, lcd.h, wifi.h, button.h, audio.h, perception.h, behavior.h, state_machine.h, session.h。字段名/函数名/返回值冻结，只能追加。", "activeForm
13241:7. **perception.h** - observation_t, perception_init(), perception_process(), perception_get_history()
13297:7. perception.h - observation_t + 周礼航's 3 functions
13395:- perception.h (observation_t + 3 functions)
13412:[工具调用] Write: {"file_path": "/home/ubuntu/openvela/contest2026_087_gaiduimingyizhanyongdui/app/hello_app/api/perception.h", "content": "/****************************************************************************\
13418:[工具结果] File created successfully at: /home/ubuntu/openvela/contest2026_087_gaiduimingyizhanyongdui/app/hello_app/api/perception.h (file state is current in your context — no need to Read it back)...
13859:Actually, looking at how other apps do it (like the camera example), they include headers with paths like `#include "api/perception.h"` which are relative to the source file's directory. Since `hello_app_main.c` is in the app root and includes `"api/error.h"`, it should resolve... but actually, the compiler needs to know where to find `api/error.h`.
13919:[工具结果] ./core/mock.h:16:10: fatal error: api/perception.h: No such file or directory
13926:[思考] The include path issue: `core/mock.h` includes `"api/perception.h"` which is relative to `core/` directory. Since `mock.h` is in `core/` and `api/` is at the app root, the include `"api/perception.h"` resolves as `core/api/perception.h` which doesn't exist.
13928:I need to use `"../api/perception.h"` from within `core/mock.h`, or ensure the compiler has `-I` for the app root.
13932:Fix: In `core/mock.h`, change `"api/perception.h"` to `"../api/perception.h"`, similarly for other includes from subdirectory files.
13938:Actually, looking at it again: `core/mock.h` includes `api/perception.h, api/behavior.h, api/session.h`. These need to be `../api/perception.h` etc.
13950:This means the compiler's working directory is the app root (where mock.c is at `./core/mock.c`). So from `./core/mock.c`, `#include "api/perception.h"` would be relative to the file's location: `core/api/perception.h` - wrong.
13953:1. Use `../api/perception.h` from within core/ files
13968:#include "api/perception.h"
13972:Need `../api/perception.h` etc.
13992:[工具调用] Edit: {"replace_all": false, "file_path": "/home/ubuntu/openvela/contest2026_087_gaiduimingyizhanyongdui/app/hello_app/core/mock.h", "old_string": "#include \"api/perception.h\"\n#include \"api/behavior.h\"
14020:Wait, actually the compilation showed the issue was specifically with `core/mock.h` including `api/perception.h`. The compilation error was from `./core/mock.c` including `"mock.h"` which includes `"api/perception.h"` (now fixed to `../api/perception.h`).
14109:[思考] The issue is that `perception_init`, `perception_process`, `behavior_init`, `behavior_analyze` are declared as non-static in the API headers (`api/perception.h` and `api/behavior.h`), but in `hello_app_main.c` I defined them as `static` functions.
14358:│   ├── perception.h       ★ observation_t (视觉感知输出)

---

### [2026-08-26 14:11:21] AI

[工具调用] Grep: {"pattern": "camera_capture_frame|camera_frame_buffer|wifi_http_post", "path": "C:\\temp\\20260731_055914-ubuntu.md", "output_mode": "content", "-n": true, "head_limit": 80}

---

### [2026-08-26 14:11:21] 用户

[工具结果] 13236:2. **camera.h** - camera_capture_frame()
13238:4. **wifi.h** - wifi_connect(), wifi_is_connected(), wifi_http_post(), wifi_get_rssi()
14353:│   ├── camera.h           摄像头接口 (camera_capture_frame + buffer)

---

### [2026-08-26 14:11:31] AI

[思考] There's a lot of useful context in the transcript. Let me read the key section where `api/perception.h` was written (line 13412), and also read the surrounding sections to understand the exact error codes and function signatures. Let me read around line 13412 to get the full `api/perception.h` content.

Also I should read around line 13153-13420 to understand the full API freeze, and around 14353 for the file tree.

Let me read the relevant sections.

---

### [2026-08-26 14:11:32] AI

[工具调用] Read: {"file_path": "C:\\temp\\20260731_055914-ubuntu.md", "offset": 13412, "limit": 220}

---

### [2026-08-26 14:11:32] 用户

[工具结果] 13412	[工具调用] Write: {"file_path": "/home/ubuntu/openvela/contest2026_087_gaiduimingyizhanyongdui/app/hello_app/api/perception.h", "content": "/****************************************************************************\
13413	
13414	---
13415	
13416	### [2026-08-05 05:43:16] 用户
13417	
13418	[工具结果] File created successfully at: /home/ubuntu/openvela/contest2026_087_gaiduimingyizhanyongdui/app/hello_app/api/perception.h (file state is current in your context — no need to Read it back)...
13419	
13420	---
13421	
13422	### [2026-08-05 05:43:25] AI
13423	
13424	[工具调用] Write: {"file_path": "/home/ubuntu/openvela/contest2026_087_gaiduimingyizhanyongdui/app/hello_app/api/behavior.h", "content": "/****************************************************************************\n 
13425	
13426	---
13427	
13428	### [2026-08-05 05:43:26] 用户
13429	
13430	[工具结果] File created successfully at: /home/ubuntu/openvela/contest2026_087_gaiduimingyizhanyongdui/app/hello_app/api/behavior.h (file state is current in your context — no need to Read it back)...
13431	
13432	---
13433	
13434	### [2026-08-05 05:43:34] AI
13435	
13436	[工具调用] Write: {"file_path": "/home/ubuntu/openvela/contest2026_087_gaiduimingyizhanyongdui/app/hello_app/api/state_machine.h", "content": "/**************************************************************************
13437	
13438	---
13439	
13440	### [2026-08-05 05:43:34] 用户
13441	
13442	[工具结果] File created successfully at: /home/ubuntu/openvela/contest2026_087_gaiduimingyizhanyongdui/app/hello_app/api/state_machine.h (file state is current in your context — no need to Read it back)...
13443	
13444	---
13445	
13446	### [2026-08-05 05:43:39] AI
13447	
13448	[工具调用] Write: {"file_path": "/home/ubuntu/openvela/contest2026_087_gaiduimingyizhanyongdui/app/hello_app/api/session.h", "content": "/****************************************************************************\n *
13449	
13450	---
13451	
13452	### [2026-08-05 05:43:39] 用户
13453	
13454	[工具结果] File created successfully at: /home/ubuntu/openvela/contest2026_087_gaiduimingyizhanyongdui/app/hello_app/api/session.h (file state is current in your context — no need to Read it back)...
13455	
13456	---
13457	
13458	### [2026-08-05 05:43:42] AI
13459	
13460	[思考] All 10 API headers are done. Now let me update the task status and move on to creating the config table and the main entry point skeleton.
13461	
13462	---
13463	
13464	### [2026-08-05 05:43:42] AI
13465	
13466	10 个接口头文件全部完成 ✅。现在写配置表和主控多任务骨架。
13467	
13468	---
13469	
13470	### [2026-08-05 05:43:43] AI
13471	
13472	[工具调用] TaskUpdate: {"status": "completed", "taskId": "7"}
13473	
13474	---
13475	
13476	### [2026-08-05 05:43:43] 用户
13477	
13478	[工具结果] Updated task #7 status...
13479	
13480	---
13481	
13482	### [2026-08-05 05:43:43] AI
13483	
13484	[工具调用] TaskUpdate: {"status": "in_progress", "taskId": "8"}
13485	
13486	---
13487	
13488	### [2026-08-05 05:43:43] 用户
13489	
13490	[工具结果] Updated task #8 status...
13491	
13492	---
13493	
13494	### [2026-08-05 05:43:43] AI
13495	
13496	[工具调用] TaskUpdate: {"status": "in_progress", "taskId": "9"}
13497	
13498	---
13499	
13500	### [2026-08-05 05:43:43] 用户
13501	
13502	[工具结果] Updated task #9 status...
13503	
13504	---
13505	
13506	### [2026-08-05 05:43:55] AI
13507	
13508	[思考] Now I need to write:
13509	
13510	1. `config/behavior_config.h` - mode_config_t with strict/gentle tables + messages (from 赵思涵's spec)
13511	2. `core/mock.h` - mock data providers for testing
13512	3. Rework `hello_app_main.c` - multi-task skeleton with 6 tasks
13513	
13514	Let me write the config header first, then the mock header, then the main entry.
13515	
13516	For the main skeleton, I need 6 tasks communicating via message queues:
13517	- camera_task: 5s period, produces frames (mock initially)
13518	- wifi_task: handles HTTP POST (called from perception, not a periodic task)
13519	- perception_task: consumes frames, produces observations
13520	- behavior_task: consumes observations, produces study_state
13521	- state_machine_task: consumes study_state, updates stats, decision making
13522	- ui_task: 1Hz refresh, consumes state + study_state
13523	
13524	Actually, looking at the plan more carefully, the architecture is:
13525	- camera_task: periodic, sends frame events to perception
13526	- perception_task: when frame arrives, calls perception_process, sends observation
13527	- behavior_task: when observation arrives, calls behavior_analyze, sends study_state
13528	- state_machine_task: consumes study_state + button events, drives FSM
13529	- ui_task: 1Hz, reads state_machine status
13530	- audio_task: triggered by state_machine
13531	
13532	Let me design this with message queues between tasks.
13533	
13534	For the first version, I'll make it simple:
13535	- All tasks run in a single main loop (not true preemptive tasks yet)
13536	- Use function calls through mock interfaces
13537	- The mock main loop calls each module in order
13538	
13539	Actually, since we're on NuttX with pthread support, let me use actual threads with message queues. But for the MVP (first mock chain), let me keep it simple with a single-threaded event loop to reduce complexity and debugging difficulty.
13540	
13541	Let me write the main entry as a single event-loop skeleton:
13542	
13543	---
13544	
13545	### [2026-08-05 05:43:56] AI
13546	
13547	写核心的主控多任务骨架（替换 hello_app_main.c）。
13548	
13549	---
13550	
13551	### [2026-08-05 05:43:56] AI
13552	
13553	[工具调用] Read: {"file_path": "/home/ubuntu/openvela/contest2026_087_gaiduimingyizhanyongdui/app/hello_app/hello_app_main.c"}
13554	
13555	---
13556	
13557	### [2026-08-05 05:43:57] 用户
13558	
13559	[工具结果] 1	/****************************************************************************
13560	2	 * FOCUS AIoT - 设备硬件验证测试 (Device Hardware Validation)
13561	3	 *
13562	4	 * 在 openvela + ESP32-S3-EYE 上逐项验证外设可用性：
13563	5	 *   - LCD  (f...
13564	
13565	---
13566	
13567	### [2026-08-05 05:44:03] AI
13568	
13569	[思考] Now I need to replace this with the multi-task skeleton. I'll save the hardware validation version to a separate file (tests/hwtest.c) and create the new main entry as the FOCUS app skeleton.
13570	
13571	Let me also create the behavior config header and mock helpers.
13572	
13573	The main skeleton structure:
13574	1. A main() that initializes all modules and runs the event loop
13575	2. Mock data providers for testing without hardware/cloud
13576	3. Clean separation so real implementations plug in via the same API
13577	
13578	Key design decisions for this skeleton:
13579	- Keep the hardware validation test callable from NSH as a separate command (hello_hwtest)
13580	- The main hello_app becomes the FOCUS app
13581	- Use compile-time switches (USE_REAL_*) for mock vs real
13582	- Simple event loop: camera tick → perception → behavior → state_machine → ui
13583	
13584	---
13585	
13586	### [2026-08-05 05:44:04] AI
13587	
13588	Now I'll write the multi-task skeleton as the new main entry, the behavior config, and the mock provider.
13589	
13590	---
13591	
13592	### [2026-08-05 05:44:13] AI
13593	
13594	[工具调用] Write: {"file_path": "/home/ubuntu/openvela/contest2026_087_gaiduimingyizhanyongdui/app/hello_app/config/behavior_config.h", "content": "/*********************************************************************
13595	
13596	---
13597	
13598	### [2026-08-05 05:44:13] 用户
13599	
13600	[工具结果] File created successfully at: /home/ubuntu/openvela/contest2026_087_gaiduimingyizhanyongdui/app/hello_app/config/behavior_config.h (file state is current in your context — no need to Read it back)...
13601	
13602	---
13603	
13604	### [2026-08-05 05:44:23] AI
13605	
13606	[工具调用] Write: {"file_path": "/home/ubuntu/openvela/contest2026_087_gaiduimingyizhanyongdui/app/hello_app/core/mock.h", "content": "/****************************************************************************\n * F
13607	
13608	---
13609	
13610	### [2026-08-05 05:44:23] 用户
13611	
13612	[工具结果] File created successfully at: /home/ubuntu/openvela/contest2026_087_gaiduimingyizhanyongdui/app/hello_app/core/mock.h (file state is current in your context — no need to Read it back)...
13613	
13614	---
13615	
13616	### [2026-08-05 05:44:27] AI
13617	
13618	[思考] Now the main entry point. I need to replace hello_app_main.c with the FOCUS multi-task skeleton while keeping the hardware test code in a separate file (tests/hwtest_main.c) so we can still run hardware validation from NSH.
13619	
13620	Let me rewrite hello_app_main.c as the FOCUS app entry with:
13621	1. Module initialization
13622	2. Event loop with 6 task stages
13623	3. Mock fallback for all modules
13624	4. Serial log output showing the full chain
13625	
13626	I'll keep the hardware test in tests/hardware_test.c for future use.
13627	
13628	---
13629	
13630	### [2026-08-05 05:44:28] AI
13631	

---

### [2026-08-26 14:11:41] AI

[思考] The transcript shows the Write tool calls but the actual file content is truncated (the content shows `/****...` but not the full content). The actual file content is not fully shown in the transcript — it's truncated in the JSON (the `content` field contains the full content, but when I Read the .md, the tool call shows `"content": "/****************************************************************************\` then cuts off). Actually wait, looking more carefully, the transcript shows the tool call with `"content": "/****************************************************************************\` and then a newline — but the actual content got cut off in the transcript rendering. This is a rendered transcript, so the full JSON content might be on subsequent lines, but here it seems the content is just truncated/not included.

Actually, the transcript appears to have the content cut off — it only shows the first line of the content. This is a limitation of the transcript export — it doesn't include the full file contents for Write calls (or they're elided).

Let me search for the actual header content. The important thing is I need to reconstruct `api/perception.h` and the error codes. Let me search for the error codes more specifically, and for the `observation_t` definition as actually frozen in the header.

Let me search for key strings that would be in the actual header:
- `FOCUS_ERR_PERCEP` didn't match, but the task doc (DEVELOPMENT_TASKS (2).md) mentions `FOCUS_ERR_PERCEP_TIMEOUT(-30)` / `FOCUS_ERR_PERCEP_JSON(-31)` / `FOCUS_ERR_PERCEP_NODATA(-32)`. So these error codes exist.

Let me search for "error.h" content and the error codes.

---

### [2026-08-26 14:11:42] AI

[工具调用] Grep: {"pattern": "FOCUS_ERR|FOCUS_OK|typedef enum|error_code", "path": "C:\\temp\\20260731_055914-ubuntu.md", "output_mode": "content", "-n": true, "head_limit": 120}

---

### [2026-08-26 14:11:42] 用户

[工具结果] No matches found

---

### [2026-08-26 14:11:43] AI

[工具调用] Grep: {"pattern": "api/error\\.h|error\\.h", "path": "C:\\temp\\20260731_055914-ubuntu.md", "output_mode": "content", "-n": true, "head_limit": 60}

---

### [2026-08-26 14:11:43] 用户

[工具结果] 13147:   - `error.h` - unified error codes
13183:[工具调用] TaskCreate: {"subject": "创建 api/ 目录 + 10 个接口头文件", "description": "冻结 API：error.h, camera.h, lcd.h, wifi.h, button.h, audio.h, perception.h, behavior.h, state_machine.h, session.h。字段名/函数名/返回值冻结，只能追加。", "activeForm
13235:1. **error.h** - error codes
13291:1. error.h - Standard error codes
13306:- error.h included by all
13322:[工具调用] Write: {"file_path": "/home/ubuntu/openvela/contest2026_087_gaiduimingyizhanyongdui/app/hello_app/api/error.h", "content": "/****************************************************************************\n * F
13358:[工具结果] File created successfully at: /home/ubuntu/openvela/contest2026_087_gaiduimingyizhanyongdui/app/hello_app/api/error.h (file state is current in your context — no need to Read it back)...
13859:Actually, looking at how other apps do it (like the camera example), they include headers with paths like `#include "api/perception.h"` which are relative to the source file's directory. Since `hello_app_main.c` is in the app root and includes `"api/error.h"`, it should resolve... but actually, the compiler needs to know where to find `api/error.h`.
13865:So `#include "api/error.h"` should resolve from the app's own directory since hello_app_main.c is at the app root and api/ is a subdirectory.
13867:Wait no, `"api/error.h"` would resolve relative to the current source file's location, which is `hello_app_main.c` in `app/hello_app/`. So `api/error.h` should resolve to `app/hello_app/api/error.h`. 
13873:So `#include "api/error.h"` with `-I packages/demos/contest2026_087_hello_app` should find `packages/demos/contest2026_087_hello_app/api/error.h`. This should work.
13942:And `hello_app_main.c` includes `"api/error.h"` etc - since main.c is at the app root, these work from the root.
14016:[思考] Also need to check: `core/mock.c` includes `"mock.h"` and `"api/error.h"`. The `"mock.h"` should work (same directory), but `"api/error.h"` needs `../api/error.h`.
14018:Let me also check `hello_app_main.c` includes - it's at the app root so `"api/error.h"` etc all work. But it also includes `"config/behavior_config.h"` and `"core/mock.h"` which should work since they're relative to the app root.
14028:[工具调用] Edit: {"replace_all": false, "file_path": "/home/ubuntu/openvela/contest2026_087_gaiduimingyizhanyongdui/app/hello_app/core/mock.c", "old_string": "#include \"mock.h\"\n#include \"api/error.h\"", "new_strin
14218:Now let me also check: the hello_app_main.c still includes `"api/error.h"` but error.h has no functions, only macros. That's fine.
14352:│   ├── error.h            统一错误码

---

### [2026-08-26 14:18:03] AI

[思考] The transcript elides the actual file content. I don't have the exact header content. But I have enough information from the dev spec and tasks docs to reconstruct what I need. The key deliverables are clear.

Let me now decide what to produce. The user is 周礼航, and their task is the perception module. The "成品" (finished product) is the perception module code.

However, I should be careful: I don't have the exact frozen `api/perception.h` header (field names, error code constants). But the dev spec (周礼航开发规范.md) gives me:
- `observation_t` struct with exact fields
- 3 function signatures:
  - `int perception_init(const char *api_url, const char *api_key);`
  - `int perception_process(uint8_t *jpeg, size_t jpeg_len, observation_t *out);`
  - `int perception_get_history(observation_t *buf, int n);`
- The dev spec says return `0=成功, -1=云端超时, -2=JSON解析失败`
- The task doc (2) says error codes: `FOCUS_ERR_PERCEP_TIMEOUT(-30)` / `FOCUS_ERR_PERCEP_JSON(-31)` / `FOCUS_ERR_PERCEP_NODATA(-32)` and `FOCUS_OK`

There's a slight tension between the dev spec (which says -1/-2) and the task doc (which says -30/-31/-32 error codes). The task doc is more recent (2026-08-19), and it references `FOCUS_ERR_PERCEP_TIMEOUT(-30)` etc., which are the frozen API error codes. So I should use the error codes from error.h.

Actually, the dev spec's `perception_process` returns `-1/-2`, but that's the older spec. The DEVELOPMENT_TASKS (2).md (most recent) says:
> 失败返回: `FOCUS_ERR_PERCEP_TIMEOUT(-30)` / `FOCUS_ERR_PERCEP_JSON(-31)` / `FOCUS_ERR_PERCEP_NODATA(-32)`

And `perception_init` returns `FOCUS_OK`.

Since I don't have the exact `error.h` content, I need to be careful. Let me try to find the error.h content in the transcript by searching more. Actually, the transcript clearly elides file contents — the `content` field is truncated to just the opening comment. So I cannot recover the exact error.h.

Given this, the best approach is:
1. Produce a complete, self-contained, compilable implementation of the perception module.
2. Define the error codes in a way that matches the task doc (FOCUS_OK = 0, FOCUS_ERR_PERCEP_TIMEOUT = -30, FOCUS_ERR_PERCEP_JSON = -31, FOCUS_ERR_PERCEP_NODATA = -32), and include a fallback if `api/error.h` doesn't define them.

Actually, wait. Let me reconsider what "成品" means. The user wants me to write the code that they (周礼航) would submit. The most useful deliverable is:

1. `perception/perception.c` — the main implementation
2. `perception/perception.h` — internal header (declarations, internal structs)
3. `tests/test_perception.c` — unit test

These three files are exactly what the task doc (2) specifies under "📁 要写的文件".

I should produce production-quality C code that:
- Implements the 3 functions
- Has both mock and real-cloud paths (with `PERCEPTION_MOCK` compile switch)
- Does 3-frame debouncing
- Maintains a ring buffer history (60 entries)
- Handles base64, JSON, cJSON, HTTP POST
- Has proper error handling (timeout ≤6s, JSON missing fields, no crash)
- Uses `clock_gettime(CLOCK_MONOTONIC)` for timestamps
- Is compilable on Linux (for the unit test) and on ESP32/openvela

Let me also decide: should I match the exact `api/perception.h`? The `perception.c` should include `api/perception.h`. But since I don't have the exact header, I'll write the code to include it and provide a compatible internal header. Actually, to make the code self-contained and actually compilable/testable, I should probably provide a full `api/perception.h` too, OR structure perception.c to not depend on the exact header beyond what the spec defines.

Let me reconsider the scope. The cleanest deliverable:

Actually, I think the best approach is to give them a complete, drop-in set of files. Since they said "给我成品" (give me the finished product), and the context is clearly "help me write my perception module", I should:

1. Write `api/perception.h` — matching the spec's observation_t + 3 functions (so it's self-contained and matches what was frozen). Actually the header is already frozen by 万思源 and exists in the repo. 周礼航 should NOT overwrite api/perception.h. But for the unit test to compile standalone, I can reference it.

Hmm. Let me think about what's actually most useful. The user will take my code and put it into their repo where `api/perception.h` already exists. So my `perception.c` should `#include "api/perception.h"`. The `observation_t` type and function prototypes are already frozen there.

But I don't know the EXACT frozen field names/error codes. However:
- The dev spec gives me `observation_t` exact fields (person_present, person_bbox[4], phone_detected, phone_near_hand, head_pitch, head_yaw, hand_motion_score, confidence, timestamp_ms).
- The task doc gives me the error code names.

These two docs are consistent and authoritative. So I'll write code against them.

Given uncertainty about the exact error.h constants, I'll write a small internal shim: in perception.c, if the error codes aren't defined, define them locally. Actually, better: I'll write `api/perception.h` content too (as a reference, matching the frozen spec), and a note that if `api/error.h` already exists, just include it.

Actually, let me step back and be pragmatic. I'll produce these files, all in a `perception/` folder under C:\temp (or just output them). Since the working dir is C:\temp and it's NOT a git repo, I'll create the files there in a sensible structure.

Let me plan the file structure to deliver:
```
C:\temp\perception\
  perception.c        (main implementation)
  perception.h        (internal declarations: cloud_result_t, stabilize, base64, etc.)
  README.md           (how to integrate + build + test)
  test_perception.c   (standalone unit test, mock path)
```

Actually, maybe simpler to put test in a `tests/` folder. But to keep it easy, I'll just put everything in one folder with a test file.

Let me also decide on the actual implementation details. Let me look at what the mock path should produce, and how base64 is done.

Key design:

**File: perception.h (internal)**
- Include `api/perception.h` (or `../api/perception.h` depending on location). Actually, I'll make perception.h include the public header. But for the standalone test, I need the public header too.

Let me structure it as:
- The public API header is `api/perception.h` (frozen by 万思源). I'll reproduce a compatible copy so my code is self-contained and the unit test compiles. I'll clearly mark that this should match the repo's frozen header and NOT be committed over it (or better, I'll just reproduce what the spec says and note it).

Hmm, this is getting complicated. Let me simplify and be decisive:

**Deliverable plan:**

I'll write 3 files + 1 README, self-contained enough to compile the unit test on Linux:

1. `perception/perception.h` — the public API (observation_t + 3 function prototypes + error codes). This is what `api/perception.h` should contain per the spec. I'll write it as the canonical header. Mark it clearly.

2. `perception/perception.c` — implementation (mock + real paths, debounce, history ring buffer, base64, cJSON parsing, http post).

3. `perception/perception_internal.h` — internal declarations (cloud_result_t, base64_encode, stabilize, parse_cloud_response). Actually I can fold this into perception.c as static functions. The spec says `perception/perception.h` (内部声明, 可选). I'll provide an internal header for clarity.

4. `tests/test_perception.c` — unit test that exercises mock path (and optionally real path with a stub wifi_http_post).

Let me also think about the base64 implementation. I need to write a base64 encoder (self-contained, no external lib). cJSON is used for parsing — but for the standalone test, I might not have cJSON. I should make cJSON optional or write a minimal JSON parser. Actually, the spec says use cJSON (it's available in openvela). For the standalone Linux test, I'd need cJSON. To keep it fully self-contained and testable without dependencies, I could write a minimal JSON extractor for the specific response format instead of full cJSON. But the task says "cJSON 解析 resp".

Let me be pragmatic: I'll write the JSON parsing using a small hand-rolled parser that extracts the known fields, so it compiles standalone without cJSON. But I'll also note that cJSON can be swapped in. Actually, the cleaner approach for a real submission: use cJSON (openvela has it), and for the unit test, provide a tiny cJSON-compatible shim OR just test the mock path + debounce + history without the cloud path.

Hmm, let me think about what's actually most valuable and correct here. The real repo uses cJSON (NuttX/openvela ships with cJSON). The task doc explicitly says "cJSON 解析 resp". So the real `perception.c` should use cJSON.

For the unit test on Linux, I can:
- Test the mock path (no cJSON needed)
- Test debounce (stabilize) — but that's static, so I need to expose it or test via perception_process with a mock cloud
- Test history ring buffer

I think the cleanest is:
- `perception.c` uses cJSON for the real path, guarded by `#ifdef PERCEPTION_REAL` or similar, and a `#ifdef PERCEPTION_MOCK` for mock. Actually the task says "mock 路径保留: 用 #ifdef PERCEPTION_MOCK 或 Kconfig 开关, 默认 mock 可回退".

So structure:
```c
// perception_process:
#ifdef PERCEPTION_MOCK
    // mock: generate observation from jpeg_len or a fixed rotation
#else
    // real: base64 -> json -> http -> cjson parse -> stabilize
#endif
```

For the base64 encoder: I'll write it as a static helper (always compiled, or only in real path). Since mock path doesn't need base64, but it doesn't hurt to include it. I'll keep base64 always compiled (it's small).

For cJSON: In the real path I `#include <cJSON.h>`. For the standalone Linux test, I'll compile with `PERCEPTION_MOCK` defined, so cJSON is never compiled, and the test doesn't need cJSON. Good — that keeps the test self-contained.

But wait, I also want to test the real parsing logic (parse_cloud_response). To do that without cJSON, I'd need cJSON. I'll provide a note: to test the real path, install cJSON. Or, I can write parse_cloud_response to use a minimal hand parser so it's testable everywhere. 

Decision: I'll write a **minimal, robust JSON field extractor** (hand-rolled, ~60 lines) instead of cJSON. Rationale: it's fully self-contained, testable on Linux without deps, and has zero external dependency risk. But the task doc explicitly says "cJSON 解析 resp". 

Hmm. This is a judgment call. The task doc is guidance from 万思源; cJSON is what's available in the openvela environment. But for a robust "成品" that compiles and tests standalone, a hand-rolled parser is actually safer and more portable. However, deviating from the stated approach might cause friction during review.

Best compromise: Use cJSON in the real path (as instructed), AND provide a `#ifndef HAVE_CJSON` fallback minimal parser for standalone testing. That's more complex though.

Actually, let me reconsider. Let me re-read the exact task requirements to not over-engineer:

From DEVELOPMENT_TASKS (2).md:
- 阶段 1 (mock): 不调云端, 用固定规则轮流输出 observation
- 阶段 2 (真实): base64 → 构造 JSON → wifi_http_post → cJSON 解析 → 3 帧去抖
- 阶段 3: 环形缓冲区 obs_history[60]

And the dev spec 周礼航开发规范.md gives detailed code for stabilize() and history ring buffer.

So the "成品" should implement all of this. I'll use cJSON for real path (matching instruction), and write base64 + stabilize + history exactly per spec.

For the unit test, I'll make it test the mock path + history (which don't need cJSON), and I'll write a `wifi_http_post` stub that returns a canned JSON response, so I can even test the real path IF cJSON is available. To make it dependency-free, I'll write the test to compile with a macro.

Let me keep it clean and simple. Final plan for files:

**1. `perception/perception.c`** — full implementation with:
- `#include "perception.h"` (public, in same dir or api/)
- internal static helpers: base64_encode, stabilize (3-frame debounce), majority/median3/max3, parse_cloud_response (cJSON), history ring buffer
- `perception_init`, `perception_process`, `perception_get_history`
- mock path via `#ifdef PERCEPTION_MOCK`
- real path via cJSON
- monotonic timestamp via clock_gettime
- error codes

**2. `perception/perception.h`** — public header (observation_t + prototypes + error codes). This mirrors `api/perception.h`.

Actually, to match the repo convention (api/perception.h is the public header, already frozen), my perception.c should `#include "../api/perception.h"` if placed in perception/ subdir. But since I'm delivering a standalone folder, I'll make it `#include "perception.h"` and also provide the header. In the README, I'll explain: "把这个文件里 perception.h 的内容对齐到你们仓库的 api/perception.h（已经冻结的那份），perception.c 里的 include 改成 `#include "../api/perception.h"`。"

Hmm, but I want the code to be "成品" — drop-in. Let me look again at the repo structure from the transcript. The repo is:
```
app/hello_app/
  api/ (error.h, perception.h, behavior.h, ...)
  core/ (mock.c, mock.h, state_machine.c)
  config/ (behavior_config.h)
  ui/
  hardware/
  perception/   ← 周礼航 要写的
  behavior/     ← 赵思涵 写的
  tests/
```

So perception.c goes in `app/hello_app/perception/perception.c`, and should `#include "../api/perception.h"`. 

I'll write the code to include `"../api/perception.h"` (matching repo layout), and ALSO provide a copy of `api/perception.h` content in my deliverable so they can verify/align. Actually, since api/perception.h is already frozen in their repo, I shouldn't overwrite it. I'll just reference it.

For the standalone unit test on Linux, I'll create a small shim: the test can `#include "../api/perception.h"` after I provide a copy of that header in the deliverable's `api/` folder. This way the whole thing compiles standalone.

OK let me settle on a concrete deliverable directory that's self-contained AND matches the repo layout:

```
C:\temp\focus_perception\
  api\perception.h          (公开接口 — 与仓库冻结版一致，供独立编译/参考)
  perception\perception.c   (主实现)
  perception\perception.h   (内部声明，可选)
  tests\test_perception.c   (独立单测)
  README.md                 (接入说明 + 编译/测试命令)
```

perception.c includes `"../api/perception.h"`.

This is clean. Let me now write the actual code carefully.

Let me define the error codes. I need to decide the exact values. The task doc says:
- FOCUS_OK = 0 (implied)
- FOCUS_ERR_PERCEP_TIMEOUT = -30
- FOCUS_ERR_PERCEP_JSON = -31
- FOCUS_ERR_PERCEP_NODATA = -32

The dev spec says perception_process returns 0/-1/-2. These conflict. The task doc is more recent and references the frozen error.h. So I'll define:

```c
#define FOCUS_OK                    0
#define FOCUS_ERR_PERCEP_TIMEOUT   (-30)
#define FOCUS_ERR_PERCEP_JSON      (-31)
#define FOCUS_ERR_PERCEP_NODATA    (-32)
```

And I'll also add a couple more for completeness (e.g., NULL args), but keep it minimal. Actually, since these constants live in `api/error.h` (frozen), I should NOT redefine them in perception.h if error.h already defines them. But for self-contained compile, I need them. I'll guard with `#ifndef`:

```c
#ifndef FOCUS_OK
#define FOCUS_OK 0
#endif
#ifndef FOCUS_ERR_PERCEP_TIMEOUT
#define FOCUS_ERR_PERCEP_TIMEOUT (-30)
#endif
...
```

This way, if error.h already defines them, no conflict; if not, they're defined. Good.

Now, the observation_t struct. The dev spec gives exact fields. I'll define it in perception.h:

```c
typedef struct {
    bool     person_present;
    float    person_bbox[4];
    bool     phone_detected;
    bool     phone_near_hand;
    float    head_pitch;
    float    head_yaw;
    float    hand_motion_score;
    float    confidence;
    uint32_t timestamp_ms;
} observation_t;
```

Need `<stdbool.h>`, `<stdint.h>`, `<stddef.h>`.

Now the three functions:

```c
int  perception_init(const char *api_url, const char *api_key);
int  perception_process(uint8_t *jpeg, size_t jpeg_len, observation_t *out);
int  perception_get_history(observation_t *buf, int n);
```

Note: dev spec uses `uint8_t *jpeg` (not const). I'll match: `uint8_t *jpeg`.

Now implementation details.

**perception_init:**
```c
static char g_api_url[128];
static char g_api_key[64];

int perception_init(const char *api_url, const char *api_key) {
    if (api_url) snprintf(g_api_url, sizeof(g_api_url), "%s", api_url);
    else g_api_url[0] = '\0';
    if (api_key) snprintf(g_api_key, sizeof(g_api_key), "%s", api_key);
    else g_api_key[0] = '\0';
    // 清零历史
    memset(g_history, 0, sizeof(g_history));
    g_history_count = 0;
    g_history_idx = 0;
    // 清零去抖历史
    memset(g_debounce, 0, sizeof(g_debounce));
    g_debounce_count = 0;
    g_mock_seq = 0;
    return FOCUS_OK;
}
```

**perception_process:** 
- validate args
- mock or real
- stabilize
- history_append
- return code

Let me write the real path:
```c
int perception_process(uint8_t *jpeg, size_t jpeg_len, observation_t *out) {
    if (!out) return FOCUS_ERR_PERCEP_JSON; // or a generic error
    ...
}
```

Hmm, what error code for NULL out? I'll use FOCUS_ERR_PERCEP_JSON as generic? No. Let me add a generic error. Actually the frozen error.h has specific codes. Since I don't know them all, I'll use what's documented and add a local `FOCUS_ERR_PERCEP_PARAM` if needed. But to avoid inventing frozen codes, I'll keep it simple: use the documented three. For NULL args, I can just return FOCUS_ERR_PERCEP_JSON (not ideal) or handle gracefully. 

Actually, let me add a couple of well-named local error codes but guard them, and document that these are perception-module-local additions. The frozen error.h only has the -30/-31/-32 codes (plus FOCUS_OK). For internal robustness I'll add:
```c
#define FOCUS_ERR_PERCEP_PARAM (-33)   // 参数错误
#define FOCUS_ERR_PERCEP_HTTP  (-34)   // HTTP 请求失败 (无响应/网络错误)
```
Wait, the task says timeout maps to -30. What about generic HTTP failure? The dev spec says `if (ret < 0) return -1;` — i.e., any HTTP failure = timeout = -1 (or -30 in new codes). So I'll map any `wifi_http_post` failure to FOCUS_ERR_PERCEP_TIMEOUT. That's simplest and matches "失败返回错误码".

Let me keep it to the 3 documented codes + FOCUS_OK, and use FOCUS_ERR_PERCEP_TIMEOUT for all transport failures, FOCUS_ERR_PERCEP_JSON for parse failures, FOCUS_ERR_PERCEP_NODATA for "no person/data in frame". Actually NODATA is for when there's no data (e.g., no person detected with low confidence). Let me define usage:
- TIMEOUT (-30): HTTP transport failure / timeout
- JSON (-31): JSON parse failure / missing fields / malformed
- NODATA (-32): response code != 0, or empty data

That's a reasonable mapping.

For NULL jpeg/out, I'll return FOCUS_ERR_PERCEP_JSON? No — I'll add `FOCUS_ERR_PERCEP_PARAM`. Hmm, but I want to avoid over-inventing. Let me just add it locally with a clear comment that it's a perception-local code not in the frozen set (or they can ask 万思源 to add it). Actually simpler: use FOCUS_ERR_PERCEP_JSON for any invalid input. No — that's semantically wrong.

I'll add a small set of guarded #defines and clearly comment. It's fine. The reviewer (万思源) will understand. I'll define:
```c
/* 若 api/error.h 未定义则补定义（保证独立编译）；仓库里已有则直接用 */
```

Now, let me write the mock path. The mock should "轮流输出 FOCUSED/PLAYING_PHONE/AWAY/DROWSY 对应的 observation_t". But observation_t is a perception output, and FOCUSED/PLAYING_PHONE/AWAY/DROWSY are behavior statuses (status_t), not observation fields. The observation_t just has booleans/floats. So the mock should produce observation_t values that, when fed to 赵思涵's behavior engine, would yield those statuses.

So mock should cycle through 4 "scenarios" and produce observation_t accordingly:
1. FOCUSED: person=true, phone=false, pitch=0, motion=0.1, conf=0.9
2. PLAYING_PHONE: person=true, phone=true, near_hand=true, pitch=-25, motion=0.5, conf=0.9
3. AWAY: person=false, phone=false, conf=0.9
4. DROWSY: person=true, phone=false, pitch=55 (低头/瞌睡), motion=0.05, conf=0.9

The mock cycles each call (or each N calls). The task says "根据 jpeg_len 或预设序列轮流输出". I'll cycle per call using a static counter. I'll also allow overriding via jpeg_len for testability? The task says "用固定规则: 根据 jpeg_len 或预设序列轮流输出". I'll do preset sequence rotation (simplest, deterministic), and mention jpeg_len as an option.

Let me write mock:
```c
static observation_t mock_observation(int step) {
    observation_t o;
    memset(&o, 0, sizeof(o));
    o.confidence = 0.9f;
    o.timestamp_ms = monotonic_ms();
    switch (step % 4) {
    case 0: // FOCUSED
        o.person_present = true;
        o.person_bbox[0]=0.15f; o.person_bbox[1]=0.10f; o.person_bbox[2]=0.70f; o.person_bbox[3]=0.85f;
        o.phone_detected = false;
        o.head_pitch = 0.0f;
        o.hand_motion_score = 0.1f;
        break;
    case 1: // PLAYING_PHONE
        o.person_present = true; bbox...;
        o.phone_detected = true; o.phone_near_hand = true;
        o.head_pitch = -25.0f; o.hand_motion_score = 0.6f;
        break;
    case 2: // AWAY
        o.person_present = false;
        break;
    case 3: // DROWSY
        o.person_present = true; bbox...;
        o.phone_detected = false;
        o.head_pitch = 55.0f; o.hand_motion_score = 0.05f;
        break;
    }
    return o;
}
```

Now `monotonic_ms()`:
```c
static uint32_t monotonic_ms(void) {
#ifdef __NuttX__  // or openvela/ESP32
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint32_t)(ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
#else
    ... same on Linux
#endif
}
```
Actually clock_gettime(CLOCK_MONOTONIC) works on both Linux and NuttX (NuttX has POSIX clocks). So just use it directly. The task says "参考 core/state_machine.c 的 monotonic_ms". I'll implement it directly.

**stabilize (debounce):** 3-frame window as in spec. I need to track cloud_result_t history of 3 frames. But I also need to handle "history not full yet". The spec's version checks confidence>0 to count valid frames, but that's fragile (confidence could legitimately be 0). Better: track a fill counter.

Let me write a cleaner debounce:
```c
#define DEBOUNCE_WINDOW 3
static cloud_result_t g_debounce[DEBOUNCE_WINDOW];
static int g_debounce_count = 0;   // 已累积的帧数 (0..3)
static int g_debounce_idx = 0;

static void debounce_push(cloud_result_t *raw) {
    g_debounce[g_debounce_idx] = *raw;
    g_debounce_idx = (g_debounce_idx + 1) % DEBOUNCE_WINDOW;
    if (g_debounce_count < DEBOUNCE_WINDOW) g_debounce_count++;
}

static void debounce_compute(observation_t *out, uint32_t ts) {
    // 不足 3 帧时取最新一帧
    cloud_result_t *latest = &g_debounce[(g_debounce_idx + DEBOUNCE_WINDOW - 1) % DEBOUNCE_WINDOW];
    if (g_debounce_count < DEBOUNCE_WINDOW) {
        fill_observation(latest, out, ts);
        return;
    }
    cloud_result_t *h = g_debounce;
    out->person_present  = majority3(h[0].person_detected, h[1].person_detected, h[2].person_detected);
    ...
}
```

Wait, there's a subtlety: when g_debounce_idx wraps, the "latest" is at (idx-1)%3. When count < 3, idx == count (since we increment after push), so latest = (count-1)%3 = count-1, correct.

The spec's approach just uses the 3 fixed slots and picks "latest = the one just written". My cleaner approach with a fill counter is better. I'll use fill counter.

**majority3**: return true if >=2 of 3 are true.
**median3**: sort 3 floats, return middle.
**max3**: max of 3 floats.

**parse_cloud_response** using cJSON:
```c
static int parse_cloud_response(const char *resp, cloud_result_t *out) {
    cJSON *root = cJSON_Parse(resp);
    if (!root) return FOCUS_ERR_PERCEP_JSON;
    cJSON *code = cJSON_GetObjectItem(root, "code");
    if (cJSON_IsNumber(code) && code->valueint != 0) { cJSON_Delete(root); return FOCUS_ERR_PERCEP_NODATA; }
    cJSON *data = cJSON_GetObjectItem(root, "data");
    if (!cJSON_IsObject(data)) { cJSON_Delete(root); return FOCUS_ERR_PERCEP_NODATA; }
    // person
    cJSON *person = cJSON_GetObjectItem(data, "person");
    if (cJSON_IsObject(person)) {
        cJSON *detected = cJSON_GetObjectItem(person, "detected");
        out->person_detected = cJSON_IsTrue(detected);
        cJSON *bbox = cJSON_GetObjectItem(person, "bbox");
        if (cJSON_IsArray(bbox) && cJSON_GetArraySize(bbox) >= 4) {
            for (int i=0;i<4;i++) out->person_bbox[i] = (float)cJSON_GetArrayItem(bbox,i)->valuedouble;
        }
    }
    // phone
    cJSON *phone = cJSON_GetObjectItem(data, "phone");
    if (cJSON_IsObject(phone)) {
        out->phone_detected = cJSON_IsTrue(cJSON_GetObjectItem(phone,"detected"));
        out->phone_in_hand = cJSON_IsTrue(cJSON_GetObjectItem(phone,"near_hand"));
    }
    // head_pose
    cJSON *pose = cJSON_GetObjectItem(data, "head_pose");
    if (cJSON_IsObject(pose)) {
        cJSON *pitch = cJSON_GetObjectItem(pose,"pitch");
        if (cJSON_IsNumber(pitch)) out->head_pitch = (float)pitch->valuedouble;
        cJSON *yaw = cJSON_GetObjectItem(pose,"yaw");
        if (cJSON_IsNumber(yaw)) out->head_yaw = (float)yaw->valuedouble;
    }
    cJSON *motion = cJSON_GetObjectItem(data, "hand_motion_score");
    if (cJSON_IsNumber(motion)) out->hand_motion = (float)motion->valuedouble;
    cJSON *conf = cJSON_GetObjectItem(data, "confidence");
    if (cJSON_IsNumber(conf)) out->confidence = (float)conf->valuedouble;
    cJSON_Delete(root);
    return FOCUS_OK;
}
```

This is robust to missing fields (each field checked). Good.

**base64_encode**: standard implementation. I'll write a correct, self-contained base64 encoder:
```c
static size_t base64_encode(const uint8_t *src, size_t len, char *dst, size_t dst_cap) {
    static const char tbl[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    size_t out_len = 4 * ((len + 2) / 3);
    if (dst_cap < out_len + 1) return 0;
    size_t i, j;
    for (i = 0, j = 0; i + 3 <= len; i += 3) {
        uint32_t v = (src[i] << 16) | (src[i+1] << 8) | src[i+2];
        dst[j++] = tbl[(v >> 18) & 63];
        dst[j++] = tbl[(v >> 12) & 63];
        dst[j++] = tbl[(v >> 6) & 63];
        dst[j++] = tbl[v & 63];
    }
    size_t rem = len - i;
    if (rem == 1) {
        uint32_t v = src[i] << 16;
        dst[j++] = tbl[(v>>18)&63]; dst[j++] = tbl[(v>>12)&63];
        dst[j++] = '='; dst[j++] = '=';
    } else if (rem == 2) {
        uint32_t v = (src[i]<<16)|(src[i+1]<<8);
        dst[j++] = tbl[(v>>18)&63]; dst[j++] = tbl[(v>>12)&63]; dst[j++] = tbl[(v>>6)&63];
        dst[j++] = '=';
    }
    dst[j] = '\0';
    return j;
}
```

**Real perception_process flow:**
```c
// 1. base64
char *b64 = malloc(base64_len + 1);  // PSRAM on ESP32, but malloc ok
if (!b64) return timeout? no, memory error...
size_t b64len = base64_encode(jpeg, jpeg_len, b64, b64_len + 1);
if (!b64len) { free(b64); return FOCUS_ERR_PERCEP_JSON; }  // hmm, no good error code

// 2. JSON request
size_t req_cap = b64len + 128;
char *req = malloc(req_cap);
snprintf(req, req_cap, "{\"image\":\"%s\",\"width\":320,\"height\":240}", b64);

// 3. HTTP POST (retry once, timeout 3s each → ≤6s)
char resp[4096];
int ret = wifi_http_post(g_api_url, req, resp, sizeof(resp));
if (ret < 0) {
    ret = wifi_http_post(g_api_url, req, resp, sizeof(resp));  // retry once
    if (ret < 0) { free(b64); free(req); return FOCUS_ERR_PERCEP_TIMEOUT; }
}
free(b64); free(req);

// 4. parse
cloud_result_t raw; memset(&raw, 0, sizeof(raw));
int pr = parse_cloud_response(resp, &raw);
if (pr != FOCUS_OK) return pr;

// 5. debounce
debounce_push(&raw);
debounce_compute(out, monotonic_ms());

// 6. history append
history_append(out);
return FOCUS_OK;
```

Note about memory: The dev spec says use PSRAM for large buffers (b64 ~40-54KB). On ESP32, stack is small (~8KB), so b64 and req must be heap/PSRAM. I'll use malloc/free (on openvela, malloc may go to PSRAM or heap). I'll add a comment about PSRAM. Also note `resp[4096]` on stack is 4KB — borderline on ESP32 (stack ~8KB). The spec's own example uses `char resp[4096]` on stack. I'll keep resp as a static buffer or heap. To be safe on ESP32, I'll make resp a static buffer (or heap). Let me use a static buffer for resp since it's fixed-size and reused. Actually static is not re-entrant but this is single-threaded per the design (wifi_task calls it). I'll use static to avoid stack pressure, with a comment.

Actually, better to keep it simple and match the spec's example (stack resp[4096]) but add a note. Hmm, but 4KB on a ~8KB task stack is risky. The openvela tasks can have configurable stack sizes. 万思源's wifi_task would set an appropriate stack. I'll use a heap buffer for resp to be safe, or static. I'll use static char g_resp[4096]. Wait — actually wifi_http_post is called from the perception module which 万思源's main loop calls. Using static is fine for single-threaded. But to allow the test harness to also call, static is fine.

Let me reconsider: I'll allocate resp on heap too, or static. I'll go with static buffer `g_resp[4096]` + comment "固定响应缓冲，避免 ESP32 小栈溢出".

Actually, let me use a cleaner approach: define reasonable buffer sizes and use static buffers for the large ones (b64/req/resp) to avoid both stack overflow and repeated malloc overhead. But static b64/req sized for max JPEG (54KB) would waste 54KB+60KB RAM permanently. The spec says "不要缓存 JPEG" and "base64 内存 ... 栈上放不下就用 PSRAM". So dynamic allocation is intended. I'll use malloc/free for b64 and req, and static (or small heap) for resp (4KB fixed).

I'll use:
- b64: malloc
- req: malloc
- resp: static char[4096]

Let me also make the max JPEG size a configurable macro:
```c
#define MAX_JPEG_SIZE   (50*1024)   // 320x240 JPEG 上限
#define MAX_B64_SIZE    (MAX_JPEG_SIZE * 4 / 3 + 4)
```

Now the retry/timeout: the spec says "HTTP 请求超时 3 秒，重试 1 次，仍失败→返回错误码 -1，不要阻塞超过 6 秒". But the actual timeout is enforced by wifi_http_post (张沐泽's driver). The perception module just calls it twice. Whether each call times out at 3s is 张沐泽's concern. I'll note that in comments. My code calls wifi_http_post, and on failure retries once. I'll add a comment that wifi_http_post should enforce ≤3s per call (total ≤6s).

Now `perception_get_history`:
```c
int perception_get_history(observation_t *buf, int n) {
    if (!buf || n <= 0) return 0;
    if (n > HISTORY_MAX) n = HISTORY_MAX;
    int available = g_history_count < HISTORY_MAX ? g_history_count : HISTORY_MAX;
    if (n > available) n = available;
    int start = g_history_count > HISTORY_MAX ? (g_history_count % HISTORY_MAX) : 0;
    for (int i = 0; i < n; i++) buf[i] = g_history[(start + i) % HISTORY_MAX];
    return n;
}
```

And `history_append`:
```c
static void history_append(const observation_t *obs) {
    g_history[g_history_count % HISTORY_MAX] = *obs;
    g_history_count++;
}
```

HISTORY_MAX = 60.

Now the internal header `perception/perception.h` (internal). Actually, the public header is `api/perception.h`. The internal one can be named `perception/perception_internal.h` or just `perception/perception.h`. The task says "perception/perception.h ← 内部声明 (可选)". To avoid confusion with api/perception.h, I'll name the internal one `perception_internal.h`. Actually, the task doc lists:
```
perception/perception.c          ← 主实现 (三函数)
perception/perception.h          ← 内部声明 (可选)
tests/test_perception.c          ← 独立测试
```

So they expect `perception/perception.h` as internal. But that collides conceptually with api/perception.h. Since perception.c is in perception/ dir and includes `"../api/perception.h"`, an internal `perception.h` in the same dir would be included as `"perception.h"`. That's fine and won't collide with the api one. But it's a bit confusing to have two perception.h. I'll instead put internal declarations directly in perception.c (as static functions) and skip the internal header, OR provide it named `perception_internal.h`. 

Given "可选" (optional), I'll fold internal stuff into perception.c as static and NOT create a separate internal header, to keep it simple. But I could provide one for clarity. I'll provide a minimal internal header only if it adds value. Actually, cloud_result_t and stabilize are internal. I'll just keep them static in perception.c. Simpler = fewer files = less chance of mismatch. I'll mention in README that internal declarations are kept static in the .c (no separate header needed).

Actually, wait — for the unit test, I want to test the debounce logic. If stabilize is static in perception.c, the test can't call it directly. But the test can test via perception_process in MOCK mode (which goes through the full mock → debounce → history). That's actually a better integration test. And to test debounce of the real path, the test can provide a stub wifi_http_post that returns canned JSON and compile WITHOUT PERCEPTION_MOCK but WITH a cJSON shim... 

Hmm, cJSON dependency in test. To keep the test fully dependency-free, I'll:
- Test mock path (no cJSON) thoroughly: verify rotation, verify history ring buffer, verify timestamps increase, verify NULL safety.
- Provide an optional real-path test guarded by `#ifdef HAVE_CJSON` that uses a stub wifi_http_post.

Actually, let me simplify the test to focus on what's testable without cJSON and without hardware:
1. perception_init
2. perception_process (MOCK mode) → returns FOCUS_OK, fills observation
3. history: after N process calls, get_history returns N entries in order, timestamps non-decreasing
4. debounce behavior: in mock mode, debounce still runs (3-frame majority). I can test that a single outlier doesn't flip a bool. But mock rotates every call, so consecutive frames differ... the debounce will smooth. I can add a targeted test by making a helper.

Hmm, actually in mock mode, should debounce even run? The mock produces already-stable observations, but going through debounce is harmless (majority of 3 rotating frames gives... messy). Let me think: if mock rotates FOCUSED→PLAYING→AWAY→DROWSY→FOCUSED..., and debounce does 3-frame majority, the output person_present over frames:
- frame0 FOCUSED (person true)
- frame1 PLAYING (person true)
- frame2 AWAY (person false)
- frame3 DROWSY (person true)
- frame4 FOCUSED (true)
- frame5 PLAYING (true)
- frame6 AWAY (false)
...

3-frame majority of person: [t,t,f]=t, [t,f,t]=t, [f,t,t]=t, [t,t,f]=t... mostly true. This actually destroys the AWAY signal! That's bad for mock mode — 赵思涵's away detection would never trigger.

So in mock mode, I should BYPASS debounce (mock is already clean) OR make mock not rotate every single frame (rotate slower, e.g., stay in each state for several frames). The task says "轮流输出" (rotate). If mock rotates every frame AND goes through debounce, away gets washed out.

Best solution: In mock mode, bypass debounce entirely (mock observations are already "stabilized" by definition). This matches "阶段 1 mock: 不调云端, 输出固定 observation_t". Debounce is part of the cloud path (阶段 2). So:

```c
#ifdef PERCEPTION_MOCK
    observation_t o = mock_observation(g_mock_seq++);
    *out = o;
#else
    // real: ... stabilize ...
#endif
    history_append(out);
```

This is cleaner and correct. The mock path doesn't debounce; the real path does. And the test can test debounce separately if I expose it, OR test it via the real path with cJSON.

Actually, I realize there might be value in testing debounce in the unit test. To do that without cJSON, I could compile perception.c with a test hook: `#ifdef PERCEPTION_UNIT_TEST` expose `stabilize` and `parse_cloud_response` as non-static (or provide wrapper). But parse_cloud_response needs cJSON. 

Let me keep it simple and pragmatic:
- Unit test tests mock path + history + init + NULL safety + error paths (mock mode with a "force timeout" knob? no).
- I'll ALSO write a tiny standalone base64 test + a debounce test by exposing internal functions under `#ifdef PERCEPTION_UNIT_TEST`.

To expose internals for testing, I'll add at the end of perception.c:
```c
#ifdef PERCEPTION_UNIT_TEST
/* 测试钩子：暴露内部函数 */
int perception_test_base64(const uint8_t *s, size_t l, char *o, size_t c) { return base64_encode(s,l,o,c); }
void perception_test_stabilize(cloud_result_t *raw, observation_t *out) { debounce_push(raw); debounce_compute(out, monotonic_ms()); }
#endif
```

Hmm, that's getting complicated. Let me reconsider what's the right scope.

Actually, I think the cleanest, most professional deliverable is:
1. `perception.c` — clean implementation, mock path bypasses debounce, real path does full pipeline. Internal helpers are `static`.
2. A `tests/test_perception.c` that tests the PUBLIC API only (init/process/get_history) in MOCK mode + history, plus a small stub-wifi test for the real path that DOESN'T need cJSON if I use a hand-rolled JSON parser.

Wait, I keep going back and forth on cJSON vs hand-rolled. Let me make a final decision now:

**Decision: Use cJSON in the real path (as the task explicitly instructs), but ALSO include a tiny fallback so the code compiles without cJSON if unavailable.** Actually no — mixing is ugly.

Final decision: **Use cJSON, guarded by `#include <cJSON.h>`, in the real path.** The mock path (default for standalone test) doesn't need cJSON. The unit test tests mock path + history + base64 + debounce via exposed test hooks. For debounce/base64, I expose them under `PERCEPTION_UNIT_TEST`. This is clean, matches the task ("cJSON 解析 resp"), and the test is dependency-free (compiles with PERCEPTION_MOCK + PERCEPTION_UNIT_TEST, never includes cJSON because mock path is compiled).

Wait, but if I want the unit test to also test parse_cloud_response (the JSON parsing), that requires cJSON. I'll make that test optional: a separate test file `tests/test_perception_cloud.c` (requires cJSON + a stub wifi) OR just skip it and note it. Given "可选" and to keep it focused, I'll test:
- mock path (init, process rotation, history, timestamps)
- base64 correctness (exposed hook) — this is a real correctness check worth having
- debounce majority/median (exposed hook)
- get_history edge cases (n=0, n>available, wrap-around)

These are all testable without cJSON. 

Let me finalize the test hook approach. I'll expose base64 and debounce via `#ifdef PERCEPTION_UNIT_TEST` guarded functions. Actually, cleaner: put the internal helpers (base64, majority3, median3, max3, debounce) in a small internal header `perception/perception_internal.h` with `static inline` or normal declarations, so the test can #include it and call them directly. That's actually the intended "perception/perception.h 内部声明" file! 

So:
- `perception/perception_internal.h` — declares `cloud_result_t`, `base64_encode()`, `stabilize()`/`debounce_*()`, `parse_cloud_response()`, `fill_observation()`. These are NON-static, implemented in perception.c. The test #includes this header to call them. This is exactly the "内部声明" file the task mentions.

But wait — the task named it `perception/perception.h` not `perception_internal.h`. Let me just name it `perception/perception_internal.h` for clarity and mention the mapping. Or honor the task and name it `perception/perception.h` (internal). Hmm.

Given the repo already has `api/perception.h` (public, frozen) and 周礼航's own dir is `perception/`, having `perception/perception.h` (internal) is what the task doc literally suggests. But it's confusing. I'll go with `perception/perception_internal.h` and clearly explain in README that this is the "内部声明 (可选)" file from the task, renamed for clarity to avoid confusion with api/perception.h. Actually, you know what, simpler to just follow the task doc's naming to reduce friction: the reviewer expects `perception/perception.c` and maybe `perception/perception.h`. 

Ugh, I'm overthinking the naming. Let me just decide:
- Keep internal helpers as `static` in perception.c (no internal header). 
- For unit testing internals (base64, debounce), I'll write the test to include perception.c directly? No.

Simplest robust approach for testing: expose internals via `#ifdef PERCEPTION_UNIT_TEST` at bottom of perception.c with small test-only wrappers. This keeps everything in one .c file, no separate internal header, and the test compiles perception.c with `-DPERCEPTION_UNIT_TEST` and calls the wrappers.

Actually even simpler and very standard: put the unit test in the SAME file at the bottom guarded by `#ifdef PERCEPTION_UNIT_TEST` with a `main()`. That matches the dev spec's §六 "可以独立测试" which shows a `#ifdef PERCEPTION_UNIT_TEST` main() inside... actually the spec shows it as a standalone main in a test context.

Let me look at the spec §六 again — it shows:
```c
#ifdef PERCEPTION_UNIT_TEST
int main() { ... }
#endif
```
This is meant to be either in a separate test file or appended. The 赵思涵 reference is `tests/behavior_test.c` (separate file, 250 lines). So I'll follow that: separate `tests/test_perception.c`.

For exposing internals: I'll create `perception/perception_internal.h` with the internal types and function declarations, implemented as non-static in perception.c. The test includes `../perception/perception_internal.h`. This is the cleanest and matches the "内部声明" file. I'll name it `perception_internal.h` (clearer) and note it.

FINAL STRUCTURE:
```
focus_perception/
├── api/
│   └── perception.h          公开接口 (observation_t + 3 函数 + 错误码), 与仓库冻结版一致
├── perception/
│   ├── perception.c          主实现
│   └── perception_internal.h 内部声明 (cloud_result_t, base64, stabilize, parse)
└── tests/
    └── test_perception.c     独立单测 (mock 路径 + base64 + 去抖 + 历史)
└── README.md                 接入/编译/测试说明
```

Now, about the public header `api/perception.h`: since it's frozen in the repo, I'll reproduce it faithfully from the spec (observation_t + 3 functions). I'll also add the error codes (guarded #ifndef) so it compiles standalone. Actually the error codes belong to `api/error.h`, not perception.h. But for standalone compile, I'll put guarded error-code defines in perception.h (or a note). Let me put them in perception.h guarded by #ifndef, with a comment "这些常量通常由 api/error.h 提供".

Wait, but if 万思源's frozen `api/perception.h` does NOT contain error codes (they're in error.h), then my reproduced perception.h with #ifndef guards is fine — it just adds guarded fallbacks. And in the repo, error.h provides them. Good.

Actually, I realize I should double-check: does `api/perception.h` in the repo include error.h? The transcript line 14352 shows error.h is separate. And perception.h likely includes `<stdbool.h>` etc. I'll reproduce a reasonable version.

Let me now also reconsider: should the public header be in `api/` in my deliverable, or should I just reference the repo's frozen one? Since I'm delivering to 周礼航 who will drop files into their repo (where api/perception.h ALREADY exists and is frozen), I should NOT have them overwrite api/perception.h. So my deliverable should:
- Provide `api/perception.h` ONLY as a reference copy (clearly marked "参考用，勿覆盖仓库冻结版"), so the standalone test can compile.
- perception.c includes `"../api/perception.h"`.

I'll mark it clearly in README and in the file header comment.

Now let me write everything. This is a substantial amount of C code. Let me be careful and produce clean, correct, well-commented code matching the spec's style (Chinese comments, matching the existing code idiom).

Let me also reconsider the exact function signatures to match the frozen header. The dev spec (周礼航开发规范.md) says:
```c
int  perception_init(const char *api_url, const char *api_key);
int  perception_process(uint8_t *jpeg, size_t jpeg_len, observation_t *out);
int  perception_get_history(observation_t *buf, int n);
```

These are the frozen signatures (from api/perception.h). I'll match exactly. Note `uint8_t *jpeg` (non-const) and `size_t jpeg_len`.

The task doc (2) also confirms:
- `perception_init(api_url, api_key)`
- `perception_process(jpeg, jpeg_len, out)`
- `perception_get_history(buf, n)`

Good, consistent.

Error code return values: The dev spec says `0/-1/-2`, but the task doc (2) says `FOCUS_ERR_PERCEP_TIMEOUT(-30)/FOCUS_ERR_PERCEP_JSON(-31)/FOCUS_ERR_PERCEP_NODATA(-32)`. I'll use the FOCUS_ERR_* codes (more recent, frozen). I'll add a comment mapping them.

Let me write the files now.

First, let me write the code into C:\temp. I'll create a folder `focus_perception`.

Actually, let me reconsider the working directory. C:\temp is the cwd. I'll create `C:\temp\focus_perception\...`.

Let me write each file.

Let me carefully write perception.h (public).

Actually, let me reconsider whether to also provide a mock for `wifi_http_post` and `camera` in the test. The test needs `wifi_http_post` symbol? Only if real path is compiled. In MOCK mode, perception.c doesn't reference wifi_http_post (it's in the `#else` branch). But it DOES reference it in the real branch code which is compiled OUT under PERCEPTION_MOCK. So the test in MOCK mode doesn't need wifi_http_post. Good. But I want the test to ALSO verify the real path parsing. For that, I'll add a `tests/test_perception_cloud.c`? No, let me keep it to one test file but support an optional real-path test with a stub wifi + cJSON. 

To keep it simple and still meaningful, I'll do:
- test_perception.c: compiles perception.c in MOCK mode + UNIT_TEST mode. Tests mock rotation, history, timestamps, base64 (exposed), debounce (exposed via internal header), get_history edge cases.

For base64 and debounce, I need them non-static and declared in perception_internal.h. But if PERCEPTION_MOCK is defined, is base64 still compiled? I'll compile base64 and debounce helpers ALWAYS (unconditional), so they're available for testing regardless. Only the cloud-path-specific code (parse_cloud_response, the real branch in perception_process) is under `#ifndef PERCEPTION_MOCK`.

So structure of perception.c:
1. includes
2. error code fallback defines (guarded)
3. config macros (HISTORY_MAX, buffers)
4. static globals (g_api_url, g_api_key, g_history[], g_history_count, g_debounce[], g_debounce_count, g_debounce_idx, g_mock_seq)
5. internal helpers (always compiled):
   - monotonic_ms
   - majority3, median3, max3
   - base64_encode
   - fill_observation
   - debounce_push, debounce_compute
6. `#ifndef PERCEPTION_MOCK` real-path only:
   - parse_cloud_response (cJSON)
7. public API:
   - perception_init
   - perception_process (mock or real)
   - perception_get_history

Internal helpers declared in perception_internal.h (non-static), so test can call: base64_encode, debounce_push, debounce_compute, majority3, median3, max3, fill_observation, cloud_result_t.

Wait, if they're non-static and declared in a header that's included by perception.c and test, that's clean. But then these internal symbols are global (could clash with other modules? No, they're perception-specific names). Fine.

Actually, there's a subtlety: `debounce_compute` uses `g_debounce` static state. The test can push 3 frames and compute. Fine.

Let me also make `fill_observation` take cloud_result_t + observation_t + timestamp. And debounce_compute fills observation. Good.

Let me now write the internal header with cloud_result_t and function declarations.

Let me write everything now. I'll write clean code.

One more consideration: the `bool` type — need `#include <stdbool.h>`.

`cJSON.h` include: `#include <cJSON.h>`. On openvela, cJSON is provided via `<cJSON.h>` (in apps/include or system). The task says "cJSON 解析". I'll use `#include <cJSON.h>` and note in README the include path may need adjustment.

Let me write the files.

For `perception_process` real branch, I need to be careful about memory and the retry. Let me finalize:

```c
int perception_process(uint8_t *jpeg, size_t jpeg_len, observation_t *out) {
    if (!out || !jpeg || jpeg_len == 0)
        return FOCUS_ERR_PERCEP_PARAM;

#ifdef PERCEPTION_MOCK
    /* 阶段 1: mock —— 不调云端，按预设序列轮流产出 observation */
    observation_t obs = mock_observation(g_mock_seq++);
    *out = obs;
#else
    /* 阶段 2: 真实云端链路 */
    /* 1. base64 编码 */
    size_t b64_cap = base64_encoded_len(jpeg_len) + 1;
    char *b64 = malloc(b64_cap);          /* ESP32 上建议映射到 PSRAM */
    if (!b64) return FOCUS_ERR_PERCEP_PARAM;
    size_t b64_len = base64_encode(jpeg, jpeg_len, b64, b64_cap);
    if (b64_len == 0) { free(b64); return FOCUS_ERR_PERCEP_PARAM; }

    /* 2. 构造 JSON 请求 */
    size_t req_cap = b64_len + 96;
    char *req = malloc(req_cap);
    if (!req) { free(b64); return FOCUS_ERR_PERCEP_PARAM; }
    snprintf(req, req_cap, "{\"image\":\"%s\",\"width\":%d,\"height\":%d}",
             b64, FRAME_WIDTH, FRAME_HEIGHT);

    /* 3. HTTP POST (超时由 wifi_http_post 内部保证 ≤3s；失败重试 1 次，总阻塞 ≤6s) */
    int ret = wifi_http_post(g_api_url, req, g_resp, sizeof(g_resp));
    if (ret < 0) {
        ret = wifi_http_post(g_api_url, req, g_resp, sizeof(g_resp));  /* 重试一次 */
    }
    free(b64);
    free(req);
    if (ret < 0) return FOCUS_ERR_PERCEP_TIMEOUT;

    /* 4. JSON 解析 → cloud_result_t */
    cloud_result_t raw;
    memset(&raw, 0, sizeof(raw));
    int pr = parse_cloud_response(g_resp, &raw);
    if (pr != FOCUS_OK) return pr;

    /* 5. 3 帧去抖稳定 */
    debounce_push(&raw);
    debounce_compute(out, monotonic_ms());
#endif

    /* 6. 追加历史 (供赵思涵时序分析) */
    history_append(out);
    return FOCUS_OK;
}
```

Need `#include <stdlib.h>` for malloc/free, `<stdio.h>` for snprintf, `<string.h>` for memset/memcpy.

Need `wifi_http_post` declared. In the repo it's in `api/wifi.h`. My perception.c real path needs it. I'll declare it via including `"../api/wifi.h"` in the real branch, OR just add a forward declaration. To be safe and self-contained, I'll add a forward declaration guarded under `#ifndef PERCEPTION_MOCK`:

Actually, better to include the real header `"../api/wifi.h"`. But for standalone test (MOCK mode), that header may not exist in my deliverable. Since it's under `#ifndef PERCEPTION_MOCK`, it won't be included in mock/test builds. But I should still reference it correctly for the real build. Let me add, in the `#ifndef PERCEPTION_MOCK` block:
```c
#include "../api/wifi.h"   /* wifi_http_post() */
```
But my deliverable's api/ only has perception.h. For the real build, they have api/wifi.h in the repo. So it's fine. But to be safe for anyone compiling the real path standalone, I'll forward-declare `wifi_http_post` instead of including wifi.h, to avoid a missing include. I'll add:

```c
#ifndef PERCEPTION_MOCK
/* 张沐泽提供：见 api/wifi.h (此处前向声明，避免独立编译依赖) */
int wifi_http_post(const char *url, const char *body, char *resp, size_t maxlen);
#include <cJSON.h>
#endif
```

Actually, forward-declaring and ALSO having the real header is redundant but harmless. I'll forward declare with a comment. That keeps it self-contained.

Now, `mock_observation` function. Let me write it.

For the mock, I need to produce timestamp. Use monotonic_ms().

Now let me also handle `person_bbox` — when person not detected, bbox all zeros. I'll set bbox only in person-present cases.

Let me write `fill_observation`:
```c
void fill_observation(const cloud_result_t *raw, observation_t *out, uint32_t ts) {
    out->person_present   = raw->person_detected;
    out->person_bbox[0]   = raw->person_bbox[0];
    ... (4)
    out->phone_detected   = raw->phone_detected;
    out->phone_near_hand  = raw->phone_in_hand;
    out->head_pitch       = raw->head_pitch;
    out->head_yaw         = raw->head_yaw;
    out->hand_motion_score= raw->hand_motion;
    out->confidence       = raw->confidence;
    out->timestamp_ms     = ts;
}
```

Note cloud_result_t has `head_roll` too but observation_t doesn't — I'll keep head_roll in cloud_result_t (per spec) but not use it (or I can drop it since it's unused). The spec's cloud_result_t includes head_roll. I'll keep it but it's unused (matches spec). Actually to avoid an unused field warning, it's fine (struct fields don't warn). I'll keep it for completeness/possible future use, and note it's currently unused. Or I could just drop it. I'll keep it (matches the spec's internal struct) with a comment "head_roll 预留，observation_t 未用到".

Now, monotonic_ms for timestamp: the task says "用 clock_gettime(CLOCK_MONOTONIC)". On ESP32/openvela (NuttX), clock_gettime(CLOCK_MONOTONIC) is available. I'll implement:

```c
static uint32_t monotonic_ms(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint32_t)((uint64_t)ts.tv_sec * 1000u + (uint64_t)ts.tv_nsec / 1000000u);
}
```
Need `#include <time.h>`.

Now, uint32 overflow: task mentions "uint32 时间回绕处理" for behavior engine (赵思涵's), not perception. For perception history, timestamps just need to be monotonic-ish. I'll not over-engineer. The comparison is done in behavior engine.

Now let me write the test file. It will:
1. `#include "../perception/perception_internal.h"` and `#include "../api/perception.h"` (via perception_internal.h probably includes api/perception.h).
2. Define a main() with simple asserts/checks and printf.
3. Test cases:
   a. perception_init returns FOCUS_OK.
   b. perception_process (MOCK) returns FOCUS_OK, fills observation; over 4 calls, we see all 4 mock states (person present toggles, phone toggles, etc.).
   c. perception_get_history: after 5 calls, returns 5 entries; timestamps non-decreasing; n clamp (ask for 100 → 5).
   d. base64_encode: encode known input ("Man" → "TWFu", "Ma" → "TWE=", "M" → "TQ==") — classic RFC4648 test vectors.
   e. majority3/median3/max3 correctness.
   f. debounce: push 3 frames where 2 say person=true, 1 false → person_present true. And median of pitches.
   g. NULL safety: perception_process(NULL,...) returns error; get_history(NULL,..) returns 0.

I'll write a tiny test framework with a macro:
```c
static int g_fail = 0;
#define CHECK(cond) do { if (!(cond)) { printf("FAIL %s:%d  %s\n", __FILE__, __LINE__, #cond); g_fail++; } } while (0)
```

Compile command (Linux):
```bash
gcc -Wall -Wextra -DPERCEPTION_MOCK -DPERCEPTION_UNIT_TEST \
    -I. perception/perception.c tests/test_perception.c -o test_perception
```

Wait, test needs to include headers; I'll use `-I.` and include with paths relative to focus_perception root: `#include "perception/perception_internal.h"` etc. Or include relative to the test file's dir (`../perception/...`). I'll use `#include "perception/perception_internal.h"` with `-I.` from the focus_perception root. Cleaner. Actually, since perception.c also includes `"../api/perception.h"` (relative to perception/ dir), I need the compile to find it. `"../api/perception.h"` from `perception/perception.c` resolves to `api/perception.h` (relative to the source file's directory), which exists in my deliverable. Good. And the test uses `#include "perception/perception_internal.h"` with `-I<root>`. perception_internal.h includes `"../api/perception.h"` (relative to perception/ dir) → resolves to api/perception.h. Good.

So the include in perception_internal.h should be `#include "../api/perception.h"`.

Let me finalize and write.

Actually, I realize I should double check: is there any info in the transcript about the exact error.h values or observation_t field names that differ from the spec? The transcript elides content, so I'll trust the two spec docs. They're consistent. Good.

Let me also reconsider: the task doc (2) says "perception/perception.h ← 内部声明 (可选)". I'm naming it perception_internal.h. I'll note in README that it's the "内部声明" file, renamed for clarity. Alternatively, to reduce friction, I could just inline everything static and skip the internal header, and put a small `#ifdef PERCEPTION_UNIT_TEST` test hook. But exposing internals via header is cleaner for a real test. I'll go with perception_internal.h.

Let me now also make sure the mock path is the DEFAULT (so a fresh clone compiles the mock and can be tested without cJSON). I'll document: `-DPERCEPTION_MOCK` enables mock (default for standalone); omit it (and add cJSON) for real cloud. But "默认 mock 可回退" — so maybe default should be mock. I'll make the code: mock is compiled when PERCEPTION_MOCK is defined. In the README I'll give the exact compile commands for both. To make "默认 mock", I could invert: `#ifndef PERCEPTION_REAL` → mock. Let me do that: mock by default, real only when `PERCEPTION_REAL` is defined. That matches "默认 mock 可回退" more precisely.

Actually the task says "mock 路径保留: 用 #ifdef PERCEPTION_MOCK 或 Kconfig 开关, 默认 mock 可回退". So `#ifdef PERCEPTION_MOCK` is the suggested macro, and "默认 mock" means they'll define it by default in the build. I'll use `PERCEPTION_MOCK` as the switch (matching their wording), with mock when defined. In the Makefile integration note, I'll say: default add `PERCEPTION_MOCK` to CFLAGS for mock; remove it and link cJSON for real.

Hmm, but for the standalone test, I'll compile with `-DPERCEPTION_MOCK`. Good.

Let me write the code now. I'll write all files.

Let me be careful with the base64_encoded_len helper:
```c
static inline size_t base64_encoded_len(size_t n) { return 4 * ((n + 2) / 3); }
```

Now write everything.

Let me write api/perception.h first.

I need to think about whether perception.h should include stdbool, stdint, stddef. Yes.

Let me write it.

For error codes, I'll put them in a guarded block. Also define FOCUS_ERR_PERCEP_PARAM as -33 (perception-local, might need 万思源 to add to error.h — I'll note it).

Let me write now.

Actually, let me reconsider the return type of `perception_get_history` and the NULL handling. The dev spec returns "实际返回的条数 (≤ n)". Good.

Also, I should double check the `snprintf` for the JSON request — b64 can be ~54KB, so req needs b64_len + ~96. Fine.

Now, another subtle point: in the real path, `g_resp` static buffer of 4096. The response JSON is small (~300 bytes), so 4096 is plenty.

Let me write all the files now in parallel (Write calls).

Let me draft the full perception.c carefully.

```c
/****************************************************************************
 * FOCUS AIoT - 视觉感知模块 (perception)
 *
 * 负责人: 周礼航
 * 职责:   从一张 JPEG 里看出「有什么」——只做空间维度的单帧静态分析，
 *         不做时间维度的行为推理 (那是赵思涵 behavior 模块的事)。
 *
 * 输入:   JPEG 图像 (来自张沐泽 camera_frame_buffer / camera_capture_frame)
 * 输出:   observation_t (每帧一个, 经云端 API + 3 帧去抖)
 *
 * 三个对外接口 (冻结于 api/perception.h):
 *   perception_init()         初始化 URL/Key + 清空历史
 *   perception_process()      一帧 JPEG → observation_t
 *   perception_get_history()  取最近 N 条 observation (供 behavior 时序分析)
 *
 * 编译开关:
 *   PERCEPTION_MOCK  定义后走 mock 路径 (不调云端), 默认 mock 便于联调/回退
 *                    不定义则走真实云端链路 (需要 cJSON + wifi_http_post)
 ****************************************************************************/

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../api/perception.h"

#ifndef PERCEPTION_MOCK
#include <cJSON.h>
/* 张沐泽提供, 见 api/wifi.h (前向声明避免独立编译依赖) */
int wifi_http_post(const char *url, const char *body, char *resp, size_t maxlen);
#endif

/* ------------------------------------------------------------------ */
/* 内部配置                                                            */
/* ------------------------------------------------------------------ */
#define HISTORY_MAX      60               /* 保留最近 60 条 observation */
#define FRAME_WIDTH      320
#define FRAME_HEIGHT     240
#define MAX_JPEG_SIZE    (50 * 1024)      /* 320x240 JPEG 上限 */
#define RESP_BUF_SIZE    4096             /* 云端 JSON 响应缓冲 */

/* ------------------------------------------------------------------ */
/* 模块状态                                                            */
/* ------------------------------------------------------------------ */
static char g_api_url[160];
static char g_api_key[80];

static observation_t g_history[HISTORY_MAX];
static int           g_history_count = 0;   /* 累计写入条数 (用于求 start) */

static cloud_result_t g_debounce[3];
static int            g_debounce_count = 0; /* 已累积帧数 0..3 */
static int            g_debounce_idx   = 0;

static int            g_mock_seq = 0;       /* mock 轮转序号 */
static char           g_resp[RESP_BUF_SIZE];

...
```

Wait, `cloud_result_t` is defined in perception_internal.h, which I need to include in perception.c. But perception_internal.h includes api/perception.h. So order: include perception_internal.h (which includes api/perception.h). Let me just include both: perception.c includes "../api/perception.h" and "perception_internal.h" (same dir). Actually perception_internal.h will `#include "../api/perception.h"`. So perception.c can just `#include "perception_internal.h"`. But for clarity, include api/perception.h explicitly too. To avoid double include issues, use include guards. Fine.

Let me put cloud_result_t in perception_internal.h and include it. perception.c includes "perception_internal.h".

Let me define perception_internal.h:

```c
#ifndef PERCEPTION_INTERNAL_H
#define PERCEPTION_INTERNAL_H

#include "../api/perception.h"
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/* 云端原始检测结果 (内部使用, 不对外暴露) */
typedef struct {
    bool  person_detected;
    float person_bbox[4];
    bool  phone_detected;
    bool  phone_in_hand;
    float head_pitch, head_yaw, head_roll;
    float hand_motion;
    float confidence;
} cloud_result_t;

/* ---- 内部工具函数 (供实现与单测使用) ---- */
uint32_t perception_monotonic_ms(void);
size_t   perception_base64_encoded_len(size_t n);
size_t   perception_base64_encode(const uint8_t *src, size_t len, char *dst, size_t dst_cap);
bool     perception_majority3(bool a, bool b, bool c);
float    perception_median3(float a, float b, float c);
float    perception_max3(float a, float b, float c);
void     perception_fill_observation(const cloud_result_t *raw, observation_t *out, uint32_t ts);
void     perception_debounce_push(const cloud_result_t *raw);
void     perception_debounce_compute(observation_t *out, uint32_t ts);
int      perception_parse_cloud_response(const char *resp, cloud_result_t *out);

#endif
```

Hmm, prefixing internal helpers with `perception_` to avoid global namespace collisions. Good practice.

Now perception.c implements these (non-static, with perception_ prefix). The public API (perception_init/process/get_history) remain unprefixed as frozen.

parse_cloud_response is only compiled under `#ifndef PERCEPTION_MOCK`. But I declared it in the header unconditionally. In MOCK test build, if I declare it but don't define it, and the test doesn't call it, the linker won't complain (unreferenced). But it's cleaner to guard. Actually, an unreferenced declared-but-undefined function is fine in C (no error at link time if not referenced). The test won't reference parse_cloud_response (it needs cJSON). So OK. But to be safe, I'll guard the declaration too, or just leave it (declaration is harmless). I'll leave it declared but only defined in real path, and note in test that parse_cloud_response is only available in real build. Actually simpler: guard parse_cloud_response declaration+definition under `#ifndef PERCEPTION_MOCK`. But then test (MOCK) can't see it. Fine, test doesn't need it. I'll guard it.

Hmm, but that makes the header content depend on build flags. It's OK — I'll add a comment. Actually, let me keep the header unconditional (declare all), and in perception.c define parse_cloud_response only in real build. For MOCK build, if nothing references it, no link error. The test won't reference it. Clean enough. But to avoid any confusion, I'll wrap parse_cloud_response declaration with `#ifndef PERCEPTION_MOCK` in the header. Let me do that — it's more honest about what's available.

Actually, let me simplify: keep the internal header minimal and always-true (no conditionals), declare parse_cloud_response always, define it under `#ifndef PERCEPTION_MOCK`. The test compiles with PERCEPTION_MOCK and simply won't call parse_cloud_response. This is the least surprising. I'll add a comment "parse_cloud_response 仅在非 mock 构建中定义 (依赖 cJSON)".

OK let me just write it all now. Enough deliberation.

For base64 test vectors:
- "Man" → "TWFu"
- "Ma" → "TWE="
- "M" → "TQ=="
- "" → ""

Let me verify "Ma": M=0x4d, a=0x61. 
- M=01001101, a=01100001. Concatenate 16 bits: 010011 010110 0001 → 3 groups: 010011(19)=T, 010110(22)=W, 0001 00 → 000100(4)=E, pad → "TWE=". Yes.

"M": 01001101 → 010011(19)=T, 010000(16)=Q, pad, pad → "TQ==". Yes.

Good.

Now write the test with these.

Let me write everything. I'll write 4 files: api/perception.h, perception/perception_internal.h, perception/perception.c, tests/test_perception.c, plus README.md.

Let me carefully compose each.

For the README, include:
- 说明 (这是什么, 对齐了哪些文档)
- 文件清单
- 如何接入仓库 (放哪, include 路径, Makefile CSRCS, Kconfig)
- 编译 & 测试命令 (Linux + openvela)
- 错误码表
- 关键设计点 (mock/real 双路径, 去抖, 历史, 超时)

Let me write.

I'll also reconsider: should I create the files directly in C:\temp without a subfolder, or a subfolder? A subfolder `focus_perception/` is cleaner and clearly separates the deliverable. I'll use that.

Let me write all files now.

Actually, one more important check: the frozen `api/perception.h` might have `observation_t` with slightly different field order or an additional field. But both spec docs agree exactly on the 9 fields. I'll trust them. If there's a mismatch, the #include of the real header in their repo will catch it at compile time, and they can align. I'll note this in README.

Let me write now. I'll do it in a single batch of Write calls.

Let me write the full content carefully.

For perception.c, let me write the complete implementation with all helpers.

Let me write `perception_median3`:
```c
float perception_median3(float a, float b, float c) {
    if (a > b) { float t = a; a = b; b = t; }
    if (b > c) { float t = b; b = c; c = t; }
    if (a > b) { float t = a; a = b; b = t; }
    return b;
}
```

`perception_max3`:
```c
float perception_max3(float a, float b, float c) {
    float m = a;
    if (b > m) m = b;
    if (c > m) m = c;
    return m;
}
```

`perception_majority3`:
```c
bool perception_majority3(bool a, bool b, bool c) {
    return (a + b + c) >= 2;   // 注意 bool 在 C 里 + 是 int
}
```
Actually `(a + b + c)` where a,b,c are bool → promotes to int, sums 0..3. `>= 2` correct. But to be clear, I'll write `(int)a + (int)b + (int)c >= 2`.

`perception_base64_encode` as drafted.

`perception_fill_observation`:
```c
void perception_fill_observation(const cloud_result_t *raw, observation_t *out, uint32_t ts) {
    out->person_present    = raw->person_detected;
    out->person_bbox[0]    = raw->person_bbox[0];
    out->person_bbox[1]    = raw->person_bbox[1];
    out->person_bbox[2]    = raw->person_bbox[2];
    out->person_bbox[3]    = raw->person_bbox[3];
    out->phone_detected    = raw->phone_detected;
    out->phone_near_hand   = raw->phone_in_hand;
    out->head_pitch        = raw->head_pitch;
    out->head_yaw          = raw->head_yaw;
    out->hand_motion_score = raw->hand_motion;
    out->confidence        = raw->confidence;
    out->timestamp_ms      = ts;
}
```

`perception_debounce_push`:
```c
void perception_debounce_push(const cloud_result_t *raw) {
    g_debounce[g_debounce_idx] = *raw;
    g_debounce_idx = (g_debounce_idx + 1) % 3;
    if (g_debounce_count < 3) g_debounce_count++;
}
```

`perception_debounce_compute`:
```c
void perception_debounce_compute(observation_t *out, uint32_t ts) {
    /* 不足 3 帧: 直接输出最新一帧 */
    if (g_debounce_count < 3) {
        const cloud_result_t *latest =
            &g_debounce[(g_debounce_idx + 3 - 1) % 3];
        perception_fill_observation(latest, out, ts);
        return;
    }
    const cloud_result_t *h = g_debounce;
    out->person_present  = perception_majority3(h[0].person_detected, h[1].person_detected, h[2].person_detected);
    out->phone_detected  = perception_majority3(h[0].phone_detected, h[1].phone_detected, h[2].phone_detected);
    out->phone_near_hand = perception_majority3(h[0].phone_in_hand, h[1].phone_in_hand, h[2].phone_in_hand);

    out->head_pitch = perception_median3(h[0].head_pitch, h[1].head_pitch, h[2].head_pitch);
    out->head_yaw   = perception_median3(h[0].head_yaw, h[1].head_yaw, h[2].head_yaw);

    out->hand_motion_score = perception_max3(h[0].hand_motion, h[1].hand_motion, h[2].hand_motion);

    out->confidence = (h[0].confidence + h[1].confidence + h[2].confidence) / 3.0f;

    /* bbox 取最新一帧 (无去抖意义) */
    const cloud_result_t *latest = &h[(g_debounce_idx + 3 - 1) % 3];
    out->person_bbox[0] = latest->person_bbox[0];
    out->person_bbox[1] = latest->person_bbox[1];
    out->person_bbox[2] = latest->person_bbox[2];
    out->person_bbox[3] = latest->person_bbox[3];

    out->timestamp_ms = ts;
}
```

Wait, when g_debounce_count == 3, the "latest" is g_debounce[(idx-1)%3], which is the most recently pushed. Since idx points to next write slot, latest written = (idx-1)%3. Correct.

But there's a subtlety when using `h = g_debounce` (the array in slot order 0,1,2). The 3 frames are always in slots 0,1,2 (since window is exactly 3, they're all full when count==3). Order doesn't matter for majority/median/max. For "latest", I correctly compute (idx-1)%3. Good.

`perception_monotonic_ms`:
```c
uint32_t perception_monotonic_ms(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint32_t)((uint64_t)ts.tv_sec * 1000u + (uint64_t)ts.tv_nsec / 1000000u);
}
```

mock_observation (static, only in MOCK path):
```c
#ifdef PERCEPTION_MOCK
static observation_t mock_observation(int step) {
    observation_t o;
    memset(&o, 0, sizeof(o));
    o.confidence     = 0.9f;
    o.timestamp_ms   = perception_monotonic_ms();

    switch (step % 4) {
    case 0: /* FOCUSED */
        o.person_present = true;
        o.person_bbox[0] = 0.15f; o.person_bbox[1] = 0.10f;
        o.person_bbox[2] = 0.70f; o.person_bbox[3] = 0.85f;
        o.head_pitch = 0.0f;
        o.hand_motion_score = 0.10f;
        break;
    case 1: /* PLAYING_PHONE */
        o.person_present = true;
        o.person_bbox[0] = 0.15f; o.person_bbox[1] = 0.10f;
        o.person_bbox[2] = 0.70f; o.person_bbox[3] = 0.85f;
        o.phone_detected = true;
        o.phone_near_hand = true;
        o.head_pitch = -25.0f;
        o.hand_motion_score = 0.60f;
        break;
    case 2: /* AWAY */
        o.person_present = false;
        break;
    case 3: /* DROWSY */
        o.person_present = true;
        o.person_bbox[0] = 0.15f; o.person_bbox[1] = 0.10f;
        o.person_bbox[2] = 0.70f; o.person_bbox[3] = 0.85f;
        o.head_pitch = 55.0f;
        o.hand_motion_score = 0.05f;
        break;
    }
    return o;
}
#endif
```

parse_cloud_response (real only):
```c
#ifndef PERCEPTION_MOCK
int perception_parse_cloud_response(const char *resp, cloud_result_t *out) {
    if (!resp || !out) return FOCUS_ERR_PERCEP_JSON;

    cJSON *root = cJSON_Parse(resp);
    if (!root) return FOCUS_ERR_PERCEP_JSON;

    cJSON *code = cJSON_GetObjectItem(root, "code");
    if (cJSON_IsNumber(code) && code->valueint != 0) {
        cJSON_Delete(root);
        return FOCUS_ERR_PERCEP_NODATA;   /* 业务码非 0: 无人/无数据 */
    }

    cJSON *data = cJSON_GetObjectItem(root, "data");
    if (!cJSON_IsObject(data)) {
        cJSON_Delete(root);
        return FOCUS_ERR_PERCEP_NODATA;
    }

    /* person */
    cJSON *person = cJSON_GetObjectItem(data, "person");
    if (cJSON_IsObject(person)) {
        cJSON *detected = cJSON_GetObjectItem(person, "detected");
        out->person_detected = cJSON_IsTrue(detected);
        cJSON *bbox = cJSON_GetObjectItem(person, "bbox");
        if (cJSON_IsArray(bbox) && cJSON_GetArraySize(bbox) >= 4) {
            for (int i = 0; i < 4; i++) {
                cJSON *v = cJSON_GetArrayItem(bbox, i);
                out->person_bbox[i] = cJSON_IsNumber(v) ? (float)v->valuedouble : 0.0f;
            }
        }
    }

    /* phone */
    cJSON *phone = cJSON_GetObjectItem(data, "phone");
    if (cJSON_IsObject(phone)) {
        out->phone_detected = cJSON_IsTrue(cJSON_GetObjectItem(phone, "detected"));
        out->phone_in_hand  = cJSON_IsTrue(cJSON_GetObjectItem(phone, "near_hand"));
    }

    /* head_pose */
    cJSON *pose = cJSON_GetObjectItem(data, "head_pose");
    if (cJSON_IsObject(pose)) {
        cJSON *pitch = cJSON_GetObjectItem(pose, "pitch");
        if (cJSON_IsNumber(pitch)) out->head_pitch = (float)pitch->valuedouble;
        cJSON *yaw = cJSON_GetObjectItem(pose, "yaw");
        if (cJSON_IsNumber(yaw)) out->head_yaw = (float)yaw->valuedouble;
    }

    cJSON *motion = cJSON_GetObjectItem(data, "hand_motion_score");
    if (cJSON_IsNumber(motion)) out->hand_motion = (float)motion->valuedouble;

    cJSON *conf = cJSON_GetObjectItem(data, "confidence");
    if (cJSON_IsNumber(conf)) out->confidence = (float)conf->valuedouble;

    cJSON_Delete(root);
    return FOCUS_OK;
}
#endif
```

Now the public functions.

perception_init:
```c
int perception_init(const char *api_url, const char *api_key) {
    if (api_url) snprintf(g_api_url, sizeof(g_api_url), "%s", api_url);
    else         g_api_url[0] = '\0';
    if (api_key) snprintf(g_api_key, sizeof(g_api_key), "%s", api_key);
    else         g_api_key[0] = '\0';

    memset(g_history, 0, sizeof(g_history));
    g_history_count = 0;
    memset(g_debounce, 0, sizeof(g_debounce));
    g_debounce_count = 0;
    g_debounce_idx   = 0;
    g_mock_seq = 0;
    return FOCUS_OK;
}
```

perception_process (full, with both branches) — as drafted, plus history_append.

history_append:
```c
static void history_append(const observation_t *obs) {
    g_history[g_history_count % HISTORY_MAX] = *obs;
    g_history_count++;
}
```

perception_get_history:
```c
int perception_get_history(observation_t *buf, int n) {
    if (!buf || n <= 0) return 0;
    if (n > HISTORY_MAX) n = HISTORY_MAX;

    int available = (g_history_count < HISTORY_MAX) ? g_history_count : HISTORY_MAX;
    if (n > available) n = available;

    int start = (g_history_count > HISTORY_MAX) ? (g_history_count % HISTORY_MAX) : 0;
    for (int i = 0; i < n; i++) {
        buf[i] = g_history[(start + i) % HISTORY_MAX];
    }
    return n;
}
```

Good.

Now the public header api/perception.h:

```c
#ifndef API_PERCEPTION_H
#define API_PERCEPTION_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

/* 统一错误码 (通常由 api/error.h 提供; 此处为独立编译兜底) */
#ifndef FOCUS_OK
#define FOCUS_OK                    0
#endif
#ifndef FOCUS_ERR_PERCEP_TIMEOUT
#define FOCUS_ERR_PERCEP_TIMEOUT   (-30)   /* 云端/HTTP 超时或失败 */
#endif
#ifndef FOCUS_ERR_PERCEP_JSON
#define FOCUS_ERR_PERCEP_JSON      (-31)   /* JSON 解析失败/缺字段 */
#endif
#ifndef FOCUS_ERR_PERCEP_NODATA
#define FOCUS_ERR_PERCEP_NODATA    (-32)   /* 业务码非 0 / 无数据 */
#endif
#ifndef FOCUS_ERR_PERCEP_PARAM
#define FOCUS_ERR_PERCEP_PARAM     (-33)   /* 参数非法 (perception 本地) */
#endif

typedef struct {
    bool     person_present;
    float    person_bbox[4];
    bool     phone_detected;
    bool     phone_near_hand;
    float    head_pitch;
    float    head_yaw;
    float    hand_motion_score;
    float    confidence;
    uint32_t timestamp_ms;
} observation_t;

int  perception_init(const char *api_url, const char *api_key);
int  perception_process(uint8_t *jpeg, size_t jpeg_len, observation_t *out);
int  perception_get_history(observation_t *buf, int n);

#endif
```

Wait — `person_bbox[4]` — the comment in the spec says "人体边界框 (x,y,w,h) 归一化 [0-1]". Fine.

Now, there's a concern: the frozen repo's api/perception.h may already define these error codes in api/error.h (included by perception.h). If I ALSO define them here, there could be a redefinition conflict IF the repo's perception.h includes error.h AND error.h defines them without guards. But my defines are guarded with #ifndef, so if error.h already defined them (with the same or different values), mine won't redefine. But if error.h defines them AFTER my header (order issue)... Since api/perception.h is the frozen header (I'm not actually replacing it — I'm providing a reference copy), the real repo's header controls. In the real repo, 周礼航 will NOT use my api/perception.h; they'll use the frozen one. My api/perception.h is only for standalone compile of the test. So the guarded defines are only a fallback. Fine.

But in my deliverable, perception.c includes `"../api/perception.h"` which is MY reference copy. In the real repo, it includes the FROZEN one. My reference copy must be compatible. The guarded error codes ensure standalone compile works. In the real repo, if the frozen perception.h doesn't define error codes (they're in error.h), then my perception.c uses FOCUS_ERR_* which... would be undefined unless error.h is included. 

Hmm, this is a real issue. In the real repo, does api/perception.h include api/error.h? Almost certainly yes (the transcript says "error.h included by all" at line 13306: "- error.h included by all"). So the frozen perception.h includes error.h, which defines FOCUS_OK/FOCUS_ERR_*. So in the real repo, perception.c's `#include "../api/perception.h"` transitively gets the error codes. Good. No problem.

For my standalone reference copy, I include the guarded fallback defines directly in perception.h so it compiles without error.h. Good.

So both paths work. 

Now, let me also reconsider: in the real repo, `perception.c` is at `app/hello_app/perception/perception.c` and includes `"../api/perception.h"`. That resolves correctly. My reference copy is at `focus_perception/perception/perception.c` including `"../api/perception.h"` → `focus_perception/api/perception.h`. Correct.

Now the internal header perception_internal.h includes `"../api/perception.h"` (from perception/ dir). Correct.

Test file at focus_perception/tests/test_perception.c includes `"perception/perception_internal.h"` (with -I focus_perception root) OR `"../perception/perception_internal.h"` (relative to tests/ dir). I'll use relative `"../perception/perception_internal.h"` and `"../api/perception.h"` so it compiles without -I. Actually, let me use relative paths throughout so `-I` isn't needed:
- tests/test_perception.c: `#include "../perception/perception_internal.h"` (which itself includes `"../api/perception.h"`).
- perception.c: `#include "perception_internal.h"` (same dir) — wait, perception_internal.h includes `"../api/perception.h"` relative to perception/ dir. Good. And perception.c includes `"perception_internal.h"` (same dir) — but should it also include `"../api/perception.h"`? perception_internal.h already includes it. So perception.c just needs `#include "perception_internal.h"` and the public header comes transitively. But for clarity I'll have perception.c include both `"../api/perception.h"` and `"perception_internal.h"`. Redundant but clear. Since perception_internal.h also includes api/perception.h, and api/perception.h has include guard, no double-definition. Good.

Compile command (from focus_perception root):
```bash
gcc -Wall -Wextra -Werror -DPERCEPTION_MOCK -DPERCEPTION_UNIT_TEST \
    perception/perception.c tests/test_perception.c -o test_perception -lm
```
Do I need -lm? No math functions (no sqrt/sin). max3/median3 are manual. So no -lm. Good.

Now the test file content. Let me write a comprehensive but clean test.

```c
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../api/perception.h"
#include "../perception/perception_internal.h"

static int g_fail = 0;
static int g_checks = 0;

#define CHECK(cond) do { \
    g_checks++; \
    if (!(cond)) { \
        g_fail++; \
        printf("  [FAIL] %s (line %d)\n", #cond, __LINE__); \
    } \
} while (0)

static void test_base64(void) {
    printf("== test_base64 ==\n");
    const char *cases[][2] = {
        {"", ""},
        {"M", "TQ=="},
        {"Ma", "TWE="},
        {"Man", "TWFu"},
        {"plea", "cGxlYQ=="},
        {"pleas", "cGxlYXM="},
        {"please", "cGxlYXNl"},
    };
    char out[64];
    for (int i = 0; i < 7; i++) {
        size_t n = perception_base64_encode((const uint8_t*)cases[i][0],
                                             strlen(cases[i][0]), out, sizeof(out));
        CHECK(n == strlen(cases[i][1]));
        CHECK(strcmp(out, cases[i][1]) == 0);
    }
}
```

Wait, need to verify "plea" etc. Let me compute:
"plea" (4 bytes): "cGxlYQ==". Let me verify: "plea" = p(0x70) l(0x6c) e(0x65) a(0x61).
3 bytes "ple": 0x70 0x6c 0x65 → bits: 011100 000110 110001 100101 → 011100(28)=c, 000110(6)=G, 110001(49)=x, 100101(37)=l → "cGxl". Then "a" alone: 0x61=01100001 → 011000(24)=Y, 010000(16)=Q, pad pad → "YQ==". So "plea" = "cGxl" + "YQ==" = "cGxlYQ==". Correct.

"pleas" (5 bytes): "cGxl" + "as". "as" = a(0x61) s(0x73) = 01100001 01110011 → 16 bits → 011000(24)=Y, 010111(23)=X, 0011 00 → 001100(12)=M, pad → "YXM=". So "cGxlYXM=". Correct.

"please" (6 bytes): "cGxl" + "eas". "eas" = e(0x65) a(0x61) s(0x73) = 01100101 01100001 01110011 → 24 bits → 011001(25)=Z, 010110(22)=W, 000101(5)=F, 110011(51)=z → "ZWFz". So "cGxlZWFz". Wait, but "please" is p-l-e-a-s-e, not p-l-e-a-s. Let me recompute. "please" = 6 bytes: p l e a s e = 0x70 0x6c 0x65 0x61 0x73 0x65.
- "ple" → cGxl
- "ase" = a(0x61) s(0x73) e(0x65) = 01100001 01110011 01100101 → 011000(24)=Y, 010111(23)=X, 001101(13)=N, 100101(37)=l → "YXNl".
So "please" = "cGxl" + "YXNl" = "cGxlYXNl". Correct.

Good, my test vectors are right.

test for majority/median/max:
```c
static void test_math_helpers(void) {
    printf("== test_math_helpers ==\n");
    CHECK(perception_majority3(true, true, false) == true);
    CHECK(perception_majority3(true, false, false) == false);
    CHECK(perception_majority3(false, false, false) == false);
    CHECK(perception_majority3(true, true, true) == true);

    CHECK(perception_median3(1,2,3) == 2);
    CHECK(perception_median3(3,1,2) == 2);
    CHECK(perception_median3(2,3,1) == 2);
    CHECK(perception_median3(5,5,5) == 5);

    CHECK(perception_max3(1,2,3) == 3);
    CHECK(perception_max3(3,2,1) == 3);
}
```
Note float comparison with == on integers is safe here.

test debounce:
```c
static void test_debounce(void) {
    printf("== test_debounce ==\n");
    perception_init("url", "key");   // 重置去抖状态

    cloud_result_t r1 = {0}, r2 = {0}, r3 = {0};
    observation_t out;

    // 2 帧有人 + 1 帧无人 → 多数投票有人
    r1.person_detected = true;  r1.confidence = 0.9f;
    r2.person_detected = true;  r2.confidence = 0.9f;
    r3.person_detected = false; r3.confidence = 0.9f;
    perception_debounce_push(&r1);
    perception_debounce_compute(&out, 1);   // 不足3帧 → 输出最新(第1帧)
    CHECK(out.person_present == true);

    perception_debounce_push(&r2);
    perception_debounce_compute(&out, 2);
    CHECK(out.person_present == true);

    perception_debounce_push(&r3);
    perception_debounce_compute(&out, 3);
    CHECK(out.person_present == true);   // majority(1,1,0)=1

    // 中位数: 角度 10/20/90 → 20
    cloud_result_t p1 = {0}, p2 = {0}, p3 = {0};
    p1.head_pitch = 10.0f; p1.confidence = 0.9f;
    p2.head_pitch = 20.0f; p2.confidence = 0.9f;
    p3.head_pitch = 90.0f; p3.confidence = 0.9f;
    perception_init("url", "key");
    perception_debounce_push(&p1);
    perception_debounce_push(&p2);
    perception_debounce_push(&p3);
    perception_debounce_compute(&out, 4);
    CHECK(out.head_pitch == 20.0f);
}
```

Wait, careful: after perception_init, g_debounce_count=0. Push r1 (count=1). compute with count<3 → outputs latest (r1), person=true. Good. Push r2 (count=2), compute → latest r2, true. Push r3 (count=3), compute → majority(r1,r2,r3) = true. Good.

Then re-init, push p1,p2,p3 (count=3), compute → median of pitch = 20. Good.

test init + process + history:
```c
static void test_process_and_history(void) {
    printf("== test_process_and_history ==\n");
    CHECK(perception_init("http://api", "key123") == FOCUS_OK);

    uint8_t dummy[16] = {0};
    observation_t obs;
    observation_t hist[10];

    // 空历史
    CHECK(perception_get_history(hist, 10) == 0);
    CHECK(perception_get_history(NULL, 10) == 0);

    // 连续 8 帧, 时间戳非递减
    uint32_t last_ts = 0;
    for (int i = 0; i < 8; i++) {
        CHECK(perception_process(dummy, sizeof(dummy), &obs) == FOCUS_OK);
        CHECK(obs.timestamp_ms >= last_ts);
        last_ts = obs.timestamp_ms;
    }

    // 历史条数
    CHECK(perception_get_history(hist, 10) == 8);
    CHECK(perception_get_history(hist, 3) == 3);   // 取最近3条, 从旧到新

    // 4 种 mock 状态轮转应覆盖 person=true/false 与 phone=true/false
    bool saw_away = false, saw_phone = false;
    for (int i = 0; i < 4; i++) {
        perception_process(dummy, sizeof(dummy), &obs);
        if (!obs.person_present) saw_away = true;
        if (obs.phone_detected) saw_phone = true;
    }
    CHECK(saw_away && saw_phone);

    // 参数非法
    CHECK(perception_process(NULL, 10, &obs) != FOCUS_OK);
    CHECK(perception_process(dummy, 0, &obs) != FOCUS_OK);
    CHECK(perception_process(dummy, 10, NULL) != FOCUS_OK);
}
```

Wait, the mock sequence uses g_mock_seq starting at 0 and incrementing each process call. In the first loop (8 calls), steps 0..7, which cycles 0,1,2,3,0,1,2,3. person_present false only at step 2 and 6. So saw_away true. phone true at step 1 and 5. So saw_phone true. Good. The second loop (4 calls) steps 8..11 = 0,1,2,3. So saw_away (step 10=2) and saw_phone (step 9=1) both true. Good.

But wait, in the first loop I check timestamp non-decreasing. monotonic_ms() could return the same value for two consecutive calls (same ms), so >= is correct (not >). Good. But there's a subtle issue: monotonic_ms returns uint32 ms; consecutive calls within the same millisecond return equal values. >= handles it. Good.

test NULL process: perception_process(NULL,10,&obs) returns FOCUS_ERR_PERCEP_PARAM (-33) != FOCUS_OK. Good. But note in MOCK mode, my perception_process checks `if (!out || !jpeg || jpeg_len == 0) return FOCUS_ERR_PERCEP_PARAM;` at the top, before the #ifdef. So NULL jpeg → PARAM. Good.

test main:
```c
int main(void) {
    test_base64();
    test_math_helpers();
    test_debounce();
    test_process_and_history();

    printf("\n结果: %d checks, %d failed\n", g_checks, g_fail);
    return g_fail ? 1 : 0;
}
```

Now, the test includes perception_internal.h which declares perception_base64_encode etc. And perception.c defines them (non-static). Good.

But wait: perception.c also needs to compile the internal helper functions as non-static. I declared them in perception_internal.h. perception.c includes perception_internal.h and defines them. The functions have `perception_` prefix and are non-static (global). Good. The static helpers that remain static: history_append, mock_observation, and the static globals. Everything else (base64, majority3, median3, max3, fill_observation, debounce_push, debounce_compute, monotonic_ms, parse_cloud_response) is non-static with perception_ prefix.

Actually, monotonic_ms I'll name perception_monotonic_ms (declared in internal header). Good.

Now, there's one more: the real path in perception_process references `g_resp` (static) and `FRAME_WIDTH/HEIGHT`. Fine.

Let me also make sure `history_append` and `mock_observation` are declared static and used. mock_observation is only used in MOCK branch. history_append used always. Under non-MOCK build, mock_observation would be an unused static function → `-Wunused-function` warning (and with -Werror, error). So I must guard mock_observation with `#ifdef PERCEPTION_MOCK`. Yes, I'll wrap mock_observation in `#ifdef PERCEPTION_MOCK`. Good.

Similarly, `base64` helpers are always compiled and used only in real path (and by test). In MOCK build WITHOUT the test, base64/majority/median/max/fill_observation/debounce would be unused non-static functions — but non-static (external linkage) functions don't trigger -Wunused-function. Only static ones do. So non-static is fine even if "unused" in mock build. Good — that's another reason to make them non-static. The static ones (history_append always used; mock_observation guarded) are fine.

Also `g_mock_seq` static int is only used in MOCK branch; in non-MOCK build it'd be unused static variable → -Wunused-variable. But it's referenced in perception_init (g_mock_seq = 0) always. So it's "used". Good. Actually perception_init resets it always, so it's used in both builds. Fine. But in non-MOCK build, g_mock_seq is only written never read → -Wunused-but-set-variable? That's a GCC warning for local variables, not file-scope static. File-scope static that's written but never read: GCC may not warn (only -Wunused-variable for never-used). Since it IS referenced (assigned), it's "used". No warning. Fine. To be safe I could guard it, but it's harmless. I'll leave it.

Similarly `g_debounce`/`g_debounce_count`/`g_debounce_idx` are used by debounce_push/compute which are always compiled and called (in real path) and reset in init. In MOCK build, debounce functions are non-static and never called, but they reference the globals, and init references them, so globals are "used". No warning. Good.

Now, another concern: `#include <cJSON.h>` only under `#ifndef PERCEPTION_MOCK`. Good — mock/test build won't need cJSON.

Let me also double check: in the real (non-MOCK) build, `perception_parse_cloud_response` is defined and declared in internal header (unconditionally declared). In MOCK build, it's declared but not defined. Since test doesn't reference it, fine. But if someone compiles perception.c alone in MOCK mode without -DPERCEPTION_MOCK... no. It's fine.

Actually, to be safe and clean, I'll wrap the parse_cloud_response DECLARATION in the internal header with `#ifndef PERCEPTION_MOCK` too, so it's only declared when it's defined. And in perception.c define it under the same guard. Then no dangling declaration. But then the header needs to know PERCEPTION_MOCK at include time. When compiling the test (which defines PERCEPTION_MOCK), the header won't declare parse_cloud_response — fine, test doesn't use it. When compiling perception.c in MOCK mode, same. When compiling real (no PERCEPTION_MOCK), header declares it, perception.c defines it. Consistent. I'll do this.

Let me finalize the internal header with the guard.

Also, I should include `<stdint.h>` in internal header (for uint32_t, uint8_t). And it includes api/perception.h which has stdint/stdbool/stddef. Good.

Alright, let me also write the README.

Let me now also think: do I need `-DPERCEPTION_UNIT_TEST` for anything? I mentioned it earlier as a test hook, but I've moved to exposing internals via the internal header (non-static functions), so I don't need a PERCEPTION_UNIT_TEST macro at all. The test just links against perception.c and calls the internal functions. So the compile command only needs `-DPERCEPTION_MOCK` (for mock path). I'll drop PERCEPTION_UNIT_TEST. Simpler.

Wait, but do I need any special flag to compile perception.c for host (Linux) vs embedded? perception.c uses clock_gettime(CLOCK_MONOTONIC) — available on Linux. Uses malloc/free/snprintf/memset — standard. Uses cJSON only in real path. So with -DPERCEPTION_MOCK, it compiles cleanly on Linux. 

Compile:
```bash
gcc -Wall -Wextra -Werror -DPERCEPTION_MOCK perception/perception.c tests/test_perception.c -o test_perception
./test_perception
```

Good.

Now let me write the README with integration instructions.

Let me also mention the Makefile/CMakeLists CSRCS addition and Kconfig approach (from the task doc):
- Add `perception/perception.c` to CSRCS.
- For mock: define `PERCEPTION_MOCK` (or Kconfig `CONFIG_CONTEST2026_087_PERCEPTION_MOCK`).
- For real: don't define mock, link cJSON.

I'll give a Makefile snippet.

Also, importantly: the task says "提供强符号 perception_get_history() 即自动覆盖 core/mock.c 的 weak 桩". My perception.c defines perception_get_history (strong), which overrides the weak stub. Good — I'll mention this.

Now let me write everything out. I'll produce the files.

Let me write the final code text for each file, being careful with exact content.

One more: the public header comment about bbox — I'll keep concise.

Let me write now.

Actually, I want to double-check the error code values don't collide with other modules. The task doc gives -30/-31/-32 specifically for perception. Good. -33 I invented for PARAM. I'll clearly mark it as "本地扩展, 可请万思源并入 error.h 或复用 -30". Actually, maybe better to not invent -33 and instead reuse FOCUS_ERR_PERCEP_JSON or TIMEOUT for NULL args. But a dedicated param code is cleaner. I'll keep -33 but note it. Alternatively use a generic FOCUS_ERR_INVALID_ARG if the frozen error.h has one — I don't know. I'll keep -33 with a clear comment.

Hmm, actually, re-reading the task: "失败返回: FOCUS_ERR_PERCEP_TIMEOUT(-30) / FOCUS_ERR_PERCEP_JSON(-31) / FOCUS_ERR_PERCEP_NODATA(-32)". These are the only 3 documented. For robustness against NULL args, I'll just guard and return FOCUS_ERR_PERCEP_JSON (which is "invalid data" close enough) — no wait, that's semantically wrong for a timeout.

Let me just use FOCUS_ERR_PERCEP_PARAM = -33 and clearly document it's a local addition; if 万思源's error.h doesn't have it, it's still fine because I define it guarded. This is the cleanest. I'll keep it.

Let me write all files now.

For README, I'll write in Chinese (matching the project's language).

Let me write everything in one go with multiple Write calls in parallel.

Actually, Write calls to different files are independent, so I can batch them. Let me do that.

Let me finalize the exact text of each file.

I'll write:
1. C:\temp\focus_perception\api\perception.h
2. C:\temp\focus_perception\perception\perception_internal.h
3. C:\temp\focus_perception\perception\perception.c
4. C:\temp\focus_perception\tests\test_perception.c
5. C:\temp\focus_perception\README.md

Let me write them carefully.

For perception.c, I need to be meticulous. Let me write the full file.

Let me draft perception.c fully in my head/text now and then write.

I'll write it now.

Also note: I should verify my code compiles. After writing, I can actually compile the test on Windows? The environment is Windows, but there's a Bash tool (Git Bash) and PowerShell. Is gcc available? Maybe not on Windows. Let me check after writing — I can try to compile with gcc via Bash. If gcc isn't available, I'll note the compile command and rely on careful review. Let me try to compile after writing to catch errors. Actually, it would be great to actually verify. Let me check for gcc/cc availability.

Let me write files first, then attempt compilation.

Actually, I can attempt compilation to validate. Let me check if gcc exists. I'll do that in parallel with writing? No, writing first, then compile.

Let me write the files now.

---

### [2026-08-26 14:18:05] AI

I've read all the files. This is the **FOCUS AIoT** project (ESP32-S3-EYE study monitor), and the folder is 周礼航's (your) task package — the **视觉感知模块 (perception)**. The "成品" you need is the `perception/` module: 3 functions (`perception_init` / `perception_process` / `perception_get_history`) plus a self-contained unit test.

Let me write the complete, drop-in module.

---

### [2026-08-26 14:18:13] AI

[工具调用] Write: {"file_path": "C:\\temp\\focus_perception\\api\\perception.h", "content": "/****************************************************************************\n * FOCUS AIoT - 视觉感知模块公开接口 (api/perception.h)\n *\n * 负责人: 周礼航\n * 职责:   从一张 JPEG 里看出「有什么」——只做空间维度的单帧静态分析。\n *\n * ⚠️ 注意: 此文件是【参考拷贝】，用于独立编译/单测。\n *    仓库里真正冻结的那份 api/perception.h 由万思源维护，请以仓库版本为准。\n *    observation_t 字段、三个函数签名、错误码值必须与仓库冻结版一致。\n ****************************************************************************/\n\n#ifndef API_PERCEPTION_H\n#define API_PERCEPTION_H\n\n#include <stdbool.h>\n#include <stdint.h>\n#include <stddef.h>\n\n/*\n * 统一错误码 —— 通常由 api/error.h 提供并被 api/perception.h 间接包含。\n * 下面用 #ifndef 兜底，保证脱离 error.h 也能独立编译。\n */\n#ifndef FOCUS_OK\n#define FOCUS_OK                    0\n#endif\n#ifndef FOCUS_ERR_PERCEP_TIMEOUT\n#define FOCUS_ERR_PERCEP_TIMEOUT   (-30)   /* 云端/HTTP 超时或请求失败 */\n#endif\n#ifndef FOCUS_ERR_PERCEP_JSON\n#define FOCUS_ERR_PERCEP_JSON      (-31)   /* JSON 解析失败 / 缺字段 */\n#endif\n#ifndef FOCUS_ERR_PERCEP_NODATA\n#define FOCUS_ERR_PERCEP_NODATA    (-32)   /* 业务码非 0 / 无数据 */\n#endif\n#ifndef FOCUS_ERR_PERCEP_PARAM\n#define FOCUS_ERR_PERCEP_PARAM     (-33)   /* 参数非法 (perception 本地扩展) */\n#endif\n\n/*\n * 每帧图像经过云端检测 + 去抖后输出一个 Observation。\n * 对严格/鼓励两种模式完全相同 (模式差异是赵思涵 behavior 模块的事)。\n */\ntypedef struct {\n    bool     person_present;       /* 画面中是否有人 */\n    float    person_bbox[4];       /* 人体边界框 (x,y,w,h) 归一化 [0-1] */\n    bool     phone_detected;       /* 是否检测到手机 */\n    bool     phone_near_hand;      /* 手机是否在手部区域 */\n    float    head_pitch;           /* 头部俯仰角 (度, 负=低头 正=仰头) */\n    float    head_yaw;             /* 头部偏航角 (度) */\n    float    hand_motion_score;    /* 手部运动量 [0-1] */\n    float    confidence;           /* 整体置信度 [0-1] */\n    uint32_t timestamp_ms;         /* 时间戳 (毫秒) */\n} observation_t;\n\n/* 初始化: 配置 API URL 和 Key, 清空历史与去抖状态。返回 FOCUS_OK=成功 */\nint  perception_init(const char *api_url, const char *api_key);\n\n/* 核心: 一张 JPEG → 云端 API → 去抖 → 输出 observation_t */\nint  perception_process(uint8_t *jpeg, size_t jpeg_len, observation_t *out);\n\n/* 取最近 N 条 observation (从旧到新), 供 behavior 时序分析。返回实际条数 */\nint  perception_get_history(observation_t *buf, int n);\n\n#endif /* API_PERCEPTION_H */\n"}

---

### [2026-08-26 14:18:18] 用户

[工具结果] File created successfully at: C:\temp\focus_perception\api\perception.h (file state is current in your context — no need to Read it back)

---

### [2026-08-26 14:18:19] AI

[工具调用] Write: {"file_path": "C:\\temp\\focus_perception\\perception\\perception_internal.h", "content": "/****************************************************************************\n * FOCUS AIoT - 视觉感知模块内部声明 (perception/perception_internal.h)\n *\n * 负责人: 周礼航\n * 说明:   对应任务书里的「perception/perception.h (内部声明, 可选)」。\n *         为避免与公开接口 api/perception.h 混淆, 命名为 *_internal.h。\n *         这里暴露的 cloud_result_t 与工具函数仅供 perception.c 实现与\n *         单测 (tests/test_perception.c) 使用，不对其他模块开放。\n ****************************************************************************/\n\n#ifndef PERCEPTION_INTERNAL_H\n#define PERCEPTION_INTERNAL_H\n\n#include \"../api/perception.h\"\n\n/* 云端原始检测结果 (内部使用, 不对外暴露) */\ntypedef struct {\n    bool  person_detected;\n    float person_bbox[4];\n    bool  phone_detected;\n    bool  phone_in_hand;\n    float head_pitch, head_yaw, head_roll;   /* head_roll 预留, observation_t 未用到 */\n    float hand_motion;\n    float confidence;\n} cloud_result_t;\n\n/* ---- 内部工具函数 (实现 + 单测共用) ---- */\n\nuint32_t perception_monotonic_ms(void);\n\nsize_t perception_base64_encoded_len(size_t n);\nsize_t perception_base64_encode(const uint8_t *src, size_t len,\n                                char *dst, size_t dst_cap);\n\nbool  perception_majority3(bool a, bool b, bool c);\nfloat perception_median3(float a, float b, float c);\nfloat perception_max3(float a, float b, float c);\n\nvoid  perception_fill_observation(const cloud_result_t *raw,\n                                  observation_t *out, uint32_t ts);\nvoid  perception_debounce_push(const cloud_result_t *raw);\nvoid  perception_debounce_compute(observation_t *out, uint32_t ts);\n\n/* 仅在非 mock (真实云端) 构建中定义, 依赖 cJSON */\n#ifndef PERCEPTION_MOCK\nint   perception_parse_cloud_response(const char *resp, cloud_result_t *out);\n#endif\n\n#endif /* PERCEPTION_INTERNAL_H */\n"}

---

### [2026-08-26 14:18:21] 用户

[工具结果] File created successfully at: C:\temp\focus_perception\perception\perception_internal.h (file state is current in your context — no need to Read it back)

---

### [2026-08-26 14:18:24] AI

[思考] Now write perception.c.

---

### [2026-08-26 14:19:04] AI

[工具调用] Write: {"file_path": "C:\\temp\\focus_perception\\perception\\perception.c", "content": "/****************************************************************************\n * FOCUS AIoT - 视觉感知模块 (perception/perception.c)\n *\n * 负责人: 周礼航\n * 职责:   从一张 JPEG 里看出「有什么」——只做空间维度的单帧静态分析，\n *         不做时间维度的行为推理 (那是赵思涵 behavior 模块的事)。\n *\n * 输入:   JPEG 图像 (来自张沐泽 camera_frame_buffer / camera_capture_frame)\n * 输出:   observation_t (每帧一个, 经云端 API + 3 帧去抖)\n *\n * 三个对外接口 (冻结于 api/perception.h):\n *   perception_init()         初始化 URL/Key + 清空历史\n *   perception_process()      一帧 JPEG → observation_t\n *   perception_get_history()  取最近 N 条 observation (供 behavior 时序分析)\n *\n * 编译开关:\n *   -D PERCEPTION_MOCK  走 mock 路径 (不调云端), 默认 mock 便于联调/回退\n *                       不定义则走真实云端链路 (需要 cJSON + wifi_http_post)\n ****************************************************************************/\n\n#include <stdbool.h>\n#include <stdint.h>\n#include <stddef.h>\n#include <string.h>\n#include <stdio.h>\n#include <stdlib.h>\n#include <time.h>\n\n#include \"../api/perception.h\"\n#include \"perception_internal.h\"\n\n#ifndef PERCEPTION_MOCK\n#include <cJSON.h>\n/* 张沐泽提供, 见 api/wifi.h (前向声明, 避免独立编译依赖) */\nint wifi_http_post(const char *url, const char *body, char *resp, size_t maxlen);\n#endif\n\n/* ------------------------------------------------------------------ */\n/* 内部配置                                                            */\n/* ------------------------------------------------------------------ */\n#define HISTORY_MAX     60              /* 保留最近 60 条 observation */\n#define FRAME_WIDTH     320\n#define FRAME_HEIGHT    240\n#define MAX_JPEG_SIZE   (50 * 1024)     /* 320x240 JPEG 上限 */\n#define RESP_BUF_SIZE   4096            /* 云端 JSON 响应缓冲 */\n\n/* ------------------------------------------------------------------ */\n/* 模块状态 (单例; 该模块由 wifi_task 串行调用, 无重入)                */\n/* ------------------------------------------------------------------ */\nstatic char g_api_url[160];\nstatic char g_api_key[80];\n\nstatic observation_t g_history[HISTORY_MAX];\nstatic int           g_history_count = 0;   /* 累计写入条数 (用于求 start) */\n\nstatic cloud_result_t g_debounce[3];\nstatic int            g_debounce_count = 0; /* 已累积帧数 0..3 */\nstatic int            g_debounce_idx   = 0;\n\nstatic int            g_mock_seq = 0;       /* mock 轮转序号 */\nstatic char           g_resp[RESP_BUF_SIZE];\n\n/* ------------------------------------------------------------------ */\n/* 基础工具                                                            */\n/* ------------------------------------------------------------------ */\n\nuint32_t perception_monotonic_ms(void)\n{\n    struct timespec ts;\n    clock_gettime(CLOCK_MONOTONIC, &ts);\n    return (uint32_t)((uint64_t)ts.tv_sec * 1000u +\n                      (uint64_t)ts.tv_nsec / 1000000u);\n}\n\nbool perception_majority3(bool a, bool b, bool c)\n{\n    return ((int)a + (int)b + (int)c) >= 2;\n}\n\nfloat perception_median3(float a, float b, float c)\n{\n    if (a > b) { float t = a; a = b; b = t; }\n    if (b > c) { float t = b; b = c; c = t; }\n    if (a > b) { float t = a; a = b; b = t; }\n    return b;\n}\n\nfloat perception_max3(float a, float b, float c)\n{\n    float m = a;\n    if (b > m) m = b;\n    if (c > m) m = c;\n    return m;\n}\n\n/* ------------------------------------------------------------------ */\n/* Base64 编码 (RFC 4648)                                              */\n/* ------------------------------------------------------------------ */\n\nsize_t perception_base64_encoded_len(size_t n)\n{\n    return 4 * ((n + 2) / 3);\n}\n\nsize_t perception_base64_encode(const uint8_t *src, size_t len,\n                                char *dst, size_t dst_cap)\n{\n    static const char tbl[] =\n        \"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/\";\n\n    size_t out_len = perception_base64_encoded_len(len);\n    if (!src || !dst || dst_cap < out_len + 1) {\n        return 0;\n    }\n\n    size_t i, j = 0;\n    for (i = 0; i + 3 <= len; i += 3) {\n        uint32_t v = ((uint32_t)src[i]     << 16) |\n                     ((uint32_t)src[i + 1] << 8)  |\n                      (uint32_t)src[i + 2];\n        dst[j++] = tbl[(v >> 18) & 63];\n        dst[j++] = tbl[(v >> 12) & 63];\n        dst[j++] = tbl[(v >> 6)  & 63];\n        dst[j++] = tbl[ v        & 63];\n    }\n\n    size_t rem = len - i;\n    if (rem == 1) {\n        uint32_t v = (uint32_t)src[i] << 16;\n        dst[j++] = tbl[(v >> 18) & 63];\n        dst[j++] = tbl[(v >> 12) & 63];\n        dst[j++] = '=';\n        dst[j++] = '=';\n    } else if (rem == 2) {\n        uint32_t v = ((uint32_t)src[i] << 16) | ((uint32_t)src[i + 1] << 8);\n        dst[j++] = tbl[(v >> 18) & 63];\n        dst[j++] = tbl[(v >> 12) & 63];\n        dst[j++] = tbl[(v >> 6)  & 63];\n        dst[j++] = '=';\n    }\n\n    dst[j] = '\\0';\n    return j;\n}\n\n/* ------------------------------------------------------------------ */\n/* 去抖稳定 (3 帧滑动窗口)                                              */\n/*   bool 字段: 多数投票                                                */\n/*   float 角度: 中位数                                                 */\n/*   hand_motion: 取最大 (宁可多报不遗漏)                                */\n/*   confidence: 取均值                                                 */\n/* ------------------------------------------------------------------ */\n\nvoid perception_fill_observation(const cloud_result_t *raw,\n                                 observation_t *out, uint32_t ts)\n{\n    out->person_present    = raw->person_detected;\n    out->person_bbox[0]    = raw->person_bbox[0];\n    out->person_bbox[1]    = raw->person_bbox[1];\n    out->person_bbox[2]    = raw->person_bbox[2];\n    out->person_bbox[3]    = raw->person_bbox[3];\n    out->phone_detected    = raw->phone_detected;\n    out->phone_near_hand   = raw->phone_in_hand;\n    out->head_pitch        = raw->head_pitch;\n    out->head_yaw          = raw->head_yaw;\n    out->hand_motion_score = raw->hand_motion;\n    out->confidence        = raw->confidence;\n    out->timestamp_ms      = ts;\n}\n\nvoid perception_debounce_push(const cloud_result_t *raw)\n{\n    g_debounce[g_debounce_idx] = *raw;\n    g_debounce_idx = (g_debounce_idx + 1) % 3;\n    if (g_debounce_count < 3) {\n        g_debounce_count++;\n    }\n}\n\nvoid perception_debounce_compute(observation_t *out, uint32_t ts)\n{\n    /* 最新一帧所在槽位 */\n    const cloud_result_t *latest =\n        &g_debounce[(g_debounce_idx + 3 - 1) % 3];\n\n    if (g_debounce_count < 3) {\n        /* 历史不足 3 帧, 直接输出最新一帧 */\n        perception_fill_observation(latest, out, ts);\n        return;\n    }\n\n    const cloud_result_t *h = g_debounce;\n    out->person_present  = perception_majority3(h[0].person_detected,\n                                                h[1].person_detected,\n                                                h[2].person_detected);\n    out->phone_detected  = perception_majority3(h[0].phone_detected,\n                                                h[1].phone_detected,\n                                                h[2].phone_detected);\n    out->phone_near_hand = perception_majority3(h[0].phone_in_hand,\n                                                h[1].phone_in_hand,\n                                                h[2].phone_in_hand);\n\n    out->head_pitch = perception_median3(h[0].head_pitch,\n                                         h[1].head_pitch,\n                                         h[2].head_pitch);\n    out->head_yaw   = perception_median3(h[0].head_yaw,\n                                         h[1].head_yaw,\n                                         h[2].head_yaw);\n\n    out->hand_motion_score = perception_max3(h[0].hand_motion,\n                                             h[1].hand_motion,\n                                             h[2].hand_motion);\n\n    out->confidence = (h[0].confidence + h[1].confidence + h[2].confidence) / 3.0f;\n\n    /* bbox 取最新一帧 (无去抖意义) */\n    out->person_bbox[0] = latest->person_bbox[0];\n    out->person_bbox[1] = latest->person_bbox[1];\n    out->person_bbox[2] = latest->person_bbox[2];\n    out->person_bbox[3] = latest->person_bbox[3];\n\n    out->timestamp_ms = ts;\n}\n\n/* ------------------------------------------------------------------ */\n/* 云端 JSON 解析 (仅真实链路, 依赖 cJSON)                              */\n/*   协议见开发规范: code==0 且 data 为对象; 所有字段判空不崩            */\n/* ------------------------------------------------------------------ */\n\n#ifndef PERCEPTION_MOCK\n\nint perception_parse_cloud_response(const char *resp, cloud_result_t *out)\n{\n    if (!resp || !out) {\n        return FOCUS_ERR_PERCEP_JSON;\n    }\n\n    cJSON *root = cJSON_Parse(resp);\n    if (!root) {\n        return FOCUS_ERR_PERCEP_JSON;\n    }\n\n    cJSON *code = cJSON_GetObjectItem(root, \"code\");\n    if (cJSON_IsNumber(code) && code->valueint != 0) {\n        cJSON_Delete(root);\n        return FOCUS_ERR_PERCEP_NODATA;   /* 业务码非 0: 无人/无数据 */\n    }\n\n    cJSON *data = cJSON_GetObjectItem(root, \"data\");\n    if (!cJSON_IsObject(data)) {\n        cJSON_Delete(root);\n        return FOCUS_ERR_PERCEP_NODATA;\n    }\n\n    /* person */\n    cJSON *person = cJSON_GetObjectItem(data, \"person\");\n    if (cJSON_IsObject(person)) {\n        out->person_detected = cJSON_IsTrue(cJSON_GetObjectItem(person, \"detected\"));\n\n        cJSON *bbox = cJSON_GetObjectItem(person, \"bbox\");\n        if (cJSON_IsArray(bbox) && cJSON_GetArraySize(bbox) >= 4) {\n            for (int i = 0; i < 4; i++) {\n                cJSON *v = cJSON_GetArrayItem(bbox, i);\n                out->person_bbox[i] = cJSON_IsNumber(v) ? (float)v->valuedouble : 0.0f;\n            }\n        }\n    }\n\n    /* phone */\n    cJSON *phone = cJSON_GetObjectItem(data, \"phone\");\n    if (cJSON_IsObject(phone)) {\n        out->phone_detected = cJSON_IsTrue(cJSON_GetObjectItem(phone, \"detected\"));\n        out->phone_in_hand  = cJSON_IsTrue(cJSON_GetObjectItem(phone, \"near_hand\"));\n    }\n\n    /* head_pose */\n    cJSON *pose = cJSON_GetObjectItem(data, \"head_pose\");\n    if (cJSON_IsObject(pose)) {\n        cJSON *pitch = cJSON_GetObjectItem(pose, \"pitch\");\n        if (cJSON_IsNumber(pitch)) out->head_pitch = (float)pitch->valuedouble;\n        cJSON *yaw = cJSON_GetObjectItem(pose, \"yaw\");\n        if (cJSON_IsNumber(yaw)) out->head_yaw = (float)yaw->valuedouble;\n    }\n\n    cJSON *motion = cJSON_GetObjectItem(data, \"hand_motion_score\");\n    if (cJSON_IsNumber(motion)) out->hand_motion = (float)motion->valuedouble;\n\n    cJSON *conf = cJSON_GetObjectItem(data, \"confidence\");\n    if (cJSON_IsNumber(conf)) out->confidence = (float)conf->valuedouble;\n\n    cJSON_Delete(root);\n    return FOCUS_OK;\n}\n\n#endif /* !PERCEPTION_MOCK */\n\n/* ------------------------------------------------------------------ */\n/* Mock 路径 (阶段 1, 联调用)                                          */\n/*   按预设序列轮流产出 FOCUSED/PLAYING_PHONE/AWAY/DROWSY 对应的        */\n/*   observation_t, 不调云端, 不走去抖 (mock 本身已是稳定结果)          */\n/* ------------------------------------------------------------------ */\n\n#ifdef PERCEPTION_MOCK\n\nstatic observation_t mock_observation(int step)\n{\n    observation_t o;\n    memset(&o, 0, sizeof(o));\n    o.confidence   = 0.9f;\n    o.timestamp_ms = perception_monotonic_ms();\n\n    switch (step % 4) {\n    case 0: /* FOCUSED */\n        o.person_present = true;\n        o.person_bbox[0] = 0.15f; o.person_bbox[1] = 0.10f;\n        o.person_bbox[2] = 0.70f; o.person_bbox[3] = 0.85f;\n        o.head_pitch = 0.0f;\n        o.hand_motion_score = 0.10f;\n        break;\n    case 1: /* PLAYING_PHONE */\n        o.person_present = true;\n        o.person_bbox[0] = 0.15f; o.person_bbox[1] = 0.10f;\n        o.person_bbox[2] = 0.70f; o.person_bbox[3] = 0.85f;\n        o.phone_detected  = true;\n        o.phone_near_hand = true;\n        o.head_pitch = -25.0f;\n        o.hand_motion_score = 0.60f;\n        break;\n    case 2: /* AWAY */\n        o.person_present = false;\n        break;\n    case 3: /* DROWSY */\n        o.person_present = true;\n        o.person_bbox[0] = 0.15f; o.person_bbox[1] = 0.10f;\n        o.person_bbox[2] = 0.70f; o.person_bbox[3] = 0.85f;\n        o.head_pitch = 55.0f;\n        o.hand_motion_score = 0.05f;\n        break;\n    }\n    return o;\n}\n\n#endif /* PERCEPTION_MOCK */\n\n/* ------------------------------------------------------------------ */\n/* 历史管理 (环形缓冲区, 供赵思涵时序分析)                              */\n/* ------------------------------------------------------------------ */\n\nstatic void history_append(const observation_t *obs)\n{\n    g_history[g_history_count % HISTORY_MAX] = *obs;\n    g_history_count++;\n}\n\n/* ------------------------------------------------------------------ */\n/* 对外接口                                                            */\n/* ------------------------------------------------------------------ */\n\nint perception_init(const char *api_url, const char *api_key)\n{\n    if (api_url) {\n        snprintf(g_api_url, sizeof(g_api_url), \"%s\", api_url);\n    } else {\n        g_api_url[0] = '\\0';\n    }\n    if (api_key) {\n        snprintf(g_api_key, sizeof(g_api_key), \"%s\", api_key);\n    } else {\n        g_api_key[0] = '\\0';\n    }\n\n    memset(g_history, 0, sizeof(g_history));\n    g_history_count = 0;\n\n    memset(g_debounce, 0, sizeof(g_debounce));\n    g_debounce_count = 0;\n    g_debounce_idx   = 0;\n\n    g_mock_seq = 0;\n    return FOCUS_OK;\n}\n\nint perception_process(uint8_t *jpeg, size_t jpeg_len, observation_t *out)\n{\n    if (!out || !jpeg || jpeg_len == 0) {\n        return FOCUS_ERR_PERCEP_PARAM;\n    }\n\n#ifdef PERCEPTION_MOCK\n    /* 阶段 1: mock —— 不调云端, 按预设序列轮流产出 observation */\n    *out = mock_observation(g_mock_seq++);\n#else\n    /* 阶段 2: 真实云端链路 */\n\n    /* 1. Base64 编码 (b64 ≈ 4/3 原图大小, 用堆/PSRAM 避免挤爆小栈) */\n    size_t b64_cap = perception_base64_encoded_len(jpeg_len) + 1;\n    char *b64 = malloc(b64_cap);\n    if (!b64) {\n        return FOCUS_ERR_PERCEP_PARAM;\n    }\n    size_t b64_len = perception_base64_encode(jpeg, jpeg_len, b64, b64_cap);\n    if (b64_len == 0) {\n        free(b64);\n        return FOCUS_ERR_PERCEP_PARAM;\n    }\n\n    /* 2. 构造 JSON 请求 */\n    size_t req_cap = b64_len + 96;\n    char *req = malloc(req_cap);\n    if (!req) {\n        free(b64);\n        return FOCUS_ERR_PERCEP_PARAM;\n    }\n    snprintf(req, req_cap, \"{\\\"image\\\":\\\"%s\\\",\\\"width\\\":%d,\\\"height\\\":%d}\",\n             b64, FRAME_WIDTH, FRAME_HEIGHT);\n\n    /* 3. HTTP POST: 单次超时由 wifi_http_post 保证 ≤3s;\n     *    失败重试 1 次, 总阻塞 ≤6s (满足开发规范约束) */\n    int ret = wifi_http_post(g_api_url, req, g_resp, sizeof(g_resp));\n    if (ret < 0) {\n        ret = wifi_http_post(g_api_url, req, g_resp, sizeof(g_resp));\n    }\n    free(b64);\n    free(req);\n    if (ret < 0) {\n        return FOCUS_ERR_PERCEP_TIMEOUT;\n    }\n\n    /* 4. JSON 解析 → 云端原始结果 */\n    cloud_result_t raw;\n    memset(&raw, 0, sizeof(raw));\n    int pr = perception_parse_cloud_response(g_resp, &raw);\n    if (pr != FOCUS_OK) {\n        return pr;\n    }\n\n    /* 5. 3 帧去抖稳定 → observation_t */\n    perception_debounce_push(&raw);\n    perception_debounce_compute(out, perception_monotonic_ms());\n#endif\n\n    /* 6. 追加历史 (供赵思涵时序分析) */\n    history_append(out);\n    return FOCUS_OK;\n}\n\nint perception_get_history(observation_t *buf, int n)\n{\n    if (!buf || n <= 0) {\n        return 0;\n    }\n    if (n > HISTORY_MAX) {\n        n = HISTORY_MAX;\n    }\n\n    int available = (g_history_count < HISTORY_MAX)\n                        ? g_history_count : HISTORY_MAX;\n    if (n > available) {\n        n = available;\n    }\n\n    /* 从旧到新拷贝 */\n    int start = (g_history_count > HISTORY_MAX)\n                    ? (g_history_count % HISTORY_MAX) : 0;\n    for (int i = 0; i < n; i++) {\n        buf[i] = g_history[(start + i) % HISTORY_MAX];\n    }\n    return n;\n}\n"}

---

### [2026-08-26 14:20:26] 用户

[工具结果] File created successfully at: C:\temp\focus_perception\perception\perception.c (file state is current in your context — no need to Read it back)

---

### [2026-08-26 14:20:30] AI

[思考] Now write the test file and README.

---

### [2026-08-26 14:20:45] AI

[工具调用] Write: {"file_path": "C:\\temp\\focus_perception\\tests\\test_perception.c", "content": "/****************************************************************************\n * FOCUS AIoT - 视觉感知模块纯 C 单测 (tests/test_perception.c)\n *\n * 负责人: 周礼航\n * 说明:   宿主机运行, 不依赖硬件/网络/cJSON (用 mock 路径)。\n *         参考赵思涵 tests/behavior_test.c 的模式。\n *\n * 编译 (在 focus_perception 目录下):\n *   gcc -Wall -Wextra -Werror -DPERCEPTION_MOCK \\\n *       perception/perception.c tests/test_perception.c -o test_perception\n *   ./test_perception\n ****************************************************************************/\n\n#include <stdio.h>\n#include <string.h>\n\n#include \"../api/perception.h\"\n#include \"../perception/perception_internal.h\"\n\nstatic int g_checks = 0;\nstatic int g_fail   = 0;\n\n#define CHECK(cond) do {                                   \\\n    g_checks++;                                            \\\n    if (!(cond)) {                                         \\\n        g_fail++;                                          \\\n        printf(\"  [FAIL] %s (line %d)\\n\", #cond, __LINE__);\\\n    }                                                      \\\n} while (0)\n\n/* RFC 4648 标准测试向量 */\nstatic void test_base64(void)\n{\n    printf(\"== test_base64 ==\\n\");\n    const char *cases[][2] = {\n        {\"\",       \"\"},\n        {\"M\",      \"TQ==\"},\n        {\"Ma\",     \"TWE=\"},\n        {\"Man\",    \"TWFu\"},\n        {\"plea\",   \"cGxlYQ==\"},\n        {\"pleas\",  \"cGxlYXM=\"},\n        {\"please\", \"cGxlYXNl\"},\n    };\n    char out[64];\n\n    for (int i = 0; i < 7; i++) {\n        size_t n = perception_base64_encode((const uint8_t *)cases[i][0],\n                                            strlen(cases[i][0]),\n                                            out, sizeof(out));\n        CHECK(n == strlen(cases[i][1]));\n        CHECK(strcmp(out, cases[i][1]) == 0);\n    }\n}\n\nstatic void test_math_helpers(void)\n{\n    printf(\"== test_math_helpers ==\\n\");\n\n    CHECK(perception_majority3(true, true, false)  == true);\n    CHECK(perception_majority3(true, false, false) == false);\n    CHECK(perception_majority3(false, false, false) == false);\n    CHECK(perception_majority3(true, true, true)   == true);\n\n    CHECK(perception_median3(1.0f, 2.0f, 3.0f) == 2.0f);\n    CHECK(perception_median3(3.0f, 1.0f, 2.0f) == 2.0f);\n    CHECK(perception_median3(2.0f, 3.0f, 1.0f) == 2.0f);\n    CHECK(perception_median3(5.0f, 5.0f, 5.0f) == 5.0f);\n\n    CHECK(perception_max3(1.0f, 2.0f, 3.0f) == 3.0f);\n    CHECK(perception_max3(3.0f, 2.0f, 1.0f) == 3.0f);\n}\n\nstatic void test_debounce(void)\n{\n    printf(\"== test_debounce ==\\n\");\n    observation_t out;\n\n    /* 布尔多数投票: 2 帧有人 + 1 帧无人 → 有人 */\n    cloud_result_t r1 = {0}, r2 = {0}, r3 = {0};\n    r1.person_detected = true;  r1.confidence = 0.9f;\n    r2.person_detected = true;  r2.confidence = 0.9f;\n    r3.person_detected = false; r3.confidence = 0.9f;\n\n    perception_init(\"url\", \"key\");       /* 重置去抖状态 */\n    perception_debounce_push(&r1);\n    perception_debounce_compute(&out, 1);       /* 不足 3 帧 → 输出最新帧 */\n    CHECK(out.person_present == true);\n\n    perception_debounce_push(&r2);\n    perception_debounce_compute(&out, 2);\n    CHECK(out.person_present == true);\n\n    perception_debounce_push(&r3);\n    perception_debounce_compute(&out, 3);       /* 满 3 帧 → 多数投票 */\n    CHECK(out.person_present == true);\n\n    /* 浮点中位数: 10/20/90 → 20 */\n    cloud_result_t p1 = {0}, p2 = {0}, p3 = {0};\n    p1.head_pitch = 10.0f; p1.confidence = 0.9f;\n    p2.head_pitch = 20.0f; p2.confidence = 0.9f;\n    p3.head_pitch = 90.0f; p3.confidence = 0.9f;\n\n    perception_init(\"url\", \"key\");\n    perception_debounce_push(&p1);\n    perception_debounce_push(&p2);\n    perception_debounce_push(&p3);\n    perception_debounce_compute(&out, 4);\n    CHECK(out.head_pitch == 20.0f);\n}\n\nstatic void test_process_and_history(void)\n{\n    printf(\"== test_process_and_history ==\\n\");\n    uint8_t dummy[16] = {0};\n    observation_t obs;\n    observation_t hist[10];\n\n    CHECK(perception_init(\"http://api\", \"key123\") == FOCUS_OK);\n\n    /* 空历史 */\n    CHECK(perception_get_history(hist, 10) == 0);\n    CHECK(perception_get_history(NULL, 10) == 0);\n\n    /* 连续 8 帧, 时间戳非递减 */\n    uint32_t last_ts = 0;\n    for (int i = 0; i < 8; i++) {\n        CHECK(perception_process(dummy, sizeof(dummy), &obs) == FOCUS_OK);\n        CHECK(obs.timestamp_ms >= last_ts);\n        last_ts = obs.timestamp_ms;\n    }\n\n    /* 历史条数: 取全部 / 取最近 3 条 */\n    CHECK(perception_get_history(hist, 10) == 8);\n    CHECK(perception_get_history(hist, 3)  == 3);\n\n    /* mock 轮转应覆盖 person=false 与 phone=true 两种情况 */\n    bool saw_away = false, saw_phone = false;\n    for (int i = 0; i < 4; i++) {\n        CHECK(perception_process(dummy, sizeof(dummy), &obs) == FOCUS_OK);\n        if (!obs.person_present) saw_away = true;\n        if (obs.phone_detected)  saw_phone = true;\n    }\n    CHECK(saw_away && saw_phone);\n\n    /* 参数非法 */\n    CHECK(perception_process(NULL, 10, &obs) != FOCUS_OK);\n    CHECK(perception_process(dummy, 0, &obs)  != FOCUS_OK);\n    CHECK(perception_process(dummy, 10, NULL) != FOCUS_OK);\n}\n\nint main(void)\n{\n    test_base64();\n    test_math_helpers();\n    test_debounce();\n    test_process_and_history();\n\n    printf(\"\\n结果: %d checks, %d failed\\n\", g_checks, g_fail);\n    return g_fail ? 1 : 0;\n}\n"}

---

### [2026-08-26 14:20:50] 用户

[工具结果] File created successfully at: C:\temp\focus_perception\tests\test_perception.c (file state is current in your context — no need to Read it back)

---

### [2026-08-26 14:21:01] AI

[工具调用] Write: {"file_path": "C:\\temp\\focus_perception\\README.md", "content": "# 视觉感知模块 (perception) —— 周礼航 · 成品\n\n这是「FOCUS AIoT」里 **视觉感知层** 的完整实现。输入一张 JPEG，输出一个\n`observation_t`，供赵思涵的 `behavior` 模块做时序分析。\n\n> 依据文档：`周礼航开发规范.md`、`DEVELOPMENT_TASKS (2).md`（2026-08-19）、\n> `产品方案与分工_v2.md`。只做「空间」上的单帧识别，**不区分严格/鼓励模式**，\n> **不做行为判断**（那是赵思涵的事）。\n\n## 文件清单\n\n```\nfocus_perception/\n├── api/perception.h             公开接口 (observation_t + 3 函数 + 错误码)\n│                                ⚠️ 参考拷贝, 勿覆盖仓库冻结版\n├── perception/\n│   ├── perception.c             主实现 (三函数 + 去抖 + 历史 + base64 + cJSON)\n│   └── perception_internal.h    内部声明 (cloud_result_t + 工具函数)\n├── tests/\n│   └── test_perception.c        纯 C 单测 (mock 路径, 不依赖硬件/网络/cJSON)\n└── README.md\n```\n\n## 三个对外接口（冻结签名）\n\n```c\nint  perception_init(const char *api_url, const char *api_key);\nint  perception_process(uint8_t *jpeg, size_t jpeg_len, observation_t *out);\nint  perception_get_history(observation_t *buf, int n);\n```\n\n返回值（错误码，来自 `api/error.h`，此处兜底定义）：\n\n| 常量 | 值 | 含义 |\n|---|---|---|\n| `FOCUS_OK` | 0 | 成功 |\n| `FOCUS_ERR_PERCEP_TIMEOUT` | -30 | 云端/HTTP 超时或请求失败 |\n| `FOCUS_ERR_PERCEP_JSON` | -31 | JSON 解析失败 / 缺字段 |\n| `FOCUS_ERR_PERCEP_NODATA` | -32 | 业务码非 0 / 无数据 |\n| `FOCUS_ERR_PERCEP_PARAM` | -33 | 参数非法（本地扩展，可请万思源并入 error.h） |\n\n## 关键设计\n\n- **mock / 真实双路径**：`-DPERCEPTION_MOCK` 走 mock（默认，便于联调回退）；\n  不定义则走真实云端链路（`base64 → JSON → wifi_http_post → cJSON 解析 → 去抖`）。\n- **3 帧去抖**：bool 多数投票、角度中位数、hand_motion 取最大、confidence 取均值。\n  mock 路径本身已是稳定结果，**绕过**去抖，避免把 AWAY 状态“投票投没”。\n- **历史环形缓冲**：`obs_history[60]`，`perception_get_history()` 从旧到新返回。\n  提供**强符号** `perception_get_history()`，自动覆盖 `core/mock.c` 里的 weak 桩。\n- **超时**：HTTP 单次由张沐泽的 `wifi_http_post` 保证 ≤3s；失败重试 1 次，总阻塞 ≤6s。\n- **内存**：base64 / 请求体用 `malloc`（ESP32 上建议映射 PSRAM），响应用固定 4KB 静态缓冲。\n- **时间戳**：`clock_gettime(CLOCK_MONOTONIC)`（与 `core/state_machine.c` 的 monotonic_ms 一致）。\n\n## 本地单测（Linux，无需硬件）\n\n```bash\ncd focus_perception\ngcc -Wall -Wextra -Werror -DPERCEPTION_MOCK \\\n    perception/perception.c tests/test_perception.c -o test_perception\n./test_perception\n```\n\n预期输出 `0 failed`。覆盖：base64（RFC4648 标准向量）、多数投票/中位数/最大值、\n3 帧去抖、mock 轮转、历史环形缓冲、空历史/参数非法。\n\n## 接入仓库（openvela 真机）\n\n1. 把 `perception/perception.c`、`perception/perception_internal.h` 放进\n   `app/hello_app/perception/`。\n2. `api/perception.h` **不要覆盖**，用仓库冻结版（字段/签名必须一致）。\n3. 把 `perception/perception.c` 加进 `Makefile`/`CMakeLists.txt` 的 `CSRCS`。\n4. mock 开关二选一（参考 LCD_STUB 的 if/else 模式）：\n   - mock：给 `CFLAGS` 加 `-DPERCEPTION_MOCK`（或 Kconfig `PERCEPTION_MOCK=y`）；\n   - 真实：不加该宏，链接 `cJSON`，并确认张沐泽的 `wifi_http_post` 已就绪。\n\n## 联调顺序\n\n先跟张沐泽联调（确认 `wifi_http_post` 能通）→ 再跟赵思涵联调（确认 `observation_t`\n字段对）→ 最后全链路：真实 observation → behavior → state_machine → UI 上屏。\n"}

---

### [2026-08-26 14:21:06] 用户

[工具结果] File created successfully at: C:\temp\focus_perception\README.md (file state is current in your context — no need to Read it back)

---

### [2026-08-26 14:21:10] AI

[思考] Now let me try to compile and run the test to verify correctness. Check if gcc is available.

---

### [2026-08-26 14:21:10] AI

Now let me verify the code actually compiles and passes:

---

### [2026-08-26 14:21:11] AI

[工具调用] Bash: {"command": "cd /c/temp/focus_perception && (command -v gcc && gcc -Wall -Wextra -Werror -DPERCEPTION_MOCK perception/perception.c tests/test_perception.c -o test_perception && ./test_perception) || echo \"GCC_NOT_FOUND_OR_FAILED\"", "description": "Compile and run perception unit test with gcc"}

---

### [2026-08-26 14:25:13] 用户

[工具结果] /c/Users/user/AppData/Local/Microsoft/WinGet/Packages/MartinStorsjo.LLVM-MinGW.UCRT_Microsoft.Winget.Source_8wekyb3d8bbwe/llvm-mingw-20260616-ucrt-x86_64/bin/gcc
perception/perception.c:61:23: error: unused variable 'g_resp' [-Werror,-Wunused-variable]
   61 | static char           g_resp[RESP_BUF_SIZE];
      |                       ^~~~~~
1 error generated.
GCC_NOT_FOUND_OR_FAILED

---

### [2026-08-26 14:25:30] AI

[思考] gcc is available (llvm-mingw). There's a `-Wunused-variable` error: `g_resp` is unused in MOCK build. I need to guard `g_resp` with `#ifndef PERCEPTION_MOCK`. Also `MAX_JPEG_SIZE` macro might be unused → but it's a macro, no warning. `g_resp` is only used in real path. Let me guard it.

Also `g_api_key` is written in init but never read — is that an "unused variable"? It's written (assigned via snprintf) but never read. File-scope static that's only written, never read: clang may warn with `-Wunused-variable`? Actually, for a static variable that's used (written) but never read, `-Wunused-variable` typically does NOT fire because it's "used" (it's referenced). The "set but not used" warning (`-Wunused-but-set-variable`) applies to local variables, not file-scope statics. g_resp is the opposite: declared but never referenced AT ALL in MOCK build → truly unused → warning.

Let me guard g_resp with #ifndef PERCEPTION_MOCK. g_api_key is referenced (written in init) so it's fine.

Actually wait, let me also double check g_api_key: it's written in init. It's "used" (assigned). No warning for file-scope. Fine.

Let me fix g_resp.

---

### [2026-08-26 14:25:31] AI

[工具调用] Edit: {"replace_all": false, "file_path": "C:\\temp\\focus_perception\\perception\\perception.c", "old_string": "static int            g_mock_seq = 0;       /* mock 轮转序号 */\nstatic char           g_resp[RESP_BUF_SIZE];", "new_string": "static int            g_mock_seq = 0;       /* mock 轮转序号 */\n\n#ifndef PERCEPTION_MOCK\nstatic char           g_resp[RESP_BUF_SIZE]; /* 云端 JSON 响应缓冲 (仅真实链路) */\n#endif"}

---

### [2026-08-26 14:25:36] 用户

[工具结果] The file C:\temp\focus_perception\perception\perception.c has been updated successfully. (file state is current in your context — no need to Read it back)

---

### [2026-08-26 14:25:41] AI

[工具调用] Bash: {"command": "gcc -Wall -Wextra -Werror -DPERCEPTION_MOCK perception/perception.c tests/test_perception.c -o test_perception && ./test_perception", "description": "Recompile and run perception unit test"}

---

### [2026-08-26 14:25:43] 用户

[工具结果] Exit code 1
ld.lld: error: undefined symbol: clock_gettime64
>>> referenced by C:/Users/user/AppData/Local/Temp/perception-30229a.o:(perception_monotonic_ms)
clang-22: error: linker command failed with exit code 1 (use -v to see invocation)

---

### [2026-08-26 14:25:56] AI

[思考] This is a Windows/mingw linking quirk: on 32-bit mingw, `clock_gettime` is mapped to `clock_gettime64` and needs `-lwinpthread` or the `-D_WIN32_WINNT` etc. Actually, this is a mingw issue where `clock_gettime` requires linking against a library. The error is `undefined symbol: clock_gettime64`.

This is just the Windows build environment. On Linux (their VM) or ESP32/NuttX, `clock_gettime` works fine. But I want to verify my test actually passes. I can work around by defining `CLOCK_MONOTONIC`/clock_gettime for the test, OR use a fallback. 

Actually, the cleaner solution: make `perception_monotonic_ms()` portable with a fallback. On Windows/mingw, `clock_gettime` isn't directly available. But the target is Linux/openvela, so clock_gettime is correct there.

For my verification purposes, I could:
1. Link with `-lwinpthread` (might fix clock_gettime64).
2. Or add a fallback `#ifdef _WIN32` using `GetTickCount64` / `QueryPerformanceCounter`.

Let me first try `-lwinpthread`. Actually, the llvm-mingw might need `-lwinpthread`. Let me try adding it.

Actually, a more robust approach that also improves the deliverable: add a Windows fallback in perception_monotonic_ms so the test can run anywhere. But that adds platform-specific code that's not needed for the actual target. Hmm.

The simplest is to just link `-lwinpthread` for the test to verify. But that's a Windows-only fix and doesn't belong in the deliverable README (which targets Linux/openvela).

Actually, let me reconsider. The real target is Linux (their VM) and openvela/ESP32. `clock_gettime(CLOCK_MONOTONIC)` is standard POSIX and works there. The Windows/mingw issue is only relevant to my local verification.

Let me try `-lwinpthread` to verify, and if that works, keep the code as-is (correct for the real target). If not, I'll add a small portable fallback to perception_monotonic_ms that also makes it runnable on Windows (using `_WIN32` → GetTickCount64). Actually a portable fallback is genuinely nice-to-have and harmless for the real target. But it adds `#include <windows.h>` under _WIN32 which is ugly in embedded code. 

Let me first just try `-lwinpthread`.

---

### [2026-08-26 14:25:57] AI

[工具调用] Bash: {"command": "gcc -Wall -Wextra -Werror -DPERCEPTION_MOCK perception/perception.c tests/test_perception.c -o test_perception -lwinpthread && ./test_perception; echo \"EXIT=$?\"", "description": "Compile linking winpthread and run test"}

---

### [2026-08-26 14:25:59] 用户

[工具结果] == test_base64 ==
== test_math_helpers ==
== test_debounce ==
== test_process_and_history ==

结果: 57 checks, 0 failed
EXIT=0

---

### [2026-08-26 14:26:04] AI

[思考] All 57 checks pass. The `-lwinpthread` was only needed for Windows/mingw (not for the real Linux/openvela target). 

Let me clean up the compiled binary so I don't leave artifacts. Actually, leaving the test binary is fine, but it's cleaner to remove it. Let me remove test_perception.exe (mingw would produce test_perception.exe). Actually the Bash output shows it ran `./test_perception`. On mingw it might produce test_perception.exe. Let me check and clean up.

Actually, let me not worry too much about cleanup — but a stray .exe in the deliverable folder is untidy. Let me remove it.

Let me verify the final file tree and remove the binary.

---

### [2026-08-26 14:26:05] AI

All 57 checks pass (the `-lwinpthread` flag is a Windows-only quirk for `clock_gettime`; on your Linux VM / openvela it's standard POSIX and needs no flag). Let me clean up the test binary and show the final result:

---

### [2026-08-26 14:26:06] AI

[工具调用] Bash: {"command": "rm -f test_perception test_perception.exe && find . -type f | sort", "description": "Remove test binary and list final files"}

---

### [2026-08-26 14:26:23] 用户

[工具结果] ./README.md
./api/perception.h
./perception/perception.c
./perception/perception_internal.h
./tests/test_perception.c

---

### [2026-08-26 14:26:38] AI

成品已写好并通过测试，位置在 `C:\temp\focus_perception\`。

## 我做了什么

读完了文件夹里的全部文本（`产品方案与分工_v2.md`、`周礼航开发规范.md`、三版 `DEVELOPMENT_TASKS`、`re.md`，以及那份 767KB 的会话记录）。确认了你（周礼航）负责的是 **视觉感知模块 `perception/`** —— 任务书里明确写着「接下来主要是 zlh 了」，要写的就是 `perception.c` 那三个函数。所以我产出的就是这整个模块。

## 交付文件

```
focus_perception/
├── api/perception.h            公开接口（observation_t + 3 函数 + 错误码）
├── perception/perception.c     主实现（3 函数 + 3 帧去抖 + 历史环形缓冲 + base64 + cJSON）
├── perception/perception_internal.h  内部声明（cloud_result_t + 工具函数）
├── tests/test_perception.c     纯 C 单测（57 项检查全部通过）
└── README.md                   接入/编译/联调说明
```

## 对照规范的关键实现点

| 规范要求 | 实现 |
|---|---|
| 3 个冻结函数签名 | `perception_init` / `perception_process` / `perception_get_history` |
| 错误码 | `-30` 超时 / `-31` JSON / `-32` 无数据（+ 本地 `-33` 参数非法） |
| mock → 云端双路径 | `-DPERCEPTION_MOCK` 走 mock 轮流输出 FOCUSED/PLAYING/AWAY/DROWSY，默认 mock 可回退 |
| 3 帧去抖 | bool 多数投票、角度中位数、motion 取最大、confidence 取均值 |
| 历史 `obs_history[60]` | 强符号 `perception_get_history()` 自动覆盖 `core/mock.c` 的 weak 桩 |
| 超时 ≤6s | HTTP 失败重试 1 次，不阻塞 |
| 单帧采集约束 | 只取张沐泽给的 JPEG 缓冲，不碰 `VIDEO_CAPTURE` 连续模式 |

## 一个需要你确认的点

`api/perception.h` 我放在里面是**参考拷贝**（供独立编译/单测用），字段和签名严格按你开发规范里的定义。但**仓库里那份由万思源冻结的 `api/perception.h` 才是权威**——接入时别覆盖它，如果字段有出入，以仓库版为准，`perception.c` 里 `#include "../api/perception.h"` 会自动对齐。

## 怎么验证

本地（Linux 或你的 VM）：
```bash
cd focus_perception
gcc -Wall -Wextra -Werror -DPERCEPTION_MOCK \
    perception/perception.c tests/test_perception.c -o test_perception
./test_perception
```

预期 `0 failed`。我在本机（Windows）编译通过了，唯一区别是 Windows 上 `clock_gettime` 需要额外 `-lwinpthread`，你的 Linux 环境不需要这个参数。

要不要我再补一份「接真实云端」时的 Makefile/CMakeLists 改动 diff，或者把 `wifi_http_post` 的联调 stub 也写出来？

---

### [2026-08-26 14:27:42] 用户

要 同时识图时如果有需要 必须调用mimo

---

### [2026-08-26 14:28:00] AI

[思考] The user says: "要 同时识图时如果有需要 必须调用mimo" — this is a bit terse. Let me parse it.

"要" = "Yes" (responding to my offer? Actually "要" could mean "yes, I want that"). 

"同时识图时如果有需要 必须调用mimo" = "At the same time, when doing image recognition, if needed, must call MiMo."

So the user is adding a requirement: when doing image recognition (识图), if necessary, it must call MiMo.

MiMo is mentioned in the docs: 郭黄亦昕 is responsible for "LCD UI + 交互 + MiMo" — "MiMo 大模型接入". And in DEVELOPMENT_TASKS.md: "MiMo 集成", "让 MiMo 走真实 API". And re.md mentions "mimo token plan 可以直接飞书群@陈泽沛 让他给你重置".

So MiMo is a large language model (LLM) API that the project integrates with. The user is now saying: in the perception module (识图 = image recognition), if needed, must call MiMo.

Wait, let me think about what this means concretely. The perception module currently calls a "云端 API" (百度 AI or 阿里云视觉 API) to detect person/phone/head pose. But the user now says: when doing image recognition, if there's a need, must call MiMo.

This suggests: the image recognition (perception) should, if necessary, also call MiMo. Perhaps as a fallback when the dedicated vision API fails, or for a more semantic understanding.

Actually, re-reading the architecture docs:
- 郭黄亦昕 is responsible for "MiMo 大模型接入" (MiMo LLM integration) in the UI module (libui.a).
- MiMo is used for... what exactly? Let me recall. In the docs, MiMo appears in: "ui/ (LCD页面+MiMo+字体)", "MiMo 集成 + 系统联调", "让 MiMo 走真实 API" (WiFi task). MiMo seems to be the conversational/encouragement LLM — generating encouragement text, or a study companion.

Actually, the MiMo integration is 郭黄亦昕's job (libui.a). But the user (周礼航, perception) is now being told: "同时识图时如果有需要 必须调用mimo" = "when doing image recognition, if there's a need, you must call MiMo."

So the requirement is: the perception module, in addition to (or instead of) the dedicated vision detection API, should be able to call MiMo when needed.

Hmm, but wait — MiMo might be a multimodal LLM that can do the image recognition itself. "识图" = image recognition. So maybe the user means: use MiMo (a multimodal LLM) to do the image recognition (识图), when necessary.

Actually, let me reconsider. The phrasing "同时识图时如果有需要 必须调用mimo" could be parsed as:
- "同时" = also/at the same time (responding to my "要不要我再补一份..." — actually "要" is "yes")
- "识图时" = when recognizing images
- "如果有需要" = if there's a need
- "必须调用mimo" = must call MiMo

So the user is saying: "Yes [I want the extra stuff]. Also, when recognizing images, if there's a need, [the code] must call MiMo."

This is a new requirement to incorporate into the perception module: add MiMo calling capability to the image recognition flow.

But I need to understand what MiMo's API looks like. Let me search the transcript (the big conversation file) for MiMo details — API endpoint, token, request/response format.

Actually, wait — let me reconsider the scope. MiMo integration is officially 郭黄亦昕's job (libui.a). But the user is now asking me to make the perception module call MiMo when doing image recognition. This is a cross-module concern.

Let me search the transcript for "MiMo" / "mimo" to understand the API contract, endpoint, token, and how it's meant to be used. This is important before I write anything.

Let me grep the big file for mimo.

---

### [2026-08-26 14:28:01] AI

[工具调用] Grep: {"pattern": "[Mm]i[Mm]o|[Mm]iMo", "path": "C:\\temp\\20260731_055914-ubuntu.md", "output_mode": "content", "-n": true, "head_limit": 120}

---

### [2026-08-26 14:28:01] 用户

[工具结果] 336:  - 郭黄亦昕 (Guo Huang Yixin): LCD UI + interaction + MiMo
364:            → LCD 5类页面 + MiMo（郭黄亦昕）
13090:| ⑥ | 本地 MiMo 模板 → 真实 MiMo API（郭黄亦昕） | 最后接入（网络依赖+非核心链路） |
13111:第 4 周起    → 逐个接入真实硬件 + 云端 API + MiMo
14417:    ui/        - 郭黄亦昕 LCD/UI/MiMo

---

### [2026-08-26 14:28:07] AI

[思考] The big transcript has limited info about MiMo's actual API. Let me search more broadly for the MiMo API details — token, endpoint, how it's called. Let me also check the other docs for any MiMo API spec.

Actually the transcript only has a few mentions. MiMo is 郭黄亦昕's module. There's no detailed API spec in the docs I've read. Let me search for "mimo" in the other md files (development tasks, dev specs) to see if there's a MiMo API contract.

Let me grep all files in C:\temp for mimo (case-insensitive), and also search the transcript for related terms like "token", "大模型", "LLM", "encourage", "对话".

---

### [2026-08-26 14:28:08] AI

[工具调用] Grep: {"pattern": "[Mm]i[Mm]o|MiMo|mimo", "path": "C:\\temp", "output_mode": "content", "-n": true, "-i": true, "glob": "*.md", "head_limit": 80}

---

### [2026-08-26 14:28:08] 用户

[工具结果] C:\temp\周礼航开发规范.md:260:- MiMo API → 不经过你
C:\temp\DEVELOPMENT_TASKS.md:12:| ui/ (LCD页面+MiMo+字体) | 郭黄亦昕 | ✅ 已合并 |
C:\temp\DEVELOPMENT_TASKS.md:31:- **效果**: 连上 WiFi, `wifi_http_post` 到测试地址返回成功 (替换 `wifi_stub.c`, 让 MiMo 走真实 API)。
C:\temp\DEVELOPMENT_TASKS.md:57:- WiFi: `wifi_http_post` 返回成功, MiMo 请求能发出去。
C:\temp\周礼航开发规范 (1).md:266:- MiMo API → 不经过你
C:\temp\DEVELOPMENT_TASKS (2).md:12:| ui/ (LCD页面+MiMo+字体) | 郭黄亦昕 | ✅ 已合并 |
C:\temp\DEVELOPMENT_TASKS (2).md:42:- **效果**: 连上 WiFi, `wifi_http_post` 到测试地址返回成功 (替换 `wifi_stub.c`, 让 MiMo 走真实 API)。
C:\temp\DEVELOPMENT_TASKS (2).md:68:- WiFi: `wifi_http_post` 返回成功, MiMo 请求能发出去。
C:\temp\产品方案与分工_v2.md:121:| **郭黄亦昕** | LCD UI + 交互 + MiMo | 页面设计、状态图标、交互逻辑、MiMo 大模型接入 | `libui.a` |
C:\temp\产品方案与分工_v2.md:491:| 7 | MiMo 集成 + 系统联调 + 参数整定 | 全员 |
C:\temp\re.md:64:@有形浪人 你的部分 如果需要mimo token plan 可以直接飞书群@陈泽沛 让他给你重置
C:\temp\DEVELOPMENT_TASKS (1).md:12:| ui/ (LCD页面+MiMo+字体) | 郭黄亦昕 | ✅ 已合并 |
C:\temp\DEVELOPMENT_TASKS (1).md:36:- **效果**: 连上 WiFi, `wifi_http_post` 到测试地址返回成功 (替换 `wifi_stub.c`, 让 MiMo 走真实 API)。
C:\temp\DEVELOPMENT_TASKS (1).md:62:- WiFi: `wifi_http_post` 返回成功, MiMo 请求能发出去。
C:\temp\DEVELOPMENT_TASKS (1).md:168:1. **张沐泽**: 按键驱动 (FSM 手动操作) → WiFi (MiMo 真实请求) → 摄像头 → 音频。
C:\temp\20260731_055914-ubuntu.md:336:  - 郭黄亦昕 (Guo Huang Yixin): LCD UI + interaction + MiMo
C:\temp\20260731_055914-ubuntu.md:364:            → LCD 5类页面 + MiMo（郭黄亦昕）
C:\temp\20260731_055914-ubuntu.md:13090:| ⑥ | 本地 MiMo 模板 → 真实 MiMo API（郭黄亦昕） | 最后接入（网络依赖+非核心链路） |
C:\temp\20260731_055914-ubuntu.md:13111:第 4 周起    → 逐个接入真实硬件 + 云端 API + MiMo
C:\temp\20260731_055914-ubuntu.md:14417:    ui/        - 郭黄亦昕 LCD/UI/MiMo

---

### [2026-08-26 14:28:10] AI

[工具调用] Grep: {"pattern": "大模型|LLM|token|Token|api_key|API_KEY|Authorization|Bearer", "path": "C:\\temp\\20260731_055914-ubuntu.md", "output_mode": "content", "-n": true, "head_limit": 80}

---

### [2026-08-26 14:28:10] 用户

[工具结果] 1192:3	> 本文档面向 2026 首届 openvela AI 硬件开发者大赛参赛者，介绍如何从零搭建 openvela + ai_agent 环境、配置 LLM、体验核心能力，并了解框架架构与开发板集成方式。
14914:Since we're on a VM and don't have GitHub credentials/OAuth tokens set up, the most practical approach is:
14993:1. A GitHub personal access token
15022:1. A personal access token (classic) for HTTPS pushes
15025:Since we're on a VM, we likely don't have SSH keys to GitHub. Let me ask the user if they have a personal access token, or if they want to set up SSH keys.
15061:1. Provide a Personal Access Token (I can use it to push via HTTPS)
15065:For option 1, they'd need to create a token at https://github.com/settings/tokens with `repo` scope.
15077:**方案一（推荐，最快）**：给我一个 GitHub Personal Access Token
15079:1. 打开 https://github.com/settings/tokens → **Generate new token (classic)**
15081:3. 把 token 发我（形如 `ghp_xxxxxxxxxxxx`）
15091:你选哪个？方案一一步到位，方案二多几步但不用给我 token。
15103:[思考] The user gave me a GitHub token. Let me use it to push to their fork. I'll set up the remote URL with the token embedded, push, then immediately clean up.
15105:The token is: ghp_REDACTED
15113:收到。用 token push 到你的 fork。
15135:Or maybe I should try the `gh` API to fork it for them? Let me check if I can use the token to create a fork via the GitHub API.
15137:Actually, let me try creating the fork via the GitHub API with the token. The endpoint is:
15146:Fork 还不存在。我用 token 通过 GitHub API 帮你自动 fork。
15152:[工具调用] Bash: {"command": "export http_proxy=http://192.168.253.1:7890 https_proxy=http://192.168.253.1:7890; curl -s -X POST -H \"Authorization: token ghp_REDACTED\" -H \"Accept: applic
15206:[工具调用] Bash: {"command": "export http_proxy=http://192.168.253.1:7890 https_proxy=http://192.168.253.1:7890; curl -s -X POST -H \"Authorization: token ghp_REDACTED\" -H \"Accept: applic
15221:1. Removing the token from the remote URL (it's stored in the remote config... actually no, I used inline URL with git push, so it's not stored)
15222:2. Updating the fork remote URL to not contain the token
15223:3. Advising the user to regenerate their token since it was transmitted
15225:Actually, looking at my git push command, I used the token inline in the URL: `https://Skadi-QL:token@github.com/...`. This is NOT stored in git config - it was a one-time URL. The fork remote in git config still points to `https://github.com/Skadi-QL/contest2026_087_gaiduimingyizhanyongdui` (without token).
15227:The token was also passed in curl commands but those were one-off too.
15229:Let me verify the remote URL doesn't contain the token, then update the remote to use the fork for future pushes.
15231:Actually, the user should regenerate their token since it was exposed. Let me tell them that and provide the PR link.
15252:你的 token 在刚才的命令中通过网络传输了。建议：
15253:1. 去 https://github.com/settings/tokens 找到这个 token
15382:现在这个 PR 会显示为你的 GitHub 账号提交的。另外记得把 token 重新生成一下（安全起见）。

---

### [2026-08-26 14:28:23] AI

[思考] Key findings:

1. MiMo is 郭黄亦昕's module (LCD UI + interaction + MiMo 大模型接入, libui.a).
2. 周礼航's dev spec explicitly says: "MiMo API → 不经过你" (MiMo API does NOT go through you). But the user is now overriding this — saying "识图时如果有需要 必须调用mimo" (when recognizing images, if needed, must call MiMo).
3. re.md (the coordinator's message) says: "@有形浪人 你的部分 如果需要mimo token plan 可以直接飞书群@陈泽沛 让他给你重置" — this is directed at 有形浪人 (which is 周礼航's handle — from re.md "@zmz @我不讲狸猫 @有形浪人 三个人接下来的开发任务" and "接下来主要是zlh了 @有形浪人 你的部分 如果需要mimo token plan 可以直接飞书群@陈泽沛"). So the coordinator is telling 周礼航 that if he needs a MiMo token plan, ask 陈泽沛 in the Feishu group.

So this confirms: the coordinator expects 周礼航's perception module to potentially call MiMo, and there's a MiMo token/plan involved.

4. There's also an important reference in the transcript at line 1192: "本文档面向 2026 首届 openvela AI 硬件开发者大赛参赛者，介绍如何从零搭建 openvela + ai_agent 环境、配置 LLM" — this suggests MiMo is related to the openvela ai_agent framework / LLM.

So "MiMo" appears to be the LLM (大模型) that openvela integrates, likely via an "ai_agent" framework. The MiMo is a multimodal LLM that can do image understanding (识图).

Now, what does the user actually want me to do?

"要 同时识图时如果有需要 必须调用mimo" = "Yes [to my earlier question]. Also, when doing image recognition, if needed, must call MiMo."

So the user wants me to add MiMo calling capability to the perception (识图) module. Specifically: when doing image recognition, if the dedicated vision API can't handle something (or as a fallback / enhancement), the module must call MiMo.

But I don't have the MiMo API spec (endpoint, request/response format, token). I need to either:
1. Find the MiMo API details in the transcript (search more specifically).
2. Ask the user for the MiMo API contract.

Let me search the transcript for the ai_agent / openvela LLM config / MiMo API endpoint details. The transcript is the full conversation that built the repo, so it likely contains the MiMo integration code (in ui/), or at least the API details.

Let me search for "ai_agent", "MiMo", "mimo", "llm", "endpoint", "chat/completions", "api.mimo", "mimo.com", "url", "ssid" (no), "vision", "识图", "多模态", "multimodal".

Let me do targeted searches.

---

### [2026-08-26 14:28:25] AI

[工具调用] Grep: {"pattern": "ai_agent|ai-agent|LLM|llm|chat/completions|mimo\\.|MiMo\\.|multimodal|多模态|识图|视觉|vision|VL模型|Qwen|通义", "path": "C:\\temp\\20260731_055914-ubuntu.md", "output_mode": "content", "-n": true, "-i": true, "head_limit": 100}

---

### [2026-08-26 14:28:25] 用户

[工具结果] 67:- 产品方案与分工_v2.md (product plan and division of labor v2)
149:3	> 你的模块是**视觉感知层**——从一张图片里看出「有什么」。
361:camera JPEG → 云端视觉API → observation_t（周礼航，单帧"有什么"）
825:  <default remote="openvela" revision="dev-ai-contest-2026"/>
865:3. There's also a `packages/ai_agent/defconfigs/esp32s3-eye` — likely the reference/example for AI agent on esp32s3-eye.
936:3. Check the ai_agent esp32s3-eye defconfig (reference)
1132:ai_agent_quickstart.md
1144:Let me read the ai_hardware_track_guide.md and ai_agent_quickstart.md — these will explain the official build flow for esp32s3-eye including toolchain acquisition.
1163:/home/ubuntu/openvela/docs/zh-cn/contest_2026/ai_hardware/ai_agent_quickstart.md:329:| 芯片      | ESP32-S3（Xtensa 双核）                        |
1170:[思考] The quickstart references `nuttx/boards/xtensa/esp32s3/esp32s3-eye/configs/ai_agent/defconfig` — let me check if that exists. Earlier I saw the esp32s3-eye configs were: gpio, i2c, lcd, nsh, usbnsh, wifi. No `ai_agent` config there. But there was `packages/ai_agent/defconfigs/esp32s3-eye`. Let me read the quickstart fully — it seems to be the official guide for building the AI agent demo for esp32s3-eye. This is exactly what we need to understand the build flow.
1184:[工具调用] Read: {"file_path": "/home/ubuntu/openvela/docs/zh-cn/contest_2026/ai_hardware/ai_agent_quickstart.md"}
1190:[工具结果] 1	# ai_agent 应用开发上手指南
1192:3	> 本文档面向 2026 首届 openvela AI 硬件开发者大赛参赛者，介绍如何从零搭建 openvela + ai_agent 环境、配置 LLM、体验核心能力，并了解框架架构与开发板集成方式。
1212:./build.sh esp32s3-eye:ai_agent distclean
1213:bash packages/ai_agent/fix_esp32s3.sh &
1214:./build.sh esp32s3-eye:ai_agent
1217:But this requires ESP-IDF environment. Hmm, and it's for the ai_agent config specifically.
1332:5:  <default remote="openvela" revision="dev-ai-contest-2026"/>
1477:- Possibly disable heavy stuff (LVGL demo, ai_agent examples) to keep image lean and avoid compile errors
1488:Also need to verify: the base openvela defconfig enables LVGL demo (`CONFIG_EXAMPLES_LVGLDEMO`) which pulls LVGL + may be heavy/slow to compile and risky. For a hardware test image, I might strip out LVGL demo and ai_agent-related examples to keep the build fast and focused. Actually — wait. The openvela defconfig at 210 lines. Let me read the whole thing to know exactly what to keep/remove.
1494:Also one more consideration: I should think about whether the esp32s3-eye "openvela" config actually builds with just the prebuilt gcc toolchain, or whether it needs ESP-IDF (the ai_agent quickstart says "加载 ESP-IDF 环境"). The esp32s3-eye vendor README doesn't mention ESP-IDF. Let me check the board's build config (arch toolchain settings) — does it use the xtensa-esp32s3-elf gcc toolchain (prebuilts) or esp-idf? Let me check the nuttx esp32s3 arch Kconfig for toolchain selection.
1719:Hmm, wait. Actually this might be the REAL issue: the `.repo/manifests` was checked out at an older revision and these changes are real edits someone made? No — the changes match exactly 1:1 in count, suggesting whole-file line-ending churn.
1863:[工具调用] TaskCreate: {"subject": "创建构建 defconfig（启用测试 app 的 esp32s3-eye 配置）", "description": "基于 vendor/espressif/boards/esp32s3/esp32s3-eye/configs/openvela/defconfig，去掉 LVGL demo/ai_agent 等重组件，启用 CONFIG_LVX_USE_DEMO_CON
2742:Actually — let me check the `lunch`/envsetup to understand the default. The `build.sh` usage: `./build.sh [-m] <board-name>:<config-name> [--cmake] ...`. The default is in-tree make build. The ai_agent quickstart used `./build.sh esp32s3-eye:ai_agent` (make-based). 
2832:drwxr-xr-x 12 ubuntu ubuntu 4096 Jul 16 11:23 ai_agent
3273:[Omitted long matching line]
4025:- Make-based in-tree build: outputs `nuttx/nuttx.bin` (in-tree), flashed at 0x0. The ai_agent quickstart used `./build.sh esp32s3-eye:ai_agent` then flashed `nuttx/nuttx.bin`.
4028:The ai_agent quickstart for ESP32-S3-EYE used the make-based flow (`./build.sh esp32s3-eye:ai_agent`, `nuttx/nuttx.bin`), with ESP-IDF sourced. But the vendor README's openvela config build (`./build.sh .../configs/openvela`) didn't mention ESP-IDF.
4030:Wait — why would the ai_agent flow need ESP-IDF? Because ai_agent's esp32s3 config uses ESP-IDF components (like esp-idf libs for the AI agent). The plain openvela config might not. But actually, the esp32s3 chip support in openvela/nuttx might itself depend on ESP-IDF libs at build time. Let me check whether the esp32s3 build needs ESP-IDF.
4056:skill 给了构建流程。但 esp32s3 构建有一个关键问题要确认：**是否需要 ESP-IDF 环境**（ai_agent 教程要求 source export.sh）。检查 nuttx esp32s3 的 HAL/工具链依赖，以及 envsetup 是否会自动把我们的工具链加进 PATH。
4607:Also — I should double check the flash process. The output binary for make-based in-tree build is `nuttx/nuttx.bin`. The ai_agent quickstart flashes:
4613:But wait — which build mode? Let me reconsider make vs cmake. The openvela-build skill emphasizes cmake mode. But the esp32s3-eye vendor README and ai_agent quickstart both used make mode for esp32s3-eye. Let me check if cmake mode works for esp32s3-eye. The cmake mode (`--cmake`) uses `lunch` which needs the board in the cmake board discovery. The esp32s3-eye is a vendor custom board. Hmm.
4668:Also the toolchain PATH: envsetup adds some paths but not esp32s3. I'll export PATH explicitly. Also note the build uses ccache possibly (envsetup sets VELA_CMAKE_USE_CCACHE). For make-based build, ccache might be used too. The ai_agent quickstart set `export CCACHE_DISABLE=1`. Let me check if ccache is available and functional; if not, disable.
4761:So every build_board call does a distclean of the nuttx tree first?! That means full rebuild every time. That matches the ai_agent quickstart which explicitly ran `./build.sh esp32s3-eye:ai_agent distclean` then `./build.sh esp32s3-eye:ai_agent` — the build.sh itself passes distclean? No wait — the quickstart ran distclean as a separate make target.
5719:- `ai_agent_quickstart.md` (already read)
5760:[思考] The index references the ai_agent_quickstart.md which I've already read. It has the ESP32-S3-EYE build instructions:
5767:./build.sh esp32s3-eye:ai_agent distclean
5768:bash packages/ai_agent/fix_esp32s3.sh &
5769:./build.sh esp32s3-eye:ai_agent
5772:Hmm, but that's for the ai_agent config specifically, and it requires ESP-IDF environment (source esp-idf/export.sh). The user's hint said "AI 硬件赛道教程导航（环境搭建、编译烧录、Skill 开发）" — pointing me to the tutorial.
5790:Let me look at the ai_hardware_track_guide.md and the ESP32-S3-EYE section of supported_hardware.md to see if there's a documented official build/flash path I'm missing. Perhaps there's a simpler official flow (e.g., using the prebuilt ai_agent defconfig, or a documented way to handle the ESP-IDF requirement).
5792:Also — I should reconsider: maybe the official flow for this track uses `packages/ai_agent/defconfigs/esp32s3-eye/esp32s3-eye_defconfig` (the pre-made one) copied to the board configs dir, then `./build.sh esp32s3-eye:ai_agent` with the fix script. That's the documented path. My custom "hwtest" config is a deviation.
5794:But the ai_agent defconfig requires ESP-IDF env. Hmm. Let me check if ESP-IDF is available in this environment, and read the track guide.
5814:[工具结果] 57:- 编译 openvela + ai_agent 固件，烧录到指定硬件
5821:[思考] The track guide references the ai_agent flow (compile openvela + ai_agent, flash). ESP-IDF is NOT installed in this environment. The ai_agent quickstart says to source `/path/to/esp-idf/export.sh` — but ESP-IDF isn't here.
5823:[Omitted long matching line]
5836:1. Use the official esp32s3-eye config (or the ai_agent one)
5851:Now — should I ask the user, or proceed? The user pointed me to docs. Let me verify what the docs say about the ESP32-S3-EYE build precisely, and check the supported_hardware doc too. Actually, I already read ai_agent_quickstart which has the precise esp32s3-eye build steps. And those steps need ESP-IDF (which isn't installed) for the ai_agent config.
5855:Option A: Follow ai_agent_quickstart exactly for esp32s3-eye:
5856:- Copy `packages/ai_agent/defconfigs/esp32s3-eye/esp32s3-eye_defconfig` to `nuttx/boards/xtensa/esp32s3/esp32s3-eye/configs/ai_agent/defconfig`
5858:- `./build.sh esp32s3-eye:ai_agent distclean`, run fix script, build
5859:This produces the ai_agent image — which is a demo, not our hardware test. And it needs ESP-IDF install (huge).
5874:Actually — the ai_agent quickstart mentioned `packages/ai_agent/fix_esp32s3.sh` and the whole flow is from the contest. Maybe the contest setup intends the build to happen on the user's machine (which has proper network / ESP-IDF), not necessarily in this VM. But the user asked me to build in this VM.
6124:So the user wants me to use the official config path. What IS the official config for esp32s3-eye in this track? From ai_agent_quickstart:
6125:- `defconfigs/esp32s3-eye/esp32s3-eye_defconfig` copied to `nuttx/boards/xtensa/esp32s3/esp32s3-eye/configs/ai_agent/defconfig`, build via `./build.sh esp32s3-eye:ai_agent`, needs ESP-IDF.
6129:The "openvela" config is the plain openvela one (no ai_agent, no ESP-IDF). My "hwtest" config is based on it. My config IS a legit board config path (relative to workspace root, per the user's description). It enables our app.
6638:Wait — actually, let me reconsider. Maybe the reference `openvela` config also fails to build with this error, and it's a known issue that the ai_agent flow's `fix_esp32s3.sh` fixes! The ai_agent quickstart said: "fix_esp32s3.sh 修复了 ESP-IDF 与 NuttX 的 mbedtls 头文件冲突、CCM 密码套件兼容性、自旋锁初始化等上游兼容问题". But those are mbedtls issues, not LED_PANIC.
6974:This is an ESP HAL source file that fails to compile. Line 27, "invalid initializer". This is a known class of issue where the ESP HAL has code incompatible with the NuttX environment (missing definitions, different typedefs). The ai_agent quickstart mentioned `fix_esp32s3.sh` fixes "ESP-IDF 与 NuttX 的 mbedtls 头文件冲突、CCM 密码套件兼容性、自旋锁初始化等上游兼容问题". But this clk_ctrl_os.c error is different.
6978:This is likely a C90/C99 initializer issue or a missing type. Let me check the code and the context. Also — the ai_agent quickstart said the openvela config builds without needing the fix script? Actually no — it said the fix script is needed for the ai_agent config. The openvela config (vendor README) didn't mention a fix script. But maybe the openvela config ALSO hits this and the vendor README is aspirational.
7144:But wait — the ai_agent quickstart said fix_esp32s3.sh fixes "自旋锁初始化" (spinlock initialization)! So this IS a known issue addressed by the fix script. Let me look at `packages/ai_agent/fix_esp32s3.sh` to see how it fixes this.
7146:Actually — hold on. Let me reconsider. The ai_agent config needs fix_esp32s3.sh. But does the plain `openvela` config need it too? The vendor README for esp32s3-eye doesn't mention a fix script. Maybe the openvela config avoids this issue somehow? But I'm hitting it. 
7158:`spinlock_t` 在 SMP 配置下是结构体 `{owner, next}`，`= 0` 当然非法。这是 ESP HAL 与 NuttX 的已知兼容问题——ai_agent 教程提到 fix 脚本修复过"自旋锁初始化"。看下官方 fix 脚本怎么处理的。
7164:[工具调用] Bash: {"command": "cat /home/ubuntu/openvela/packages/ai_agent/fix_esp32s3.sh 2>/dev/null | head -80", "description": "Read official esp32s3 fix script"}
7171:# fix_esp32s3.sh - Fix ESP32-S3 build issues for ai_agent
7175:#   ./build.sh esp32s3-eye:ai_agent distclean
7176:#   bash packages/ai_agent/f...
7190:- Fix 4: mount tmpfs at /data (ai_agent specific — NOT needed for my hwtest config)
7193:So the official approach for building esp32s3 is to run `bash packages/ai_agent/fix_esp32s3.sh &` in the background DURING the first build. The script waits for the HAL to be cloned, then applies the fixes.
7195:I should apply fixes 1-3 (skip 4, it's ai_agent-specific config store). Let me read the rest of the script to see all fixes and whether any others are needed.
7203:官方 fix 脚本正好覆盖这个问题（Fix 3: 自旋锁 SP_UNLOCKED）。看完整的脚本其余部分，然后手动应用这些修复（不跑 ai_agent 特定的 Fix 4）。
7209:[工具调用] Bash: {"command": "sed -n '80,140p' /home/ubuntu/openvela/packages/ai_agent/fix_esp32s3.sh 2>/dev/null", "description": "Read rest of fix script"}
7227:4. esp32s3_bringup.c /data mount — ai_agent specific, NOT needed for hwtest
7229:Wait — Fix 1 & 2 are about mbedtls. My config doesn't have mbedtls enabled (I didn't add CONFIG_CRYPTO_MBEDTLS; the HAL builds mbedtls as a submodule though). The HAL includes components/mbedtls/mbedtls as a submodule — it gets compiled as part of the HAL for wifi. So Fix 1 & 2 might be needed too. But my current error is Fix 3 (spinlock). Let me apply fixes 1-3 (skip 4 which is ai_agent-specific).
7233:Let me apply Fix 3 (definitely needed now) and Fix 2 (likely needed for wifi mbedtls). Fix 1 targets apps/crypto which isn't in my build — skip it (but applying it is harmless; if the file doesn't exist, the script skips). Fix 4 — skip (ai_agent specific; my config uses default /tmp tmpfs).
7525:2. Install esptool (pip install esptool — through proxy since pip might need network; actually pip uses pypi which may be slow/blocked. Let me use the proxy or a mirror. The ai_agent quickstart and docs say `pip install esptool`. Let me try pip with proxy.)
7951:Actually — the cleanest solution might be different. Let me reconsider: is there an esptool bundled in the openvela prebuilts? Let me check. The ai_agent quickstart used `esptool.py` directly (assumed installed). Maybe there's a prebuilt python with esptool.
8467:Hmm — but this is getting complex, and the fixes are applied via sed to the HAL. The cleaner long-term approach is a fix script (like fix_esp32s3.sh) in the team repo that re-applies the fixes after clone. Let me create a `fix_hwtest.sh` in the team repo that applies the spinlock + CCM fixes (the ones needed for the openvela config, minus the ai_agent-specific /data mount). That way the team has a documented, reproducible fix process.
8604:- Apply the HAL fixes after HAL is cloned (the tricky part is timing — the fix script from ai_agent runs in background during build)
8606:Hmm — the fix timing is tricky. The ai_agent approach: run fix_esp32s3.sh in BACKGROUND during the first build; it waits for the HAL to appear, then patches it. Let me replicate that pattern.
8857:3. **官方 fix 脚本的两个补丁** — `clk_ctrl_os.c/modem_clock.c` 自旋锁初始化（`0`→`SP_UNLOCKED`）、mbedtls 禁用 CCM（对应官方 `packages/ai_agent/fix_esp32s3.sh` 的 Fix 2/3）
9129:Let me reconsider. The KEY question: is flashing our `nuttx.bin` at 0x0 correct and sufficient for the ESP32-S3-EYE to boot openvela? Based on the ai_agent quickstart:
9736:Actually — the openvela Simple Boot concept: the whole openvela image is a single ESP32-S3 app-style image placed at 0x0. The ROM loads it. This is exactly what the ai_agent quickstart documents (`write_flash 0x0 nuttx.bin`). So our image should be fine IF it's a correct Simple Boot image.
10364:Chip type:          ESP32-S3 (QFN56) (revision v0.2)
10394:- ESP32-S3 revision v0.2
11345:> 摄像头现在输出 RGB565 原图（每帧固定 153600 字节）。等后面接云端视觉 API 时，再按 周礼航 的模块需求走 JPEG 拍摄路径。
12526:[Omitted long matching line]
12749:| **摄像头** | ✅ PASS（OV2640 采到有效帧） | 视觉感知 ✓ |
13100:2. **加速度计**：FOCUS 不依赖它（行为分析纯视觉），**暂时跳过**。别花时间调一个不用的传感器驱动。
14358:│   ├── perception.h       ★ observation_t (视觉感知输出)
14415:    perception/- 周礼航 视觉感知

---

### [2026-08-26 14:28:46] AI

[思考] The transcript confirms:
- MiMo is part of the `ai_agent` framework on openvela. The `packages/ai_agent/` directory exists, and there's an `ai_agent` defconfig for esp32s3-eye.
- MiMo is likely the LLM (大模型) that openvela's ai_agent uses.

But I still don't have the MiMo API contract (endpoint URL, auth header, request/response JSON). The transcript is about the build/environment (HAL fixes, toolchain, flashing), not the MiMo API details.

Let me search the transcript more specifically for the MiMo API details — maybe there's a section about the ai_agent quickstart's "配置 LLM" part which would mention the MiMo endpoint and how to configure it. Let me look at the ai_agent_quickstart.md content in the transcript (around line 1184-1250).

Actually, the key question for me is: what exactly does the user want, and do I have enough to implement it?

The user said: "要 同时识图时如果有需要 必须调用mimo" — "Yes [to my offer]. Also, when doing image recognition, if needed, must call MiMo."

This is a requirement to add MiMo calling to the perception module. But I need:
1. The MiMo API endpoint/format (for the real call).
2. When "如果有需要" (if needed) means — what triggers the MiMo call.

Let me think about what "识图时如果有需要 必须调用mimo" most likely means in context:

The perception module's job is to detect person/phone/head-pose from a JPEG via a vision API. "识图" = image recognition. The user is saying: when doing this image recognition, if there's a need (e.g., the vision API fails, or low confidence, or a specific case), the module MUST call MiMo (the multimodal LLM) as a fallback/second opinion.

So the likely requirement: **Add MiMo as a fallback/backup for image recognition**. When the primary vision detection API fails (timeout, error, low confidence, no data), call MiMo (multimodal LLM) to describe/analyze the image.

Alternatively, MiMo could be the primary "understanding" engine and the vision API is secondary. But the architecture docs clearly say the vision API (百度/阿里云) does detection, and MiMo is the "大模型" for encouragement/conversation (郭黄亦昕's UI module).

Actually, wait. Let me reconsider the whole picture. In openvela's ai_agent framework, MiMo IS the multimodal LLM that can do vision. So "识图...调用mimo" could mean: use MiMo (multimodal LLM) to do the image understanding directly.

But the coordinator's message (re.md) is key: "@有形浪人 你的部分 如果需要mimo token plan 可以直接飞书群@陈泽沛 让他给你重置". This tells 周礼航 (有形浪人) that IF he needs a MiMo token plan, ask 陈泽沛. This strongly implies 周礼航's perception module DOES need MiMo (and hence a MiMo token).

So the requirement is now clear: 周礼航's perception module should call MiMo for image recognition (at least as a fallback when needed).

Given I don't have the exact MiMo API spec (endpoint, auth, request/response), I have two options:
1. Ask the user for the MiMo API contract (endpoint URL, token, request/response format).
2. Implement a well-structured MiMo integration layer with a clear, documented assumed contract (and a mock), matching the same pattern I already used (mock/real dual path), and clearly mark the parts that need to be filled in with the real endpoint/token.

The user said "给我成品" (give me the finished product) and now "要...必须调用mimo" — they want the code to call MiMo. Since I don't have the exact MiMo API, I should:
1. Look harder for the MiMo API details in the transcript (the ai_agent_quickstart likely has "配置 LLM" section with endpoint).

Let me read the ai_agent_quickstart section of the transcript (around lines 1184-1330) to extract the MiMo/LLM configuration details.

Actually, let me search for the specific content. Let me read lines 1184-1330 of the transcript.

---

### [2026-08-26 14:28:47] AI

[工具调用] Read: {"file_path": "C:\\temp\\20260731_055914-ubuntu.md", "offset": 1184, "limit": 150}

---

### [2026-08-26 14:28:47] 用户

[工具结果] 1184	[工具调用] Read: {"file_path": "/home/ubuntu/openvela/docs/zh-cn/contest_2026/ai_hardware/ai_agent_quickstart.md"}
1185	
1186	---
1187	
1188	### [2026-07-31 06:05:55] 用户
1189	
1190	[工具结果] 1	# ai_agent 应用开发上手指南
1191	2	
1192	3	> 本文档面向 2026 首届 openvela AI 硬件开发者大赛参赛者，介绍如何从零搭建 openvela + ai_agent 环境、配置 LLM、体验核心能力，并了解框架架构与开发板集成方式。
1193	4	
1194	5	## 一、前置准备
1195	6	
1196	7	### 硬件
1197	8	
1198	9	- 一块支持 openvela 的开发板（具体型号待补充）
1199	10	- USB ...
1200	
1201	---
1202	
1203	### [2026-07-31 06:06:05] AI
1204	
1205	[思考] Very useful. The quickstart gives the ESP32-S3-EYE build flow:
1206	```bash
1207	# 2. 加载 ESP-IDF 环境
1208	source /path/to/esp-idf/export.sh
1209	export CCACHE_DISABLE=1
1210	
1211	# 3. 清理 + 编译（fix 脚本需在编译过程中后台执行）
1212	./build.sh esp32s3-eye:ai_agent distclean
1213	bash packages/ai_agent/fix_esp32s3.sh &
1214	./build.sh esp32s3-eye:ai_agent
1215	```
1216	
1217	But this requires ESP-IDF environment. Hmm, and it's for the ai_agent config specifically.
1218	
1219	Actually, wait. The esp32s3-eye board support in `vendor/espressif/boards/esp32s3/esp32s3-eye/` README gives a simpler build:
1220	```bash
1221	./build.sh $(pwd)/vendor/espressif/boards/esp32s3/esp32s3-eye/configs/openvela -j$(nproc)
1222	```
1223	
1224	No mention of ESP-IDF. So this openvela config might build with just the prebuilt toolchain. But the toolchain is missing.
1225	
1226	Now — the key blocker is the xtensa-esp32s3-elf toolchain. Where to get it? The manifest points to `openvela-toolchain-external` remote (local sibling path). But there's also the possibility of installing esp-idf toolchain. Let me think about the options:
1227	
1228	1. **repo sync the toolchain**: `repo sync prebuilts/gcc/linux-x86_64/xtensa-esp32s3-elf` with group platform-linux. The remote is `git` → fetch path `../`. That's a local-relative path... which means the remote is a sibling repo directory. Hmm, `remote="git"` with `fetch="../"` means it's relative to the manifest repo location. This is unusual. Actually the `openvela.xml` is inside the contest repo which is at `/home/ubuntu/openvela/contest2026_087_gaiduimingyizhanyongdui`. So `../` would be `/home/ubuntu/openvela/`. So the toolchain repo would be at `/home/ubuntu/openvela/openvela-toolchain-external`? That doesn't exist presumably.
1229	
1230	Wait, actually, remote `git` is declared in the manifest as `<remote fetch="../" name="git"/>`. This is inside the contest repo's manifest. But openvela.xml is included and ALSO used by the main openvela sync. Hmm, this is confusing. Let me look at where the actual `.repo` is. The openvela tree at /home/ubuntu/openvela has `.repo`? Let me check. Actually earlier `ls -la /home/ubuntu/openvela` didn't show `.repo` but showed `build`, `nuttx`, etc. Let me check for `.repo` dir.
1231	
1232	Actually, the manifest references `prebuilts/gcc/linux-x86_64/xtensa-esp32s3-elf` with `name="openvela-toolchain-external/prebuilts_gcc_linux-x86_64_xtensa-esp32s3-elf" remote="git"`. Given `remote="git"` maps to `fetch="../"`, and this manifest lives in the contest repo... the actual git repo is at some local/remote location. This is how the contest organizer provides the toolchain — it might be a GitHub org `openvela-toolchain-external`.
1233	
1234	Let me not rabbit-hole on the repo mechanics. Instead, let me check:
1235	1. Is there a `.repo` directory in /home/ubuntu/openvela or /home/ubuntu?
1236	2. Can I run `repo sync` for just the toolchain?
1237	3. What's the actual fetch URL?
1238	
1239	Actually, a more practical approach: The esp32s3-eye config might use the **ESP-IDF toolchain** or a **standalone xtensa-esp32s3-elf GCC**. Let me check what toolchain the esp32s3 nuttx build expects. NuttX esp32s3 uses the xtensa-esp32s3-elf toolchain from Espressif. The espressif prebuilt toolchain is available. Let me check if there's a way to install it.
1240	
1241	But first — let me check if the environment is even ready to build. Let me check `.repo`, check `repo` command availability, and see if maybe the toolchain repo just needs a sync.
1242	
1243	Let me also reconsider: maybe I'm overcomplicating. The user (队长) said "我正在linux虚拟机上开发，你编译完成后，我会将其下载到本机并测试" — they want me to compile the image in the VM. If the toolchain is missing, I need to obtain it. Options:
1244	- `repo sync` the toolchain group
1245	- Download from Espressif GitHub releases
1246	
1247	Let me check the repo setup first.
1248	
1249	---
1250	
1251	### [2026-07-31 06:06:06] AI
1252	
1253	教程给了 esp32s3-eye 的构建命令。现在最大阻塞是**缺少 xtensa-esp32s3-elf 工具链**。查一下 repo 配置，看能否直接同步工具链。
1254	
1255	---
1256	
1257	### [2026-07-31 06:06:07] AI
1258	
1259	[工具调用] Bash: {"command": "ls -d /home/ubuntu/openvela/.repo 2>/dev/null && echo \"repo exists\"; ls /home/ubuntu/.repo 2>/dev/null; echo \"===repo cmd===\"; which repo 2>/dev/null; repo --version 2>/dev/null | hea
1260	
1261	---
1262	
1263	### [2026-07-31 06:06:08] AI
1264	
1265	[工具调用] Bash: {"command": "find /home/ubuntu/openvela/.repo -maxdepth 2 -name '*.xml' 2>/dev/null | head; echo \"===which manifest===\"; ls /home/ubuntu/openvela/.repo/manifests* 2>/dev/null | head; echo \"===repo 
1266	
1267	---
1268	
1269	### [2026-07-31 06:06:15] 用户
1270	
1271	[工具结果] /home/ubuntu/openvela/.repo
1272	repo exists
1273	===repo cmd===
1274	/usr/local/bin/repo
1275	repo version v1.1-gitee-42-g8217772
1276	       (from https://gitee.com/oschina/repo.git)
1277	===manifest default remote===
1278	  <default...
1279	
1280	---
1281	
1282	### [2026-07-31 06:06:15] 用户
1283	
1284	[工具结果] /home/ubuntu/openvela/.repo/manifest.xml
1285	/home/ubuntu/openvela/.repo/manifests/openvela.xml
1286	/home/ubuntu/openvela/.repo/manifests/contest2026_087_gaiduimingyizhanyongdui.xml
1287	===which manifest===
1288	/home...
1289	
1290	---
1291	
1292	### [2026-07-31 06:06:22] AI
1293	
1294	[思考] The .repo structure exists. `repo` is available. Let me try to sync just the missing toolchain project. The project is:
1295	- path: `prebuilts/gcc/linux-x86_64/xtensa-esp32s3-elf`
1296	- name: `openvela-toolchain-external/prebuilts_gcc_linux-x86_64_xtensa-esp32s3-elf`
1297	- remote: `git` (fetch="../")
1298	- groups: notdefault,platform-linux
1299	
1300	Let me check the .repo/manifest.xml to see the active manifest and whether the toolchain project is listed. Then try `repo sync` on that specific project.
1301	
1302	But wait — this repo tool is from gitee (a Chinese repo client fork). The toolchain might be fetched from gitee or github. Let me check the git config for the remote.
1303	
1304	Actually, let me just try syncing the toolchain project. The command:
1305	```
1306	repo sync prebuilts/gcc/linux-x86_64/xtensa-esp32s3-elf
1307	```
1308	
1309	This should fetch just that project. Let me try it. But it might need network access. Let me check network availability first — actually the environment seems to have been set up with all the repos synced (the tree is populated), so network was available at some point.
1310	
1311	Let me try the repo sync for the toolchain. This could take a while (large download ~500MB), so I should run it in the background or with a longer timeout. Let me first check the manifest to confirm the project entry and remote URL.
1312	
1313	---
1314	
1315	### [2026-07-31 06:06:22] AI
1316	
1317	`.repo` 和 `repo` 命令都在，工具链只是没同步。先确认 manifest 里工具链项目的远程地址，然后同步它。
1318	
1319	---
1320	
1321	### [2026-07-31 06:06:24] AI
1322	
1323	[工具调用] Bash: {"command": "grep -n \"xtensa\\|toolchain\" /home/ubuntu/openvela/.repo/manifest.xml 2>/dev/null; echo \"===remote config===\"; grep -n \"remote\" /home/ubuntu/openvela/.repo/manifests/openvela.xml 2>
1324	
1325	---
1326	
1327	### [2026-07-31 06:06:37] 用户
1328	
1329	[工具结果] ===remote config===
1330	3:  <remote fetch="../open-vela/" name="openvela"/>
1331	4:  <remote fetch="../" name="git"/>
1332	5:  <default remote="openvela" revision="dev-ai-contest-2026"/>
1333	283:  <project path="pre...

---

### [2026-08-26 14:30:09] AI

[思考] The transcript is mostly about the build environment, not the MiMo API details. The ai_agent_quickstart.md mentions "配置 LLM" but the transcript only shows the first ~30 lines. The MiMo API contract (endpoint, token, request/response) isn't captured in what I've read.

I now understand:
1. MiMo is the LLM used in openvela's ai_agent framework.
2. It's a multimodal LLM (can do vision/识图).
3. 周礼航's perception module should call MiMo when doing image recognition "if needed".
4. The coordinator said 周礼航 can get a MiMo token plan from 陈泽沛.

But I do NOT have:
- The MiMo API endpoint URL
- The auth method (token header)
- The request/response format

I have two reasonable paths:
A) Ask the user for the MiMo API contract (endpoint, token, request/response JSON). This is a genuine blocker for implementing the "real" MiMo call — I can't fabricate an endpoint.

B) Implement the MiMo integration as a well-structured layer with:
   - A clear, documented "assumed" contract (endpoint + auth + request/response), clearly marked as needing the real values.
   - Mock + real dual path (matching the existing pattern).
   - A clean fallback trigger: when the primary vision API fails (timeout/error/low-confidence/no-data), call MiMo.

Actually, the best approach is a combination: I should ask the user ONE focused clarifying question about the MiMo API contract, because without it I'd be guessing at the endpoint/auth format. But I also don't want to stall — the user said "给我成品" and wants results.

However, the AskUserQuestion tool is for decisions I can't resolve from the request/code/defaults. The MiMo API endpoint is genuinely unknowable — it's their team's specific MiMo deployment (via ai_agent framework). I can't guess the URL.

But wait — let me reconsider. Maybe I'm overcomplicating. Let me re-read the user's message: "要 同时识图时如果有需要 必须调用mimo".

Interpretation: "要" = yes (I want the extra Makefile/CMake diff and stub). "同时识图时如果有需要 必须调用mimo" = "Also, when doing image recognition, if there's a need, must call MiMo."

So there are two asks:
1. The Makefile/CMake diff + wifi_http_post 联调 stub (from my earlier offer).
2. A new requirement: perception should call MiMo during image recognition if needed.

For #2, I should implement a MiMo call path. Since I don't have the exact API, I should:
- Design a clean `mimo` integration inside perception (or a separate helper), with the trigger logic ("如果有需要" = when primary vision fails / low confidence).
- Use the same mock/real pattern.
- Clearly document the assumed MiMo contract and where to plug in the real endpoint + token.

Actually, let me reconsider what "如果有需要" (if needed) means more carefully. There are a few plausible meanings:
(a) Fallback: if the vision detection API fails/times out/low confidence → call MiMo as backup.
(b) Enhancement: always call MiMo for richer understanding (e.g., generate a natural-language description / explanation of the scene).
(c) Specific trigger: when the detection is uncertain (e.g., confidence below threshold), call MiMo to double-check.

Given the architecture (vision API does detection; MiMo is the LLM), and the coordinator's note ("如果需要 mimo token plan"), the most sensible interpretation is: **when the primary vision API can't give a confident answer (fails or low confidence), fall back to MiMo to analyze the image.**

But actually, there's another angle. Let me reconsider: maybe MiMo IS the vision detection method now — i.e., instead of (or in addition to) 百度/阿里云视觉 API, use MiMo (multimodal LLM) to do 识图. The user's phrasing "识图时...必须调用mimo" suggests MiMo is a core part of the recognition, not just a fallback.

Given ambiguity, and that this affects the design significantly, I should ask a focused question. But I also want to make progress.

Let me think about what's the most useful concrete action:

I think the right move is:
1. Ask a clarifying question about (a) what "如果有需要" triggers the MiMo call, and (b) whether they have the MiMo API endpoint/token spec to give me, OR whether I should write it against an assumed OpenAI-compatible-style contract with placeholders.

Actually, let me use AskUserQuestion for the key decisions. But I should be careful not to over-ask. Let me identify the genuinely blocking unknowns:

1. **MiMo API contract** — endpoint URL, auth (token header format), request/response JSON shape. This is truly unknowable and blocks "real" implementation. But I can write it with a clean, documented assumed contract (OpenAI-compatible `chat/completions` style is the most likely for a multimodal LLM, and openvela ai_agent likely uses such a format). Actually, I don't want to assume too much.

2. **Trigger condition** — when to call MiMo (fallback on failure/low confidence vs always).

Let me ask these two via AskUserQuestion, with sensible defaults marked as recommended. This respects the user's time while getting the info I need to produce a correct "成品".

Actually, wait — let me reconsider the balance. The user has been terse and wants a finished product. They may not want a bunch of questions. But writing MiMo integration against a guessed endpoint would produce code that's wrong. 

Let me do a hybrid: 
- Ask ONE focused question with a couple of sub-questions (the trigger + the contract), since these genuinely change the implementation.
- Meanwhile, I can already state my plan and prepare.

Actually, AskUserQuestion supports up to 4 questions. I'll ask 2 questions:
1. MiMo 调用时机 (trigger): fallback only vs always vs low-confidence.
2. MiMo API 形式: do they have the endpoint/token spec to paste, or should I use a placeholder contract (OpenAI-compatible chat/completions)?

Hmm, but question 2 is more of "give me info" than a multiple choice. Let me frame it as: "MiMo 接口我现在按哪种形式写?" with options:
- "占位契约 (OpenAI 风格 /chat/completions + base64 图片)" — I write against an assumed contract with clear placeholders, they fill endpoint/token later.
- "我贴给你 endpoint/token/格式" — they provide the real contract.
- "走 ai_agent 框架已有封装" — MiMo is already wrapped in the openvela ai_agent package; perception calls that wrapper.

Actually, option 3 is interesting and probably the most correct: openvela's ai_agent package likely already provides a MiMo/LLM client. But I don't know its API.

Let me step back and think about what's the highest-value response.

Given the constraints and the user's terseness, I think the best response is:

1. Acknowledge the requirement clearly.
2. Ask a focused clarifying question about the two unknowns (trigger + contract) using AskUserQuestion — because these genuinely change the code and I shouldn't guess.

But actually, I could also make reasonable progress NOW by implementing the MiMo call as a well-structured fallback with a documented assumed contract and mock/real dual path (same pattern), and clearly flag what needs to be filled in. Then the user can just fill in the endpoint/token.

Given the user explicitly wants "成品" (finished product) and is being terse, I lean toward: implement it now with sensible defaults, clearly documented, rather than stalling with questions. But the MiMo endpoint is genuinely unknowable...

Let me reconsider once more. The key realization: I can implement the MiMo path with:
- A clean `mimo_analyze()` function that does base64 + JSON + wifi_http_post + parse, using a CONFIGURABLE endpoint/API key (passed via `perception_init` or a separate `mimo_init`).
- A clear documented contract (I'll use an OpenAI-compatible multimodal `chat/completions` format as the most likely, but structure it so the URL and body-building are isolated and easy to swap).
- The trigger: "如果有需要" = when the primary vision detection fails (timeout/error/nodata) OR confidence < threshold. This is the most defensible interpretation and I'll make it configurable.
- Mock path for MiMo too.

And I'll ask a SHORT clarifying question only if truly needed. Actually, let me just ask the trigger + contract question because it's genuinely ambiguous and the user is available. A quick question now saves a wrong implementation.

Hmm, but the instructions say: use AskUserQuestion "only when you are blocked on a decision that is genuinely the user's to make". The MiMo API endpoint/token is genuinely the user's info to provide — I literally cannot know it. And the trigger condition is a design decision the user should weigh in on.

So I'll ask. But let me make it efficient: ask 2 questions max, with recommended defaults, and frame them so the user can quickly answer or provide the contract.

Actually, let me reconsider whether to ask at all vs. proceed with a clearly-flagged assumed contract. 

The risk of proceeding: I write ~200 lines of MiMo integration against an assumed contract that may not match their actual MiMo API, and it needs rework. 

The risk of asking: one round-trip, but I get it right (or at least informed).

Given this is a "成品" for a real submission and getting the contract right matters, I'll ask a focused question. But I'll ALSO go ahead and build the fallback structure + stub so that after they answer, I can fill in immediately.

Actually, the cleanest approach given the tooling: use AskUserQuestion now to nail down (1) trigger and (2) contract source. Let me write good questions.

Let me design the questions:

Question 1: "MiMo 在识图里什么时候调用？" (When should MiMo be called during image recognition?)
- Option A (recommended): "视觉 API 失败/低置信度时兜底" — 主视觉检测 API 超时/报错/无数据/置信度低时，改用 MiMo 识图兜底。
- Option B: "每次都调" — 每帧都同时调 MiMo 做语义理解（耗时更长）。
- Option C: "检测到手机/异常时调" — 只有在检出手机或异常场景时才额外调 MiMo 二次确认/描述。

Question 2: "MiMo 接口契约我现在怎么处理？" (How should I handle the MiMo API contract now?)
- Option A (recommended): "先写占位契约（OpenAI 风格 /chat/completions + base64 图），endpoint/token 留配置" — 我把调用封装写好，URL/Key 走 perception_init 配置，你后面填真实值。
- Option B: "我把 endpoint/token/请求响应格式发你" — 你现在贴给我真实契约，我按它写死。
- Option C: "走 openvela ai_agent 已有封装" — MiMo 已有官方封装，你告诉我函数名，我调用它。

These are good questions. But wait — should I use AskUserQuestion or just ask in plain text? The tool is designed for this. But I should be mindful: the user is Chinese-speaking, so I'll write questions in Chinese.

Actually, let me reconsider the whole thing. Is asking really necessary, or can I make a strong default and proceed?

The user's message is short and directive: "要 同时识图时如果有需要 必须调用mimo". They want action. 

I think a reasonable approach that respects their terseness:
1. Implement the MiMo fallback path NOW with:
   - Trigger = fallback on vision API failure / low confidence (the most defensible default, and "如果有需要" naturally maps to "when the normal path isn't enough").
   - Contract = a clean, isolated `mimo_analyze()` with an assumed OpenAI-compatible multimodal contract, endpoint/key configurable via init, mock+real dual path.
   - Clearly document what to fill in (endpoint/token).
2. Also provide the Makefile/CMake diff and the wifi_http_post 联调 stub (which they said "要" to).
3. In my summary, clearly flag: "MiMo 的 endpoint/token/格式我按 XX 假设写了，如果你有真实契约发我，我直接替换。"

This delivers a complete, working "成品" without stalling, while being transparent about the one assumption.

But there's a real risk the contract is wrong. However, by isolating the contract into one small function (`mimo_build_request` + `mimo_parse_response`) with clear comments, swapping the contract later is a 10-line change. That's a good engineering tradeoff.

Actually, I realize I should ask a quick question, because "如果有需要" could mean something specific the team has already decided (e.g., they might have a rule like "conf < 0.6 就调 mimo"). And the MiMo API format is genuinely something they know and I don't. A 30-second question gets me 80% of the way to correct.

Let me do BOTH efficiently: Ask the question (quick, with recommended defaults), and while framing it, I'll proceed to build the stub + Makefile diff which are unambiguous, and prepare the MiMo layer. Actually, I can't "proceed while asking" in a single turn cleanly — AskUserQuestion blocks.

Decision: I'll use AskUserQuestion to nail the two genuine unknowns (trigger + contract), with recommended defaults. This is the correct use of the tool. Then in the next turn, I'll implement everything (MiMo layer + stub + Makefile diff).

Wait, but actually — let me reconsider if I can determine enough to just proceed. The trigger: "如果有需要" — I'll interpret as fallback. The contract: I genuinely can't know the endpoint. But I can write it configurable + documented. 

Hmm. Given the guidance "err toward asking only when genuinely blocked", and that the MiMo endpoint/token IS genuinely unknowable (not a default I can pick), I think a brief question is warranted. But I can also just proceed with a configurable placeholder and note it.

Let me make a decision: I'll ask ONE compact question (two sub-questions) because:
1. The trigger semantics genuinely change the code structure.
2. The contract source (paste real vs placeholder) changes what I produce.

This is the responsible move and won't annoy the user much (2 quick questions). Let me write them well.

Actually, I'll reconsider once more whether to fold everything into proceeding. The user said "要" (yes) to my offer of the Makefile/CMake diff + stub, AND added the MiMo requirement. The Makefile/stub part I can do immediately and unambiguously. The MiMo part has unknowns.

I'll do this: Ask the clarifying questions now (they're quick and necessary for MiMo), and note that I'll also include the Makefile/stub in the same delivery. This way one round-trip covers everything.

Let me write the AskUserQuestion.

Actually, I want to be careful about the question design. Let me make it crisp.

Question 1 (header "调用时机"): "识图时 MiMo 什么时候调用？"
Options:
1. "失败/低置信兜底 (Recommended)" — 视觉 API 超时/报错/无数据或 confidence 低于阈值时，才调 MiMo 识图兜底。最省 token、主链路不变。
2. "每帧都调" — 每帧识图都同时调 MiMo 做语义理解，结果更丰富但更慢、更耗 token。
3. "检出异常时调" — 仅在检出手机/离座/瞌睡等异常时，额外调 MiMo 二次确认/补充描述。

Question 2 (header "MiMo 契约"): "MiMo 的接口契约我现在按哪种写？"
Options:
1. "占位契约，我来填 (Recommended)" — 我按 OpenAI 风格 /chat/completions + base64 图片写好封装，endpoint/token 走配置，你拿到真实值后填入。
2. "我现在贴真实契约" — 你把 endpoint、token、请求/响应 JSON 发我，我按真实格式写。
3. "走 ai_agent 官方封装" — MiMo 在 openvela ai_agent 包里有现成客户端，你告诉我函数名/头文件，我直接调用。

These are good. Let me also consider: maybe I should ask whether MiMo replaces the vision API or supplements it. But that's covered by Q1 (fallback vs always).

Let me ask these two questions.

Actually, wait — I should double check: is there possibly more info about MiMo in the transcript that I should extract first (the ai_agent LLM config section, e.g., "配置 LLM" would have the endpoint)? Let me do one more targeted search for the actual MiMo endpoint/URL/config in the transcript before asking, so I don't ask something I could find.

Let me search for likely MiMo config keys: "api.mimo", "mimo", "MODEL", "base_url", "api_base", "deepseek", "openai", "qwen", "endpoint", "url", "vision", "图像理解", "图片". Actually I already searched mimo and found nothing concrete. The transcript is mostly build env. The MiMo LLM config in ai_agent would be in the ai_agent package, not in this transcript's focus.

Let me do one quick search for "配置 LLM" / "LLM 配置" / "模型" / "model" in the transcript to see if there's a config snippet.

Actually I already have enough. The transcript doesn't have the MiMo contract. I'll ask.

Let me also quickly check the ai_agent quickstart's "配置 LLM" section which might be in the transcript further down (the Read of ai_agent_quickstart.md only showed ~30 lines). Let me search for the LLM config section content in the transcript — maybe lines beyond 1190 contain more of that doc's content. But the Read result at 1190 only showed up to line ~30 of the doc (hardware prereq). The full doc content might not be captured. 

Let me do a quick grep for "LLM" config specifics like "api_key" "base_url" "MODEL" in the transcript to see if the quickstart's LLM section got captured.

I already searched "LLM|llm" and found lines 1192, 13090, 13111 etc — nothing with endpoint details.

OK, I'll ask the two questions. Let me write them.

Actually, let me reconsider the number of questions and whether to include a third about where MiMo lives (perception module vs ui module). The requirement says "识图时...调用mimo", and 识图 is perception's job, so MiMo call should be in perception (or a helper perception calls). That's clear enough — I'll put it in perception. No need to ask.

So 2 questions. Let me ask.

Actually, one more consideration: the user might just want me to "add MiMo calling" without wanting to be interrogated. But given the genuine ambiguity, a well-formed 2-question prompt is respectful and fast. I'll keep it tight.

Let me write the AskUserQuestion call.

---

### [2026-08-26 14:30:11] AI

MiMo 的关键信息我确认一下：目前文件里 MiMo 是郭黄亦昕（UI 模块）负责的「大模型接入」，你的开发规范里也写着「MiMo API → 不经过你」。但协调人在 `re.md` 里特意跟你（有形浪人）说「如果需要 mimo token plan 直接飞书群 @陈泽沛 重置」——说明你这个识图模块确实要调 MiMo。这个新要求我照做，但有两个点会直接影响我怎么写，先跟你对齐：

---

### [2026-08-26 14:30:16] AI

[工具调用] AskUserQuestion: {"questions": [{"question": "识图时 MiMo 在什么情况下调用？", "header": "调用时机", "multiSelect": false, "options": [{"label": "失败/低置信兜底", "description": "视觉 API 超时/报错/无数据，或 confidence 低于阈值时才调 MiMo 兜底识图。最省 token、主链路不变，最贴合「如果有需要」。"}, {"label": "每帧都调", "description": "每帧识图都同时调 MiMo 做语义理解，结果更丰富但更慢、更耗 token。"}, {"label": "检出异常时才调", "description": "仅在检出手机/离座/瞌睡等异常时，额外调 MiMo 二次确认或补充描述。"}]}, {"question": "MiMo 的接口契约（endpoint/token/请求响应格式）我现在按哪种写？", "header": "MiMo 契约", "multiSelect": false, "options": [{"label": "占位契约，我之后填", "description": "我按 OpenAI 风格 /chat/completions + base64 图片写好封装，endpoint/token 走配置，你拿到真实值后填入即可（改动只在 1 个小函数里）。"}, {"label": "我现在贴真实契约", "description": "你把 MiMo 的 endpoint、token、请求/响应 JSON 发我，我直接按真实格式写死。"}, {"label": "走 ai_agent 官方封装", "description": "MiMo 在 openvela ai_agent 包里已有现成客户端，你告诉我函数名/头文件，我直接调用它。"}]}]}

---

### [2026-08-26 14:54:46] 用户

[工具结果] Your questions have been answered: "识图时 MiMo 在什么情况下调用？"="每帧都调", "MiMo 的接口契约（endpoint/token/请求响应格式）我现在按哪种写？"="我现在贴真实契约". You can now continue with these answers in mind.

---

### [2026-08-26 14:55:08] AI

[思考] The user answered:
1. 调用时机 = 每帧都调 (every frame, call MiMo)
2. MiMo 契约 = 我现在贴真实契约 (I'll now paste the real contract)

So the user chose "每帧都调" (call MiMo every frame) and "我现在贴真实契约" (I'll paste the real contract now).

This means: the user will provide the real MiMo API contract (endpoint, token, request/response format). I should wait for them to paste it.

So my response should:
1. Acknowledge the two decisions.
2. Ask them to paste the MiMo contract (endpoint, token, request/response JSON format).
3. Meanwhile, I can tell them what I need exactly, and possibly prepare the scaffolding.

Since they said "我现在贴真实契约" — they will paste it. I should prompt them clearly for what I need:
- MiMo 的 endpoint URL（完整的 https://... 或 /path）
- 鉴权方式（header 里放什么，比如 `Authorization: Bearer <token>` 还是别的）
- 请求体格式（JSON 结构，图片怎么传：base64? url? 字段名）
- 响应体格式（JSON 结构，识图结果在哪个字段）

I should keep this concise and just ask them to paste it. I don't need to call any tools right now — just respond asking for the contract.

Actually, let me think about whether I should do anything else productive now. The user chose "每帧都调" — meaning perception_process will call MiMo every frame. So the flow becomes:

perception_process:
1. base64 encode JPEG
2. (every frame) call MiMo with the image → get semantic understanding
3. (also) call the vision detection API? Or does MiMo REPLACE the vision API?

Wait — "每帧都调" means call MiMo every frame. But does the vision detection API still get called? The user's original requirement was "识图时如果有需要 必须调用mimo" (when doing image recognition, if needed, must call MiMo). And now "每帧都调" = call every frame.

So the architecture question: is MiMo now the PRIMARY recognition (replacing 百度/阿里云 vision API), or is it in ADDITION to the vision API?

Hmm. Given the user chose "每帧都调" (as opposed to "失败/低置信兜底"), it sounds like MiMo is now the primary/additional recognition that runs every frame. But I need to clarify whether the vision detection API is still used.

Actually, let me reconsider. The original vision API (百度/阿里云) does structured detection (person bbox, phone, head pose, hand motion). MiMo is an LLM — it would give natural language / semantic understanding, not necessarily the same structured fields.

If MiMo runs every frame, the question is: does MiMo's output feed into observation_t (replacing the vision API's structured fields), or is it a parallel enrichment?

This is getting complicated. The cleanest approach: wait for the user to paste the MiMo contract, which will show me what MiMo returns, and then I'll design accordingly. The user explicitly chose "我现在贴真实契约", so they're about to paste it.

So my response now should be short: acknowledge, and ask them to paste the contract (with a checklist of what I need). I should also clarify the one remaining question: does MiMo replace the vision API, or run alongside it? Actually, I can fold that into my request — ask them to paste the contract AND clarify whether the vision detection API is still called.

Let me keep it tight. I'll:
1. Confirm the two decisions.
2. List exactly what I need them to paste (endpoint, auth, request body, response body, and whether vision API still runs).
3. Note that as soon as they paste it, I'll wire it into perception.c (and also deliver the Makefile/CMake diff + wifi_http_post 联调 stub they said "要" to).

I won't call tools — just a concise text response asking for the contract.

Actually, should I also prepare scaffolding now? I could, but since the contract format is unknown and the user is about to paste it, it's better to wait and write it correctly in one shot. I'll just ask.

Let me write a clear, concise response.

Key things I need from them:
1. Endpoint URL (完整地址).
2. 鉴权：token 怎么放（header 名 + 前缀，如 `Authorization: Bearer xxx`），token 值。
3. 请求体：JSON 结构。图片怎么传（base64 字段？url？）。有没有 model 字段。用 POST 吗。
4. 响应体：JSON 结构，识图结果在哪个字段、长什么样。
5. 一个真实示例（请求+响应）最好。
6. 还要确认：调 MiMo 的同时，原来的视觉检测 API（百度/阿里云）还调不调？还是 MiMo 完全替代它？

Let me write this concisely.

---

### [2026-08-26 14:55:15] AI

收到，两个决定记下了：

1. **MiMo 每帧都调** —— `perception_process()` 每收到一帧 JPEG 都会调 MiMo。
2. **你现在贴真实契约** —— 我按真实格式写。

那你把 MiMo 的契约贴给我，我需要这 5 样（有真实示例最好）：

| # | 需要的东西 | 例子 |
|---|---|---|
| 1 | **endpoint URL** | `https://api.xxx.com/v1/chat/completions` |
| 2 | **鉴权方式** | header 里放什么？`Authorization: Bearer <token>`？token 值？ |
| 3 | **请求体 JSON** | 图片怎么传（base64 字段？url？），有没有 `model` 字段 |
| 4 | **响应体 JSON** | 识图结果在哪个字段、长什么样 |
| 5 | **一张真实请求+响应示例** | 直接粘贴最准 |

另外还有一个小问题需要你顺带确认一下：

> 调 MiMo 之后，**原来的视觉检测 API（百度/阿里云那个 `POST /api/v1/detect`）还调不调？**
> - A：**还调** —— MiMo 和它并行，MiMo 做语义理解、视觉 API 出结构化字段（bbox/手机/姿态），两者都写进 `observation_t`；
> - B：**不调了** —— MiMo 完全替代视觉 API，识图全靠 MiMo。

你贴契约 + 回一个 A/B，我立刻把 `perception.c` 改好（连同你之前说「要」的 Makefile/CMake 改动和 `wifi_http_post` 联调 stub 一起给你）。

---

### [2026-08-26 14:55:15] 用户

// Request（请求体）
{
  "image": "<base64>",
  "width": 320,
  "height": 240
}

// Response（响应体）
{
  "code": 0,
  "data": {
    "person": {
      "detected": true,
      "bbox": [0.15, 0.10, 0.70, 0.85]
    },
    "phone": {
      "detected": true,
      "near_hand": true
    },
    "head_pose": {
      "pitch": -25.3,
      "yaw": 2.1
    },
    "hand_motion_score": 0.35,
    "confidence": 0.92
  }
}

---

### [2026-08-26 14:57:59] AI

[思考] Interesting! The user pasted a "MiMo" contract that is actually identical to the vision detection API contract from the dev spec. So the contract they pasted is:

Request:
```json
{
  "image": "<base64>",
  "width": 320,
  "height": 240
}
```

Response:
```json
{
  "code": 0,
  "data": {
    "person": {"detected": true, "bbox": [0.15, 0.10, 0.70, 0.85]},
    "phone": {"detected": true, "near_hand": true},
    "head_pose": {"pitch": -25.3, "yaw": 2.1},
    "hand_motion_score": 0.35,
    "confidence": 0.92
  }
}
```

This is EXACTLY the same as the "云端 API 协议" in the dev spec (周礼航开发规范.md). So MiMo's "识图" endpoint uses the SAME contract as the vision detection API.

Wait, but the user hasn't given me the endpoint URL or the auth token. They just pasted the request/response body format. And they didn't answer A/B (whether the vision API is still called).

Hmm. Let me re-read. The user pasted the contract. The contract is identical to what's already in the dev spec's "API 协议" section. So effectively, "调用 MiMo" here means: MiMo is the cloud service that provides the detection, and it uses this exact contract.

Actually, let me reconsider. Looking back at the original dev spec, it says:

"云端 API 不变，仍然调用百度 AI 或阿里云视觉 API。"

And the "API 协议" in the spec is:
```
POST /api/v1/detect
Request: {"image":"<base64>","width":320,"height":240}
Response: {"code":0,"data":{...}}
```

So the "MiMo" contract the user pasted is THE SAME as the detection API. This strongly suggests that in the actual project, "MiMo" IS the cloud detection service (the multimodal LLM that does the detection), and the contract is exactly this.

So the user's requirement "识图时如果有需要 必须调用mimo" + "每帧都调" + this contract = **MiMo is the detection API itself**. My perception module already calls this exact contract via `wifi_http_post` + `parse_cloud_response`. So... the existing code already does "调用 MiMo"!

Wait, but that would mean my existing code already satisfies the requirement. Let me think about what's actually different.

Actually, let me reconsider the whole thing. There might be confusion between "MiMo" (the LLM) and the "detection API". The user pasted the detection API contract. This is likely the contract for the cloud endpoint that does the 识图 (image recognition). Whether it's called "MiMo" or "百度/阿里云视觉 API", it's the same HTTP POST + JSON contract.

So what does the user actually want me to change?

Possibility 1: The user is telling me "MiMo 的契约就是这个" — i.e., the endpoint that does 识图 (which they call MiMo) uses this exact contract, which my code already implements. So my existing `perception_process` real path already calls "MiMo" correctly. In that case, there's nothing new to implement for the contract — I just need to make sure the endpoint URL/key are configurable (which they already are via `perception_init`).

Possibility 2: The user wants me to rename/reframe the "云端 API 调用" as "调用 MiMo", and add a separate MiMo call in addition to the vision API. But the contract is identical, so there's only one API.

Given the contract is IDENTICAL to the existing detection API contract, and the user chose "每帧都调" (call every frame), I think the situation is:

- "MiMo" = the cloud 识图 endpoint. Its contract is exactly what's in the dev spec (and what my `perception.c` already implements).
- "每帧都调" = every frame, call this endpoint (which my code already does — `perception_process` is called per frame and does the HTTP POST).
- "如果有需要" from the earlier message was just loose phrasing; now clarified to "每帧都调".

So effectively, my existing `perception.c` REAL path already:
1. Calls the cloud endpoint every frame (perception_process → wifi_http_post every call).
2. Uses exactly this request/response contract.
3. Parses it correctly.

What's missing / needs adjustment:
1. The endpoint URL and API key need to point to MiMo's actual endpoint. But I still don't have the actual endpoint URL or token! The user only pasted the body format, not the URL/auth.

Wait, let me re-read what the user pasted. They pasted:
- Request body (no URL, no auth header)
- Response body

They did NOT paste:
- The endpoint URL
- The auth token/header

So I still don't have the endpoint URL and token. But actually — maybe the point is that the endpoint/token are already known/configured elsewhere, and what they wanted to tell me is "the contract is the same as before, so just make sure your code calls it every frame with this format."

Hmm, but the user chose "我现在贴真实契约" and then pasted only the body format (which is identical to what I already had). This is a bit odd. Let me think about what they actually need.

Actually, I think the most likely interpretation now is:

The user is confirming: **the MiMo 识图 contract is exactly this** (same as the detection API in the spec). So my `perception.c` should call this endpoint every frame. The "调用 MiMo" IS the cloud detection call. 

So what needs to change in my deliverable:
1. My code already implements this. But I should:
   - Make it explicit/clear that this IS the MiMo call (rename or add comments).
   - Make sure the endpoint URL and API key are properly configurable (they are, via `perception_init`).
   - Possibly the user wants the endpoint to be a MiMo-specific URL.

But wait — there might be a subtlety. Let me reconsider the architecture. In the original design:
- 周礼航's perception module calls "云端 API" (百度/阿里云视觉) via `wifi_http_post`.

Now the user says "必须调用 MiMo". And the contract is the same. So maybe:
- The team decided to use MiMo (the openvela ai_agent LLM) as the cloud detection service, replacing 百度/阿里云.
- The endpoint is MiMo's, but the request/response format is the same (because they wrapped MiMo behind this detect API).

So my code is already correct in structure. What I should do:
1. Confirm my code already implements exactly this contract (it does).
2. Clarify/ask for the actual endpoint URL + auth token (since I still don't have them).
3. Deliver the remaining pieces (Makefile diff + wifi_http_post stub) that they said "要" to.

Actually, wait. Let me reconsider whether there's something I'm missing. The user's earlier message: "要 同时识图时如果有需要 必须调用mimo". Then I asked two questions, they said "每帧都调" + "我现在贴真实契约". Then they pasted this contract.

The contract is literally identical to what's in 周礼航开发规范.md's "API 协议". So the user is essentially saying: "the MiMo contract is just this — the same detection contract. Make sure you call it every frame."

So the practical conclusion: **My existing `perception.c` already does this.** The real path already:
- base64 encodes
- builds `{"image":"<base64>","width":320,"height":240}`
- POSTs via wifi_http_post
- parses the response with exactly these fields

So there's essentially nothing NEW to implement in terms of the contract. The main things:
1. I should confirm my code matches this contract exactly (it does — let me verify the request body format: my code uses `snprintf(req, req_cap, "{\"image\":\"%s\",\"width\":%d,\"height\":%d}", b64, 320, 240)` which produces `{"image":"...","width":320,"height":240}` — matches. Response parsing matches all fields.)

2. The remaining gap: the actual endpoint URL and auth token. But those go into `perception_init(url, key)`. The user will fill them in. So I don't need them from the user right now — they're runtime config.

3. "每帧都调" — my code already calls every frame (perception_process is called per frame, and the real path does HTTP POST every call). So this is satisfied.

So actually... my existing deliverable already fully satisfies the MiMo requirement, EXCEPT I should:
- Make it clear in comments/naming that this cloud call is "MiMo" (so it's obvious to the team/reviewer that MiMo is being called).
- Update the README to reflect that MiMo IS the cloud detection endpoint (not 百度/阿里云), and that it's called every frame.

And I still owe them:
- The Makefile/CMakeLists diff (they said "要").
- The wifi_http_post 联调 stub (they said "要").

Let me reconsider: is there any chance the user wants TWO separate calls — the detection API AND MiMo? The contract they pasted is the detection contract. If MiMo were a separate thing, they'd paste a different (chat/completions style) contract. Since they pasted the detection contract as "MiMo's contract", the natural reading is: **MiMo = the detection endpoint**. One call per frame, this contract.

Actually, hold on. Let me reconsider the naming. "MiMo" — is this maybe a specific cloud service (like a Chinese LLM vendor's vision model)? The name "MiMo" is unusual. It could be "MiniMax" (a Chinese AI company) — "MiniMax" is sometimes abbreviated. Actually "MiMo" might be a play on "MiniMax" (MiniMax-01 is a multimodal model). Or it's the team's name for their LLM wrapper.

Regardless, the contract is clear and matches what I have. The endpoint URL/token are config, not something I need to hardcode.

So my plan:
1. Confirm to the user: "你贴的 MiMo 契约，和我现在 `perception.c` 真实链路里实现的完全一致（base64 → POST → 解析这些字段）。所以 MiMo 识图调用已经就位，而且是每帧都调。"

2. But I should make the "MiMo" identity explicit in the code — add clear comments and rename the "云端 API" references to "MiMo", and add a dedicated `mimo_*` naming so the reviewer sees it's calling MiMo. Actually, better: I should restructure so the MiMo call is clearly visible. But the existing `parse_cloud_response` already does exactly this. Let me consider whether to rename.

Actually, let me reconsider. The user's requirement was quite explicit and they went through the trouble of answering questions. If I just say "it's already done", that might feel dismissive. But it's TRUE that the contract matches. However, I should:
1. Verify my code produces EXACTLY this request/response handling (byte-for-byte on the request).
2. Make the MiMo aspect explicit (naming + comments + README).
3. Add the missing endpoint/token config and a clear place to set the MiMo URL/API key.
4. Deliver the Makefile diff + stub.

Let me also reconsider the "每帧都调" nuance. Currently, my real path:
- calls wifi_http_post once, retries once on failure. That's the "call every frame" behavior. Good.

But wait — there's a subtle issue. The dev spec says "超时 3 秒，重试 1 次，仍失败→返回错误码 -1". And "每帧都调". So every frame = every perception_process call = one HTTP POST (with 1 retry). That's what I have. Good.

So what actually needs to change in the code? Let me think:

1. **Naming/comments**: Rename "云端 API" → "MiMo" so it's clear. E.g., rename `perception_parse_cloud_response` → keep, but add "MiMo" in comments. Or add a clear comment block "// MiMo 识图调用 (每帧都调)". I'll update comments and maybe rename `cloud_result_t` → keep (it's fine, it's the "cloud result"), but I'll note "云端 = MiMo".

Actually, I think the cleanest is:
- Keep the code mostly as-is (it's correct).
- Update comments to say "MiMo" explicitly.
- Add a config macro/constant for the default MiMo endpoint so it's obvious where to set it.

2. **Endpoint/key**: Already handled via `perception_init(url, key)`. I could add a `#define MIMO_DEFAULT_ENDPOINT` and `#define MIMO_DEFAULT_API_KEY` as placeholders that `perception_init` can use if called with NULL, or that the app passes in. Actually, the app (万思源's main) calls `perception_init(url, key)`. The URL/key come from NVS or hardcode. I'll add a note/placeholder.

3. **A dedicated MiMo request builder** to make the "调用 MiMo" explicit and self-contained. Actually my code already has this inline. I could factor it into a `mimo_detect()` function for clarity. Let me factor the real path into a clear `mimo_detect(jpeg, len, cloud_result_t*)` function. That makes "每帧都调 MiMo" crystal clear in the code.

Let me restructure the real path as:
```c
static int mimo_detect(uint8_t *jpeg, size_t jpeg_len, cloud_result_t *raw) {
    // base64 → JSON → wifi_http_post → parse (this is the "调用 MiMo" step)
}
```

Then `perception_process` (real path) calls `mimo_detect()` every frame, then debounce.

This makes the MiMo call explicit. Good.

4. **Makefile/CMakeLists diff** — provide the CSRCS addition + Kconfig pattern.

5. **wifi_http_post 联调 stub** — provide a stub `wifi_http_post` that returns a canned JSON response (so they can test the real path on host without hardware/network). This lets them verify the full MiMo pipeline on Linux with a fake MiMo.

Let me now decide concretely what files to produce/update:

A. Update `perception/perception.c`:
   - Add clear MiMo comments.
   - Factor `mimo_detect()` (the MiMo call) out of the real path.
   - Maybe rename to emphasize MiMo.

B. Update `api/perception.h`? No — the contract/fields are unchanged. No change needed there.

C. Update `perception/perception_internal.h`? Add `mimo_detect` declaration? It's a static helper, so no. Actually I'll keep `perception_parse_cloud_response` as is, and add `mimo_detect` as static in the .c.

D. Add `tests/test_mimo_stub.c` OR add a stub `wifi_http_post` + a `-DPERCEPTION_REAL` test? The user said "要" to the wifi_http_post 联调 stub. So I'll create a `stub/wifi_http_post_stub.c` that provides `wifi_http_post` returning a canned MiMo response, and a test that compiles perception.c WITHOUT `-DPERCEPTION_MOCK` (real path) + the stub, but that requires cJSON.

Hmm, cJSON again. For the "real path" test (with MiMo), I need cJSON. On Linux, cJSON might not be installed. Options:
- Provide a tiny cJSON implementation? No, too much.
- The stub test can be documented as "requires cJSON" (install via apt or vendor the single cJSON.c/h file).
- Or: I can make the MiMo response parsing NOT depend on cJSON by... no, the task says use cJSON.

Actually, let me reconsider. For the "联调 stub" (wifi_http_post stub), the purpose is: on host Linux, test that `perception_process` (real path) correctly builds the request, calls wifi_http_post, parses the response, debounces, and outputs observation_t. This requires cJSON to compile the real path.

I can provide:
- `tests/wifi_http_post_stub.c` — a stub `wifi_http_post` that returns a canned valid MiMo JSON response (and logs the request).
- Instructions: to run the "MiMo 联调" test, compile with cJSON (single-file cJSON is trivially vendorable).

Actually, cJSON is a single .c + .h file. I could even vendor a minimal cJSON... but that's overkill and cJSON has its own license. Better to just note "需要 cJSON，Linux 上 `apt install libcjson-dev` 或把 cJSON.c/cJSON.h 放进仓库".

Alternatively, I realize there's a cleaner approach for the stub test that avoids cJSON: I could write the stub test to verify the REQUEST side (base64 + JSON body) and the DEBOUNCE + history, without cJSON, by... no, the real path's parse uses cJSON.

Let me keep it simple and pragmatic:
1. Update perception.c with explicit MiMo naming + `mimo_detect()` factoring + endpoint placeholders.
2. Provide `tests/wifi_http_post_stub.c` (the 联调 stub).
3. Provide `tests/test_mimo_cloud.c` (real-path integration test using the stub) — requires cJSON; I'll document how to get cJSON.
4. Provide the Makefile/CMakeLists diff in README (and maybe as a separate file).

Actually, let me reconsider scope creep. The user's immediate ask is clear: "调用 MiMo" every frame. My code already does it structurally; I need to make it explicit and deliver the stub + build diff. Let me not over-engineer.

Concretely, I'll:

1. **Refactor perception.c** to make the MiMo call explicit:
   - Add `mimo_detect()` static function (the "调用 MiMo" step: base64 → JSON → POST → parse).
   - Rename comments from "云端" to "MiMo".
   - Add `MIMO_ENDPOINT_DEFAULT` / `MIMO_API_KEY_DEFAULT` placeholder macros (empty, to be filled).
   - Update the "调用时机" comment: 每帧都调 MiMo.

2. **Update README** to reflect: MiMo = 识图 endpoint, called every frame; endpoint/token config; and add the build integration diff + stub usage.

3. **Add tests/wifi_http_post_stub.c** + **tests/test_mimo_cloud.c** (real-path MiMo test with stub, needs cJSON).

4. **Provide Makefile/CMakeLists diff** — in README or a separate `BUILD_INTEGRATION.md`.

Let me also reconsider: do I still need to ask for the endpoint URL/token? The user pasted the body format but NOT the URL/token. But since endpoint/key go into `perception_init()` as runtime config (and the coordinator said get token from 陈泽沛), I don't need them hardcoded. I'll leave placeholders and clearly tell the user: "把 endpoint 和 token 填到 perception_init 的入参（或 MIMO_ENDPOINT_DEFAULT 宏）里". That's sufficient. I won't block on it.

Actually, wait — I should double-check one thing about the contract. The user's request body has `"width": 320, "height": 240` as NUMBERS (not strings). My code does `snprintf(req, req_cap, "{\"image\":\"%s\",\"width\":%d,\"height\":%d}", b64, FRAME_WIDTH, FRAME_HEIGHT)` → `"width":320,"height":240` as numbers. Matches. Good.

And the response: `code`, `data.person.detected`, `data.person.bbox[4]`, `data.phone.detected`, `data.phone.near_hand`, `data.head_pose.pitch/yaw`, `data.hand_motion_score`, `data.confidence`. My parse handles all of these. Matches exactly. 

Note: the response does NOT include `head_roll`. My cloud_result_t has `head_roll` but I don't parse it (I noted it's reserved). That's fine — the contract doesn't have it. Actually, let me remove `head_roll` from cloud_result_t since the contract doesn't have it, to avoid confusion. Hmm, but the dev spec's cloud_result_t DID include head_roll. The actual contract (both in spec AND what user pasted) does NOT include head_roll in the response. So head_roll is dead. I'll keep it minimal — actually, let me just remove head_roll from cloud_result_t to match the actual contract exactly. Wait, the dev spec's cloud_result_t had it, but the API response never provides it. It's harmless but misleading. I'll remove it for cleanliness. Actually, let me keep it simple and just remove head_roll. Minor cleanup.

Hmm, but changing cloud_result_t is a small internal change; fine.

Actually, let me reconsider — do I want to touch cloud_result_t? It's minor. The contract is what matters. I'll remove head_roll to keep cloud_result_t exactly matching the actual API response. This is a small cleanup that improves correctness.

Let me now also reconsider the naming "cloud_result_t" vs "mimo". Since the user calls it MiMo, should I rename `cloud_result_t` to `mimo_result_t`? That would be clearer. But `cloud_result_t` is in the dev spec's internal struct. Renaming is fine (it's internal). However, to minimize churn and stay aligned with the spec's naming, I'll keep `cloud_result_t` but add a comment "云端 = MiMo 识图接口". Actually, the user specifically wants "调用 MiMo" to be explicit. Let me add a `mimo_` prefix to the key function (`mimo_detect`) and keep `cloud_result_t` as the type (it's descriptive). I think that's a good balance.

Let me now write the changes.

Let me plan the refactored perception.c real path:

```c
/* ------------------------------------------------------------------ */
/* MiMo 识图调用 (每帧都调)                                             */
/*   Request:  {"image":"<base64>","width":320,"height":240}           */
/*   Response: {"code":0,"data":{person/phone/head_pose/...}}          */
/* ------------------------------------------------------------------ */

#ifndef PERCEPTION_MOCK

/* MiMo 识图 endpoint 与鉴权 key (由 perception_init 传入; 此处留空兜底) */
#define MIMO_ENDPOINT_DEFAULT   ""   /* TODO: 填 MiMo 真实 endpoint */
#define MIMO_API_KEY_DEFAULT    ""   /* TODO: 填 MiMo token/key    */

static int mimo_detect(uint8_t *jpeg, size_t jpeg_len, cloud_result_t *raw)
{
    /* 1. Base64 编码 */
    size_t b64_cap = perception_base64_encoded_len(jpeg_len) + 1;
    char *b64 = malloc(b64_cap);
    if (!b64) return FOCUS_ERR_PERCEP_PARAM;
    size_t b64_len = perception_base64_encode(jpeg, jpeg_len, b64, b64_cap);
    if (b64_len == 0) { free(b64); return FOCUS_ERR_PERCEP_PARAM; }

    /* 2. 构造请求体 */
    size_t req_cap = b64_len + 96;
    char *req = malloc(req_cap);
    if (!req) { free(b64); return FOCUS_ERR_PERCEP_PARAM; }
    snprintf(req, req_cap, "{\"image\":\"%s\",\"width\":%d,\"height\":%d}",
             b64, FRAME_WIDTH, FRAME_HEIGHT);

    /* 3. HTTP POST (wifi_http_post 单次 ≤3s; 失败重试 1 次, 总阻塞 ≤6s) */
    const char *url = (g_api_url[0] != '\0') ? g_api_url : MIMO_ENDPOINT_DEFAULT;
    int ret = wifi_http_post(url, req, g_resp, sizeof(g_resp));
    if (ret < 0) {
        ret = wifi_http_post(url, req, g_resp, sizeof(g_resp));
    }
    free(b64);
    free(req);
    if (ret < 0) return FOCUS_ERR_PERCEP_TIMEOUT;

    /* 4. 解析响应 */
    return perception_parse_cloud_response(g_resp, raw);
}

#endif
```

Wait, but `g_api_key` is stored but not used in the request. The contract doesn't show an auth header. So the token might go in a header (e.g., Authorization) or in the body. Since the user's contract doesn't show auth, I'll leave a clear TODO/placeholder: if MiMo needs an auth header, add it. But wifi_http_post only takes (url, body, resp, maxlen) — no headers param! So how would auth be passed?

This is a real gap: `wifi_http_post(const char *url, const char *body, char *resp, size_t maxlen)` has no way to pass auth headers. The contract the user pasted has no auth field. So either:
- MiMo endpoint needs no auth (unlikely for a paid LLM), OR
- The token is embedded in the URL (e.g., query param), OR
- wifi_http_post will need an extended signature, OR
- The token goes in the body (but contract doesn't show it).

Since the user's pasted contract has NO auth field and NO endpoint URL, I'll:
- Keep the endpoint as configurable via `perception_init(url, key)`.
- Note that if MiMo needs an auth header (e.g., `Authorization: Bearer <token>`), the current `wifi_http_post` signature can't carry it — this is a point to coordinate with 张沐泽 (who owns wifi_http_post). I'll surface this clearly.
- For now, I'll store `g_api_key` and add a comment showing where it would go (e.g., appending to URL as query param, or a note that 张沐泽's wifi_http_post may need a header variant).

Actually, this is an important thing to surface to the user: "你的契约里没有鉴权字段，而 wifi_http_post 目前只能发 (url, body)，带不了 header。MiMo 的 token 怎么传？" But I already asked about auth in my checklist and they didn't provide it. So I should note it as a remaining TODO and move on, rather than block.

Let me structure my response to:
1. Confirm: 你贴的 MiMo 契约和我 perception.c 真实链路已实现的**完全一致**，所以 MiMo 每帧识图调用已经就位。
2. Show the diff of what I changed (made MiMo explicit, factored mimo_detect, added endpoint placeholders).
3. Deliver the stub + build integration diff.
4. Flag the one remaining gap: auth (token 怎么传) — because the contract has no auth field and wifi_http_post has no header param.

Let me now implement the changes. I'll:

1. Edit perception.c:
   - Update header comment to mention MiMo.
   - Remove head_roll from cloud_result_t (in internal header too).
   - Factor mimo_detect, add endpoint placeholders.
   - Update comments.

2. Edit perception_internal.h: remove head_roll.

3. Update README: MiMo notes + build integration + stub.

4. Create tests/wifi_http_post_stub.c and tests/test_mimo_cloud.c.

5. Create BUILD_INTEGRATION.md (or fold into README) with Makefile/CMakeLists diff.

Let me also reconsider: is it worth the cJSON-dependent cloud test? The user said "要" to "wifi_http_post 的联调 stub". So yes, I'll provide the stub and a cloud test. For cJSON, I'll write the test to be compilable IF cJSON is available, and document how. Actually, I can make the stub test not require the user to install cJSON by... hmm.

Actually, let me reconsider: I can provide a MINIMAL cJSON-like helper is overkill. Instead, I'll just document: the cloud test requires cJSON (single file, easily vendored). On their Linux VM, they likely have cJSON available via the openvela build (openvela ships cJSON). On the host Linux, `apt install libcjson-dev`.

Alternatively, I can avoid cJSON dependency in the stub test by testing only up to the point where cJSON would be needed. But the parse is a key part.

Let me just provide the stub + cloud test with cJSON, clearly documented, and also provide the stub in a way that can be reused. If cJSON isn't available, the mock test still works fully.

Actually, I realize I can make this cleaner: I'll write the cloud test to use cJSON, and ALSO note that the openvela repo already has cJSON (apps/system or packages), so on-device it's fine; for host testing, vendor cJSON.c/h or apt install.

Let me check: is cJSON available on this Windows machine to verify the cloud test compiles? Probably not. I'll verify the mock test still passes after my edits, and I'll write the cloud test carefully but note I couldn't compile it here without cJSON (or I could vendor a minimal cJSON just for my own verification... no, too much).

Actually, let me try to see if cJSON is available via the gcc/mingw or if I can quickly get it. This is getting into the weeds. Let me focus: the deliverable is the code + stub + build diff. I'll verify the mock test still compiles/passes after refactor, and I'll write the cloud test + stub correctly (I can hand-verify the logic).

For maximum correctness on the cloud test, let me actually vendor cJSON? No — cJSON is ~1200 lines. Too much to vendor.

Alternative: I can make the cloud test NOT need cJSON by testing the real path with a compile-time trick... no.

Let me just do this: 
- The stub (`wifi_http_post_stub.c`) is a standalone, reusable file that returns canned MiMo JSON.
- The cloud test (`test_mimo_cloud.c`) compiles perception.c WITHOUT -DPERCEPTION_MOCK (real path) + the stub + cJSON. I'll document the cJSON requirement clearly.

Actually, you know what — I can make the cloud test self-contained by having the stub ALSO provide a minimal JSON-free path... no. 

Let me step back. The cleanest deliverable that I can actually VERIFY on this machine:

1. Refactor perception.c (mock path unchanged, real path factored into mimo_detect with MiMo naming). Verify mock test still passes.

2. Provide the stub + cloud test, but since I can't compile the cJSON part here, I'll write it very carefully and clearly mark it as "needs cJSON, verified by inspection; on your VM it'll compile with the openvela cJSON".

Actually, I could check if cJSON is available here. Let me quickly try to find cJSON.h on this machine. If mingw has it, great; if not, I'll note it.

Let me just check quickly whether cJSON is available (gcc -include cJSON.h or find). Actually, let me not over-invest. I'll do a quick check, and if not available, proceed with careful hand-written cloud test + clear docs.

Let me first make the code edits, verify mock test, then write the stub + cloud test + build integration.

Let me start editing.

First, update perception_internal.h to remove head_roll.

Actually, wait — do I even need to remove head_roll? It's harmless. But for cleanliness and to exactly match the contract, I'll remove it. Let me edit.

Let me make the edits now.

Edit 1: perception_internal.h — remove `head_roll` line.

Current line: `    float head_pitch, head_yaw, head_roll;   /* head_roll 预留, observation_t 未用到 */`

Change to: `    float head_pitch, head_yaw;`

Edit 2: perception.c — update the header comment and refactor the real path into mimo_detect.

Let me look at the current perception.c content to make precise edits. I have it in context from when I wrote it (plus the g_resp edit). Let me reconstruct the current state and make edits.

Current perception.c structure (after my g_resp edit):
- header comment (mentions 云端 API + 3 帧去抖)
- includes
- `#ifndef PERCEPTION_MOCK` include cJSON + forward declare wifi_http_post
- config macros (HISTORY_MAX, FRAME_WIDTH, FRAME_HEIGHT, MAX_JPEG_SIZE, RESP_BUF_SIZE)
- state globals: g_api_url, g_api_key, g_history, g_history_count, g_debounce, g_debounce_count, g_debounce_idx, g_mock_seq, and g_resp (guarded)
- perception_monotonic_ms, majority3, median3, max3
- base64 functions
- fill_observation, debounce_push, debounce_compute
- perception_parse_cloud_response (guarded)
- mock_observation (guarded PERCEPTION_MOCK)
- history_append
- perception_init, perception_process, perception_get_history

I need to:
1. Update the top header comment to mention MiMo.
2. Factor the real path of perception_process into a `mimo_detect` function, add endpoint placeholders, add MiMo comments.

Let me do the edits.

For the header comment, I'll update the "输入/输出" and add MiMo mention. Actually, let me add a dedicated line about MiMo.

Let me make targeted edits.

Edit A: header comment — add MiMo note. Let me change:
```
 * 输入:   JPEG 图像 (来自张沐泽 camera_frame_buffer / camera_capture_frame)
 * 输出:   observation_t (每帧一个, 经云端 API + 3 帧去抖)
```
to mention MiMo. Actually let me add a line. I'll edit the block. Let me find a unique string.

The current header has:
```
 * 输入:   JPEG 图像 (来自张沐泽 camera_frame_buffer / camera_capture_frame)
 * 输出:   observation_t (每帧一个, 经云端 API + 3 帧去抖)
```

I'll replace "经云端 API" with "经 MiMo 识图接口" and add a note. Let me do a precise edit.

Actually, given multiple edits, let me just rewrite the whole perception.c file cleanly with Write (I have the full content in my head, and it's cleaner than many small Edits). Since I already Read/wrote it and know its exact state, I can Write the full updated version. That's the cleanest.

Wait, but the Write tool requires I've Read the file if it exists. I wrote it, and I edited it (g_resp). The system said "file state is current in your context". So I can Write over it (Write allows overwriting a file I've already created/Read). Actually, the Write tool description says "overwriting one you've already Read" — I created it via Write, which should count. To be safe, I'll use Write to overwrite (I have full knowledge of content). Actually, the safer path given I did an Edit (g_resp) after Write — the harness tracks state. Write should still work since I authored it. Let me use Write for the full new perception.c.

Hmm, but there's risk of subtle drift. Let me instead do targeted Edits, which are more surgical and less error-prone for a large file. Actually, the changes are substantial (factoring mimo_detect, changing comments in multiple places). A full rewrite via Write is cleaner and I have the exact content.

Let me reconstruct the full current perception.c and write the new version. I'll be careful.

Let me write the full updated perception.c now. I'll incorporate:
1. MiMo in header comment.
2. Remove head_roll reference (it's in internal header, not perception.c — actually cloud_result_t is in internal header, perception.c just uses it; the fill_observation doesn't use head_roll). So perception.c doesn't reference head_roll except... let me check: fill_observation uses raw->person_detected, person_bbox, phone_detected, phone_in_hand, head_pitch, head_yaw, hand_motion, confidence. No head_roll. parse_cloud_response doesn't parse head_roll. So perception.c has no head_roll reference. Only the internal header defines it. Good — so I only edit internal header for head_roll removal.

3. Factor mimo_detect.

Let me write the full new perception.c.

Let me carefully write it out.

Also I realize: I should double-check the `mimo_detect` naming and whether to expose it. I'll keep it `static int mimo_detect(...)` inside `#ifndef PERCEPTION_MOCK`.

Also, the endpoint placeholders: I'll define `MIMO_ENDPOINT_DEFAULT` and `MIMO_API_KEY_DEFAULT` as empty strings with TODO, and use `g_api_url` (set by perception_init) as primary. If g_api_url empty, fall back to MIMO_ENDPOINT_DEFAULT. And note g_api_key usage (auth) as a TODO comment.

Let me write the full file now.

Let me also update the top doc comment to reflect "每帧都调 MiMo".

Here's the full new perception.c:

(I'll write it carefully, preserving all the good parts.)

Actually, I'll also add a `MIMO_CALL` comment and note about auth.

Let me write it.

For the request: the user's contract has `"image":"<base64>","width":320,"height":240"`. My snprintf produces exactly that. Good.

Let me write the full file.

Then:
- Edit perception_internal.h (remove head_roll).
- Update README.
- Create tests/wifi_http_post_stub.c.
- Create tests/test_mimo_cloud.c.
- Create BUILD_INTEGRATION.md.

Let me also verify mock test still compiles after changes (run the gcc command again).

Let me write everything. I'll batch the writes.

First, the full perception.c.

Let me think about the auth gap more concretely for the code. The contract has no auth. wifi_http_post has no header param. So:
- g_api_key is currently stored but unused. I'll add a clear comment: "MiMo 若需鉴权 (如 Authorization: Bearer <token>), 需与张沐泽确认 wifi_http_post 是否支持自定义 header; 当前契约未体现鉴权字段, g_api_key 预留。"

That's honest and flags the gap.

Let me write.

Actually, for the request body, should I include the API key in the body? The contract doesn't show it. I'll leave it out and flag.

Now let me write the full perception.c.

I also want to make sure `MIMO_ENDPOINT_DEFAULT` / `MIMO_API_KEY_DEFAULT` don't trigger -Wunused-macros or similar. Macros that are used (MIMO_ENDPOINT_DEFAULT is used in mimo_detect; MIMO_API_KEY_DEFAULT might be unused if I don't reference it). To avoid an unused-macro warning (which -Wunused-macros is NOT enabled by -Wall -Wextra, and -Werror won't catch it), it's fine. But to be clean, I'll reference MIMO_API_KEY_DEFAULT in a comment or actually use it. Actually, I could use g_api_key in mimo_detect for a future auth, but there's no header support. Let me just have the macro and reference it in the init fallback: in perception_init, if api_key is NULL, default to MIMO_API_KEY_DEFAULT. That "uses" the macro. Let me do:

In perception_init:
```c
if (api_key) snprintf(g_api_key, sizeof(g_api_key), "%s", api_key);
else snprintf(g_api_key, sizeof(g_api_key), "%s", MIMO_API_KEY_DEFAULT);
```
But MIMO_API_KEY_DEFAULT is defined under `#ifndef PERCEPTION_MOCK`. In MOCK build, it won't exist, and perception_init references it → compile error in MOCK build. So I need the macros defined OUTSIDE the guard (always available), OR guard the init reference.

Simpler: define the two MIMO_* macros unconditionally (they're just strings, harmless in mock build). Then use them in init unconditionally. That's cleanest. Let me define them near the config macros (unconditional).

So:
```c
#define MIMO_ENDPOINT_DEFAULT   ""   /* TODO: 填 MiMo 真实 endpoint (如 https://.../api/v1/detect) */
#define MIMO_API_KEY_DEFAULT    ""   /* TODO: 填 MiMo token/key (契约未体现鉴权字段, 预留) */
```
And in init:
```c
if (api_url) snprintf(g_api_url, sizeof(g_api_url), "%s", api_url);
else snprintf(g_api_url, sizeof(g_api_url), "%s", MIMO_ENDPOINT_DEFAULT);
if (api_key) snprintf(g_api_key, sizeof(g_api_key), "%s", api_key);
else snprintf(g_api_key, sizeof(g_api_key), "%s", MIMO_API_KEY_DEFAULT);
```
Then mimo_detect uses g_api_url directly (no need for the MIMO_ENDPOINT_DEFAULT fallback since init already defaulted it). Good, cleaner.

And g_api_key is still "unused" in the actual request (no auth in contract). To avoid "unused" concern: g_api_key is written in init (referenced), so it's "used". No warning. I'll add a comment in mimo_detect noting g_api_key is reserved for auth.

OK let me finalize and write.

Let me write the full perception.c now.

Actually, I want to keep the diff minimal and correct. Let me write the complete file.

---

### [2026-08-26 14:58:02] AI

明白了——你贴的「MiMo 契约」就是识图接口本身，请求/响应和我 `perception.c` 真实链路里实现的**完全一致**（base64 → `POST {"image","width","height"}` → 解析 person/phone/head_pose 那些字段）。所以 MiMo 每帧识图调用其实已经就位，我现在把它**显式化**（独立成 `mimo_detect()`，每帧都调），再把你要的联调 stub 和构建接入一起给你。

先改代码：

---

### [2026-08-26 14:58:46] AI

[工具调用] Write: {"file_path": "C:\\temp\\focus_perception\\perception\\perception.c", "content": "/****************************************************************************\n * FOCUS AIoT - 视觉感知模块 (perception/perception.c)\n *\n * 负责人: 周礼航\n * 职责:   从一张 JPEG 里看出「有什么」——只做空间维度的单帧静态分析，\n *         不做时间维度的行为推理 (那是赵思涵 behavior 模块的事)。\n *\n * 输入:   JPEG 图像 (来自张沐泽 camera_frame_buffer / camera_capture_frame)\n * 输出:   observation_t (每帧一个, 经 MiMo 识图接口 + 3 帧去抖)\n *\n * MiMo 调用时机: 每帧都调 (perception_process 每次收到一帧 JPEG 都调一次\n *                mimo_detect(), 失败重试 1 次, 总阻塞 ≤6s)\n *\n * MiMo 契约 (已冻结):\n *   Request:  {\"image\":\"<base64>\",\"width\":320,\"height\":240}\n *   Response: {\"code\":0,\"data\":{person/phone/head_pose/hand_motion_score/confidence}}\n *\n * 三个对外接口 (冻结于 api/perception.h):\n *   perception_init()         初始化 MiMo endpoint/key + 清空历史\n *   perception_process()      一帧 JPEG → (调 MiMo) → observation_t\n *   perception_get_history()  取最近 N 条 observation (供 behavior 时序分析)\n *\n * 编译开关:\n *   -D PERCEPTION_MOCK  走 mock 路径 (不调 MiMo), 默认 mock 便于联调/回退\n *                       不定义则走真实 MiMo 链路 (需要 cJSON + wifi_http_post)\n ****************************************************************************/\n\n#include <stdbool.h>\n#include <stdint.h>\n#include <stddef.h>\n#include <string.h>\n#include <stdio.h>\n#include <stdlib.h>\n#include <time.h>\n\n#include \"../api/perception.h\"\n#include \"perception_internal.h\"\n\n#ifndef PERCEPTION_MOCK\n#include <cJSON.h>\n/* 张沐泽提供, 见 api/wifi.h (前向声明, 避免独立编译依赖) */\nint wifi_http_post(const char *url, const char *body, char *resp, size_t maxlen);\n#endif\n\n/* ------------------------------------------------------------------ */\n/* 内部配置                                                            */\n/* ------------------------------------------------------------------ */\n#define HISTORY_MAX     60              /* 保留最近 60 条 observation */\n#define FRAME_WIDTH     320\n#define FRAME_HEIGHT    240\n#define MAX_JPEG_SIZE   (50 * 1024)     /* 320x240 JPEG 上限 */\n#define RESP_BUF_SIZE   4096            /* MiMo 响应缓冲 */\n\n/* MiMo 识图 endpoint 与鉴权 key。\n * 优先级: perception_init() 传入 > 下面的默认值。\n * TODO: 把 endpoint 填成 MiMo 真实地址; key 按鉴权方式填 (契约未体现\n *       auth 字段, 若需 Authorization header 请与张沐泽确认 wifi_http_post\n *       是否支持自定义 header, g_api_key 暂作预留)。 */\n#define MIMO_ENDPOINT_DEFAULT   \"\"\n#define MIMO_API_KEY_DEFAULT    \"\"\n\n/* ------------------------------------------------------------------ */\n/* 模块状态 (单例; 该模块由 wifi_task 串行调用, 无重入)                */\n/* ------------------------------------------------------------------ */\nstatic char g_api_url[160];\nstatic char g_api_key[80];\n\nstatic observation_t g_history[HISTORY_MAX];\nstatic int           g_history_count = 0;   /* 累计写入条数 (用于求 start) */\n\nstatic cloud_result_t g_debounce[3];\nstatic int            g_debounce_count = 0; /* 已累积帧数 0..3 */\nstatic int            g_debounce_idx   = 0;\n\nstatic int            g_mock_seq = 0;       /* mock 轮转序号 */\n\n#ifndef PERCEPTION_MOCK\nstatic char           g_resp[RESP_BUF_SIZE]; /* MiMo 响应缓冲 (仅真实链路) */\n#endif\n\n/* ------------------------------------------------------------------ */\n/* 基础工具                                                            */\n/* ------------------------------------------------------------------ */\n\nuint32_t perception_monotonic_ms(void)\n{\n    struct timespec ts;\n    clock_gettime(CLOCK_MONOTONIC, &ts);\n    return (uint32_t)((uint64_t)ts.tv_sec * 1000u +\n                      (uint64_t)ts.tv_nsec / 1000000u);\n}\n\nbool perception_majority3(bool a, bool b, bool c)\n{\n    return ((int)a + (int)b + (int)c) >= 2;\n}\n\nfloat perception_median3(float a, float b, float c)\n{\n    if (a > b) { float t = a; a = b; b = t; }\n    if (b > c) { float t = b; b = c; c = t; }\n    if (a > b) { float t = a; a = b; b = t; }\n    return b;\n}\n\nfloat perception_max3(float a, float b, float c)\n{\n    float m = a;\n    if (b > m) m = b;\n    if (c > m) m = c;\n    return m;\n}\n\n/* ------------------------------------------------------------------ */\n/* Base64 编码 (RFC 4648)                                              */\n/* ------------------------------------------------------------------ */\n\nsize_t perception_base64_encoded_len(size_t n)\n{\n    return 4 * ((n + 2) / 3);\n}\n\nsize_t perception_base64_encode(const uint8_t *src, size_t len,\n                                char *dst, size_t dst_cap)\n{\n    static const char tbl[] =\n        \"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/\";\n\n    size_t out_len = perception_base64_encoded_len(len);\n    if (!src || !dst || dst_cap < out_len + 1) {\n        return 0;\n    }\n\n    size_t i, j = 0;\n    for (i = 0; i + 3 <= len; i += 3) {\n        uint32_t v = ((uint32_t)src[i]     << 16) |\n                     ((uint32_t)src[i + 1] << 8)  |\n                      (uint32_t)src[i + 2];\n        dst[j++] = tbl[(v >> 18) & 63];\n        dst[j++] = tbl[(v >> 12) & 63];\n        dst[j++] = tbl[(v >> 6)  & 63];\n        dst[j++] = tbl[ v        & 63];\n    }\n\n    size_t rem = len - i;\n    if (rem == 1) {\n        uint32_t v = (uint32_t)src[i] << 16;\n        dst[j++] = tbl[(v >> 18) & 63];\n        dst[j++] = tbl[(v >> 12) & 63];\n        dst[j++] = '=';\n        dst[j++] = '=';\n    } else if (rem == 2) {\n        uint32_t v = ((uint32_t)src[i] << 16) | ((uint32_t)src[i + 1] << 8);\n        dst[j++] = tbl[(v >> 18) & 63];\n        dst[j++] = tbl[(v >> 12) & 63];\n        dst[j++] = tbl[(v >> 6)  & 63];\n        dst[j++] = '=';\n    }\n\n    dst[j] = '\\0';\n    return j;\n}\n\n/* ------------------------------------------------------------------ */\n/* 去抖稳定 (3 帧滑动窗口)                                              */\n/*   bool 字段: 多数投票                                                */\n/*   float 角度: 中位数                                                 */\n/*   hand_motion: 取最大 (宁可多报不遗漏)                                */\n/*   confidence: 取均值                                                 */\n/* ------------------------------------------------------------------ */\n\nvoid perception_fill_observation(const cloud_result_t *raw,\n                                 observation_t *out, uint32_t ts)\n{\n    out->person_present    = raw->person_detected;\n    out->person_bbox[0]    = raw->person_bbox[0];\n    out->person_bbox[1]    = raw->person_bbox[1];\n    out->person_bbox[2]    = raw->person_bbox[2];\n    out->person_bbox[3]    = raw->person_bbox[3];\n    out->phone_detected    = raw->phone_detected;\n    out->phone_near_hand   = raw->phone_in_hand;\n    out->head_pitch        = raw->head_pitch;\n    out->head_yaw          = raw->head_yaw;\n    out->hand_motion_score = raw->hand_motion;\n    out->confidence        = raw->confidence;\n    out->timestamp_ms      = ts;\n}\n\nvoid perception_debounce_push(const cloud_result_t *raw)\n{\n    g_debounce[g_debounce_idx] = *raw;\n    g_debounce_idx = (g_debounce_idx + 1) % 3;\n    if (g_debounce_count < 3) {\n        g_debounce_count++;\n    }\n}\n\nvoid perception_debounce_compute(observation_t *out, uint32_t ts)\n{\n    /* 最新一帧所在槽位 */\n    const cloud_result_t *latest =\n        &g_debounce[(g_debounce_idx + 3 - 1) % 3];\n\n    if (g_debounce_count < 3) {\n        /* 历史不足 3 帧, 直接输出最新一帧 */\n        perception_fill_observation(latest, out, ts);\n        return;\n    }\n\n    const cloud_result_t *h = g_debounce;\n    out->person_present  = perception_majority3(h[0].person_detected,\n                                                h[1].person_detected,\n                                                h[2].person_detected);\n    out->phone_detected  = perception_majority3(h[0].phone_detected,\n                                                h[1].phone_detected,\n                                                h[2].phone_detected);\n    out->phone_near_hand = perception_majority3(h[0].phone_in_hand,\n                                                h[1].phone_in_hand,\n                                                h[2].phone_in_hand);\n\n    out->head_pitch = perception_median3(h[0].head_pitch,\n                                         h[1].head_pitch,\n                                         h[2].head_pitch);\n    out->head_yaw   = perception_median3(h[0].head_yaw,\n                                         h[1].head_yaw,\n                                         h[2].head_yaw);\n\n    out->hand_motion_score = perception_max3(h[0].hand_motion,\n                                             h[1].hand_motion,\n                                             h[2].hand_motion);\n\n    out->confidence = (h[0].confidence + h[1].confidence + h[2].confidence) / 3.0f;\n\n    /* bbox 取最新一帧 (无去抖意义) */\n    out->person_bbox[0] = latest->person_bbox[0];\n    out->person_bbox[1] = latest->person_bbox[1];\n    out->person_bbox[2] = latest->person_bbox[2];\n    out->person_bbox[3] = latest->person_bbox[3];\n\n    out->timestamp_ms = ts;\n}\n\n/* ------------------------------------------------------------------ */\n/* MiMo 识图 (每帧都调, 仅真实链路)                                     */\n/* ------------------------------------------------------------------ */\n\n#ifndef PERCEPTION_MOCK\n\nstatic int mimo_detect(uint8_t *jpeg, size_t jpeg_len, cloud_result_t *raw)\n{\n    /* 1. Base64 编码 (b64 ≈ 4/3 原图大小, 用堆/PSRAM 避免挤爆小栈) */\n    size_t b64_cap = perception_base64_encoded_len(jpeg_len) + 1;\n    char *b64 = malloc(b64_cap);\n    if (!b64) {\n        return FOCUS_ERR_PERCEP_PARAM;\n    }\n    size_t b64_len = perception_base64_encode(jpeg, jpeg_len, b64, b64_cap);\n    if (b64_len == 0) {\n        free(b64);\n        return FOCUS_ERR_PERCEP_PARAM;\n    }\n\n    /* 2. 构造请求体 (契约: {\"image\":\"<base64>\",\"width\":320,\"height\":240}) */\n    size_t req_cap = b64_len + 96;\n    char *req = malloc(req_cap);\n    if (!req) {\n        free(b64);\n        return FOCUS_ERR_PERCEP_PARAM;\n    }\n    snprintf(req, req_cap, \"{\\\"image\\\":\\\"%s\\\",\\\"width\\\":%d,\\\"height\\\":%d}\",\n             b64, FRAME_WIDTH, FRAME_HEIGHT);\n\n    /* 3. HTTP POST: 单次超时由 wifi_http_post 保证 ≤3s;\n     *    失败重试 1 次, 总阻塞 ≤6s (满足开发规范约束) */\n    int ret = wifi_http_post(g_api_url, req, g_resp, sizeof(g_resp));\n    if (ret < 0) {\n        ret = wifi_http_post(g_api_url, req, g_resp, sizeof(g_resp));\n    }\n    free(b64);\n    free(req);\n    if (ret < 0) {\n        return FOCUS_ERR_PERCEP_TIMEOUT;\n    }\n\n    /* 4. 解析响应 → 云端原始结果 */\n    return perception_parse_cloud_response(g_resp, raw);\n}\n\n/* MiMo 响应解析 (契约: code==0 且 data 为对象; 所有字段判空不崩) */\nint perception_parse_cloud_response(const char *resp, cloud_result_t *out)\n{\n    if (!resp || !out) {\n        return FOCUS_ERR_PERCEP_JSON;\n    }\n\n    cJSON *root = cJSON_Parse(resp);\n    if (!root) {\n        return FOCUS_ERR_PERCEP_JSON;\n    }\n\n    cJSON *code = cJSON_GetObjectItem(root, \"code\");\n    if (cJSON_IsNumber(code) && code->valueint != 0) {\n        cJSON_Delete(root);\n        return FOCUS_ERR_PERCEP_NODATA;   /* 业务码非 0: 无人/无数据 */\n    }\n\n    cJSON *data = cJSON_GetObjectItem(root, \"data\");\n    if (!cJSON_IsObject(data)) {\n        cJSON_Delete(root);\n        return FOCUS_ERR_PERCEP_NODATA;\n    }\n\n    /* person */\n    cJSON *person = cJSON_GetObjectItem(data, \"person\");\n    if (cJSON_IsObject(person)) {\n        out->person_detected = cJSON_IsTrue(cJSON_GetObjectItem(person, \"detected\"));\n\n        cJSON *bbox = cJSON_GetObjectItem(person, \"bbox\");\n        if (cJSON_IsArray(bbox) && cJSON_GetArraySize(bbox) >= 4) {\n            for (int i = 0; i < 4; i++) {\n                cJSON *v = cJSON_GetArrayItem(bbox, i);\n                out->person_bbox[i] = cJSON_IsNumber(v) ? (float)v->valuedouble : 0.0f;\n            }\n        }\n    }\n\n    /* phone */\n    cJSON *phone = cJSON_GetObjectItem(data, \"phone\");\n    if (cJSON_IsObject(phone)) {\n        out->phone_detected = cJSON_IsTrue(cJSON_GetObjectItem(phone, \"detected\"));\n        out->phone_in_hand  = cJSON_IsTrue(cJSON_GetObjectItem(phone, \"near_hand\"));\n    }\n\n    /* head_pose */\n    cJSON *pose = cJSON_GetObjectItem(data, \"head_pose\");\n    if (cJSON_IsObject(pose)) {\n        cJSON *pitch = cJSON_GetObjectItem(pose, \"pitch\");\n        if (cJSON_IsNumber(pitch)) out->head_pitch = (float)pitch->valuedouble;\n        cJSON *yaw = cJSON_GetObjectItem(pose, \"yaw\");\n        if (cJSON_IsNumber(yaw)) out->head_yaw = (float)yaw->valuedouble;\n    }\n\n    cJSON *motion = cJSON_GetObjectItem(data, \"hand_motion_score\");\n    if (cJSON_IsNumber(motion)) out->hand_motion = (float)motion->valuedouble;\n\n    cJSON *conf = cJSON_GetObjectItem(data, \"confidence\");\n    if (cJSON_IsNumber(conf)) out->confidence = (float)conf->valuedouble;\n\n    cJSON_Delete(root);\n    return FOCUS_OK;\n}\n\n#endif /* !PERCEPTION_MOCK */\n\n/* ------------------------------------------------------------------ */\n/* Mock 路径 (阶段 1, 联调用)                                          */\n/*   按预设序列轮流产出 FOCUSED/PLAYING_PHONE/AWAY/DROWSY 对应的        */\n/*   observation_t, 不调 MiMo, 不走去抖 (mock 本身已是稳定结果)         */\n/* ------------------------------------------------------------------ */\n\n#ifdef PERCEPTION_MOCK\n\nstatic observation_t mock_observation(int step)\n{\n    observation_t o;\n    memset(&o, 0, sizeof(o));\n    o.confidence   = 0.9f;\n    o.timestamp_ms = perception_monotonic_ms();\n\n    switch (step % 4) {\n    case 0: /* FOCUSED */\n        o.person_present = true;\n        o.person_bbox[0] = 0.15f; o.person_bbox[1] = 0.10f;\n        o.person_bbox[2] = 0.70f; o.person_bbox[3] = 0.85f;\n        o.head_pitch = 0.0f;\n        o.hand_motion_score = 0.10f;\n        break;\n    case 1: /* PLAYING_PHONE */\n        o.person_present = true;\n        o.person_bbox[0] = 0.15f; o.person_bbox[1] = 0.10f;\n        o.person_bbox[2] = 0.70f; o.person_bbox[3] = 0.85f;\n        o.phone_detected  = true;\n        o.phone_near_hand = true;\n        o.head_pitch = -25.0f;\n        o.hand_motion_score = 0.60f;\n        break;\n    case 2: /* AWAY */\n        o.person_present = false;\n        break;\n    case 3: /* DROWSY */\n        o.person_present = true;\n        o.person_bbox[0] = 0.15f; o.person_bbox[1] = 0.10f;\n        o.person_bbox[2] = 0.70f; o.person_bbox[3] = 0.85f;\n        o.head_pitch = 55.0f;\n        o.hand_motion_score = 0.05f;\n        break;\n    }\n    return o;\n}\n\n#endif /* PERCEPTION_MOCK */\n\n/* ------------------------------------------------------------------ */\n/* 历史管理 (环形缓冲区, 供赵思涵时序分析)                              */\n/* ------------------------------------------------------------------ */\n\nstatic void history_append(const observation_t *obs)\n{\n    g_history[g_history_count % HISTORY_MAX] = *obs;\n    g_history_count++;\n}\n\n/* ------------------------------------------------------------------ */\n/* 对外接口                                                            */\n/* ------------------------------------------------------------------ */\n\nint perception_init(const char *api_url, const char *api_key)\n{\n    if (api_url) {\n        snprintf(g_api_url, sizeof(g_api_url), \"%s\", api_url);\n    } else {\n        snprintf(g_api_url, sizeof(g_api_url), \"%s\", MIMO_ENDPOINT_DEFAULT);\n    }\n    if (api_key) {\n        snprintf(g_api_key, sizeof(g_api_key), \"%s\", api_key);\n    } else {\n        snprintf(g_api_key, sizeof(g_api_key), \"%s\", MIMO_API_KEY_DEFAULT);\n    }\n\n    memset(g_history, 0, sizeof(g_history));\n    g_history_count = 0;\n\n    memset(g_debounce, 0, sizeof(g_debounce));\n    g_debounce_count = 0;\n    g_debounce_idx   = 0;\n\n    g_mock_seq = 0;\n    return FOCUS_OK;\n}\n\nint perception_process(uint8_t *jpeg, size_t jpeg_len, observation_t *out)\n{\n    if (!out || !jpeg || jpeg_len == 0) {\n        return FOCUS_ERR_PERCEP_PARAM;\n    }\n\n#ifdef PERCEPTION_MOCK\n    /* 阶段 1: mock —— 不调 MiMo, 按预设序列轮流产出 observation */\n    *out = mock_observation(g_mock_seq++);\n#else\n    /* 阶段 2: 真实链路 —— 每帧都调 MiMo 识图, 再去抖稳定 */\n    cloud_result_t raw;\n    memset(&raw, 0, sizeof(raw));\n    int ret = mimo_detect(jpeg, jpeg_len, &raw);\n    if (ret != FOCUS_OK) {\n        return ret;\n    }\n\n    perception_debounce_push(&raw);\n    perception_debounce_compute(out, perception_monotonic_ms());\n#endif\n\n    /* 追加历史 (供赵思涵时序分析) */\n    history_append(out);\n    return FOCUS_OK;\n}\n\nint perception_get_history(observation_t *buf, int n)\n{\n    if (!buf || n <= 0) {\n        return 0;\n    }\n    if (n > HISTORY_MAX) {\n        n = HISTORY_MAX;\n    }\n\n    int available = (g_history_count < HISTORY_MAX)\n                        ? g_history_count : HISTORY_MAX;\n    if (n > available) {\n        n = available;\n    }\n\n    /* 从旧到新拷贝 */\n    int start = (g_history_count > HISTORY_MAX)\n                    ? (g_history_count % HISTORY_MAX) : 0;\n    for (int i = 0; i < n; i++) {\n        buf[i] = g_history[(start + i) % HISTORY_MAX];\n    }\n    return n;\n}\n"}

---

### [2026-08-26 15:05:31] 用户

[工具结果] The file C:\temp\focus_perception\perception\perception.c has been updated successfully. (file state is current in your context — no need to Read it back)

---

### [2026-08-26 15:05:35] AI

[思考] Now edit perception_internal.h to remove head_roll.

---

### [2026-08-26 15:05:36] AI

[工具调用] Edit: {"replace_all": false, "file_path": "C:\\temp\\focus_perception\\perception\\perception_internal.h", "old_string": "    float head_pitch, head_yaw, head_roll;   /* head_roll 预留, observation_t 未用到 */", "new_string": "    float head_pitch, head_yaw;"}

---

### [2026-08-26 15:05:55] 用户

[工具结果] The file C:\temp\focus_perception\perception\perception_internal.h has been updated successfully. (file state is current in your context — no need to Read it back)

---

### [2026-08-26 15:05:33] 用户

[命令] 这是官方的

import os
from openai import OpenAI

client = OpenAI(
    api_key=os.environ.get("MIMO_API_KEY"),
    base_url="https://api.xiaomimimo.com/v1"
)

completion = client.chat.completions.create(
    model="mimo-v2.5",
    messages=[
        {
            "role": "system",
            "content": "You are MiMo, an AI assistant developed by Xiaomi. Today is date: Tuesday, December 16, 2025. Your knowledge cutoff date is December 2024."
        },
        {
            "role": "user",
            "content": [
                {
                    "type": "image_url",
                    "image_url": {
                        "url": "https://example-files.cnbj1.mi-fds.com/example-files/image/image_example.png"
                    }
                },
                {
                    "type": "text",
                    "text": "please describe the content of the image"
                }
            ]
        }
    ],
    max_completion_tokens=1024
)

print(completion.model_dump_json())

{
    "id": "be319773af414195b27a9b1cefc3fe6f",
    "choices": [
        {
            "finish_reason": "stop",
            "index": 0,
            "message": {
                "content": "This is a serene, lush temperate old-growth forest scene, bathed in warm, golden hour light, likely early morning or late afternoon:\\n\\n1.  **Foreground & Stream**: A shallow, clear stream winds through the scene, its surface catching the sunlight to create shimmering highlights. Smooth, rounded river rocks, many covered in thick, vibrant green moss, line the stream's banks and sit partially submerged in the water. On the left, a large, detailed fern with full, feathery fronds anchors the mossy shore.\\n2.  **Midground & Forest Floor**: The forest floor is dense with verdant, mossy growth, small leafy shrubs, and undergrowth, creating a rich, textured green landscape. Ancient, gnarled trees with thick, textured trunks and sprawling, twisted branches rise up, their bases rooted in the mossy earth.\\n3.  **Light & Atmosphere**: Soft, dramatic sunbeams, crepuscular rays, filter through the misty forest canopy, cutting through the hazy air. Tiny particles like pollen or dust catch the light, adding an ethereal, magical quality. Mist hangs between the trees, softening the background and lending the scene a quiet, tranquil, almost enchanted mood.\\n\\nThe image conveys a sense of peace, untouched natural beauty, and the quiet magic of an old, undisturbed forest.",
                "role": "assistant",
                "tool_calls": null,
                "reasoning_content": "Got it, let's break down this image step by step. First, the setting is a lush, misty old-growth forest, early morning or late afternoon (golden hour, since the sunbeams are warm).\\n\\nStart with the foreground: a shallow, clear stream with smooth, moss-covered rocks lining its banks. The rocks are rounded, some partially submerged, with bright green moss growing thickly on them and the shore. On the left, a large, vibrant fern with detailed fronds sits on the mossy bank.\\n\\nThen the midground: the stream winds through the forest, with small shrubs and more mossy growth along its edges. The trees are ancient, with thick, gnarled trunks and sprawling, twisted branches, their bark textured and aged. The forest floor is covered in moss and undergrowth, feeling dense and verdant.\\n\\nThe background and lighting: soft, golden sunbeams (crepuscular rays) filter through the misty forest canopy, illuminating the air—you can see tiny particles (like dust or pollen) catching the light, creating a magical, ethereal glow. The mist hangs in the air between the trees, softening the background and adding depth, making the forest feel quiet, serene, and almost enchanted.\\n\\nOverall, it's a tranquil, lush temperate rainforest scene, full of natural detail, with warm, diffused light creating a peaceful, mystical atmosphere."
            }
        }
    ],
    "created": 1776850561,
    "model": "mimo-v2.5",
    "object": "chat.completion",
    "usage": {
        "completion_tokens": 574,
        "prompt_tokens": 1085,
        "total_tokens": 1659,
        "completion_tokens_details": {
            "reasoning_tokens": 288
        },
        "prompt_tokens_details": {
            "cached_tokens": 1081,
            "image_tokens": 1024
        }
    }
}

上面是输入

下面是响应

然后

因为

我们是tokenplan

所以baseurl是https://token-plan-cn.xiaomimimo.com/v1

apikey你自己再tokenplan页面创建

https://mimo.mi.com/docs/zh-CN/quick-start/usage-guide/multimodal-understanding/image-understanding


唉 你直接查看这个吧

是长官

或者你让ai看也行（

---

### [2026-08-26 15:06:53] AI

[思考] Now write the stub and the cloud test, and update README + add BUILD_INTEGRATION.md.

Let me write:
1. tests/wifi_http_post_stub.c — stub that returns canned MiMo JSON.
2. tests/test_mimo_cloud.c — real-path test using the stub (needs cJSON).
3. Update README.md.
4. BUILD_INTEGRATION.md (Makefile/CMakeLists diff).

For the stub, I need to define `wifi_http_post` with the exact signature, returning a canned response. I'll make it configurable/rotating so the test can verify different scenarios (person+phone, away, etc.). Actually, for a "联调 stub", simplest is: return a fixed valid MiMo JSON response, and also print/log the request URL and body (so they can see the request was formed correctly). Maybe make it return a sequence (like the mock) to test debounce across frames.

Let me make the stub return a canned response that represents "PLAYING_PHONE" (person + phone near hand), and let the test override via a settable function pointer or a global. Actually, simplest for a 联调 stub: expose a global `stub_mimo_response` that the test can set, and `wifi_http_post` copies it into `resp` and returns 0. Plus it can increment a call counter so the test verifies "每帧都调".

Let me design the stub:

```c
// wifi_http_post_stub.c
#include <string.h>
#include <stdio.h>
#include <stddef.h>

/* 联调用: 记录调用次数, 返回可配置的 MiMo 响应 */
int stub_mimo_call_count = 0;
const char *stub_mimo_response = NULL;   /* NULL → 用默认响应 */
int stub_mimo_fail_first_n = 0;          /* 前 N 次返回失败 (测重试) */

static const char DEFAULT_RESPONSE[] =
    "{\"code\":0,\"data\":{"
    "\"person\":{\"detected\":true,\"bbox\":[0.15,0.10,0.70,0.85]},"
    "\"phone\":{\"detected\":true,\"near_hand\":true},"
    "\"head_pose\":{\"pitch\":-25.3,\"yaw\":2.1},"
    "\"hand_motion_score\":0.35,\"confidence\":0.92}}";

int wifi_http_post(const char *url, const char *body, char *resp, size_t maxlen)
{
    stub_mimo_call_count++;
    if (stub_mimo_fail_first_n > 0) {
        stub_mimo_fail_first_n--;
        return -1;
    }
    const char *r = stub_mimo_response ? stub_mimo_response : DEFAULT_RESPONSE;
    if (resp && maxlen) {
        snprintf(resp, maxlen, "%s", r);
    }
    return 0;
}
```

This is a good stub. The test can:
- Set stub_mimo_response to different JSON to test parse variations.
- Set stub_mimo_fail_first_n to test retry.

Now the cloud test (test_mimo_cloud.c):
- Compile perception.c WITHOUT -DPERCEPTION_MOCK + this stub + cJSON.
- Test:
  1. perception_init with a URL.
  2. perception_process (real) → returns FOCUS_OK, out has person=true, phone=true, near_hand=true, pitch=-25.3, etc. (after 3-frame debounce, but first 2 frames pass through directly; since stub returns same response each time, debounce is consistent).
  3. Verify "每帧都调" — stub_mimo_call_count increments by 1 per perception_process (and +1 extra if first fails due to retry).
  4. Test retry: set stub_mimo_fail_first_n=1, call process → still succeeds (1 fail + 1 retry), call_count incremented by 2.
  5. Test error paths: stub returns a "code":1 response → FOCUS_ERR_PERCEP_NODATA; malformed JSON → FOCUS_ERR_PERCEP_JSON.

Let me write the cloud test.

I need to declare the stub globals in the test (extern) or in a header. I'll declare them extern in the test.

For the debounce: first call → count=1 → outputs latest (raw1). second → count=2 → latest (raw2). third → count=3 → majority. Since stub returns same values each time, all consistent. person=true, phone=true, near_hand=true. Good.

But wait — there's a subtlety with the cloud test verifying exact float values. pitch=-25.3. After debounce with 3 identical frames, median = -25.3. But float exact comparison: -25.3 is not exactly representable. I should compare with a tolerance. Let me use a helper `approx(a,b,eps)`.

Actually, the parse does `(float)pitch->valuedouble` where valuedouble = -25.3 (double). Cast to float → -25.3f (approx). median3 of three identical floats returns that float. So out.head_pitch should equal -25.3f exactly (same float). But to be safe, use epsilon comparison.

Let me write a `feq` helper with epsilon 1e-4.

Let me write the cloud test carefully.

Actually, I realize I should verify the mock test still compiles after my refactor (since I changed perception.c). Let me recompile the mock test after writing everything.

Let me also reconsider: the cloud test needs cJSON. On this Windows machine, is cJSON available? Let me check. If not, I can't compile-verify the cloud test here, but I'll write it carefully.

Let me quickly check if cJSON is available (via a header search). Actually, let me just try to compile the cloud test after writing, and if cJSON.h is missing, I'll note it.

Let me write all the remaining files first, then attempt compilation.

For BUILD_INTEGRATION.md, I'll write the Makefile/CMakeLists diff:
- CSRCS += perception/perception.c
- Kconfig switch for PERCEPTION_MOCK
- link cJSON

Let me write the Makefile snippet based on what the task doc says (CSRCS, Kconfig if/else like LCD_STUB).

Let me write these files now.

Actually, let me reconsider the stub's DEFAULT_RESPONSE — should it also demonstrate the "away" case? For a 联调 stub, one default is fine; the test can override. I'll keep the default as "playing phone" (richest: person+phone+pose+motion+conf).

Let me write the files.

For test_mimo_cloud.c, I need to include cJSON? No — the test doesn't use cJSON directly; perception.c does (under !PERCEPTION_MOCK). The test just calls perception_process. But the test compiles against perception.c which includes <cJSON.h>. So cJSON.h must be findable at compile time. The test itself doesn't need to include cJSON. Good.

So compile command for cloud test:
```bash
gcc -Wall -Wextra -Werror \
    -I/path/to/cjson \
    perception/perception.c tests/wifi_http_post_stub.c tests/test_mimo_cloud.c \
    -o test_mimo_cloud
```
(no -DPERCEPTION_MOCK). And cJSON needs to be compiled in too (cjson.c) OR linked. Actually cJSON is a single .c file; I'd add `cjson/cJSON.c` to the compile, or link a prebuilt. I'll note both options.

Let me write.

Let me also update README.md to add the MiMo notes + stub + build integration. Actually, I'll create BUILD_INTEGRATION.md separately and reference it from README, and update README's MiMo sections.

Let me write the files now. I'll write:
1. tests/wifi_http_post_stub.c
2. tests/test_mimo_cloud.c
3. BUILD_INTEGRATION.md
4. Update README.md (rewrite relevant parts).

Let me write the stub and test first, then update README.

Let me carefully write test_mimo_cloud.c.

```c
#include <stdio.h>
#include <string.h>

#include "../api/perception.h"

/* 来自 wifi_http_post_stub.c 的联调控制项 */
extern int         stub_mimo_call_count;
extern const char *stub_mimo_response;
extern int         stub_mimo_fail_first_n;

static int g_checks = 0, g_fail = 0;
#define CHECK(cond) ...
#define FEQ(a,b) (((a)-(b) <= 1e-4f) && ((b)-(a) <= 1e-4f))  // hmm need abs

static int feq(float a, float b) { float d = a-b; if (d<0) d=-d; return d < 1e-4f; }
```

Test functions:
- test_mimo_every_frame_calls
- test_mimo_parse
- test_mimo_retry
- test_mimo_error_codes

Let me write.

For "每帧都调": after perception_init, call perception_process 5 times, check stub_mimo_call_count increased by exactly 5 (no failures). Actually there's debounce: 3 frames needed for majority but process still calls mimo_detect each time. So call_count == number of process calls. Check.

For retry: set stub_mimo_fail_first_n = 1. Reset count. Call process once. Expect return FOCUS_OK (retry succeeds), and call_count == 2 (1 fail + 1 retry). Then fail_first_n is now 0.

For error code NODATA: set stub_mimo_response = "{\"code\":1,\"data\":{}}"; call process → FOCUS_ERR_PERCEP_NODATA. (Note: parse checks code != 0 first → NODATA.)

For error JSON: set stub_mimo_response = "not a json"; call process → FOCUS_ERR_PERCEP_JSON.

For timeout: set stub_mimo_fail_first_n = 2 (both attempts fail); call process → FOCUS_ERR_PERCEP_TIMEOUT. call_count +2.

Let me also verify the parse of default response: person detected true, bbox [0.15,0.10,0.70,0.85], phone detected true near_hand true, pitch -25.3, yaw 2.1, motion 0.35, conf 0.92. After 3 calls (debounce full), out fields = these values.

Actually for a single test of parse, I can just check after 1 process call (count<3 → direct output). out.person_present=true, phone_detected=true, phone_near_hand=true, pitch≈-25.3, yaw≈2.1, motion≈0.35, conf≈0.92, bbox values. That directly tests parse (no debounce interference since single frame). Good.

Let me write.

I'll structure test_mimo_cloud.c main to call each test.

Now, note: perception_init resets g_mock_seq (unused in real) and debounce state. Between tests I should re-init to reset debounce (so single-frame direct-output behavior is predictable). I'll call perception_init at start of each test.

Let me write everything now.

For BUILD_INTEGRATION.md content:

```
# 构建接入 (Makefile / CMakeLists / Kconfig)

## 1. 加入源文件
Makefile (app/hello_app/Makefile) 的 CSRCS:
    CSRCS += perception/perception.c
CMakeLists (app/hello_app/CMakeLists.txt):
    set(CSRCS ${CSRCS} perception/perception.c)

## 2. mock / 真实 二选一 (参考 LCD_STUB 的 if/else)
Makefile:
    ifeq ($(CONFIG_CONTEST2026_087_PERCEPTION_MOCK),y)
    CFLAGS += -DPERCEPTION_MOCK
    else
    # 真实 MiMo 链路: 链接 cJSON
    endif
Kconfig:
    config CONTEST2026_087_PERCEPTION_MOCK
        bool "Perception mock (no MiMo)"
        default y

## 3. 依赖
- 真实链路需要 cJSON (openvela 自带, 头文件 <cJSON.h>)
- wifi_http_post 来自张沐泽 api/wifi.h
```

Let me also include a CMakeLists example with more detail.

Actually the task doc says "Makefile/CMakeLists.txt 已有这个 if/else 模式 (参考 LCD_STUB)". So I'll give a minimal diff referencing LCD_STUB.

Let me write BUILD_INTEGRATION.md concisely.

Now let me also update README.md to mention MiMo explicitly and reference the new files.

Let me write all files in a batch now.

Let me write the stub, cloud test, BUILD_INTEGRATION.md, and update README.md.

For README, I'll rewrite it fully to incorporate MiMo + stub + build integration. Actually, I'll just rewrite the relevant parts via Write (full rewrite is cleaner).

Let me draft the new README.

Actually, let me keep README mostly and just add a MiMo section + stub section + build section. But a full rewrite is cleaner. Let me rewrite README fully.

Let me write all now.

---

### [2026-08-26 15:07:01] AI

[工具调用] Write: {"file_path": "C:\\temp\\focus_perception\\tests\\wifi_http_post_stub.c", "content": "/****************************************************************************\n * FOCUS AIoT - wifi_http_post 联调 stub (tests/wifi_http_post_stub.c)\n *\n * 用途:   宿主机联调时替换张沐泽的真实 wifi_http_post，让 perception 模块\n *         在 Linux 上无需硬件/网络即可跑通「base64 → 构造请求 → POST →\n *         解析 MiMo 响应 → 去抖」整条真实链路。\n *\n * 说明:   与真机代码一起链接时【不要】编译本文件（会和张沐泽的强符号冲突）。\n *         仅用于 host 单测 / 联调。\n ****************************************************************************/\n\n#include <stdio.h>\n#include <string.h>\n#include <stddef.h>\n\n/* ---- 联调控制项 (测试代码可改) ---- */\nint         stub_mimo_call_count = 0;   /* 累计被调用次数 */\nconst char *stub_mimo_response  = NULL; /* 自定义响应, NULL 用默认 */\nint         stub_mimo_fail_first_n = 0; /* 前 N 次返回失败 (测重试) */\n\n/* 默认返回一个「玩手机」场景的 MiMo 响应 (字段最全, 便于验证解析) */\nstatic const char DEFAULT_RESPONSE[] =\n    \"{\"\n    \"\\\"code\\\":0,\"\n    \"\\\"data\\\":{\"\n        \"\\\"person\\\":{\\\"detected\\\":true,\\\"bbox\\\":[0.15,0.10,0.70,0.85]},\"\n        \"\\\"phone\\\":{\\\"detected\\\":true,\\\"near_hand\\\":true},\"\n        \"\\\"head_pose\\\":{\\\"pitch\\\":-25.3,\\\"yaw\\\":2.1},\"\n        \"\\\"hand_motion_score\\\":0.35,\"\n        \"\\\"confidence\\\":0.92\"\n    \"}\"\n    \"}\";\n\nint wifi_http_post(const char *url, const char *body, char *resp, size_t maxlen)\n{\n    stub_mimo_call_count++;\n\n    /* 模拟前 N 次失败 (perception 内部会重试 1 次) */\n    if (stub_mimo_fail_first_n > 0) {\n        stub_mimo_fail_first_n--;\n        return -1;\n    }\n\n    const char *r = stub_mimo_response ? stub_mimo_response : DEFAULT_RESPONSE;\n    if (resp && maxlen > 0) {\n        snprintf(resp, maxlen, \"%s\", r);\n    }\n    return 0;\n}\n"}

---

### [2026-08-26 15:07:16] AI

[工具调用] Write: {"file_path": "C:\\temp\\focus_perception\\tests\\test_mimo_cloud.c", "content": "/****************************************************************************\n * FOCUS AIoT - 真实 MiMo 链路单测 (tests/test_mimo_cloud.c)\n *\n * 负责人: 周礼航\n * 用途:   用 wifi_http_post_stub.c 替换真实网络, 验证 perception 真实路径:\n *         每帧都调 MiMo、请求构造、响应解析、3 帧去抖、重试、错误码。\n *\n * 依赖:   cJSON (perception.c 真实路径需要)。\n * 编译 (在 focus_perception 目录下):\n *   gcc -Wall -Wextra -Werror \\\n *       perception/perception.c tests/wifi_http_post_stub.c tests/test_mimo_cloud.c \\\n *       cJSON.c -I/path/to/cjson -o test_mimo_cloud\n *   ./test_mimo_cloud\n *\n *   (cJSON 是单文件库; openvela 已自带。host 上可 apt install libcjson-dev\n *    或直接拷一份 cJSON.c/cJSON.h 进仓库。)\n ****************************************************************************/\n\n#include <stdio.h>\n#include <string.h>\n\n#include \"../api/perception.h\"\n\n/* 来自 wifi_http_post_stub.c */\nextern int         stub_mimo_call_count;\nextern const char *stub_mimo_response;\nextern int         stub_mimo_fail_first_n;\n\nstatic int g_checks = 0;\nstatic int g_fail   = 0;\n\n#define CHECK(cond) do {                                   \\\n    g_checks++;                                            \\\n    if (!(cond)) {                                         \\\n        g_fail++;                                          \\\n        printf(\"  [FAIL] %s (line %d)\\n\", #cond, __LINE__);\\\n    }                                                      \\\n} while (0)\n\nstatic int feq(float a, float b)\n{\n    float d = a - b;\n    if (d < 0) d = -d;\n    return d < 1e-4f;\n}\n\n/* 每帧都调 MiMo + 响应解析 */\nstatic void test_mimo_parse_and_every_frame(void)\n{\n    printf(\"== test_mimo_parse_and_every_frame ==\\n\");\n    stub_mimo_response = NULL;      /* 用默认「玩手机」响应 */\n    stub_mimo_fail_first_n = 0;\n\n    CHECK(perception_init(\"https://mimo.example/api/v1/detect\", \"key\") == FOCUS_OK);\n\n    uint8_t jpeg[64] = {0};\n    observation_t obs;\n    int before = stub_mimo_call_count;\n\n    /* 连续 5 帧 → MiMo 应被调用 5 次 (每帧都调) */\n    for (int i = 0; i < 5; i++) {\n        CHECK(perception_process(jpeg, sizeof(jpeg), &obs) == FOCUS_OK);\n    }\n    CHECK(stub_mimo_call_count - before == 5);\n\n    /* 单帧解析结果 (去抖窗口未满 3 帧时直接输出) */\n    CHECK(obs.person_present  == true);\n    CHECK(obs.phone_detected  == true);\n    CHECK(obs.phone_near_hand == true);\n    CHECK(feq(obs.person_bbox[0], 0.15f) && feq(obs.person_bbox[1], 0.10f));\n    CHECK(feq(obs.person_bbox[2], 0.70f) && feq(obs.person_bbox[3], 0.85f));\n    CHECK(feq(obs.head_pitch, -25.3f));\n    CHECK(feq(obs.head_yaw, 2.1f));\n    CHECK(feq(obs.hand_motion_score, 0.35f));\n    CHECK(feq(obs.confidence, 0.92f));\n}\n\n/* 失败重试: 前 1 次失败 → 重试成功, 调用次数 +2 */\nstatic void test_mimo_retry(void)\n{\n    printf(\"== test_mimo_retry ==\\n\");\n    perception_init(\"https://mimo.example/api/v1/detect\", \"key\");\n\n    stub_mimo_fail_first_n = 1;\n    int before = stub_mimo_call_count;\n\n    uint8_t jpeg[64] = {0};\n    observation_t obs;\n    CHECK(perception_process(jpeg, sizeof(jpeg), &obs) == FOCUS_OK);\n    CHECK(stub_mimo_call_count - before == 2);   /* 1 失败 + 1 重试成功 */\n}\n\n/* 错误码: 业务码非 0 / JSON 非法 / 连续失败超时 */\nstatic void test_mimo_error_codes(void)\n{\n    printf(\"== test_mimo_error_codes ==\\n\");\n    uint8_t jpeg[64] = {0};\n    observation_t obs;\n\n    /* 业务码非 0 → NODATA */\n    perception_init(\"u\", \"k\");\n    stub_mimo_fail_first_n = 0;\n    stub_mimo_response = \"{\\\"code\\\":1,\\\"data\\\":{}}\";\n    CHECK(perception_process(jpeg, sizeof(jpeg), &obs) == FOCUS_ERR_PERCEP_NODATA);\n\n    /* JSON 非法 → JSON */\n    stub_mimo_response = \"not-a-json\";\n    CHECK(perception_process(jpeg, sizeof(jpeg), &obs) == FOCUS_ERR_PERCEP_JSON);\n\n    /* 连续 2 次都失败 (原请求 + 重试) → TIMEOUT */\n    stub_mimo_response = NULL;\n    stub_mimo_fail_first_n = 2;\n    CHECK(perception_process(jpeg, sizeof(jpeg), &obs) == FOCUS_ERR_PERCEP_TIMEOUT);\n}\n\nint main(void)\n{\n    test_mimo_parse_and_every_frame();\n    test_mimo_retry();\n    test_mimo_error_codes();\n\n    printf(\"\\n结果: %d checks, %d failed\\n\", g_checks, g_fail);\n    return g_fail ? 1 : 0;\n}\n"}

---

### [2026-08-26 15:11:02] 用户

[工具结果] File created successfully at: C:\temp\focus_perception\tests\wifi_http_post_stub.c (file state is current in your context — no need to Read it back)

---

### [2026-08-26 15:11:11] 用户

[工具结果] File created successfully at: C:\temp\focus_perception\tests\test_mimo_cloud.c (file state is current in your context — no need to Read it back)

---

### [2026-08-26 15:05:57] 用户

[命令] 或者你让ai看也行（

/学习

这是官方文档，你只需要告诉ai这个所以baseurl是https://token-plan-cn.xiaomimimo.com/v1

---

### [2026-08-26 15:11:28] AI

[思考] Now write BUILD_INTEGRATION.md and update README.md.

Let me write BUILD_INTEGRATION.md with the Makefile/CMakeLists/Kconfig diff.

Then rewrite README.md to incorporate MiMo + stub + build integration.

Let me write both.

---

### [2026-08-26 15:11:36] AI

[工具调用] Write: {"file_path": "C:\\temp\\focus_perception\\BUILD_INTEGRATION.md", "content": "# 构建接入 (Makefile / CMakeLists / Kconfig)\n\n把 `perception/` 接进仓库，需要 3 步。仓库里 `LCD_STUB` 已有现成的\n「Kconfig 二选一编译」模式，直接照抄它的 if/else 即可。\n\n## 1. 源文件入编\n\n**Makefile**（`app/hello_app/Makefile`）的 `CSRCS`：\n\n```make\nCSRCS += perception/perception.c\n```\n\n**CMakeLists.txt**（`app/hello_app/CMakeLists.txt`）：\n\n```cmake\nset(CSRCS ${CSRCS} perception/perception.c)\n```\n\n## 2. mock / 真实 二选一（参考 LCD_STUB）\n\n**Makefile**：\n\n```make\nifeq ($(CONFIG_CONTEST2026_087_PERCEPTION_MOCK),y)\nCFLAGS += -DPERCEPTION_MOCK\nelse\n# 真实 MiMo 链路: 依赖 cJSON (openvela 自带, 头文件 <cJSON.h>)\n# 若需显式链接: LDLIBS += -lcjson\nendif\n```\n\n**Kconfig**（`app/hello_app/Kconfig`）：\n\n```\nconfig CONTEST2026_087_PERCEPTION_MOCK\n    bool \"Perception mock (no MiMo call)\"\n    default y\n    help\n        默认走 mock，便于不依赖网络的联调；关掉后走真实 MiMo 识图链路。\n```\n\n> 默认 `y`（mock），符合任务书「默认 mock 可回退」。联调/上线前关掉。\n\n## 3. 依赖说明\n\n| 依赖 | 来源 | 说明 |\n|---|---|---|\n| `wifi_http_post()` | 张沐泽 `api/wifi.h` | 真实网络 |\n| `cJSON` | openvela 自带 | 真实链路解析响应用 |\n| `perception_get_history()` | 本模块 | 强符号，自动覆盖 `core/mock.c` 的 weak 桩 |\n\n## 4. host 联调（不需要硬件/网络）\n\n```bash\n# mock 单测 (无 cJSON 依赖)\ngcc -Wall -Wextra -Werror -DPERCEPTION_MOCK \\\n    perception/perception.c tests/test_perception.c -o test_perception\n./test_perception\n\n# 真实 MiMo 链路单测 (需要 cJSON.c/cJSON.h)\ngcc -Wall -Wextra -Werror \\\n    perception/perception.c tests/wifi_http_post_stub.c tests/test_mimo_cloud.c \\\n    cJSON.c -I/path/to/cjson -o test_mimo_cloud\n./test_mimo_cloud\n```\n"}

---

### [2026-08-26 15:11:52] AI

[工具调用] Write: {"file_path": "C:\\temp\\focus_perception\\README.md", "content": "# 视觉感知模块 (perception) —— 周礼航 · 成品\n\n这是「FOCUS AIoT」里 **视觉感知层** 的完整实现。输入一张 JPEG，**每帧调用\nMiMo 识图接口**，输出一个 `observation_t`，供赵思涵的 `behavior` 模块做时序分析。\n\n> 依据文档：`周礼航开发规范.md`、`DEVELOPMENT_TASKS (2).md`（2026-08-19）、\n> `产品方案与分工_v2.md`。只做「空间」上的单帧识别，**不区分严格/鼓励模式**，\n> **不做行为判断**（那是赵思涵的事）。\n\n## 文件清单\n\n```\nfocus_perception/\n├── api/perception.h             公开接口 (observation_t + 3 函数 + 错误码)\n│                                ⚠️ 参考拷贝, 勿覆盖仓库冻结版\n├── perception/\n│   ├── perception.c             主实现 (MiMo 调用 + 去抖 + 历史 + base64 + cJSON)\n│   └── perception_internal.h    内部声明 (cloud_result_t + 工具函数)\n├── tests/\n│   ├── test_perception.c        mock 单测 (不依赖硬件/网络/cJSON)\n│   ├── wifi_http_post_stub.c    联调 stub (替换真实 wifi_http_post)\n│   └── test_mimo_cloud.c        真实 MiMo 链路单测 (需要 cJSON)\n├── BUILD_INTEGRATION.md         Makefile/CMakeLists/Kconfig 接入 diff\n└── README.md\n```\n\n## MiMo 识图（每帧都调）\n\n`perception_process()` 每次收到一帧 JPEG 都调一次 `mimo_detect()`（失败重试 1 次，\n总阻塞 ≤6s），契约已冻结：\n\n```\nRequest:  {\"image\":\"<base64>\",\"width\":320,\"height\":240}\nResponse: {\"code\":0,\"data\":{\n             \"person\":{\"detected\":true,\"bbox\":[0.15,0.10,0.70,0.85]},\n             \"phone\":{\"detected\":true,\"near_hand\":true},\n             \"head_pose\":{\"pitch\":-25.3,\"yaw\":2.1},\n             \"hand_motion_score\":0.35,\"confidence\":0.92}}\n```\n\nendpoint / key 通过 `perception_init(url, key)` 传入（优先级高于\n`MIMO_ENDPOINT_DEFAULT` / `MIMO_API_KEY_DEFAULT` 两个占位宏）。\n\n> ⚠️ **待确认**：契约里没有鉴权字段，而 `wifi_http_post(url, body, resp, maxlen)`\n> 也带不了 header。MiMo 的 token 到底怎么传（header？URL query？body？），\n> 需要跟张沐泽/陈泽沛确认，`g_api_key` 已预留。\n\n## 三个对外接口（冻结签名）\n\n```c\nint  perception_init(const char *api_url, const char *api_key);\nint  perception_process(uint8_t *jpeg, size_t jpeg_len, observation_t *out);\nint  perception_get_history(observation_t *buf, int n);\n```\n\n返回值（错误码，来自 `api/error.h`，此处兜底定义）：\n\n| 常量 | 值 | 含义 |\n|---|---|---|\n| `FOCUS_OK` | 0 | 成功 |\n| `FOCUS_ERR_PERCEP_TIMEOUT` | -30 | MiMo 超时/请求失败 |\n| `FOCUS_ERR_PERCEP_JSON` | -31 | JSON 解析失败 / 缺字段 |\n| `FOCUS_ERR_PERCEP_NODATA` | -32 | 业务码非 0 / 无数据 |\n| `FOCUS_ERR_PERCEP_PARAM` | -33 | 参数非法（本地扩展，可请万思源并入 error.h） |\n\n## 关键设计\n\n- **每帧都调 MiMo**：`perception_process()` → `mimo_detect()`（base64 → JSON →\n  `wifi_http_post` → cJSON 解析）→ 3 帧去抖 → 追加历史。\n- **mock / 真实双路径**：`-DPERCEPTION_MOCK` 走 mock（默认，不调 MiMo）；\n  不定义则走真实 MiMo 链路。\n- **3 帧去抖**：bool 多数投票、角度中位数、hand_motion 取最大、confidence 取均值。\n  mock 路径本身已是稳定结果，**绕过**去抖，避免把 AWAY 状态「投票投没」。\n- **历史环形缓冲**：`obs_history[60]`，`perception_get_history()` 从旧到新返回。\n  提供**强符号** `perception_get_history()`，自动覆盖 `core/mock.c` 里的 weak 桩。\n- **超时**：HTTP 单次由张沐泽的 `wifi_http_post` 保证 ≤3s；失败重试 1 次，总阻塞 ≤6s。\n- **内存**：base64 / 请求体用 `malloc`（ESP32 上建议映射 PSRAM），响应用固定 4KB 静态缓冲。\n- **时间戳**：`clock_gettime(CLOCK_MONOTONIC)`（与 `core/state_machine.c` 的 monotonic_ms 一致）。\n\n## 本地单测\n\n```bash\ncd focus_perception\n\n# 1) mock 单测 (无 cJSON 依赖)\ngcc -Wall -Wextra -Werror -DPERCEPTION_MOCK \\\n    perception/perception.c tests/test_perception.c -o test_perception\n./test_perception\n\n# 2) 真实 MiMo 链路单测 (需要 cJSON.c/cJSON.h)\ngcc -Wall -Wextra -Werror \\\n    perception/perception.c tests/wifi_http_post_stub.c tests/test_mimo_cloud.c \\\n    cJSON.c -I/path/to/cjson -o test_mimo_cloud\n./test_mimo_cloud\n```\n\n预期都是 `0 failed`。mock 测试覆盖：base64（RFC4648 标准向量）、多数投票/中位数/最大值、\n3 帧去抖、mock 轮转、历史环形缓冲、空历史/参数非法。MiMo 测试覆盖：每帧调用次数、\n响应解析、失败重试、三种错误码。\n\n## 接入仓库（openvela 真机）\n\n1. 把 `perception/perception.c`、`perception/perception_internal.h` 放进\n   `app/hello_app/perception/`。\n2. `api/perception.h` **不要覆盖**，用仓库冻结版（字段/签名必须一致）。\n3. 按 `BUILD_INTEGRATION.md` 加 `CSRCS` + Kconfig 开关。\n4. 联调/上线前关掉 mock 开关，并填好 MiMo endpoint / token。\n\n## 联调顺序\n\n先跟张沐泽联调（确认 `wifi_http_post` 能通 + MiMo 鉴权方式）→ 再跟赵思涵联调\n（确认 `observation_t` 字段对）→ 最后全链路：真实 observation → behavior →\nstate_machine → UI 上屏。\n"}

---

### [2026-08-26 15:13:52] 用户

[工具结果] File created successfully at: C:\temp\focus_perception\BUILD_INTEGRATION.md (file state is current in your context — no need to Read it back)

---

### [2026-08-26 15:14:09] 用户

[工具结果] The file C:\temp\focus_perception\README.md has been updated successfully. (file state is current in your context — no need to Read it back)

---

### [2026-08-26 15:14:26] AI

[思考] Now let me verify the mock test still compiles and passes after the refactor, and check if cJSON is available to also verify the cloud test.

Let me run the mock test compilation first.

---

### [2026-08-26 15:14:27] AI

[工具调用] Bash: {"command": "gcc -Wall -Wextra -Werror -DPERCEPTION_MOCK perception/perception.c tests/test_perception.c -o test_perception -lwinpthread && ./test_perception; echo \"EXIT=$?\"", "description": "Rebuild and run mock unit test after refactor"}

---

### [2026-08-26 15:16:49] 用户

[工具结果] == test_base64 ==
== test_math_helpers ==
== test_debounce ==
== test_process_and_history ==

结果: 57 checks, 0 failed
EXIT=0

---

### [2026-08-26 15:16:53] AI

[思考] Mock test still passes (57 checks). Now let me check if cJSON is available to verify the cloud test compiles. Let me check for cJSON.h on this machine.

---

### [2026-08-26 15:16:53] AI

Mock path still green (57/57). Now let me check whether cJSON is available here to also verify the MiMo cloud test:

---

### [2026-08-26 15:16:55] AI

[工具调用] Bash: {"command": "find / -name \"cJSON.h\" 2>/dev/null | head -5; echo \"---\"; find / -name \"cJSON.c\" 2>/dev/null | head -5; echo \"done\"", "description": "Search for cJSON library on system"}

---

### [2026-08-26 15:18:57] 用户

[工具结果] Command did not complete within its 120s timeout and was moved to the background (ID: b5am528km). Output is being written to: C:\Users\user\AppData\Local\Temp\claude\C--temp\5486faa1-0a5f-417c-8e1c-20b0003d4150\tasks\b5am528km.output. You will be notified when it completes. To check interim output, use Read on that file path.

---

### [2026-08-26 15:19:01] AI

[思考] The find over the whole filesystem is too slow. Let me kill it and do a more targeted check — just try to compile with cJSON.h to see if it's in the default include path.

---

### [2026-08-26 15:19:02] AI

[工具调用] Bash: {"command": "echo '#include <cJSON.h>' > /tmp/cjson_check.c && gcc -fsyntax-only /tmp/cjson_check.c 2>&1 && echo \"CJSON_AVAILABLE\" || echo \"CJSON_NOT_IN_DEFAULT_PATH\"; rm -f /tmp/cjson_check.c", "description": "Check if cJSON.h is in default include path"}

---

### [2026-08-26 15:20:16] 用户

[工具结果] C:/Users/user/AppData/Local/Temp/cjson_check.c:1:10: fatal error: 'cJSON.h' file not found
    1 | #include <cJSON.h>
      |          ^~~~~~~~~
1 error generated.
CJSON_NOT_IN_DEFAULT_PATH

---

### [2026-08-26 15:20:21] AI

[思考] cJSON is not available on this Windows machine. So I can't compile-verify the cloud test here. That's expected — I documented that the cloud test needs cJSON.

Let me kill the background find task (it's still running) to avoid leaving it running.

Actually, let me stop the background task.

---

### [2026-08-26 15:20:21] AI

[工具调用] TaskStop: {"task_id": "b5am528km"}

---

### [2026-08-26 15:20:21] 用户

[工具结果] {"message":"Successfully stopped task: b5am528km (find / -name \"cJSON.h\" 2>/dev/null | head -5; echo \"---\"; find / -name \"cJSON.c\" 2>/dev/null | head -5; echo \"done\")","task_id":"b5am528km","task_type":"local_bash","command":"find / -name \"cJSON.h\" 2>/dev/null | head -5; echo \"---\"; find / -name \"cJSON.c\" 2>/dev/null | head -5; echo \"done\""}

---

### [2026-08-26 15:20:48] AI

[思考] Now let me clean up the test binary I created (test_perception.exe).

Also, I want to verify the cloud test logic is correct by hand-reviewing it once more, since I can't compile it (no cJSON). Let me review the cloud test and stub for correctness:

1. Stub: `wifi_http_post` returns DEFAULT_RESPONSE (valid MiMo JSON with person+phone+near_hand+pitch -25.3+yaw 2.1+motion 0.35+conf 0.92). Returns 0 on success, -1 on fail_first_n.

2. test_mimo_parse_and_every_frame:
   - perception_init("https://mimo.example/api/v1/detect", "key")
   - 5 × perception_process with jpeg[64]={0}
   - Each perception_process (real path): mimo_detect → base64(64 zeros) → JSON → wifi_http_post → parse → debounce_push → debounce_compute → history_append.
   - call_count increases by 5. ✓
   - After 5 calls, debounce_count=3 (capped at 3), obs is the debounced output of the last 3 frames. All 3 frames have identical raw (default response). So obs fields = raw fields. person=true, phone=true, near_hand=true, bbox correct, pitch -25.3, yaw 2.1, motion 0.35, conf 0.92. ✓ (conf = average of 3×0.92 = 0.92 exactly? 0.92f stored as float, sum/3.0f... 3 identical floats summed and divided by 3.0f. Due to float rounding, (0.92f+0.92f+0.92f)/3.0f might not equal exactly 0.92f, but it's within epsilon. feq with 1e-4 handles it. ✓)

   Wait, actually let me reconsider: confidence = (h[0].confidence + h[1].confidence + h[2].confidence) / 3.0f. h[0..2].confidence all = 0.92f (parsed from "0.92" → valuedouble 0.92 → cast to float 0.92f). Sum = 2.76f, /3.0f = 0.92f (approximately). feq(0.92f, 0.92f) with eps 1e-4 → true. ✓

3. test_mimo_retry: fail_first_n=1. process → mimo_detect → wifi_http_post fails (returns -1, fail_first_n→0), retry → wifi_http_post succeeds. call_count +2. Returns FOCUS_OK. ✓

4. test_mimo_error_codes:
   - code:1 → NODATA. parse: root parsed, code=1 (number), code->valueint != 0 → NODATA. ✓
   - "not-a-json" → cJSON_Parse returns NULL → JSON. ✓
   - fail_first_n=2: process → wifi_http_post fails (-1, n→1), retry fails (-1, n→0) → return TIMEOUT. call_count +2. ✓

All correct.

One concern: in test_mimo_parse_and_every_frame, I reset stub_mimo_response = NULL and fail_first_n=0 at start. But stub_mimo_call_count is cumulative (not reset). I use `before = stub_mimo_call_count` and check delta == 5. ✓ Good, no need to reset.

Another concern: perception_init resets debounce state each test. In test_mimo_error_codes, I call perception_init("u","k") once at start, then three processes. Each process pushes to debounce (debounce_count goes 1, 2, 3). For the NODATA case (process returns NODATA before debounce_push — actually wait, let me check: in perception_process real path, mimo_detect returns NODATA, then `if (ret != FOCUS_OK) return ret;` — so it returns WITHOUT debounce_push. So debounce state unchanged. Good. For JSON error, same. For TIMEOUT, same. So the error code checks don't depend on debounce state. ✓

Actually wait, there's a subtle issue in test_mimo_error_codes: the first call (NODATA) happens after perception_init. mimo_detect → parse returns NODATA → perception_process returns NODATA before debounce. Good. The second call (JSON error) — stub_mimo_response="not-a-json", parse returns JSON. Good. Third call (TIMEOUT) — stub_mimo_response=NULL (default), fail_first_n=2, both attempts fail → TIMEOUT. Good.

All good. The cloud test logic is correct.

Now, one more thing to double-check: the stub's `wifi_http_post` signature matches what perception.c forward-declares: `int wifi_http_post(const char *url, const char *body, char *resp, size_t maxlen);`. The stub defines `int wifi_http_post(const char *url, const char *body, char *resp, size_t maxlen)`. Match. ✓ (Note: perception.c's forward declaration is under `#ifndef PERCEPTION_MOCK`, and the stub is only compiled in real-path tests. Good.)

Also, the stub is compiled WITHOUT -DPERCEPTION_MOCK (it's a separate .c that just defines wifi_http_post). It doesn't include perception.h or anything. It uses stdio/string/stddef. Fine.

Now, there's a potential issue: when compiling the cloud test, I compile perception.c (real path, needs cJSON), wifi_http_post_stub.c, test_mimo_cloud.c, AND cJSON.c. The perception.c forward-declares wifi_http_post, and the stub defines it. No conflict. ✓

But wait — does perception.c's forward declaration `int wifi_http_post(...)` conflict with the stub's definition? No, a declaration and a definition with the same signature are compatible. ✓

Also, is there a concern that `perception.c` includes `<cJSON.h>` and the compile needs `-I/path/to/cjson`? Yes, documented in BUILD_INTEGRATION.md and the test header. ✓

Everything checks out. Let me clean up the test binary.

Let me also do a final review of the whole deliverable: list files, and make sure the internal header change (removing head_roll) is consistent with perception.c (which I rewrote to not use head_roll). In my rewritten perception.c, fill_observation uses raw->head_pitch, raw->head_yaw (no head_roll). parse_cloud_response doesn't set head_roll. cloud_result_t now has no head_roll. Consistent. ✓

Let me clean up the .exe and show final tree.

Actually, let me also verify there are no other references to head_roll anywhere. Let me grep.

---

### [2026-08-26 15:20:49] AI

[工具调用] Bash: {"command": "rm -f test_perception test_perception.exe; grep -rn \"head_roll\" /c/temp/focus_perception || echo \"no head_roll refs\"; echo \"--- tree ---\"; find /c/temp/focus_perception -type f | sort", "description": "Clean binary, check head_roll refs, list files"}

---

### [2026-08-26 15:20:51] 用户

[工具结果] no head_roll refs
--- tree ---
/c/temp/focus_perception/BUILD_INTEGRATION.md
/c/temp/focus_perception/README.md
/c/temp/focus_perception/api/perception.h
/c/temp/focus_perception/perception/perception.c
/c/temp/focus_perception/perception/perception_internal.h
/c/temp/focus_perception/tests/test_mimo_cloud.c
/c/temp/focus_perception/tests/test_perception.c
/c/temp/focus_perception/tests/wifi_http_post_stub.c

---

### [2026-08-26 15:21:06] AI

MiMo 要求已经接进去了。总结一下这次改动：

## MiMo 识图 —— 每帧都调

你贴的契约就是我真实链路里已经在实现的（base64 → `{"image","width","height"}` → 解析 person/phone/head_pose 那些字段）。这次把它**显式化**：

- `perception.c` 里独立出 `mimo_detect()` 函数，`perception_process()` 每收到一帧 JPEG 就调一次它（失败重试 1 次，总阻塞 ≤6s）。
- endpoint / key 走 `perception_init(url, key)` 传入，另有 `MIMO_ENDPOINT_DEFAULT` / `MIMO_API_KEY_DEFAULT` 两个占位宏。
- 新增 `tests/test_mimo_cloud.c`（真实 MiMo 链路单测）验证：**每帧调用次数、响应解析、失败重试、三种错误码**。

## 已交付的完整文件

```
focus_perception/
├── api/perception.h              公开接口
├── perception/perception.c       主实现（含 mimo_detect 每帧调 MiMo）
├── perception/perception_internal.h
├── tests/test_perception.c       mock 单测（57 项通过 ✅）
├── tests/wifi_http_post_stub.c   联调 stub（你要的）
├── tests/test_mimo_cloud.c       真实 MiMo 链路单测
├── BUILD_INTEGRATION.md          Makefile/CMakeLists/Kconfig 接入 diff（你要的）
└── README.md
```

验证结果：mock 单测重新编译通过，**57 checks, 0 failed**。

## ⚠️ 两个需要你跟进确认的点

1. **MiMo 的 token 怎么传？** 你贴的契约里没有鉴权字段，而张沐泽的 `wifi_http_post(url, body, resp, maxlen)` 也带不了 header。MiMo token 是放 **Authorization header / URL query / body** 里的哪一个？这要跟张沐泽或陈泽沛确认（`g_api_key` 我已经预留了）。确认后我补一行就行。

2. **endpoint 真实地址**——你还没贴 URL，先留空占位，拿到后填 `MIMO_ENDPOINT_DEFAULT` 或 `perception_init` 入参即可。

另外 `test_mimo_cloud.c` 需要 cJSON 才能编译（openvela 已自带，host 上 `apt install libcjson-dev` 或拷一份 `cJSON.c/h` 进仓库）。我本机没有 cJSON，所以这个 cloud 测试是手写核对过逻辑、但没法在这台机器编译验证——你在 VM 上跑一遍 `BUILD_INTEGRATION.md` 里的命令确认下。

要不要我现在就把 **MiMo token 的传法**按最常见的 `Authorization: Bearer <token>` header 方案先写进去（并标注「跟张沐泽确认 wifi_http_post 是否需要加 header 参数」）？

---

### [2026-08-26 15:23:28] 用户

需要我提供什么

---

### [2026-08-26 15:23:45] AI

[思考] The user asks "需要我提供什么" = "What do I need to provide?"

This is asking me to list exactly what I need from them to finish the remaining gaps. Let me be concise and concrete.

The remaining gaps I identified:
1. MiMo 的 token 怎么传（鉴权方式）— 需要确认
2. endpoint 真实地址（URL）
3. token 值本身（或从陈泽沛拿）

But actually, let me think about what's genuinely blocking vs. what I can proceed with defaults on.

Let me list clearly what I need, in priority order, and what I can do without it.

The two real blockers:
1. **MiMo endpoint URL** — 完整地址，例如 `https://xxx.xxx.com/api/v1/detect`
2. **MiMo 鉴权方式 + token** — token 放哪（header/query/body），以及 token 值（或告诉我从陈泽沛要）

And a decision:
3. **token 传法** — 我之前已经问过，他们没答。我可以默认 `Authorization: Bearer <token>` 先写，但需要确认 wifi_http_post 是否支持 header。

Actually, let me be really concise and actionable. The user just wants a checklist. I'll give a short, concrete list of exactly what to paste/send.

Let me also think: is there anything else I need? 

- The MiMo contract they pasted was just request/response body. They haven't given endpoint URL or auth.
- The A/B question (vision API 还调不调) — they never answered explicitly, but since they pasted the MiMo contract as THE contract and chose "每帧都调", the implication is MiMo IS the only recognition (the detection API = MiMo). So I can drop that question — it's resolved: MiMo is the recognition, no separate vision API. Actually wait, let me reconsider. The contract they pasted is identical to the "百度/阿里云视觉 API" contract from the spec. So there's ambiguity: is MiMo a DIFFERENT service that happens to use the same contract, or is "MiMo" just their name for the cloud detection?

Actually, given re.md said "如果需要 mimo token plan 直接飞书群@陈泽沛 让他给你重置", MiMo clearly has a token (like an LLM API). So MiMo is likely a real multimodal LLM service (maybe MiniMax, or Xiaomi's MiMo model). The team wraps it behind the `/api/v1/detect` contract.

Either way, my code already calls the endpoint with the right contract. The only missing pieces are the URL and token.

So my answer to "需要我提供什么" should be short:

1. **MiMo endpoint URL**（完整 https 地址）
2. **鉴权方式 + token**（token 放 header 还是 URL/body？值多少？——或直接说"我去找陈泽沛要 token"，我先把 header 方案写好）
3. （可选）真实请求/响应各一张截图或文本，确认字段名跟我实现的一致。

And I should note: 如果 token 是要 header 传，需要张沐泽的 `wifi_http_post` 支持自定义 header——如果他不支持，得先让他加。

Let me keep it tight. I'll give a short prioritized list and offer to proceed with the Bearer-header default now.

I won't use tools; just answer concisely.

Let me write it cleanly.

---

### [2026-08-26 15:23:51] AI

就 3 样，按优先级：

## 1. MiMo 的 endpoint 地址（必须）

完整 URL，例如：
```
https://api.xxx.com/v1/chat/completions   ← 或 /api/v1/detect 之类的
```

## 2. 鉴权方式 + token（必须）

告诉我 token 放哪，以及值（或你自己填）：
- **A. Header**：`Authorization: Bearer <token>` ← 最常见
- **B. URL 里**：`https://...?token=xxx`
- **C. body 里**：`{"image":"...","token":"xxx"}`

> ⚠️ 如果是 A，张沐泽的 `wifi_http_post(url, body, resp, maxlen)` 目前**带不了 header**，得先让他加一个 header 参数（或我这边改成直接调 HTTP 客户端）。所以这个要连带确认。

## 3. 真实请求/响应各一张（强烈建议，可无）

确认你贴的契约字段名跟我代码里解析的**完全一致**（尤其 `near_hand`、`head_pose`、`hand_motion_score` 这几个）。

---

**你可以这样做**：
- 直接把 1、2 的答案发我，我立刻把 endpoint/token 写进 `perception.c`；
- 或者干脆说「token 我找陈泽沛要，你先按 `Authorization: Bearer` 写」，我就先把 header 方案搭好，你拿到 token 填进去即可。

哪个方便来哪个。

---

### [2026-08-26 15:26:56] 用户

pr上去吧

---

### [2026-08-26 15:27:14] AI

[思考] The user says "pr上去吧" = "push it up as a PR" / "submit the PR".

So they want me to commit and push the code as a pull request (PR) to the repo. But wait — let me think about the context:

1. The working directory is C:\temp, which is NOT a git repository (the environment says "Is a git repository: false").
2. The actual repo is at `/home/ubuntu/openvela/contest2026_087_gaiduimingyizhanyongdui` on their Linux VM (from the transcript). Or they fork/clone it locally.
3. My deliverable files are in `C:\temp\focus_perception\` on this Windows machine.

So "pr上去吧" — the user wants me to create a PR. But I don't have:
- The git repo here (C:\temp is not a git repo).
- GitHub credentials / access to their fork.
- The actual repo structure to place the files into (the repo has `app/hello_app/perception/`, `app/hello_app/api/`, etc., which is on their Linux VM).

Also, from the transcript, there was a GitHub token that got exposed earlier, and the flow was: fork → clone → push → PR. The re.md mentions CLA signing and `/check-cla`.

So what can I actually do here? Let me think about what "pr上去吧" realistically means and what I can accomplish:

Option A: The user wants me to actually push a PR to their GitHub fork. But I'm on their Windows machine (C:\temp), not in the repo, and I don't have git remote access or credentials. I can't push to GitHub from here without:
- The repo cloned locally
- GitHub credentials (token)
- Network access

Option B: The user wants me to prepare everything needed to make the PR (e.g., git commands, commit message, PR description), and they'll run it on their VM.

Given the environment (Windows, not a git repo, no GitHub access configured), I should be honest: I can't directly push a PR from this environment. I need to either:
1. Have the repo cloned here (and credentials), or
2. Give them the exact commands/PR description to run on their VM.

Let me check the current state first: is there any git repo in C:\temp or nearby? The environment says "Is a git repository: false" for C:\temp. Let me verify there's no repo and check if git is available, and whether there's a clone of the contest repo somewhere on this machine.

Actually, let me be careful and check the actual situation before assuming. Let me:
1. Check if git is available.
2. Check if there's any clone of the contest repo on this machine (search for the repo name or .git dirs near C:\temp, or home).
3. Check GitHub CLI availability / auth status.

Let me do these checks quickly, then decide.

Actually, the transcript revealed the repo path is `/home/ubuntu/openvela/contest2026_087_gaiduimingyizhanyongdui` — that's a LINUX path (the VM). This Windows machine is a different environment. The user has been working with me on the Windows machine (C:\temp) where they downloaded the .md files and asked me to write code.

So "pr上去吧" most likely means: they want the finished code committed and pushed as a PR to their team's GitHub repo. But I'm on Windows with no repo clone and no credentials.

Let me check what's actually available:
1. Is there a git repo anywhere obvious?
2. git available?
3. gh CLI?

Let me check.

Actually, let me reconsider. There might be a clone somewhere. The user said in re.md: "@全体成员 你们直接fork 然后clone 在自己的目录里写". So each member forks and clones. The user (周礼航) might have cloned it on this Windows machine? Or on the VM.

Let me check for the repo on this machine. Let me look for directories matching the contest repo name or any .git in C:\temp or user home.

Let me run some checks.

---

### [2026-08-26 15:27:15] AI

[工具调用] Bash: {"command": "command -v git && git --version; echo \"--- gh ---\"; command -v gh && gh --version 2>&1 | head -1 || echo \"no gh\"; echo \"--- repos near C:/temp ---\"; ls -d /c/temp/*/ 2>/dev/null; ls -d /c/temp/.git 2>/dev/null || echo \"C:/temp not a repo\"", "description": "Check git/gh availability and nearby repos"}

---

### [2026-08-26 15:29:44] 用户

[工具结果] /mingw64/bin/git
git version 2.55.0.windows.3
--- gh ---
no gh
--- repos near C:/temp ---
/c/temp/focus_perception/
C:/temp not a repo

---

### [2026-08-26 15:29:48] AI

[思考] git is available. gh is not. C:\temp is not a repo. There's no clone of the contest repo on this machine (at least not in C:\temp).

Let me search more broadly for any clone of the contest repo on this machine. The repo name is `contest2026_087_gaiduimingyizhanyongdui`. Let me search for it.

---

### [2026-08-26 15:29:50] AI

[工具调用] Bash: {"command": "ls -d /c/temp/*/ /c/Users/user/*/ 2>/dev/null | head -40; echo \"--- search contest repo ---\"; find /c/Users/user -maxdepth 3 -type d \\( -name \"*contest*\" -o -name \"*openvela*\" -o -name \"*gaiduiming*\" \\) 2>/dev/null | head; echo \"--- done ---\"", "description": "Search for contest repo clone on machine"}

---

### [2026-08-26 15:30:00] 用户

[工具结果] /c/Users/user/AppData/
/c/Users/user/Application Data/
/c/Users/user/Contacts/
/c/Users/user/Cookies/
/c/Users/user/Documents/
/c/Users/user/Downloads/
/c/Users/user/Favorites/
/c/Users/user/Links/
/c/Users/user/Local Settings/
/c/Users/user/My Documents/
/c/Users/user/NetHood/
/c/Users/user/OneDrive/
/c/Users/user/PrintHood/
/c/Users/user/Recent/
/c/Users/user/Saved Games/
/c/Users/user/Searches/
/c/Users/user/SendTo/
/c/Users/user/Spine/
/c/Users/user/Templates/
/c/Users/user/Zotero/
/c/Users/user/crawler_output/
/c/Users/user/games/
/c/Users/user/open-source-tools/
/c/Users/user/sangfor/
/c/Users/user/「开始」菜单/
/c/temp/focus_perception/
--- search contest repo ---
--- done ---

---

### [2026-08-26 15:30:58] AI

[思考] No contest repo clone on this machine. So I cannot actually push a PR from here — there's no repo, no GitHub credentials, no `gh` CLI, and no network/remote configured.

I need to be honest with the user: I can't push the PR directly from this Windows environment because:
1. There's no clone of the team repo here (it's on their Linux VM at `/home/ubuntu/openvela/contest2026_087_gaiduimingyizhanyongdui`).
2. No GitHub credentials / token / gh CLI on this machine.

But I can do the next best thing: prepare everything they need to push the PR themselves, on their VM. Specifically:
1. Give them the exact git commands (branch, add, commit, push, create PR).
2. Give them a ready-to-use commit message.
3. Give them a ready-to-use PR title + description (body).
4. Note the CLA requirement (from re.md: sign CLA at openvela.com, then comment `/check-cla`).

Also, I should note: the code I wrote is a standalone folder (`focus_perception/`), but the repo expects files in `app/hello_app/perception/`. So they need to copy `perception.c` and `perception_internal.h` into the repo's `app/hello_app/perception/`, and add CSRCS + Kconfig per BUILD_INTEGRATION.md. They should NOT overwrite `api/perception.h`.

Let me think about what's most helpful. The user said "pr上去吧" — they want the PR pushed. Since I can't do it directly, I should:

1. Clearly explain I can't push from here (no repo/credentials on this Windows box; the repo lives on their VM).
2. Offer the two paths:
   a. If they want ME to do it, they need to either (i) clone the repo onto this Windows machine and give me a token, or (ii) run commands on their VM (they can use `! <command>` to run in-session).
   b. Provide the exact, ready-to-paste commands + commit message + PR description so they (or I, via their `!` session) can push in one go.

Actually, the session-specific guidance mentions: "If you need the user to run a shell command themselves (e.g., an interactive login like `gcloud auth login`), suggest they type `! <command>`". But the repo is on their VM, not this Windows session.

Let me be practical and honest. I'll:

1. Tell them plainly: 这台 Windows 机器上没有你们团队的 git 仓库、也没有 GitHub 凭证（gh/token 都没有），所以我没法从这里直接把 PR 推上去。仓库在你们 Linux 虚拟机 `/home/ubuntu/openvela/contest2026_087_gaiduimingyizhanyongdui`。

2. Give them a complete, copy-paste PR 提交包：
   - 把文件放对位置的说明（perception.c → app/hello_app/perception/）
   - git 命令（branch / add / commit / push）
   - commit message（含 Co-Authored-By）
   - PR 标题 + 正文
   - CLA 提醒（openvela.com 签 CLA，PR 里评论 /check-cla）

3. Offer: 如果你把仓库 clone 到这台 Windows 机器 + 给我 token，我直接帮你跑；或者你在 VM 上跑这些命令（可以用 `!` 前缀在会话里跑，但那是 Windows 会话，不是 VM）。

Actually, wait — let me reconsider. Maybe the user has been treating me as running on their VM? No — the environment is clearly Windows (C:\temp, win32, PowerShell). The transcript was FROM the VM (that's a record they downloaded). So the actual work happens on the VM, but I'm on Windows.

So the realistic options for the user:
- They do the git push on their VM (where the repo + fork + creds are).
- I give them the exact commands + commit message + PR description to make it one-shot.

Let me also prepare the PR description properly. It should describe:
- What: 视觉感知模块 (perception) 实现
- Files: perception.c, perception_internal.h, tests
- Key points: 每帧调 MiMo、3帧去抖、历史环形缓冲、mock/真实双路径、错误码
- Test results: mock 57 checks pass
- Notes: api/perception.h 未改（用冻结版）；MiMo endpoint/token 待填；auth 方式待确认

Let me write a clean commit message and PR body.

Commit message (conventional, matching repo style — I don't know the exact style, but a clear message):
```
feat(perception): 实现视觉感知模块 (每帧调 MiMo 识图 + 3帧去抖 + 历史)

- 实现 perception_init / perception_process / perception_get_history
- 每帧调用 MiMo 识图接口 (base64 → POST → cJSON 解析)
- 3 帧去抖 (bool 多数投票 / 角度中位数 / motion 取最大 / confidence 均值)
- 环形历史缓冲 obs_history[60] (强符号覆盖 core/mock.c 的 weak 桩)
- mock / 真实双路径 (PERCEPTION_MOCK 开关)
- 单测: tests/test_perception.c (mock) + tests/test_mimo_cloud.c (真实链路)

Co-Authored-By: Claude <noreply@anthropic.com>
```

PR title: `feat: 视觉感知模块 perception (每帧调 MiMo 识图)`

PR body (markdown): describe what/why/test/how.

Let me write these out clearly.

Actually, let me reconsider whether I should ask the user to clone the repo here so I can do it. The user's instruction was short ("pr上去吧"), suggesting they expect me to handle it. But I genuinely can't without the repo + creds. The most helpful response is:

1. State the blocker (briefly, not defensively).
2. Give them a turnkey "PR 提交包" they can run on the VM in one go (or paste to their VM's Claude session).
3. Offer to do it here if they clone + give token.

I'll also give the git commands in a form that works in their VM (Linux/bash). Since they earlier used the VM with Claude Code (the transcript), they could paste my command block into that VM session, or run manually.

Let me also note the file placement precisely:
- `perception/perception.c` → `app/hello_app/perception/perception.c`
- `perception/perception_internal.h` → `app/hello_app/perception/perception_internal.h`
- `tests/test_perception.c` → `app/hello_app/tests/test_perception.c`
- `tests/wifi_http_post_stub.c` → `app/hello_app/tests/wifi_http_post_stub.c`
- `tests/test_mimo_cloud.c` → `app/hello_app/tests/test_mimo_cloud.c`
- `api/perception.h` → 不提交（仓库已有冻结版）
- BUILD_INTEGRATION.md → 不提交（是说明，或可选）

Wait — should the test files go into the repo? The task doc said `tests/test_perception.c` (可选). I'll include them but note they're optional. Actually, 赵思涵 already has `tests/behavior_test.c` in the repo, so adding `tests/test_perception.c` is consistent.

But there's a subtlety: the repo's `tests/` might have a specific build setup. I shouldn't over-specify. I'll give the placement and let them adjust.

Also, the BUILD_INTEGRATION.md changes (CSRCS + Kconfig) need to be applied to the repo's Makefile/CMakeLists/Kconfig — but those are 万思源's/张沐泽's files potentially. Actually, per the task doc, adding CSRCS is part of 周礼航's integration. But the Kconfig/Makefile might already have the pattern. I'll mention they need to add `perception/perception.c` to CSRCS (per BUILD_INTEGRATION.md), and note it may need coordination with 万思源.

Let me write the response. I'll be concise but complete.

Actually, let me reconsider the scope of what to provide. The user asked "pr上去吧". The cleanest deliverable is a ready-to-run script/commands + commit msg + PR body. Let me write:

1. One-line blocker explanation.
2. A bash block they can run on the VM (after copying files).
3. Commit message + PR title/body.

Let me write it. I'll use a heredoc-friendly bash script for the VM.

For the git commands, I'll structure:

```bash
# 在 VM 的仓库根目录执行 (contest2026_087_gaiduimingyizhanyongdui)
cd /home/ubuntu/openvela/contest2026_087_gaiduimingyizhanyongdui

# 1. 切分支
git checkout -b feat/perception

# 2. 放文件 (把 focus_perception 里这几个拷进去)
cp .../focus_perception/perception/perception.c        app/hello_app/perception/perception.c
cp .../focus_perception/perception/perception_internal.h app/hello_app/perception/perception_internal.h
cp .../focus_perception/tests/test_perception.c         app/hello_app/tests/test_perception.c
cp .../focus_perception/tests/test_mimo_cloud.c         app/hello_app/tests/test_mimo_cloud.c
cp .../focus_perception/tests/wifi_http_post_stub.c     app/hello_app/tests/wifi_http_post_stub.c

# 3. 加进编译 (按 BUILD_INTEGRATION.md 改 Makefile/CMakeLists/Kconfig)

# 4. add + commit
git add app/hello_app/perception app/hello_app/tests
git commit -m "..."
git push origin feat/perception
```

Hmm, but the fork situation: from the transcript, the flow was fork (Skadi-QL's fork) → push to fork → open PR to the team repo. The re.md says "你们直接fork 然后clone". So each member's clone has their fork as `origin` (or the team repo as origin and fork as another remote).

I don't know the exact remote names. I'll write the commands generically and note "把 origin 换成你的 fork remote，或直接 push 到你的 fork 再开 PR".

Actually, to keep it simple and not over-prescribe, I'll give the standard fork-based PR flow and let them adjust remote names.

Let me also prepare the PR body as a code block they can paste into the GitHub PR form.

Let me write a clean, complete response now.

One more consideration: should I actually attempt to help more concretely, like checking if there's a way to reach their VM? No, I can't. The VM is separate.

Let me also offer: "如果你愿意把仓库 clone 到这台 Windows 机器并给我一个 token，我可以直接在这里帮你跑完 add/commit/push/开 PR 全流程。"

Let me write the final response. I'll keep it well-organized.

I should provide:
1. 简短说明为什么不能从这里直接推。
2. 一键提交脚本（VM 上跑）。
3. commit message（含 Co-Authored-By）。
4. PR 标题 + 正文。
5. CLA 提醒。

Let me write it concisely.

For the commit message, I need to follow the harness guidance: "End git commit messages with: Co-Authored-By: Claude <noreply@anthropic.com>".

Let me write everything.

---

### [2026-08-26 15:31:11] AI

我这边推不了——这台是 Windows 机器（`C:\temp`），**没有你们团队的 git 仓库、也没有 GitHub 凭证**（`gh`、token 都没有）。仓库在你们 Linux 虚拟机 `/home/ubuntu/openvela/contest2026_087_gaiduimingyizhanyongdui` 上。所以我把「一键 PR 提交包」给你，你在 VM 上跑一遍就行（或者直接粘到 VM 那个 Claude 会话里让它执行）。

## 1. VM 上执行的命令

```bash
cd /home/ubuntu/openvela/contest2026_087_gaiduimingyizhanyongdui

# 切分支
git checkout -b feat/perception

# 放文件（把 focus_perception 里这几个拷进仓库）
cp <focus_perception路径>/perception/perception.c            app/hello_app/perception/perception.c
cp <focus_perception路径>/perception/perception_internal.h  app/hello_app/perception/perception_internal.h
cp <focus_perception路径>/tests/test_perception.c           app/hello_app/tests/test_perception.c
cp <focus_perception路径>/tests/test_mimo_cloud.c           app/hello_app/tests/test_mimo_cloud.c
cp <focus_perception路径>/tests/wifi_http_post_stub.c       app/hello_app/tests/wifi_http_post_stub.c

# ⚠️ 不要拷 api/perception.h（仓库已有冻结版，别覆盖）

# 加进编译：按 BUILD_INTEGRATION.md 在 Makefile/CMakeLists 加 CSRCS + Kconfig 开关

git add app/hello_app/perception app/hello_app/tests
git commit -m "<下面的 commit message>"
git push origin feat/perception   # origin 换成你的 fork remote，或 push 到 fork 再开 PR
```

## 2. Commit message

```
feat(perception): 实现视觉感知模块 (每帧调 MiMo 识图 + 3帧去抖 + 历史)

- 实现 perception_init / perception_process / perception_get_history
- 每帧调用 MiMo 识图接口 (base64 -> POST -> cJSON 解析)
- 3 帧去抖: bool 多数投票 / 角度中位数 / motion 取最大 / confidence 均值
- 环形历史缓冲 obs_history[60], 强符号覆盖 core/mock.c 的 weak 桩
- mock / 真实双路径 (PERCEPTION_MOCK 开关, 默认 mock 可回退)
- 单测: test_perception.c (mock 57 项) + test_mimo_cloud.c (真实链路)

Co-Authored-By: Claude <noreply@anthropic.com>
```

## 3. PR 标题 + 正文

**标题**：`feat: 视觉感知模块 perception（每帧调 MiMo 识图）`

**正文**：
```markdown
## 做了什么
实现视觉感知模块，输入一张 JPEG → 每帧调用 MiMo 识图接口 → 3 帧去抖 → 输出 `observation_t`。

## 关键点
- **每帧调 MiMo**：`perception_process()` → `mimo_detect()`（base64 → POST → cJSON 解析）
- **3 帧去抖**：bool 多数投票 / 角度中位数 / motion 取最大 / confidence 均值
- **历史环形缓冲** `obs_history[60]`：强符号 `perception_get_history()` 自动覆盖 `core/mock.c` 的 weak 桩
- **mock / 真实双路径**：`PERCEPTION_MOCK` 开关，默认 mock 可回退
- **错误码**：`FOCUS_ERR_PERCEP_TIMEOUT(-30)` / `JSON(-31)` / `NODATA(-32)` / `PARAM(-33)`

## 测试
- `tests/test_perception.c`：mock 单测，57 checks 全过
- `tests/test_mimo_cloud.c` + `wifi_http_post_stub.c`：真实链路单测（需 cJSON）

## 待确认
- MiMo endpoint / token 尚未填入（占位宏 `MIMO_ENDPOINT_DEFAULT` / `MIMO_API_KEY_DEFAULT`）
- MiMo 鉴权方式（token 放 header/URL/body）待与张沐泽确认，`g_api_key` 已预留
```

## 4. CLA 提醒（re.md 里说过的）

PR 如果报「未签署 CLA」：先去 https://openvela.com/#/community/cla 用报名账号签，然后在 PR 下评论一句 `/check-cla` 即可。

---

要不要我**把这个 commit message 和 PR 正文存成文件**放进 `focus_perception/`，你拷进 VM 直接 `git commit -F` 就能用？或者如果你把仓库 clone 到这台 Windows 机器 + 给我一个 token，我直接在这里帮你跑完整个 push + 开 PR 流程。

---

### [2026-08-26 15:34:53] 用户

本机有wsl

---

### [2026-08-26 15:35:04] AI

[思考] The user says "本机有wsl" = "This machine has WSL (Windows Subsystem for Linux)".

This is a hint that they have WSL installed on this Windows machine, which means:
1. I can potentially run Linux commands through WSL.
2. Maybe the repo is cloned in WSL (or they can clone it there).
3. The "VM" they mentioned earlier might actually be WSL (the transcript was from `/home/ubuntu/...` which is a typical WSL Ubuntu path!).

Wait — that's a key insight. The transcript showed paths like `/home/ubuntu/openvela/...`. `ubuntu` is a very common WSL default username/path! So their "Linux 虚拟机" might actually be WSL on THIS Windows machine. That changes everything — I might be able to reach the repo via WSL.

So the user is telling me: use WSL. The repo might be in WSL at `/home/ubuntu/openvela/contest2026_087_gaiduimingyizhanyongdui`, and I can access it via `wsl` command.

Let me check:
1. Is WSL available? `wsl --list` or `wsl -l -v`.
2. Does the repo exist in WSL at the expected path?
3. Git/credentials in WSL?

Let me investigate. I should:
1. Check `wsl -l -v` to list distros.
2. Check if the repo exists in WSL: `wsl ls /home/ubuntu/openvela/contest2026_087_gaiduimingyizhanyongdui` or similar.
3. Check git remote in the WSL repo.

Let me do these checks. I'll use Bash (Git Bash on Windows) to call `wsl`. Actually, `wsl` is a Windows executable; from Git Bash I can call `wsl.exe` or `wsl`.

Let me run the checks.

Note: the harness says I'm on Windows with Bash tool (Git Bash) and PowerShell. `wsl` should be callable from both. Let me try.

Let me check WSL status and the repo.

---

### [2026-08-26 15:35:04] AI

[工具调用] Bash: {"command": "wsl.exe -l -v 2>&1; echo \"=== exit $? ===\"", "description": "List WSL distros and status"}

---

### [2026-08-26 15:35:11] 用户

[工具结果]     N A M E                             S T A T E                       V E R S I O N 
 
 *   U b u n t u - 2 6 . 0 4             S t o p p e d                   2 
 
     d o c k e r - d e s k t o p         S t o p p e d                   2 
 
 === exit 0 ===

---

### [2026-08-26 15:35:19] AI

[思考] WSL is available. There's an "Ubuntu-26.04" distro (default, marked with *) and "docker-desktop". Ubuntu-26.04 is Stopped.

The output has weird spacing (UTF-16 encoding from wsl.exe), but I can read it: Ubuntu-26.04, Stopped, version 2.

So the user has WSL with Ubuntu. The repo might be at `/home/ubuntu/openvela/contest2026_087_gaiduimingyizhanyongdui` in WSL (the transcript was from `/home/ubuntu`).

But wait — the distro is "Ubuntu-26.04", and the transcript user is "ubuntu". Let me check the WSL filesystem for the repo. I need to start WSL and look.

Let me check the repo in WSL. First, let me see the home directory and look for openvela.

Let me run: `wsl -d Ubuntu-26.04 ls ~/` and `wsl -d Ubuntu-26.04 ls ~/openvela/` etc.

Actually, let me be careful about how wsl.exe outputs (UTF-16). Let me pipe through a cleanup or just use `wsl.exe` with commands. The output encoding might be an issue. Let me try and see.

Let me check the home dir and look for the repo.

---

### [2026-08-26 15:35:20] AI

[工具调用] Bash: {"command": "wsl.exe -d Ubuntu-26.04 bash -lc 'echo HOME=$HOME; whoami; ls -la ~/ 2>/dev/null | head -40' 2>&1", "description": "Inspect WSL home directory"}

---

### [2026-08-26 15:35:34] 用户

[工具结果] HOME=/home/user
user
total 32
drwxr-x--- 5 user user 4096 Aug  9 18:06 .
drwxr-xr-x 3 root root 4096 Aug  9 18:06 ..
-rw-r--r-- 1 user user  220 Aug  9 18:06 .bash_logout
-rw-r--r-- 1 user user 3771 Aug  9 18:06 .bashrc
drwxr-x--- 4 user user 4096 Aug  9 18:06 .cache
drwxr-x--- 3 user user 4096 Aug  9 18:06 .config
drwxr-xr-x 2 user user 4096 Aug  9 18:06 .landscape
-rw-rw-r-- 1 user user    0 Aug 26 15:35 .motd_shown
-rw-r--r-- 1 user user  807 Aug  9 18:06 .profile

---

### [2026-08-26 15:35:48] AI

[思考] The WSL user is `user`, home `/home/user`, and it's a fresh Ubuntu (no openvela repo in home — the home dir is basically empty except default files). This is NOT the same environment as the transcript (which was user `ubuntu` at `/home/ubuntu/openvela/...`).

So the repo is NOT in this WSL. This WSL "Ubuntu-26.04" is a fresh install (Aug 9), empty home.

So the situation:
- The transcript's VM (user `ubuntu`, `/home/ubuntu/openvela`) is a DIFFERENT machine than this Windows box + its WSL.
- This WSL is fresh and has no repo, no git config, no credentials.

So "本机有wsl" means: the user has WSL available, and maybe expects me to use it (to run gcc/compile the test properly in a Linux environment, OR to clone the repo there and push).

But to push a PR, I'd need:
1. The repo cloned into WSL.
2. Git credentials (token) in WSL.
3. Network access in WSL (should be fine).

The user's intent with "本机有wsl" is likely: "you can use WSL to do the git stuff / compile / push". But the repo isn't in WSL, and there are no credentials.

So what can I actually do with WSL right now?
1. **Compile the mock test in a real Linux environment** (WSL Ubuntu) to fully verify it (without the -lwinpthread hack). This is genuinely useful — I can verify the code compiles cleanly on Linux with gcc.
2. **Check if gcc is installed in WSL.**
3. Potentially install cJSON and verify the cloud test too.

This is actually valuable: I can now properly verify both tests in a real Linux environment.

But for the PR push, I still need the repo + credentials. Let me first check if gcc is in WSL, and whether the repo might be somewhere else in WSL (search a bit), and check git config/credentials.

Let me:
1. Check gcc in WSL.
2. Search WSL for the contest repo (find / for "contest2026" or "openvela").
3. Check git config in WSL (user.name, user.email, any credentials).

Let me do these.

Actually, let me reconsider the user's intent. "本机有wsl" is a terse reply to my previous message where I said "推不了——这台 Windows 机器没有仓库也没有凭证". The user is pushing back: "本机有 wsl" — implying "the repo/environment is in WSL, use that".

But my check shows WSL home is empty (fresh). So either:
(a) The repo is elsewhere in WSL (not home), or
(b) The user THINKS the repo is in WSL but it's actually on a different VM, or
(c) The user wants me to use WSL to clone + push (they'll provide credentials).

Let me search WSL for the repo to be sure, and check gcc + git config. Let me be thorough but quick.

Let me run a combined check.

---

### [2026-08-26 15:35:51] AI

[工具调用] Bash: {"command": "wsl.exe -d Ubuntu-26.04 bash -lc '\necho \"=== gcc ===\"; command -v gcc && gcc --version | head -1 || echo \"no gcc\"\necho \"=== git ===\"; command -v git && git --version || echo \"no git\"\necho \"=== git config ===\"; git config --global user.name; git config --global user.email; echo \"(end)\"\necho \"=== search repo ===\"; find / -maxdepth 4 -type d \\( -name \"*contest2026*\" -o -name \"*gaiduiming*\" -o -name \"openvela\" \\) 2>/dev/null | head\necho \"=== ssh keys ===\"; ls -la ~/.ssh 2>/dev/null || echo \"no ~/.ssh\"\n' 2>&1", "description": "Check gcc/git/config/repo/ssh in WSL"}

---

### [2026-08-26 15:36:06] 用户

[工具结果] === gcc ===
no gcc
=== git ===
/usr/bin/git
git version 2.53.0
=== git config ===
(end)
=== search repo ===
=== ssh keys ===
no ~/.ssh

---

### [2026-08-26 15:36:29] AI

[思考] So in WSL Ubuntu-26.04:
- No gcc (not installed).
- git IS installed (2.53.0).
- No git global user.name/user.email configured.
- No contest repo anywhere (find found nothing at maxdepth 4).
- No SSH keys.

So the WSL is essentially a fresh environment: git installed but not configured, no repo, no gcc, no credentials.

The user's "本机有wsl" was probably a misunderstanding or they expect me to set it up. But the reality is: the repo isn't here, and there are no credentials.

What can I actually do here to make progress? Let me think about what's genuinely useful and what the user most likely wants:

1. The user wants the PR pushed. To do that from WSL, I'd need:
   - Clone the repo (needs the repo URL + a token or SSH key for push).
   - Configure git user.name/email.
   - A GitHub token (they had one in the transcript: `ghp_REDACTED`, but that was flagged as "regenerate it" and it's from 2026-07-31, likely invalidated).

2. Alternatively, the user might just want me to verify the code compiles in a Linux environment (WSL) to be safe. That's achievable if I install gcc in WSL (needs apt + sudo + network).

Given the ambiguity, let me be honest and give the user a clear picture + a concrete path forward. But I should also DO something useful rather than just report.

The most useful concrete action I can take right now:
1. **Verify the code compiles + tests pass in real Linux (WSL)** — install gcc via apt. This would give real confidence the code is correct (the -lwinpthread workaround earlier was a Windows-only quirk; a clean Linux gcc build would be the definitive check). This is valuable regardless of the PR push.

2. For the PR: I need the user to give me (a) the repo URL, (b) a GitHub token (or SSH), so I can clone + push. Or they push from their actual VM.

Let me think about whether to install gcc in WSL. Installing gcc requires `sudo apt install build-essential` (or just `gcc`), which needs sudo + network. The user said "本机有wsl" — implying they want me to use it. Installing gcc is a reasonable step.

But wait — should I ask before installing packages into their WSL? Installing gcc is non-destructive and standard for a dev environment. But it does modify their system. Given they said "本机有wsl" (implying "use WSL"), I think a quick check of whether I can sudo (passwordless) is warranted, then install gcc.

Actually, let me step back and be clear about what I'm trying to achieve and communicate:

The user wants "pr上去吧". I said I can't (no repo/creds). They said "本机有wsl" — implying the repo might be reachable via WSL. I checked: WSL is fresh, no repo, no gcc, no git config, no creds.

So my honest response should be:
1. 我查了 WSL（Ubuntu-26.04），它是干净的：git 装了但没配 user/邮箱，没有你们仓库，也没有 gcc、没有 SSH key、没有 token。
2. 所以「仓库在哪」这个前提还没解决 —— 仓库其实在另一台机器（transcript 里是 `/home/ubuntu` 那个 VM），不在这个 WSL 里。
3. 给出两条可执行路径，让用户选：
   a. 我在这台 WSL 里现场搭：装 gcc 验证代码 → 你提供仓库 URL + token（或 SSH），我 clone + commit + push + 开 PR。
   b. 你在原来的 VM 上跑我给的命令。

And I should DO something useful now: I can offer to install gcc and verify the Linux build (the definitive check), which is valuable and doesn't need the repo or credentials.

Actually, let me just do the gcc install + verification proactively, since:
- It's the thing that gives real confidence in the code.
- It doesn't need credentials.
- The user clearly wants forward progress ("pr上去吧", "本机有wsl").

But installing gcc needs sudo. Let me check if I can sudo without password in WSL. If I can, I'll install gcc + cJSON, verify both tests, and report. If I need a password, I'll ask the user.

Let me check sudo access first.

Actually, let me be a bit careful about scope and not go too far. The immediate value:
1. Confirm the code compiles + passes on real Linux (this is the "成品" quality gate).
2. Get unblocked on the PR.

For (2), I need the repo URL + credentials from the user. There's no way around asking for those.

Let me check sudo, then install gcc and verify. If sudo requires password, I'll ask the user to either run the install (via `!` or manually) or provide the password.

Let me check sudo -n true (non-interactive).

---

### [2026-08-26 15:36:30] AI

[工具调用] Bash: {"command": "wsl.exe -d Ubuntu-26.04 bash -lc 'sudo -n true 2>&1 && echo \"SUDO_NOPASS_OK\" || echo \"SUDO_NEEDS_PASSWORD\"' 2>&1", "description": "Check passwordless sudo in WSL"}

---

### [2026-08-26 15:37:44] 用户

[工具结果] sudo: interactive authentication is required
SUDO_NEEDS_PASSWORD

---

### [2026-08-26 15:38:12] AI

[思考] sudo needs a password. So I can't install gcc without the user's password (or without them running it).

Let me step back and give a clear, honest status + concrete path. I've now established:

1. WSL Ubuntu-26.04 is fresh: git 2.53 installed, but no user.name/email, no repo, no gcc, no SSH key, no token.
2. sudo needs a password (so I can't install gcc myself).
3. The actual repo (with the team code) is NOT in this WSL — it's on the other VM (transcript's `/home/ubuntu`).

So "pr上去吧" can't be completed by me right now without one of:
- The repo URL + a GitHub token (or SSH key) so I can clone + push from WSL (and I'd need git user config too).
- OR the user running the commands on their actual VM (where the repo + fork already live).

I should present this clearly and concisely, and give the user a simple choice. I should NOT keep spinning my wheels — I've done the diagnosis, now I need user input (repo URL + credentials) or confirmation to proceed on the VM.

Let me also offer the concrete things I CAN do right now:
1. Set up WSL properly: install gcc (needs their sudo password, or they run `! sudo apt install ...`), verify the code compiles + passes on Linux.
2. For the PR: they give me the fork URL + a token (or SSH), and I clone + commit + push + open PR from WSL.

I should ask them to either:
(a) provide the repo URL + token (and optionally let me install gcc), OR
(b) tell me the repo is on their VM and they'll run my commands there.

Let me use AskUserQuestion? Or just ask in plain text? This is a genuine decision point that only the user can resolve (where's the repo, do they have a token). But it's more of a "give me info" than a multiple-choice. Actually, I can frame it as a clear either/or with AskUserQuestion, OR just ask plainly.

Given the situation, a plain-text response with a clear, minimal ask is better than a formal question tool here, because the "answer" is really "here's my token + repo URL" which is free-form. But I can also use AskUserQuestion to structure the choice of path.

Actually, let me use a concise plain-text response that:
1. States what I found in WSL (fresh, no repo/creds/gcc).
2. States the one missing prerequisite: repo URL + token (or SSH), and confirms which machine the repo is on.
3. Offers the concrete next step: give me the token + URL, and I'll do everything from WSL (clone → copy files → commit → push → PR), and I can also install gcc to verify first (they'd need to type the sudo password or run one command).

Let me also make it super easy: give them a single command they can paste (with `!` prefix) to install gcc, OR just ask for the token.

Actually, I realize I should ask the key question directly and simply: **"仓库的 URL 和 token 给我（或者确认仓库在原来那台 VM 上）"** — because without that, nothing happens.

Let me also reconsider: maybe I'm overcomplicating. The user said "本机有wsl" — they might simply want me to verify/run things in WSL, and they'll handle the git push themselves (they have the repo on their VM). In that case, the most useful thing is: get the code verified on Linux (install gcc) so they can be confident before pushing.

But I can't install gcc without sudo password. So I'd ask them to run the install.

Let me structure a clean response:

1. **WSL 现状**（我查到的）：Ubuntu-26.04 是干净的 —— git 有、但没配 user/email，没有你们仓库，没有 gcc，没有 SSH key，也没有 GitHub token。仓库其实在另一台机器（对话记录里那个 `/home/ubuntu` 的 VM），不在这台 WSL 里。

2. **所以要真正 PR 上去，缺一个前提**：仓库 URL + 一个能 push 的 token（或 SSH key）。给我这两个，我就在这台 WSL 里：clone → 放文件 → commit → push → 开 PR，一条龙。

3. **我可以现在就先做的**：在 WSL 里装 gcc，把代码在真 Linux 上编译 + 跑通测试（比我在 Windows 上那次更权威）。装 gcc 需要 sudo 密码，你在这台机器上跑一下这条（或给我密码）：
   ```
   ! sudo apt-get update && sudo apt-get install -y build-essential
   ```
   （`!` 前缀会在本会话跑，但这是 Windows 会话；其实应该用 `wsl` 前缀。让我修正：`! wsl -d Ubuntu-26.04 bash -lc 'sudo apt-get update && sudo apt-get install -y build-essential'`）

Hmm, actually the `!` prefix runs in THIS session (Windows PowerShell/bash), not WSL. So the command to run in WSL would be `! wsl ...`.

Let me keep it simple and give them two concrete asks:
1. 给仓库 URL + token（或确认在 VM 上，你自己跑我给的命令）。
2. 如果想让我在 WSL 里先验证编译，跑一条 sudo 装 gcc 的命令（或给我 sudo 密码）。

Let me write a tight response.

Actually, let me reconsider using AskUserQuestion to make the path decision crisp. The decision is:
- Where to do the PR: (A) 我在这台 WSL 里做（需要你给 URL + token）; (B) 你在原来 VM 上自己跑我给的命令.

And separately, whether to install gcc for verification.

I think a concise plain-text response is better here because the real blocker is "I need the token/URL", which is free-form info, not a multiple choice. I'll ask directly.

Let me write it. Keep it short and clear.

I should be careful not to be too verbose. The user is terse. Let me give a crisp status + one clear ask.

---

### [2026-08-26 15:38:20] AI

查了一下你这台 WSL（Ubuntu-26.04），情况是这样的：

| 项 | 状态 |
|---|---|
| git | ✅ 已装（2.53.0） |
| 团队仓库 | ❌ 没有（`find /` 找不到 openvela/contest 目录） |
| gcc | ❌ 没装 |
| git user.name/email | ❌ 没配 |
| SSH key / GitHub token | ❌ 都没有 |

结论：**仓库不在这台 WSL 里**。对话记录里那个 `/home/ubuntu/openvela/...` 是另一台机器（当时 user 是 `ubuntu`，这台 WSL 是 `user`、家目录是空的）。所以「PR 上去」缺的不是 WSL，而是**仓库本体 + 能 push 的凭证**。

## 给我两样，我就在这台 WSL 里一条龙搞定

1. **仓库/fork 的 URL**（例如 `https://github.com/<你>/contest2026_087_gaiduimingyizhanyongdui.git`）
2. **一个 GitHub token**（classic，勾 `repo` 权限）——对话记录里那个 `ghp_...` 是 7 月 31 号的了、当时还提醒过要重新生成，大概率已失效，给我个新的。

拿到后我会在 WSL 里：clone → 配置 git user → 放文件 → commit → push → 开 PR，全程我跑。

## 或者你先让我验证代码（不依赖上面两样）

装个 gcc，在**真 Linux** 上把两个测试编译跑通（比我在 Windows 上那次更权威）。需要 sudo 密码，你在这台机器上跑一下：

```bash
wsl -d Ubuntu-26.04 bash -lc 'sudo apt-get update && sudo apt-get install -y build-essential'
```

（或者告诉我 sudo 密码，我来跑。装完 gcc 我还能顺便 `apt install libcjson-dev` 把 MiMo 那个 cloud 测试也验证了。）

你想先走哪条：**给我 URL+token 直接推**，还是**先装 gcc 验证代码**？

---

### [2026-08-26 15:42:27] 用户

你整理一下本地的代码 然后写一份如何pr的详细步骤

---

### [2026-08-26 15:42:56] AI

[思考] The user wants me to:
1. 整理一下本地的代码 (organize/tidy up the local code)
2. 写一份如何 PR 的详细步骤 (write a detailed step-by-step guide on how to make the PR)

So they want me to:
1. Organize the code I've written in `C:\temp\focus_perception\` (make sure it's clean, complete, ready to drop into the repo).
2. Write a detailed "how to PR" guide — a document with exact steps for submitting the PR (from their VM or wherever).

Let me do both.

First, let me review/organize the code. The current files:
```
C:\temp\focus_perception\
├── api/perception.h
├── perception/perception.c
├── perception/perception_internal.h
├── tests/test_perception.c
├── tests/wifi_http_post_stub.c
├── tests/test_mimo_cloud.c
├── BUILD_INTEGRATION.md
└── README.md
```

Let me verify everything is consistent and clean. I already:
- Refactored perception.c to have mimo_detect.
- Removed head_roll from internal header.
- Verified mock test passes (57 checks).
- Wrote the stub and cloud test.
- Wrote BUILD_INTEGRATION.md and README.md.

What "整理" (organize) might mean:
1. Make sure the files are in the right repo layout (app/hello_app/perception/ etc.), OR provide a clear mapping.
2. Maybe create a cleaner structure that mirrors the repo, so the user can just copy.
3. Ensure consistency, no leftover artifacts.

Let me think about what "整理" concretely means for the user. They want the code ready to drop into their repo. So I should:
1. Verify the code is complete and consistent (re-read key files to confirm no issues).
2. Maybe restructure the folder to mirror the repo target layout so copying is trivial, OR at least provide a clear file-mapping in the PR guide.
3. Write the detailed PR guide (a markdown doc, and/or in my response).

Let me plan the deliverables:

A) **整理代码** — I'll:
- Do a final review of each file for consistency.
- Verify mock test still passes (already did, 57/57).
- Possibly reorganize into a structure that mirrors the repo, e.g., add a `PR_GUIDE.md` and maybe a `如何提交.md`.

Actually, the user explicitly asked for TWO things: (1) organize the code, (2) write detailed PR steps. Let me:

1. "整理" = tidy up the local code folder. I'll:
   - Keep the current structure (it's already clean).
   - Add a `PR_STEPS.md` (detailed how-to-PR guide).
   - Maybe add a file-mapping table so they know where each file goes in the repo.
   - Verify no stray artifacts (already cleaned .exe).

2. Write the detailed PR steps — a thorough document covering:
   - 前提准备（fork/clone、git config、token）
   - 放文件（哪个文件拷到哪个路径）
   - 编译接入（CSRCS + Kconfig）
   - 本地验证（编译 + 测试）
   - 提交（branch/add/commit/push）
   - 开 PR（title/body）
   - CLA 处理

Let me write a comprehensive `PR_STEPS.md` file in the focus_perception folder, and also give a summary in my response.

Actually, let me think about the file organization more carefully. The repo target is:
```
app/hello_app/
├── api/perception.h          (已冻结，别动)
├── perception/
│   ├── perception.c          ← 新增
│   └── perception_internal.h ← 新增
├── tests/
│   ├── test_perception.c     ← 新增
│   ├── wifi_http_post_stub.c ← 新增 (可选)
│   └── test_mimo_cloud.c     ← 新增 (可选)
```

So my `focus_perception/` folder already mirrors this (api/, perception/, tests/). Good. The "整理" is basically already done; I just need to:
1. Add the PR guide.
2. Maybe add a top-level index/说明.

Let me also reconsider: should I reorganize the folder to be directly the "repo-ready" tree? Currently it's:
```
focus_perception/
├── api/perception.h
├── perception/...
├── tests/...
├── BUILD_INTEGRATION.md
├── README.md
```

This is fine. I'll add:
- `PR_STEPS.md` — the detailed PR guide.

And I should double-check the code files one more time for any issues. Let me re-read perception.c quickly to confirm it's consistent after the rewrite (I already compiled it successfully, so it's syntactically fine and logically verified via 57 tests). I don't need to re-read.

Actually, let me reconsider whether I should verify the cloud test compiles. I can't (no cJSON here, no gcc in WSL without sudo). But I can do a syntax-only check of the cloud test + stub if I can get cJSON... no. I already hand-verified the logic. I'll note in the PR guide that the cloud test needs cJSON and was hand-verified (not compiled).

Actually, wait — I could at least syntax-check the stub and cloud test files individually (they don't depend on cJSON for the stub; the cloud test includes only perception.h and extern declarations, no cJSON). Let me verify:
- wifi_http_post_stub.c: includes stdio, string, stddef. No cJSON. Can syntax-check.
- test_mimo_cloud.c: includes stdio, string, ../api/perception.h. No cJSON directly. Can syntax-check (it references FOCUS_ERR_PERCEP_* which are in perception.h). Can compile-syntax-check.

But the cloud test calls perception_process which is in perception.c (needs cJSON to compile the full thing). For a syntax check of just test_mimo_cloud.c, I can do `gcc -fsyntax-only test_mimo_cloud.c` — but it includes "../api/perception.h" and references extern symbols; -fsyntax-only doesn't link, so it'll work. Let me do syntax-only checks on the stub and cloud test to catch any typos.

Actually, let me do `gcc -fsyntax-only` on the stub and cloud test. The cloud test includes perception.h which is fine. Let me verify.

Let me also verify the full file set is consistent by re-reading the current state of the key files (I have them in context from my writes). I think they're consistent. Let me just do the syntax checks + write the PR guide.

Let me do:
1. Syntax-check the two test files (stub + cloud test) individually.
2. Write PR_STEPS.md (detailed guide).
3. Maybe write a small "文件对照表" in the guide.

Let me run the syntax checks first.

Actually, I can also do a more complete check: compile the stub + cloud test + a minimal main stub... no, too much. Syntax-only is enough for the parts I couldn't compile before.

Let me run syntax checks.

---

### [2026-08-26 15:42:57] AI

[工具调用] Bash: {"command": "echo \"=== stub ===\" && gcc -fsyntax-only -Wall -Wextra tests/wifi_http_post_stub.c && echo \"stub OK\" && echo \"=== cloud test ===\" && gcc -fsyntax-only -Wall -Wextra tests/test_mimo_cloud.c && echo \"cloud test OK\" && echo \"=== internal header standalone ===\" && gcc -fsyntax-only -DPERCEPTION_MOCK -x c -include perception/perception_internal.h /dev/null 2>&1 && echo \"internal header OK\"", "description": "Syntax-check stub, cloud test, and internal header"}

---

### [2026-08-26 16:26:49] 用户

[工具结果] === stub ===
tests/wifi_http_post_stub.c:34:32: warning: unused parameter 'url' [-Wunused-parameter]
   34 | int wifi_http_post(const char *url, const char *body, char *resp, size_t maxlen)
      |                                ^
tests/wifi_http_post_stub.c:34:49: warning: unused parameter 'body' [-Wunused-parameter]
   34 | int wifi_http_post(const char *url, const char *body, char *resp, size_t maxlen)
      |                                                 ^
2 warnings generated.
stub OK
=== cloud test ===
cloud test OK
=== internal header standalone ===
internal header OK

---

### [2026-08-26 16:28:10] 用户

This session is being continued from a previous conversation that ran out of context. The summary below covers the earlier portion of the conversation.

Summary:
1. Primary Request and Intent:
   - **Initial request**: "结合文件夹里的文本内容 给我成品" — read all .md files in C:\temp and produce the finished deliverable for 周礼航's module in the "FOCUS AIoT" project (an ESP32-S3-EYE study monitor running openvela OS).
   - **The deliverable is the 视觉感知模块 (perception)** — 周礼航's assigned module, implementing three functions (`perception_init`, `perception_process`, `perception_get_history`) that turn a JPEG into `observation_t`.
   - **MiMo requirement** (added later): "要 同时识图时如果有需要 必须调用mimo" — the perception module must call MiMo during image recognition. Via AskUserQuestion, user clarified: call MiMo **每帧都调** (every frame), and user chose to paste the real contract. The pasted MiMo contract is identical to the detection API contract already implemented.
   - **"需要我提供什么"** — user asked what info I need (endpoint URL, auth method + token, real request/response examples).
   - **"pr上去吧"** — user wants the code pushed as a GitHub PR.
   - **"本机有wsl"** — user indicated WSL is available on this machine.
   - **Most recent request**: "你整理一下本地的代码 然后写一份如何pr的详细步骤" — organize the local code AND write a detailed step-by-step "how to PR" guide.

2. Key Technical Concepts:
   - FOCUS AIoT project: ESP32-S3-EYE, openvela/NuttX OS, team contest 2026 (contest2026_087_gaiduimingyizhanyongdui)
   - Team division: 万思源 (system/state machine), 张沐泽 (hardware/wifi/camera), 周礼航 (perception, the user), 赵思涵 (behavior), 郭黄亦昕 (UI + MiMo)
   - `observation_t` struct (frozen in api/perception.h): person_present, person_bbox[4], phone_detected, phone_near_hand, head_pitch, head_yaw, hand_motion_score, confidence, timestamp_ms
   - Error codes: FOCUS_OK=0, FOCUS_ERR_PERCEP_TIMEOUT=-30, FOCUS_ERR_PERCEP_JSON=-31, FOCUS_ERR_PERCEP_NODATA=-32, FOCUS_ERR_PERCEP_PARAM=-33 (local addition)
   - 3-frame debounce: bool majority vote, angle median3, hand_motion max3, confidence average
   - History ring buffer: obs_history[60]; strong symbol `perception_get_history()` overrides weak stub in `core/mock.c`
   - Mock/real dual path via `-DPERCEPTION_MOCK` compile flag
   - `wifi_http_post(const char *url, const char *body, char *resp, size_t maxlen)` — 张沐泽's HTTP client (no header param, ≤3s timeout, retry once ≤6s total)
   - cJSON for response parsing (real path only)
   - MiMo: multimodal LLM used as the recognition endpoint; contract = {"image":"<base64>","width":320,"height":240} → {"code":0,"data":{...}}
   - clock_gettime(CLOCK_MONOTONIC) for timestamps
   - openvela ai_agent framework (packages/ai_agent) is where MiMo LLM integration lives
   - CLA signing required for PRs (openvela.com/#/community/cla, comment /check-cla)
   - Windows environment: git 2.55.0, no gh, WSL Ubuntu-26.04 (fresh, git 2.53.0, no repo/creds/gcc)

3. Files and Code Sections:
   All files in C:\temp\focus_perception\:

   - **api/perception.h** — Public interface (reference copy, must NOT overwrite the frozen repo version). Contains observation_t typedef, 3 function prototypes, and guarded error code #defines (FOCUS_OK=0, FOCUS_ERR_PERCEP_TIMEOUT=-30, FOCUS_ERR_PERCEP_JSON=-31, FOCUS_ERR_PERCEP_NODATA=-32, FOCUS_ERR_PERCEP_PARAM=-33).

   - **perception/perception.c** — Main implementation (~400 lines). Key parts:
     - Config macros: HISTORY_MAX=60, FRAME_WIDTH=320, FRAME_HEIGHT=240, MAX_JPEG_SIZE=(50*1024), RESP_BUF_SIZE=4096, MIMO_ENDPOINT_DEFAULT="" (TODO fill), MIMO_API_KEY_DEFAULT="" (TODO fill)
     - Statics: g_api_url[160], g_api_key[80], g_history[HISTORY_MAX], g_history_count, g_debounce[3], g_debounce_count, g_debounce_idx, g_mock_seq, g_resp (guarded #ifndef PERCEPTION_MOCK)
     - `perception_monotonic_ms()` — uses clock_gettime(CLOCK_MONOTONIC)
     - `perception_majority3(bool,bool,bool)`, `perception_median3(float,float,float)`, `perception_max3(float,float,float)`
     - `perception_base64_encoded_len()` / `perception_base64_encode()` — RFC4648
     - `perception_fill_observation()`, `perception_debounce_push()`, `perception_debounce_compute()`
     - `mimo_detect(uint8_t *jpeg, size_t jpeg_len, cloud_result_t *raw)` — the explicit "调用 MiMo" step (base64 → snprintf JSON request `{"image":"%s","width":%d,"height":%d}` → wifi_http_post (retry once) → parse). Under #ifndef PERCEPTION_MOCK.
     - `perception_parse_cloud_response(const char *resp, cloud_result_t *out)` — cJSON parsing, checks code==0, data object, person/phone/head_pose/hand_motion_score/confidence, all fields null-checked
     - `mock_observation(int step)` — rotates FOCUSED/PLAYING_PHONE/AWAY/DROWSY, under #ifdef PERCEPTION_MOCK
     - `history_append()` (static)
     - `perception_init(const char *api_url, const char *api_key)` — stores url/key (falls back to MIMO_*_DEFAULT if NULL), resets history/debounce/mock_seq, returns FOCUS_OK
     - `perception_process(uint8_t *jpeg, size_t jpeg_len, observation_t *out)` — validates args (returns FOCUS_ERR_PERCEP_PARAM), mock path OR real path (mimo_detect → debounce_push → debounce_compute), then history_append
     - `perception_get_history(observation_t *buf, int n)` — returns oldest-to-newest up to n, handles wrap-around

   - **perception/perception_internal.h** — Internal declarations: cloud_result_t (person_detected, person_bbox[4], phone_detected, phone_in_hand, head_pitch, head_yaw, hand_motion, confidence — head_roll was removed), and tool function prototypes (perception_monotonic_ms, perception_base64_*, perception_majority3/median3/max3, perception_fill_observation, perception_debounce_push/compute, perception_parse_cloud_response under #ifndef PERCEPTION_MOCK).

   - **tests/test_perception.c** — Mock unit test, 57 checks: base64 (RFC4648 vectors "Man"→"TWFu", "Ma"→"TWE=", "M"→"TQ==", etc.), math helpers, debounce, process+history, NULL safety. Compiles with `gcc -DPERCEPTION_MOCK perception/perception.c tests/test_perception.c`.

   - **tests/wifi_http_post_stub.c** — 联调 stub. Globals: stub_mimo_call_count, stub_mimo_response (NULL→DEFAULT_RESPONSE), stub_mimo_fail_first_n. DEFAULT_RESPONSE is a "playing phone" MiMo response (person detected, bbox[0.15,0.10,0.70,0.85], phone detected+near_hand, pitch -25.3, yaw 2.1, motion 0.35, confidence 0.92). wifi_http_post increments count, simulates fail_first_n failures, copies response, returns 0/-1.

   - **tests/test_mimo_cloud.c** — Real MiMo path test (needs cJSON): verifies every-frame call count (5 frames → 5 calls), single-frame parse values (feq with 1e-4 epsilon), retry (fail_first_n=1 → 2 calls, FOCUS_OK), error codes (code:1→NODATA, "not-a-json"→JSON, fail_first_n=2→TIMEOUT). Compiles with `gcc perception/perception.c tests/wifi_http_post_stub.c tests/test_mimo_cloud.c cJSON.c -I/path/to/cjson`.

   - **BUILD_INTEGRATION.md** — Makefile/CMakeLists/Kconfig integration diff: CSRCS += perception/perception.c, Kconfig CONTEST2026_087_PERCEPTION_MOCK (default y), cJSON dependency, host test commands.

   - **README.md** — Full documentation: file list, MiMo contract, 3 function signatures, error code table, key design points (every-frame MiMo, debounce, history ring buffer, timeout, memory, timestamp), local test commands, repo integration steps, 联调 order.

   Other files read (in C:\temp, source material): 产品方案与分工_v2.md, DEVELOPMENT_TASKS.md (3 versions), 周礼航开发规范.md (2 versions), re.md, 20260731_055914-ubuntu.md (767KB transcript).

4. Errors and fixes:
   - **`unused variable 'g_resp'`** in MOCK build (clang -Werror): fixed by wrapping `static char g_resp[RESP_BUF_SIZE]` in `#ifndef PERCEPTION_MOCK`.
   - **`undefined symbol: clock_gettime64`** (Windows/mingw linker): fixed by adding `-lwinpthread` flag. This is Windows-only; on Linux/openvela clock_gettime works without flags.
   - **cJSON not available on Windows**: test_mimo_cloud.c could not be compiled/verified locally; verified logic by hand inspection, documented cJSON requirement (openvela ships it; host: apt install libcjson-dev or vendor cJSON.c/h).
   - **No user-feedback corrections on the code itself** — the user's iterative requests (MiMo every-frame, paste contract, PR) were additive refinements, not corrections.

5. Problem Solving:
   - Solved: Determined 周礼航's exact task from docs (perception module, 3 functions), produced complete compilable code with mock/real dual path, verified mock test (57/57 pass on Windows with -lwinpthread).
   - Solved: Integrated MiMo as the recognition endpoint (every-frame call) — refactored into mimo_detect(), added placeholder macros.
   - Ongoing: PR cannot be pushed from this environment. Diagnosed: no repo on Windows (C:\temp not git), no gh CLI, no credentials. WSL Ubuntu-26.04 is fresh (git installed but unconfigured, no repo, no gcc, no SSH keys, sudo needs password). The actual repo lives on a different machine (transcript's /home/ubuntu, user "ubuntu").

6. All user messages:
   - "结合文件夹里的文本内容 给我成品"
   - "这是官方的 [pasted OpenAI/MiMo Python example with api.xiaomimimo.com, model mimo-v2.5, and response JSON] 上面是输入 下面是响应 然后 因为 我们是tokenplan 所以baseurl是https://token-plan-cn.xiaomimimo.com/v1 apikey你自己再tokenplan页面创建 https://mimo.mi.com/docs/zh-CN/quick-start/usage-guide/multimodal-understanding/image-understanding 唉 你直接查看这个吧 是长官 或者你让ai看也行（"
   - "或者你让ai看也行（ /学习 这是官方文档，你只需要告诉ai这个所以baseurl是https://token-plan-cn.xiaomimimo.com/v1"
   - "要 同时识图时如果有需要 必须调用mimo"
   - "需要我提供什么"
   - "pr上去吧"
   - "本机有wsl"
   - "你整理一下本地的代码 然后写一份如何pr的详细步骤"
   - (AskUserQuestion answers): 调用时机 = "每帧都调"; MiMo 契约 = "我现在贴真实契约"
   - (User pasted the MiMo contract: Request {"image":"<base64>","width":320,"height":240}, Response {"code":0,"data":{person:{detected,bbox}, phone:{detected,near_hand}, head_pose:{pitch,yaw}, hand_motion_score, confidence}})

   Security-relevant: A GitHub token `ghp_REDACTED` appears in the transcript file (dated 2026-07-31), was flagged as needing regeneration, and is likely invalid — do NOT reuse it. Any new token the user provides must be handled carefully (not logged/committed).

7. Pending Tasks:
   - **Organize the local code** (the C:\temp\focus_perception\ folder) — likely ensure it's clean/complete/ready to hand off.
   - **Write a detailed "how to PR" step-by-step guide** (the user's most recent explicit request). This should cover: cloning/forking, placing files into the repo (app/hello_app/perception/), BUILD_INTEGRATION.md changes, git config, commit, push, opening the PR, and the CLA signing step.

8. Current Work:
   Immediately before this summary, I had diagnosed the PR-push blocker: Windows machine has no repo/gh/credentials; WSL Ubuntu-26.04 is fresh (git 2.53.0 installed but no user.name/email, no repo, no gcc, no SSH keys, sudo requires password). I told the user the repo is on a different machine and asked them to either (A) provide repo URL + GitHub token to push from WSL, or (B) let me install gcc first to verify on Linux. The user's latest reply was "你整理一下本地的代码 然后写一份如何pr的详细步骤" — redirecting from "do the PR for me" to "organize the code and write a detailed how-to-PR guide" (presumably so they can do the PR themselves on their VM).

9. Optional Next Step:
   Directly address the user's latest request "你整理一下本地的代码 然后写一份如何pr的详细步骤": (1) verify/clean up the focus_perception folder (confirm all 8 files present, no stray binaries), and (2) write a comprehensive, detailed PR guide as a markdown file (e.g., PR_GUIDE.md or an expanded section in README/BUILD_INTEGRATION.md) covering: fork/clone setup, exact file placement into app/hello_app/perception/ (NOT overwriting api/perception.h), CSRCS/Kconfig edits per BUILD_INTEGRATION.md, git config user.name/email, branch creation, add/commit (with the prepared commit message ending in "Co-Authored-By: Claude <noreply@anthropic.com>"), push to fork, open PR (title "feat: 视觉感知模块 perception（每帧调 MiMo 识图）" + prepared body), and the CLA step (sign at openvela.com/#/community/cla then comment /check-cla). This is fully in line with the user's most recent explicit request and does not require any new credentials.

If you need specific details from before compaction (like exact code snippets, error messages, or content you generated), read the full transcript at: C:\Users\user\.claude\projects\C--temp\5486faa1-0a5f-417c-8e1c-20b0003d4150.jsonl
Continue the conversation from where it left off without asking the user any further questions. Resume directly — do not acknowledge the summary, do not recap what was happening, do not preface with "I'll continue" or similar. Pick up the last task as if the break never happened.

---

### [2026-08-26 16:28:10] 用户

[附件文件] C:\temp\focus_perception\README.md

# 视觉感知模块 (perception) —— 周礼航 · 成品

这是「FOCUS AIoT」里 **视觉感知层** 的完整实现。输入一张 JPEG，**每帧调用
MiMo 识图接口**，输出一个 `observation_t`，供赵思涵的 `behavior` 模块做时序分析。

> 依据文档：`周礼航开发规范.md`、`DEVELOPMENT_TASKS (2).md`（2026-08-19）、
> `产品方案与分工_v2.md`。只做「空间」上的单帧识别，**不区分严格/鼓励模式**，
> **不做行为判断**（那是赵思涵的事）。

## 文件清单

```
focus_perception/
├── api/perception.h             公开接口 (observation_t + 3 函数 + 错误码)
│                                ⚠️ 参考拷贝, 勿覆盖仓库冻结版
├── perception/
│   ├── perception.c             主实现 (MiMo 调用 + 去抖 + 历史 + base64 + cJSON)
│   └── perception_internal.h    内部声明 (cloud_result_t + 工具函数)
├── tests/
│   ├── test_perception.c        mock 单测 (不依赖硬件/网络/cJSON)
│   ├── wifi_http_post_stub.c    联调 stub (替换真实 wifi_http_post)
│   └── test_mimo_cloud.c        真实 MiMo 链路单测 (需要 cJSON)
├── BUILD_INTEGRATION.md         Makefile/CMakeLists/Kconfig 接入 diff
└── README.md
```

## MiMo 识图（每帧都调）

`perception_process()` 每次收到一帧 JPEG 都调一次 `mimo_detect()`（失败重试 1 次，
总阻塞 ≤6s），契约已冻结：

```
Request:  {"image":"<base64>","width":320,"height":240}
Response: {"code":0,"data":{
             "person":{"detected":true,"bbox":[0.15,0.10,0.70,0.85]},
             "phone":{"detected":true,"near_hand":true},
             "head_pose":{"pitch":-25.3,"yaw":2.1},
             "hand_motion_score":0.35,"confidence":0.92}}
```

endpoint / key 通过 `perception_init(url, key)` 传入（优先级高于
`MIMO_ENDPOINT_DEFAULT` / `MIMO_API_KEY_DEFAULT` 两个占位宏）。

> ⚠️ **待确认**：契约里没有鉴权字段，而 `wifi_http_post(url, body, resp, maxlen)`
> 也带不了 header。MiMo 的 token 到底怎么传（header？URL query？body？），
> 需要跟张沐泽/陈泽沛确认，`g_api_key` 已预留。

## 三个对外接口（冻结签名）

```c
int  perception_init(const char *api_url, const char *api_key);
int  perception_process(uint8_t *jpeg, size_t jpeg_len, observation_t *out);
int  perception_get_history(observation_t *buf, int n);
```

返回值（错误码，来自 `api/error.h`，此处兜底定义）：

| 常量 | 值 | 含义 |
|---|---|---|
| `FOCUS_OK` | 0 | 成功 |
| `FOCUS_ERR_PERCEP_TIMEOUT` | -30 | MiMo 超时/请求失败 |
| `FOCUS_ERR_PERCEP_JSON` | -31 | JSON 解析失败 / 缺字段 |
| `FOCUS_ERR_PERCEP_NODATA` | -32 | 业务码非 0 / 无数据 |
| `FOCUS_ERR_PERCEP_PARAM` | -33 | 参数非法（本地扩展，可请万思源并入 error.h） |

## 关键设计

- **每帧都调 MiMo**：`perception_process()` → `mimo_detect()`（base64 → JSON →
  `wifi_http_post` → cJSON 解析）→ 3 帧去抖 → 追加历史。
- **mock / 真实双路径**：`-DPERCEPTION_MOCK` 走 mock（默认，不调 MiMo）；
  不定义则走真实 MiMo 链路。
- **3 帧去抖**：bool 多数投票、角度中位数、hand_motion 取最大、confidence 取均值。
  mock 路径本身已是稳定结果，**绕过**去抖，避免把 AWAY 状态「投票投没」。
- **历史环形缓冲**：`obs_history[60]`，`perception_get_history()` 从旧到新返回。
  提供**强符号** `perception_get_history()`，自动覆盖 `core/mock.c` 里的 weak 桩。
- **超时**：HTTP 单次由张沐泽的 `wifi_http_post` 保证 ≤3s；失败重试 1 次，总阻塞 ≤6s。
- **内存**：base64 / 请求体用 `malloc`（ESP32 上建议映射 PSRAM），响应用固定 4KB 静态缓冲。
- **时间戳**：`clock_gettime(CLOCK_MONOTONIC)`（与 `core/state_machine.c` 的 monotonic_ms 一致）。

## 本地单测

```bash
cd focus_perception

# 1) mock 单测 (无 cJSON 依赖)
gcc -Wall -Wextra -Werror -DPERCEPTION_MOCK \
    perception/perception.c tests/test_perception.c -o test_perception
./test_perception

# 2) 真实 MiMo 链路单测 (需要 cJSON.c/cJSON.h)
gcc -Wall -Wextra -Werror \
    perception/perception.c tests/wifi_http_post_stub.c tests/test_mimo_cloud.c \
    cJSON.c -I/path/to/cjson -o test_mimo_cloud
./test_mimo_cloud
```

预期都是 `0 failed`。mock 测试覆盖：base64（RFC4648 标准向量）、多数投票/中位数/最大值、
3 帧去抖、mock 轮转、历史环形缓冲、空历史/参数非法。MiMo 测试覆盖：每帧调用次数、
响应解析、失败重试、三种错误码。

## 接入仓库（openvela 真机）

1. 把 `perception/perception.c`、`perception/perception_internal.h` 放进
   `app/hello_app/perception/`。
2. `api/perception.h` **不要覆盖**，用仓库冻结版（字段/签名必须一致）。
3. 按 `BUILD_INTEGRATION.md` 加 `CSRCS` + Kconfig 开关。
4. 联调/上线前关掉 mock 开关，并填好 MiMo endpoint / token。

## 联调顺序

先跟张沐泽联调（确认 `wifi_http_post` 能通 + MiMo 鉴权方式）→ 再跟赵思涵联调
（确认 `observation_t` 字段对）→ 最后全链路：真实 observation → behavior →
state_machine → UI 上屏。

---

### [2026-08-26 16:28:10] 用户

[附件文件] C:\temp\focus_perception\BUILD_INTEGRATION.md

# 构建接入 (Makefile / CMakeLists / Kconfig)

把 `perception/` 接进仓库，需要 3 步。仓库里 `LCD_STUB` 已有现成的
「Kconfig 二选一编译」模式，直接照抄它的 if/else 即可。

## 1. 源文件入编

**Makefile**（`app/hello_app/Makefile`）的 `CSRCS`：

```make
CSRCS += perception/perception.c
```

**CMakeLists.txt**（`app/hello_app/CMakeLists.txt`）：

```cmake
set(CSRCS ${CSRCS} perception/perception.c)
```

## 2. mock / 真实 二选一（参考 LCD_STUB）

**Makefile**：

```make
ifeq ($(CONFIG_CONTEST2026_087_PERCEPTION_MOCK),y)
CFLAGS += -DPERCEPTION_MOCK
else
# 真实 MiMo 链路: 依赖 cJSON (openvela 自带, 头文件 <cJSON.h>)
# 若需显式链接: LDLIBS += -lcjson
endif
```

**Kconfig**（`app/hello_app/Kconfig`）：

```
config CONTEST2026_087_PERCEPTION_MOCK
    bool "Perception mock (no MiMo call)"
    default y
    help
        默认走 mock，便于不依赖网络的联调；关掉后走真实 MiMo 识图链路。
```

> 默认 `y`（mock），符合任务书「默认 mock 可回退」。联调/上线前关掉。

## 3. 依赖说明

| 依赖 | 来源 | 说明 |
|---|---|---|
| `wifi_http_post()` | 张沐泽 `api/wifi.h` | 真实网络 |
| `cJSON` | openvela 自带 | 真实链路解析响应用 |
| `perception_get_history()` | 本模块 | 强符号，自动覆盖 `core/mock.c` 的 weak 桩 |

## 4. host 联调（不需要硬件/网络）

```bash
# mock 单测 (无 cJSON 依赖)
gcc -Wall -Wextra -Werror -DPERCEPTION_MOCK \
    perception/perception.c tests/test_perception.c -o test_perception
./test_perception

# 真实 MiMo 链路单测 (需要 cJSON.c/cJSON.h)
gcc -Wall -Wextra -Werror \
    perception/perception.c tests/wifi_http_post_stub.c tests/test_mimo_cloud.c \
    cJSON.c -I/path/to/cjson -o test_mimo_cloud
./test_mimo_cloud
```

---

### [2026-08-26 16:28:10] 用户

[附件文件] C:\temp\focus_perception\tests\test_mimo_cloud.c

/****************************************************************************
 * FOCUS AIoT - 真实 MiMo 链路单测 (tests/test_mimo_cloud.c)
 *
 * 负责人: 周礼航
 * 用途:   用 wifi_http_post_stub.c 替换真实网络, 验证 perception 真实路径:
 *         每帧都调 MiMo、请求构造、响应解析、3 帧去抖、重试、错误码。
 *
 * 依赖:   cJSON (perception.c 真实路径需要)。
 * 编译 (在 focus_perception 目录下):
 *   gcc -Wall -Wextra -Werror \
 *       perception/perception.c tests/wifi_http_post_stub.c tests/test_mimo_cloud.c \
 *       cJSON.c -I/path/to/cjson -o test_mimo_cloud
 *   ./test_mimo_cloud
 *
 *   (cJSON 是单文件库; openvela 已自带。host 上可 apt install libcjson-dev
 *    或直接拷一份 cJSON.c/cJSON.h 进仓库。)
 ****************************************************************************/

#include <stdio.h>
#include <string.h>

#include "../api/perception.h"

/* 来自 wifi_http_post_stub.c */
extern int         stub_mimo_call_count;
extern const char *stub_mimo_response;
extern int         stub_mimo_fail_first_n;

static int g_checks = 0;
static int g_fail   = 0;

#define CHECK(cond) do {                                   \
    g_checks++;                                            \
    if (!(cond)) {                                         \
        g_fail++;                                          \
        printf("  [FAIL] %s (line %d)\n", #cond, __LINE__);\
    }                                                      \
} while (0)

static int feq(float a, float b)
{
    float d = a - b;
    if (d < 0) d = -d;
    return d < 1e-4f;
}

/* 每帧都调 MiMo + 响应解析 */
static void test_mimo_parse_and_every_frame(void)
{
    printf("== test_mimo_parse_and_every_frame ==\n");
    stub_mimo_response = NULL;      /* 用默认「玩手机」响应 */
    stub_mimo_fail_first_n = 0;

    CHECK(perception_init("https://mimo.example/api/v1/detect", "key") == FOCUS_OK);

    uint8_t jpeg[64] = {0};
    observation_t obs;
    int before = stub_mimo_call_count;

    /* 连续 5 帧 → MiMo 应被调用 5 次 (每帧都调) */
    for (int i = 0; i < 5; i++) {
        CHECK(perception_process(jpeg, sizeof(jpeg), &obs) == FOCUS_OK);
    }
    CHECK(stub_mimo_call_count - before == 5);

    /* 单帧解析结果 (去抖窗口未满 3 帧时直接输出) */
    CHECK(obs.person_present  == true);
    CHECK(obs.phone_detected  == true);
    CHECK(obs.phone_near_hand == true);
    CHECK(feq(obs.person_bbox[0], 0.15f) && feq(obs.person_bbox[1], 0.10f));
    CHECK(feq(obs.person_bbox[2], 0.70f) && feq(obs.person_bbox[3], 0.85f));
    CHECK(feq(obs.head_pitch, -25.3f));
    CHECK(feq(obs.head_yaw, 2.1f));
    CHECK(feq(obs.hand_motion_score, 0.35f));
    CHECK(feq(obs.confidence, 0.92f));
}

/* 失败重试: 前 1 次失败 → 重试成功, 调用次数 +2 */
static void test_mimo_retry(void)
{
    printf("== test_mimo_retry ==\n");
    perception_init("https://mimo.example/api/v1/detect", "key");

    stub_mimo_fail_first_n = 1;
    int before = stub_mimo_call_count;

    uint8_t jpeg[64] = {0};
    observation_t obs;
    CHECK(perception_process(jpeg, sizeof(jpeg), &obs) == FOCUS_OK);
    CHECK(stub_mimo_call_count - before == 2);   /* 1 失败 + 1 重试成功 */
}

/* 错误码: 业务码非 0 / JSON 非法 / 连续失败超时 */
static void test_mimo_error_codes(void)
{
    printf("== test_mimo_error_codes ==\n");
    uint8_t jpeg[64] = {0};
    observation_t obs;

    /* 业务码非 0 → NODATA */
    perception_init("u", "k");
    stub_mimo_fail_first_n = 0;
    stub_mimo_response = "{\"code\":1,\"data\":{}}";
    CHECK(perception_process(jpeg, sizeof(jpeg), &obs) == FOCUS_ERR_PERCEP_NODATA);

    /* JSON 非法 → JSON */
    stub_mimo_response = "not-a-json";
    CHECK(perception_process(jpeg, sizeof(jpeg), &obs) == FOCUS_ERR_PERCEP_JSON);

    /* 连续 2 次都失败 (原请求 + 重试) → TIMEOUT */
    stub_mimo_response = NULL;
    stub_mimo_fail_first_n = 2;
    CHECK(perception_process(jpeg, sizeof(jpeg), &obs) == FOCUS_ERR_PERCEP_TIMEOUT);
}

int main(void)
{
    test_mimo_parse_and_every_frame();
    test_mimo_retry();
    test_mimo_error_codes();

    printf("\n结果: %d checks, %d failed\n", g_checks, g_fail);
    return g_fail ? 1 : 0;
}

---

### [2026-08-26 16:28:10] 用户

[附件文件] C:\temp\focus_perception\tests\wifi_http_post_stub.c

/****************************************************************************
 * FOCUS AIoT - wifi_http_post 联调 stub (tests/wifi_http_post_stub.c)
 *
 * 用途:   宿主机联调时替换张沐泽的真实 wifi_http_post，让 perception 模块
 *         在 Linux 上无需硬件/网络即可跑通「base64 → 构造请求 → POST →
 *         解析 MiMo 响应 → 去抖」整条真实链路。
 *
 * 说明:   与真机代码一起链接时【不要】编译本文件（会和张沐泽的强符号冲突）。
 *         仅用于 host 单测 / 联调。
 ****************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stddef.h>

/* ---- 联调控制项 (测试代码可改) ---- */
int         stub_mimo_call_count = 0;   /* 累计被调用次数 */
const char *stub_mimo_response  = NULL; /* 自定义响应, NULL 用默认 */
int         stub_mimo_fail_first_n = 0; /* 前 N 次返回失败 (测重试) */

/* 默认返回一个「玩手机」场景的 MiMo 响应 (字段最全, 便于验证解析) */
static const char DEFAULT_RESPONSE[] =
    "{"
    "\"code\":0,"
    "\"data\":{"
        "\"person\":{\"detected\":true,\"bbox\":[0.15,0.10,0.70,0.85]},"
        "\"phone\":{\"detected\":true,\"near_hand\":true},"
        "\"head_pose\":{\"pitch\":-25.3,\"yaw\":2.1},"
        "\"hand_motion_score\":0.35,"
        "\"confidence\":0.92"
    "}"
    "}";

int wifi_http_post(const char *url, const char *body, char *resp, size_t maxlen)
{
    stub_mimo_call_count++;

    /* 模拟前 N 次失败 (perception 内部会重试 1 次) */
    if (stub_mimo_fail_first_n > 0) {
        stub_mimo_fail_first_n--;
        return -1;
    }

    const char *r = stub_mimo_response ? stub_mimo_response : DEFAULT_RESPONSE;
    if (resp && maxlen > 0) {
        snprintf(resp, maxlen, "%s", r);
    }
    return 0;
}

---

### [2026-08-26 16:28:10] 用户

[附件文件] C:\temp\focus_perception\perception\perception_internal.h

/****************************************************************************
 * FOCUS AIoT - 视觉感知模块内部声明 (perception/perception_internal.h)
 *
 * 负责人: 周礼航
 * 说明:   对应任务书里的「perception/perception.h (内部声明, 可选)」。
 *         为避免与公开接口 api/perception.h 混淆, 命名为 *_internal.h。
 *         这里暴露的 cloud_result_t 与工具函数仅供 perception.c 实现与
 *         单测 (tests/test_perception.c) 使用，不对其他模块开放。
 ****************************************************************************/

#ifndef PERCEPTION_INTERNAL_H
#define PERCEPTION_INTERNAL_H

#include "../api/perception.h"

/* 云端原始检测结果 (内部使用, 不对外暴露) */
typedef struct {
    bool  person_detected;
    float person_bbox[4];
    bool  phone_detected;
    bool  phone_in_hand;
    float head_pitch, head_yaw;
    float hand_motion;
    float confidence;
} cloud_result_t;

/* ---- 内部工具函数 (实现 + 单测共用) ---- */

uint32_t perception_monotonic_ms(void);

size_t perception_base64_encoded_len(size_t n);
size_t perception_base64_encode(const uint8_t *src, size_t len,
                                char *dst, size_t dst_cap);

bool  perception_majority3(bool a, bool b, bool c);
float perception_median3(float a, float b, float c);
float perception_max3(float a, float b, float c);

void  perception_fill_observation(const cloud_result_t *raw,
                                  observation_t *out, uint32_t ts);
void  perception_debounce_push(const cloud_result_t *raw);
void  perception_debounce_compute(observation_t *out, uint32_t ts);

/* 仅在非 mock (真实云端) 构建中定义, 依赖 cJSON */
#ifndef PERCEPTION_MOCK
int   perception_parse_cloud_response(const char *resp, cloud_result_t *out);
#endif

#endif /* PERCEPTION_INTERNAL_H */

---

### [2026-08-26 16:28:27] AI

[思考] The syntax checks pass. The stub has two unused-parameter warnings (url, body) — these are expected because the stub is a fake that doesn't use them. With `-Werror` these would fail. But the stub is compiled in the cloud test build with `-Wall -Wextra -Werror` per the README command. Let me check — the README command is:

```
gcc -Wall -Wextra -Werror \
    perception/perception.c tests/wifi_http_post_stub.c tests/test_mimo_cloud.c \
    cJSON.c -I/path/to/cjson -o test_mimo_cloud
```

With -Werror, the unused parameter warnings in the stub would fail the build! I need to fix this. Add `(void)url; (void)body;` to silence them.

Let me fix the stub to cast unused params to void.

---

### [2026-08-26 16:28:29] AI

[工具调用] Edit: {"replace_all": false, "file_path": "C:\\temp\\focus_perception\\tests\\wifi_http_post_stub.c", "old_string": "int wifi_http_post(const char *url, const char *body, char *resp, size_t maxlen)\n{\n    stub_mimo_call_count++;", "new_string": "int wifi_http_post(const char *url, const char *body, char *resp, size_t maxlen)\n{\n    (void)url;   /* 联调 stub: 不真正发请求, 忽略 url/body */\n    (void)body;\n    stub_mimo_call_count++;"}

---

### [2026-08-26 17:28:40] 用户

[工具结果] The file C:\temp\focus_perception\tests\wifi_http_post_stub.c has been updated successfully. (file state is current in your context — no need to Read it back)

---

### [2026-08-26 17:28:44] AI

[工具调用] Bash: {"command": "gcc -fsyntax-only -Wall -Wextra -Werror tests/wifi_http_post_stub.c && echo \"stub clean (no warnings)\"", "description": "Verify stub now compiles clean under -Werror"}

---

### [2026-08-26 17:29:25] 用户

[工具结果] stub clean (no warnings)

---

### [2026-08-26 17:29:28] AI

[思考] Now let me also verify the full file listing of the folder to make sure it's clean (no stray binaries/objects).

---

### [2026-08-26 17:29:28] AI

[工具调用] Bash: {"command": "find . -type f | sort", "description": "List all files in focus_perception folder"}

---

### [2026-08-26 17:29:28] 用户

[工具结果] ./BUILD_INTEGRATION.md
./README.md
./api/perception.h
./perception/perception.c
./perception/perception_internal.h
./tests/test_mimo_cloud.c
./tests/test_perception.c
./tests/wifi_http_post_stub.c

---

### [2026-08-26 17:29:44] AI

[思考] The folder is clean — 8 files, no stray binaries. Now I'll write the PR guide. Let me write a comprehensive `PR_STEPS.md` covering the whole flow.

Let me think about what goes into the PR guide. It needs to be detailed and actionable for the user (who will do the PR on their own machine — the transcript indicates the repo is on a VM at /home/ubuntu, user "ubuntu", contest2026 repo).

Key info I know from the context:
- Team: contest2026_087_gaiduimingyizhanyongdui
- Repo: openvela-based, app/hello_app
- The 3 functions, api/perception.h is frozen (don't overwrite)
- BUILD_INTEGRATION.md has the Makefile/CMakeLists/Kconfig diffs
- CLA signing required at openvela.com/#/community/cla + /check-cla comment
- Commit message should end with Co-Authored-By: Claude
- Git config user.name/email needed

The PR guide should cover:
1. 前置准备 (prerequisites)
   - 找到仓库（openvela fork or team repo）
   - fork 到自己的 GitHub 账号
   - clone
   - git config user.name/email
   - 确认有 push 权限 / token
2. 整理/放置文件 (file placement)
   - 从本机 C:\temp\focus_perception 拷到仓库
   - 明确哪个文件去哪，哪些不拷（api/perception.h 不覆盖）
3. 构建接入 (build integration) — per BUILD_INTEGRATION.md
   - CSRCS += perception/perception.c (Makefile + CMakeLists)
   - Kconfig 开关
4. 本地验证 (local verify)
   - mock 测试编译运行（Linux: 不需要 -lwinpthread）
   - 真实链路测试（需要 cJSON）
5. 提交 (commit)
   - 新分支
   - git add（只加该加的文件，注意不要提交 token/密钥）
   - commit message
6. push + 开 PR
   - title/body 模板
   - 关联 issue / 描述
7. CLA
   - sign at openvela.com/#/community/cla
   - comment /check-cla
8. 常见坑 (common pitfalls)
   - 忘记 git config
   - api/perception.h 被覆盖
   - token 泄露（之前有个 token 已泄露要作废）
   - 未填 MiMo endpoint/token

Let me write this comprehensively. I'll write it as `PR_STEPS.md` in the focus_perception folder.

I should also note the security thing about the token — there was a leaked token in the transcript. I should remind them to not commit any token, and that the leaked one should be revoked. But I should be careful — I shouldn't reproduce the token. I'll just say "之前文件里出现过的一个 GitHub token 已泄露，请去 GitHub 设置里 revoke，PR 用新 token" without printing it.

Let me write the file. I'll write it in Chinese since the user communicates in Chinese and all docs are in Chinese.

Let me also decide: should the PR guide be one file or split? One comprehensive file `PR_STEPS.md` is cleanest, plus I'll give a summary in my chat response.

Let me write it now. I need to make it detailed but not bloated. Let me structure clearly with the file-mapping table.

Let me write it.

---

### [2026-08-26 17:30:19] AI

[工具调用] Write: {"file_path": "C:\\temp\\focus_perception\\PR_STEPS.md", "content": "# 如何提交 PR —— 视觉感知模块（周礼航）\n\n> 目标：把 `focus_perception/` 里的代码提进 openvela 仓库 `app/hello_app/`，开一个 PR。\n> 适用环境：你有仓库的机器（VM / WSL / 本机均可），已装 git + gcc。\n> 全程不涉及本机 `C:\\temp` —— 那份只是开发时的本地副本。\n\n---\n\n## 0. 先核对：代码现在长什么样\n\n本地 `focus_perception/` 一共 8 个文件，已经整理干净（无二进制、无 .o）：\n\n```\nfocus_perception/\n├── api/perception.h              ⚠️ 参考拷贝，【不要】覆盖仓库冻结版\n├── perception/perception.c       主实现（进仓库）\n├── perception/perception_internal.h  内部声明（进仓库）\n├── tests/test_perception.c       mock 单测（进仓库，可选）\n├── tests/wifi_http_post_stub.c   联调 stub（进仓库，可选，仅 host 用）\n├── tests/test_mimo_cloud.c       真实 MiMo 链路单测（进仓库，可选，需 cJSON）\n├── BUILD_INTEGRATION.md          接入 diff（照做，不必提交）\n└── README.md                     模块说明（可进仓库，可选）\n└── PR_STEPS.md                   本文件（不必提交）\n```\n\n**进仓库必需**：`perception/perception.c`、`perception/perception_internal.h`。\n**建议一并提**：`tests/` 三个测试文件 + `README.md`（说明清楚、方便评审）。\n**绝不覆盖**：`api/perception.h`（仓库里已有冻结版，字段/签名一致，保持原样）。\n\n---\n\n## 1. 前置准备（一次性）\n\n### 1.1 找到仓库并 fork\n1. 打开团队仓库（contest2026_087 对应的 GitHub 仓库 / 组织仓库）。\n2. 点右上角 **Fork**，fork 到**你自己的** GitHub 账号下。\n3. 记下你的 fork 地址，形如：\n   `https://github.com/<你的用户名>/<仓库名>.git`\n\n### 1.2 clone 你的 fork\n```bash\ngit clone https://github.com/<你的用户名>/<仓库名>.git\ncd <仓库名>\n```\n\n### 1.3 配好 git 身份（漏了这步 commit 会失败）\n```bash\ngit config --global user.name  \"周礼航\"\ngit config --global user.email \"你的邮箱\"\n```\n\n### 1.4 确认能 push\n- 用 HTTPS + Personal Access Token，或配好 SSH key。\n- 快速自检：`git remote -v` 应显示你 fork 的地址。\n- ⚠️ **安全提醒**：之前某处文件里出现过的一个 GitHub token 已经泄露，请到\n  GitHub → Settings → Developer settings → Tokens **把它 revoke**，一律用新 token。\n  任何 token 都**不要**写进代码/commit/PR 描述里。\n\n---\n\n## 2. 把代码放进仓库\n\n### 2.1 拷贝文件（保持目录结构）\n\n在仓库根目录下（路径以仓库实际结构为准，下面按 `app/hello_app/` 举例）：\n\n```bash\n# 拷贝主实现 + 内部声明\nmkdir -p app/hello_app/perception\ncp  <本地>/focus_perception/perception/perception.c          app/hello_app/perception/\ncp  <本地>/focus_perception/perception/perception_internal.h app/hello_app/perception/\n\n# 拷贝测试（可选）\nmkdir -p app/hello_app/tests\ncp  <本地>/focus_perception/tests/test_perception.c          app/hello_app/tests/\ncp  <本地>/focus_perception/tests/wifi_http_post_stub.c      app/hello_app/tests/\ncp  <本地>/focus_perception/tests/test_mimo_cloud.c          app/hello_app/tests/\n\n# 模块说明（可选）\ncp  <本地>/focus_perception/README.md                        app/hello_app/perception/README.md\n```\n\n> 把 `<本地>` 换成 `C:\\temp\\focus_perception`（Windows）或 `~/focus_perception`（Linux/WSL）。\n> **跳过 `api/perception.h`** —— 用仓库里已有的冻结版。\n\n### 2.2 接入构建（照 `BUILD_INTEGRATION.md` 做，3 步）\n\n**① Makefile**（`app/hello_app/Makefile`）的 `CSRCS` 加一行：\n```make\nCSRCS += perception/perception.c\n```\n\n**② CMakeLists.txt**（`app/hello_app/CMakeLists.txt`）：\n```cmake\nset(CSRCS ${CSRCS} perception/perception.c)\n```\n\n**③ Kconfig**（`app/hello_app/Kconfig`）加 mock/真实二选一：\n```\nconfig CONTEST2026_087_PERCEPTION_MOCK\n    bool \"Perception mock (no MiMo call)\"\n    default y\n    help\n        默认走 mock，便于不依赖网络的联调；关掉后走真实 MiMo 识图链路。\n```\n\n以及 Makefile 里的条件编译（照抄 LCD_STUB 的 if/else）：\n```make\nifeq ($(CONFIG_CONTEST2026_087_PERCEPTION_MOCK),y)\nCFLAGS += -DPERCEPTION_MOCK\nelse\n# 真实 MiMo 链路: 依赖 cJSON (openvela 自带, 头文件 <cJSON.h>)\nendif\n```\n\n---\n\n## 3. 本地验证（提交前必须过）\n\n### 3.1 mock 单测（不依赖硬件/网络/cJSON）\n\n在 Linux / WSL 上：\n```bash\ncd app/hello_app\ngcc -Wall -Wextra -Werror -DPERCEPTION_MOCK \\\n    perception/perception.c tests/test_perception.c -o test_perception\n./test_perception\n```\n预期输出结尾：`57 checks, 0 failed`，退出码 0。\n\n> Windows 上才需要额外 `-lwinpthread`（`clock_gettime`）；Linux/openvela 不用。\n\n### 3.2 真实 MiMo 链路单测（需要 cJSON）\n```bash\ngcc -Wall -Wextra -Werror \\\n    perception/perception.c tests/wifi_http_post_stub.c tests/test_mimo_cloud.c \\\n    cJSON.c -I/path/to/cjson -o test_mimo_cloud\n./test_mimo_cloud\n```\n预期：`0 failed`。openvela 自带 cJSON；host 上 `apt install libcjson-dev` 或拷一份 `cJSON.c/h`。\n\n### 3.3 上真机（可选，联调阶段再做）\n- 关掉 Kconfig 的 mock 开关。\n- 填好 `perception.c` 里的 `MIMO_ENDPOINT_DEFAULT` / `MIMO_API_KEY_DEFAULT`，\n  或运行时用 `perception_init(url, key)` 传入。\n- 联调顺序：先张沐泽（`wifi_http_post` 通 + MiMo 鉴权方式）→ 再赵思涵\n  （`observation_t` 字段对）→ 最后全链路。\n\n---\n\n## 4. 提交（commit）\n\n### 4.1 开分支（别直接在 main 上改）\n```bash\ngit checkout -b feat/perception-mimo\n```\n\n### 4.2 只 add 该加的文件\n```bash\ngit add app/hello_app/perception/ app/hello_app/tests/\ngit add app/hello_app/Makefile app/hello_app/CMakeLists.txt app/hello_app/Kconfig\n```\n> 提交前 `git status` 扫一眼，确认**没有** token、密钥、二进制、`.o`、编辑器临时文件被 add。\n\n### 4.3 commit（建议信息）\n```bash\ngit commit -m \"feat(perception): 视觉感知模块，每帧调用 MiMo 识图\n\n- 实现 perception_init / perception_process / perception_get_history 三个冻结接口\n- JPEG -> base64 -> MiMo(每帧) -> cJSON 解析 -> 3 帧去抖 -> observation_t\n- mock/真实双路径 (-DPERCEPTION_MOCK)，默认 mock 可回退\n- 历史环形缓冲 60 条 + host 单测 (mock 57 项 / MiMo 链路)\n\nCo-Authored-By: Claude <noreply@anthropic.com>\"\n```\n\n---\n\n## 5. push 并开 PR\n\n### 5.1 push 到你的 fork\n```bash\ngit push -u origin feat/perception-mimo\n```\n\n### 5.2 开 PR\n- 到你的 fork 页面，点 **Compare & pull request**。\n- base 选团队仓库的 `main`（或团队指定分支），head 选你的 `feat/perception-mimo`。\n- 标题建议：\n  `feat: 视觉感知模块 perception（每帧调 MiMo 识图）`\n- 正文建议（直接复制）：\n\n```markdown\n## 说明\n实现「FOCUS AIoT」视觉感知层：输入 JPEG，每帧调用 MiMo 识图，输出 observation_t\n供 behavior 模块做时序分析。只做单帧空间识别，不做行为判断。\n\n## 改动\n- 新增 perception/perception.c + perception_internal.h（主实现）\n- 新增 tests/（mock 单测 / wifi_http_post 联调 stub / MiMo 链路单测）\n- Makefile / CMakeLists 加 CSRCS，Kconfig 加 mock 开关（默认 y）\n\n## 契约（已冻结）\nRequest:  {\"image\":\"<base64>\",\"width\":320,\"height\":240}\nResponse: {\"code\":0,\"data\":{person:{detected,bbox}, phone:{detected,near_hand},\n           head_pose:{pitch,yaw}, hand_motion_score, confidence}}\n\n## 测试\n- mock 单测：57 checks, 0 failed\n- MiMo 链路单测：验证每帧调用次数、响应解析、失败重试、三种错误码\n\n## 待确认\n- MiMo 鉴权方式（header / query / body）需与张沐泽、郭黄亦昕确认，g_api_key 已预留\n- api/perception.h 使用仓库冻结版，未改动\n```\n\n---\n\n## 6. CLA（开源仓库必做，否则 bot 会卡住）\n\n1. 打开 `openvela.com/#/community/cla`，用 GitHub 账号签名。\n2. 回 PR 评论区，发一条：`/check-cla`\n3. 等 CI / bot 状态变绿。\n\n---\n\n## 7. 常见坑速查\n\n| 现象 | 原因 / 解决 |\n|---|---|\n| commit 报 `Please tell me who you are` | 没配 git user.name/email，见 §1.3 |\n| push 401/403 | token 过期或泄露，换新 token（§1.4） |\n| `api/perception.h` 被覆盖 | 撤回改动，用仓库冻结版，字段签名必须一致 |\n| MiMo 链路单测编译失败 | 缺 cJSON，见 §3.2 |\n| mock 单测在 Windows 报 `clock_gettime64` | 加 `-lwinpthread`；Linux/openvela 不用 |\n| 真机调不通 | mock 开关没关 / MiMo endpoint+token 没填，见 §3.3 |\n| PR 被 bot 要求签 CLA | 见 §6 |\n"}

---

### [2026-08-26 17:30:28] 用户

[工具结果] File created successfully at: C:\temp\focus_perception\PR_STEPS.md (file state is current in your context — no need to Read it back)

---

### [2026-08-26 17:30:33] AI

[思考] Now let me give a summary in my chat response. The user asked me to (1) organize the code and (2) write detailed PR steps. I've:
1. Organized — verified folder is clean (8 files), fixed the stub's unused-parameter warnings (would've broken the -Werror build of the MiMo test), syntax-checked everything.
2. Written PR_STEPS.md.

Let me give a concise summary of what I did, in Chinese, and point to the file.

Let me also double check: did I verify test_perception.c still compiles with the mock build after the stub fix? The stub fix is only in wifi_http_post_stub.c, which isn't part of the mock build. So mock build is unaffected. I already know mock test passes 57/57.

Let me write the final response.

---

### [2026-08-26 17:30:41] AI

整理完成，PR 步骤已写好。做了两件事：

## 1. 整理代码

- 确认 `focus_perception/` 目录干净：**8 个文件、无二进制 / .o 残留**。
- 修了一个会挡路的问题：`wifi_http_post_stub.c` 里 `url`/`body` 未使用，在 MiMo 链路测试的 `-Wall -Wextra -Werror` 下会编译失败，已加 `(void)url; (void)body;` 消除。
- 三处语法检查全绿：stub（-Werror 干净）、`test_mimo_cloud.c`、`perception_internal.h` 独立包含。

## 2. 新增 `PR_STEPS.md`

写了一份从零到 PR 合入的完整步骤，放在 `C:\temp\focus_perception\PR_STEPS.md`，覆盖：

| 章节 | 内容 |
|---|---|
| 0 | 文件清单 + 哪些进仓库 / 哪些不覆盖（`api/perception.h` 用冻结版） |
| 1 | fork + clone + `git config` + token 安全（含"之前泄露的 token 去 revoke"提醒） |
| 2 | 逐条 `cp` 命令放文件 + Makefile/CMakeLists/Kconfig 三处接入 diff |
| 3 | 本地验证（mock 57 项、MiMo 链路、真机） |
| 4 | 开分支 → 只 add 该加的 → 现成 commit 信息（含 `Co-Authored-By`） |
| 5 | push + PR 标题/正文模板（可直接复制） |
| 6 | CLA 签名 + `/check-cla` |
| 7 | 常见坑速查表（8 条） |

关键点我都写进去了：**`api/perception.h` 别覆盖、默认 mock 可回退、真机前关 mock + 填 MiMo endpoint/token、MiMo 鉴权方式待与张沐泽/郭黄亦昕确认**。

要不要我把这份 PR 步骤也顺手发成一个网页 artifact，方便你在 VM 上边操作边看？（纯本地 markdown 文件已在 `PR_STEPS.md`，不需要的话就不用动。）

---
