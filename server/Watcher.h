#ifndef WATCHER_HPP
#define WATCHER_HPP

#include <assert.h>
#include <poll.h>

#include <vector>
#include <iostream>
#include <map>

#include "Channel.h"


namespace SS {
  class Eventloop;

  class Watcher {
    public:
      Watcher(Eventloop* loop);
      void poll(int timeout, std::vector<Channel*> &);
      void update_channel(Channel* ch);
      
    private:
      void fill_active_channel(int events_num, std::vector<Channel*> &active_channels);

      Eventloop* loop;
      std::vector<struct pollfd> pollfds;
      std::map<int, Channel*> channel_map; 
  };
}

#endif