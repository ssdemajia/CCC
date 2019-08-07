#include "Server.h"
#include <string.h>
// #include <functional>

using namespace SS;

Server::Server(Eventloop* loop, IP& ip, const std::string name):
  loop(loop), name(name), acceptor(loop, ip), conn_id(0), local_ip(ip)
{
  acceptor.set_callback(std::bind(&Server::new_connection, this, std::placeholders::_1, std::placeholders::_2));
}

void Server::new_connection(int sockfd, IP& peer_ip) {
  assert(sockfd > 0);
  char buf[32];
  snprintf(buf, sizeof(buf), "#%d", conn_id);
  conn_id++;
  std::string conn_name = name + buf;
  std::cout << "server.new_connection:" << conn_name << ", peer:" << peer_ip.get_ip() << std::endl;
  ConnPtr connp = std::make_shared<Conn>(this, loop, conn_name, sockfd, local_ip, peer_ip);
  connections[conn_name] = connp;
  connp->set_msg_callback(msg_cb);
  connp->set_conn_callback(conn_cb);
  connp->established();
}

void Server::start() {
  is_started = true;
  acceptor.listen();
}