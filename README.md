# cpp_learn
# cpplearn

这份 Markdown 格式的速查表专门为你当前的 **`2.1.1-multi-io`** 项目量身定制，你可以直接将其复制到你的笔记或 Source Insight 的说明文档中。

---

# Git 常用命令速查表 (Gitee 专用版)

## 🚀 一、 每日开发：上传代码 (Push)

当你修改了代码（例如在 Source Insight 里改了 `Multi-io.c`），按照这三步走：

1. **暂存修改**（把改动装进信封）：
```bash
git add .

```


2. **提交备注**（在信封上写下改了什么）：
```bash
git commit -m "修改了打印逻辑并修复线程陷阱"

```


3. **推送到云端**（把信寄给 Gitee）：
```bash
git push -u origin main

```



---

## 📥 二、 同步更新：拉取代码 (Pull)

如果你在 Gitee 网页端直接改了代码，或者需要同步云端最新的状态：

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

