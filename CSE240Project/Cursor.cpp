#include "Cursor.h"
Cursor::Cursor()
{
	direction=true;
	arrow=CSurface::OnLoad("arrow.png");

}
Cursor::~Cursor(){
	SDL_FreeSurface(arrow);
}
void Cursor::Draw(SDL_Surface*  display)
{
	if(direction)
		CSurface::OnDraw(display, arrow,x-30,y-7,0,0,60,14);
	else
		CSurface::OnDraw(display, arrow,x-7,y-30,0,15,14,60);
}