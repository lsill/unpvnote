#include	"../lib/unp.h"

int
main(int argc, char **argv)
{
	int					sockfd;
	struct sockaddr_in	servaddr;

	if (argc != 2)
		err_quit("usage: tcpcli <IPaddress>");

	sockfd = Socket(AF_INET, SOCK_STREAM, 0);

    // 初始化目标服务器地址
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);    // argv[1] 目标ip地址

	Connect(sockfd, (SA *) &servaddr, sizeof(servaddr));

    // stdin 标准输入读取数据
    // 通常用于从命令行或终端读取用户输入。它是一个预定义的文件流，与程序的标准输入设备关联，通常是键盘。
	str_cli(stdin, sockfd);		/* do it all */

	exit(0);
}
