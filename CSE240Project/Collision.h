#ifndef COLLISION_H
#define COLLISION_H
#include <SDL2/SDL.h>
#include <vector>
#include "Definitions.h"
#include <cmath>

class Collision {
public:
	Collision();
public:
	static bool BoxCollision( SDL_Rect &A, SDL_Rect &B );
	static bool PointBoxCollision(int x, int y, std::vector<SDL_Rect> &B );
	static bool CircleBoxCollision( Circle &A, SDL_Rect &B );
	static bool CircleBoxCollision( Circle &A, std::vector<SDL_Rect> &B);
	static double distance( int x1, int y1, int x2, int y2 );
	static bool CircleCollision( Circle &A, Circle &B );

};

#endif