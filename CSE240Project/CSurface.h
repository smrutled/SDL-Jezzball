#ifndef _CSURFACE_H_    
#define _CSURFACE_H_
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

class CSurface {
public:
	CSurface();
public:
	static SDL_Surface* OnLoad(char* File);
	static SDL_Surface* OnLoadBMP(char* File);
	static bool OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y);
	static bool OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y, int X2, int Y2, int W, int H);
	static bool Transparent(SDL_Surface* Surf_Dest, int R, int G, int B);
	static void PrintStrings( SDL_Surface *sDest, TTF_Font *fnt, std::string str, int X, int Y, int r, int g, int b );

};
#endif