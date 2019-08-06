#ifndef SS_IP_H
#define SS_IP_H

#include <netinet/in.h> // sockaddr_in

#include <string>
namespace SS
{
  class IP {
    public:
      IP() {}
      IP(const std::string ip, uint16_t port);
      struct sockaddr_in& get_addr();
      void set_addr(sockaddr_in& in_addr) { addr = in_addr; }
      void set_addr(sockaddr* in_addr) {
        auto a = (sockaddr_in*)in_addr;
        addr = *a;
      }
    private:
      sockaddr_in addr;
  };
} // namespace SS
#endif