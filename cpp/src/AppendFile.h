#pragma once 

#include <fstream> 
#include <mutex>
#include <memory>
#include <assert.h>

#include <iostream>

namespace cpp
{

class AppendFile
{
public:
    using ptr = std::shared_ptr<AppendFile>;

    explicit AppendFile(const char* file = nullptr);

    ~AppendFile();

    void open(const char* file);

    void close();    

    void flush();

    template<typename T>
    AppendFile& append(const T& val)
    {
        std::lock_guard<std::recursive_mutex> lock(m_mutex);
        assert(m_fstream.is_open());
        //std::cout << val;
        m_fstream << val;
        return *this;
    }

    template<typename T>
    AppendFile& operator<<(const T& val)
    {
        return append(val);
    }

private:
    std::recursive_mutex m_mutex;
    std::fstream m_fstream;
};
    
} // namespace cpp
