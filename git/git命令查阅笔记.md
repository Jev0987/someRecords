# git基础知识

* 工作空间
* 暂存区
* 本地库
* 远程库

工作空间：当前工作目录

暂存区：Git仓库内部的的中间区域，也就是版本库.git目录下的index文件

本地库：commit后提交到本地库

远程库：例如GitHub，GitLab，远程同步

基础逻辑：

1. 使用`git init`，将【工作空间】加入到git

2. 使用`git add xxx`保存【暂存区】

3. 使用`git commit -m "说明"`提交到【本地库】

4. 使用`git push`推到【远程库】

> Git 的数据结构是多分枝的链表
>
> 使不同版本的工作目录链接起来
> 
> 有HEAD指针指向当前操作的工作版本


# 常用命令

在当前目录创建新的Git仓库
```
git init
```

添加文件到暂存库中（谨慎使用add */.）
```shell
git add .
```

提交到本地库
```shell
git commit -m "message"
```

推送到远程库（配置好了远程仓库的情况下）
```shell
git push
```

# 分支操作
创建分支
```shell
git branch <name>
```

切换分支
```shell
git checkout <name> 
git switch <name>
```

创建同时切换分支
```shell
git checkout -b <name>
git switch -c <name>
```

合并某分支到当前分支
```shell
git merge <name>
```

删除分支
```shell
git branch -d <name>
```

移动分支（把name分支移动到HEAD）
```shell
git branch f <name>
```

分支太杂乱，太长，太多commit
```shell
git rebase -i HEAD~x
```
```shell
git rebase -i [分支hash]
```
在 vim中修改 需要合并掉的分支

改掉对应的分支，将pick 改成 f

最后保存提交

**合并分支**
pull下来
```shell
git checkout targetBranch
git pull
git merge targetBranch
```

检查冲突




# stash 临时保存(压栈)
执行临时存储，添加备注
```shell
git stash save "message"
```

查看存储
```shell
git stash list
```

查看做了哪些改动
```shell
git stash show
git stash show stash@{num}
```

查看存储的改动
```shell
git stash show -p
git stash show stash@{num} -p
```

应用存储
```shell
git stash apply
```

恢复之前缓存的工作目录
```shell
git stash pop
```

丢弃stash@{$num}存储
```shell
git stash drop stash@{$num}
```

删除所有的缓存stash
```shell
git stash clear
```


