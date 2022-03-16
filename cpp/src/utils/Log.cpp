#include "Log.h"


namespace utils
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

void Logger::init(const std::string& strFile, ELogLevel eLevel, bool bAsync, size_t threadNum)
{
    std::unique_lock<std::mutex> lock(m_mutex);
    m_bAsync = bAsync;
    if (m_bAsync)
    {
        m_ptrThreads = std::make_shared<ThreadPool>(threadNum); 
    }

    m_ptrAppender = std::make_shared<StdoutAppender>(m_strFile);
    m_strFile = strFile;
    m_eLevel = eLevel;
}

void Logger::log(const std::string& str)
{
    if (m_bAsync)
    {
        m_ptrThreads->push([this, str](){
            std::unique_lock<std::mutex> lock(m_mutex);
            m_ptrAppender->append(str);
        });
    }
    else
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_ptrAppender->append(str);
    }
}
 
LogStream::LogStream(ELogLevel eLevel, const std::string& strTime, const std::string& strFile, const std::string& strFunc, uint32_t nLine)
{
    static const char* spliter = " ";
    m_ostringstream << strTime << spliter;
    m_ostringstream << getLogLevelName(eLevel) << spliter;
    m_ostringstream << "[" << strFile << ":" << strFunc << ":" << nLine <<"]" << spliter;
    m_ostringstream << "[" << std::this_thread::get_id() << "]" << spliter;
}

LogStream::~LogStream()
{
    m_ostringstream << std::endl;
    utils::Logger::instance()->log(m_ostringstream.str());
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
    switch (eLevel)
    {
#define XX(str) \
    case ELogLevel::LOG_LEVEL_##str: \
        return "[" #str "]";

        XX(TRACE)
        XX(DEBUG)
        XX(INFO)
        XX(WARN)
        XX(ERROR)
    }

    return "[]"; 
}

} // namespace utils
