#pragma once

#include "System.h"

#include <string.h>


namespace cpp
{


void memZero(void* buf, size_t size)
{
    ::memset(buf, 0, size);
}
   

    
} // namespace cpp
