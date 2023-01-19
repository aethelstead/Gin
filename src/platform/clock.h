#ifndef CLOCK_H
#define CLOCK_H

typedef unsigned int uint;

namespace Gin
{
namespace Platform
{
    void sleep(uint milliseconds);

    uint ticks();
}
}

#endif
