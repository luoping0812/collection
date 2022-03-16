#include "Acceptor.h"
#include "Log.h"

namespace cpp
{

namespace net
{

Acceptor::Acceptor(EventLoop::ptr ptrEventLoop, Socket::ptr ptrSock, IPAddress::ptr ptrAddr)
    : m_ptrSock(ptrSock)
    , m_ptrEventLoop(ptrEventLoop)
{
    m_ptrSock->bind(ptrAddr);

    if (m_ptrSock->listen())
    {
        LOG_FMT_INFO("server start listen addr %s", ptrAddr->getIpPort().c_str());
    }

    m_ptrChannel = std::make_shared<Channel>(m_ptrSock);
    m_ptrChannel->addListenEvent(EPOLLIN | EPOLLET);
    m_ptrChannel->setEventCallback(std::bind(&Acceptor::handleEvent, this));
    ptrEventLoop->updateChannel(m_ptrChannel);

    LOG_DEBUG();
}

Acceptor::~Acceptor()
{
    LOG_DEBUG();
}

void Acceptor::setNewConnectionCB(newConnectionCB_t cb)
{
    m_newConnectionCB = cb;
}

void Acceptor::handleEvent()
{
    IPAddress::ptr addr;
    Socket::ptr clientSock = m_ptrSock->accept(addr);
    if (!clientSock)
    {
        LOG_INFO() << "socket accept errro";
        return;
    }
    clientSock->setNonBlocking();
    LOG_FMT_INFO("new client %s connected.", addr->getIpPort().c_str()); 
    m_newConnectionCB(clientSock);
}

} // namespace net

} // namespace cpp
