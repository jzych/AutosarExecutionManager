#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include "socket.h"

namespace ara {
namespace com {
namespace ipc {

int Socket::socket(int domain, int type, int protocol) const noexcept
{
    return ::socket(domain, type, protocol);
}

int Socket::close(int fd) const noexcept
{
    return ::close(fd);
}

int Socket::remove(char const* path) const noexcept
{
    return ::remove(path);
}

int Socket::bind(int fd, const sockaddr* addr, socklen_t len) const noexcept
{
    return ::bind(fd, addr, len);
}

int Socket::listen(int fd, int backlog) const noexcept
{
    return ::listen(fd, backlog);
}

int Socket::accept(int fd, sockaddr* addr, socklen_t* len) const noexcept
{
    return ::accept(fd, addr, len);
}

int Socket::connect(int fd, sockaddr* addr, socklen_t len) const noexcept
{
    return ::connect(fd, addr, len);
}

}  // namespace ipc
}  // namespace com
}  // namespace ara