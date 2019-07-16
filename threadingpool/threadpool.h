#ifndef THREAD_POOL
#define THREAD_POOL

#include "task.h"
#include <pthread.h>
#include <iostream>
#include <vector>
#include <queue>

class ThreadPool {
public:
  static ThreadPool* create_pool(int num = 10); // 默认参数不能同时在函数定义和函数声明
  void add_task(Task* t);
  Task* get_task();
  bool alive();
private:
  ThreadPool(int num);
  static void* ThreadFunc(void*);

  bool is_running;  // 此时线程池正在运行
  std::vector<pthread_t> threads;
  std::queue<Task*> task_queue;
  pthread_mutex_t lock; // 互斥锁保护条件量
  pthread_cond_t cond; // 条件变量
};
#endif