Q:写一个输出默认TCP和UDP发送和接收級冲区大小的程序.

A: [Link](https://github.com/lsill/unpvnote/blob/main/demo/buffer_size.cpp)

Q:在调用connect之前，调用getsockopt得到套接字接收缓冲区的大小和MSS,并输出这两个值。connect返回成功后，再次
获取这两个套接字选项并输出它们的值。值变化了吗?为什么?运行本客户程序两个实例，一个连接到本地网络上的一个服务器，
另一个连接到非本地网络上的一个远程服务器。MSS交化吗?为什么?

A:首先声明这个程序没有“唯一正确”的输出，其结果随系统而变化。有些系统(尤如Solaris2.5.1及史早版本)总是返回0值的
套接字缓冲区大小，使得我们无法查看该值在连接前后有什么事发生。

至于MSS，在connect之前显示的值是实现的默认值(通常是536或512)，在connect之后显示的值则取决于可能有的来自对端的
MSS选项。举例来说，本地以太网上connect之后的值可能是1460。然而connect某个远程网络上的一个服务器主机之后显示的
MSS值可能类似默认值，除非你的系统支持路径MTU发现功能。如果可能的话，在程序运行期间运行一个像tcpdump这样的工具，
以查看来自对端的SYN分节中的真正MSS选项。

至于套接字接收缓冲区的大小，许多实现在连接建立之后把它向上舍入成MSS的倍数。查看连接建立之后套接字接收缓冲区大小的另一
个方法是使用像tcpdump这样的工具监视分组，观察TCP的通告窗口(advertised window)。
[代码例子](https://github.com/lsill/unpvnote/blob/main/sockopt/rcvbuf.c)

Q:在调用exit之前设置SO_LINGER套接字选项，把作为其输入的linger结构中的l_onoff成员设置为1，l_linger成员设置为0。
先启动服务器，然后启动客户。在客户上键入一行或两行文本以检验操作正常，然后键入EOF以终止客户，将发生什么情况?
终止客户后，在客户主机上运行netstat，查看套接字是否经历了TIME_WAIT状态。

A:如果l_onoff为非0值且l_linger为0，那么当close某个连接时TCP将中止该连接。这就是说TCP将丢弃保留在套
接字发送缓冲区中的任何数据，并发送一个RST给对端，而没有通常的四分组连接终止序列。这么一来避免了TCP的TIME_WAIT
状态，然而存在以下可能性:在2MSL秒内创建该连接的另一个化身，导致来自刚被终止的连接上的旧的重复分节被不正确地递送
到新的化身上。

客户端主动打开链接，会丢发送缓冲区所有数据，发送一个RST而不是四分组（4分节）交换来终止链接，
哪怕是客户端关闭的，服务器套接字也不会有TIME_WAIT状态。

Q:假设有两个TCP客户在同一时间启动，都设買SO_REUSEADDR套接字选项，且以相同的本地IP地址和相同的端口号(臂如说，1500)
调用bind，但一个客户连接到198.69.10.2的端口7000，另一个客户连接到198.69.10.2(相同的IP地址)的端口8000。
闸述所出现的竞争状态。

A:第一个客户调用setsockopt、bind和connect。如果第二个客户在第一个客户调用bind和connect之间调用bind，那么它将返回
EADDRINUSE错误。然而一旦第一个客户己连接到对端，第二个客户的bind就正常工作，因为第一个客户的套接字当时处于己连接状态。
处理这种竞爭状态的唯一办法是让第二个客户在bind调用返回EADDRINUSE错误的情况下再尝试调用bind多次，而不是一返回该错误就放弃

Q:ping程序的许多版本有一个-d标志用于开启SO_DEBUG套接字选项，这是干什么用的?

A:它不起任何作用，因为ping使用ICMP套接字，而SO_DEBUG套接字选项只影响TCP套接字。SO_DEBUG套接字选项的描述一直有些笼通，
譬如说“这个选项开启相应协议层中的调试”，但是实现该选项的唯一协议层一直只是TCP。

Q:假设客户执行了两个write调用:第一个写4字节，第二个写396字节。另假设服务器的ACK延滞时间为100ms，客户与服务器之间的RTT为
100ms，服务器处理客户请求的时间为50ms。面一个时间线图展示延滞的ACK与Nagle算法的相互作用（E-6）。

假设设置了TCP_NODELAY套接字选项？(E-7)

假设进程调用writev一次性处理完4字节级冲区和396字节缓冲区？(E-8)

A:
[E-6](https://raw.githubusercontent.com/lsill/gitLink/main/document/photo/note/unix/E_6.jpg)
[E-7](https://raw.githubusercontent.com/lsill/gitLink/main/document/photo/note/unix/E_7.jpg)
[E-8](https://raw.githubusercontent.com/lsill/gitLink/main/document/photo/note/unix/E_8.jpg)

Q:RFC 1122 [Barden198] 确定的延滞ACK的建议间隔。

A:“延滞必须低于0.5秒钟，而且在完全大小分节流上至少每隔一个分节就应该有一个ACK”。源自Berkeley的实现延滞ACK最久200ms

Q:假设客户和服务器都设置了SO_KEEPALIVE套接字选项。连接两端维护连通性，但是连接上没有应用数据在交换。当保持存活定时器每2小时
到期时，在连接上有多少TCP分节被交换

A:只交换2个而不是4个TCP分节。两个系统的定时器精确同步的可能性非常低;因此一端的保持存活定时器会比另一端略早一点超时
。首先超时的那一端发送保持存活侦探分组，导致另一端确认这个分组。然而保持存活侦探分组的接收导致时钟略慢的主机把保持存
活定时器重置到2小时。

Q:几乎所有实现都在头文件<sys/socket.h>中定义了SO_ACCEPTCON常值，该选项为什么存在?

A:最初的套接字API并没有listen函数。相反，socket函数的第四个参数含有套接字选项，而SO_ACCEPTCON就是用来指定监听
套接字的。加了listen函数后，这个选项还是保留着，不过现在只是由内核来设置。



