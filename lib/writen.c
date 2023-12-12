/* include writen */
#include	"unp.h"
// fd:文件描述符，vptr:指向缓冲区的指针，n:要写入的字节数
ssize_t						/* Write "n" bytes to a descriptor. */
writen(int fd, const void *vptr, size_t n)
{
	size_t		nleft;  // 跟踪还需要写入的字节数
	ssize_t		nwritten;   // 存储单次 write 调用写入的字节数
	const char	*ptr;   // ptr 是一个字符指针，指向当前写入位置，加const是保证指向位置的值不会被修改 也就是*ptr = val是不合法的
    // 初始化
	ptr = vptr;
	nleft = n;
	while (nleft > 0) {
		if ( (nwritten = write(fd, ptr, nleft)) <= 0) {
			if (nwritten < 0 && errno == EINTR)
				nwritten = 0;		/* and call write() again  <-- */
			else
				return(-1);			/* error */
		}

		nleft -= nwritten;
		ptr   += nwritten;
	}
	return(n);  // writen要么成功写入所有字节，要么返回错误-1
}
/* end writen */

void
Writen(int fd, void *ptr, size_t nbytes)
{
	if (writen(fd, ptr, nbytes) != nbytes)
		err_sys("writen error");
}
