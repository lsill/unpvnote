#include	"unp.h"

// fp:stdin标准输入
void
dg_cli(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen)
{
	int	n;
	char	sendline[MAXLINE], recvline[MAXLINE + 1];

	while (Fgets(sendline, MAXLINE, fp) != NULL) {  // fp 从命令行读数据写入到sendline中

		Sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);

		n = Recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);

		recvline[n] = 0;	/* null terminate */
		Fputs(recvline, stdout);    // stdout 输出到命令行上
	}
}

// 调用recvfrom指定的第五和第六个参数是空指针。这告知内核我们并不关心应答数据报由谁发送。这样做存在一个风险:
// 任何进程不论是在与本客户进程相同的主机上还是在不同的主机上，都可以向本客户的IP地址和端又发送数据报，这些
// 数据报将被客户读入并被认为是服务器的应答。