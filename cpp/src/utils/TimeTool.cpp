
#include "TimeTool.h"
#include <sstream>
#include <time.h>

namespace utils
{
    


time_t TimeTool::now()
{
    return ::time(nullptr);
}

void TimeTool::getCurrentDateTime(int& year, int& month, int& day, int& hour, int& min, int& sec)
{
    time_t n = TimeTool::now(); 
    struct tm* t = ::localtime(&n);
    year = t->tm_year + 1900;
    month = t->tm_mon;
    day = t->tm_mday;
    hour = t->tm_hour;
    min = t->tm_min;
    sec = t->tm_sec;
}

std::string TimeTool::getCurrentDateTime(const char* fmt)
{
    time_t n = TimeTool::now(); 
    struct tm* t = ::localtime(&n);
    char buf[128] = "";
    ::strftime(buf, sizeof(buf), fmt, t);
    return buf;
}
   
} // namespace utils