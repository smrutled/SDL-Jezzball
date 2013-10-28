#ifndef CURSOR_H    
#define CURSOR_H
#include "CSurface.h"
class Cursor
{
    public:
	SDL_Texture* texture;
	int x, y;
	bool direction;
    Cursor(SDL_Texture* texture);
	~Cursor();
    void Update();
    
    void Draw(SDL_Renderer*  renderer);
};
#endif