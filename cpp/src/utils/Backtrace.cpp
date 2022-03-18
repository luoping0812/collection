#include "Backtrace.h"

#include <execinfo.h>

namespace utils
{

std::vector<std::string> Backtrace()
{
    std::vector<std::string> ret;

    void** buf = (void**)::malloc(sizeof(void*) * 1024); 
    int n = ::backtrace(buf, 1024);

    char ** res = ::backtrace_symbols(buf, n);

    if (!res)
    {
        delete buf;
        return ret;
    }

    for (int i = 0; i < n; i++)
    {
        ret.push_back(res[i]);
    }
    delete res;
    delete buf;

    return ret;
}
    
} // namespace utils
