#ifndef GIN_H
#define GIN_H

#include <map>

#include "platform.h"
#include "logger.h"
#include "rendering.h"
#include "game.h"

const int TARGET_FPS = 60;

namespace Gin
{
    struct Gin
    {
        static Gin* instance;

        static bool start();

        bool running;

        Platform::Window* window;
        Logger* logger;
        RenderContext* renderContext;
        Game* game;

        uint fps;
        uint frames;

        Gin() :
            running{ false },
            window{ nullptr },
            logger{ nullptr },
            renderContext{ nullptr },
            game{ nullptr },
            fps{ 0 },
            frames{ 0 }
        {}

        bool init();
        void quit();
        void run();

        void handle_keyboard();

        void update();
        void render(); 

    };

}

#endif
