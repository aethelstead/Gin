#ifndef GIN_H
#define GIN_H

#include <map>

#include "platform.h"
#include "logger.h"
#include "rendering.h"
#include "game.h"

namespace Gin
{
    struct Gin
    {
        static Gin* instance;

        static bool start();

        bool running;

        std::map<Platform::KeyCode, bool> keydownMap;
        std::map<Platform::KeyCode, bool> prevKeydownMap;

        Platform::Window* window;
        Logger* logger;
        RenderContext* renderContext;
        Game* game;

        Gin() :
            running{ false },
            window{ nullptr },
            logger{ nullptr },
            renderContext{ nullptr },
            game{ nullptr }
        {}

        bool init();
        void quit();
        void run();

        void handle_keyboard(GameCommand& command);

        void update();
        void render(); 

    };

}

#endif
