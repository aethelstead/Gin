#include <iostream>
#include <SDL2/SDL.h>

#include "../gamepad.h"

using namespace Gin;
using namespace Platform;

int Gamepad::nGamepads = 0;

Gamepad* Gamepad::open()
{
    SDL_GameController* internalGamepad = SDL_GameControllerOpen(nGamepads++); // @TODO: Gamepad will have no way of knowing what its index is, is this a problem?
    if (!internalGamepad)
        return nullptr;

    Gamepad* gamepad = new Gamepad();
    gamepad->internal = internalGamepad;

    return gamepad;
}

void Gamepad::close(Gamepad* gamepad)
{
    SDL_GameControllerClose((SDL_GameController*)gamepad->internal);
    delete gamepad;
}

bool Gamepad::button_pressed(GamepadButton button)
{
    // @TODO: Implicit cast Uint8 to bool, be explicit?
    return SDL_GameControllerGetButton((SDL_GameController*)internal, (SDL_GameControllerButton)button);
}
