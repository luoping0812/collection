#include "Endian.h"

#include "arpa/inet.h"

namespace net
{

EEndian Endian::getHostEndian()
{
    uint32_t x = 0x12345678;
    char *c = (char*)&x;
    return *c == 0x78 ? EEndian::ENDIAN_LITTLE : EEndian::ENDIAN_BIG;
}

uint16_t Endian::hton(uint16_t val)
{
    return ::htons(val); 
}

uint32_t Endian::hton(uint32_t val)
{
    return ::htonl(val);
}

uint16_t Endian::ntoh(uint16_t val)
{
    return ::ntohs(val);
}

uint32_t Endian::ntoh(uint32_t val)
{
    return ::ntohl(val);
}

} // namespace net
