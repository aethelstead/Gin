#ifndef CAMERA_H
#define CAMERA_H

#include "../geometry.h"

using namespace Gin;

struct Camera
{
    Point pos;
    Point dims;

    Camera()
    {}

    Camera(Point _pos, Point _dimensions):
        pos{ _pos },
        dims{ _dimensions }
    {}

    Rect viewport()
    {
        return Rect(pos, dims);
    }
};

#endif
