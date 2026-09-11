# FOCUS AIoT — 学习专注监测终端

> 队伍编号 087 ｜ 赛道：AI 硬件产品创新 ｜ 硬件：ESP32-S3-EYE + openvela

## 一、作品简介

FOCUS AIoT 是一台放在书桌上的**学习专注监测终端**。它用板载摄像头持续拍摄学习画面，
通过**视觉模型**判断学习者是否在玩手机、是否离座、是否瞌睡，实时在 240×240 LCD 上
给出状态与提醒；一次学习结束后，设备把统计上报服务器，由 **LLM 生成学习建议**，
完整报告在网页端查看。

**亮点**：

- **双模式**：严格模式（紧盯不放）与鼓励模式（温柔提醒），共用硬件，策略/文案/阈值全不同。
- **端云协同**：设备只负责采集与显示，视觉识别与建议生成放在**自托管模型 + 服务器**，
  设备无需 TLS 栈、无需大算力。
- **网页报告**：设备屏只有 240×240，长文本放不下 —— 完整学习报告（含 LLM 建议正文）
  在网页端呈现，设备屏只提示网址。
- **全链路可复现**：视觉模型、中转服务器、内网穿透、固件编译烧录，本文档给出从零步骤。

## 二、选题方向

**AI 硬件产品创新**。

理由：本作品是"硬件 + 端侧采集 + 云端 AI"的完整产品形态，重点在于把
**视觉理解模型**落到真实可用的硬件终端上，并解决"设备算力/网络受限时如何使用云端 AI"
这一工程问题（固件无 TLS 栈 → HTTP 中转；屏幕小 → 网页报告）。

## 三、系统架构

```
┌──────────────┐  ① RGB565 采集
│ ESP32-S3-EYE │──────────────┐
│   openvela   │              ▼
│              │       ② TinyJPEG 编码 (160×120 降采样)
│ 摄像头/LCD/  │              ▼
│ 按键/LED     │       ③ HTTP POST base64 图
└──────┬───────┘              ▼
       │              ┌─────────────────────┐
       │              │  中转服务器(公网)    │
       │              │  tools/mimo_relay.py│
       │              │  :8060              │
       │              └───┬─────────────┬───┘
       │  ⑤ LLM 建议       │             │ ④ 转发图片
       │                   ▼             ▼
       │            ┌───────────┐  ┌─────────────┐
       │            │ MiMo API  │  │ frp 内网穿透 │
       │            │ (建议生成) │  │ :7000       │
       │            └───────────┘  └──────┬──────┘
       │                                 ▼
       │                        ┌────────────────────┐
       └── ⑥ 网页 /report  ─────│ 本机视觉模型服务    │
              /preview          │ YOLOv8+手部分割:8000│
                                └────────────────────┘
```

**为什么这么设计**：ESP32 固件没有 TLS 栈，无法直连 HTTPS 云端 API；视觉模型需要 GPU，
跑在 PC 上。因此由中转服务器做协议转换与转发，并顺带提供网页报告。

## 四、目录结构

```text
contest2026_087_gaiduimingyizhanyongdui/
├─ app/hello_app/            # 设备端应用（openvela 应用）
│  ├─ api/                   # 团队冻结的跨模块接口
│  ├─ core/                  # 状态机 FSM、会话统计、RGB565→JPEG 编码
│  │  ├─ state_machine.c     #   4 状态：IDLE/MODE_SELECT/MONITORING/REPORT
│  │  └─ rgb565_jpeg.c       #   TinyJPEG 编码（含 160×120 降采样）
│  ├─ perception/            # 视觉感知：JPEG → 识图服务 → observation_t（3 帧去抖）
│  ├─ behavior/              # 行为分析：observation 时序 → study_state_t（双模式阈值）
│  ├─ ui/                    # LCD 页面渲染、中文字库、图标
│  ├─ hardware/              # 真实驱动：OV2640(V4L2)、WiFi、按键、音频、ST7789
│  └─ tests/                 # 主机单元测试（UI/行为/感知）
├─ board/contest_board/      # 板级配置
│  └─ configs/hwtest/defconfig   # ← 本作品使用的 openvela 配置
├─ tools/
│  ├─ mimo_relay.py          # 中转服务器：识图转发 + 学习报告 + 网页
│  └─ generate_ui_cjk_font.py# 中文字库生成脚本
├─ logs/                     # AI Coding 对话日志
├─ 视觉模型README.md          # 视觉模型服务的完整说明（模型/阈值/接口/许可）
└─ README.md
```

## 五、从零搭建（评委复现步骤）

分五步：**① 拉取工程 → ② 编译烧录固件 → ③ 部署视觉模型 → ④ 部署中转服务器 + 内网穿透 → ⑤ 全链路验证**

---

### 步骤 1：拉取 openvela 全量工程

```bash
repo init -u https://github.com/open-vela/contest2026_087_gaiduimingyizhanyongdui \
  -b dev-ai-contest-2026 -m contest2026_087_gaiduimingyizhanyongdui.xml
repo sync -c -j8
```

同步后本仓位于工作区 `contest2026_087_gaiduimingyizhanyongdui/`，
openvela 源码在外层（`nuttx/`、`apps/`、`packages/`、`vendor/`）。

> `app/hello_app/` 会通过 manifest 的 `<linkfile>` 软链到
> `packages/demos/contest2026_087_hello_app`，**无需手动拷贝**。

---

### 步骤 2：编译并烧录设备固件

**环境**：Linux（推荐 Ubuntu 22.04），工具链用 openvela prebuilts 自带即可。

```bash
# 进入 openvela 工作区根目录（本仓的上一级）
cd ..

# 用本作品的板级配置编译（首次会拉依赖并全量编译，约 10-20 分钟）
./build.sh contest2026_087_gaiduimingyizhanyongdui/board/contest_board/configs/hwtest -j2
```

产物：`nuttx/nuttx.bin`

**增量编译**（改代码后更快）：

```bash
export PATH=$PWD/vela-opensource/prebuilts/gcc/linux-x86_64/xtensa-esp32s3-elf/bin:$PATH
make -C nuttx -j2
```

**烧录**（需 esptool）：

```bash
esptool -c esp32s3 -p COM6 -b 460800 \
  --before default-reset --after hard-reset \
  write_flash 0x0 nuttx.bin
```

> `-p` 换成你的串口（Windows `COM6`，Linux `/dev/ttyUSB0`）。
> 若报 `invalid header`，确认烧到地址 `0x0` 且带 `--after hard-reset`。

**运行**：

```
nsh> hello_app hwwifi <你的WiFi名> <密码>     # 连 WiFi（识图需要）
nsh> hello_app                                # 启动主程序
```

**按键操作**（BOOT 键）：

| 操作 | 效果 |
|---|---|
| 长按 1–3 秒 | 进入模式选择（严格/鼓励） |
| 短按 | 开始监测 / 切换模式 / 从报告页返回 |
| 超长按 >3 秒 | 结束本次学习，进入报告页 |

> 只有**进入监测状态后**才采集与识图（IDLE/模式选择/报告页不采集）。

---

### 步骤 3：部署视觉模型服务（本机，建议 GPU）

本作品使用的视觉模型是 **Phone-Use Detection Service**（YOLOv8 + 手部分割），
完整说明见仓库内 `视觉模型README.md`。简述：

```bash
# 需要 Python 3.10+ 与 NVIDIA GPU（CPU 推理会明显变慢）
python -m venv .venv

# Windows:
.venv\Scripts\python -m pip install -r requirements.txt
# Linux/macOS:
.venv/bin/python -m pip install -r requirements.txt

# 下载手部权重（手机权重首次推理自动下载）
.venv/Scripts/python scripts/download_weights.py

# 启动服务（监听 0.0.0.0:8000）
.venv/Scripts/python scripts/run_server.py
```

启动成功输出：`Phone-use detection server on http://0.0.0.0:8000  (LAN accessible)`

**自测**（务必用**局域网 IP** 而非 127.0.0.1，并绕过系统代理）：

```bash
curl --noproxy "*" -X POST http://192.168.x.x:8000/detect -F "file=@photo.jpg"
```

返回示例：

```json
{
  "using_phone": true, "has_person": true, "confidence": 0.87,
  "reason": "hand_grabbing_phone",
  "phone": {"label": "cell phone", "bbox": [218,185,325,329]},
  "hand":  {"label": "hand",       "bbox": [241,243,404,332]},
  "persons": [{"label": "person",  "bbox": [104,12,453,330]}],
  "img_shape": [337, 596]
}
```

**模型说明**：手机检测用 YOLOv8n(COCO)，手部用 YOLO26m-seg-hand
（FreiHAND+HaGRID 训练，AGPL-3.0）。判定逻辑为「手框与手机框 IoU 超阈值 **或**
手中心落在手机框按 `hand_center_margin` 扩展的区域内」。阈值集中在
`app/detector.py` 的 `DetectorConfig`。GPU（RTX 4060）单帧约 **78ms**，冷启动约 2s。

---

### 步骤 4：部署中转服务器 + 内网穿透

设备没有 TLS 栈无法直连 HTTPS；视觉模型跑在你 PC 的局域网内。因此需要：
(a) 一台**有公网 IP 的服务器**跑中转；(b) 用 **frp 内网穿透**把服务器请求打到本机模型。

#### 4.1 服务器：启动中转服务

```bash
# 把本仓的 tools/mimo_relay.py 上传到服务器
scp tools/mimo_relay.py root@<服务器IP>:/root/

# 启动（DETECT_URL 指向 frp 映射出的本机模型端口，见 4.2）
RELAY_TOKEN=focus087relay \
PORT=8060 \
DETECT_URL=http://127.0.0.1:8001/detect \
MIMO_API_KEY=<你的 MiMo API Key，用于生成学习建议> \
nohup python3 /root/mimo_relay.py > /root/relay.log 2>&1 &
```

云服务器安全组需放行 **8060**（设备与网页访问）与 **7000**（frp）。

> `MIMO_API_KEY` 仅用于**学习报告的建议生成**，可不填（会退回本地模板文案），
> 不影响识图功能。

#### 4.2 内网穿透：frp（服务器跑 frps，本机跑 frpc）

**服务器侧**：

```bash
cat > /root/frp/frps.toml <<'EOF'
bindPort = 7000
auth.method = "token"
auth.token = "focus087frp"
proxyBindAddr = "127.0.0.1"   # 映射端口只绑回环，模型服务不暴露公网
EOF

nohup /root/frp/frps -c /root/frp/frps.toml > /root/frps.log 2>&1 &
```

**本机侧**（Windows，`C:\frp\frpc.toml`）：

```toml
loginFailExit = false          # 断线自动重连，不退出
serverAddr = "<服务器IP>"
serverPort = 7000
auth.method = "token"
auth.token = "focus087frp"

[[proxies]]
name = "phone-detect"
type = "tcp"
localIP = "127.0.0.1"
localPort = 8000               # 本机视觉模型服务
remotePort = 8001              # 映射到服务器的 127.0.0.1:8001
```

```powershell
C:\frp\frpc.exe -c C:\frp\frpc.toml
```

**验证隧道**（服务器上执行，应返回 `{"status":"ok",...}`）：

```bash
curl -s -m 8 http://127.0.0.1:8001/health
```

#### 4.3 设备端地址配置

若你的服务器 IP 与默认不同，改这三处后重新编译：

| 文件 | 常量 | 说明 |
|---|---|---|
| `app/hello_app/perception/perception.c` | `MIMO_ENDPOINT_DEFAULT` | 识图端点 `http://<服务器>:8060/v1/chat/completions` |
| `app/hello_app/ui/mimo.c` | `REPORT_API_URL` | 报告上传 `http://<服务器>:8060/report` |
| `app/hello_app/perception/perception.c` | `MIMO_API_KEY_DEFAULT` | 中继令牌（= 服务器的 `RELAY_TOKEN`） |

---

### 步骤 5：验证全链路

| # | 检查项 | 命令/现象 |
|---|---|---|
| 1 | 本机模型 | `curl --noproxy "*" http://127.0.0.1:8000/health` → ok |
| 2 | 隧道 | 服务器 `curl -s http://127.0.0.1:8001/health` → ok |
| 3 | 中继 | 服务器 `ss -tlnp \| grep 8060` |
| 4 | 设备 | `hello_app hwwifi <ssid> <pass>` 后 `hello_app` |

**串口应看到**：

```
[state_machine] MODE_SELECT -> MONITORING
[cam] #1 采集OK 153600B -> 转JPEG...
[cam] #1 JPEG 1xxxxB -> 云端识图...          ← 降采样后约 15-25KB
[percep] 识图 HTTP OK, resp=HTTP/1.0 200 OK
[percep] 识图 person=1 phone=1 inhand=1 pitch=0.0 motion=1.00 conf=0.6x
```

**网页端**：

- 实时画面预览：`http://<服务器IP>:8060/preview`
- 学习报告：`http://<服务器IP>:8060/report`（完成一次学习后生成）

## 六、中转服务器接口

`tools/mimo_relay.py` 除转发外还提供网页服务：

| 路由 | 方法 | 说明 |
|---|---|---|
| `/v1/chat/completions` | POST | 设备识图请求（OpenAI 兼容）→ 转发视觉模型 → 转回设备格式 |
| `/report` | POST | 设备上报学习统计 → 调 LLM 生成建议 → 存盘 |
| `/report` | GET | 完整学习报告网页 |
| `/report.json` | GET | 报告数据（网页 JS 拉取） |
| `/preview` | GET | 摄像头实时预览网页 |
| `/preview.jpg` | GET | 最新一帧画面 |

**协议转换由中继完成**（设备发 OpenAI 格式，视觉模型是 multipart 表单且字段名不同），
因此**设备固件无需感知后端模型**，换模型只改中继。

## 七、主机单元测试

无需硬件即可运行：

```bash
cmake -S app/hello_app/tests -B build/focus-aiot-tests
cmake --build build/focus-aiot-tests
ctest --test-dir build/focus-aiot-tests --output-on-failure
```

UI 单测也可独立编译（复用 `lcd.c` 的 `UI_UNIT_TEST` 调试接口）：

```bash
cd app/hello_app
gcc -o /tmp/t_ui tests/test_ui.c ui/lcd.c ui/lcd_icons.c ui/mimo.c \
    ui/ui_cjk_font.c ui/ui_draw.c -DUI_UNIT_TEST -I. -Iapi -Iui -lpthread
/tmp/t_ui
```

## 八、AI Coding 使用说明

本作品全程使用 AI 辅助开发：

- **需求拆解与接口设计**：把"学习监测"拆成 5 个可并行模块，冻结 `api/*.h` 接口，
  5 名成员并行开发互不阻塞。
- **跨模块集成**：由 AI 将各成员提交的实现接入主循环，并解决合并冲突
  （如感知模块换模型时与主线的冲突）。
- **深度调试**：多个硬件级问题由 AI 主导定位，例如：
  - **任务栈溢出踩坏 TLS 导致 `printf` 崩溃** —— 反汇编算出 TinyJPEG 单帧栈帧
    8032 字节，超出当时 8KB 的任务栈（且发现 builtin 注册表缓存导致 STACKSIZE
    改动未生效）；
  - **摄像头第 2 帧起采集失败** —— 读内核 `v4l2_cap.c` 发现 RING 模式判据为
    `vbuf_top != vbuf_next`，未消费容器残留导致 `-ENOMEM`；
  - **大图上传压垮 WiFi** —— 把崩溃栈解析到 `esf_buf_alloc_dynamic` / `up_irq_restore`，
    定位为请求体过大，据此引入降采样与缓冲调整。
- **文档**：本 README 的搭建步骤与排障说明由 AI 整理。

完整对话日志见 `logs/` 目录。

## 九、已知限制

- **大请求体下的 WiFi 稳定性**：向 WiFi 发送路径一次性灌入过大请求体
  （>80KB base64）时，可能出现 `CPU1 IDLE` / `hpwork` 崩溃（ESP32-S3 SMP 与 WiFi
  驱动的内核级问题，`VADDR` 落在代码段）。本作品已通过**上传图降采样至 160×120
  （请求体约 25KB）+ 分块发送 + 调大 IOB/WiFi 缓冲**显著缓解，实测可连续多帧识图；
  长时间运行若仍偶发，属该 openvela 移植的底层问题，非应用逻辑缺陷。
- **AI 建议依赖 LLM Key**：未配置有效 `MIMO_API_KEY` 时，报告建议正文由规则模板生成，
  功能不受影响。
- **视觉模型建议 GPU**：CPU 推理会明显变慢，建议用带 NVIDIA GPU 的机器。
- **中继与前缀依赖**：演示时本机的视觉模型服务与 `frpc` 必须保持运行，否则识图失败。

## 十、许可

- 本仓代码：参赛作品。
- 手部模型 `NightingaleCen/YOLO26m-seg-hand`：AGPL-3.0。
- YOLOv8 / ultralytics：AGPL-3.0。
- TinyJPEG：public domain。
