#include "tools.h"
#include <arpa/inet.h>
#include <errno.h>
#include <string.h> // strerror
#include <stdarg.h>

void Log(FILE* target, char* fmt, ...) {
  va_list valist;
  va_start(valist, fmt);
  char banner[] = "[tinyserver]";
  int new_length = sizeof(banner+strlen(fmt));
  char* newfmt = new char[new_length];
  newfmt[new_length] = '\0';
  strcpy(newfmt, banner);
  strcpy(newfmt+ new_length, fmt);
  vfprintf(target, newfmt, valist);
  va_end(valist);
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
void Listen(int sockfd, int backlog=10) {
  if (listen(sockfd, backlog) != 0) {
    Log(stderr, "listen error: %s\n", strerror(errno));
    exit(0);
  }
}
int Accept(int listenfd, SA* addr, socklen_t* addrlen) {
  int clientfd;
  if ((clientfd = accept(listenfd, addr, addrlen)) == -1) {
    Log(stderr, "accpet error: %s\n", strerror(errno));
    exit(0);
  }
  return clientfd;
}