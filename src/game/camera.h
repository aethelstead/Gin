#ifndef CAMERA_H
#define CAMERA_H

#include "../geometry.h"

using namespace Gin;

struct Camera
{
    Point pos;
    Point dimensions;

    Camera()
    {}

    Camera(Point _pos, Point _dimensions):
        pos{ _pos },
        dimensions{ _dimensions }
    {}
};

#endif
