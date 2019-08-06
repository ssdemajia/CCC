#include "Acceptor.h"
#include "Socket.h"
#include <functional>
using namespace SS;

Acceptor::Acceptor(Eventloop* loop, IP& ip):
  loop(loop), accept_socket(), accept_channel(loop, accept_socket.get_fd()), listenning(false) {
  accept_socket.set_reuse_addr();
  accept_socket.bind_addr(ip);
  accept_channel.set_read_callback(std::bind(&Acceptor::handle_read, this));
}

void Acceptor::listen() {
  listenning = true;
  accept_socket.listen();
  accept_channel.enable_read();
}

void Acceptor::handle_read() {
  IP ip;
  int connfd = accept_socket.accept(ip);
  if (cb) cb(connfd, ip);
}