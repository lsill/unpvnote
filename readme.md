## UNIX网络编程函数注释

### 3. 套接字编程简介
#### 3.8 ntop和函数封装
- [ntop](https://github.com/lsill/unpvnote/blob/main/lib/sock_ntop.c)

#### 3.9 readn、readline和writen
- [readn](https://github.com/lsill/unpvnote/blob/main/lib/readn.c)
- [writen](https://github.com/lsill/unpvnote/blob/main/lib/writen.c)
- [readline](https://github.com/lsill/unpvnote/blob/main/lib/readline.c)

### 4. 基本TCP套接字编程
####  4.5 listen函数
- [Listen](https://github.com/lsill/unpvnote/blob/main/lib/wrapsock.c)
#### 4.8 典型并发服务程序轮廓
- [并发服务](https://github.com/lsill/unpvnote/blob/main/demo/demo1.c)
#### 4.10 获取套接字的地址族
- [sockfd_to_family](https://github.com/lsill/unpvnote/blob/main/lib/sockfd_to_family.c)
#### 习题
[Q&A](https://github.com/lsill/unpvnote/blob/main/QA/fourth.md)

### 5. TCP 客户/服务程序示例
####  5.2 TCP回射服务器程序：main函数
- [tcpserv01](https://github.com/lsill/unpvnote/blob/main/tcpcliserv/tcpserv01.c)
#### 5.3 TCP 回射服务器程序:str_echo 函数
- [strecho](https://github.com/lsill/unpvnote/blob/main/lib/str_echo.c)
#### 5.4 TCP 回射客户程序:main 函数
- [tcpcli01](https://github.com/lsill/unpvnote/blob/main/tcpcliserv/tcpcli01.c)
#### 5.5 TCP回射客户程序:str_cli函数
- [str_cli](https://github.com/lsill/unpvnote/blob/main/lib/str_cli.c)
#### 5.8 POSIX 信号处理
- [signal](https://github.com/lsill/unpvnote/blob/main/lib/signal.c)
#### 5.9 处理 SIGCHLD信号
- [sig_chld](https://github.com/lsill/unpvnote/blob/main/tcpcliserv/sigchldwait.c)
#### 5.10 wait和waitid 函数
- [sig_chld(pid)](https://github.com/lsill/unpvnote/blob/main/tcpcliserv/sigchldwaitpid.c)
- [修改后的ser示例](https://github.com/lsill/unpvnote/blob/main/tcpcliserv/tcpserv04.c)
