---
name: nuttx-http-client-stability
description: 让 NuttX / openvela 上的 HTTP 客户端稳定上传大 body（每帧数十至数百 KB）。当出现：连续上传若干帧后 connect/send 失败、周期性上传中断、TIME_WAIT 或 IOB 耗尽、需要每帧 POST 一张图到服务器、想要用降分辨率/降采样「解决」上传失败、或要在嵌入式端实现 HTTP keep-alive 长连接时使用。
---

# NuttX HTTP 客户端大 body 上传稳定性

## 先定性：是不是「每帧新建连接」造成的

症状：连续上传若干帧后 `connect()` / `send()` 失败（连接类错误），重启后又能传几帧。

机理：一次 POST 走完 `socket → connect → send(body) → recv → close`。当 body
（base64 后可达 200 KB+）远大于 TCP 发送缓冲，且**帧率高于 TIME_WAIT 的回收速率**
时，连接资源与 IOB 池被逐步吃光 → `connect` 直接失败。

**先算一笔账**：`body 大小 ÷ CONFIG_NET_SEND_BUFSIZE` 若是十几倍，每帧都要反复灌满
/排空发送链；再看 `CONFIG_IOB_NBUFFERS × IOB_BUFSIZE` 是不是只有几十 KB。

## 主修法：整轮复用一条 TCP 长连接

不要每帧建连。维护一个持久 socket，请求带 `Connection: keep-alive`。

**关键陷阱**：keep-alive 下对端**不会关闭连接**，原来「一直 recv 直到返回 0」的读
响应方式会**永久阻塞**（直到 `SO_RCVTIMEO` 超时）。必须改为：

1. 读到 `\r\n\r\n` 拿到完整响应头；
2. 从响应头解析 `Content-Length`；
3. 按该长度读满响应体即返回。

只有在 HTTP/1.0 风格、无 `Content-Length` 时才退回「读到关闭」。

其它要点：

- 缓存 socket 时**按 host:port 记忆**，目标变了要重连；
- 出错就丢弃连接，下次调用重建，并**重发一次**（请求需幂等或可容忍重复）；
- 响应头里出现 `Connection: close` 时主动丢弃该连接；
- 单线程调用则无需加锁，但要在注释里写明这个前提；
- 响应缓冲要能同时装下**响应头 + 响应体**（调用方通常按 `\r\n\r\n` 跳头）。

## 服务端必须配套

- **`protocol_version = "HTTP/1.1"`。** Python `BaseHTTPRequestHandler` 默认
  HTTP/1.0，会在每个响应后强制关连接 —— 客户端怎么改都白搭。
- **每个响应都要有 `Content-Length`**，否则客户端无法定界。
- **任何提前 return 之前都要先把请求体读干净。** 否则 403/400 这类分支返回时，
  残留的 body 会被 keep-alive 连接当成**下一个请求的起始行**，后续请求全部错乱。
  这条极难从现象定位 —— 表现为「偶发地、越往后越乱」。
- 给 handler 设 `timeout`（如 120s）回收空闲连接，否则服务端线程被长期占住。

## 加大缓冲（是配合，不是替代）

板级 defconfig 里：

| 符号 | 作用 |
|---|---|
| `CONFIG_NET_SEND_BUFSIZE` | 单连接 TCP 发送缓冲；给到接近一帧 body 的量级 |
| `CONFIG_IOB_NBUFFERS` | IOB 池大小，决定能排队多少未确认数据 |
| `CONFIG_IOB_NCHAINS` | 链头数。**Kconfig 默认是 `= IOB_NBUFFERS`（当 `NET_READAHEAD=y`）** —— 手动改 NBUFFERS 时必须一起改，否则卡在旧值 |
| `CONFIG_IOB_THROTTLE` | 保留量，按 NBUFFERS 的 ~20% 设 |

`CONFIG_IOB_NCHAINS` 的默认值来自 `mm/iob/Kconfig`：
`default IOB_NBUFFERS if NET_READAHEAD`。改 NBUFFERS 后用
`make -C nuttx savedefconfig` 复核，能立刻看出 NCHAINS 是否漏改。

改完记得同步改 `nuttx/.config`（增量构建不会重新生成它）。

## 不要用降采样 / 降分辨率来「解决」

降分辨率确实能减小 body，但会**丢掉小目标（手机、手部等）的细节，实测显著降低
识别率**。传输压力应该用长连接 + 缓冲解决。若已经这么绕过，回头评估识别率是否被
牺牲了 —— 把 320×240 降到 160×120 就是 4 倍的信息损失。

## 验证：协议改动要能本地复现

服务端切 HTTP/1.1 后，用一条 TCP 连接连发多个请求（**其中穿插会提前 return 的
分支，如鉴权失败**），逐条按 `Content-Length` 读响应，确认全部正确 —— 这能一次
覆盖 keep-alive 与「提前 return 污染流」两个坑。
