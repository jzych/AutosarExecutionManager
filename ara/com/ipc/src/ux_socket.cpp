#include "ux_socket.h"

#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include <iostream>

#include "socket.h"

namespace ara {
namespace com {
namespace ipc {

inline void exit_error(char const* msg)
{
    if (msg != nullptr)
        std::cerr << msg << '\n';
    exit(EXIT_FAILURE);
}

UxSocket::UxSocket(std::unique_ptr<ISocket>&& sock) : sock_impl_(std::move(sock))
{
    if (sock_impl_ == nullptr)
        sock_impl_ = std::make_unique<Socket>();

    sock_fd_ = sock_impl_->socket(AF_UNIX, SOCK_STREAM | SOCK_CLOEXEC | SOCK_NONBLOCK, 0);

    if (sock_fd_ == -1) {
        throw std::runtime_error("UxSocket open failure(-1)\n");
    }
}

UxSocket::~UxSocket()
{
    if (sock_impl_->close(sock_fd_) == -1)
        exit_error("UxSocket close() failure(-1)\n");
}

void UxSocket::configure_sockaddr_un(sockaddr_un& addr, char const* path) const noexcept
{
    memset(&addr, 0, sizeof(sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, path, sizeof(sockaddr_un) - 1);
}

void UxSocket::bind(char const* path)
{
    if (sock_impl_->remove(path) == -1 && errno != ENOENT)
        throw std::runtime_error("UxSocket remove() failure(-1)\n");

    struct sockaddr_un addr;
    configure_sockaddr_un(addr, path);

    if (sock_impl_->bind(sock_fd_, (sockaddr*)&addr, sizeof(sockaddr_un)) == -1)
        throw std::runtime_error("UxSocet bind() failure(-1)\n");
}

void UxSocket::listen(int backlog)
{
    if (sock_impl_->listen(sock_fd_, backlog) == -1)
        throw std::runtime_error("UxSocket listen() failure(-1)\n");
}

int UxSocket::accept(sockaddr* sock_addr, socklen_t* sock_len)
{
    int conn_sock = sock_impl_->accept(sock_fd_, sock_addr, sock_len);

    if (conn_sock == -1 && errno != EAGAIN)
        throw std::runtime_error("UxSocket accept() failure(-1)\n");

    return conn_sock;
}

void UxSocket::connect(char const* path)
{
    struct sockaddr_un addr;
    configure_sockaddr_un(addr, path);

    if (sock_impl_->connect(sock_fd_, (sockaddr*)&addr, sizeof(sockaddr_un)) == -1)
        throw std::runtime_error("UxSocket connect()failure(-1)\n");
}

int UxSocket::get_socket_fd() const noexcept
{
    return sock_fd_;
}

}  // namespace ipc
}  // namespace com
}  // namespace ara
