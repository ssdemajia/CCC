#include <stdio.h>
#include <memory>
#include <iostream>
namespace SS
{
class ErrorMsg
{
public:
  ErrorMsg(std::ostream &io = std::cout) : io(io) {}
  template <typename S>
  void print(S str)
  {
    io << str << "\n";
  }

  template <typename S, typename... Args>
  void print(S str, const Args... rest)
  {
    io << str << " ";
    print(rest...);
  }

private:
  std::ostream &io;
};
} // namespace SS