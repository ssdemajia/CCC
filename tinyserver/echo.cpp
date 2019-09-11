#include "tools.h"
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define MAXLINE 1024

void echo(int);

int main(int argc, char const *argv[])
{
  if (argc != 2) {
    Log(stderr, "usage: %s <port>\n", argv[0]);
    exit(0);
  }
  int listenfd, connfd;
  char client_host[MAXLINE], client_port[MAXLINE];
  struct sockaddr_storage clientaddr;

  listenfd = OpenListenfd(argv[1]);
  if (listenfd == -1) {
    Log(stderr, "openlistenfd error\n");
    exit(0);
  }
  while (true) {
    socklen_t clientlen = sizeof(struct sockaddr_storage);
    connfd = Accept(listenfd, (SA*)&clientaddr, &clientlen);
    Getnameinfo((SA*)&clientaddr, clientlen, 
                client_host, MAXLINE,
                client_port, MAXLINE, 0);
    printf("Connected: %s:%s\n", client_host, client_port);
    echo(connfd);
    close(connfd);
    printf("Close: %s:%s\n", client_host, client_port);
  }
  return 0;
}

void echo(int connfd) {
  char buf[MAXLINE];
  int read_count = 0;
  while ((read_count = read(connfd, buf, MAXLINE)) != 0) {
    if (read_count == -1) {
      Log(stderr, "echo error: %s\n", strerror(errno));
      exit(0);
    }
    printf("received %d bytes\n", (int)read_count);
    write(connfd, buf, read_count);
  }
}
