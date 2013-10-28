#include "CSurface.h"
CSurface::CSurface() {
}
SDL_Texture* CSurface::load_image(char* File, SDL_Renderer* renderer) {
	SDL_Texture* texture = nullptr;
	if ((texture = IMG_LoadTexture(renderer, File)) == nullptr) {
		return nullptr;
	}
	return texture;
}

bool CSurface::OnDraw(SDL_Renderer* renderer, SDL_Texture* texture, int X, int Y, int W, int H) {
    if(renderer == nullptr || texture == nullptr)
        return false;
 
    SDL_Rect DestR;

    DestR.x = X;
    DestR.y = Y;
	DestR.w = W;
	DestR.h = H;
    SDL_RenderCopy(renderer, texture, nullptr, &DestR);
 
    return true;
}

bool CSurface::OnDraw(SDL_Renderer* renderer, SDL_Texture* texture, int X, int Y, int W, int H, int X2, int Y2, int W2, int H2)
{    
	if (renderer == nullptr || texture == nullptr)
		return false;

	SDL_Rect DestR;     
	DestR.x = X;    
	DestR.y = Y;
	DestR.w = W;
	DestR.h = H;
	SDL_Rect SrcR;     
	SrcR.x = X2;    
	SrcR.y = Y2;    
	SrcR.w = W2;    
	SrcR.h = H2;
	SDL_RenderCopy(renderer, texture, &SrcR, &DestR);   
	return true;
}



void CSurface::PrintStrings( SDL_Surface *sDest, TTF_Font *fnt, std::string str, int X, int Y, int r, int g, int b ) {
	SDL_Rect SrcR;
	SrcR.x = X;    
	SrcR.y = Y;
	SDL_Color clr;
    clr.r = r;
    clr.g = g;
    clr.b = b;
	SDL_Surface *sText = TTF_RenderText_Solid( fnt, str.c_str(), clr );
	SDL_BlitSurface( sText,NULL, sDest,&SrcR );
	SDL_FreeSurface( sText );
}
