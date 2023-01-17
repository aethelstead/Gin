#ifndef SPRITE_H
#define SPRITE_H

#include "../geometry.h"
#include "../platform/platform.h"

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
        texture{ nullptr }
    {}
};

#endif