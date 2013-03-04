#ifndef GAME_H    
#define	GAME_H
#include "SDL.h"
#include "CSurface.h"
#include "CEvent.h"
#include "Cursor.h"
#include "Ball.h"
#include "Line.h"
#include <vector>
#include "Definitions.h"


class Game: public CEvent {
private:
	bool Running;
	bool completebox;
	Uint32 waittime;
	Uint32 framestarttime;
	Sint32 delaytime;
	int GameState;
	int lvl, life;
	int area;
	SDL_Surface*    Display;
	SDL_Surface*	Game_Title;
	Cursor* gamecursor;
	Ball* ball;
	Line* line;
	SDL_Rect* box;
	std::vector<Ball> ballList;
	std::vector<SDL_Rect> boxList;
	

public:
	Game();
	int Start();
	bool Init();
	void Input(SDL_Event* Event);
	void OnExit();
	void Update();
	void OnRender();
	void OnCleanup();

	int DetermineBoxFill();
	void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
	void OnLButtonDown(int mX, int mY);
	void OnRButtonDown(int mX, int mY);
	void OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle);
};

#endif