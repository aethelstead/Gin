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
    for (const auto tileset : world->tilemap->tilesets)
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

void View::render()
{
    Renderer::clear(context);

    render_tilemap();

   for (const auto sprite : sprites)
   {
        Renderer::copy(context, sprite->texture, sprite->clip, sprite->view);
   }

    Renderer::flip(context);
}

void View::render_tilemap()
{
    Point inView;
    inView.x = world->camera->dimensions.x / world->tilemap->tileDims.x;
    inView.y = world->camera->dimensions.y / world->tilemap->tileDims.y;

    Point start;
    start.x = world->camera->pos.x / world->tilemap->tileDims.x;
    start.y = world->camera->pos.y / world->tilemap->tileDims.y;

    // Over-render by one tile if the map scrolls.
    Point end;
    end.x = (world->tilemap->mapDims.x > inView.x) ? start.x + inView.x + 1 : world->tilemap->mapDims.x;
    end.y = (world->tilemap->mapDims.y > inView.y) ? start.y + inView.y + 2 : world->tilemap->mapDims.y;

    Tileset firstTileset = world->tilemap->tilesets[0];
    Rect src(Point(0, 0), firstTileset.tileDims);
    Rect dst(Point(0, 0), world->tilemap->tileDims);

    for (const auto& layer : world->tilemap->layers)
    {
        for (int y = start.y; y < end.y; y++)
        {
            for (int x = start.x; x < end.x; x++)
            {
                int tileIdx = (y * world->tilemap->mapDims.x) + x;
                int tileVal = layer.tiles[tileIdx];

                if (tileVal < 0)
                    continue;

                // Find the tileset to use
                Tileset tileset = firstTileset;
                for (const auto& ts : world->tilemap->tilesets)
                {
                    if (tileVal < ts.firstTileId)
                        break;

                    tileset = ts;
                }

                src.x = ((tileVal - tileset.firstTileId) % tileset.dims.x) * tileset.tileDims.x;
                src.y = ((tileVal - tileset.firstTileId) / tileset.dims.y) * tileset.tileDims.y;

                dst.x = (x * world->tilemap->tileDims.x) - world->camera->pos.x;
                dst.y = (y * world->tilemap->tileDims.y) - world->camera->pos.y;

                Renderer::copy(context, textures[tileset.name], src, dst);
            }
        }
    }
}
