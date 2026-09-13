#!/usr/bin/env python3
"""
FOCUS AIoT - 串口桥接 (tools/serial_bridge.py)
================================================
设备经 USB 串口把 JPEG 发给本脚本, 本脚本调用本机视觉模型识别, 再把结果
写回串口给设备。**完全绕开 WiFi** —— 设备经 WiFi 发大包会触发 openvela
ESP32-S3 SMP 移植的 WiFi 驱动崩溃 (esf_buf_alloc_dynamic)。

  设备 --USB 串口--> 本脚本 --> 视觉模型 (:8000 /detect)
  设备 <--USB 串口-- 本脚本 <-- JSON

设备端协议 (见 app/hello_app/core/serial_link.h):
  设备 → 电脑:  ###IMG <b64len>\\n<base64>\\n###ENDIMG
  电脑 → 设备:  ###RESULT <jsonlen>\\n<json>\\n###ENDRESULT
  设备 → 电脑:  ###REPORT <jsonlen>\\n<json>\\n###ENDREPORT
                 (一局结束上报统计, 本脚本转投服务器生成学习报告)

用法:
  python serial_bridge.py --port COM6                  # Windows
  python serial_bridge.py --port /dev/ttyUSB0          # Linux

  # 可选: 指定模型服务与报告服务器
  python serial_bridge.py --port COM6 \\
      --detect-url http://192.168.43.5:8000/detect \\
      --report-url http://<服务器IP>:8060/report
"""

import argparse
import base64
import json
import sys
import threading
import time
import urllib.error
import urllib.request

import serial  # pyserial


def stdin_pump(ser):
    """把本窗口的键盘输入转发到串口, 这样可以直接敲 nsh 命令 (如 hello_app)。

    桥接脚本同时充当串口终端: 设备日志打印到本窗口, 键盘输入发回设备。
    """
    while True:
        try:
            line = sys.stdin.readline()
        except Exception:  # noqa: BLE001
            return
        if not line:
            return
        try:
            ser.write(line.encode("utf-8", "replace"))
            ser.flush()
        except Exception:  # noqa: BLE001
            return


# ----------------------------------------------------------------------
# 设备期望的字段映射 (与 tools/mimo_relay.py 保持一致)
# ----------------------------------------------------------------------

def to_openai_envelope(result):
    """视觉模型返回 → 设备期望的 OpenAI chat/completions 信封。

    设备 perception.c 从 choices[0].message.content 取 JSON, 字段:
      person_present / person_bbox[x,y,w,h 归一化] / phone_detected /
      phone_near_hand / head_pitch / head_yaw / hand_motion_score / confidence

    本机模型无头部姿态/运动量: 头姿置 0; hand_motion_score 用作"玩手机"开关
    (行为引擎要求 >0.3 才判 PLAYING_PHONE), 按"看手机也归为玩手机"一刀切,
    using_phone=true 时置 1.0。
    """
    persons = result.get("persons") or []
    img_shape = result.get("img_shape") or [0, 0]
    img_h = float(img_shape[0]) or 0.0
    img_w = float(img_shape[1]) or 0.0

    bbox = [0.0, 0.0, 0.0, 0.0]
    if persons and img_w > 0 and img_h > 0:
        bb = persons[0].get("bbox") or []
        if len(bb) >= 4:
            x1, y1, x2, y2 = (float(bb[0]), float(bb[1]),
                              float(bb[2]), float(bb[3]))
            bbox = [
                max(0.0, min(1.0, x1 / img_w)),
                max(0.0, min(1.0, y1 / img_h)),
                max(0.0, min(1.0, (x2 - x1) / img_w)),
                max(0.0, min(1.0, (y2 - y1) / img_h)),
            ]

    using_phone = bool(result.get("using_phone"))
    observation = {
        "person_present": bool(result.get("has_person")),
        "person_bbox": bbox,
        "phone_detected": bool(result.get("phone")),
        "phone_near_hand": using_phone,
        "head_pitch": 0.0,
        "head_yaw": 0.0,
        "hand_motion_score": 1.0 if using_phone else 0.0,
        "confidence": float(result.get("confidence") or 0.0),
    }

    envelope = {
        "choices": [{
            "index": 0,
            "finish_reason": "stop",
            "message": {
                "role": "assistant",
                "content": json.dumps(observation, ensure_ascii=False),
            },
        }],
    }
    return json.dumps(envelope, ensure_ascii=False)


# ----------------------------------------------------------------------
# HTTP helpers
# ----------------------------------------------------------------------

# 本地模型服务调用必须绕过系统代理: 否则 urllib 会把发往 127.0.0.1 的请求
# 交给 http_proxy/all_proxy, 表现为**超时**(本项目实测踩过)。
_LOCAL_OPENER = urllib.request.build_opener(urllib.request.ProxyHandler({}))


def call_detect(detect_url, jpeg_bytes, timeout=30):
    """multipart/form-data 调视觉模型 (绕过系统代理)。"""
    boundary = "----focusaiotserialbridge"
    parts = [
        ("--%s\r\n" % boundary).encode(),
        b'Content-Disposition: form-data; name="file"; filename="frame.jpg"\r\n',
        b"Content-Type: image/jpeg\r\n\r\n",
        jpeg_bytes,
        ("\r\n--%s--\r\n" % boundary).encode(),
    ]
    body = b"".join(parts)
    req = urllib.request.Request(
        detect_url, data=body,
        headers={"Content-Type": "multipart/form-data; boundary=" + boundary})
    with _LOCAL_OPENER.open(req, timeout=timeout) as resp:
        return json.loads(resp.read().decode("utf-8", "replace"))


def forward_report(report_url, stats_json):
    if not report_url:
        return
    try:
        req = urllib.request.Request(
            report_url, data=stats_json.encode(),
            headers={"Content-Type": "application/json"})
        with urllib.request.urlopen(req, timeout=60) as resp:
            resp.read()
        print("[bridge] 报告已转投服务器", file=sys.stderr)
    except Exception as e:  # noqa: BLE001
        print("[bridge] 报告转投失败: %s" % e, file=sys.stderr)


# ----------------------------------------------------------------------
# 主循环: 逐行解析设备输出
# ----------------------------------------------------------------------

def sum16(data):
    """与设备端一致的 16 位累加和校验。"""
    return sum(data) & 0xFFFF


def read_payload(ser, length):
    """精确读取 length 字节。"""
    buf = b""
    while len(buf) < length:
        chunk = ser.read(length - len(buf))
        if not chunk:
            raise TimeoutError("等待设备数据超时")
        buf += chunk
    return buf


def skip_payload_tail(ser, marker):
    """读到并消费掉 marker 所在行。"""
    while True:
        line = ser.readline()
        if not line:
            return
        if marker in line:
            return


# 回写分块: 一次性写几百字节会让设备端输入缓冲来不及收而**丢字节**
# (实测: 回传 JSON 出现 "mesrole" 这类字符缺失)。小块 + 让出即可。
TX_CHUNK = 64
TX_GAP = 0.004


def paced_write(ser, data):
    """分块写入串口, 每块后短暂让出, 避免接收端丢数据。"""
    for i in range(0, len(data), TX_CHUNK):
        ser.write(data[i:i + TX_CHUNK])
        ser.flush()
        if i + TX_CHUNK < len(data):
            time.sleep(TX_GAP)


def skip_to_eol(ser):
    """消费掉当前行剩余部分 (到 \\n)。"""
    while True:
        ch = ser.read(1)
        if not ch or ch == b"\n":
            return


def main():
    ap = argparse.ArgumentParser(description="FOCUS AIoT 串口桥接")
    ap.add_argument("--port", required=True, help="串口号, 如 COM6 或 /dev/ttyUSB0")
    ap.add_argument("--baud", type=int, default=460800)
    ap.add_argument("--detect-url", default="http://127.0.0.1:8000/detect")
    ap.add_argument("--report-url", default="",
                    help="学习报告服务器 (留空则不上报), 如 http://<服务器IP>:8060/report")
    args = ap.parse_args()

    print("[bridge] 串口 %s @ %d" % (args.port, args.baud))
    print("[bridge] 视觉模型 %s" % args.detect_url)
    if args.report_url:
        print("[bridge] 报告服务器 %s" % args.report_url)

    ser = serial.Serial(args.port, args.baud, timeout=5)
    frames = 0

    # 键盘输入转发到串口 (可直接敲 nsh 命令), 后台线程运行
    threading.Thread(target=stdin_pump, args=(ser,), daemon=True).start()
    print("[bridge] 可在本窗口直接输入 nsh 命令 (如 hello_app); Ctrl+C 退出\n")

    try:
        while True:
            line = ser.readline()
            if not line:
                continue

            try:
                text = line.decode("utf-8", "replace").strip()
            except Exception:  # noqa: BLE001
                continue

            # ---- 图像请求: ###IMG <len> <sum> ----
            if text.startswith("###IMG "):
                try:
                    parts = text.split()
                    if len(parts) < 3:
                        print("[bridge] 协议错误: %s" % text, file=sys.stderr)
                        continue
                    want = int(parts[1])
                    want_sum = int(parts[2])

                    b64 = read_payload(ser, want)
                    skip_to_eol(ser)          # 吃掉 base64 后的换行
                    ser.readline()            # 吃掉 ###ENDIMG 行

                    # 校验: 丢字节则请设备重发整帧 (串口控制台大块传输不可靠)
                    if sum16(b64) != want_sum:
                        print("[bridge] 图片校验失败, 请求重传", file=sys.stderr)
                        paced_write(ser, b"###AGAIN\n")
                        continue

                    jpeg = base64.b64decode(b64)
                    t0 = time.time()
                    result = call_detect(args.detect_url, jpeg)
                    payload = to_openai_envelope(result).encode("utf-8")

                    # 回写: ###RESULT <len> <sum> (设备同样会校验并可能要求重发)
                    hdr = b"###RESULT %d %d\n" % (len(payload), sum16(payload))
                    paced_write(ser, hdr)
                    paced_write(ser, payload)
                    paced_write(ser, b"\n###ENDRESULT\n")

                    # 等设备 ACK: ###OK 表示校验通过, ###AGAIN 表示要重发结果
                    ser.timeout = 30
                    while True:
                        ack = ser.readline()
                        if not ack:
                            raise TimeoutError("等待设备 ACK 超时")
                        if b"###OK" in ack:
                            break
                        if b"###AGAIN" in ack:
                            print("[bridge] 设备请求重发结果", file=sys.stderr)
                            paced_write(ser, hdr)
                            paced_write(ser, payload)
                            paced_write(ser, b"\n###ENDRESULT\n")
                            continue

                    frames += 1
                    print("[bridge] #%d %dB -> using_phone=%s has_person=%s "
                          "(%dms)" % (frames, len(jpeg),
                                      result.get("using_phone"),
                                      result.get("has_person"),
                                      int((time.time() - t0) * 1000)),
                          file=sys.stderr)
                except Exception as e:  # noqa: BLE001
                    print("[bridge] 图像处理失败: %s" % e, file=sys.stderr)

            # ---- 报告上报 ----
            elif text.startswith("###REPORT "):
                try:
                    want = int(text[10:])
                    payload = read_payload(ser, want)
                    skip_to_eol(ser)
                    ser.readline()            # 吃掉 ###ENDREPORT 行
                    print("[bridge] 收到报告: %s" % payload.decode("utf-8", "replace"),
                          file=sys.stderr)
                    forward_report(args.report_url, payload.decode("utf-8", "replace"))
                except Exception as e:  # noqa: BLE001
                    print("[bridge] 报告处理失败: %s" % e, file=sys.stderr)

            # 其余是设备日志, 原样透传到终端便于观察
            else:
                sys.stdout.write(text + "\n")
                sys.stdout.flush()

    except KeyboardInterrupt:
        print("\n[bridge] 退出 (共处理 %d 帧)" % frames)
    finally:
        ser.close()


if __name__ == "__main__":
    main()
