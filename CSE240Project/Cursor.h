#ifndef CURSOR_H    
#define CURSOR_H
#include "CSurface.h"
class Cursor
{
public:
	SDL_Texture* texture;
	int x, y;
	SDL_Cursor* cursorWE;
	SDL_Cursor* cursorNS;
	
	bool direction;
	Cursor();
	Cursor(SDL_Texture* texture);
	~Cursor();
	void ChangeDirection();

	void Draw(SDL_Renderer* renderer);
};
#endif