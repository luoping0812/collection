#pragma once

#include "Epoll.h"

#include <memory>

namespace cpp
{

namespace net
{
    
class EventLoop
{
public:
    using ptr = std::shared_ptr<EventLoop>;

    EventLoop();

    void loop();

    void updateChannel(Channel* ptrChannel);
    void deleteeChannel(Channel* ptrChannel);

private:
    bool m_bQuit;
    net::Epoll::ptr m_ptrEpoll;
};
    
} // namespace net

} // namespace cpp
