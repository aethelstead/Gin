#include "game.h"
#include "logger.h"
#include "keyboard.h"
#include "platform.h" // @TODO: Game shouldn't need platform

using namespace Gin;
using namespace Platform;

void Game::init()
{
    player = new Entity();
}

void Game::handle_keyboard()
{
    if (Keyboard::key_released(KeyCode::A) || Keyboard::key_released(KeyCode::D)|| Keyboard::key_released(KeyCode::S)|| Keyboard::key_released(KeyCode::W))
    {
        player->moving = false;
    }

    if (Keyboard::key_pressed(KeyCode::W))
    {
        player->moving = true;
        player->direction.x = 0;
        player->direction.y = -1;
    }
    else if (Keyboard::key_pressed(KeyCode::D))
    {
        player->moving = true;
        player->direction.x = 1;
        player->direction.y = 0;
    }
    else if (Keyboard::key_pressed(KeyCode::S))
    {
        player->moving = true;
        player->direction.x = 0;
        player->direction.y = 1;
    }
    else if (Keyboard::key_pressed(KeyCode::A))
    {
        player->moving = true;
        player->direction.x = -1;
        player->direction.y = 0;
    }

    
}

void Game::update()
{
    handle_keyboard();

    // Update player position
    int movingVal = (player->moving) ? 1 : 0;
    player->pos.x += (movingVal * player->direction.x);
    player->pos.y += (movingVal * player->direction.y);
}
