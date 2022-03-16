#include "Socket.h"
#include "Macro.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>

namespace net
{

Socket::Socket(int family, int type, int protocol)
    : m_family(family)
    , m_type(type)
    , m_protocol(protocol)
{

    LOG_DEBUG();

}

Socket::~Socket()
{
    if (-1 != m_sock)
    {
        close();
    }
    LOG_DEBUG();
}

int Socket::createSocket(int family, int type, int protocol)
{
    int ret = ::socket(family, type, protocol);
    handle_error();
    return ret;
}

bool Socket::init()
{
    m_sock = ::socket(m_family, m_type, m_protocol);
    if (m_sock < 0)
    {
        handle_error();
        return false;
    }
    return true;
}

bool Socket::init(int sock)
{
    m_sock = sock; 
    if (m_sock < 0)
    {
        handle_error();
        return false;
    }
    return true;
}

bool Socket::bind(const IPAddress::ptr ptrAddr)
{
    int ret = ::bind(m_sock, ptrAddr->getSockAddr(), ptrAddr->getSockAddrLen());
    if (-1 == ret)
    {
        handle_error();
        return false;
    }
    return true;
}

bool Socket::listen(int backlog)
{
    int ret = ::listen(m_sock, backlog);
    if (-1 == ret)
    {
        handle_error();
        return false;
    }
    return true;

}

bool Socket::connect(const IPAddress::ptr ptrAddr)
{
    int ret = ::connect(m_sock, ptrAddr->getSockAddr(), ptrAddr->getSockAddrLen());
    if (-1 == ret)
    {
        handle_error();
        return false;
    }
    return true;

}

Socket::ptr Socket::accept(IPAddress::ptr& ptrAddr)
{
    int clientSock = -1;
    if (AF_INET == getFamily())
    {
        struct sockaddr_in addr;
        socklen_t len;
        clientSock = ::accept(m_sock, (struct sockaddr*)&addr, &len);
        ptrAddr = std::make_shared<IPv4Address>(addr);
    }
    else if (AF_INET6 == getFamily())
    {
        struct sockaddr_in6 addr;
        socklen_t len;
        clientSock = ::accept(m_sock, (struct sockaddr*)&addr, &len);
        ptrAddr = std::make_shared<IPv6Address>(addr);
    }

    Socket::ptr sock = std::make_shared<Socket>(m_family, m_type, m_protocol);
    if (sock->init(clientSock))
    {
        return sock;
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

ssize_t Socket::recvFrom(void* buf, size_t len, IPAddress::ptr& ptrAddr, int flags)
{
    ssize_t ret = 0;
    if (AF_INET == getFamily())
    {
        struct sockaddr_in addr;
        socklen_t len;
        ret = ::recvfrom(m_sock, buf, len, flags, (struct sockaddr*)(&addr), &len);
        ptrAddr = std::make_shared<IPv4Address>(addr);
    }
    else if (AF_INET6 == getFamily())
    {
        struct sockaddr_in6 addr;
        socklen_t len;
        ret = ::recvfrom(m_sock, buf, len, flags, (struct sockaddr*)(&addr), &len);
        ptrAddr = std::make_shared<IPv6Address>(addr);
    }

    return ret;
}

bool Socket::setOption(int level, int option, const void* optval, socklen_t len)
{
    int ret = setsockopt(m_sock, level, option, optval, len);
    if (-1 == ret)
    {
        handle_error();
        return false;
    }
    return true;

}

bool Socket::getOption(int level, int option, void* optval, socklen_t* len)
{
    int ret = getsockopt(m_sock, level, option, optval, len);
    if (-1 == ret)
    {
        handle_error();
        return false;
    }
    return true;

}

bool Socket::setNonBlocking()
{
    int flags = ::fcntl(m_sock, F_GETFL, 0);
    flags |= O_NONBLOCK;
    int ret = ::fcntl(m_sock, F_SETFL, flags);
    return ret;
}

IPAddress::ptr Socket::getLocalAddress()
{
    IPAddress::ptr addr;
    switch (getFamily())
    {
    case AF_INET:
        addr = std::make_shared<IPv4Address>();
        break;
    case AF_INET6:
        addr = std::make_shared<IPv6Address>();
        break;
    default:
        break;
    }
    socklen_t addrlen = addr->getSockAddrLen();
    int ret = getsockname(m_sock, addr->getSockAddr(), &addrlen);
    if (-1 == ret)
    {
        handle_error();
        return nullptr;
    }
    return addr;
}

IPAddress::ptr Socket::getPeerAddress()
{
    IPAddress::ptr addr;
    switch (getFamily())
    {
    case AF_INET:
        addr = std::make_shared<IPv4Address>();
        break;
    case AF_INET6:
        addr = std::make_shared<IPv6Address>();
        break;
    default:
        break;
    }
    socklen_t addrlen = addr->getSockAddrLen();
    int ret = getpeername(m_sock, addr->getSockAddr(), &addrlen);
    if (-1 == ret)
    {
        handle_error();
        return nullptr;
    }
    return addr;

}


} // namespace net