//
// Created by lsill on 2023/12/27.
//
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>

void print_buffer_size(int sock_fd, int opt_name, const char* opt_desc)
{
    int opt_val;
    socklen_t opt_len = sizeof(opt_val);
    // int     getsockopt(int fd,int level, int opt_name, void * __restrict, socklen_t * __restrict);
    // level : 这个参数指定了选项的代码级别。例如，要获取套接字层面的选项，使用 SOL_SOCKET。对于特定协议（如 TCP）的选项，使用相应的协议级别（例如，IPPROTO_TCP）
    // opt_name: 这个参数指定了要访问的选项的名称。例如，SO_REUSEADDR、SO_RCVBUF 等。不同的 opt_name 值允许访问套接字的不同属性。
    // __restrict: 这是一个指向变量的指针，用于存储获取的选项值, 调用函数前，需要分配足够的空间来存储返回的选项值
    // _restrict:这个变量将被设置为实际返回的选项值的大小。
    if (getsockopt(sock_fd, SOL_SOCKET, opt_name, &opt_val, &opt_len) < 0 )
    {
        perror("get socket opt failed");
        exit(EXIT_FAILURE);
    }
    printf("%s: %d\n", opt_desc, opt_val);
}

int main()
{
    int tcp_sock, udp_sock;

    tcp_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (tcp_sock < 0)
    {
        perror("TCP socket creation failed");
        exit(EXIT_FAILURE);
    }
    udp_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (udp_sock < 0) {
        perror("UDP socket creation failed");
        exit(EXIT_FAILURE);
    }
    print_buffer_size(tcp_sock, SO_SNDBUF, "TCP Send Buffer Size");
    print_buffer_size(tcp_sock, SO_RCVBUF, "TCP RECV Buffer Size");

    print_buffer_size(udp_sock, SO_SNDBUF, "UDP Send Buffer Size");
    print_buffer_size(udp_sock, SO_RCVBUF, "UDP RECV Buffer Size");

    close(tcp_sock);
    close(udp_sock);

    return 0;
}