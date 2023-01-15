#ifndef BITMAP_H
#define BITMAP_H

#include "../geometry.h"

typedef unsigned int uint;

namespace Gin
{
namespace Platform
{
    struct Bitmap
    {
        static Bitmap* open(const char* path);

        Point dimensions;
        uint* pixels;
        void* internal;

        Bitmap()
        {}

        ~Bitmap();
    };
}
}

#endif
