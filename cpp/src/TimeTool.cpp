
#include "TimeTool.h"

#include <sstream>

#include <iostream>

#ifndef WIN32
    #include <sys/time.h>
#endif

#include <time.h>

namespace cpp
{

Date Date::getCurrentDate()
{
    time_t now = ::time(nullptr);
    struct tm *t = ::localtime(&now);
    return Date{t->tm_year + 1900, t->tm_mon, t->tm_mday};
}

std::string Date::format(const char* fmt) const
{
    std::ostringstream os;
    char* p = const_cast<char*>(fmt);
    while(p && '\0' != *p)
    {
        if ('%' == *p)
        {
            ++p;
            switch (*p)
            {
                case 'Y': os << m_nYear; break;
                case 'M': os << m_nMonth; break;
                case 'D': os << m_nDay; break;
                default: os << *p; break;
            }
        }
        else
        {
            os << *p;
        }
        ++p;
    }

    return os.str(); 
}

Time Time::getCurrentTime()
{
#ifdef WIN32
    time_t now = ::time(nullptr);
    struct tm* t = ::localtime(&now);
    return Time{t->tm_hour, t->tm_min, t->tm_sec, 0};
#else
    struct timeval tv;
    ::gettimeofday(&tv, nullptr);
    time.m_nHour = tv.tv_sec / 60 / 60;
    time.m_nMin = tv.tv_sec / 60 % 60;
    time.m_nSec = tv.tv_sec % 60;
    time.m_nMSec = tv.tv_usec / 1000;
    return Time{tv.tv_hour/60/60, tv.tv_min/60%60, tv.tv_sec%60, tv.tv_usec/1000};
#endif
}

std::string Time::format(const char* fmt) const
{
    std::ostringstream os;
    char* p = const_cast<char*>(fmt);
    while(p && '\0' != *p)
    {
        if ('%' == *p)
        {
            ++p;
            switch (*p)
            {
                case 'H': os << m_nHour; break;
                case 'm': os << m_nMin; break;
                case 'S': os << m_nSec; break;
                case 's': os << m_nMSec; break;
                default: os << *p; break;
            }
        }
        else
        {
            os << *p;
        }
        ++p;
    }

    return os.str(); 
}

DateTime DateTime::getCurrentDateTime()
{
    DateTime dateTime;
#ifdef WIN32
    time_t now = ::time(nullptr);
    struct tm* t = ::localtime(&now);
    dateTime.m_date.m_nYear = t->tm_year + 1900;
    dateTime.m_date.m_nMonth = t->tm_mon;
    dateTime.m_date.m_nDay = t->tm_mday;
    dateTime.m_time.m_nHour = t->tm_hour;
    dateTime.m_time.m_nMin = t->tm_min;
    dateTime.m_time.m_nSec = t->tm_sec;
    dateTime.m_time.m_nMSec = 0;
#else
    dateTime.m_date = getCurrentDate();
    dateTime.m_time = getCurrentTime();
#endif

    return dateTime;
}
 
std::string DateTime::format(const char* fmt) const
{
    std::ostringstream os;
    char* p = const_cast<char*>(fmt);
    while(p && '\0' != *p)
    {
        if ('%' == *p)
        {
            ++p;
            switch (*p)
            {
                case 'Y': os << m_date.m_nYear; break;
                case 'M': os << m_date.m_nMonth; break;
                case 'D': os << m_date.m_nDay; break;
                case 'H': os << m_time.m_nHour; break;
                case 'm': os << m_time.m_nMin; break;
                case 'S': os << m_time.m_nSec; break;
                case 's': os << m_time.m_nMSec; break;
                default: os << *p; break;
            }
        }
        else
        {
            os << *p;
        }
        ++p;
   }

    return os.str(); 
}   

} // namespace cpp
