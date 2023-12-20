#include	"unp.h"

void
str_cli(FILE *fp, int sockfd)
{
	char	sendline[MAXLINE], recvline[MAXLINE];
    // 使用 Fgets 函数从 fp 指向的文件流中读取一行文本到 sendline。Fgets 会在遇到换行符或文件结束时停止读取。
	while (Fgets(sendline, MAXLINE, fp) != NULL) {
        // 将 sendline 中的数据发送到服务器。strlen(sendline) 确定要发送的字节数。
		Writen(sockfd, sendline, strlen(sendline));

		if (Readline(sockfd, recvline, MAXLINE) == 0)
			err_quit("str_cli: server terminated prematurely");
        // 将从服务器接收的数据（存储在 recvline 中）使用 Fputs 函数输出到标准输出（stdout
        // ）。这样，服务器的响应就可以在用户的屏幕上显示。
		Fputs(recvline, stdout);
	}
}
