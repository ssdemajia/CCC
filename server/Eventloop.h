#ifndef EVENTLOOP_H
#define EVENTLOOP_H

#include <iostream> 

namespace SS
{
  __thread Eventloop* local_loop = nullptr;  // 当前线程local的eventloop

  class Eventloop {
    public:
      Eventloop();
      ~Eventloop();

      static EventLoop* get_current_loop() { return local_loop; };
      start();
      finish();
    private:
      const pid_t thread_id;
      bool looping;
  }
} // namespace SS
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
#endif