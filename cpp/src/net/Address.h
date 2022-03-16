#ifndef ADDRESS_H
#define ADDRESS_H


#include <memory>
#include <string>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

namespace net
{

class IPAddress
{
public:
    using ptr = std::shared_ptr<IPAddress>;
    virtual ~IPAddress() {}

    static IPAddress::ptr create(struct sockaddr* addr);

    int getFamily() const;
    virtual std::string getIp() const = 0;
    virtual uint16_t getPort() const = 0;
    virtual std::string getIpPort() const = 0;
    virtual struct sockaddr* getSockAddr() = 0;
    virtual const struct sockaddr* getSockAddr() const = 0;
    virtual socklen_t getSockAddrLen() const = 0;
};

class IPv4Address : public IPAddress
{
public:
    using ptr = std::shared_ptr<IPv4Address>;

    explicit IPv4Address();
    explicit IPv4Address(const std::string& strIp, const uint16_t nPort);
    explicit IPv4Address(const uint16_t nPort, bool bLoopBackOnly = false);
    explicit IPv4Address(const struct sockaddr_in& addr);

    ~IPv4Address();

    virtual std::string getIp() const override;
    virtual uint16_t getPort() const override;
    virtual std::string getIpPort() const override;
    virtual struct sockaddr* getSockAddr();
    virtual const struct sockaddr* getSockAddr() const override;
    virtual socklen_t getSockAddrLen() const override;

private:
    struct sockaddr_in m_addr;
};
 
class IPv6Address : public IPAddress
{
public:
    using ptr = std::shared_ptr<IPv6Address>;

    explicit IPv6Address(); 
    explicit IPv6Address(const std::string& strIp, const uint16_t nPort);
    explicit IPv6Address(const uint16_t nPort, bool bLoopBackOnly = false);
    explicit IPv6Address(const struct sockaddr_in6& addr);
    ~IPv6Address();

    virtual std::string getIp() const override;
    virtual uint16_t getPort() const override;
    virtual std::string getIpPort() const override;
    virtual struct sockaddr* getSockAddr();
    virtual const struct sockaddr* getSockAddr() const override;
    virtual socklen_t getSockAddrLen() const override;

private:
    struct sockaddr_in6 m_addr;

};
    
} // namespace net

#endif