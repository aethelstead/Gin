#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <assert.h>

#include "../platform/platform.h"
#include "../geometry.h"
#include "../logger.h"
#include "../assets.h"
#include "../keyboard.h"
#include "game.h"

using namespace Gin;
using namespace Platform;

// @TODO: Only define these once
#define DIRECTION_NONE Point(0, 0)
#define DIRECTION_NORTH Point(0, -1)
#define DIRECTION_EAST Point(1, 0)
#define DIRECTION_SOUTH Point(0, 1)
#define DIRECTION_WEST Point(-1, 0)

void Game::main()
{
    Config config = Config::load();

    auto p = new Player();

    Game game;
    if (!game.init(config))
        return;

    int frameCount = 0;

    bool quit = false;
    while (!quit)
    {
        uint startTicks = ticks();

        quit = game.update(frameCount);

        const int TARGET_FPS = 60;
        const int MAX_DELAY = 1000 / TARGET_FPS;
        uint currTicks = ticks();
        int deltaTime = currTicks - startTicks;
        assert(deltaTime >= 0);
        int delay = MAX_DELAY - deltaTime;
        if (delay < 0)
            delay = 0;

        Gin::Platform::sleep(delay);
        ++frameCount;
    }

    game.quit();
}

bool Game::init(Config config)
{
    window = Window::open("Test", config.windowDimensions.x, config.windowDimensions.y);
    if (!window)
    {
        Logger::log_error("Failed to open window.");
        return false;
    }

    renderer = Renderer::open(window);
    if (!renderer)
    {
        Logger::log_error("Failed to open renderer.");
        return false;
    }

    WorldMap* worldmap = WorldMap::open("assets/maps/untitled.tmx");
    world = World::create(worldmap, Point(config.windowDimensions.x, config.windowDimensions.y));
    view = View::create(world, renderer);

    return true;
}


void Game::quit()
{
    delete renderer;
    Window::close(window);
}

void Game::handle_events()
{
    Keyboard::prevKeydownMap = Keyboard::keydownMap;

    Event e;
    while (poll_events(&e))
    {
        if (e.type == EventType::Quit)
        {
            // Handle quit
        }
        else if (e.type == EventType::Keydown)
        {
            KeyCode code = (KeyCode)e.keycode;
            Keyboard::keydownMap[code] = true;
        }
        else if (e.type == EventType::Keyup)
        {
            KeyCode code = (KeyCode)e.keycode;
            Keyboard::keydownMap[code] = false;
        }
    }
}

void Game::handle_keyboard()
{
    if (Keyboard::key_released(KeyCode::W) ||
        Keyboard::key_released(KeyCode::A) ||
        Keyboard::key_released(KeyCode::S) ||
        Keyboard::key_released(KeyCode::D))
    {
        world->player->moving = false;
    }
    if (Keyboard::key_pressed(KeyCode::Escape))
    {
        requestQuit = true;
    }
    else if (Keyboard::key_pressed(KeyCode::W))
    {
        world->player->moving = true;
        world->player->direction = DIRECTION_NORTH;
    }
    else if (Keyboard::key_pressed(KeyCode::A))
    {
        world->player->moving = true;
        world->player->direction = DIRECTION_WEST;
    }
    else if (Keyboard::key_pressed(KeyCode::S))
    {
        world->player->moving = true;
        world->player->direction = DIRECTION_SOUTH;
    }
    else if (Keyboard::key_pressed(KeyCode::D))
    {
        world->player->moving = true;
        world->player->direction = DIRECTION_EAST;
    }
}

bool Game::update(int frameCount)
{
    handle_events();

    handle_keyboard();

    world->update();
    view->update(frameCount);

    render();

    return requestQuit;
}

void Game::render()
{
    renderer->clear();

    render_tilemap();

   for (const auto sprite : view->sprites)
   {
        renderer->copy(sprite->texture, sprite->clip, sprite->view);
   }

    renderer->flip();
}

void Game::render_tilemap()
{
    Point inView;
    inView.x = world->camera->dims.x / world->tilemap->tileDims.x;
    inView.y = world->camera->dims.y / world->tilemap->tileDims.y;

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

                renderer->copy(view->textures[tileset.name], src, dst);
            }
        }
    }
}
