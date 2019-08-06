#ifndef SS_SOCKET_H
#define SS_SOCKET_H
#include <sys/types.h>
#include <string>

#include "IP.h"

namespace SS
{
  class Socket {
    public:
      Socket(int sockfd);
      Socket();
      ~Socket();

      int get_fd() { return sockfd; }
      void listen();
      void set_reuse_addr();
      void bind_addr(IP &ip);
      int accept(IP& ip);
    private:
      int sockfd;
  };
} // namespace SS

#endif