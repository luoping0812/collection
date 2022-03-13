#pragma once

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

    explicit Socket(int sock)
        : m_sock(sock) {}

    static int createSocket(int family, int type, int protocol);

    bool bind(const IPAddress::ptr ptrAddr);
    bool listen(int backlog = SOMAXCONN);
    bool connect(const IPAddress::ptr ptrAddr);
    Socket::ptr accept(IPAddress::ptr ptrAddr);
    bool close();

    ssize_t read(void *buf, size_t count);
    ssize_t write(const void *buf, size_t count);
    ssize_t send(const void* buf, size_t len, int flags = 0);
    ssize_t sendTo(const void* buf, size_t len, const IPAddress::ptr ptrAddr, int flags = 0);
    ssize_t recv(void* buf, size_t len, int flags = 0);
    ssize_t recvFrom(void* buf, size_t len, IPAddress::ptr ptrAddr, int flags = 0);

private:
    int m_sock;
};
    
} // namespace net

    
} // namespace cpp
