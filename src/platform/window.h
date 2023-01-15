#ifndef WINDOW_H
#define WINDOW_H

namespace Gin
{
namespace Platform
{

    struct Window
    {
        // @TODO: Overload this function to allow the user to specify window's initial X and Y position.
        static Window* open(const char* title, int width, int height);
        static void close(Window* window);

        void* internal;

        Window():
            internal{ nullptr }
        {}
    };

}
}

#endif
