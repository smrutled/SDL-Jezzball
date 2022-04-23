#ifndef CURSOR_H    
#define CURSOR_H
#include "CSurface.h"
#include "Definitions.h"

enum class CURSOR_STATE
{
	ARROW,
	DIRECTION
};

class Cursor
{
public:
	SDL_Texture* texture;
	int x, y;
	SDL_Cursor* cursorWE;
	SDL_Cursor* cursorNS;
	SDL_Cursor* cursorArrow;
	CURSOR_STATE state;
	bool direction;
	Cursor();
	Cursor(SDL_Texture* texture);
	~Cursor();
	void SetState(CURSOR_STATE state);
	void ChangeDirection();

	void Draw(SDL_Renderer* renderer);
};
#endif