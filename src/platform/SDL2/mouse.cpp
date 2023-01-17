#include <SDL2/SDL.h>

#include "../mouse.h"

using namespace Gin;
using namespace Platform;

Point Mouse::pos = Point(0, 0);
Point Mouse::prevPos = Point(0, 0);
bool Mouse::leftButtonDown = false;
bool Mouse::rightButtonDown = false;
bool Mouse::prevLeftButtonDown = false;
bool Mouse::prevRightButtonDown = false;

bool Mouse::moved()
{
    return pos != prevPos;
}

bool Mouse::left_button_pressed()
{
    return leftButtonDown;
}

bool Mouse::left_button_released()
{
    return (prevLeftButtonDown == true && leftButtonDown == false);
}

bool Mouse::right_button_pressed()
{
    return rightButtonDown;
}

bool Mouse::right_button_released()
{
    return (prevRightButtonDown == true && rightButtonDown == false);
}
