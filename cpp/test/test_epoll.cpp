#include "Epoll.h"
#include "Socket.h"
#include "Log.h"
#include "TcpServer.h"
#include "EventLoop.h"
#include "System.h"
#include "Macro.h"
#include "Backtrace.h"

#include <signal.h>

using namespace utils;
using namespace net;

void handleSig(int sig)
{
    std::cout << sig << std::endl; 
    std::vector<std::string> res = utils::Backtrace();
    for (int i = 0; i < res.size(); i++)
    {
        LOG_INFO() << res.at(i);
    }
}

int main(int argc, char const *argv[])
{
    signal(SIGSEGV, handleSig);
    signal(SIGKILL, handleSig);
    signal(35, handleSig);

    utils::Logger::instance()->init("test_epoll.log", LLV_DEBUG);

    Socket::ptr ptrSock = std::make_shared<Socket>(AF_INET, SOCK_STREAM, 0);
    ptrSock->init();

    EventLoop::ptr eventLoop = std::make_shared<EventLoop>();
    IPAddress::ptr addr = std::make_shared<IPv4Address>(8000);
    TcpServer::ptr ptrServer = std::make_shared<TcpServer>(eventLoop, ptrSock, addr);
    ptrServer->setHandEventCB([](Connection::ptr ptrCon){
            if (!ptrCon->isConnected())
            {
                ptrCon->close();
            }

            std::string msg;
            ptrCon->read(msg); 
            LOG_FMT_INFO("recv client %s msg: %s, size: %d", ptrCon->getPeerAddress()->getIpPort().c_str(), msg.c_str(), msg.size()); 
    });

    eventLoop->loop();
    
    return 0;
}


