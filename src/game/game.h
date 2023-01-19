#ifndef GAME_H
#define GAME_H

#include <vector>

#include "../platform/platform.h"
#include "../renderer/renderer.h"
#include "tilemap.h"
#include "config.h"
#include "world.h"
#include "view.h"

struct Game
{
    static void main();

    bool requestQuit;                  // Set to true to signal to the caller of Game::update that its time to quit.
    Gin::Platform::Window* window;
    Renderer* renderer;
    World* world;
    View* view;

    Game():
        requestQuit{ false },
        window{ nullptr },
        renderer{ nullptr },
        world{ nullptr },
        view{ nullptr }
    {}

    bool init(Config config);

    void quit();

    void handle_events();
    void handle_keyboard();

    bool update(int frameCount);

    void render();
    void render_tilemap(Tilemap& tilemap);
};

#endif
