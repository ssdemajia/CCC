#ifndef EVENTLOOP_H
#define EVENTLOOP_H

#include <vector>
#include <memory>

#include "Thread.h"
#include "Channel.h"
#include "Watcher.h"

namespace SS
{
  class Eventloop {
    public:
      Eventloop(int timeout=1000);
      ~Eventloop();

      static Eventloop* get_current_loop();
      void quit();
      void loop();
      void update_channel(Channel* ch);
    private:
      const pid_t thread_id;
      bool looping;
      int timeout;

      std::shared_ptr<Watcher> watcher;
      std::vector<Channel*> active_channels;
  };
} // namespace SS
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
#endif