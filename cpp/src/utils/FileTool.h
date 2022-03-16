#ifndef FILETOOL_H
#define FILETOOL_H


#include <string>

namespace utils 
{

class FileTool
{
public:
    static std::string getFileNameFromDir(const std::string& dir);

};

}

#endif