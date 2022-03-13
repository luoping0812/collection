#include "Socket.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

namespace cpp
{

namespace net
{

int Socket::createSocket(int family, int type, int protocol)
{
    return ::socket(family, type, protocol);
}
   
bool Socket::bind(const IPAddress::ptr ptrAddr)
{
    int ret = ::bind(m_sock, ptrAddr->getSockAddr(), ptrAddr->getSockAddrLen());
    if (-1 == ret)
    {
        return false;
    }
    return true;
}

bool Socket::listen(int backlog)
{
    int ret = ::listen(m_sock, backlog);
    if (-1 == ret)
    {
        return false;
    }
    return true;

}

bool Socket::connect(const IPAddress::ptr ptrAddr)
{
    int ret = ::connect(m_sock, ptrAddr->getSockAddr(), ptrAddr->getSockAddrLen());
    if (-1 == ret)
    {
        return false;
    }
    return true;
}

Socket::ptr Socket::accept(IPAddress::ptr ptrAddr)
{
    int clientSock = -1;
    if (AF_INET == ptrAddr->getFamily())
    {
        struct sockaddr_in addr;
        socklen_t len;
        clientSock = ::accept(m_sock, ptrAddr->getSockAddr(), &len);
        ptrAddr = IPAddress::create((struct sockaddr*)(&addr));
    }
    else if (AF_INET6 == ptrAddr->getFamily())
    {
        struct sockaddr_in6 addr;
        socklen_t len;
        clientSock = ::accept(m_sock, (struct sockaddr*)&addr, &len);
        ptrAddr = IPAddress::create((struct sockaddr*)(&addr));
    }

    if (clientSock > 0)
    {
        return std::make_shared<Socket>(clientSock);
    }

    return nullptr;
}

bool Socket::close()
{
    int ret = ::close(m_sock);
    if (-1 == ret)
    {
        return false;
    }

    return true;
}

ssize_t Socket::read(void *buf, size_t count)
{
    return ::read(m_sock, buf, count);
}

ssize_t Socket::write(const void *buf, size_t count)
{
    return ::write(m_sock, buf, count);
}

ssize_t Socket::send(const void* buf, size_t len, int flags)
{
    return ::send(m_sock, buf, len, flags);
}

ssize_t Socket::sendTo(const void* buf, size_t len, const IPAddress::ptr ptrAddr, int flags)
{
    return ::sendto(m_sock, buf, len, flags, ptrAddr->getSockAddr(), ptrAddr->getSockAddrLen());
}

ssize_t Socket::recv(void* buf, size_t len, int flags)
{
    return ::recv(m_sock, buf, len, flags);
}

ssize_t Socket::recvFrom(void* buf, size_t len, IPAddress::ptr ptrAddr, int flags)
{
    ssize_t ret = 0;
    if (AF_INET == ptrAddr->getFamily())
    {
        struct sockaddr_in addr;
        socklen_t len;
        ret = ::recvfrom(m_sock, buf, len, flags, (struct sockaddr*)(&addr), &len);
        ptrAddr = IPAddress::create((struct sockaddr*)(&addr));
    }
    else if (AF_INET6 == ptrAddr->getFamily())
    {
        struct sockaddr_in6 addr;
        socklen_t len;
        ret = ::recvfrom(m_sock, buf, len, flags, (struct sockaddr*)(&addr), &len);
        ptrAddr = IPAddress::create((struct sockaddr*)(&addr));
    }

    return ret;
}


} // namespace net

    
} // namespace cpp
