#include "Collision.h"

/*This piece of code was originally from Lazy Foo' Productions
 (http://lazyfoo.net/)*/

bool Collision::BoxCollision(SDL_Rect& A, SDL_Rect& B)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = A.x;
	rightA = A.x + A.w;
	topA = A.y;
	bottomA = A.y + A.h;

	//Calculate the sides of rect B
	leftB = B.x;
	rightB = B.x + B.w;
	topB = B.y;
	bottomB = B.y + B.h;

	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;

}


bool Collision::PointBoxCollision(int x, int y, std::vector<SDL_Rect>& B)
{
	for (unsigned int i = 0; i < B.size(); i++)
	{
		if (x >= B[i].x && x <= B[i].x + B[i].w)
			if (y >= B[i].y && y <= B[i].y + B[i].h)
				return true;
	}
	return false;
}
bool Collision::CircleBoxCollision(Circle& A, SDL_Rect& B)
{
	//Closest point on collision box
	int cX, cY;

	//Find closest x offset
	if (A.x < B.x)
	{
		cX = B.x;
	}
	else if (A.x > B.x + B.w)
	{
		cX = B.x + B.w;
	}
	else
	{
		cX = A.x;
	}

	//Find closest y offset
	if (A.y < B.y)
	{
		cY = B.y;
	}
	else if (A.y > B.y + B.h)
	{
		cY = B.y + B.h;
	}
	else
	{
		cY = A.y;
	}

	//If the closest point is inside the circle
	if (distance(A.x, A.y, cX, cY) < A.r)
	{
		//This box and the circle have collided
		return true;
	}

	//If the shapes have not collided
	return false;
}


bool Collision::CircleBoxCollision(Circle& A, std::vector<SDL_Rect>& B)
{
	//Closest point on collision box
	int cX, cY;

	//Go through the B boxes
	for (unsigned int Bbox = 0; Bbox < B.size(); Bbox++)
	{
		//Find closest x offset
		if (A.x < B[Bbox].x)
		{
			cX = B[Bbox].x;
		}
		else if (A.x > B[Bbox].x + B[Bbox].w)
		{
			cX = B[Bbox].x + B[Bbox].w;
		}
		else
		{
			cX = A.x;
		}

		//Find closest y offset
		if (A.y < B[Bbox].y)
		{
			cY = B[Bbox].y;
		}
		else if (A.y > B[Bbox].y + B[Bbox].h)
		{
			cY = B[Bbox].y + B[Bbox].h;
		}
		else
		{
			cY = A.y;
		}

		//If the closest point is inside the circle
		if (distance(A.x, A.y, cX, cY) < A.r)
		{
			//This box and the circle have collided
			return true;
		}
	}

	//If the shapes have not collided
	return false;
}



double Collision::distance(int x1, int y1, int x2, int y2)
{
	//Return the distance between the two points
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

bool Collision::CircleCollision(Circle& A, Circle& B)
{
	//If the distance between the centers of the circles is less than the sum of their radii
	if (distance(A.x, A.y, B.x, B.y) < (A.r + B.r))
	{
		//The circles have collided
		return true;
	}

	//If not
	return false;
}