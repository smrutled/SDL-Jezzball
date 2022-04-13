#ifndef LINE_H    
#define LINE_H
#include "CSurface.h"
#include "Collision.h"
#include <vector>

class Line
{
private:
	int x, y, speed;
	bool direction, complete1, complete2;
	bool destroy;


public:
	SDL_Rect Rect1;
	SDL_Rect Rect2;
	Line(int x, int y, bool direction);
	~Line();
	bool getDirection();
	void Move();
	void CheckBoxCollision(std::vector<SDL_Rect>& B);
	void CheckBallCollision(Circle& c);
	bool CheckCompleted();
	bool CheckDestroyed();

	void Draw(SDL_Renderer* renderer);
};
#endif