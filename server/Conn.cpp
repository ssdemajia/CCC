#include "Conn.h"
#include <functional>
#include "Server.h"
using namespace SS;

Conn::Conn(Server* server, Eventloop* loop, const std::string& name, int sockfd, IP& local_ip, IP& peer_ip):
  loop(loop), state(Connecting), name(name), local_ip(local_ip), peer_ip(peer_ip), 
  sock(sockfd), channel(loop, sockfd), server(server)
{
  channel.set_read_callback(std::bind(&Conn::handle_read, this)); // 绑定非静态函数使用指针
}

void Conn::handle_read() {
  char buf[65535];
  size_t n = read(channel.get_fd(), buf, sizeof(buf));
  printf("Conn::handle_read read:%ld, %s\n", n, name.c_str());
  ConnPtr conn_ptr = server->get_connection(name);
  msg_cb(conn_ptr, buf, n);
}

void Conn::established() {
  assert(state == Connecting);
  state = Connected;
  channel.enable_read();
}