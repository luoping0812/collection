
#include "FileTool.h"

namespace utils 
{

std::string FileTool::getFileNameFromDir(const std::string& dir)
{
#ifdef WIN32
    auto beg = dir.rfind("\\") + 1;
#else
    auto beg = dir.rfind("/") + 1;
#endif
    auto end = dir.rfind(".");

    return dir.substr(beg, end-beg);
}

}