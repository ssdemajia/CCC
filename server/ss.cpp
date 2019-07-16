#include "ss.h"

int get_ipv4_listener(int port)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_port = htons(port);
    addr.sin_family = AF_INET;
    inet_pton(AF_INET, "0.0.0.0", &addr.sin_addr);
    bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
    listen(sockfd, 15);
    return sockfd;
}

