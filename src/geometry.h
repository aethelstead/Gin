#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <string>
 
struct Point
{
    int x;
    int y;

    Point():
        x{ 0 },
        y{ 0 }
    {}

    Point(int _x, int _y):
        x{ _x },
        y{ _y }
    {}

    Point(const Point& p):
        x{ p.x },
        y{ p.y }
    {}

    void operator = (const Point& rhs)
    {   x = rhs.x; 
        y = rhs.y;
    }

    bool operator == (const Point& rhs)
    { 
        return (x == rhs.x && y == rhs.y);
    }

    bool operator != (const Point& rhs)
    {
        return (x != rhs.x || y != rhs.y);
    }

    Point operator + (const Point& rhs)
    {
        Point res;
        res.x = x + rhs.x;
        res.y = y + rhs.y;
        
        return res;
    }

    Point operator - (const Point& rhs)
    {
        Point res;
        res.x = x - rhs.x;
        res.y = y - rhs.y;
        
        return res;
    }
};

struct Rect
{
    int x;
    int y;
    int w;
    int h;
    int left;
    int top;
    int right;
    int bottom;

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

    Rect(int _x, int _y, int _w, int _h):
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

    Rect(Point pos, Point dims):
        x{ pos.x },
        y{ pos.y },
        w{ dims.x },
        h{ dims.y }
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

#endif
