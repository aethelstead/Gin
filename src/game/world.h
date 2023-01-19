#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include "../platform/platform.h"
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

    WorldMap()
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
        camera( nullptr ),
        player( nullptr )
    {}

    std::vector<Entity*> entities();

    void update();
};

#endif
