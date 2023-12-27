#include	"unp.h"

// 该函数永不终止，因为UDP是一个无连接的协议，它没有像TCP中EOF之类的东西。

void
dg_echo(int sockfd, SA *pcliaddr, socklen_t clilen)
{
	int			n;
	socklen_t	len;
	char		mesg[MAXLINE];

	for ( ; ; ) {
		len = clilen;
		n = Recvfrom(sockfd, mesg, MAXLINE, 0, pcliaddr, &len);

		Sendto(sockfd, mesg, n, 0, pcliaddr, len);
	}
}

// 该函数提供的是一个迭代服务器(iterative server)，而不是像TCP服务器那样可以提供一个并发服务器。其中没有对
// fork的调用，因此单个服务器进程就得处理所有客户。一般来说，大至数TCP服务器是并发的，而大多数UDP服务器是迭代的。
//
// 对于本套接字，UDP层中隐含有排队发生。事实上每个UDP套接字都有一个接收缓冲区，到达该套接字的每个数据报都进入
// 这个套接字接收缓冲区。当进程调用recvfrom时，缓冲区中的下一个数据报以FIFO(先入先出)顺序返回给进程。这样，
// 在进程能够读该套接字中任何已排好队的数据报之前，如果有多个数据报到达该套接字，那么相继到达的数据报仅仅加到
// 该套接字的接收缓冲区中。然而这个缓冲区的大小是有限的

