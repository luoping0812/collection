
#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include "Address.h"
#include "Socket.h" 
#include "EventLoop.h"
#include "Callback.h"
#include "Channel.h"

#include <memory>
#include <string>

namespace cpp
{

namespace net
{

class Acceptor : public std::enable_shared_from_this<Acceptor>
{
public:
    using ptr = std::shared_ptr<Acceptor>;

    Acceptor(EventLoop::ptr ptrEventLoop, Socket::ptr ptrSock, IPAddress::ptr ptrAddr);
    ~Acceptor();

    void setNewConnectionCB(newConnectionCB_t cb);
    void handleEvent();

private:
    Socket::ptr m_ptrSock;
    Channel::ptr m_ptrChannel;
    EventLoop::ptr m_ptrEventLoop;
    newConnectionCB_t m_newConnectionCB;
};

    
} // namespace net

    
} // namespace cpp

#endif
