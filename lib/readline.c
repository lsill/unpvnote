/* include readline */
#include	"unp.h"

static int	read_cnt;   // 追踪 read_buf 中剩余的未读字符数
static char	*read_ptr;  // 指向 read_buf 中下一个要读取的字符
static char	read_buf[MAXLINE];  // 用于存储从文件描述符读取的数据

static ssize_t
my_read(int fd, char *ptr)
{

	if (read_cnt <= 0) {    // read_buf中没有剩余的字符可读，需要从文件描述符中读取更多数据
again:
		if ( (read_cnt = read(fd, read_buf, sizeof(read_buf))) < 0) {
			if (errno == EINTR) // 信号中断后尝试恢复
				goto again;
			return(-1); // 发生错误后返回-1
		} else if (read_cnt == 0)   // 文件读取达到末尾
			return(0);
		read_ptr = read_buf;    // 将read_ptr指向重新读取的read_buf
	}

	read_cnt--; // 缓冲区剩余未读的字符减1
	*ptr = *read_ptr++; // read_ptr指向的当前指向的字符复制到ptr指向的位置，并递进到下一个字符
	return(1);
}

// fd:文件描述符 vptr:是指向调用者提供的缓冲区的指针，maxlen:缓冲区的最大长度。
ssize_t
readline(int fd, void *vptr, size_t maxlen)
{
	ssize_t	n, rc;  // 记录已经读取的字符数
	char	c, *ptr;    // 临时存储从my_read读取的字符

	ptr = vptr; // 让ptr指向缓冲区
	for (n = 1; n < maxlen; n++) {
		if ( (rc = my_read(fd, &c)) == 1) { // == 1成功读取
			*ptr++ = c; // ptr指向位置的值更新为c，ptr指向下一个位置
			if (c == '\n')
				break;	/* newline is stored, like fgets() 遇到换行符跳出循环*/
		} else if (rc == 0) {   // 所有都读取完了
			*ptr = 0;   // 0（空字符）终止字符串
			return(n - 1);	/* EOF, n - 1 bytes were read */
		} else
			return(-1);		/* error, errno set by read() */
	}

	*ptr = 0;	/* null terminate like fgets() */
	return(n);
}

ssize_t
readlinebuf(void **vptrptr)
{
	if (read_cnt)
		*vptrptr = read_ptr;
	return(read_cnt);
}
/* end readline */

ssize_t
Readline(int fd, void *ptr, size_t maxlen)
{
	ssize_t		n;

	if ( (n = readline(fd, ptr, maxlen)) < 0)
		err_sys("readline error");
	return(n);
}
