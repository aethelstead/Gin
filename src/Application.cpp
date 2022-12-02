#include <iostream>

#include "Application.h"
#include "Logger.h"

bool Application::running = false;
SDL_Window* Application::window = NULL;

bool Application::init()
{
    // Init SDL.
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        Logger::log_error("Failed to init SDL.");
        return false;
    }

    // Create Window.
    window = SDL_CreateWindow("Gin Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
    window = NULL;
    if (!window)
    {
        Logger::log_error("Failed to get window.");
        return false;
    }

    return true;
}

void Application::quit()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Application::start()
{
    if (!init())
    {
        return false;
    }

    run();

    quit();

    return true;
}

void Application::run()
{
    running = true;

    SDL_Event e;
    while(running)
    {
        SDL_Delay(5000);
        running = false;
    }
}
