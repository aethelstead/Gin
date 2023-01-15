#ifdef __WIN32
#define SDL_MAIN_HANDLED
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "../../platform.h"
#include "../../game/game.h"

int main(int argc, char* argv[])
{

    // @TODO: Might not be necessary to init EVERYTHING
    if (SDL_Init( SDL_INIT_EVERYTHING ) != 0)
        return 1;
    if (IMG_Init( IMG_INIT_PNG | IMG_INIT_WEBP ) == 0)
        return 1;
    if (Mix_Init( MIX_INIT_MP3 ) == 0)
        return 1;

    Game::main();

    Mix_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}
