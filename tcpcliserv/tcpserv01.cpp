extern "C" {
    #include "../lib/unp.h"
}
// 一个基本的多进程服务器
int
main(int argc, char **argv)
{
	int					listenfd, connfd;  //
	pid_t				childpid;
	socklen_t			clilen;
	struct sockaddr_in	cliaddr, servaddr;

	listenfd = Socket(AF_INET, SOCK_STREAM, 0); // listenfd:用于监听连接请求的套接字文件描述符，创建一个 TCP 套接字（SOCK_STREAM）用于监听，AF_INET 表明使用 IPv4 地址。

    // 这些是初始化地址servaddr
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);   // INADDR_ANY 通配符地址，值为 0.0.0.0
    // 用于指示服务器应该绑定到所有可用的网络接口上。这对于多宿主机（即有多个网络接口的主机）非常有用，因为它允许服务器接受发送到任何一个网络接口的连接。
	servaddr.sin_port        = htons(SERV_PORT);    // SERV_PORT 指定的一个端口

    // 将 listenfd 套接字绑定到 servaddr 指定的地址和端口。
	Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

    // 开始监听 LISTENQ是一个长度
	Listen(listenfd, LISTENQ);

	for ( ; ; ) {
		clilen = sizeof(cliaddr);
        // 等待接受连接请求，接收到的连接描述符存储在connfd中，客户端的地址信息存在cliaddr
		connfd = Accept(listenfd, (SA *) &cliaddr, &clilen);

		if ( (childpid = Fork()) == 0) {	/* child process */
			Close(listenfd);	/* close listening socket */
			str_echo(connfd);	/* process the request */
			exit(0);
		}
		Close(connfd);			/* parent closes connected socket */
	}
}
