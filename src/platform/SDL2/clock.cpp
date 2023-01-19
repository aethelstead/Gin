#include <SDL2/SDL.h>

#include "../clock.h"

void Gin::Platform::sleep(uint milliseconds)
{
    SDL_Delay(milliseconds);
}

uint Gin::Platform::ticks()
{
    return SDL_GetTicks();
}
