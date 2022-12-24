#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <map>
#include "platform.h"

struct Keyboard
{
    static std::map<Gin::Platform::KeyCode, bool> keydownMap;
    static std::map<Gin::Platform::KeyCode, bool> prevKeydownMap;
    
    static bool key_pressed(Gin::Platform::KeyCode keyCode);

    static bool key_released(Gin::Platform::KeyCode keyCode);    
};

#endif
