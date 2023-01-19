#ifndef RENDERER_H
#define RENDERER_H

#include "../platform/window.h"
#include "../platform/bitmap.h"
#include "../geometry.h"
#include "texture.h"

struct Renderer
{
    static Renderer* open(Gin::Platform::Window* window);

    void* internal;

    Renderer():
        internal( nullptr )
    {}

    ~Renderer();

    void clear();

    void copy(Texture* texture, Rect srcRect, Rect dstRect);

    void flip();
};

#endif
