#include "Log.h"


using namespace cpp;

int main(int argc, char const *argv[])
{
    cpp::Logger::instance()->init("test.log", LLV_INFO, true, 4);

    LOG_INFO() << "hello";
    LOG_INFO() << "hello";
    LOG_INFO() << "hello";
    LOG_INFO() << "hello";
    LOG_INFO() << "hello";
    LOG_INFO() << "hello";

    LOG_FMT_LEVEL(LLV_INFO, "123 %d", 10);
    LOG_FMT_INFO("fmt %s %d", "hello", 123);
    LOG_FMT_INFO("fmt %s %d", "hello", 123);
    LOG_FMT_INFO("fmt %s %d", "hello", 123);
    LOG_FMT_INFO("fmt %s %d", "hello", 123);
    LOG_FMT_INFO("fmt %s %d", "hello", 123);
    LOG_FMT_INFO("fmt %s %d", "hello", 123);

    return 0;
}
