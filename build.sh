clang++ src/main.cpp src/gin.cpp src/game.cpp src/entity.cpp src/logger.cpp src/platform_sdl2.cpp src/rendering.cpp -o bin/gin -lSDL2 -lSDL2_image
#x86_64-w64-mingw32-gcc -o bin/gin.exe src/main.cpp src/runtime.cpp src/logger.cpp src/platform_sdl2.cpp src/rendering.cpp -lSDL2 -lSDL2_image