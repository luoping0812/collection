#ifndef CONNECTION_H
#define CONNECTION_H

#include "Socket.h"
#include "Channel.h"
#include "EventLoop.h"

#include <memory>
#include <string>

namespace cpp
{

namespace net
{

class Connection : public std::enable_shared_from_this<Connection>
{
public:
    using ptr = std::shared_ptr<Connection>;

    Connection(EventLoop::ptr ptrEventLoop, Socket::ptr ptrSock, IPAddress::ptr ptrPeerAddr = IPAddress::ptr());

    void read(std::string& str);

    void write(const std::string& str);

    void handleEvent();

    void setHandleEventCB(std::function<void(Connection::ptr)> cb);

    IPAddress::ptr getPeerAddress();

private:
    Socket::ptr m_ptrSock;
    Channel::ptr m_ptrChannel;
    EventLoop::ptr m_ptrEventLoop;
    std::function<void(Connection::ptr)> m_cb;
    std::string m_strReadBuffer;
    std::string m_strWriteBuffer;
    IPAddress::ptr m_ptrPeerAddr;
    bool m_bConnected;
};

} // namespace net

    
} // namespace cpp



#endif