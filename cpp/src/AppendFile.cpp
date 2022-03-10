#pragma once

#include "AppendFile.h"

namespace cpp
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
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_fstream.is_open())
    {
        m_fstream.close();
    }
    m_fstream.open(file, std::ios::app);
}

void AppendFile::flush()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_fstream.flush();
}

AppendFile::~AppendFile()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_fstream.is_open())
    {
        m_fstream.flush();
    }
    
    m_fstream.close();
}

    
} // namespace cpp
