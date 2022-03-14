#pragma once

namespace cpp
{


template<typename T>
class Singleton
{
public:
    static T* instance()
    {
        static T* s_ptrInstance = new T();
        return s_ptrInstance; 
    }
};

} // namespace cpp
