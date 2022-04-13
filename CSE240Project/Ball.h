#ifndef BALL_H    
#define BALL_H
#include "CSurface.h"
#include "Collision.h"


class Ball
{
private:
	SDL_Texture* texture;

public:
	Circle c;
	int vx, vy;
	Ball(int cx, int cy, int xvel, int yvel, SDL_Texture* texture);

	void Move(std::vector<SDL_Rect>& rects);

	void CheckBoxCollision(std::vector<SDL_Rect>& B);

	void Draw(SDL_Renderer* renderer);
};
#endif
