#include "Epoll.h"
#include "Socket.h"
#include "Log.h"
#include "TcpServer.h"
#include "EventLoop.h"
#include "System.h"
#include "Macro.h"

using namespace cpp;
using namespace cpp::net;

int main(int argc, char const *argv[])
{
    cpp::Logger::instance()->init("test_epoll.log", LLV_INFO);

    Socket::ptr ptrSock = std::make_shared<Socket>(AF_INET, SOCK_STREAM, 0);
    ptrSock->init();

    EventLoop::ptr eventLoop = std::make_shared<EventLoop>();
    IPAddress::ptr addr = std::make_shared<IPv4Address>(8000);
    TcpServer::ptr ptrServer = std::make_shared<TcpServer>(eventLoop, ptrSock, addr);
    ptrServer->setHandEventCB([](Socket::ptr ptrSock){
        char buf[128];
        while (true)
        {
            memZero(buf, sizeof(buf));
            int ret = ptrSock->read(buf, sizeof(buf));
            if (ret <= 0)
            {
                LOG_FMT_INFO("recv client %s error, errno: %d, errmsg: %s, ret = %d", ptrSock->getPeerAddress()->getIpPort().c_str(), errno, strerror(errno), ret);
                break;
            }
            LOG_FMT_INFO("recv client %s msg: %s, size: %d", ptrSock->getPeerAddress()->getIpPort().c_str(), buf, ret); 
        }
    });

    eventLoop->loop();
    
    return 0;
}


