#ifndef CHANNEL_H
#define CHANNEL_H



#include "Socket.h"
#include "Callback.h"

#include <memory>

namespace cpp
{

namespace net
{

class Channel
{
public:
    using ptr = std::shared_ptr<Channel>;

    Channel(Socket::ptr ptrSock);

    Socket::ptr getSocketPtr();

    void handleEvent();

    void setEventCallback(newConnectionCB_t cb);

    void addListenEvent(int event);

    int getListenEvent() { return m_nListenEvent; }

    bool isExist() { return m_bExist; }

    void setExist(bool val) { m_bExist = val; }

private:
    Socket::ptr m_ptrSock;
    newConnectionCB_t m_cb;

    int m_nListenEvent;

    bool m_bExist;
};

    
} // namespace net

} // namespace cpp

#endif