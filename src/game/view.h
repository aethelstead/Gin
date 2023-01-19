#ifndef VIEW_H
#define VIEW_H

#include <map>
#include <vector>
#include <string>

#include "../platform/platform.h"
#include "../renderer/renderer.h"
#include "../renderer/texture.h"
#include "world.h"
#include "camera.h"
#include "sprite.h"

struct View
{
    static View* create(World* world, Renderer* renderer);

    World* world;
    std::vector<Sprite*> sprites;
    std::map<std::string, Texture*> textures;

    View():
        world( nullptr )
    {}

    void update(int frameCount);

};

#endif
