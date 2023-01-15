#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

#include "../platform.h"
#include "../geometry.h"
#include "../logger.h"
#include "../assets.h"
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

    Game game;
    if (!game.init(config))
        return;

    bool quit = false;
    while (!quit)
    {
        Gin::Platform::update();
        quit = game.update();
        Gin::Platform::sleep(17);
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

    context = RenderContext::open(window);
    if (!context)
    {
        Logger::log_error("Failed to open render context.");
        return false;
    }

    WorldMap* worldmap = WorldMap::open("assets/maps/untitled.tmx");
    world = World::create(worldmap, Point(config.windowDimensions.x, config.windowDimensions.y));
    view = View::create(world, context);

    return true;
}

void Game::quit()
{
    RenderContext::close(context);
    Window::close(window);
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

bool Game::update()
{
    handle_keyboard();

    world->update();
    view->update();
    
    view->render();

    return requestQuit;
}
