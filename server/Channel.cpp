#include "Channel.h"

#include <poll.h>
#include <string.h>

#include <iostream>

#include "Eventloop.h"

using namespace SS;
const int Channel::IgnoreEvent = 0;
const int Channel::ReadEvent = POLLIN | POLLPRI;
const int Channel::WriteEvent = POLLOUT;

void Channel::handle_event() {
  if (revents & POLLERR) {
    std::cerr << "channel::handle_event() error:" << strerror(errno) << std::endl;
    if (error_callback) error_callback();
  }
  if (revents & (POLLIN | POLLPRI | POLLHUP)) {
    std::cout << "channel::handle_event() read" << std::endl;
    if (read_callback) read_callback();
  }
  if (revents & POLLOUT) {
    std::cout << "channel::handle_event() write" << std::endl;
    if (write_callback) write_callback();
  }
}

void Channel::update(int flag) {
  events |= flag;
  loop->update_channel(this);
}