/*
这个例子没有使用线程池
 */
#include "../server/ss.h"
#include <string>
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h> // INET_ADDRSTRLEN

void *thread_func(void *args)
{
    Client *client = (Client *)args;
    char saddr[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(client->addr->sin_addr), saddr, sizeof(saddr));
    std::cout << saddr << std::endl;
    close(client->sockfd);
    delete client->addr;
    delete client;
    return nullptr;
}

int main(int argc, char const *argv[])
{
    int serverfd = get_ipv4_listener(9999); // 建立一个在0.0.0.0:9999上监听的socket
    pthread_t tid;
    while (true)
    {
        Client *client = new Client();
        client->addr = new sockaddr_in();
        socklen_t len = sizeof(sockaddr_in);
        client->sockfd = accept(serverfd, (sockaddr *)client->addr, &len);

        pthread_create(&tid, nullptr, thread_func, client);
    }
    return 0;
}
