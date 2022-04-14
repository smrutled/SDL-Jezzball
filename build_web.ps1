git clone https://github.com/emscripten-core/emsdk.git
cd emsdk
./emsdk install latest
./emsdk activate latest
cd ..
New-Item -Name "web" -ItemType "directory" -Force
cd CSE240Project
emcc Collision.cpp CSurface.cpp Cursor.cpp Ball.cpp Game.cpp Input_Events.cpp Line.cpp main.cpp -o ..\web\index.html --preload-file assets -Wall -g -std=c++20 -lm -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' -s USE_SDL_TTF=2
cd ..