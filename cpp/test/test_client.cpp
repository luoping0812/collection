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
    cpp::Logger::instance()->init("test_client.log", LLV_INFO, false, 4);
    int sock = Socket::createSocket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        LOG_INFO() << "create socket error";
        return -1;
    }

    Socket::ptr ptrSock = std::make_shared<Socket>(sock);
    IPAddress::ptr ptrAddr = std::make_shared<IPv4Address>("127.0.0.1", 8000);
    if (ptrSock->connect(ptrAddr))
    {
        //LOG_FMT_INFO("connect to %s success.", ptrAddr->getIpPort().c_str()); 
    }
    else
    {
        //LOG_FMT_INFO("connect to %s failed.", ptrAddr->getIpPort().c_str()); 
        return -1;
    }

    char buf[128];
    while (true)
    {
        memZero(buf, sizeof(buf));
        cin >> buf;
        ptrSock->send(buf, sizeof(buf));
    }

    ptrSock->close();
    
    return 0;
}
