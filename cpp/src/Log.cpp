#include "Log.h"


namespace cpp
{

std::string getLogLevelName(ELogLevel eLevel)
{
    std::stringstream os;
    os << "[";
    switch (eLevel)
    {
#define XX(str) \
    case ELogLevel::LOG_LEVEL_##str: \
        os << #str; \
        break;

        XX(TRACE)
        XX(DEBUG)
        XX(INFO)
        XX(WARN)
        XX(ERROR)
    }
    os << "]";

    return os.str(); 
}

Logger::Logger()
    : m_strFile(TimeTool::getCurrentDateTime() + ".log")
    , m_eLevel(ELogLevel::LOG_LEVEL_INFO)
    , m_bAsync(false)
{

}

void Logger::init(const std::string& strFile, ELogLevel eLevel, bool bAsync, size_t threadNum)
{
    m_bAsync = bAsync;
    if (m_bAsync)
    {
        m_ptrThreads = std::make_shared<ThreadPool>(threadNum); 
    }

    m_strFile = strFile;
    m_eLevel = eLevel;
    m_ptrAppendFile = std::make_shared<AppendFile>(strFile.c_str());
}

void Logger::log(const std::string& str)
{
    if (!m_ptrAppendFile)
    {
        m_ptrAppendFile = std::make_shared<AppendFile>(m_strFile.c_str());
    }

    if (m_bAsync)
    {
        m_ptrThreads->push([this, str](){
            m_ptrAppendFile->append(str).flush();
        });
    }
    else
    {
        m_ptrAppendFile->append(str).flush();
    }
}
 
LogStream::LogStream(ELogLevel eLevel, const std::string& strTime, const std::string& strFile, const std::string& strFunc, uint32_t nLine)
{
    static const char* spliter = " ";
    m_ostringstream << strTime << spliter;
    m_ostringstream << getLogLevelName(eLevel) << spliter;
    m_ostringstream << "[" << strFile << ":" << nLine <<"]" << spliter;
    m_ostringstream << "[" << strFunc << "]" << spliter;
}

LogStream::~LogStream()
{
    m_ostringstream << std::endl;
    cpp::Logger::instance()->log(m_ostringstream.str());
}

void LogStream::format(const char* fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);

#ifdef WIN32
    size_t size = sizeof(char) * 4096;
    char *buf = (char*)malloc(size);
    ::vsnprintf(buf, size, fmt, vl);
#else
    char* buf = nullptr;
    ::vasprintf(&buf, fmt, vl);
#endif
    m_ostringstream << buf;

    if (buf)
    {
        free(buf);
    }

    va_end(vl);
}
   
} // namespace cpp
