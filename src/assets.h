#ifndef ASSETS_H
#define ASSETS_H

#include <map>
#include <string>

#include "platform.h"

struct Assets
{
    static std::map<std::string, Gin::Platform::Bitmap*> bitmaps;
};

#endif
