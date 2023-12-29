//
// Created by lsill on 2023/12/28.
//

#include <sys/socket.h>
#include <cstdlib>
#include <cstring>
#include <arpa/inet.h>

int main(int argc, char** argv)
{
    if (argc != 2)
        exit(0);

    int sockfd;
    socklen_t len;
    struct sockaddr_in addr, cli_addr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(4444);
    struct in_addr in;
    inet_aton(argv[1], &in);
    addr.sin_addr = in;

    if (connect(sockfd, (sockaddr *)&addr, sizeof(addr))< 0)
    {
        exit(0);
    }

    len = sizeof(cli_addr);
    getsockname(sockfd, (sockaddr*) &cli_addr, &len);
}
