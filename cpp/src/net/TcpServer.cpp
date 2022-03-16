#include "TcpServer.h"

#include "Log.h"

namespace cpp
{

namespace net
{

TcpServer::TcpServer(EventLoop::ptr ptrEventLoop, Socket::ptr ptrSock, IPAddress::ptr ptrAddr)
    : m_ptrAcceptor(std::make_shared<Acceptor>(ptrEventLoop, ptrSock, ptrAddr))
{
    m_ptrAcceptor->setNewConnectionCB(std::bind(&TcpServer::onNewConnection, this, std::placeholders::_1));

    int nSize = std::thread::hardware_concurrency();
    m_ptrThreads = std::make_shared<ThreadPool>(nSize);
    for (int i = 0; i < nSize; i++)
    {
        EventLoop::ptr eventLoop = std::make_shared<EventLoop>();
        m_vecSubReactor.push_back(eventLoop);
        m_ptrThreads->push(std::bind(&EventLoop::loop, eventLoop));
    }
    LOG_DEBUG();
}

TcpServer::~TcpServer()
{
    LOG_DEBUG();
}

void TcpServer::onNewConnection(Socket::ptr clientSock)
{
    int index = clientSock->getSocket() % m_vecSubReactor.size();
    Connection::ptr ptrCon = std::make_shared<Connection>(m_vecSubReactor[index], clientSock);
    ptrCon->setHandleEventCB(std::bind(&TcpServer::handleEvent, this, std::placeholders::_1));
    ptrCon->setDeleteConnectionCB(std::bind(&TcpServer::onDeleteConnection, this, std::placeholders::_1));
    m_mapFd2Connection.insert(std::make_pair(clientSock->getSocket(), ptrCon));
}

void TcpServer::onDeleteConnection(Socket::ptr clientSock)
{
    auto itr = m_mapFd2Connection.find(clientSock->getSocket());
    if (itr != m_mapFd2Connection.end())
    {
        m_mapFd2Connection.erase(itr);
    }
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
