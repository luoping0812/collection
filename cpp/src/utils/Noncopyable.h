#ifndef NONCOPYABLE_H
#define NONCOPYABLE_H

namespace cpp
{

class Noncopyable
{
public:
    Noncopyable() = default;
    ~Noncopyable() = default;

private:
    Noncopyable(const Noncopyable& ) = delete;
    Noncopyable& operator=(const Noncopyable& ) = delete;
};
    
} // namespace cpp


#endif