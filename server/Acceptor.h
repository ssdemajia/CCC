#ifndef ACCEPTOR_H
#define ACCEPTOR_H
#include <string>
#include <functional>

#include "Eventloop.h"
#include "IP.h"
#include "Socket.h"
namespace SS
{
  typedef std::function<void(int, IP&)> new_conn_callback;
  class Acceptor {
    public:
      Acceptor(Eventloop* loop, IP& ip);

      void set_callback(new_conn_callback cb) { this->cb = cb; }
      void listen();
      bool is_listenning() { return listenning; }
    private:
      void handle_read();
      Eventloop* loop;
      Socket accept_socket;
      Channel accept_channel;
      new_conn_callback cb;
      bool listenning = false;
  };
} // namespace SS

#endif