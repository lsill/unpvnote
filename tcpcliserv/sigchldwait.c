#include	"../lib/unp.h"

void
sig_chld(int signo)
{
	pid_t	pid;
	int		stat;

	pid = wait(&stat);  // wait 函数返回结束子进程的 PID，并将退出状态写入 stat。
	printf("child %d terminated\n", pid);
	return;
}
