#include "TcpServer.h"

#include "Log.h"

namespace cpp
{

namespace net
{

TcpServer::TcpServer(EventLoop::ptr ptrEventLoop, Socket::ptr ptrSock, IPAddress::ptr ptrAddr)
    : m_ptrEventLoop(ptrEventLoop)
    , m_ptrAcceptor(std::make_shared<Acceptor>(ptrEventLoop, ptrSock, ptrAddr))
{

    m_ptrAcceptor->setNewConnectionCB(std::bind(&TcpServer::onNewConnection, this, std::placeholders::_1));

}


void TcpServer::onNewConnection(Socket::ptr ptrSock)
{
    IPAddress::ptr addr;
    Socket::ptr clientSock = ptrSock->accept(addr);
    if (!clientSock)
    {
        LOG_INFO() << "socket accept errro";
        return;
    }

    LOG_FMT_INFO("new client %s connected.", addr->getIpPort().c_str()); 

    clientSock->setNonBlocking();
    Channel* ptrChannel = new Channel(clientSock);
    ptrChannel->addListenEvent(EPOLLIN | EPOLLET);
    ptrChannel->setEventCallback(std::bind(&TcpServer::handleEvent, shared_from_this(), std::placeholders::_1));
    m_ptrEventLoop->updateChannel(ptrChannel);
}

void TcpServer::setHandEventCB(std::function<void(Socket::ptr)> cb)
{
    m_cb = cb;
}

void TcpServer::handleEvent(Socket::ptr ptrSock)
{
    m_cb(ptrSock);
}

} // namespace net

    
} // namespace cpp
