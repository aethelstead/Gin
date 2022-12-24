#include "keyboard.h"

using namespace Gin;
using namespace Platform;

std::map<KeyCode, bool> Keyboard::keydownMap = std::map<KeyCode, bool>();
std::map<KeyCode, bool> Keyboard::prevKeydownMap = std::map<KeyCode, bool>();

bool Keyboard::key_pressed(Gin::Platform::KeyCode keyCode)
{
    return (keydownMap[keyCode] == true);
}

bool Keyboard::key_released(Gin::Platform::KeyCode keyCode)
{
    return (prevKeydownMap[keyCode] == true && keydownMap[keyCode] == false);
}
