#ifndef SS_CONN_H
#define SS_CONN_H
/*
这个文件主要定义Conn这个类，每个conn表示一个连接
*/

#include <memory>
#include "Eventloop.h"
#include "IP.h"
#include "Socket.h"
// #include "Server.h"
namespace SS
{
  class Server;
  class Conn;
  typedef std::shared_ptr<Conn> ConnPtr;
  typedef std::function<void(ConnPtr, char*, size_t)> MsgCallback;
  typedef std::function<void(ConnPtr)> ConnCallback;

  class Conn
  {
    public:
      Conn(Server* server, Eventloop* loop, const std::string& name, int sockfd, IP& local_ip, IP& peer_ip);
      void send(void *buf, size_t len);
      void set_msg_callback(MsgCallback cb) { msg_cb = cb; }
      void set_conn_callback(ConnCallback cb) { conn_cb = cb; }
      void established();
      bool is_connected() { return state == Connected; }
      
    private:
      void handle_read();
      enum State {Connecting, Connected, Disconnected};
      State state;

      std::string name;
      Eventloop* loop;
      Server* server;
      IP local_ip;
      IP peer_ip;
      Socket sock;
      Channel channel;
      MsgCallback msg_cb;
      ConnCallback conn_cb;  
  };
} // namespace SS

#endif