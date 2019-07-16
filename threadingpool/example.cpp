#include "threadpool.h"
#include "task.h"
#include "../server/ss.h"
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h> // INET_ADDRSTRLEN


class EchoTask: public Task {
public:
  void run() {
    Client * client = (Client*)args;
    char saddr[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(client->addr->sin_addr), saddr, sizeof(saddr));
    std::cout << saddr << std::endl;
    close(client->sockfd);
    delete client->addr;
    delete client;
  }
};


int main(int argc, char const *argv[])
{
  int threads_num = 10;
  ThreadPool* pool = ThreadPool::create_pool(threads_num);
  int serverfd = get_ipv4_listener(9999);  // 建立一个在0.0.0.0:9999上监听的socket

  while (true) {
    Client* client = new Client();
    client->addr = new sockaddr_in();
    socklen_t len = sizeof(sockaddr_in);
    client->sockfd = accept(serverfd, (sockaddr*)client->addr, &len);
    Task* t = new EchoTask();
    t->set_args(client);
    pool->add_task(t);
  }
  return 0;
}
