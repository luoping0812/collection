
#include "Channel.h"

namespace cpp
{

namespace net
{

Channel::Channel(Socket::ptr ptrSock)
    : m_ptrSock(ptrSock)
    , m_bExist(false)
{

}

Socket::ptr Channel::getSocketPtr()
{
    return m_ptrSock;
}

void Channel::setEventCallback(newConnectionCB_t cb)
{
    m_cb = cb;
}
    
void Channel::handleEvent()
{
    m_cb(m_ptrSock);
}

bool Channel::addListenEvent(int event)
{
    m_nListenEvent |= event; 
}

} // namespace net

    
} // namespace cpp
