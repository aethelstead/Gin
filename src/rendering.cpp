#include "rendering.h"

using namespace Gin;
using namespace Platform;
using namespace Geometry;

void Renderer::clear(RenderContext* context)
{
    int N_PIXELS = context->buffer->dimensions.x * context->buffer->dimensions.y;
    int i = 0;
    while (i < N_PIXELS)
    {
        context->buffer->pixels[i] = context->clearColor;
        ++i;
    }
}

void Renderer::draw_point(RenderContext* context, Point point)
{
    context->buffer->pixels[point.x + (point.y * context->buffer->dimensions.x)] = context->drawColor;
}

void Renderer::draw_line(RenderContext* context, Point start, Point end)
{
    // Uses bresenham's line-drawing algorithm.
    int x1 = start.x; int x2 = end.x;
    int y1 = start.y; int y2 = end.y;

    int dx = abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
    int dy = abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2, e2;

    for (;;)
    {
        draw_point(context, Point(x1, y1));
        if ((x1 == x2) && (y1 == y2))
        {
            break;
        }

        e2 = err;

        if (e2 > -dx)
        {
            err -= dy;
            x1 += sx;
        }

        if (e2 < dy)
        {
            err += dx;
            y1 += sy;
        }
    }
}

#include <iostream>

void Renderer::draw_rect(RenderContext* context, Rect rect)
{
    const Point START = Point(rect.x, rect.y);//rect.top_left();
    const Point END = Point(rect.x + rect.w, rect.y + rect.h);//rect.bottom_right();

    std::cout << START.x << START.y << "\n";
    std::cout << END.x << END.y << "\n";

    Point p = START;

    bool ON_TOP_LINE = (p.y == START.y);
    bool ON_BOTTOM_LINE = (p.y == END.y);
    bool END_OF_ROW = (p.x >= END.x);

    while (p != END)
    {
        ON_TOP_LINE = (p.y == START.y);
        ON_BOTTOM_LINE = (p.y == END.y);
        END_OF_ROW = (p.x >= END.x);

        if (ON_TOP_LINE)
        {
            draw_point(context, p);
            ++p.x;

            if (END_OF_ROW)
            {
                p.x = START.x;
                ++p.y;
            }
        }
        else if (ON_BOTTOM_LINE)
        {
            std::cout << "L";
            draw_point(context, p);
            ++p.x;
        }
        else
        {
            p.x = START.x;
            draw_point(context, p);
            p.x = END.x;
            draw_point(context, p);

            ++p.y;

            if (ON_BOTTOM_LINE)
            {
                draw_point(context, p);
                p.x = START.x;
            }
        }
    }
}

void Renderer::draw_bitmap(RenderContext* context, Surface* bitmap)
{
    blit(bitmap, context->buffer);
}

void Renderer::draw_bitmap(RenderContext* context, Surface* bitmap, Rect srcRect, Rect dstRect)
{
    blit(bitmap, context->buffer, srcRect, dstRect);
}
