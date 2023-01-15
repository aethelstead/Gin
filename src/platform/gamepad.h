#ifndef GAMEPAD_H
#define GAMEPAD_H

namespace Gin
{
namespace Platform
{
    enum class GamepadButton
    {
        A = 0,
        B = 1,
        X = 2,
        Y = 3,
        DPAD_UP = 11,
        DPAD_DOWN = 12,
        DPAD_LEFT = 13,
        DPAD_RIGHT = 14
    };

    struct Gamepad
    {
        static int nGamepads;
        static Gamepad* open();
        static void close(Gamepad* gamepad);

        void* internal;

        Gamepad():
            internal{ nullptr }
        {}

        bool button_pressed(GamepadButton button);
    };
}
}

#endif
