# 双fork创建守护进程

linux下创建守护进程（双重fork创建守护进程）

1. 父进程创建子进程；
2. 父进程退出；
3. 子进程1创建新会话，子进程1成为新会话领头进程；
4. 子进程1 创建 子进程2
5. 子进程1退出，即会话领头进程退出。此操作防止其他进程占用终端设备文件后被替代；
6. 子进程2作为守护进程在后台运行；

Code：
```cpp
void startDaemon() {
    signal(SIGPIPE, SIG_IGN);

    std::cout << "start daemon, pid: " << getpid() << std::endl;
    // 创建子进程1
    pid_t pid = fork();
    if (pid > 0) {
        std::cout << "father proc exit, pid: " << getpid() << std::endl;
        exit(0);  // 父进程退出
    } else if (pid < 0) {
        std::cout << "first children create fail, pid: " << pid << std::endl;
        exit(-1);
    }

    std::cout << "daemon first children, pid: " << getpid() << std::endl;

    // 第一个子进程创建会话，它将成为会话领头进程
    if (setsid() == -1) {
        std::cout << "daemon setsid failed" << std::endl;
        exit(-1);
    }

    std::cout << "daemon try umask" << std::endl;

    // 子进程1创建子进程2
    pid = fork();

    if (pid > 0) {
        std::cout << "father proc exit, pid: " << getpid() << std::endl;
        exit(0);  // 子进程1退出
    } else if (pid < 0) {
        std::cout << "second children create fail, pid: " << pid << std::endl;
        exit(-1);
    }
    std::cout << "daemon second children, pid: " << getpid() << std::endl;
    std::cout << "finish daemon" << std::endl;

    // 子进程2成为守护进程
    umask(0);  // 文件掩码，决定了进程创建文件时的默认权限
    chdir("/");  // 进程的工作路径（这里注意权限的问题）

    // 将默认打开的文件描述符关闭：0:标准输入；1: 标准输出；2: 标准错误
    for (int i = 0; i < 3; i++) {  
        close(i);
    }
    
    // 打开/dev/null设备，向它写数据会被丢弃
    int stdfd = open("/dev/null", O_RDWR);  

     // 把标准输出和标准错误重定向到/dev/null，意味着这些信息丢弃
    dup2(stdfd, STDOUT_FILENO); 
    dup2(stdfd, STDERR_FILENO);
}
```

## 为什么要这样做？
在linux和unix系统中，【会话】是一个或多个进程的集合，每个会话都有一个会话领头进程。

**会话领头进程**是创建该会话的**第一个进程**，也是该会话中其他进程的父进程。

**控制终端**是与会话关联的一个特殊设备，通常是用户通过键盘和显示器与系统交互的设备。

一个**会话**可以有一个**控制终端**，也可以没有。

如果一个会话有一个控制终端，那么这个控制终端就是会话领头进程的控制终端。

当会话领头进程【打开一个未被其他进程占用的终端设备文件】时，这个**终端设备**就会成为这个会话的终端。这就意味着会话领头进程和它的所有子进程都可以通过这个**终端设备**与用户交互。

这就是为什么在创建守护进程时，我们希望避免守护进程成为会话领头进程，因为我们【**不希望守护进程有控制终端**】。

**守护进程应该独立于任何终端，不受用户的直接控制**


