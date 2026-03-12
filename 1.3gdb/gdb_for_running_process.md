**gdb调试正在运行中的程序：**
用处：
    程序不动了
    程序死了
    从头开始调试很麻烦

*要想调试，必须获得其键值编号*
```ps -ef |grep demo```

```
(base) zzaw@DESKTOP-H56O0VV:~/cpp_project/lesson/1.3gdb$ ps -ef |grep demo
zzaw       37514   15335  0 15:47 pts/5    00:00:00 ./demo
zzaw       38286   37607  0 15:49 pts/6    00:00:00 grep --color=auto demo
```
37514就是其编号

下一步```gdb demo -p 37514```
一般来说，调试时demo会暂停，可是我这里没有暂停







你尝试用 GDB 附加（attach）到一个已经在运行的 `./demo` 进程，但 GDB 报错：
```
Could not attach to process. ... ptrace: Operation not permitted.
```
这说明系统配置**禁止了当前用户对其他进程进行 ptrace 操作**，即使目标进程属于同一用户。因此，GDB 无法控制该进程，程序自然也就没有暂停。

---

## 为什么无法 attach？
Linux 内核通过 `ptrace` 系统调用实现调试功能。出于安全考虑，许多发行版（如 Ubuntu）默认启用了 **YAMA 安全模块**，通过 `/proc/sys/kernel/yama/ptrace_scope` 限制 ptrace 的使用：
- `0`：任何进程都可以被 ptrace（传统模式）。
- `1`（默认值）：只有进程的父进程或具有 `CAP_SYS_PTRACE` 能力的进程才能 ptrace。
- `2`：仅管理员（root）或具有 `CAP_SYS_PTRACE` 的进程可以使用 ptrace。
- `3`：不允许任何进程使用 ptrace（通常不启用）。

你的系统很可能设置为 `1` 或 `2`，导致你（非 root）无法 attach 到不是自己子进程的 `./demo`。

---

## 如何解决？

### 方案一：临时修改 ptrace_scope（推荐）
用 root 权限将 ptrace_scope 临时改为 `0`，允许所有进程互相调试：
```bash
sudo sysctl -w kernel.yama.ptrace_scope=0
```
此设置立即生效，但**重启后恢复默认**。若想永久修改，可编辑 `/etc/sysctl.d/10-ptrace.conf` 或 `/etc/sysctl.conf` 文件，找到 `kernel.yama.ptrace_scope` 行改为 `0`。

修改后再次运行 GDB attach 应该就能成功，程序会暂停在当前位置。

### 方案二：以 root 身份运行 GDB
虽然可行，但**不推荐**，因为 root 权限过大，容易误操作。
```bash
sudo gdb ./demo -p 37514
```

### 方案三：直接在 GDB 中运行程序（更简单）
既然你需要调试，最直接的方式是**让 GDB 启动程序**，而不是 attach 到一个已经在运行的进程。因为你的程序是循环打印，完全可以：
```bash
gdb ./demo
(gdb) run
```
程序会直接在 GDB 中运行，你可以随时按 `Ctrl+C` 中断，设置断点等。这样完全不受 ptrace_scope 影响。

---

## 为什么程序没有暂停？
当你 attach 时，GDB 会尝试暂停目标进程。但由于 attach 失败，GDB 根本没有获得控制权，所以程序继续运行，不会暂停。

如果直接使用 `gdb ./demo` 启动，并且没有设置断点，程序也会一直运行直到结束。若希望它启动后暂停，可以在 `main` 函数或感兴趣的位置设置断点：
```bash
(gdb) break main
(gdb) run
```
这样程序会在 `main` 入口处暂停。

---
