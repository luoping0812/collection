#ifndef SOCKET_H
#define SOCKET_H


#include "Noncopyable.h"
#include "Address.h"

#include <memory>
#include <string>


namespace cpp
{

namespace net
{

class Socket : Noncopyable
{
public:
    using ptr = std::shared_ptr<Socket>;

    static int createSocket(int family, int type, int protocol);

    explicit Socket(int family, int type, int protocol);
    bool init();
    bool init(int sock);
    bool bind(const IPAddress::ptr ptrAddr);
    bool listen(int backlog = SOMAXCONN);
    bool connect(const IPAddress::ptr ptrAddr);
    Socket::ptr accept(IPAddress::ptr& ptrAddr);
    bool close();

    ssize_t read(void *buf, size_t count);
    ssize_t write(const void *buf, size_t count);
    ssize_t send(const void* buf, size_t len, int flags = 0);
    ssize_t sendTo(const void* buf, size_t len, const IPAddress::ptr ptrAddr, int flags = 0);
    ssize_t recv(void* buf, size_t len, int flags = 0);
    ssize_t recvFrom(void* buf, size_t len, IPAddress::ptr& ptrAddr, int flags = 0);

    bool setOption(int level, int option, const void* result, socklen_t len);
    bool getOption(int level, int option, void* result, socklen_t* len);

    bool setNonBlocking();

    IPAddress::ptr getLocalAddress();
    IPAddress::ptr getPeerAddress();

    int getFamily() { return m_family; }
    int getType() { return m_type; }
    int getProtocol() { return m_protocol; }
    int getSocket() { return m_sock; }

private:
    int m_family;
    int m_type;
    int m_protocol;
    int m_sock;
};
    
} // namespace net

    
} // namespace cpp


#endif