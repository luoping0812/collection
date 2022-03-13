#include "Log.h"
#include "Socket.h"
#include "System.h"

#include <iostream>
#include <stdlib.h>
#include <string.h>


using namespace std;
using namespace cpp;
using namespace cpp::net;

int main(int argc, char const *argv[])
{
    cpp::Logger::instance()->init("test_server.log", LLV_INFO, false, 4);
    int sock = Socket::createSocket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        LOG_INFO() << "create socket error";
        return -1;
    }

    Socket::ptr ptrSock = std::make_shared<Socket>(sock);
    IPAddress::ptr ptrAddr = std::make_shared<IPv4Address>(8000);
    ptrSock->bind(ptrAddr);
    ptrSock->listen();
    
    IPAddress::ptr clientAddr = std::make_shared<IPv4Address>(); 
    Socket::ptr ptrClient = ptrSock->accept(clientAddr);
    if (nullptr != ptrClient)
    {
        LOG_FMT_INFO("client %s connected.", clientAddr->getIpPort().c_str()); 
    }
    
    char buf[128];
    while (true)
    {
        memZero(buf, sizeof(buf));
        if (!ptrClient->recv(buf, sizeof(buf)))
        {
            break;
        }
        LOG_FMT_INFO("recv client %s msg: %s", ptrAddr->getIpPort().c_str(), buf); 
    }

    ptrClient->close();
    ptrSock->close(); 

    return 0;
}
