#ifndef ENTITY_H
#define ENTITY_H

#include <string>

#include "../geometry.h"
#include "tilemap.h"

struct Entity
{
    static Entity* create(Point pos, Point dims, std::string& archetype);

    int id;
    bool moving;
    Point pos;
    Point dims;
    Point direction;
    std::string archetype;

    Entity():
        moving{ false },
        pos{ Point(0, 0) },
        dims{ Point(0, 0) },
        direction{ Point(0, 0) },
        archetype{ std::string() }
    {}

    Rect rect()
    {
        return Rect(pos, dims);
    }
};

#endif
