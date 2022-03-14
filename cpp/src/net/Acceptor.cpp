#include "Acceptor.h"

namespace cpp
{

namespace net
{

Acceptor::Acceptor(EventLoop::ptr ptrEventLoop, Socket::ptr ptrSock, IPAddress::ptr ptrAddr)
    : m_ptrSock(ptrSock)
    , m_ptrEventLoop(ptrEventLoop)
{
    m_ptrSock->bind(ptrAddr);
    m_ptrSock->listen();

    Channel* ch = new Channel(m_ptrSock);
    ch->addListenEvent(EPOLLIN | EPOLLET);
    ch->setEventCallback(std::bind(&Acceptor::handleNewConnectionCB, this, std::placeholders::_1));
    ptrEventLoop->updateChannel(ch);
}
    
void Acceptor::setNewConnectionCB(newConnectionCB_t cb)
{
    m_newConnectionCB = cb;
}

void Acceptor::handleNewConnectionCB(Socket::ptr ptrSock)
{
    m_newConnectionCB(ptrSock);
}

} // namespace net

} // namespace cpp
