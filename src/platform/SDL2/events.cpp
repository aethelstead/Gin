#include <SDL2/SDL.h>

#include "../events.h"

using namespace Gin;
using namespace Platform;

int Gin::Platform::poll_events(Event* outEvent)
{
    SDL_Event e;
    int pollResult = SDL_PollEvent(&e);

    outEvent->type = (EventType)e.type;
    outEvent->keycode = (int)e.key.keysym.sym;

    return pollResult;
}
