#include	"../lib/unp.h"

int main(int argc, char **argv)
{
    pid_t pid;
    int listenfd, connfd;
    listenfd = Socket( ... );
    // fill in sockaddr_in() with server's well-known port
    Bind(listenfd, ...);
    Listen(listenfd, LISTENQ);
    for (; ;)
    {
        // 等待连接建立
        connfd = Accept(listenfd, ...); // probably blocks
        if ((pid = Fork()) == 0)
        {
            // 子进程处理doit服务
            Close(listenfd);    // child closes listening socket
            doit(connfd);       // process the request
            Close(connfd);      // done with this client
            exit(0);            // child terminates
        }
        // 子进程已经对connfd提供服务，父进程就可以关闭连接套接字
        Close(connfd);          // parent closes connected socket
    }
}