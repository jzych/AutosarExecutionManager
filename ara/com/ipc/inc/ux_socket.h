#ifndef ARA_COM_IPC_UX_SOCKET_H_
#define ARA_COM_IPC_UX_SOCKET_H_

#include <cstdint>
#include <memory>

struct sockaddr;
struct sockaddr_un;

namespace ara {
namespace com {
namespace ipc {

using socklen_t = uint32_t;
class ISocket;
class Socket;

class UxSocket
{
public:
    explicit UxSocket(std::unique_ptr<ISocket>&& sock = nullptr);
    ~UxSocket();

    void bind(char const* path);
    void listen(int backlog = 0);
    int accept(sockaddr* sock_addr = nullptr, socklen_t* sock_len = nullptr);
    void connect(char const* path);
    int get_socket_fd() const noexcept;

private:
    void configure_sockaddr_un(sockaddr_un& addr, char const* path) const noexcept;

private:
    int sock_fd_;
    std::unique_ptr<ISocket> sock_impl_;
};

}
}
}

#endif  // !ARA_COM_IPC_UX_SOCKET_H_