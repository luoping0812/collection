#include "Socket.h"
#include "Macro.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>

namespace cpp
{

namespace net
{

Socket::Socket(int family, int type, int protocol)
    : m_family(family)
    , m_type(type)
    , m_protocol(protocol)
{

    LOG_INFO() << "Socket::Socket()";

}

Socket::~Socket()
{
    if (-1 != m_sock)
    {
        close();
    }
    LOG_INFO() << "Socket::~Socket()";
}

int Socket::createSocket(int family, int type, int protocol)
{
    int ret = ::socket(family, type, protocol);
    handle_error(ret > 0, ret, ret);
}

bool Socket::init()
{
    handle_error((m_sock = ::socket(m_family, m_type, m_protocol)) > 0, true, false); 
}

bool Socket::init(int sock)
{
    handle_error((m_sock = sock) > 0, true, false); 
}

bool Socket::bind(const IPAddress::ptr ptrAddr)
{
    handle_error(0 == ::bind(m_sock, ptrAddr->getSockAddr(), ptrAddr->getSockAddrLen()), true, false);
}

bool Socket::listen(int backlog)
{
    handle_error(0 == ::listen(m_sock, backlog), true, false);
}

bool Socket::connect(const IPAddress::ptr ptrAddr)
{
    handle_error(0 == ::connect(m_sock, ptrAddr->getSockAddr(), ptrAddr->getSockAddrLen()), true, false);
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

    if (clientSock > 0)
    {
        Socket::ptr sock = std::make_shared<Socket>(m_family, m_type, m_protocol);
        handle_error(sock->init(clientSock), sock, nullptr);
    }
    return nullptr;
}

bool Socket::close()
{
    handle_error(0 == ::close(m_sock), true, false);
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
    handle_error(0 == setsockopt(m_sock, level, option, optval, len), true, false);
}

bool Socket::getOption(int level, int option, void* optval, socklen_t* len)
{
    handle_error(0 == getsockopt(m_sock, level, option, optval, len), true, false);
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
    handle_error(0 == getsockname(m_sock, addr->getSockAddr(), &addrlen), addr, nullptr);
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
    handle_error(0 == getpeername(m_sock, addr->getSockAddr(), &addrlen), addr, nullptr);
}


} // namespace net

    
} // namespace cpp
