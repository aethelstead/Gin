#ifndef PLATFORM_H
#define PLATFORM_H

#include <stdlib.h>

#include "geometry.h"

namespace Gin
{
namespace Platform
{
    using namespace Geometry;

    typedef unsigned int    uint;
    typedef unsigned int    uint32;

    struct Surface
    {
        static Surface* create_empty(Point dims);

        void* internal;
        Point dimensions;
        uint32* pixels;

        Surface():
            internal{ nullptr },
            dimensions{ Point(0, 0) },
            pixels{ nullptr }
        {}

        Surface(Point dims):
            internal{ nullptr },
            dimensions{ dims },
            pixels{ nullptr }
        {}

        ~Surface();
    };

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

    enum class KeyCode
    {
        None = 0,
        Escape = 27,
        Space = 32,
        Q = 113,
        W = 119,
        A = 97,
        S = 115,
        D = 100
    };

    // @TODO: This matches up exactly with SDL_EventType which is fine for now but won't work for other platform implementations.
    enum class EventType
    {
        None = 0,
        Quit = 256,
        Keydown = 768,
        Keyup = 769
    };

    struct KeyboardEvent
    {
        KeyCode code;

        KeyboardEvent():
            code{ KeyCode::None }
        {}
    };

    // struct KeydownEvent

    struct Event
    {
        void* internal;
        EventType type;
        KeyboardEvent keyboard;

        Event():
            internal{ nullptr },
            type{ EventType::None },
            keyboard{ KeyboardEvent() }
        {}
    };

    bool init();
    void quit();

    Window* open_window(const char* title, int width, int height);
    void close_window(Window* window);

    uint ticks();
    void sleep(uint milliseconds);

    void blit(Surface* srcBitmap, Surface* dstBitmap);
    void blit(Surface* srcBitmap, Surface* dstBitmap, Rect srcRect, Rect dstRect);

    Surface* load_image(const char* filePath);

    // Gets the next event from the event queue. Returns > 0 if found and updates the Event e with the event data. Returns 0 if no events on queue.
    int next_event(Event* e);
}
}

#endif
