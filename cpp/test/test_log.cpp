#include "../Log.h"


int main(int argc, char const *argv[])
{
    cpp::Logger::instance()->init("test.log", LLV_INFO);

    LOG_INFO() << "hello";
    //LOG_FMT_INFO("%s", "hello");
    return 0;
}
