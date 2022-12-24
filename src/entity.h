#ifndef ENTITY_H
#define ENTITY_H

#include "geometry.h"

namespace Gin
{
    using namespace Geometry;

    struct Entity
    {
        Point pos;
        Point direction;
        bool moving;
        bool attacking;

        Entity():
            pos{ Point(0, 0) },
            direction{ Point(0, 1) }, // Face south by default
            moving{ false },
            attacking{ false }
        {}
    };
}

#endif
