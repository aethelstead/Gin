#ifndef FILE_H
#define FILE_H

#include <string>

namespace Gin
{
namespace Platform
{
    bool read_file(const char* filePath, std::string& outFileText);
}
}

#endif
