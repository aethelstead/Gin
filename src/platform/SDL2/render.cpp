#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../render.h"

using namespace Gin;
using namespace Platform;

RenderContext* RenderContext::open(Window* window)
{
    SDL_Renderer* internalRenderer = SDL_CreateRenderer((SDL_Window*)window->internal, -1, SDL_RENDERER_ACCELERATED);
    if (!internalRenderer)
        return nullptr;

    RenderContext* context = new RenderContext();
    context->internal = internalRenderer;

    return context;
}

void RenderContext::close(RenderContext* context)
{
    SDL_Renderer* internalRenderer = (SDL_Renderer*)context->internal;
    SDL_DestroyRenderer(internalRenderer);
    delete context;
}

Texture* Texture::open(RenderContext* context, Point dimensions)
{
    SDL_Renderer* internalRenderer = (SDL_Renderer*)context->internal;
    SDL_Texture* internalTexture = SDL_CreateTexture( internalRenderer, 
                                                      SDL_PIXELFORMAT_RGBA8888,
                                                      SDL_TEXTUREACCESS_TARGET,
                                                      dimensions.x,
                                                      dimensions.y);
    if (!internalTexture)
        return nullptr;
    
    Texture* texture = new Texture();
    texture->internal = internalTexture;

    return texture;
}

Texture* Texture::open(RenderContext* context, Bitmap* bitmap)
{
    SDL_Surface* internalSurface = (SDL_Surface*)bitmap->internal;
    SDL_Renderer* internalRenderer = (SDL_Renderer*)context->internal;
    SDL_Texture* internalTexture = SDL_CreateTextureFromSurface(internalRenderer, internalSurface);

    SDL_FreeSurface(internalSurface);

    if (!internalTexture)
        return nullptr;

    Texture* texture = new Texture();
    texture->internal = internalTexture;

    return texture;
}

Texture* Texture::open(RenderContext* context, const char* path)
{
    SDL_Renderer* internalRenderer = (SDL_Renderer*)context->internal;
    SDL_Texture* internalTexture = IMG_LoadTexture(internalRenderer, path);
    if (!internalTexture)
        return nullptr;
    
    Texture* texture = new Texture();
    texture->internal = internalTexture;

    return texture;
}

void Texture::close(Texture* texture)
{
    SDL_Texture* internalTexture = (SDL_Texture*)texture->internal;
    SDL_DestroyTexture(internalTexture);
    delete texture;
}

void Renderer::clear(RenderContext* context)
{
    SDL_Renderer* internalRenderer = (SDL_Renderer*)context->internal;
    SDL_RenderClear(internalRenderer);
}

void Renderer::copy(RenderContext* context, Texture* texture, Rect srcRect, Rect dstRect)
{
    SDL_Renderer* internalRenderer = (SDL_Renderer*)context->internal;
    SDL_Texture* internalTexture = (SDL_Texture*)texture->internal;
    SDL_Rect sr = { srcRect.x, srcRect.y, srcRect.w, srcRect.h };
    SDL_Rect dr = { dstRect.x, dstRect.y, dstRect.w, dstRect.h };
    SDL_RenderCopy(internalRenderer, internalTexture, &sr, &dr);
}

void Renderer::flip(RenderContext* context)
{
    SDL_Renderer* internalRenderer = (SDL_Renderer*)context->internal;
    SDL_RenderPresent(internalRenderer);
}
