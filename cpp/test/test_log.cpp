#include "Log.h"

#include <chrono>

int main(int argc, char const *argv[])
{
    cpp::Logger::instance()->init("test.log", LLV_INFO, true, 4);

    LOG_INFO() << "hello";
    LOG_INFO() << "hello";
    LOG_INFO() << "hello";
    LOG_INFO() << "hello";
    LOG_INFO() << "hello";
    LOG_INFO() << "hello";

    LOG_FMT_INFO("fmt %s %d", "hello", 123);
    LOG_FMT_INFO("fmt %s %d", "hello", 123);
    LOG_FMT_INFO("fmt %s %d", "hello", 123);
    LOG_FMT_INFO("fmt %s %d", "hello", 123);
    LOG_FMT_INFO("fmt %s %d", "hello", 123);
    LOG_FMT_INFO("fmt %s %d", "hello", 123);


    return 0;
}
