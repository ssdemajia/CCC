#ifndef THREAD_HPP
#define THREAD_HPP

#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>

#include <string>
#include <functional>

namespace SS
{
  class Thread{
    public:
      typedef std::function<void()> ThreadFunc;
      Thread(ThreadFunc, const std::string& name = std::string());
      static pid_t tid();
  };
} // namespace SS
#endif