#include <SDL2/SDL.h>

#include "../renderer.h"

Renderer* Renderer::open(Gin::Platform::Window* window)
{
    SDL_Renderer* internalRenderer = SDL_CreateRenderer((SDL_Window*)window->internal, -1, SDL_RENDERER_ACCELERATED);
    if (!internalRenderer)
        return nullptr;

    Renderer* renderer = new Renderer();
    renderer->internal = internalRenderer;

    // @TODO: This is ugly but do I REALLY have to pass a renderer everytime I open a texture? CBA TBH. Probabkly will just bite the bullet and pass renderer when opening a texture, also refactor View so that it doesn;t load the textures itself as I dont want to pass renderer to view I want to keep it in Game.
    // Set a static pointer to the internal renderer in the Texture class so that it can open textures independently.
    Texture::internalRenderer = internalRenderer;

    return renderer;
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer((SDL_Renderer*)internal);
}

void Renderer::clear()
{
    SDL_RenderClear((SDL_Renderer*)internal);
}

void Renderer::copy(Texture* texture, Rect srcRect, Rect dstRect)
{
    SDL_Texture* internalTexture = (SDL_Texture*)texture->internal;
    SDL_Rect sr = { srcRect.x, srcRect.y, srcRect.w, srcRect.h };
    SDL_Rect dr = { dstRect.x, dstRect.y, dstRect.w, dstRect.h };
    SDL_RenderCopy((SDL_Renderer*)internal, internalTexture, &sr, &dr);
}

void Renderer::flip()
{
    SDL_RenderPresent((SDL_Renderer*)internal);
}
