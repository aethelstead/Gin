#include <SDL2/SDL.h>
#include "window.h"

struct Window
{
    void* internal;
    Surface* backBuffer;
    
    Window():
        internal{ nullptr },
        backBuffer{ nullptr }
    {}

    ~Window();

    void swap_buffers();
};
