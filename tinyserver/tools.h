#ifndef TINYSERVER_TOOLS_H
#define TINYSERVER_TOOLS_H

#include <string>
#include <sys/socket.h>

typedef struct sockaddr SA;

/* 将网络序的ip地址转换为字符串形式 */
std::string hex2dd(uint32_t add); 

/* 建立与hostname的连接 */
int OpenCistenfd(const char* hostname, char* port);

/* 创建一个监听描述符 */
int OpenListenfd(const char* port);

/* 日志打印文件 */
void Log(FILE* target, const char* fmt, ...);

/* 系统函数的包装函数 */
int Socket(int domain, int type, int protocol);
void Connect(int clientfd, const SA* addr, socklen_t addrlen);
void Bind(int sockfd, const SA * addr, socklen_t addrlen);
void Listen(int sockfd, int backlog = 10);
int Accept(int listenfd, SA* addr, socklen_t* addrlen);
void Getaddrinfo(const char* host, const char* service, 
                 const struct addrinfo* hints, struct addrinfo** result);
void Getnameinfo(const SA* sa, socklen_t salen, char* host, size_t hostlen,
                 char* service, size_t servlen, int flags);
void Setsockopt(int sockfd, int level, int optname,
                const void *optval, socklen_t optlen);
#endif