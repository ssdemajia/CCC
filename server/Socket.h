#ifndef SS_SOCKET_H
#define SS_SOCKET_H
#include <sys/types.h>
#include <string>
namespace SS
{
  class Socket {
    public:
      Socket(int sockfd);
      Socket(const std::string addr, uint16_t port);
  };
} // namespace SS

#endif