#include "Thread.h"

using namespace SS;

pid_t Thread::tid() {
#ifdef SYS_gettid
  pid_t id = syscall(SYS_gettid);
#else
#error "SYS_gettid unavailable on this system"
#endif
  return id;
}