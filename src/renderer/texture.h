#ifndef TEXTURE_H
#define TEXTURE_H

#include "../platform/bitmap.h"

struct Texture
{
    static void* internalRenderer;

    static Texture* open(Gin::Platform::Bitmap* bitmap);

    void* internal;

    Texture():
        internal{ nullptr }
    {}

    ~Texture();
};

#endif
