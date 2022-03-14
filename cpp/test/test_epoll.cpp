#include "Epoll.h"
#include "Socket.h"
#include "Log.h"

using namespace cpp;
using namespace cpp::net;

int main(int argc, char const *argv[])
{
    cpp::Logger::instance()->init("test_epoll.log", LLV_INFO);
    Socket::ptr ptrSock = std::make_shared<Socket>(AF_INET, SOCK_STREAM, 0);
    if (!ptrSock->init())
    {
        return -1;
    }
    IPAddress::ptr ptrAddr = std::make_shared<IPv4Address>(8000);
    ptrSock->bind(ptrAddr);
    ptrSock->listen();
 
    Epoll::ptr epoll = std::make_shared<Epoll>(ptrSock);
    epoll->init();
    epoll->accept();
    
    epoll->close();
    
    return 0;
}


