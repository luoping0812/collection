
#ifndef EVENTLOOP_H
#define EVENTLOOP_H

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
    ~EventLoop();

    void loop();

    void updateChannel(Channel::ptr ptrChannel);
    void deleteeChannel(Channel::ptr ptrChannel);

private:
    bool m_bQuit;
    net::Epoll::ptr m_ptrEpoll;
};
    
} // namespace net

} // namespace cpp


#endif