#ifndef CONFIG_H
#define CONFIG_H

#include "../geometry.h"

struct Config
{
    static Config load();

    Point windowDimensions;

    Config()
    {}

};

#endif