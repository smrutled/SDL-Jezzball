#ifndef _CSURFACE_H_    
#define _CSURFACE_H_
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class CSurface {
public:
	CSurface();
public:
	static SDL_Texture* load_image(char* File, SDL_Renderer* renderer);
	static bool OnDraw(SDL_Renderer* renderer, SDL_Texture* texture, int X, int Y, int W, int H);
	static bool OnDraw(SDL_Renderer* renderer, SDL_Texture* texture, int X, int Y, int W, int H, int X2, int Y2, int W2, int H2);
	static bool Transparent(SDL_Surface* Surf_Dest, int R, int G, int B);
	static void PrintStrings(SDL_Surface* sDest, TTF_Font* fnt, std::string str, int X, int Y, int r, int g, int b);

};
#endif