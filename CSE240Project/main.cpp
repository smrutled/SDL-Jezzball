#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include <SDL2/SDL.h>
#include "Game.h"
#include <stdio.h>
Game App;

void game_loop()
{
	App.Loop();
}

int main( int argc, char* args[] ) 
{ 
	printf("Starting Game\n");

 if (App.Init() == false) {
	 printf("Init failed\n");
	 return -1;
 }

#ifdef __EMSCRIPTEN__

 emscripten_set_main_loop(game_loop, 0, 1);
 App.OnCleanup();
#else
 return App.Start();
#endif


} 