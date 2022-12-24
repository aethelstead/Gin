#include "game.h"
#include "logger.h"

using namespace Gin;

void Game::init()
{
    player = new Entity();

    //KeyBindings::add(EventType::Keydown, Keycode::W, GameCommand::MOVE_NORTH);
}

void Game::update(const GameCommand& command)
{
    handle_command(command);

    // Update player position
    int movingVal = (player->moving) ? 1 : 0;
    player->pos.x += (movingVal * player->direction.x);
    player->pos.y += (movingVal * player->direction.y);
}

void Game::handle_command(const GameCommand& command)
{
    if (command == GameCommand::PLAYER_MOVE_NORTH)
    {
        player->moving = true;
        player->direction.x = 0;
        player->direction.y = -1;
    }
    else if (command == GameCommand::PLAYER_MOVE_EAST)
    {
        player->moving = true;
        player->direction.x = 1;
        player->direction.y = 0;
    }
    else if (command == GameCommand::PLAYER_MOVE_SOUTH)
    {
        player->moving = true;
        player->direction.x = 0;
        player->direction.y = 1;
    }
    else if (command == GameCommand::PLAYER_MOVE_WEST)
    {
        player->moving = true;
        player->direction.x = -1;
        player->direction.y = 0;
    }
    else if (command == GameCommand::PLAYER_MOVE_STOP)
    {
        player->moving = false;
    }
    else if (command == GameCommand::PLAYER_ATTACK)
    {
        player->attacking = true;
    }
    else if (command == GameCommand::PLAYER_ATTACK_STOP)
    {
        player->attacking = false;
    }
}
