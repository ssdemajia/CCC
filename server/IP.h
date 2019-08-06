#ifndef SS_IP_H
#define SS_IP_H

#include <netinet/in.h> // sockaddr_in

#include <string>
namespace SS
{
  class IP {
    public:
      IP(const std::string ip, uint16_t port);
      ~IP();
    private:
      struct sockaddr_in* addr;
  };
} // namespace SS
#endif