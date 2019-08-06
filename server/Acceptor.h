#ifndef ACCEPTOR_H
#define ACCEPTOR_H
#include <string>
#include "Eventloop.h"

namespace SS
{
  class Acceptor {
    public:
      Acceptor(Eventloop* loop, const std::string addr);
    
    private:
      Eventloop* loop;
  };
} // namespace SS

#endif