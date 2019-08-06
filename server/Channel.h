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
      bool ignore_event() { return events == IgnoreEvent; };
      void set_read_callback(Callback cb) { read_callback = cb; }
      void set_write_callback(Callback cb) { write_callback = cb; }
      void set_error_callback(Callback cb) { error_callback = cb; }
      void set_revents(int revents) { this->revents = revents; }
      int get_events() { return events; }
      int get_index() { return index; }
      int get_fd() { return fd; }
      void set_index(int index) { this->index = index; }

      void enable_read() { update(ReadEvent); }
      void enable_write() { update(WriteEvent); }

    private:
      static const int IgnoreEvent;
      static const int ReadEvent; 
      static const int WriteEvent;

      void update(int flag);

      Eventloop* loop;
      const int fd;
      int index = -1; // 在pollfd数组中的索引
      short int events = 0;
      short int revents = 0;

      Callback read_callback;
      Callback write_callback;
      Callback error_callback;
  };
} // namespace SS
#endif