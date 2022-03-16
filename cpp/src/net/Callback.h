#pragma once

#include "Socket.h"
#include <functional>

namespace net
{


using newConnectionCB_t = std::function<void(Socket::ptr ptrSock)>; 
using connectionCloseCB_t = std::function<void(Socket::ptr ptrSock)>; 

    
} // namespace net