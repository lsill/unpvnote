#include	"../lib/unp.h"

// dg_cli 是和协议无关的，不能查看传递给connect的套接字地址结构的内容
// 函数启动后如果服务器未启动不会报错，只有尝试发包的时候才会报错，因为没有tcp的三次握手
void
dg_cli(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen)
{
	int		n;
	char	sendline[MAXLINE], recvline[MAXLINE + 1];

	Connect(sockfd, (SA *) pservaddr, servlen);

	while (Fgets(sendline, MAXLINE, fp) != NULL) {

		Write(sockfd, sendline, strlen(sendline));

		n = Read(sockfd, recvline, MAXLINE);

		recvline[n] = 0;	/* null terminate */
		Fputs(recvline, stdout);
	}
}
