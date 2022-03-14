
#pragma once

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

    Epoll(uint32_t nMaxEvents = 1000);
    
    ~Epoll();

    bool init();

    void updateChannel(Channel* ptrChannel);
    void deleteChannel(Channel* ptrChannel);

    std::vector<Channel*> poll(int timeout = -1);

private:
    int m_epollFd;
    uint32_t m_nMaxEvents;
    struct epoll_event* m_ptrEvents;
};

    
} // namespace net

    
} // namespace cpp
