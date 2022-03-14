
#pragma once

#include "Socket.h"
#include <memory>

namespace cpp
{

namespace net
{

class Epoll
{
public:
    using ptr = std::shared_ptr<Epoll>;

    Epoll(Socket::ptr ptrSock);

    bool init();

    bool accept();

    void handleReadEvent(int fd);

    bool close();

private:
    int m_epollFd;
    Socket::ptr m_ptrServSock;
};

    
} // namespace net

    
} // namespace cpp
