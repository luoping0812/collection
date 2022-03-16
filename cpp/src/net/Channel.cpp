#include "Channel.h"
#include "Log.h"

namespace cpp
{

namespace net
{

Channel::Channel(Socket::ptr ptrSock)
    : m_ptrSock(ptrSock)
    , m_nListenEvent(0)
    , m_bExist(false)
{
    LOG_DEBUG();
}

Channel::~Channel()
{
    LOG_DEBUG();
}

Socket::ptr Channel::getSocketPtr()
{
    return m_ptrSock;
}

void Channel::setEventCallback(std::function<void()> cb)
{
    m_cb = cb;
}
    
void Channel::handleEvent()
{
    m_cb();
}

void Channel::addListenEvent(uint32_t event)
{
    m_nListenEvent |= event; 
}

} // namespace net

    
} // namespace cpp
