#include "threadpool.h"

ThreadPool* ThreadPool::create_pool(int num) {
  return new ThreadPool(num); 
}

ThreadPool::ThreadPool(int num) {
  is_running = true;
  lock = PTHREAD_MUTEX_INITIALIZER;
  cond = PTHREAD_COND_INITIALIZER;

  for (int i = 0; i < num; i++) {
    pthread_t id;
    pthread_create(&id, NULL, ThreadFunc, this);
  }
}

void ThreadPool::add_task(Task* t) {
  pthread_mutex_lock(&lock); // 在持有互斥锁期间
  task_queue.push(t);
  pthread_cond_signal(&cond); // 条件变量通知等待线程
  pthread_mutex_unlock(&lock); // 互斥锁解锁
}

Task* ThreadPool::get_task() {
  pthread_mutex_lock(&lock);

  while (task_queue.size() == 0)  // 当task_queue的长度为0时，使用pthread_cond_wait释放lock，进入睡眠
    pthread_cond_wait(&cond, &lock); 
  Task* t = task_queue.front();
  task_queue.pop();

  pthread_mutex_unlock(&lock);
  return t;
}

void* ThreadPool::ThreadFunc(void* arg) {
  // 线程执行的函数
  ThreadPool* pool = (ThreadPool*) arg;
  while(pool->is_running) {
    Task* task = pool->get_task();
    if (!task) break;
    std::cout << pthread_self() << "get a job!" << std::endl;
    task->run();
  }
  return nullptr;
}

bool ThreadPool::alive() { return is_running; }