#ifndef ARA_COM_IPC_SOCKET_H_
#define ARA_COM_IPC_SOCKET_H_

#include "Isocket.h"

namespace ara {
namespace com {
namespace ipc {

class Socket : public ISocket
{
public:
    Socket() {}
    ~Socket() override {}

    int socket(int domain, int type, int protocol) const noexcept override;
    int close(int fd) const noexcept override;
    int remove(char const* path) const noexcept override;
    int bind(int fd, const sockaddr* addr, socklen_t len) const noexcept override;
    int listen(int fd, int backlog) const noexcept override;
    int accept(int fd, sockaddr* addr, socklen_t* len) const noexcept override;
    int connect(int fd, sockaddr* addr, socklen_t len) const noexcept override;
};

}
}
}

#endif  // !ARA_COM_IPC_SOCKET_H_