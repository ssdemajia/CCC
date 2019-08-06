#include "Channel.h"

using namespace SS;

void Channel::handle_event() {
  if (events & POLL_ERR) {
    std::cerr << "channel::handle_event() error" << std::endl;
  }
  //Todo
}
