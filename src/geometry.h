#ifndef GEOMETRY_H
#define GEOMETRY_H

namespace Gin
{
namespace Geometry
{

    typedef unsigned int uint;
    typedef unsigned int uint32;

    struct Point
    {
        uint x;
        uint y;

        Point():
            x{ 0 },
            y{ 0 }
        {}

        Point(uint _x, uint _y):
            x{ _x },
            y{ _y }
        {}

        Point(const Point& p):
            x{ p.x },
            y{ p.y }
        {}

        bool operator == (const Point& rhs)
            { return (x == rhs.x && y == rhs.y); }
        bool operator != (const Point& rhs)
            { return (x != rhs.x || y != rhs.y); }

        Point operator + (const Point& rhs)
        {
            Point res;

            res.x = x + rhs.x;
            res.y = y + rhs.y;
            
            return res;
        }
    };

    // @TODO: Should Vec2 be its own thing?
    //typedef Point Vec2;

    struct Rect
    {
        uint x;
        uint y;
        uint w;
        uint h;

        uint left;
        uint top;
        uint right;
        uint bottom;

        Rect():
            x{ 0 },
            y{ 0 },
            w{ 0 },
            h{ 0 }
        {
            left = x;
            top = y;
            right = x + w;
            bottom = y + h;
        }

        Rect(uint _x, uint _y, uint _w, uint _h):
            x{ _x },
            y{ _y },
            w{ _w },
            h{ _h }
        {
            left = x;
            top = y;
            right = x + w;
            bottom = y + h;
        }

        Rect(Point topLeft, Point bottomRight):
            x{ topLeft.x },
            y{ topLeft.y },
            w{ bottomRight.x - topLeft.x },
            h{ bottomRight.y - topLeft.y }
        {
            left = x;
            top = y;
            right = x + w;
            bottom = y + h;
        }

        Rect(const Rect& r):
            x{ r.x },
            y{ r.y },
            w{ r.w },
            h{ r.h }
        {
            left = x;
            top = y;
            right = x + w;
            bottom = y + h;
        }

        Point top_left()
        {
            return Point(left, top);
        }
        Point top_right()
        {
            return Point(right, top);
        }
        Point bottom_left()
        {
            return Point(left, bottom);
        }
        Point bottom_right()
        {
            return Point(right, bottom);
        }

    };
}
}

#endif
