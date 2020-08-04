#ifndef SOCKS_TCP_TYPES_H
#define SOCKS_TCP_TYPES_H

#include <array>
#include <cstdint>

namespace Socks
{
namespace Network
{
namespace Tcp
{
constexpr std::size_t const MAX_SIZE = 1024;

using Byte = std::uint8_t;
using MsgBuf = std::array<Byte, MAX_SIZE>;
} // namespace Tcp
} // namespace Network
} // namespace Socks

#endif // SOCKS_TCP_TYPES_H
