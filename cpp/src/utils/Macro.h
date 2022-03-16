#ifndef MACRO_H
#define MACRO_H


#include "Log.h"

#include <exception>
#include <string>
#include <string.h>

namespace utils
{
    
#define handle_error() \
            LOG_FMT_ERROR("%s error, errno: %d, errmsg: %s.", __FUNCTION__, errno, strerror(errno));

} // namespace utils 

#endif