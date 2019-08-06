#include "IP.h"
#include <arpa/inet.h> // inet_pton
#include <strings.h>
#include <iostream>

using namespace SS;

IP::IP(const std::string ip, uint16_t port) {
  ::bzero(&addr, sizeof(struct sockaddr_in));
  const char* cip = ip.c_str();
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  int status = inet_pton(AF_INET, cip, &addr.sin_addr);
  if (status == 0) {
    std::cerr << "IP格式错误：" << ip << std::endl;
  }
  if (status == -1) {
    std::cerr << "IP转换错误：" << ip << std::endl;
  }
}

struct sockaddr_in& IP::get_addr() {
  return addr;
}