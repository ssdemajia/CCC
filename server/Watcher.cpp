#include "Watcher.h"

using namespace SS;

Watcher::Watcher(Eventloop* loop): loop(loop) {}

void Watcher::poll(int timeout, std::vector<Channel*> &active_channels) {
    int events_num = ::poll(&*pollfds.begin(), pollfds.size(), timeout);
    //使用全局作用域里的poll函数
    if (events_num > 0) {  // 准备就绪的事件
      fill_active_channel(events_num, active_channels);  
    } else if (events_num == 0) {
      std::cout << "没事发生" << std::endl;
    } else {
      std::cerr << "Watcher::poll发生错误" << std::endl;
    }
  }

  void Watcher::fill_active_channel(int events_num, std::vector<Channel*> &active_channels) {
    for (auto iter = pollfds.cbegin(); iter != pollfds.end() && events_num > 0; iter++) {
      if (iter->revents > 0) {
        std::map<int, Channel*>::const_iterator ch_iter = channel_map.find(iter->fd);
        assert(ch_iter != channel_map.end());
        Channel* ch = ch_iter->second;
        ch->set_revents(iter->revents);
        active_channels.push_back(ch);
        --events_num;
      }
    }
  }

  void Watcher::update_channel(Channel* ch) {
    if (ch->get_index() == -1) {  //当前channel才生成, 需要插入进去
      struct pollfd pfd;
      pfd.fd = ch->get_fd();
      pfd.events = ch->get_events();
      pfd.revents = 0;
      pollfds.push_back(pfd);
      int index = pollfds.size()-1;
      ch->set_index(index);
      channel_map[pfd.fd] = ch;
    } else {
      int index = ch->get_index();
      assert(index >= 0 && index < pollfds.size());
      struct pollfd &pfd = pollfds[index];
      assert(pfd.fd == ch->get_fd());
      pfd.events = ch->get_events();
      pfd.revents = 0;
      if (ch->ignore_event()) {
        pfd.fd = -1;
      }
    }
  }