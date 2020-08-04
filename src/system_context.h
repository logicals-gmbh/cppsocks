#ifndef SYSTEM_CONTEXT_H
#define SYSTEM_CONTEXT_H

#include <ws_types.h>

#include <unistd.h>

#include <cstddef>
#include <memory>

namespace WS
{

namespace Network
{

class TcpSocket
{
  public:
  static ssize_t const NUM_EOF;
  static ssize_t const NUM_CONTINUE;

  virtual ~TcpSocket() {}
  virtual ssize_t read(MsgBuf& buf) = 0;
  virtual ssize_t write(void const* buf, std::size_t buflen) = 0;
};

using TcpSocketInstance = std::unique_ptr<TcpSocket>;

class TcpListenSocket
{
  public:
  virtual ~TcpListenSocket() {}
  virtual TcpSocketInstance accept() = 0;
};

using TcpListenSocketInstance = std::unique_ptr<TcpListenSocket>;

class Context
{
  public:
  virtual ~Context() {}
  virtual TcpListenSocketInstance createListenSocket(int port) = 0;
};
} // namespace Network
namespace System
{
void initQuitCondition();
bool quitCondition();
} // namespace System
} // namespace WS

#endif /* SYSTEM_CONTEXT_H */