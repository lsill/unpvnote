Q:我们有两个应用程序，一个使用TCP，另一个使用UDP。TCP套接字的接收缓冲区中有4096字节的数据，UDP套接字的
接收缓冲区中有两个2048字节的数据报。TCP应用程序调用read，指定其第三个参数为4096，UDP应用程序调用
recvfxom，指定其第三个参数也为4096。这两个应用程序有什么差别吗?

A:read返回4096字节的数据，recvfrom则返回2048字节(2个数据报中的第一个)。不管应用请求多大，recvfrom
决不会返回多于1个数据报的数据。

TCP `read`:从缓冲区读取连续的字节流，可以读取多个 TCP 发送过来的数据片段，直到达到请求的字节数或者缓冲区数据读完为止。
UDP `recvfrom`:每次读取一个完整的数据报，即使请求的字节数大于单个数据报的大小，也不会读取多个数据报。

Q:每个己连接TCP套接字都有自己的套接字接收缓冲区。监听套接字情况怎样?你认为它有自己的套接字接收缓冲区吗?

A:监听TCP套接字也许有一个套接字接收缓冲区大小，但是它绝不会接受数据。大多数实现并不预先给套接字发送缓冲区
或接收缓冲区分配内存空间。使用SO_SNDBUP和SO_RCVBUF套接字选项指定的套接字缓冲区大小仅仅是给套接字设定的
上限。

Q:在udp客户程序中每次写一个数据报到套接字处放一个printf调用，这会改变接收到分组的百分比吗?为什么?在udp服务器程序
中每次从套接字读一个数据报处放一个printf调用，这会改变接收到分组的百分比吗?为什么?

A:在客户程序中放一个printf调用会在每个数据报之间引入一个延迟，从而允许服务器接收更多的数据报。在服务器程序中
放一个printf调用则会导致服务器丢失更多数据报。

Q:对于UDP/IPV4套接字，可传递给sendto的最大长度是多少;也就是说，可装填在一个UDP/IPv4数据报中的最大数据量是多少?
UDP/IPV6又有什么不同?

A:IPv4数据报最大为65535字节，这由16位的总长度字段限定。IPv4首部需要20字节，UDP首部需要8字节，留给UDP用户数据最
大65507字节。对于没有任何扩展首部的IPv6数据报而言(自然没有特大报支持，因为特大净荷长度是一个步跳选项，出
现在步跳选项扩展首部中)，扣除IPv6首部的净荷最大为65535字节，再扣除8字节UDP首部，留给UDP用户数据最大65527字节。

客户如果没有预先设置发送缓冲区大小，源自Berkeley的内核就给sendto调用返回EMSGSIZE错误，因为套接字发送缓冲区的默认大小
通常不足以暂存最大的UDP数据报。如果先设置客户套接字缓冲区大小再发送和接收UDP数据报，那么服务器不返送任何数据报。问题出在
服务器的UDP套接字接收缓冲区小于我们发送的数据报，因此该数据报被丢弃掉而不是被递送到套接字。最终的办法就是修改服务器程序，
预先设置它的套接字发送缓冲区与接收缓冲区的大小。

Q:







