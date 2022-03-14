#include "Log.h"


namespace cpp
{

FileAppender::FileAppender(const std::string& name)
{
    m_ptrAppend = std::shared_ptr<AppendFile>();
    m_ptrAppend->open(name.c_str());
}

void FileAppender::append(const std::string& str)
{
    m_ptrAppend->append(str);
    m_ptrAppend->flush();
}

FileAppender::~FileAppender()
{
    m_ptrAppend->close();
}

StdoutAppender::StdoutAppender(const std::string& name)
{

}

void StdoutAppender::append(const std::string& str)
{
    std::cout << str;
    std::cout.flush();
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
}

void Logger::log(const std::string& str)
{
    if (!m_ptrAppender)
    {
        m_ptrAppender = std::make_shared<StdoutAppender>(m_strFile);
    }

    if (m_bAsync)
    {
        m_ptrThreads->push([this, str](){
            m_ptrAppender->append(str);
        });
    }
    else
    {
        m_ptrAppender->append(str);
    }
}
 
LogStream::LogStream(ELogLevel eLevel, const std::string& strTime, const std::string& strFile, const std::string& strFunc, uint32_t nLine)
{
    static const char* spliter = " ";
    m_ostringstream << strTime << spliter;
    m_ostringstream << getLogLevelName(eLevel) << spliter;
    m_ostringstream << "[" << strFile << ":" << strFunc << ":" << nLine <<"]" << spliter;
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

    if (buf)
    {
        m_ostringstream << buf;
        free(buf);
    }

    va_end(vl);
}
 
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

} // namespace cpp
