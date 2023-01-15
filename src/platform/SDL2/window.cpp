#include <SDL2/SDL.h>
#include "../window.h"

using namespace Gin;
using namespace Platform;

Window* Window::open(const char* title, int width, int height)
{   
    SDL_Window* internalWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (!internalWindow)
        return nullptr;

    Window* window = new Window();
    window->internal = internalWindow;

    return window;
}

void Window::close(Window* window)
{
    SDL_Window* internalWindow = static_cast<SDL_Window*>(window->internal);
    SDL_DestroyWindow(internalWindow);
    delete window;
}
