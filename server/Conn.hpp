#ifndef CONN_H
#define CONN_H
/*
这个文件主要定义connection这个类，每个connection表示一个连接
 */
namespace SS
{
class Connection
{
public:
  void send(void *buf, size_t len);
}
} // namespace SS

#endif