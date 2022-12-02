#ifndef APPLICATION_H
#define APPLICATION_H

#include <SDL2/SDL.h>

struct Application
{
    static bool running;
    static SDL_Window* window;

    static bool init();
    static void quit();
    static bool start();
    static void run();
};

#endif