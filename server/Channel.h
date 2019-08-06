#ifndef CHANNEL_H
#define CHANNEL_H
#include <functional>

namespace SS
{
  class Eventloop;
  typedef std::function<void()> Callback;
  class Channel {
    public:
      Channel(Eventloop *loop, int fd): loop(loop), fd(fd) {}

      void handle_event();
      void set_read_callback(Callback &cb) { read_callback = cb; }
      void set_write_callback(Callback &cb) { write_callback = cb; }
      void set_error_callback(Callback &cb) { error_callback = cb; }
      void set_revents(int revents) { this->revents = revents; }
      int get_events() { return events; }

    private:
      Eventloop* loop;
      const int fd;

      int events;
      int revents;
      Callback read_callback;
      Callback write_callback;
      Callback error_callback
  }
} // namespace SS
#endif