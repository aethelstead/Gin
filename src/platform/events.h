#ifndef EVENTS_H
#define EVENTS_H

namespace Gin
{
namespace Platform
{
    enum class EventType
    {
        Quit = 256,
        Keydown = 768,
        Keyup = 769
    };

    // @TODO: Create KeyboardEvent, MouseEvent structs and use here instead of this being flat and only including theproperties needed right now.
    struct Event
    {
        EventType type;
        int keycode;
    };

    int poll_events(Event* outEvent);
}
}

#endif
