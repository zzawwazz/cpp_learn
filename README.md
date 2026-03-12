# cpp_learn

# Git 常用命令速查表

## 🚀 一、 每日开发：上传代码 (Push)
1. **暂存修改**（把改动装进信封）：
```bash
git add .

```
2. **提交备注**（在信封上写下改了什么）：
```bash
git commit -m "修改了打印逻辑并修复线程陷阱"

```
3. **推送到云端**：
```bash
git push -u origin main

```
---

## 📥 二、 同步更新：拉取代码 (Pull)

如果你在网页端直接改了代码，或者需要同步云端最新的状态：

* **直接拉取并合并**：
```bash
git pull origin master

```
---

## 🔍 三、 状态查询与“后悔药”

| 命令 | 作用 | 推荐使用场景 |
| --- | --- | --- |
| **`git status`** | 查看哪些文件改了没交 | **每次操作前**先运行，心里有数 |
| **`git log --oneline`** | 查看简洁的提交历史 | 想看看自己这几天都干了啥 |
| **`git remote -v`** | 检查远程仓库地址 | 确认现在走的是 SSH 还是 HTTPS |
| **`git checkout -- <文件名>`** | **撤销修改** | 代码改乱了，想恢复到上次提交的样子 |

---

## ⚠️ 四、 常见报错解决

> **1. 提示“Dubious ownership”（目录所有权问题）**
> ```bash
> git config --global --add safe.directory /srv/samba/shared_folder/2.1.1-multi-io
> 
> ```
> 
> 

> **2. 提示“Already up to date”**
> 说明云端和本地代码是一致的，不需要重复拉取或推送。

> **3. 验证 SSH 免密连接是否成功**
> ```bash
> ssh -T git@gitee.com
> 
> ```
> 
> 

---

## 🛠️ 五、 进阶：排除垃圾文件 (`.gitignore`)

为了防止像 `multi-io` 这种编译出来的二进制程序（很大且没必要备份）传到云端，建议在文件夹里新建一个 `.gitignore` 文件，内容如下：

```text
# 忽略编译出的可执行文件
multi-io
server
a.out

# 忽略对象文件和库文件
*.o
*.a
*.so

# 忽略 Source Insight 的缓存或临时文件
*.si4project/
*.vsp

```

---


如果你希望将当前文件夹中的文件分别提交到 Git 仓库，每次提交只包含部分文件。Git 允许你灵活地选择哪些文件进入下一次提交，通过分次 `git add` 和 `git commit` 即可实现。以下是具体操作步骤：

---

## 1. 初始化 Git 仓库（如果尚未初始化）
在文件夹 `1.3gdb` 内执行：
```bash
git init
```
这将创建一个 `.git` 子目录，开始版本控制。

---

## 2. 分批次添加文件并提交
假设你想先提交 `demo` 文件，可以：
```bash
git add demo
git commit -m "add demo executable"
```
接着提交 `core` 文件：
```bash
git add core
git commit -m "add core dump file"
```
以此类推，每次添加一个或一组你想放在同一个提交中的文件，然后立即提交。

---

## 3. 每次提交前确认暂存区状态
用 `git status` 查看当前哪些文件已被暂存（绿色）、哪些未被暂存（红色）：
```bash
git status
```
确保你只添加了本次想要提交的文件。

---

## 4. 批量添加的注意事项
- 如果误用 `git add .` 或 `git add *`，会将所有未暂存的文件一次性加入暂存区。若你希望分开提交，**避免**使用它们。
- 如果已经用 `git add .` 添加了所有文件，但还没提交，可以用 `git reset` 撤销暂存（保留文件修改）：
  ```bash
  git reset
  ```
  然后重新按需添加。

---

## 5. 提交信息规范
建议每次提交的信息简明扼要，说明该次提交包含的文件或改动。例如：
- `git commit -m "add how_to_use_gdb.cpp"`  
- `git commit -m "update gdb_order.md"`

---

## 6. 查看提交历史
提交完成后，可以用 `git log` 查看每次提交的记录，确认文件是否按预期分开。

---

这样，你就实现了“不同文件不同 commit”的目标。如果后续还要修改某个文件，只需再次 `git add` 该文件并提交即可。Git 会记录每次的改动，保持历史清晰。