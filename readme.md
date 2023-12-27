**UNIX网络编程卷1：套接字联网API（第3版） 的笔记。**

**已经购买了正版实体图书**


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
#### Q&A
- [Q&A](https://github.com/lsill/unpvnote/blob/main/QA/fifth.md)

### 第六章 I/O复用：select和poll函数
#### 6.1 I/O模型
- [I/O模型对比](https://github.com/lsill/nbook/blob/main/content/UNIX/IO_model_com.md)
#### 6.3 select函数
- [select描述符](https://github.com/lsill/nbook/blob/main/content/UNIX/select_functon.md)
#### 6.4 str_cli (select重构版)
- [str_cli](https://github.com/lsill/unpvnote/blob/main/select/strcliselect01.c)
#### 6.6 str_cli(shutdown重构版)
- [str_cli](https://github.com/lsill/unpvnote/blob/main/select/strcliselect02.c)
#### 6.8 select服务plus版本(增加复用)
- [增加描述符复用版](https://github.com/lsill/unpvnote/blob/main/tcpcliserv/tcpservselect01.c)
#### 6.10 poll函数
- [poll解释](https://github.com/lsill/nbook/blob/main/content/UNIX/poll_function.md)
#### 6.11 描述符复用服务poll重构
- [poll重构](https://github.com/lsill/unpvnote/blob/main/tcpcliserv/tcpservpoll01.c)

#### Q&A
- [Q&A](https://github.com/lsill/unpvnote/blob/main/QA/sixth.md)

### 第7章 套接字选项
#### 7.2 getsocketopt和setocketopt函数
- [选项表](https://github.com/lsill/nbook/blob/main/content/UNIX/getsocket_setsocket.md)
#### 7.3 检查选项是否受支持并获取默认值
- [checkopts](https://github.com/lsill/unpvnote/blob/main/sockopt/checkopts.c)
#### 7.5 通用套接字选项
- [选项详情](https://github.com/lsill/nbook/blob/main/content/UNIX/common_socket_opt.md)
#### 7.6 IPv4 套接字选项
- [选项详情](https://github.com/lsill/nbook/blob/main/content/UNIX/ipv4_socket_opt.md)
#### 7.8 IPv6 套接字选项
- [选项详情](https://github.com/lsill/nbook/blob/main/content/UNIX/ipv6_socket_opt.md)
#### 7.9 TCP 套接字选项
- [选项详情](https://github.com/lsill/nbook/blob/main/content/UNIX/tcp_socket_opt.md)
#### 7.10 SCTP 套接字选项
- [选项详情](https://github.com/lsill/nbook/blob/main/content/UNIX/sctp_socket_opt.md)



