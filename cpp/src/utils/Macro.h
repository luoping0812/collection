#ifndef MACRO_H
#define MACRO_H


#include "Log.h"

#include <string.h>

namespace cpp
{
    
#define handle_error(condition, retTrue, retFalse) \
    if (!(condition)) \
    { \
        LOG_FMT_ERROR("%s error, errno: %d, errmsg: %s.", __FUNCTION__, errno, strerror(errno)); \
        return retFalse; \
    } \
    return retTrue;


} // namespace cpp

#endif