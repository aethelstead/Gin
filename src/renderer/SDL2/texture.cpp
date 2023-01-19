#include <SDL2/SDL.h>

#include "../texture.h"

void* Texture::internalRenderer = nullptr;

Texture* Texture::open(Gin::Platform::Bitmap* bitmap)
{
    if (!internalRenderer)
        return nullptr;

    SDL_Surface* internalSurface = (SDL_Surface*)bitmap->internal;
    SDL_Texture* internalTexture = SDL_CreateTextureFromSurface((SDL_Renderer*)internalRenderer, internalSurface);

    SDL_FreeSurface(internalSurface);

    if (!internalTexture)
        return nullptr;

    Texture* texture = new Texture();
    texture->internal = internalTexture;

    return texture;
}

Texture::~Texture()
{
    SDL_DestroyTexture((SDL_Texture*)internal);
}
