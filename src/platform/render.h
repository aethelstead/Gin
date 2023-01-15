#ifndef RENDER_H
#define RENDER_H

#include "../geometry.h"
#include "window.h"
#include "bitmap.h"

namespace Gin
{
namespace Platform
{
    struct RenderContext
    {
        static RenderContext* open(Window* window);
        static void close(RenderContext* context);

        void* internal;

        RenderContext():
            internal{ nullptr }
        {}
    };

    struct Texture
    {
        // Opens an empty texture.
        static Texture* open(RenderContext* context, Point dimensions);
        // Opens a texture from a bitmap
        static Texture* open(RenderContext* context, Bitmap* bitmap);
        // Opens a texture from an image file.
        static Texture* open(RenderContext* context, const char* path);
        static void close(Texture* texture);

        void* internal;

        Texture():
            internal{ nullptr }
        {}
    };

    struct Renderer
    {
        static void clear(RenderContext* context);
        // Copies the texture into the render context.
        static void copy(RenderContext* context, Texture* texture, Rect srcRect, Rect dstRect);
        // Copies the srcTexture to the dstTexture.
        //static void copy(RenderContext* context, Texture* srcTexture, Texture* dstTexture, Rect srcRect, Rect dstRect);
        static void flip(RenderContext* context);
    };
}
}

#endif
