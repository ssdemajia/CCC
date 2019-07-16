#if !defined(TASK)
#define TASK

class Task {
public:
  virtual void run() = 0;
  void set_args(void* args) {
    this->args = args;
  }
protected:
  void * args;
};

#endif // TASK
