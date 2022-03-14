#pragma once

#include "Acceptor.h"
#include "EventLoop.h"
#include "Address.h"
#include "Socket.h"

#include <memory>
#include <functional>

namespace cpp
{

namespace net
{

class TcpServer : public std::enable_shared_from_this<TcpServer>
{
public:
    using ptr = std::shared_ptr<TcpServer>;

    TcpServer(EventLoop::ptr ptrEventLoop, Socket::ptr ptrSock, IPAddress::ptr ptrAddr);

    void setHandEventCB(std::function<void(Socket::ptr)> cb);

    void handleEvent(Socket::ptr ptrSock);

    void onNewConnection(Socket::ptr ptrSock);

private:
    Acceptor::ptr m_ptrAcceptor;
    EventLoop::ptr m_ptrEventLoop;
    std::function<void(Socket::ptr )> m_cb;
};
    
} // namespace net
    
} // namespace cpp
