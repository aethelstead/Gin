#include "gin.h"

// @TODO: Move main to Platform?
int main(int argc, char* argv[])
{
    if (!Gin::Gin::start())
    {
        return 1;
    }

    return 0;
}
