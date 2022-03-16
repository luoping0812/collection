#ifndef CONNECTION_H
#define CONNECTION_H

#include "Socket.h"
#include "Channel.h"
#include "EventLoop.h"

#include <memory>
#include <string>

namespace net
{

class Connection : public std::enable_shared_from_this<Connection>
{
public:
    using ptr = std::shared_ptr<Connection>;

    Connection(EventLoop::ptr ptrEventLoop, Socket::ptr ptrSock, IPAddress::ptr ptrPeerAddr = IPAddress::ptr());

    ~Connection();

    void read(std::string& str);

    void write(const std::string& str);

    void close();

    void handleEvent();

    void setHandleEventCB(std::function<void(Connection::ptr)> cb) { m_handCB = cb; }
    void setDeleteConnectionCB(std::function<void(Socket::ptr )> cb) { m_delCB = cb; };

    IPAddress::ptr getPeerAddress();
    bool isConnected() { return m_bConnected; }

private:
    Socket::ptr m_ptrSock;
    Channel::ptr m_ptrChannel;
    EventLoop::ptr m_ptrEventLoop;
    std::function<void(Connection::ptr)> m_handCB;
    std::function<void(Socket::ptr )> m_delCB;
    std::string m_strReadBuffer;
    std::string m_strWriteBuffer;
    IPAddress::ptr m_ptrPeerAddr;
    bool m_bConnected;
};

} // namespace net

    
#endif