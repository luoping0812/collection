#include "Log.h"
#include "Socket.h"
#include "System.h"

#include <iostream>
#include <stdlib.h>
#include <string.h>


using namespace std;
using namespace utils;
using namespace net;

int main(int argc, char const *argv[])
{
    utils::Logger::instance()->init("test_server.log", LLV_INFO, false, 4);
    Socket::ptr ptrSock = std::make_shared<Socket>(AF_INET, SOCK_STREAM, 0);
    if (!ptrSock->init())
    {
        return -1;
    }
    IPAddress::ptr ptrAddr = std::make_shared<IPv4Address>(8000);
    ptrSock->bind(ptrAddr);
    ptrSock->listen();
    
    IPAddress::ptr clientAddr;
    Socket::ptr ptrClient = ptrSock->accept(clientAddr);
    if (nullptr != ptrClient && nullptr != clientAddr)
    {
        LOG_FMT_INFO("client %s connected.", clientAddr->getIpPort().c_str()); 
    }
    else
    {
        LOG_ERROR() << "accept error";
    }
    
    char buf[128];
    while (true)
    {
        memZero(buf, sizeof(buf));
        //int ret = ptrClient->recv(buf, sizeof(buf));
        int ret = ptrClient->read(buf, sizeof(buf));
        if (ret <= 0)
        {
            LOG_FMT_INFO("recv client %s error, errno: %d, errmsg: %s", clientAddr->getIpPort().c_str(), errno, strerror(errno));
            break;
        }
        LOG_FMT_INFO("recv client %s msg: %s, size: %d", clientAddr->getIpPort().c_str(), buf, ret); 
    }

    ptrClient->close();
    ptrSock->close(); 

    return 0;
}
