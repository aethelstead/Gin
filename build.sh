clang++ \
\
-I/home/jim/vcpkg/installed/x64-linux/include/ \
-L/home/jim/vcpkg/installed/x64-linux/lib/ \
\
src/assets.cpp \
src/logger.cpp \
src/keyboard.cpp \
src/game/world.cpp \
src/game/view.cpp \
src/game/sprite.cpp \
src/game/config.cpp \
src/game/game.cpp \
src/game/tilemap.cpp \
src/platform/file.cpp \
src/platform/SDL2/main.cpp \
src/platform/SDL2/clock.cpp \
src/platform/SDL2/window.cpp \
src/platform/SDL2/bitmap.cpp \
src/platform/SDL2/events.cpp \
src/renderer/SDL2/renderer.cpp \
src/renderer/SDL2/texture.cpp \
\
-o bin/tilegame \
\
-lSDL2 -lSDL2_image -lSDL2_mixer -ltmxparser -lz -ltinyxml2 
