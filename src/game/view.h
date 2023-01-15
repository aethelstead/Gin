#ifndef VIEW_H
#define VIEW_H

#include <map>
#include <vector>
#include <string>

#include "../platform.h"
#include "world.h"
#include "camera.h"
#include "sprite.h"

struct View
{
    static View* create(World* world, RenderContext* context);

    // @TODO: Should the view hold the renderContext?
    RenderContext* context;
    World* world;
    std::vector<Sprite*> sprites;
    std::map<std::string, Gin::Platform::Texture*> textures;

    View():
        context( nullptr ),
        world( nullptr ),
        sprites{ std::vector<Sprite*>() },
        textures{ std::map<std::string, Gin::Platform::Texture*>() }
    {}

    void update();

    void render();
    void render_tilemap();

};

#endif
