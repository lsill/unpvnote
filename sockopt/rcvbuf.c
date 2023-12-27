#include	"../lib/unp.h"
#include	<netinet/tcp.h>		/* for TCP_MAXSEG */

// MSS (Maximum Segment Size) 最大报文段长度
// MTU (Maximum Transmission UNit) MTU是 最大传输单元
int
main(int argc, char **argv)
{
	int					sockfd, rcvbuf, mss;
	socklen_t			len;
	struct sockaddr_in	servaddr;

	if (argc != 2)
		err_quit("usage: rcvbuf <IPaddress>");

	sockfd = Socket(AF_INET, SOCK_STREAM, 0);

	len = sizeof(rcvbuf);
	Getsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &rcvbuf, &len);   // 获取套接字sockfd的接收缓冲区大小
	len = sizeof(mss);
	Getsockopt(sockfd, IPPROTO_TCP, TCP_MAXSEG, &mss, &len);    // 获取套接字sockfd MSS的值
	printf("defaults: SO_RCVBUF = %d, MSS = %d\n", rcvbuf, mss);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(13);		/* daytime server */
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	Connect(sockfd, (SA *) &servaddr, sizeof(servaddr));

	len = sizeof(rcvbuf);
	Getsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &rcvbuf, &len); // 获取 连接后 套接字sockfd的接收缓冲区大小
	len = sizeof(mss);
	Getsockopt(sockfd, IPPROTO_TCP, TCP_MAXSEG, &mss, &len);  // 获取 连接后 套接字sockfd MSS的值
	printf("after connect: SO_RCVBUF = %d, MSS = %d\n", rcvbuf, mss);

	exit(0);
}
