#include <thread>
/*
   这个类用于确保程序出现异常时，其他线程还能被join回收内存
*/
class ThreadGuard {
  public:
    explicit ThreadGuard(std::thread& _t): t(_t) {}
    ~ThreadGuard() {
      if (t.joinable()) t.join();
    }
    ThreadGuard(ThreadGuard const&) = delete;
    ThreadGuard& operator=(ThreadGuard const&) = delete;
  private:
    std::thread& t;
};