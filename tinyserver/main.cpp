#include "tools.h"
#include "http_parser.h"
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include <functional>

#define MAXLINE 1024

void handle(int);

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
    handle(connfd);
    close(connfd);
    printf("Close: %s:%s\n", client_host, client_port);
  }
  return 0;
}
int message_begin_cb(http_parser* p)
{
	return 0;
}
 
int header_field_cb(http_parser* p, const char* buf, size_t len)
{
	return 0;
}
 
int header_value_cb(http_parser* p, const char* buf, size_t len)
{
	return 0;
}
 
int request_url_cb(http_parser* p, const char* buf, size_t len)
{
	return 0;
}
 
int response_status_cb(http_parser*p, const char* buf, size_t len)
{
	return 0;
}
 
void check_body_is_final(const http_parser* p)
{
}
 
int body_cb(http_parser* p, const char* buf, size_t len)
{
	return 0;
}
 
int headers_complete_cb(http_parser* p)
{
	return 0;
}
 
int message_complete_cb(http_parser* p)
{
	return 0;
}
 
int chunk_header_cb(http_parser* p)
{
	return 0;
}
 
int chunk_complete_cb(http_parser* p)
{

	return 0;
}

void handle(int connfd) {
  http_parser_settings settings = { message_begin_cb, request_url_cb, response_status_cb, header_field_cb, header_value_cb,
				headers_complete_cb, body_cb, message_complete_cb, chunk_header_cb, chunk_complete_cb };
  http_parser* parser = (http_parser*)malloc(sizeof(http_parser));
  http_parser_init(parser, HTTP_REQUEST);
  char buf[MAXLINE];
  int read_count = 0;
  while ((read_count = read(connfd, buf, MAXLINE)) != 0) {
    if (errno == EINTR) {
      continue;
    }
    if (read_count == -1) {
      Log(stderr, "read error: %s\n", strerror(errno));
      break;
    }
    if (read_count != 0) {
      break;
    }
  }
  printf("received %d bytes: %s\n", (int)read_count, buf);
  http_parser_execute(parser, &settings, buf, read_count-1);
  printf("content-length: %ld\n", parser->content_length);
  send(connfd, "sssss", 6, 0);
}
