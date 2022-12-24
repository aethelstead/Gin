#ifndef GAME_H
#define GAME_H

#include "entity.h"

namespace Gin
{
    struct Game
    {
        Entity* player;

        Game():
            player{ nullptr }
        {}

        ~Game()
        {}

        void init();

        void handle_keyboard();

        void update();
    };
}

#endif
