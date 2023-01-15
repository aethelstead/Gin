#ifndef TILEMAP_H
#define TILEMAP_H

#include <string>
#include <vector>

#include "../geometry.h"
#include "../platform.h"

using namespace Gin;
using namespace Platform;

struct Tileset
{
    int firstTileId;
    Point dims;
    Point tileDims;
    std::string name;

    Tileset():
        firstTileId{ 0 },
        dims{ Point(0, 0) },
        tileDims{ Point(0, 0) }
    {}
};

struct TilemapLayer
{
    int* tiles;

    TilemapLayer():
        tiles{ nullptr }
    {}
};

struct Tilemap
{
    Point mapDims;
    Point tileDims;
    std::vector<TilemapLayer> layers;
    std::vector<Tileset> tilesets;

    Tilemap():
        mapDims{ Point(0, 0) },
        tileDims{ Point(0, 0) }/*,
        layers{ nullptr },
        tilesets{ nullptr }*/
    {}

    Tilemap(Point mapDims, Point tileDims, std::vector<Tileset> tilesets, std::vector<TilemapLayer> layers):
        mapDims{ mapDims },
        tileDims{ tileDims },
        tilesets{ std::vector<Tileset>(tilesets) },
        layers{ std::vector<TilemapLayer>(layers) }
    {
    }

    ~Tilemap()
    {}

    
};

#endif
