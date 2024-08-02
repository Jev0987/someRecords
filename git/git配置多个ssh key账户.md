# 如何在git中配置多个ssh 账户

1. 生成git ssh key
2. 配置config文件
3. 配置ssh key到对应的git远程终端中

## 1. 生成不同的git ssh key
``` shell
ssh-keygen -t rsa -C "youemail@xxx.com” -f ~/.ssh/gitlab-rsa
```

``` shell 
ssh-keygen -t rsa -C "youemail@xxx.com” -f ~/.ssh/github-rsa
```

在.ssh目录下检查一下是否生成了对应的ssh key文件

```shell
ls ~/.ssh
```

```shell
github-rsa.pub  gitlab-rsa.pub github-rsa  gitlab-rsa
```

## 2. 配置config文件
### 2.1 创建config文件（无后缀名）
linux：touch ~/.ssh/config

windows : C:\Users\用户名\.ssh\

>建议直接在git bash中操作，直接使用linux命令


### 2.2 填写配置内容

linux : `vim ~/.ssh/config`

windows : 可以直接在对应路径C:\Users\用户名\.ssh\进行编辑

**linux下配置**
``` txt
# gitlab
Host gitlab.com
        HostName gitlab.com
        PreferredAuthentications publickey
        IdentityFile ~/.ssh/gitlab-rsa

# github
Host github.com
        HostName github.com
        PreferredAuthentications publickey
        IdentityFile ~/.ssh/github-rsa


# 配置文件参数
# Host : Host可以看作需要识别的模式，需要配置对应的主机名和ssh文件
# HostName : 要登录主机的主机名
# User : 登录名
# IdentityFile : 指明上面User对应的identityFile路径
```

**windows下的配置**
``` txt
# gitlab
Host gitlab.com
        HostName gitlab.com
        PreferredAuthentications publickey
        IdentityFile C:\\Users\\xxx\\.ssh\\gitlab-rsa

# github
Host github.com
        HostName github.com
        PreferredAuthentications publickey
        IdentityFile C:\\Users\\xxx\\.ssh\\github-rsa


# 配置文件参数
# Host : Host可以看作需要识别的模式，需要配置对应的主机名和ssh文件
# HostName : 要登录主机的主机名
# User : 登录名
# IdentityFile : 指明上面User对应的identityFile路径
```

## 3. 配置ssh key到对应的git远程终端中
### 3.1 复制ssh key

```shell
cat ~/.ssh/github-rsa.pub
```

```shell
cat ~/.ssh/gitlab-rsa.pub
```

![ssh key截图](../pic/image.png)

### 3.2 在远程仓库中配置

setting找到ssh key
复制进去就可以了

例如：GitHub

* 点击头像

* 选择**setting**

* 点击**SSH and GPG keys**

* 粘贴对应的ssh key

### 3.3 测试
```shell
ssh -T git@github.com
```
![alt text](../pic/image2.png)


ok 完成