#include	"../lib/unp.h"

//(1)如果对端TCP发送数据，那么该套接字变为可读，并且read返回一个大于0的值(即读入数据的字节数)。
//(2)如果对端TCP发送一个FIN(对端进程终止)，那么该套接字变为可读，并且read返回0(EOF).
//(3)如果对端TCP发送一个RST(对端主机崩溃并重新启动)，那么该套接字变为可读，并且read返回-1，而errno中含有确切的错误码。
void
str_cli(FILE *fp, int sockfd)
{
	int			maxfdp1;
	fd_set		rset;   // select 调用描述符的集合
	char		sendline[MAXLINE], recvline[MAXLINE];

	FD_ZERO(&rset); // 初始化描述符集合
	for ( ; ; ) {
		FD_SET(fileno(fp), &rset);  // 添加文件描述符fd到集合中
		FD_SET(sockfd, &rset);  // 添加到套接字(也是描述符)到集合中
		maxfdp1 = max(fileno(fp), sockfd) + 1;  // maxfdp1，它的值是待测试的最大描达符加1,描述符0，1,2...maxfdp1 - 1均将被测试。
		Select(maxfdp1, &rset, NULL, NULL, NULL);   // 阻塞，知道fp或者sockfd 到可读
		if (FD_ISSET(sockfd, &rset)) {	/* socket is readable */
			if (Readline(sockfd, recvline, MAXLINE) == 0)
				err_quit("str_cli: server terminated prematurely");
			Fputs(recvline, stdout);
		}

		if (FD_ISSET(fileno(fp), &rset)) {  /* input is readable */
			if (Fgets(sendline, MAXLINE, fp) == NULL)
				return;		/* all done */
			Writen(sockfd, sendline, strlen(sendline));
		}
	}
}

// 潜在的问题考感有多个来自标准输入的文本输入行可用的情况，使用fgets读取输入，使可用的文本
// 输入行呗读入到stdio(fp)所用的缓存区中，然而，fgets只返回其中的一行，其余输入行
// 仍在stdio缓冲区中。Writen把fgets返回的单个输入行写给服务器，然后select再次被调用
// 以等待新的工作，而不管stdio缓冲区中还有额外的输入行待消费。究其原因在于select不知道stdio
// 使用了缓冲区————select只是从read系统调用的角度指出是否有数据可读，而不是从fgets之类的
// 调用考虑。混合使用stdio和select被认为是非常容易犯错误的，这样做的时候要小心。

// 同样的问题存在于readline调用中。这回select不可见的数据不是隐藏在stdio级冲区中，而是隐藏
// 在readline自己的缓冲区中。
// 因此可能的解决办法之一是修改我们的代码，在调用select之前使用可以看的到缓冲区的函数数，以查
// 看是否存在己经读入而尚末消费的数据。然而为了处理readline缓冲区中既可能有不完整的输入行〈意
// 味着我们需要继续读入)，也可能有一个或多个完整的输入行(这些行我们可以直接消费)这两种情况而引
// 入的复杂性会迅速增长到难以控制的地步。