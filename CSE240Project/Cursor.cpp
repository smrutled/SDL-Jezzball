#include "Cursor.h"
Cursor::Cursor(SDL_Texture* texture)
{
	direction = true;
	this->texture = texture;

}
Cursor::~Cursor() {
}
void Cursor::Draw(SDL_Renderer* renderer)
{
	if (direction)
		CSurface::OnDraw(renderer, texture, x - 30, y - 7, 60, 14, 0, 0, 60, 14);
	else
		CSurface::OnDraw(renderer, texture, x - 7, y - 30, 14, 60, 0, 15, 14, 60);
}