#ifndef TILEMAP_H
#define TILEMAP_H

#include <map>
#include <string>
#include <vector>

#include "../geometry.h"
#include "../platform/platform.h"

using namespace Gin;
using namespace Platform;

struct TileAnimFrame
{
    int tileId;
    int duration;   // The duration this anim frame will be shown for before next frame (in milliseconds).

    TileAnimFrame():
        tileId{ 0 },
        duration{ 0 }
    {}
};

struct Tileset
{
    int firstTileId;
    Point dims;
    Point tileDims;
    std::string name;
    std::map<int, std::vector<Rect>> collideablesMap;
    // Map of the ID of the tile to its tile animation frames (itself included).
    std::map<int, std::vector<TileAnimFrame>> animationsMap;

    Tileset():
        firstTileId{ 0 }
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

    Tilemap()
    {}

    Tilemap(Point mapDims, Point tileDims, std::vector<Tileset> tilesets, std::vector<TilemapLayer> layers):
        mapDims{ mapDims },
        tileDims{ tileDims },
        tilesets{ tilesets },
        layers{ layers }
    {
    }

    ~Tilemap()
    {}

    // Returns a copy of the tilemap that is clipped to the bounds.
    void clip(Tilemap& outTilemap, Rect bounds);

    // Returns a list of all the solid/ collideable tiles in the tilemap.
    std::vector<Rect> solid_tiles();
};

#endif
