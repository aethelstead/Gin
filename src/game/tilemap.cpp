#include "tilemap.h"

std::vector<Rect> Tilemap::collideables(Rect bounds)
{
    // @TODO: Check bounds isnt too big
    // @TODO: Make it possible to omit bounds parameter and return whole tilemap

    Point inView;
    inView.x = bounds.w / tileDims.x;
    inView.y = bounds.h / tileDims.y;

    Point start;
    start.x = bounds.x / tileDims.x;
    start.y = bounds.y / tileDims.y;

    Point end;
    end.x = (mapDims.x > inView.x) ? start.x + inView.x : mapDims.x;
    end.y = (mapDims.y > inView.y) ? start.y + inView.y : mapDims.y;

    // List of all types of tile that its possible to collide with
    std::vector<int> collTileIds;
    for (const auto& tileset : tilesets)
    {
        for (const auto& kvp : tileset.collideablesMap)
        {
            int tileId = kvp.first;
            auto tileColls = kvp.second;
            for (const auto& tileColl : tileColls)
            {
                collTileIds.push_back(tileId);
            }
        }
    }

    std::vector<Rect> colls;

    for (const auto& layer : layers)
    {
        for (int y = start.y; y < end.y; y++)
        {
            for (int x = start.x; x < end.x; x++)
            {
                int tileIdx = (y * mapDims.x) + x;
                int tileVal = layer.tiles[tileIdx] - 1;

                for (const auto& collTileId : collTileIds)
                {
                    if (tileVal == collTileId)
                    {
                        Rect r;
                        r.x = (x * tileDims.x);
                        r.y = (y * tileDims.y);
                        r.w = tileDims.x;
                        r.h = tileDims.y;

                        colls.push_back(r);
                    }
                }
            }
        }
    }

    return colls;
}
