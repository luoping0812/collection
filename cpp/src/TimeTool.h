#pragma once


#include <string>

namespace cpp
{

struct Date
{
public:
    static Date getCurrentDate();
    std::string format(const char* fmt = "%Y-%M-%D") const;

public:
    int m_nYear; // 年
    int m_nMonth; // 月
    int m_nDay; // 日
};

struct Time
{
public:
    static Time getCurrentTime();
    std::string format(const char* fmt = "%H:%m:%S.%s") const;

public:
    int m_nHour; // 小时
    int m_nMin; // 分钟
    int m_nSec; // 秒
    int m_nMSec; // 毫秒
};

struct DateTime
{
public:
    static DateTime getCurrentDateTime();
    std::string format(const char* fmt = "%Y-%M-%D %H:%m:%S.%s") const;

public:
    Date m_date;
    Time m_time;
};
   
} // namespace cpp
