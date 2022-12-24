#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "platform.h"

namespace Gin
{
namespace Platform
{
    Surface* Surface::create_empty(Point dims)
    {
        Surface* surface = new Surface(dims);

        const int BPP = 32;
        SDL_Surface* internalSurface = SDL_CreateRGBSurface(0, dims.x, dims.y, BPP, 0, 0, 0, 0);
        surface->internal = internalSurface;
        surface->pixels = static_cast<uint*>(internalSurface->pixels);

        return surface;
    }

    Surface::~Surface()
    {
        SDL_Surface* srfc = (SDL_Surface*)internal;
        SDL_FreeSurface(srfc);
    }
    
    Window::~Window()
    {
        SDL_Window* wnd = static_cast<SDL_Window*>(internal);
        SDL_DestroyWindow(wnd);
    }

    void Window::swap_buffers()
    {
        SDL_Window* wnd = static_cast<SDL_Window*>(internal);
        SDL_UpdateWindowSurface(wnd);
    }

    bool init()
    {
        // @TODO: Check for errors in each subsys init and log from here.
        bool sdlOk = (SDL_Init( SDL_INIT_EVERYTHING ) == 0) ? true : false;
        bool ttfOk = (TTF_Init() == 0) ? true : false;
        bool imgOk = (IMG_Init( IMG_INIT_PNG | IMG_INIT_WEBP ) != 0) ? true : false;
        bool mixOk = (Mix_Init( MIX_INIT_MP3 ) != 0) ? true : false;
        return (sdlOk && ttfOk && imgOk && mixOk);
    }

    void quit()
    {
        Mix_Quit();
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();
    }

    Window* open_window(const char* title, int width, int height)
    {   
        SDL_Window* sdlWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
        if (!sdlWindow)
        {
            return nullptr;
        }

        // Create window
        Window* window = new Window();
        window->internal = sdlWindow;

        // Get window BackBuffer
        Surface* backBuffer = new Surface();
        backBuffer->internal = SDL_GetWindowSurface(sdlWindow);
        SDL_Surface* internalSurface = static_cast<SDL_Surface*>(backBuffer->internal);
        backBuffer->pixels = static_cast<uint32*>(internalSurface->pixels);
        backBuffer->dimensions = Point(width, height);
        window->backBuffer = backBuffer;

        return window;
    }

    void close_window(Window* window)
    {
        SDL_Window* internalWindow = static_cast<SDL_Window*>(window->internal);
        SDL_DestroyWindow(internalWindow);
        //delete window;
    }

    uint ticks()
    {
        return SDL_GetTicks();
    }

    void sleep(uint milliseconds)
    {
        SDL_Delay(milliseconds);
    }

    void blit(Surface* srcBitmap, Surface* dstBitmap)
    {
        // @TODO: Use nullptr?
        SDL_BlitSurface((SDL_Surface*)srcBitmap->internal, NULL, (SDL_Surface*)dstBitmap->internal, NULL);
    }
    void blit(Surface* srcBitmap, Surface* dstBitmap, Rect srcRect, Rect dstRect)
    {
        SDL_Rect sr = { (int)srcRect.x, (int)srcRect.y, (int)srcRect.w, (int)srcRect.h };
        SDL_Rect dr = { (int)dstRect.x, (int)dstRect.y, (int)dstRect.w, (int)dstRect.h };
        SDL_BlitSurface((SDL_Surface*)srcBitmap->internal, &sr, (SDL_Surface*)dstBitmap->internal, &dr);
    }

    Surface* load_image(const char* filePath)
    {
        SDL_Surface* srfc = IMG_Load(filePath);
        // @TODO: Error checking

        Point dims(srfc->w, srfc->h);
        Surface* surface = new Surface(dims);
        surface->internal = srfc;
        surface->pixels = static_cast<uint32*>(srfc->pixels);

        return surface;
    }

    int next_event(Event* e)
    {
        SDL_Event internalEvent;
        int pollResult = SDL_PollEvent(&internalEvent);
        e->type = (EventType)internalEvent.type;

        if (e->type == EventType::Keydown)
        {
            e->keyboard.code = (KeyCode)internalEvent.key.keysym.sym;
        }
        else if (e->type == EventType::Keyup)
        {
            e->keyboard.code = (KeyCode)internalEvent.key.keysym.sym;
        }


        return pollResult;
    }

    TTFont* open_font(const char* filePath, int ptSize)
    {
        TTF_Font* internalFont = TTF_OpenFont(filePath, ptSize);

        TTFont* font = new TTFont();
        font->internal = internalFont;

        return font;
    }

    void close_font(TTFont* font)
    {
        TTF_Font* internalFont = (TTF_Font*)font->internal;
        TTF_CloseFont(internalFont);

        delete font;
    }

    void render_text(Surface* surface, TTFont* font, const char* text, Rect dest)
    {
        // @TODO: Support colours besides white
        SDL_Color white = { 0xff, 0xff, 0xff };
        SDL_Surface* textSurface = TTF_RenderText_Solid((TTF_Font*)font->internal, text, white);
        SDL_Rect dr = { (int)dest.x, (int)dest.y, (int)dest.w, (int)dest.h };
        SDL_BlitSurface(textSurface, NULL, (SDL_Surface*)surface->internal, &dr);
        SDL_FreeSurface(textSurface);
    }

}
}
