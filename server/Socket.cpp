#include "Socket.h"
#include <unistd.h> // close(fd)
#include <sys/socket.h>
#include <string.h> // strerror
#include <assert.h>
#include <vector>
#include <iostream>

using namespace SS;

Socket::Socket(int sockfd) {
  this->sockfd = sockfd;
}

Socket::Socket(): sockfd(-1) {
#if __APPLE__
  sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
#else
  sockfd = socket(AF_INET, SOCK_STREAM|SOCK_NONBLOCK|SOCK_CLOEXEC, IPPROTO_TCP);
#endif
  if (sockfd < 0) {
    std::cerr << "create socket error" << std::endl;
  }
}

Socket::~Socket() {
  if (sockfd != -1)
    close(sockfd);
}

void Socket::set_reuse_addr() {
  int enable = 1;
  if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) < 0) {
    std::cerr << "set reuse addr socket error" << std::endl;
  }
}

void Socket::bind_addr(IP &ip) {
  assert(sockfd != -1);
  sockaddr* addr = (sockaddr*)&ip.get_addr();
  if (::bind(sockfd, (sockaddr*)&ip.get_addr(), sizeof(ip.get_addr())) < 0) {
    std::cerr << "bind socket error" << std::endl;
  }
}

void Socket::listen() {
  assert(sockfd != -1);
  if (::listen(sockfd, 16) < 0) {
    std::cerr << "listen socket error:" << strerror(errno) << std::endl;
  }
}

int Socket::accept(IP& ip) {
  struct sockaddr addr;
  socklen_t size;
  int connfd = ::accept(sockfd, &addr, (socklen_t*)&size);
  if (connfd < 0) {
    std::cerr << "accept socket error:" << strerror(errno) << std::endl;
  }
  ip.set_addr(&addr);
  std::cout << "accept:" << connfd << ", ip:" << ip.get_ip() << ",port:" << ip.get_port()<< std::endl;
  return connfd;
}