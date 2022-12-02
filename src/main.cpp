#include "Application.h"

int main(int argc, char* argv[])
{
    if (!Application::start())
    {
        return 1;
    }

    return 0;
}
