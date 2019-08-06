#include "Eventloop.h"

#include <iostream>

using namespace SS;

 __thread Eventloop* local_loop = NULL;  // 当前线程local的eventloop

Eventloop::Eventloop(int timeout) : timeout(timeout), looping(false), thread_id(Thread::tid()), watcher(new Watcher(this)) {
  if (local_loop) {
    std::cout << "有另一个loop运行在这个线程中:" << thread_id << std::endl; 
  } else {
    local_loop = this;
  }
}

Eventloop* Eventloop::get_current_loop() {
  return local_loop;
}
void Eventloop::loop() {
  looping = true;
  
  while (looping) {
    active_channels.clear();
    watcher->poll(timeout, active_channels);
    for (auto channel : active_channels) {
      channel->handle_event();
    }
  }
}

void Eventloop::quit() {
  std::cout << "Eventlopp quit." << std::endl;
  looping = false;
}

void Eventloop::update_channel(Channel* ch) {
  watcher->update_channel(ch);
}