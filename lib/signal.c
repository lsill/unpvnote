/* include signal */
#include	"unp.h"

// typedef	void	Sigfunc(int);	/* for signal handlers */
// signo:信号编号 func:指向函数的指针
Sigfunc *
signal(int signo, Sigfunc *func)
{
	struct sigaction	act, oact;  // act:处理新的信号行为 oact:保存旧的信号处理行为

	act.sa_handler = func;
	sigemptyset(&act.sa_mask);  // sigemptyset 初始化一个空的信号集
	act.sa_flags = 0;   // sa_flags 成员设置为 0，这意味着没有特殊的行为被设置。
	if (signo == SIGALRM) {
#ifdef	SA_INTERRUPT
		act.sa_flags |= SA_INTERRUPT;	/* SunOS 4.x */
#endif
	} else {
#ifdef	SA_RESTART
		act.sa_flags |= SA_RESTART;		/* SVR4, 44BSD */
#endif
	}
	if (sigaction(signo, &act, &oact) < 0)  // sigaction 函数来设置指定信号的处理行为
		return(SIG_ERR);
	return(oact.sa_handler);
}
/* end signal */

Sigfunc *
Signal(int signo, Sigfunc *func)	/* for our signal() function */
{
	Sigfunc	*sigfunc;

	if ( (sigfunc = signal(signo, func)) == SIG_ERR)
		err_sys("signal error");
	return(sigfunc);
}
