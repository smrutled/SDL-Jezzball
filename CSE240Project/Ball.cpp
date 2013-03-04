#include "Ball.h"

Ball::Ball(int cx,int cy, int xvel, int yvel)
{
	ball=CSurface::OnLoad("ball.png");
	CSurface::Transparent(ball,255,255,255);
	c.r=15;
	c.x=cx;
	c.y=cy;
	vx=xvel;
	vy=yvel;
}

void Ball::Move(std::vector<SDL_Rect> &rects)
{
c.x += vx;

if( ( c.x - c.r< 0 ) || ( c.x + c.r > SCREENWIDTH ) || ( Collision::CircleBoxCollision( c, rects )))
    {
        c.x -= vx;
		vx*=-1;
    }

    c.y += vy;

    if( ( c.y - c.r < 0 ) || ( c.y + c.r > SCREENHEIGHT ) || ( Collision::CircleBoxCollision( c, rects )))
    {
        c.y -= vy;
		vy*=-1;
    }
}

void Ball::CheckBoxCollision(std::vector<SDL_Rect> &B)
{
	 for( int i = 0; i < B.size(); i++ ){
		 if(Collision::CircleBoxCollision(c,B[i]))
		 {
			 if(c.x>=B[i].x && c.x<=B[i].x+B[i].w)
				 vx*=-1;
			 if(c.y>=B[i].y && c.y<=B[i].y+B[i].h)
				 vy*=-1;
		 }
	 }
		 

}

void Ball::Draw(SDL_Surface*  display)
{
	CSurface::OnDraw(display,ball,c.x-c.r,c.y-c.r);
}