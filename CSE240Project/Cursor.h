#ifndef CURSOR_H    
#define CURSOR_H
#include "CSurface.h"
class Cursor
{
    public:
	SDL_Surface* arrow;
	int x, y;
	bool direction;
    Cursor();
	~Cursor();
    void Update();
    
    void Draw(SDL_Surface*  display);
};
#endif