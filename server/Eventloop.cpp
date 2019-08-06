#include "Eventloop.h"

using namespace SS;

Eventloop::Eventloop() : looping(false), thread_id(Thread::thread_id()){
  if (local_loop) {
    std::cout << "有另一个loop运行在这个线程中:" << thread_id << std::endl; 
  } else {
    local_loop = this;
  }
}

void Eventloop::start() {
  looping = true;
}

