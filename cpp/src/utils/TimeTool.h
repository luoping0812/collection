#ifndef TIMETOOL_H
#define TIMETOOL_H


#include <string>

namespace utils
{

class TimeTool 
{
public:
    static time_t now();
    static void getCurrentDateTime(int& year, int& month, int& day, int& hour, int& min, int& sec);
    static std::string getCurrentDateTime(const char* fmt = "%Y-%m-%d %H:%M:%S");
};
   
} // namespace utils

#endif