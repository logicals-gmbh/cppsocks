#ifndef SOCKS_HTTP_STATES_HPP
#define SOCKS_HTTP_STATES_HPP

#include <socks_http_handler.hpp>
#include <socks_ws_handler.hpp>

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>

#include <cstring>
#include <stdexcept>

namespace Socks
{
namespace Network
{
namespace Http
{

class HttpState;

using HttpStateInstance = std::shared_ptr<HttpState>;

class HttpStateContext
{
  public:
  virtual ~HttpStateContext() = default;

  virtual void setNextState(HttpStateInstance nextState) = 0;
  virtual RequestInfo const& requestInfo() = 0;
  virtual HttpHandlerFactory& httpHandlerFactory() = 0;
  virtual WsHandlerFactory& wsHandlerFactory() = 0;
  virtual Socks::Network::Tcp::Connection* tcpConnection() = 0;
};

class HttpState
{
  public:
  explicit HttpState(HttpStateContext* fsm) : fsm{fsm} {}
  virtual ~HttpState() = default;

  virtual void onEnter() = 0;
  virtual void onReceive(Byte const* buf, std::size_t len) = 0;
  virtual void onDisconnect() {}

  protected:
  HttpStateContext* fsm;
};

class HttpGetState final : public HttpState
{
  public:
  explicit HttpGetState(HttpStateContext* fsm) : HttpState{fsm}, handler{fsm->httpHandlerFactory().createHttpHandler()} {}
  void onEnter() override;
  void onReceive(Byte const* buf, std::size_t len) override;

  private:
  HttpHandlerInstance handler;
};

class HttpInitState final : public HttpState
{
  public:
  explicit HttpInitState(HttpStateContext* fsm, RequestInfo& requestInfo)
      : HttpState{fsm}, requestInfo(requestInfo), recvBuf{{0}}, numRecv(0)
  {
  }
  virtual void onEnter() override { throw std::runtime_error("HttpInitState::onEnter() must not be called."); }
  void onReceive(Byte const* buf, std::size_t len) override;

  private:
  RequestInfo& requestInfo;
  std::array<char, 4096> recvBuf;
  std::size_t numRecv;
};

} // namespace Http
} // namespace Network
} // namespace Socks

#if SOCKS_HEADER_ONLY == 1
#include <socks_http_states.cpp>
#endif /* SOCKS_HEADER_ONLY */

#endif /* SOCKS_HTTP_STATES_HPP */
