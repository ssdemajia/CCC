#ifndef SERVER_H
#define SERVER_H

#include <functional>
#include <map>

#include "Eventloop.h"
#include "IP.h"
#include "Acceptor.h"
#include "Conn.h"

namespace SS
{
class Server {
  public:
    Server(Eventloop* loop, IP& ip, const std::string name);

    void start();
    ConnPtr get_connection(const std::string& name) { return connections[name]; }
    void set_msg_callback(MsgCallback cb) { msg_cb = cb; }
    void set_conn_callback(ConnCallback cb) { conn_cb = cb; }

  private:
    void new_connection(int fd, IP& ip);
    
    bool is_started;
    std::string name;
    int conn_id;
    IP local_ip;
    Eventloop* loop;
    Acceptor acceptor;
    std::map<std::string, ConnPtr> connections;
    MsgCallback msg_cb;
    ConnCallback conn_cb;
};
} // namespace ss
#endif