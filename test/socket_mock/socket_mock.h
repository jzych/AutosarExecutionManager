#ifndef UX_SOCKET_IMPL_MOCK_H_
#define UX_SOCKET_IMPL_MOCK_H_

#include <gmock/gmock.h>
#include "Isocket.h"

class SocketMock : public ara::com::ipc::ISocket
{
public:
    MOCK_CONST_METHOD3(socket, int(int domain, int type, int protocol));
    MOCK_CONST_METHOD1(close, int(int fd));
    MOCK_CONST_METHOD1(remove, int(char const* path));
    MOCK_CONST_METHOD3(bind, int(int fd, const sockaddr* addr, socklen_t len));
    MOCK_CONST_METHOD2(listen, int(int fd, int backlog));
    MOCK_CONST_METHOD3(accept, int(int fd, sockaddr* addr, socklen_t* len));
    MOCK_CONST_METHOD3(connect, int(int fd, sockaddr* addr, socklen_t len));
};

#endif  // !UX_SOCKET_IMPL_MOCK_H_