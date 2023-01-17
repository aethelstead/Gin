#include <iostream>
#include <map>
#include <cmath>
#include <Tmx.h>

#include "../geometry.h"
#include "../assets.h"
#include "world.h"

#define DIRECTION_NONE Point(0, 0)
#define DIRECTION_NORTH Point(0, -1)
#define DIRECTION_EAST Point(1, 0)
#define DIRECTION_SOUTH Point(0, 1)
#define DIRECTION_WEST Point(-1, 0)

WorldMap* WorldMap::open(const char* path)
{
    // @TODO: Tilesets must be located under maps/ folder for this to work.
    Tmx::Map* tmxMap = new Tmx::Map();
    tmxMap->ParseFile(path);

    if (tmxMap->HasError())
        return nullptr;
        
    WorldMap* worldmap = new WorldMap();

    worldmap->mapDims = Point(tmxMap->GetWidth(), tmxMap->GetHeight());
    worldmap->tileDims = Point(tmxMap->GetTileWidth(), tmxMap->GetTileHeight());
    
    // Load TSX tilesets into worldmap tilesets.
    for (const auto tsx : tmxMap->GetTilesets())
    {
        Tileset tileset;
        tileset.name = tsx->GetName();
        // @TODO: Should tileset dims be replaced by columns and nTiles?
        tileset.dims.x = tsx->GetTileCount() / tsx->GetColumns();
        tileset.dims.y = tsx->GetColumns();
        tileset.firstTileId = tsx->GetFirstGid();
        tileset.tileDims = Point(tsx->GetTileWidth(), tsx->GetTileHeight());

        for (const auto& tile : tsx->GetTiles())
        {
            if (tile->IsAnimated())
            {
                std::vector<TileAnimFrame> frames;
                for (const auto tmxFrame : tile->GetFrames())
                {
                    TileAnimFrame frame;
                    frame.tileId = tmxFrame.GetTileID();
                    frame.duration = tmxFrame.GetDuration();

                    frames.push_back(frame);
                }
                tileset.animationsMap[ tile->GetId() ] = frames;
            }

            // Tile is collideable if it has objects
            std::vector<Rect> collideables;
            if (tile->HasObjects())
            {
                for (const auto& obj : tile->GetObjects())
                {
                    Rect r;
                    r.x = obj->GetX();
                    r.y = obj->GetY();
                    r.w = obj->GetWidth();
                    r.h = obj->GetHeight();

                    collideables.push_back(r);
                }
            }

            tileset.collideablesMap[ tile->GetId() ] = collideables;
        }

        Assets::bitmaps[tileset.name] = Bitmap::open(tsx->GetImage()->GetSource().c_str());

        worldmap->tilesets.push_back(tileset);
    }

    int nTiles = worldmap->mapDims.x * worldmap->mapDims.y;

    // Load TMX layers into worldmap layers.
    for (const auto tmxLayer : tmxMap->GetTileLayers())
    {
        TilemapLayer layer;
        layer.tiles = (int*)calloc(nTiles, sizeof(int));
        for (int i = 0; i < nTiles; ++i)
        {
            layer.tiles[i] = tmxLayer->GetTile(i).gid;
        }

        worldmap->layers.push_back(layer);
    }

    
    static int nextId = 0; // @TODO: Remove
    for (const auto obj : tmxMap->GetObjectGroup(0)->GetObjects())  // @TODO: Hardcoded to first object group for entities
    {
        Entity entity;
        entity.id = ++nextId;
        entity.pos = Point(obj->GetX(), obj->GetY());
        entity.dims = Point(obj->GetWidth(), obj->GetHeight());
        
        // Get archetype property for each entity.
        auto propset = obj->GetProperties();
        entity.archetype = propset.GetStringProperty("archetype");

        worldmap->entities.push_back(entity);
    }

    delete tmxMap;

    return worldmap;
}

World* World::create(WorldMap* worldmap, Point viewDims)
{
    World* world = new World();

    world->tilemap = Tilemap(worldmap->mapDims, worldmap->tileDims, worldmap->tilesets, worldmap->layers);
    world->camera = new Camera(Point(0, 0), viewDims);
    world->npcs = std::vector<NPC*>();

    for (auto mapEntity : worldmap->entities)
    {
        if (mapEntity.archetype == "player")
        {
            world->player = new Player();
            world->player->pos = mapEntity.pos;
            world->player->dims = mapEntity.dims;
            world->player->archetype = mapEntity.archetype;
        }
        else
        {
            NPC* npc = new NPC();
            npc->pos = mapEntity.pos;
            npc->dims = mapEntity.dims;
            npc->archetype = mapEntity.archetype;
            world->npcs.push_back(npc);
        }
    }

    return world;
}

std::vector<Entity*> World::entities()
{
    std::vector<Entity*> ents;
    ents.push_back(player);

    for (const auto npc : npcs)
    {
        ents.push_back(npc);
    }

    return ents;
}

void World::update()
{
    Point mapDimensions;
    mapDimensions.x = tilemap.mapDims.x * tilemap.tileDims.x;
    mapDimensions.y = tilemap.mapDims.y * tilemap.tileDims.y;

    // Check for player out of bounds
    Point collideDirection = DIRECTION_NONE;
    if (player->pos.x < 0)
        collideDirection = DIRECTION_WEST;
    else if (player->pos.y < 0)
        collideDirection = DIRECTION_NORTH;
    else if (player->pos.x + player->dims.x > mapDimensions.x)
        collideDirection = DIRECTION_EAST; 
    else if (player->pos.y + player->dims.y > mapDimensions.y)
        collideDirection = DIRECTION_SOUTH;

    // Get the ID of the tile the player is standing on.
    Point playerTile;
    playerTile.x = player->pos.x / tilemap.tileDims.x;
    playerTile.y = player->pos.y / tilemap.tileDims.y;
    int playerTileIdx = (playerTile.y * tilemap.mapDims.x) + playerTile.x;

    // Get the tiles to the N-E-S-W of the player
    int north = playerTileIdx - tilemap.mapDims.x;
    int east = playerTileIdx + 1;
    int south = playerTileIdx + tilemap.mapDims.x;
    int west = playerTileIdx - 1;

    std::vector<Rect> collideables = tilemap.collideables(Rect(camera->pos, camera->dimensions));

    // Add every NPC to the list of collideables
    for (const auto& npc : npcs)
    {
        collideables.push_back(npc->rect());
    }

    for (const auto& coll : collideables)
    {
        Rect a = player->rect();
        Rect b = coll;
        bool collision = (a.left() < b.right() && a.right() > b.left() && a.top() < b.bottom() && a.bottom() > b.top());
        if (collision)
        {
            Point c;
            c.x = a.left() - b.left();
            c.y = a.top() - b.top();

            if (std::abs(c.x) > std::abs(c.y))
            {
                if (c.x < 0)
                {
                    collideDirection = DIRECTION_EAST;
                }
                else if (c.x > 0)
                {
                    collideDirection = DIRECTION_WEST;
                }
            }
            else
            {
                if (c.y < 0)
                {
                    collideDirection = DIRECTION_SOUTH;
                }
                else if (c.y > 0)
                {
                    collideDirection = DIRECTION_NORTH;
                }
            }
        }
    }

    int movingVal = (player->moving) ? 1 : 0;
    if (player->direction != collideDirection)
    {
        player->pos.x += (movingVal * player->direction.x);
        player->pos.y += (movingVal * player->direction.y);
    }

    // Update camera world pos
    Point halfView;
    halfView.x = (camera->dimensions.x / 2);
    halfView.y = (camera->dimensions.y / 2);
    if (player->pos.x > halfView.x && player->pos.x < mapDimensions.x - halfView.x)
    {
        camera->pos.x = player->pos.x - halfView.x;
    }
    if (player->pos.y > halfView.y && player->pos.y < mapDimensions.y - halfView.y)
    {
        camera->pos.y = player->pos.y - halfView.y;
    }
}
