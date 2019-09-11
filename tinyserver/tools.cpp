#include "tools.h"
#include <arpa/inet.h>
#include <errno.h>
#include <string.h> // strerror
#include <stdarg.h>
#include <netdb.h>  // getaddrinfo
#include <unistd.h> // close

void Log(FILE* target, const char* fmt, ...) {
  va_list valist;
  va_start(valist, fmt);
  char banner[] = "[tinyserver]";
  int new_length = sizeof(strlen(banner) + strlen(fmt)+1);
  char* newfmt = new char[new_length];
  newfmt[new_length] = '\0';
  strcpy(newfmt, banner);
  strcat(newfmt+ new_length, fmt);
  vfprintf(target, newfmt, valist);
  va_end(valist);
}

int OpenClientfd(const char* hostname, char* port) {
  int clientfd;
  struct addrinfo hints, *listp, *p;

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_NUMERICSERV | AI_ADDRCONFIG;
  Getaddrinfo(hostname, port, &hints, &listp);
  /* 遍历地址链表 */
  for (p = listp; p; p = p->ai_next) { 
    if ((clientfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0) 
      continue;
    if (connect(clientfd, p->ai_addr, p->ai_addrlen) != -1)
      break;
    Close(clientfd);
  }
  freeaddrinfo(listp);
  if (!p) return -1;
  return clientfd;
}

int OpenListenfd(const char* port) {
  int listenfd, optval = 1;
  struct addrinfo hints, *listp, *p;

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG | AI_NUMERICSERV;
  Getaddrinfo(nullptr, port, &hints, &listp);
  /* 遍历地址链表 */
  for (p = listp; p; p = p->ai_next) { 
    if ((listenfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0) 
      continue;
    Setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int));
    if (bind(listenfd, p->ai_addr, p->ai_addrlen) == 0)
      break;
    Close(listenfd);
  }
  freeaddrinfo(listp);
  if (!p) return -1;

  Listen(listenfd);
  return listenfd;
}

std::string hex2dd(uint32_t add) {
  char *caddr = new char[INET_ADDRSTRLEN];
  caddr[INET_ADDRSTRLEN-1] = '\0';
  inet_ntop(AF_INET, &add, caddr, INET_ADDRSTRLEN);
  return std::string(caddr);
}

int Socket(int domain, int type, int protocol) {
  int sockfd;
  if ((sockfd = socket(domain, type, protocol)) < 0) {
    Log(stderr, "socket error: %s\n", strerror(errno));
    exit(0);
  }
  return sockfd;
}
void Connect(int clientfd, const SA* addr, socklen_t addrlen) {
  if (connect(clientfd, addr, addrlen) != 0) {
    Log(stderr, "connect error: %s\n", strerror(errno));
    exit(0);
  }
}
void Bind(int sockfd, const SA * addr, socklen_t addrlen) {
  if (bind(sockfd, addr, addrlen) != 0) {
    Log(stderr, "bind error: %s\n", strerror(errno));
    exit(0);
  }
}
void Listen(int sockfd, int backlog) {
  if (listen(sockfd, backlog) != 0) {
    Log(stderr, "listen error: %s\n", strerror(errno));
    exit(0);
  }
}
int Accept(int listenfd, SA* addr, socklen_t* addrlen) {
  int clientfd;
  if ((clientfd = accept(listenfd, addr, addrlen)) == -1) {
    Log(stderr, "accpet error: %s\n", strerror(errno));
    close(listenfd);
    exit(0);
  }
  return clientfd;
}

void Getaddrinfo(const char* host, const char* service, 
                 const struct addrinfo* hints, struct addrinfo** result) 
{
  int errcode = getaddrinfo(host, service, hints, result);
  if (errcode != 0) {
    Log(stderr, "getaddrinfo error: %s\n", gai_strerror(errcode));
  }              
}

/* 根据地址结构体获得主机地址、服务端口 */
void Getnameinfo(const SA* sa, socklen_t salen, char* host, size_t hostlen,
                 char* service, size_t servlen, int flags) 
{
  int errcode = getnameinfo(sa, salen, host, hostlen, service, servlen, flags);
  if (errcode != 0) {
    Log(stderr, "getnameinfo error: %s\n", gai_strerror(errcode));
  }
}

void Setsockopt(int sockfd, int level, int optname,
             const void *optval, socklen_t optlen) {
  if (setsockopt(sockfd, level, optname, optval, optlen) != 0) {
    Log(stderr, "setsockopt error: %s\n", strerror(errno));
    exit(0);
  }
}

void Close(int fd) {
  if (close(fd) != 0) {
    Log(stderr, "close error: %s\n", strerror(errno));
    exit(0);
  }
}