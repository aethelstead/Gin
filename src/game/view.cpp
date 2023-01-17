#include <algorithm>

#include "../assets.h"
#include "view.h"

using namespace Gin;
using namespace Platform;

View* View::create(World* world, RenderContext* context)
{
    View* view = new View();

    view->context = context;
    view->world = world;

    // Load texture for each tileset
    for (const auto tileset : world->tilemap.tilesets)
    {
        Bitmap* bitmap = Assets::bitmaps[tileset.name];
        view->textures[tileset.name] = Texture::open(context, bitmap);
    }

    for (const auto entity : world->entities())
    {
        Sprite* sprite = new Sprite();
        sprite->entityId = entity->id;
        sprite->texture = view->textures[entity->archetype];
        
        // @TODO: Use tmxparser and do this properly
        if  (entity->archetype == "player")
        {
            sprite->clip = Rect(0, 0, 32, 32);
        }
        else if (entity->archetype == "slime")
        {
            sprite->clip = Rect(0, 0, 16, 16);
        }
        

        Point viewPos = entity->pos - world->camera->pos;
        sprite->view = Rect(viewPos, entity->dims);

        view->sprites.push_back(sprite);
    }

    return view;
}

void View::update()
{
    // @TODO: Doesn't cache sprites that have been added to the world since init.
    for (const auto sprite : sprites)
    {
        for (const auto entity : world->entities())
        {
            if (entity->id == sprite->entityId)
            {
                Point viewPos = entity->pos - world->camera->pos;
                sprite->view.x = viewPos.x;
                sprite->view.y = viewPos.y;
            }
        }
    }
}
