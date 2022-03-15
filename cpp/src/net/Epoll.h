#ifndef EPOLL_H
#define EPOLL_H

#include "Socket.h"
#include "Channel.h"

#include <memory>
#include <vector>

#include <sys/epoll.h>

namespace cpp
{

namespace net
{

class Epoll
{
public:
    using ptr = std::shared_ptr<Epoll>;

    Epoll(int nMaxEvents = 1000);
    
    ~Epoll();

    bool init();

    void updateChannel(Channel::ptr ptrChannel);
    void deleteChannel(Channel::ptr ptrChannel);

    std::vector<Channel*> poll(int timeout = -1);

private:
    int m_epollFd;
    int m_nMaxEvents;
    struct epoll_event *m_ptrEvents;
};

    
} // namespace net

    
} // namespace cpp

#endif