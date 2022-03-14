#include "Epoll.h"
#include "Macro.h"
#include "System.h"

#include <unistd.h>

namespace cpp
{

namespace net
{

Epoll::Epoll(uint32_t nMaxEvents)
    : m_nMaxEvents(nMaxEvents)
{
}

Epoll::~Epoll()
{
    if (-1 != m_epollFd)
    {
        ::close(m_epollFd);
        m_epollFd = -1;
        delete[] m_ptrEvents;
    }
}

bool Epoll::init()
{
    m_ptrEvents = new epoll_event[m_nMaxEvents];
    handle_error(-1 != (m_epollFd = ::epoll_create1(0)), true, false);
}
    
void Epoll::updateChannel(Channel* ptrChannel)
{
    int sockfd = ptrChannel->getSocketPtr()->getSocket();
    struct epoll_event ev;
    ev.data.ptr = ptrChannel;

    if (ptrChannel->getListenEvent() & EPOLLIN)
    {
        ev.events |= EPOLLIN;
    }

    if (ptrChannel->getListenEvent() & EPOLLOUT)
    {
        ev.events |= EPOLLOUT;
    }

    if (ptrChannel->getListenEvent() & EPOLLET)
    {
        ev.events |= EPOLLET;
    }

    if (!ptrChannel->isExist())
    {
        ::epoll_ctl(m_epollFd, EPOLL_CTL_ADD, sockfd, &ev);
        ptrChannel->setExist(true);
    }
    else
    {
        ::epoll_ctl(m_epollFd, EPOLL_CTL_MOD, sockfd, &ev);
    }
}

void Epoll::deleteChannel(Channel* ptrChannel)
{
    int sockfd = ptrChannel->getSocketPtr()->getSocket();
    struct epoll_event ev;
    ev.data.ptr = ptrChannel;
    ::epoll_ctl(m_epollFd, EPOLL_CTL_DEL, sockfd, &ev);
}

std::vector<Channel*> Epoll::poll(int timeout)
{
    std::vector<Channel*> vecChannel;
    int nfds = ::epoll_wait(m_epollFd, m_ptrEvents, m_nMaxEvents, timeout);
    if (-1 == nfds)
    {
        LOG_INFO() << "epoll accept errro";
        return vecChannel;
    }

    for (int n = 0; n < nfds; ++n)
    {
        Channel* ch = (Channel* )m_ptrEvents[n].data.ptr;
        vecChannel.emplace_back(ch);
    }

    return vecChannel;
}

} // namespace net

    
} // namespace cpp
