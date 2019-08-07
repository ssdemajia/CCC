#include "Eventloop.h"
#include "IP.h"
#include "Acceptor.h"
#include <iostream>
void create_new_conn(int sockfd, SS::IP& ip) {
  printf("new connection");
  std::cout<<"who are you" << std::endl;
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