---
name: openvela-build-recovery
description: 诊断和恢复 openvela / NuttX（ESP32-S3 等）的构建失败。当出现以下任一情况时使用：编译产物凭空消失（distclean 后 nuttx.bin 与 .o 全没了）、esp-hal-3rdparty 目录丢失或 clone 失败、链接期报一串 undefined reference、Kconfig 开关被默认值悄悄改掉（改了 defconfig 却不生效）、xtensa-esp32s3-elf-gcc command not found、改动 STACKSIZE/CFLAGS 后不重新编译、或需要判断某次构建是否真的产出了含新改动的固件。
---

# openvela / NuttX 构建失败恢复

## 铁律：不要用 `./build.sh` 做增量编译

`build.sh` 内部是 `configure.sh -e`，**配置一变就 `make distclean`**。而
`arch/xtensa/src/esp32s3/Make.defs` 末尾有：

```make
distclean::
	$(call DELDIR,chip/$(ESP_HAL_3RDPARTY_REPO))
```

它会连 `chip/esp-hal-3rdparty` **源码**一起删掉，外加全部 `.o`。下次构建要从
GitHub 重拉（全量 clone 约 444 MB）。

- **首次构建**（`nuttx/.config` 不存在）：可以用 `./build.sh <config-path> -jN`，
  此时没有已配置的 `.config`，不触发 distclean。
- **之后一律**：

  ```bash
  export PATH=$PWD/prebuilts/gcc/linux-x86_64/xtensa-esp32s3-elf/bin:$PATH
  make -C nuttx -j$(nproc)
  ```

- 副作用：`build.sh` 结尾会 `make savedefconfig` 并把结果**覆盖回板级 defconfig**，
  冲掉手写注释和显式 `=y` 行。要保留就先备份、构建后还原。

判断走哪条路：`[ -f nuttx/.config ]`。

## esp-hal-3rdparty 丢失 / 拉取太慢

**不要**等 make 自己 clone（444 MB 全量）。按钉住的 SHA 浅取，约 92 MB / 20 秒：

```bash
cd nuttx/arch/xtensa/src/esp32s3 && rm -rf esp-hal-3rdparty \
  && mkdir esp-hal-3rdparty && cd $_
git init -q && git remote add origin https://github.com/espressif/esp-hal-3rdparty.git
git fetch -q --depth=1 origin 9fc713a95b1ff150dd0b0647e465d3c624056bb1
git checkout -q FETCH_HEAD
```

之后 `make -C nuttx -j` 会自动补子模块并应用 mbedtls 补丁。

SHA 从 `nuttx/arch/xtensa/src/esp32s3/Make.defs` 的 `ESP_HAL_3RDPARTY_VERSION`
读取（`ifndef` 守卫，可能被外部变量覆盖）。

⚠️ 别让 `make -j` 触发 clone 规则并发执行——多个 job 会互踩、带宽翻倍。先单进程
手工拉好，再跑 make。

## Kconfig 默认值会悄悄吃掉你的配置

`.config` 里缺某个符号时，`make` 会跑 `olddefconfig` 按 Kconfig 的 `default` 补齐。
默认值是 `y` 的开关就被**悄悄打开**了。

典型：`config X_STUB bool ... default y`，而板级 defconfig 里一行没写 →
生成的 `.config` 缺符号 → 补成 `y` → 编出桩版本，链接期报桩里没有的符号
（如只在真实驱动里实现的 `wifi_set_http_auth`）。

**修法**：在 defconfig 里**显式**写 `# CONFIG_X is not set`。`savedefconfig` 只
省略「值等于默认值」的符号，显式写的反值会被保留。

**校验板级 defconfig 是否完整**：`make -C nuttx savedefconfig` 会生成
`nuttx/defconfig`，它就是最小配置集；正确的板级 defconfig 必须**逐行包含**它：

```bash
while IFS= read -r line; do
  case "$line" in ''|'#'*) continue;; esac
  grep -qxF "$line" <板级 defconfig> || echo "缺失: $line"
done < nuttx/defconfig
```

## 链接期一串 undefined reference：`.built` 归档语义

`apps/Application.mk` 里「把 `.o` 塞进 `libapps.a`」这个动作挂在 `.built` 标记的
规则上：

```make
$(PREFIX).built: $(AROBJS)
	$(foreach BATCH, ..., $(shell $(call ARLOCK, $(BIN), $(ALL_OBJS_$(BATCH)))))
```

`.built` 比 `.o` 新 → make 认为无事可做 → **根本不执行归档**。

所以**删了 `libapps.a` 就必须连所有 `.built` 一起删**，否则新归档缺成员。典型症状：
`undefined reference` 指向 `cJSON_*`、某个 app 的 `*_main`、或
`builtin_list.c` 里 `g_builtins` 表登记的符号。

`find` 默认**不跟随符号链接**，而 `apps/packages`、`apps/external`、`apps/tests`
等都是软链，必须用 `-L` 或显式列出真实目录：

```bash
find -L apps packages external frameworks tests vendor <选手仓> \
     -name ".built" -not -path "*/.git/*" -delete
rm -f apps/libapps.a nuttx/staging/libapps.a
```

## 改了 STACKSIZE / CFLAGS 却不重新编译

`apps/builtin/builtin_list.h` 和 `registry/` 是**缓存**的。改 app 的 Makefile 后
必须删掉它们强制重建：

```bash
rm -f apps/.context apps/builtin/builtin_list.h apps/builtin/registry/.updated
rm -f apps/builtin/registry/<app>.bdat apps/builtin/registry/<app>.pdat
find <app 目录> -name "*.o" -delete
```

验证：`grep <app> apps/builtin/builtin_list.h` 看登记的 STACKSIZE 是否是新的。

## 工具链不在 PATH

manifest 里 xtensa 工具链常带 `groups="notdefault,platform-linux"`，
`repo sync -c -j8` **不会拉它**。手动补：

```bash
git clone --depth=1 \
  https://github.com/openvela-toolchain-external/prebuilts_gcc_linux-x86_64_xtensa-esp32s3-elf \
  prebuilts/gcc/linux-x86_64/xtensa-esp32s3-elf
```

`build.sh` 会 `source build/envsetup.sh` 摆弄 PATH。若要先 export PATH 再调
build.sh，同时 `export VELA_ORIGINAL_PATH="$PATH"` —— envsetup 用它来恢复 PATH。

## 不要用 md5 判断「是否是新固件」

NuttX 把版本/日期编进 `lib_utsname.c`，**每次构建 md5 都会变**，即使源码没动。
验证某个改动是否进了固件，用：

- `xtensa-esp32s3-elf-nm nuttx | grep <符号>` —— 符号在不在
- 反汇编比对函数指令数：
  `objdump -d nuttx | awk '/<func>:/,/^$/' | wc -l`
- `strings -a nuttx | grep <字面量>`（注意优化可能把字符串消掉）
