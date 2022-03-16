#include "System.h"

#include <string.h>

namespace utils
{

void memZero(void* buf, size_t size)
{
    ::memset(buf, 0, size);
}
   

} // namespace utils