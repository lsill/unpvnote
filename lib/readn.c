/* include readn */
#include	"unp.h"

// EINTR错误 （表示系统调用被一个捕获的信号中断）
// fd:文件描述符，vptr:指向缓冲区的指针，n:要读取的字节数
ssize_t						/* Read "n" bytes from a descriptor. */
readn(int fd, void *vptr, size_t n)
{
	size_t	nleft;  // 跟踪还需要读取的字节数
	ssize_t	nread;  // 单词read读取的字节数
	char	*ptr;   // 指向当前读取的位置

	ptr = vptr; // 指向读取开始的位置 (void*) 转换为 (char*) 是因为指针必须按照所读或者所写的字节数增长，但c但允许void指针增长（c编译器不知道void指向的数据类型）
	nleft = n;
	while (nleft > 0) {
		if ( (nread = read(fd, ptr, nleft)) < 0) {
			if (errno == EINTR)
				nread = 0;		/* and call read() again */
			else
				return(-1);
		} else if (nread == 0)
			break;				/* EOF */

		nleft -= nread;
		ptr   += nread;
	}
	return(n - nleft);		/* return >= 0 */   // 读取了所有的字节后返回0
}
/* end readn */

ssize_t
Readn(int fd, void *ptr, size_t nbytes)
{
	ssize_t		n;

	if ( (n = readn(fd, ptr, nbytes)) < 0)
		err_sys("readn error");
	return(n);
}
