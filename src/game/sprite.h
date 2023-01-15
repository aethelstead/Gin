#ifndef SPRITE_H
#define SPRITE_H

#include "../geometry.h"
#include "../platform.h"

using namespace Gin;
using namespace Platform;

struct Sprite
{
    int entityId;
    Rect view;
    Rect clip;
    Texture* texture;

    Sprite():
        entityId{ 0 },
        clip{ Rect(0, 0, 0, 0) },
        view{ Rect(0, 0, 0, 0) },
        texture{ nullptr }
    {}
};

#endif