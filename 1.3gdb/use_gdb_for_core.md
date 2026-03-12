gdb 调试 core 文件
如果程序在运行的过程中发生了内存泄漏，会被内核强行终止，提示“段错误(吐核)”，内存的状态将保存在core文件中，方便程序员进一步分析。
Linux不会生成core文件，需要修改系统参数。调试core文件的步骤如下:
1) 用ulimit-a查看当前用户的资源限制参数;
    其中
        stack size                  (kbytes, -s) 8192为栈内存大小
        open files                          (-n) 1000000为打开文件的最大数量
        core file size              (blocks, -c) 0为核文件的大小
2) 用ulimit -c unlimited把 core file size 改为 unlimited（无限制）;
3) 运行程序，产生core文件;

若运行 `./demo` 时出现了 `Segmentation fault (core dumped)`，但当前目录下并没有生成 core 文件。虽然 `ulimit -c` 显示 unlimited，但 core dump 的生成还受其他因素影响。
---
## 1. core 文件被重定向到了其他位置
Linux 通过 `/proc/sys/kernel/core_pattern` 控制 core 文件的保存路径和命名规则。  
执行以下命令查看当前配置：
```bash
cat /proc/sys/kernel/core_pattern
```
常见情况：
- 若输出为 `core`，则 core 文件会生成在程序的工作目录，文件名为 `core`。
- 若输出为 `/var/coredumps/core.%e.%p` 等带路径的字符串，则 core 文件保存在指定目录（如 `/var/coredumps`）。
- 若输出为 `|/usr/lib/systemd/systemd-coredump` 等以管道符开头的，则 core 被交给了 systemd-coredump 处理，可用 `coredumpctl` 查看。

**解决方法**：  
- 如果是管道到 systemd-coredump，使用 `coredumpctl list` 和 `coredumpctl debug` 来查看。
- 如果希望 core 文件生成在当前目录，可以临时修改 core_pattern（需要 root 权限）：
  ```bash
  sudo sh -c 'echo "core" > /proc/sys/kernel/core_pattern'
  ```
  但注意这只是临时生效，重启后会恢复。


出现core文件后使用```gdb demo core```进行调试
```bt```查看函数调用栈
