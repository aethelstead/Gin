#ifndef CONFIG_H
#define CONFIG_H

#include "../geometry.h"

struct Config
{
    static Config load();

    Point windowDimensions;

    Config():
        windowDimensions{ Point(0, 0) }
    {}

};

#endif