#ifndef SINGLETON_H
#define SINGLETON_H


namespace utils
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

} // namespace utils

#endif