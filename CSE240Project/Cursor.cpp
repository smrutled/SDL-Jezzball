#include "Cursor.h"
Cursor::Cursor()
{
	direction = true;
	cursorWE = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEWE);
	cursorNS = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENS);
	SDL_SetCursor(cursorWE);
	SDL_ShowCursor(SDL_ENABLE);
	texture = NULL;
}
Cursor::Cursor(SDL_Texture* texture)
{
	cursorWE = NULL;
	cursorNS = NULL;
	direction = true;
	this->texture = texture;

}
Cursor::~Cursor() {
	if (cursorWE)SDL_FreeCursor(cursorWE);
	if(cursorNS)SDL_FreeCursor(cursorNS);
	if (texture)SDL_DestroyTexture(texture);
}
void Cursor::ChangeDirection()
{
	direction = !direction;
	if (cursorWE)
	{
		if (direction)
			SDL_SetCursor(cursorWE);
		else
			SDL_SetCursor(cursorNS);
	}
	
}
void Cursor::Draw(SDL_Renderer* renderer)
{
	if (texture)
	{
		if (direction)
			CSurface::OnDraw(renderer, texture, x - 30, y - 7, 60, 14, 0, 0, 60, 14);
		else
			CSurface::OnDraw(renderer, texture, x - 7, y - 30, 14, 60, 0, 15, 14, 60);
	}
}