#include "Channel.h"

#include <poll.h>

#include <iostream>

#include "Eventloop.h"

using namespace SS;
const int Channel::IgnoreEvent = 0;
const int Channel::ReadEvent = POLLIN | POLLPRI;
const int Channel::WriteEvent = POLLOUT;

void Channel::handle_event() {
  if (events & POLLERR) {
    std::cerr << "channel::handle_event() error" << std::endl;
    if (error_callback) error_callback();
  }
  if (events & (POLLIN | POLLPRI | POLLHUP)) {
    if (read_callback) read_callback();
  }
  if (events & POLLOUT) {
    if (write_callback) write_callback();
  }
}

void Channel::update(int flag) {
  events |= flag;
  loop->update_channel(this);
}