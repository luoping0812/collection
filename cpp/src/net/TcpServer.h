#ifndef TCPSERVER_H
#define TCPSERVER_H


#include "Acceptor.h"
#include "EventLoop.h"
#include "Address.h"
#include "Socket.h"
#include "Connection.h"
#include "ThreadPool.h"

#include <memory>
#include <functional>
#include <unordered_map>
#include <vector>

namespace cpp
{

namespace net
{

class TcpServer : public std::enable_shared_from_this<TcpServer>
{
public:
    using ptr = std::shared_ptr<TcpServer>;

    TcpServer(EventLoop::ptr ptrEventLoop, Socket::ptr ptrSock, IPAddress::ptr ptrAddr);
    ~TcpServer();

    void onNewConnection(Socket::ptr clientSock);
    void onDeleteConnection(Socket::ptr clientSock);

    void setHandEventCB(std::function<void(Connection::ptr)> cb);

    void handleEvent(Connection::ptr ptrCon);


private:
    Acceptor::ptr m_ptrAcceptor;
    std::unordered_map<int, Connection::ptr> m_mapFd2Connection;
    std::vector<EventLoop::ptr> m_vecSubReactor;
    std::function<void(Connection::ptr)> m_cb;
    ThreadPool::ptr m_ptrThreads;
};
    
} // namespace net
    
} // namespace cpp


#endif