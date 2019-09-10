#ifndef TINYSERVER_TOOLS_H
#define TINYSERVER_TOOLS_H

#include <string>
#include <sys/socket.h>

typedef struct sockaddr SA;

/* 将网络序的ip地址转换为字符串形式 */
std::string hex2dd(uint32_t add); 

/* 日志打印文件 */
void Log(FILE* target, char* fmt, ...);

/* 下面是系统函数的包装函数 */
int Socket(int domain, int type, int protocol);
void Connect(int clientfd, const SA* addr, socklen_t addrlen);
void Bind(int sockfd, const SA * addr, socklen_t addrlen);
void Listen(int sockfd, int backlog);
int Accept(int listenfd, SA* addr, socklen_t* addrlen);

#endif