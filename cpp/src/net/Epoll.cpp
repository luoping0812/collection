#include "Epoll.h"
#include "Macro.h"
#include "System.h"

#include <unistd.h>

namespace net
{

Epoll::Epoll(int nMaxEvents)
    : m_nMaxEvents(nMaxEvents)
{
    LOG_DEBUG();
}

Epoll::~Epoll()
{
    if (-1 != m_epollFd)
    {
        ::close(m_epollFd);
        m_epollFd = -1;
        delete[] m_ptrEvents;
    }
    LOG_DEBUG();
}

bool Epoll::init()
{
    m_ptrEvents = new epoll_event[m_nMaxEvents];
    utils::memZero(m_ptrEvents, sizeof(struct epoll_event) * m_nMaxEvents);
    m_epollFd = ::epoll_create1(0);
    if (m_epollFd < 0)
    {
        return false; 
    }
    return true;
}
    
void Epoll::updateChannel(Channel::ptr ptrChannel)
{
    int sockfd = ptrChannel->getSocketPtr()->getSocket();
    struct epoll_event ev;
    utils::memZero(&ev, sizeof(struct epoll_event));
    ev.data.ptr = ptrChannel.get();
    //ev.data.fd = sockfd;
    ev.events = ptrChannel->getListenEvent();
    if (!ptrChannel->isExist())
    {
        int ret = ::epoll_ctl(m_epollFd, EPOLL_CTL_ADD, sockfd, &ev);
        if (-1 == ret)
        {
            handle_error();
            return;
        }
        ptrChannel->setExist(true);
    }
    else
    {
        int ret =::epoll_ctl(m_epollFd, EPOLL_CTL_MOD, sockfd, &ev);
        if (-1 == ret)
        {
            handle_error();
            return;
        }
    }

    LOG_INFO() << "update epoll event success.";
}

void Epoll::deleteChannel(Channel::ptr ptrChannel)
{
    int sockfd = ptrChannel->getSocketPtr()->getSocket();
    struct epoll_event ev;
    ev.data.ptr = ptrChannel.get();
    //ev.data.fd = sockfd;
    int ret = ::epoll_ctl(m_epollFd, EPOLL_CTL_DEL, sockfd, &ev);
    if (-1 == ret)
    {
        handle_error(); 
        return;
    }
    ptrChannel->setExist(false);
    LOG_INFO() << "del epoll event success.";
}

std::vector<Channel*> Epoll::poll(int timeout)
{
    std::vector<Channel*> vecChannel;
    int nfds = ::epoll_wait(m_epollFd, m_ptrEvents, m_nMaxEvents, timeout);
    if (-1 == nfds)
    {
        handle_error(); 
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