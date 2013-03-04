#ifndef BALL_H    
#define BALL_H
#include "CSurface.h"
#include "Collision.h"


class Ball
{
    private:
    SDL_Surface* ball;
	
    public:
	Circle c;
	int vx, vy;
    Ball(int x,int y, int xvel, int yvel);
    
	void Move(std::vector<SDL_Rect> &rects);
    
    void CheckBoxCollision(std::vector<SDL_Rect> &B);
    
    void Draw(SDL_Surface*  display);
};
#endif
