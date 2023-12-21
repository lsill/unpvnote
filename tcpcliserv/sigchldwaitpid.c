#include	"../lib/unp.h"

void
sig_chld(int signo)
{
	pid_t	pid;
	int		stat;

	while ( (pid = waitpid(-1, &stat, WNOHANG)) > 0)    // -1 等待任意子进程 WNOHANG使子进程不被阻塞，如果没有子进程退出，waitpid立马返回而不是等待
		printf("child %d terminated\n", pid);
	return;
}
