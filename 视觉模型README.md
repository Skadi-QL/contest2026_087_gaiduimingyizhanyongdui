# Phone-Use Detection Service

基于 **YOLOv8 + 手部分割** 的"使用手机"行为检测 HTTP 服务。

用于把嵌入式设备（如摄像头/开发板）拍摄的图像传入本机推理服务，服务返回 JSON 判定结果，
再由设备显示/报警。

## 工作方式

```
嵌入式设备(拍照)  --HTTP POST-->  本机 FastAPI 服务  --JSON--> 设备显示/报警
```

也支持你的"中转服务器"架构：

```
嵌入式设备 --图片--> 中转服务器 --HTTP POST /detect--> 本机 FastAPI 服务
设备 <--JSON-- 中转服务器 <--JSON (using_phone: true/false)--
```

中转服务器只需要把这个服务的 HTTP 接口包一层即可。

## 模型

| 用途 | 模型 | 说明 |
|---|---|---|
| 手机检测 | YOLOv8n (COCO) | 检测 `cell phone`，ultralytics 首次使用自动下载 |
| 手部检测 | NightingaleCen/YOLO26m-seg-hand | FreiHAND+HaGRID 训练的手部分割模型 ~52MB |

复合判定（尺度无关，适配不同分辨率摄像头）：
手部框与手机框 **IoU ≥ 阈值**，**或** 手框中心落在手机框按 `hand_center_margin`(默认 0.6)扩展的区域内 → 判定"使用手机"。

实测（RTX 4060 Laptop，640 输入）：
- 稳态单帧延迟：**~78 ms**
- 冷启动（首次请求，含模型加载）：~2 s

阈值见 `app/detector.py` 的 `DetectorConfig`。

## 快速开始

```bash
# 1. 安装依赖（首次含 torch-CUDA，需几分钟）
.venv/Scripts/python -m pip install -r requirements.txt

# 2. 下载手部权重（手机权重下载到 weights/）
.venv/Scripts/python scripts/download_weights.py

# 3. 启动服务
.venv/Scripts/python scripts/run_server.py
```

服务监听 `0.0.0.0:8000`，局域网内设备可访问。

## API

### `POST /detect`

上传图片，返回 JSON 判定。

```bash
curl -X POST http://<本机IP>:8000/detect \
  -H "Content-Type: multipart/form-data" \
  -F "file=@photo.jpg"
```

响应示例：

```json
{
  "using_phone": true,
  "confidence": 0.77,
  "reason": "phone_near_or_overlapping_hand",
  "elapsed_ms": 42.1,
  "phone": {"label": "cell phone", "conf": 0.91, "bbox": [120, 80, 200, 150], "mask_poly": []},
  "hand": {"label": "hand", "conf": 0.85, "bbox": [110, 75, 210, 160], "mask_poly": [[...]]},
  "detections": [ ... ],
  "img_shape": [1080, 1920]
}
```

| 字段 | 说明 |
|---|---|
| `using_phone` | 是否判定为使用手机 |
| `confidence` | 复合置信度（配对手机×手部置信度） |
| `reason` | 判定原因，便于调试 |
| `phone` / `hand` | 命中的手机/手部目标（`bbox` 为 xyxy） |
| `detections` | 全部检测框 |

### `POST /detect/visualize`

上传图片，返回画好检测框的 JPG（调试用）。

```bash
curl -X POST http://<本机IP>:8000/detect/visualize \
  -F "file=@photo.jpg" -o annotated.jpg
```

### `GET /health`

服务健康检查，返回是否使用 GPU。

## 自测客户端

```bash
.venv/Scripts/python scripts/send_image.py sample_images/photo.jpg
```

## 调整阈值

所有行为阈值都在 `app/detector.py` 的 `DetectorConfig` 中，可改代码或传参调整：

- `iou_threshold`：手手机框重叠阈值（更严格拉高，宽松调低）
- `center_dist_px`：手部中心与手机框中心距离阈值
- `conf`：检测置信度门槛

## 嵌入式设备接入注意事项

- 通信走 HTTP multipart 上传图片，设备端只需支持 HTTP POST + 解析 JSON。
- 本机 IP 用 `ipconfig` 查（局域网内设备需同网段）。
- 实时性：RTX 4060 上单帧约几十毫秒量级；若设备端图片很大，可先在设备端缩小再上传。

## 许可

- 本服务代码：见仓库（未声明许可则按 AGPL-3.0 参考模型来源 NightingaleCen）。
- 手部模型 `NightingaleCen/YOLO26m-seg-hand`：AGPL-3.0。
- YOLOv8 / ultralytics：AGPL-3.0。