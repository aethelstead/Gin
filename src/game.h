#ifndef GAME_H
#define GAME_H

#include "entity.h"

namespace Gin
{
    enum class GameCommand
    {
        NONE = 0,
        PLAYER_MOVE_NORTH,
        PLAYER_MOVE_EAST,
        PLAYER_MOVE_SOUTH,
        PLAYER_MOVE_WEST,
        PLAYER_MOVE_STOP,
        PLAYER_ATTACK,
        PLAYER_ATTACK_STOP
    };

    struct Game
    {
        Entity* player;

        Game():
            player{ nullptr }
        {}

        ~Game()
        {}

        void init();

        void update(const GameCommand& command);

        void handle_command(const GameCommand& command);

    };
}

#endif
