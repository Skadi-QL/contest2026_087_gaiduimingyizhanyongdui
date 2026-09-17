#!/usr/bin/env bash
# ============================================================================
# FOCUS AIoT - ESP32-S3-EYE 固件构建脚本
#
# 用法 (在 openvela 工作区根目录执行):
#   bash contest2026_087_gaiduimingyizhanyongdui/scripts/build_hwtest.sh
#
#   首次运行 : 拉 ESP HAL + 全量编译 (约 15-40 分钟, 取决于网络)
#   之后运行 : 增量编译 (只跑 make, 不再重新配置)
#
# 产物:
#   nuttx/nuttx.bin   烧录到 ESP32-S3-EYE 的 0x0 地址
#   nuttx/nuttx       ELF (带符号, 调试用)
#
# 本脚本替评委做掉了手动复现时最容易踩的四个坑, 每一步都注明了原因:
#   1. 交叉工具链不在 PATH   —— manifest 里它是 notdefault 组, repo sync 不拉
#   2. ESP HAL 编译不过      —— 官方 fix_esp32s3.sh 的 4 项兼容补丁
#   3. 画面卷动/颜色错乱     —— 本仓 patches/ 下的相机 DMA 对齐补丁
#   4. 仓库 defconfig 被改   —— build.sh 结尾会 savedefconfig 覆盖回来
# ============================================================================
set -uo pipefail

REPO="$(cd "$(dirname "$0")/.." && pwd)"          # 本参赛仓根目录
ROOTDIR="$(cd "$REPO/.." && pwd)"                 # openvela 工作区根目录
NUTTX="$ROOTDIR/nuttx"
CONFIG_REL="contest2026_087_gaiduimingyizhanyongdui/board/contest_board/configs/hwtest"
DEFCONFIG="$REPO/board/contest_board/configs/hwtest/defconfig"
CAM_C="$NUTTX/arch/xtensa/src/esp32s3/esp32s3_cam.c"
CAM_PATCH="$REPO/patches/0001-nuttx-esp32s3-cam-realign-dma-on-first-vsync.patch"
HAL_DIR="$NUTTX/arch/xtensa/src/esp32s3/esp-hal-3rdparty"
HAL_SHA=9fc713a95b1ff150dd0b0647e465d3c624056bb1
JOBS="${JOBS:-$(nproc)}"
PROXY="${http_proxy:-}"

say() { echo "[build] $*"; }
die() { echo "[build] ✗ $*" >&2; exit 1; }

say "工作区: $ROOTDIR"
say "并行度: $JOBS"

# ---------- 1. 交叉工具链 ----------------------------------------------------
# manifest 里 xtensa-esp32s3-elf 带 groups="notdefault,platform-linux",
# 所以 `repo sync -c -j8` 不会拉它 —— 少了它编译会刷屏
# `xtensa-esp32s3-elf-gcc: command not found`。
TOOLCHAIN="$ROOTDIR/prebuilts/gcc/linux-x86_64/xtensa-esp32s3-elf"
if [ ! -x "$TOOLCHAIN/bin/xtensa-esp32s3-elf-gcc" ]; then
  cat >&2 <<'EOF'
[build] ✗ 找不到交叉工具链。补一步:

  git clone --depth=1 \
    https://github.com/openvela-toolchain-external/prebuilts_gcc_linux-x86_64_xtensa-esp32s3-elf \
    prebuilts/gcc/linux-x86_64/xtensa-esp32s3-elf

EOF
  exit 1
fi
export PATH="$TOOLCHAIN/bin:$PATH"

# build.sh 会 source build/envsetup.sh 摆弄 PATH; 记下当前值, 构建前再确认一次
VELA_ORIGINAL_PATH="$PATH"
export VELA_ORIGINAL_PATH

# ---------- 2. ESP HAL ------------------------------------------------------
# 钉住 SHA 浅取只要 ~90MB / 20 秒; 交给 make 自己 clone 则是 444MB 全量,
# 网络慢时要 20-30 分钟。子模块仍由 make 在 context 阶段拉。
if [ ! -d "$HAL_DIR/.git" ]; then
  say "拉取 ESP HAL (钉住的 SHA ${HAL_SHA:0:7}) ..."
  rm -rf "$HAL_DIR"
  mkdir -p "$HAL_DIR"
  (
    cd "$HAL_DIR" || exit 1
    git init -q
    git remote add origin https://github.com/espressif/esp-hal-3rdparty.git
    git fetch -q --depth=1 origin "$HAL_SHA" && git checkout -q FETCH_HEAD
  ) || die "ESP HAL 拉取失败 (检查网络/代理; 可 export http_proxy=... 后重试)"
  say "ESP HAL 就绪"
else
  say "ESP HAL 已在, 跳过"
fi

# ---------- 3. ESP HAL / mbedtls 兼容补丁 -----------------------------------
# 这两项是本作品验证过的构建所必需的, 都是幂等的:
#
# (a) clk_ctrl_os.c 的自旋锁初始化 —— 不打必然编译失败。
#     nuttx 自 508ece9fb2d "define spinlock with atomic type" 起把 spinlock_t
#     变成了结构体, 而 HAL 钉住的 9fc713a 比它早 3 个月, 仍按标量写:
#       #define LOCK_INITIALIZER_UNLOCKED 0
#       static lock_type_t periph_spinlock = LOCK_INITIALIZER_UNLOCKED;
#     → clk_ctrl_os.c:27:41: error: invalid initializer
#     SP_UNLOCKED 由 nuttx/spinlock_type.h 提供, 就是结构体形式的未上锁初值。
#
# (b) apps/crypto/mbedtls/Make.defs 的 -I → -isystem —— ESP-IDF 与 nuttx 的
#     cipher_info_t 布局不同, 改用 -isystem 让 ESP-IDF 的头文件在编译 esp-hal
#     源文件时优先, 避免结构体冲突。
#
# 注: 官方 packages/ai_agent/fix_esp32s3.sh 还包含另外两项 (禁用 HAL mbedtls 的
# MBEDTLS_CCM_C、给 esp32s3_bringup.c 挂 /data tmpfs), 那是给 ai_agent 用的,
# 本作品不需要, 故这里不引入 —— 以保证评委编出的固件与本队真机验证的一致。
HAL_CLK="$HAL_DIR/components/esp_hw_support/clk_ctrl_os.c"
if [ -f "$HAL_CLK" ] && ! grep -q "SP_UNLOCKED" "$HAL_CLK"; then
  say "补丁 (a): clk_ctrl_os.c 自旋锁初始化"
  sed -i 's/#define LOCK_INITIALIZER_UNLOCKED       0/#define LOCK_INITIALIZER_UNLOCKED       SP_UNLOCKED/' "$HAL_CLK"
fi

MDEFS="$ROOTDIR/apps/crypto/mbedtls/Make.defs"
if [ -f "$MDEFS" ] && ! grep -q "isystem" "$MDEFS"; then
  say "补丁 (b): apps/crypto/mbedtls/Make.defs -I → -isystem"
  sed -i \
    -e 's|CFLAGS += ${INCDIR_PREFIX}$(APPDIR)/crypto/mbedtls/include|CFLAGS += -isystem $(APPDIR)/crypto/mbedtls/include|' \
    -e 's|CFLAGS += ${INCDIR_PREFIX}$(APPDIR)/crypto/mbedtls/mbedtls/include|CFLAGS += -isystem $(APPDIR)/crypto/mbedtls/mbedtls/include|' \
    -e 's|CXXFLAGS += ${INCDIR_PREFIX}$(APPDIR)/crypto/mbedtls/include|CXXFLAGS += -isystem $(APPDIR)/crypto/mbedtls/include|' \
    -e 's|CXXFLAGS += ${INCDIR_PREFIX}$(APPDIR)/crypto/mbedtls/mbedtls/include|CXXFLAGS += -isystem $(APPDIR)/crypto/mbedtls/mbedtls/include|' \
    "$MDEFS"
fi

# ---------- 4. 相机 DMA 帧对齐补丁 ------------------------------------------
# 缺了它: 画面水平卷动, 且卷动量每帧不同; 卷动量为奇数字节时 RGB565 的
# 2 字节配对整体错位, 表现为偏蓝偏绿的彩色纹样。详见补丁头部注释。
if grep -q "Realign the DMA write pointer" "$CAM_C" 2>/dev/null; then
  say "相机 DMA 对齐补丁已应用, 跳过"
elif [ -f "$CAM_PATCH" ]; then
  say "应用相机 DMA 对齐补丁"
  if git -C "$NUTTX" apply "$CAM_PATCH" 2>/dev/null ||
     (cd "$NUTTX" && patch -p1 --forward --silent < "$CAM_PATCH"); then
    say "相机补丁已应用"
  else
    say "警告: 相机补丁应用失败 —— 画面可能出现卷动/颜色错乱, 请手动检查"
  fi
else
  say "警告: 未找到 $CAM_PATCH"
fi

# ---------- 5. 构建 ---------------------------------------------------------
if [ -f "$NUTTX/.config" ]; then
  # 已配置过: 直接增量编译。
  # 不要再用 ./build.sh —— 它内部是 configure.sh -e, 配置一变就 make distclean,
  # 而 Make.defs 里的 `distclean:: DELDIR chip/esp-hal-3rdparty` 会把刚拉好的
  # ESP HAL 连同全部目标文件一起删掉, 下次构建又要重下。
  say "检测到已有配置, 走增量编译: make -C nuttx -j$JOBS"
  make -C "$NUTTX" -j"$JOBS"
  rc=$?
else
  # 首次: 用官方 build.sh 生成 .config 并全量编译。
  say "首次构建: ./build.sh $CONFIG_REL -j$JOBS  (需外网)"
  # build.sh 结尾会 make savedefconfig 并把结果覆盖回本仓的 defconfig,
  # 冲掉手写注释; 先备份, 构建后还原。
  cp "$DEFCONFIG" "$DEFCONFIG.buildbak" 2>/dev/null || true
  ( cd "$ROOTDIR" && ./build.sh "$CONFIG_REL" -j"$JOBS" )
  rc=$?
  [ -f "$DEFCONFIG.buildbak" ] && mv -f "$DEFCONFIG.buildbak" "$DEFCONFIG"
fi

# ---------- 6. 校验产物 -----------------------------------------------------
BIN="$NUTTX/nuttx.bin"
if [ "${rc:-1}" -ne 0 ] || [ ! -f "$BIN" ]; then
  cat >&2 <<EOF

[build] ✗ 构建失败 (exit ${rc:-1})。

常见原因:
  * ESP HAL 子模块下载被打断  -> 重跑本脚本即可, HAL 主体已在, 只会补子模块
  * 代理没配                -> export http_proxy=http://<host>:<port> 后重跑
  * 出现 'xtensa-esp32s3-elf-gcc: command not found'
                            -> 工具链没装全, 见本脚本第 1 步的提示

本脚本可重复运行, 已完成的步骤会自动跳过。
EOF
  exit 1
fi

say "✅ 构建成功"
echo "     固件: $BIN  ($(du -h "$BIN" | cut -f1), md5 $(md5sum "$BIN" | cut -c1-12))"
echo "     ELF : $NUTTX/nuttx"
echo
echo "     烧录 (需 esptool >= 4.8):"
echo "       esptool -c esp32s3 -p COM6 -b 460800 \\"
echo "         --before default-reset --after hard-reset \\"
echo "         write_flash 0x0 $BIN"
echo
echo "     设备运行:"
echo "       nsh> hello_app hwwifi <你的WiFi名> <密码>"
echo "       nsh> hello_app"
