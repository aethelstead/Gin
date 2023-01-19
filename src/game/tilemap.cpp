#include "tilemap.h"

void Tilemap::clip(Tilemap& outTilemap, Rect bounds)
{
    // @TODO: Check bounds isnt too big
    // @TODO: Make it possible to omit bounds parameter and return whole tilemap?

    Point inView;
    inView.x = bounds.w / tileDims.x;
    inView.y = bounds.h / tileDims.y;

    Point start;
    start.x = bounds.x / tileDims.x;
    start.y = bounds.y / tileDims.y;

    Point end;
    end.x = (mapDims.x > inView.x) ? start.x + inView.x : mapDims.x;
    end.y = (mapDims.y > inView.y) ? start.y + inView.y : mapDims.y;

    outTilemap.mapDims.x = end.x - start.x;
    outTilemap.mapDims.y = end.y - start.y;
    outTilemap.tileDims = tileDims;
    outTilemap.tilesets = tilesets;

    int nTiles = mapDims.x * mapDims.y;

    int clipTileIdx = 0;
    for (const auto& layer : layers)
    {
        TilemapLayer clipLayer;
        clipLayer.tiles = (int*)calloc(nTiles, sizeof(int));

        for (int y = start.y; y < end.y; y++)
        {
            for (int x = start.x; x < end.x; x++)
            {
                int tileIdx = (y * mapDims.x) + x;
                int tileVal = layer.tiles[tileIdx];     // @TODO: Need to -1 here?

                clipLayer.tiles[++clipTileIdx] = tileVal;
            }
        }

        outTilemap.layers.push_back(clipLayer);
    }
}
