#ifndef GAME_H    
#define	GAME_H
#include <SDL2/SDL.h>
#include "CSurface.h"
#include "Cursor.h"
#include "Ball.h"
#include "Line.h"
#include <vector>
#include "Definitions.h"


class Game{
private:
	bool Running;
	bool completebox;
	Uint32 waittime;
	Uint32 framestarttime;
	Sint32 delaytime;
	int GameState;
	int lvl, life;
	int area;
	SDL_Window*    window;
	SDL_Renderer*	renderer;
	SDL_Texture*	tex_game_title;
	SDL_Texture*	tex_cursor;
	SDL_Texture*	tex_ball;
	SDL_Event Event;
	Cursor* cursor;
	Ball* ball;
	Line* line;
	SDL_Rect* box;
	std::vector<Ball> ballList;
	std::vector<SDL_Rect> boxList;
	

public:
	Game();
	int Start();
	bool Init();
	void Loop();
	void Input(SDL_Event* Event);
	void OnExit();
	void Update();
	void OnRender();
	void OnCleanup();

	int DetermineBoxFill();
	void OnKeyDown(SDL_Keycode sym, SDL_Keymod mod);
	void OnLButtonDown(int mX, int mY);
	void OnRButtonDown(int mX, int mY);
	void OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle);
};

#endif