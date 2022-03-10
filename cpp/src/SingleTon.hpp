#pragma once

namespace cpp
{


template<typename T>
class SingleTon
{
public:
    static T* instance()
    {
        static T* s_ptrInstance = new T();
        return s_ptrInstance; 
    }
};

} // namespace cpp
