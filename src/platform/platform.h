#ifndef PLATFORM_H
#define PLATFORM_H

#include "window.h"
#include "bitmap.h"
#include "render.h"
#include "keyboard.h"
#include "mouse.h"
#include "gamepad.h"
#include "file.h"

typedef unsigned int uint;

namespace Gin
{
namespace Platform
{
    void sleep(uint milliseconds);

    uint ticks();

    void update();
}
}

#endif
