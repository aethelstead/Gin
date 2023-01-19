#ifndef MOUSE_H
#define MOUSE_H

#include "geometry.h"

struct Mouse
{
    static Point pos;
    static Point prevPos;
    static bool leftButtonDown;
    static bool rightButtonDown;
    static bool prevLeftButtonDown;
    static bool prevRightButtonDown;

    static bool moved();

    static bool left_button_pressed();
    static bool left_button_released();
    static bool right_button_pressed();
    static bool right_button_released();
    // @TODO: Handle mouse wheel
};

#endif
