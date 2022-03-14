#include "Epoll.h"
#include "Macro.h"
#include "System.h"

#include <sys/epoll.h>
#include <unistd.h>

namespace cpp
{

namespace net
{

Epoll::Epoll(Socket::ptr ptrSock)
    : m_ptrServSock(ptrSock)
{
}

bool Epoll::init()
{
    handle_error(-1 != (m_epollFd = ::epoll_create1(0)), true, false);
}
    
bool Epoll::accept()
{
    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = m_ptrServSock->getSocket();
    int ret = ::epoll_ctl(m_epollFd, EPOLL_CTL_ADD, m_ptrServSock->getSocket(), &ev);
    if (-1 == ret)
    {
        LOG_FMT_INFO("epoll add sock %d errro", m_ptrServSock->getSocket());
        return false;
    }

    struct epoll_event events[100];
    while (true)
    {
        int nfds = ::epoll_wait(m_epollFd, events, 100, -1);
        if (-1 == nfds)
        {
            LOG_INFO() << "epoll accept errro";
            return false;
        }

        for (int n = 0; n < nfds; ++n)
        {
            if (events[n].data.fd == m_ptrServSock->getSocket())
            {
                IPAddress::ptr addr;
                Socket::ptr clientSock = m_ptrServSock->accept(addr);
                if (!clientSock)
                {
                    LOG_INFO() << "socket accept errro";
                    return false;
                }

                LOG_FMT_INFO("new client %s connected.", addr->getIpPort().c_str()); 

                clientSock->setNonBlocking();
                ev.events = EPOLLIN | EPOLLET;
                ev.data.fd = clientSock->getSocket();
                int ret = ::epoll_ctl(m_epollFd, EPOLL_CTL_ADD, clientSock->getSocket(), &ev);
                if (-1 == ret)
                {
                    LOG_INFO() << "epoll add sock errro";
                    return false;
                }
            }
            else
            {
                handleReadEvent(events[n].data.fd);
            }
        }
    }
}

void Epoll::handleReadEvent(int fd)
{
    Socket::ptr ptrClient = std::make_shared<Socket>(
                        m_ptrServSock->getFamily(), m_ptrServSock->getType(), m_ptrServSock->getProtocol());
    ptrClient->init(fd);
 
    char buf[128];
    while (true)
    {
        memZero(buf, sizeof(buf));
        int ret = ptrClient->read(buf, sizeof(buf));
        if (ret <= 0)
        {
            LOG_FMT_INFO("recv client %s error, errno: %d, errmsg: %s", ptrClient->getPeerAddress()->getIpPort().c_str(), errno, strerror(errno));
            break;
        }
        LOG_FMT_INFO("recv client %s msg: %s, size: %d", ptrClient->getPeerAddress()->getIpPort().c_str(), buf, ret); 
    }
}

bool Epoll::close()
{
    ::close(m_epollFd);
}

} // namespace net

    
} // namespace cpp
