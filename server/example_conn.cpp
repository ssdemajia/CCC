#include "Eventloop.h"
#include "Server.h"
#include "Conn.h"
using namespace SS;
void onConnection(ConnPtr conn) {
  if (conn->is_connected()) {
    printf("connected!\n");
  }
}

void onMessage(ConnPtr conn, char* buf, size_t n) {
  printf("onMessage\n");
  buf[n-1] = '\0';
  printf("receive msg:%s\n", buf);
}
int main() {
  Eventloop loop;
  IP ip("127.0.0.1", 9999);
  Server server(&loop, ip, "test server");
  server.set_conn_callback(onConnection);
  server.set_msg_callback(onMessage);
  server.start();
  loop.loop();
}