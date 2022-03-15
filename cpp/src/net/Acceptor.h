
#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include "Address.h"
#include "Socket.h" 
#include "EventLoop.h"
#include "Callback.h"

#include <memory>
#include <string>

namespace cpp
{

namespace net
{

class Acceptor
{
public:
    using ptr = std::shared_ptr<Acceptor>;

    Acceptor(EventLoop::ptr ptrEventLoop, Socket::ptr ptrSock, IPAddress::ptr ptrAddr);

    void setNewConnectionCB(newConnectionCB_t cb);
    void handleNewConnectionCB(Socket::ptr ptrSock);



private:
    Socket::ptr m_ptrSock;
    EventLoop::ptr m_ptrEventLoop;
    newConnectionCB_t m_newConnectionCB;
};

    
} // namespace net

    
} // namespace cpp

#endif
