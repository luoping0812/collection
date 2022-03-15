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


void TcpServer::onNewConnection(Socket::ptr clientSock)
{
    Connection::ptr ptrCon = std::make_shared<Connection>(m_ptrEventLoop, clientSock);
    ptrCon->setHandleEventCB(std::bind(&TcpServer::handleEvent, this, std::placeholders::_1));
    m_mapFd2Connection.insert(std::make_pair(clientSock->getSocket(), ptrCon));
}

void TcpServer::setHandEventCB(std::function<void(Connection::ptr)> cb)
{
    m_cb = cb;
}

void TcpServer::handleEvent(Connection::ptr ptrCon)
{
    m_cb(ptrCon);
}

} // namespace net

    
} // namespace cpp
