#ifndef PLATFORM_H
#define PLATFORM_H

#include "platform/window.h"
#include "platform/bitmap.h"
#include "platform/render.h"
#include "platform/keyboard.h"
#include "platform/mouse.h"
#include "platform/gamepad.h"
#include "platform/file.h"

namespace Gin
{
namespace Platform
{
    void sleep(int milliseconds);

    int ticks();

    void update();
}
}

#endif
