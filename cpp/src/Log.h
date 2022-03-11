#pragma once

#include "Singleton.hpp"
#include "TimeTool.h"
#include "FileTool.h"
#include "AppendFile.h"
#include "ThreadPool.h"

#include <string>
#include <memory>
#include <sstream>

#include <stdint.h>
#include <stdarg.h>

#define LLV_TRACE           cpp::ELogLevel::LOG_LEVEL_TRACE
#define LLV_DEBUG           cpp::ELogLevel::LOG_LEVEL_DEBUG
#define LLV_INFO            cpp::ELogLevel::LOG_LEVEL_INFO
#define LLV_WARN            cpp::ELogLevel::LOG_LEVEL_WARN
#define LLV_ERROR           cpp::ELogLevel::LOG_LEVEL_ERROR

#define LOCAL_INFO \
    cpp::TimeTool::getCurrentDateTime() , cpp::FileTool::getFileNameFromDir(__FILE__), __FUNCTION__, __LINE__

#define LOG_LEVEL(level) \
    if (level >= cpp::Logger::instance()->getLevel()) \
        cpp::LogStream(level, LOCAL_INFO).stream()

#define LOG_TRACE()          LOG_LEVEL(LLV_TRACE)
#define LOG_DEBUG()          LOG_LEVEL(LLV_DEBUG)
#define LOG_INFO()           LOG_LEVEL(LLV_INFO)
#define LOG_WARN()           LOG_LEVEL(LLV_WARN)
#define LOG_ERROR()          LOG_LEVEL(LLV_ERROR)

#define LOG_FMT_LEVEL(level, fmt, ...) \
    if (level >= cpp::Logger::instance()->getLevel()) \
        cpp::LogStream(level, LOCAL_INFO).format(fmt, __VA_ARGS__)

#define LOG_FMT_TRACE(fmt, ...)          LOG_FMT_LEVEL(LLV_TRACE, fmt, __VA_ARGS__)
#define LOG_FMT_DEBUG(fmt, ...)          LOG_FMT_LEVEL(LLV_DEBUG, fmt, __VA_ARGS__)
#define LOG_FMT_INFO(fmt, ...)           LOG_FMT_LEVEL(LLV_INFO,  fmt, __VA_ARGS__)
#define LOG_FMT_WARN(fmt, ...)           LOG_FMT_LEVEL(LLV_WARN,  fmt, __VA_ARGS__)
#define LOG_FMT_ERROR(fmt, ...)          LOG_FMT_LEVEL(LLV_ERROR, fmt, __VA_ARGS__)

namespace cpp
{

enum class ELogLevel
{
    LOG_LEVEL_TRACE,
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR,
};

static inline std::string getLogLevelName(ELogLevel eLevel);

class Logger : public Singleton<Logger>
{
public:
    Logger();
    void init(const std::string& strFile, ELogLevel eLevel, bool bAsync = false, size_t threadNum = 2);
    ELogLevel getLevel() const { return m_eLevel; }

    void log(const std::string& str);

private:
    bool m_bAsync;
    ThreadPool::ptr m_ptrThreads;

    std::string m_strFile;
    ELogLevel m_eLevel;
    AppendFile::ptr m_ptrAppendFile;
};   

class LogStream
{
public:
    using ptr = std::shared_ptr<LogStream>;

    LogStream(ELogLevel eLevel, const std::string& strTime, const std::string& strFile \
            , const std::string& strFunc, uint32_t nLine);

    ~LogStream();

    std::ostringstream& stream() { return m_ostringstream; }

    void format(const char* fmt, ...);

private:
    std::ostringstream m_ostringstream;
};
 
} // namespace cpp

