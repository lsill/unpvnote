#include	"../lib/unp.h"

void
str_cli(FILE *fp, int sockfd)
{
	int			maxfdp1, stdineof;
	fd_set		rset;
	char		buf[MAXLINE];
	int		n;

	stdineof = 0;   // 标志为0表示 select标准输入的可读性
	FD_ZERO(&rset);
	for ( ; ; ) {
		if (stdineof == 0)
			FD_SET(fileno(fp), &rset);
		FD_SET(sockfd, &rset);
		maxfdp1 = max(fileno(fp), sockfd) + 1;
		Select(maxfdp1, &rset, NULL, NULL, NULL);

		if (FD_ISSET(sockfd, &rset)) {	/* socket is readable */    // sockfd一直在rset集合中，表示在遇到stdineof为1前，可以一直读取数据
			if ( (n = Read(sockfd, buf, MAXLINE)) == 0) {
				if (stdineof == 1)
					return;		/* normal termination */
				else
					err_quit("str_cli: server terminated prematurely");
			}

			Write(fileno(stdout), buf, n);
		}

		if (FD_ISSET(fileno(fp), &rset)) {  /* input is readable */ // 如果还有描述符fd还有数据可读，那么可以继续回写
			if ( (n = Read(fileno(fp), buf, MAXLINE)) == 0) {
				stdineof = 1;
				Shutdown(sockfd, SHUT_WR);	/* send FIN */  // SHUT_WR 关闭连接的写这一半
                // 当前留在套接字发送缓冲区中的数据将被发送掉，后跟TCP的正常连接终止序列。
                // 不管套接字描述符的引用计数是否等于0，这样的写半部关闭照样执行。
                // 进程不能再对这样的套接字调用任何写函数。
				FD_CLR(fileno(fp), &rset);  // 删除rset中的fp，防止再次进入回写服务器逻辑中
				continue;
			}

			Writen(sockfd, buf, n);
		}
	}
}


// int shutdown (int sockfd, int howto);
// howto 选项
// SHUT_RD
// 关闭连接的读这一半——套接字中不再有数据可接收，而且套接字接收缓冲区中的现有数据都被丢弃。
// 进程不能再对这样的套接字调用任何读函数数。
// 对一个TCP套接字这样调用shutdow函数后，由该套接字接收的来自对端的任何数据都被确认，然后悄然丢弃
// StHUT_WR
// 关闭连接的写这一半——对于TCP套接字，这称为半关闭(half close)。当前留在套接字发送缓冲区中的数据
// 将被发送掉，后跟TCP的正常连接终止序列。不管套接字描述符的引用计数是否等于0，这样的写半部关闭照样
// 执行。进程不能再对这样的套接字调用任何写函数。