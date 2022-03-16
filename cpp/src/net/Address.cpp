#include "Address.h"
#include "System.h"
#include "LexicalCast.h"
#include "Endian.h"
#include "Log.h"

#include <arpa/inet.h>

namespace net
{

IPAddress::ptr IPAddress::create(struct sockaddr* addr)
{
    if (nullptr == addr)
    {
        return nullptr;
    }

    switch (addr->sa_family)
    {
    case AF_INET: 
        return std::make_shared<IPv4Address>(*(struct sockaddr_in*)(addr));
        break;
    case AF_INET6: 
        return std::make_shared<IPv6Address>(*(struct sockaddr_in6*)(addr));
        break;
    default:
        break;
    }

    return nullptr;
}

int IPAddress::getFamily() const
{
    return getSockAddr()->sa_family;
}

IPv4Address::IPv4Address()
{
    utils::memZero(&m_addr, sizeof(m_addr));
    m_addr.sin_family = AF_INET;
    LOG_DEBUG();
}

IPv4Address::IPv4Address(const struct sockaddr_in& addr)
{
    m_addr = addr;
    LOG_DEBUG();
}

IPv4Address::IPv4Address(const std::string& strIp, const uint16_t nPort)
{
    utils::memZero(&m_addr, sizeof(m_addr));
    m_addr.sin_family = AF_INET;
    ::inet_pton(AF_INET, strIp.c_str(), &(m_addr.sin_addr));
    m_addr.sin_port = Endian::hton(nPort);
    LOG_DEBUG();
}

IPv4Address::IPv4Address(const uint16_t nPort, bool bLoopBackOnly)
{
    utils::memZero(&m_addr, sizeof(m_addr));
    m_addr.sin_family = AF_INET;
    m_addr.sin_addr.s_addr = Endian::hton(bLoopBackOnly ? INADDR_LOOPBACK : INADDR_ANY);
    m_addr.sin_port = Endian::hton(nPort);
    LOG_DEBUG();
}

IPv4Address::~IPv4Address()
{
    LOG_DEBUG();
}

std::string IPv4Address::getIp() const
{
    char buf[16];
    return ::inet_ntop(AF_INET, &m_addr.sin_addr, buf, (socklen_t)sizeof(buf));
}

uint16_t IPv4Address::getPort() const
{
    return Endian::ntoh(m_addr.sin_port);
}

std::string IPv4Address::getIpPort() const
{
    return getIp() + ":" + lexical_cast<std::string>(getPort());
}

struct sockaddr* IPv4Address::getSockAddr()
{
    return (struct sockaddr*)&m_addr;
}

const struct sockaddr* IPv4Address::getSockAddr() const
{
    return (const struct sockaddr*)&m_addr;
}

socklen_t IPv4Address::getSockAddrLen() const
{
    return (socklen_t)(sizeof(m_addr));
}
 
IPv6Address::IPv6Address(const struct sockaddr_in6& addr)
{
    m_addr = addr;
    LOG_DEBUG();
}

IPv6Address::IPv6Address()
{
    utils::memZero(&m_addr, sizeof(m_addr));
    m_addr.sin6_family = AF_INET6;
    LOG_DEBUG();
}

IPv6Address::IPv6Address(const std::string& strIp, const uint16_t nPort)
{
    utils::memZero(&m_addr, sizeof(m_addr));
    m_addr.sin6_family = AF_INET6;
    ::inet_pton(AF_INET6, strIp.c_str(), &(m_addr.sin6_addr));
    m_addr.sin6_port = Endian::hton(nPort);
    LOG_DEBUG();
}

IPv6Address::IPv6Address(const uint16_t nPort, bool bLoopBackOnly)
{
    utils::memZero(&m_addr, sizeof(m_addr));
    m_addr.sin6_family = AF_INET6;
    m_addr.sin6_addr = bLoopBackOnly ? in6addr_loopback : in6addr_any;
    m_addr.sin6_port = Endian::hton(nPort);
    LOG_DEBUG();
}

IPv6Address::~IPv6Address()
{
    LOG_DEBUG();
}

std::string IPv6Address::getIp() const
{
    char buf[64];
    return ::inet_ntop(AF_INET6, &m_addr.sin6_addr, buf, (socklen_t)sizeof(buf));
}

uint16_t IPv6Address::getPort() const
{
    return Endian::ntoh(m_addr.sin6_port);
}

std::string IPv6Address::getIpPort() const
{
    return getIp() + "-" + lexical_cast<std::string>(getPort());
}

struct sockaddr* IPv6Address::getSockAddr()
{
    return (struct sockaddr*)&m_addr;
}

const struct sockaddr* IPv6Address::getSockAddr() const
{
    return (const struct sockaddr*)&m_addr;
}
 
socklen_t IPv6Address::getSockAddrLen() const
{
    return (socklen_t)(sizeof(m_addr));
}   

} // namespace net

