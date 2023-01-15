#ifndef CAMERA_H
#define CAMERA_H

#include "../geometry.h"

using namespace Gin;

struct Camera
{
    Point pos;
    Point dimensions;

    Camera():
        pos{ Point(0, 0) },
        dimensions{ Point(0, 0) }
    {}

    Camera(Point _pos, Point _dimensions):
        pos{ _pos },
        dimensions{ _dimensions }
    {}
};

#endif
