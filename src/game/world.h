#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include "../platform/render.h"
#include "tilemap.h"
#include "camera.h"
#include "player.h"
#include "npc.h"

struct WorldMap
{
    static WorldMap* open(const char* path);

    Point mapDims;
    Point tileDims;
    std::vector<TilemapLayer> layers;
    std::vector<Tileset> tilesets;
    std::vector<Entity> entities; 

    WorldMap():
        mapDims{ Point(0, 0) },
        tileDims( Point(0, 0) ),
        layers{ std::vector<TilemapLayer>() },
        tilesets{ std::vector<Tileset>() },
        entities{ std::vector<Entity>() }
    {}
};

struct World
{
    static World* create(WorldMap* worldmap, Point viewDims);

    Tilemap* tilemap;
    Camera* camera;
    Player* player;
    std::vector<NPC*> npcs;

    World():
        tilemap( nullptr ),
        camera( nullptr ),
        player( nullptr )
    {}

    std::vector<Entity*> entities();

    void update();
};

#endif
