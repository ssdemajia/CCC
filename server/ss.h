/*
这个头文件主要定义了一下比如建立socket连接相关的api
 */

#if !defined(SS_H)
#define SS_H

#include <sys/socket.h>
#include <arpa/inet.h> // inet_pton
#include <string.h> // bzero
struct Client {
  int sockfd;
  sockaddr_in* addr;
};
int get_ipv4_listener(int port);

#endif // SS_H
