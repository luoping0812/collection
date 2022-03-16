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
    utils::Logger::instance()->init("test_client.log", LLV_INFO, false, 4);
    Socket::ptr ptrSock = std::make_shared<Socket>(AF_INET, SOCK_STREAM, 0);
    if (!ptrSock->init())
    {
        return -1;
    }

    IPAddress::ptr ptrAddr = std::make_shared<IPv4Address>("127.0.0.1", 8000);
    if (ptrSock->connect(ptrAddr))
    {
        LOG_FMT_INFO("connect to %s success.", ptrAddr->getIpPort().c_str()); 
    }
    else
    {
        return -1;
    }

    char buf[128];
    while (true)
    {
        memZero(buf, sizeof(buf));
        cin >> buf;
        ptrSock->send(buf, strlen(buf));
    }

    ptrSock->close();
    
    return 0;
}
