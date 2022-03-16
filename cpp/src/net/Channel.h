#ifndef CHANNEL_H
#define CHANNEL_H



#include "Socket.h"
#include "Callback.h"

#include <memory>

namespace net
{

class Channel : public std::enable_shared_from_this<Channel>
{
public:
    using ptr = std::shared_ptr<Channel>;

    Channel(Socket::ptr ptrSock);

    ~Channel();

    Socket::ptr getSocketPtr();

    void handleEvent();

    void setEventCallback(std::function<void()> cb);

    void addListenEvent(uint32_t event);

    uint32_t getListenEvent() { return m_nListenEvent; }

    bool isExist() { return m_bExist; }

    void setExist(bool val) { m_bExist = val; }

private:
    Socket::ptr m_ptrSock;
    std::function<void()> m_cb;
    uint32_t m_nListenEvent;
    uint32_t m_nRedingEvent;
    bool m_bExist;
};

    
} // namespace net

#endif