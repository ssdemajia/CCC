#include "Eventloop.h"

void create_new_conn(int sockfd, SS::IP& ip) {
  printf("new connection")
  write("who are you");
  close(sockfd);
}
int main() {
  SS::IP ip("127.0.0.1", 8989);
  SS::Eventloop loop;
  SS::Acceptor ac(&loop, ip);
  ac.set_callback(create_new_conn);
  ac.listen();

  loop.loop();
}