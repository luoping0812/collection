#include "EventLoop.h"

namespace cpp
{

namespace net
{

EventLoop::EventLoop()
    : m_bQuit(false)
{
    m_ptrEpoll = std::make_shared<Epoll>();
    m_ptrEpoll->init();
}

void EventLoop::loop()
{
    while (!m_bQuit)
    {
        std::vector<Channel*> vecChannels = m_ptrEpoll->poll();
        for (auto ch : vecChannels)
        {
            ch->handleEvent();
        }
    }
}
    
void EventLoop::updateChannel(Channel::ptr ptrChannel)
{
    m_ptrEpoll->updateChannel(ptrChannel);
}

void EventLoop::deleteeChannel(Channel::ptr ptrChannel)
{
    m_ptrEpoll->deleteChannel(ptrChannel);
}

} // namespace net

    
} // namespace cpp
