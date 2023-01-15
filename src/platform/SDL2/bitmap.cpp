#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../bitmap.h"

using namespace Gin;
using namespace Platform;

Bitmap* Bitmap::open(const char* path)
{
    SDL_Surface* surface = IMG_Load(path);

    Bitmap* bitmap = new Bitmap();
    bitmap->internal = surface;
    bitmap->dimensions = Point(surface->w, surface->h);
    bitmap->pixels = static_cast<uint*>(surface->pixels);

    return bitmap;
}

Bitmap::~Bitmap()
{
    SDL_FreeSurface((SDL_Surface*)internal);
}
