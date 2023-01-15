#include <SDL2/SDL.h>
#include "../../platform.h"
#include "../../geometry.h"

void Gin::Platform::sleep(int milliseconds)
{
    SDL_Delay(milliseconds);
}

int Gin::Platform::ticks()
{
    return SDL_GetTicks();
}

void Gin::Platform::update()
{
    Keyboard::prevKeydownMap = Keyboard::keydownMap;
    Mouse::prevPos = Mouse::pos;
    Mouse::prevLeftButtonDown = Mouse::leftButtonDown;
    Mouse::prevRightButtonDown = Mouse::rightButtonDown;

    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            // Handle quit
        }
        else if (e.type == SDL_KEYDOWN)
        {
            KeyCode code = (KeyCode)e.key.keysym.sym;
            Keyboard::keydownMap[code] = true;
        }
        else if (e.type == SDL_KEYUP)
        {
            KeyCode code = (KeyCode)e.key.keysym.sym;
            Keyboard::keydownMap[code] = false;
        }
        else if (e.type == SDL_MOUSEMOTION)
        {
            Mouse::pos = Point(e.motion.x, e. motion.y);
        }
        else if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            if (e.button.button == SDL_BUTTON_LEFT)
            {
                Mouse::leftButtonDown = true;
            }
            else if (e.button.button == SDL_BUTTON_RIGHT)
            {
                Mouse::rightButtonDown = true;
            }
        }
        else if (e.type == SDL_MOUSEBUTTONUP)
        {
            if (e.button.button == SDL_BUTTON_LEFT)
            {
                Mouse::leftButtonDown = false;
            }
            else if (e.button.button == SDL_BUTTON_RIGHT)
            {
                Mouse::rightButtonDown = false;
            }
        }
    }
}
