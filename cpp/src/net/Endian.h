
#ifndef ENDIAN_H
#define ENDIAN_H

#include <stdint.h>

namespace net 
{

enum class EEndian 
{
    ENDIAN_BIG,
    ENDIAN_LITTLE,
};

class Endian
{
public:
    static EEndian getHostEndian();

    static uint16_t hton(uint16_t val);
    static uint32_t hton(uint32_t val);
    static uint16_t ntoh(uint16_t val);
    static uint32_t ntoh(uint32_t val);
};



} // namespace net 


#endif