#include "Line.h"

Line::Line(int x,int y, bool direction)
{
	this->x=x;
	this->y=y;
	this->direction=direction;
	speed=20;
	complete1=false;
	complete2=false;
	destroy=false;
	Rect1.x=x;
	Rect1.y=y;
	Rect2.x=x;
	Rect2.y=y;
	if(direction)
	{
	Rect1.w=0;
	Rect1.h=10;
	Rect2.w=0;
	Rect2.h=10;
	}
	else
	{
	Rect1.w=10;
	Rect1.h=0;
	Rect2.w=10;
	Rect2.h=0;
	}
}
Line::~Line(){
}

bool Line::getDirection()
{
	return direction;
}
void Line::Move()
{
	if(direction)
	{
		if(Rect1.x>0 && !complete1){
		Rect1.x-=speed;
		Rect1.w+=speed;
		if(Rect1.x<=0)
			complete1=true;
		}
		if((Rect2.x+Rect2.w)<SCREEN_WIDTH && !complete2){
		Rect2.w+=speed;
		if(Rect2.x+Rect2.w>=SCREEN_WIDTH)
			complete2=true;
		}
	}
	else
	{
		if(Rect1.y>0 && !complete1){
		Rect1.y-=speed;
		Rect1.h+=speed;
		if(Rect1.y<=0)
			complete1=true;
		}
		if((Rect2.y+Rect2.h)<SCREEN_HEIGHT && !complete2){
		Rect2.h+=speed;
		if(Rect2.y+Rect2.h>=SCREEN_HEIGHT)
			complete2=true;
		}
	}
}

void Line::CheckBoxCollision(std::vector<SDL_Rect> &B)
{
			 for( int i = 0; i < B.size(); i++ )
			{
				if(Collision::BoxCollision(Rect1,B[i]))
				{
					complete1=true;
					if(direction)
						Rect1.x=B[i].x+B[i].w;
					else
						Rect1.y=B[i].y+B[i].h;
					complete1=true;
				}

				if(Collision::BoxCollision(Rect2,B[i]))
				{
					complete2=true;
					if(direction)
						Rect2.w=B[i].x-Rect2.x;
					else
						Rect2.h=B[i].y-Rect2.y;
				}
		
			}
}
void Line::CheckBallCollision(Circle &c)
{
	if(Collision::CircleBoxCollision(c,Rect1) ||Collision::CircleBoxCollision(c,Rect2))
	{
		destroy=true;
	}
}

bool Line::CheckCompleted()
{
	return complete1 && complete2;
}

bool Line::CheckDestroyed()
{
	return destroy;
}
void Line::Draw(SDL_Renderer*  renderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(renderer, &Rect1);
	SDL_RenderFillRect(renderer, &Rect2);
}