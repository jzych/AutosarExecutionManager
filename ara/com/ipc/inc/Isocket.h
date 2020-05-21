#ifndef ARA_COM_IPC_ISOCKET_H_
#define ARA_COM_IPC_ISOCKET_H_

using socklen_t = unsigned int;
struct sockaddr;

namespace ara {
namespace com {
namespace ipc {

class ISocket
{
public:
    virtual ~ISocket() {}

    virtual int socket(int, int, int) const = 0;
    virtual int close(int) const = 0;
    virtual int remove(char const*) const = 0;
    virtual int bind(int, const sockaddr*, socklen_t) const = 0;
    virtual int listen(int, int) const = 0;
    virtual int accept(int, sockaddr*, socklen_t*) const = 0;
    virtual int connect(int, sockaddr*, socklen_t) const= 0;
};

}
}
}

#endif // !ARA_COM_IPC_ISOCKET_H_