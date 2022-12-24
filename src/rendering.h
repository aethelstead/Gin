#ifndef RENDERER_H
#define RENDERER_H

#include "platform.h"
#include "geometry.h"

namespace Gin
{

using namespace Platform;
using namespace Geometry;

    enum class Color
    {
        Black = 0x000000,
        White = 0xffffff,
        Red = 0xff0000,
        Green = 0x00ff00,
        Blue = 0x0000ff,
        Yellow = 0xffff00,
        Magenta = 0xff00ff,
        Cyan = 0x00ffff
    };

    struct RenderContext
    {
        Surface* buffer;
        TTFont* font;

        uint clearColor;
        uint drawColor;
        uint fillColor;

        RenderContext(Point dimensions):
            clearColor{ (uint)Color::Black },
            drawColor{ (uint)Color::White },
            fillColor{ (uint)Color::Magenta },
            font{ nullptr }
        {
            buffer = Surface::create_empty(dimensions);
        }

        ~RenderContext()
        {
            close_font(font);
        }
    };

    struct Renderer
    {
        static void clear(RenderContext* context);

        static void draw_point(RenderContext* context, Point point);

        static void draw_line(RenderContext* context, Point start, Point end);

        static void draw_rect(RenderContext* context, Rect rect);

        static void draw_bitmap(RenderContext* context, Surface* bitmap);
        static void draw_bitmap(RenderContext* context, Surface* bitmap, Rect srcRect, Rect dstRect);

        static void draw_text(RenderContext* context, const char* text, Rect dest);
    };
}

#endif

