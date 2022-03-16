#include "AppendFile.h"

namespace utils 
{

AppendFile::AppendFile(const char* file)
{
    if (file)
    {
        open(file);
    }
}

void AppendFile::open(const char* file)
{
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    close();
    m_fstream.open(file, std::ios::app);
}

void AppendFile::close()
{
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    if (m_fstream.is_open())
    {
        flush();
        m_fstream.close();
    }
}

void AppendFile::flush()
{
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    if (m_fstream.is_open())
    {
        m_fstream.flush();
    }
}

AppendFile::~AppendFile()
{
    close();
}

    
} // namespace utils 
