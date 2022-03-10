#pragma once 

#include <fstream> 
#include <mutex>
#include <memory>

#include <ostream>

namespace cpp
{

class AppendFile
{
public:
    using ptr = std::shared_ptr<AppendFile>;

    explicit AppendFile(const char* file = nullptr);
    ~AppendFile();


    void open(const char* file);

    void flush();

    template<typename T>
    AppendFile& append(T& val)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_fstream << val;
        return *this;
    }

    template<typename T>
    AppendFile& operator<<(T& val)
    {
        return append(val);
    }

private:
    std::mutex m_mutex;
    std::fstream m_fstream;
};
    
} // namespace cpp
