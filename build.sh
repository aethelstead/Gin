clang++ \
\
-I/home/jim/vcpkg/installed/x64-linux/include/ \
-L/home/jim/vcpkg/installed/x64-linux/lib/ \
\
src/assets.cpp \
src/logger.cpp \
src/game/world.cpp \
src/game/view.cpp \
src/game/sprite.cpp \
src/game/config.cpp \
src/game/game.cpp \
src/game/tilemap.cpp \
src/platform/file.cpp \
src/platform/SDL2/main.cpp \
src/platform/SDL2/platform.cpp \
src/platform/SDL2/window.cpp \
src/platform/SDL2/render.cpp \
src/platform/SDL2/gamepad.cpp \
src/platform/SDL2/bitmap.cpp \
src/platform/SDL2/keyboard.cpp \
src/platform/SDL2/mouse.cpp \
\
-o bin/tilegame \
\
-lSDL2 -lSDL2_image -lSDL2_mixer -ltmxparser -lz -ltinyxml2 
