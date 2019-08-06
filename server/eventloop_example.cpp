#include "Eventloop.h"
#include <sys/timerfd.h>
#include <string.h>

SS::Eventloop* loop;

void timeout() {
  printf("Timeout\n");
  loop->quit();
}

int main(int argc, char const *argv[])
{
  loop = new SS::Eventloop();
  int timefd = timerfd_create(CLOCK_MONOTONIC, TFD_CLOEXEC|TFD_NONBLOCK);

  SS::Channel ch(loop, timefd);
  ch.set_read_callback(timeout);
  ch.enable_read();

  struct itimerspec howlong;
  bzero(&howlong, sizeof(howlong));
  howlong.it_value.tv_sec = 2;
  timerfd_settime(timefd, 0, &howlong, nullptr);

  loop->loop();
  close(timefd);
  return 0;
}
