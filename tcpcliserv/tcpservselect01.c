/* include fig01 */
#include	"../lib/unp.h"

int
main(int argc, char **argv)
{
	int					i, maxi, maxfd, listenfd, connfd, sockfd;   // listenfd, connfd, sockfd：套接字描述符 maxi, maxfd：跟踪client arr最大索引和最大描述符
	int					nready, client[FD_SETSIZE];     // nready:准备好的描述符的数量
	ssize_t				n;
	fd_set				rset, allset;   // 文件描述符的集合
	char				buf[MAXLINE];
	socklen_t			clilen;
	struct sockaddr_in	cliaddr, servaddr;

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(SERV_PORT);

	Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

	Listen(listenfd, LISTENQ);  // 初始化监听服务器

	maxfd = listenfd;			/* initialize */
	maxi = -1;					/* index into client[] array */
	for (i = 0; i < FD_SETSIZE; i++)
		client[i] = -1;			/* -1 indicates available entry */
	FD_ZERO(&allset);
	FD_SET(listenfd, &allset);
/* end fig01 */

/* include fig02 */
	for ( ; ; ) {
		rset = allset;		/* structure assignment */
		nready = Select(maxfd+1, &rset, NULL, NULL, NULL);

		if (FD_ISSET(listenfd, &rset)) {	/* new client connection */
			clilen = sizeof(cliaddr);
			connfd = Accept(listenfd, (SA *) &cliaddr, &clilen);
#ifdef	NOTDEF  // 预处理指令，存在NOTDEF  走斤这里
			printf("new client: %s, port %d\n",
					Inet_ntop(AF_INET, &cliaddr.sin_addr, 4, NULL),
					ntohs(cliaddr.sin_port));
#endif

			for (i = 0; i < FD_SETSIZE; i++)
				if (client[i] < 0) {
					client[i] = connfd;	/* save descriptor */
					break;
				}
			if (i == FD_SETSIZE)
				err_quit("too many clients");

			FD_SET(connfd, &allset);	/* add new descriptor to set */
			if (connfd > maxfd)
				maxfd = connfd;			/* for select */
			if (i > maxi)
				maxi = i;				/* max index in client[] array */

			if (--nready <= 0)
				continue;				/* no more readable descriptors */
		}

		for (i = 0; i <= maxi; i++) {	/* check all clients for data */    // maxi最大的客户端索引，超过了就无需再去检查
			if ( (sockfd = client[i]) < 0)
				continue;
			if (FD_ISSET(sockfd, &rset)) {
				if ( (n = Read(sockfd, buf, MAXLINE)) == 0) {
						/*4connection closed by client */
					Close(sockfd);
					FD_CLR(sockfd, &allset);
					client[i] = -1;
				} else
					Writen(sockfd, buf, n);

				if (--nready <= 0)
					break;				/* no more readable descriptors */
			}
		}
	}
}
/* end fig02 */

// 存在的问题
// 拒绝服务型攻击
// 不幸的是，上面给出的服务器程序存在一个问题。考虑一下如果有一个悉意的客户连接到该服务器，发送一个字节的数据(不是换行符)后进入睡眠，
// 将会发生什么。服务器将调用read，它从客户读入这个单字节的数据，然后阻塞于下一个read调用，以等待来自该客户的其余数据。•服务器于是
// 因为这么一个容户而被阻塞(称它被“挂起”也许更确切些)，不能再为其他任何客户提供服务(不论是接受新的客户连接还是读取现有客户的数据)，
// 直到那个恶意客户发出一个换行符或者终止为止。
// 这里的一个基本概念是:当一个服务器在处理多个客户时，它绝对不能阻塞于只与单个客户相关的某个函数调用。否则可能导致服务器被挂起，拒绝
// 为所有其他客户提供服务。这就是所谓的拒绝服务(denial of service)型攻击。它就是针对服务器做些动作，导致服务器不再能为其他合法
// 客户提供服务。可能的解决办法包括:
// (a)使用非阻塞式I/O;
// (b)让每个客户由单独的控制线程提供服务(例如创建一个子进程或一个线程来服务每个客户):
// (c)对I/O操作设置一个超时