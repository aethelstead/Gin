#ifndef TEXTURE_H
#define TEXTURE_H

struct Texture
{
    void* internal;

    Texture():
        internal(nullptr)
    {}
};

#endif
