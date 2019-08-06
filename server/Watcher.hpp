#ifndef WATCHER_HPP
#define WATCHER_HPP

#include <vector>

namespace SS {
  class Channel;

  class Watcher {
    public:
      Watcher(Eventloop* loop);
      void poll(int timeout);
      void update_channel(Channel* c);

    private:
      std::vector<pollfd> pollfds;
      std::map<int, Channel*> channel_map; 
  }

  void Watcher::poll(int timeout) {
    int events_num = ::poll(&*pollfds.begin(), pollfds.size(), timeout);
    //使用全局作用域里的poll函数
    if (events_num > 0) {  // 准备就绪的事件
      
    } else if (events_num == 0) {
      std::cout << "没事发生" << std::endl;
    } else {
      std::cerr << "Watcher::poll发生错误" << std::endl;
    }
  }
}
