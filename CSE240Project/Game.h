#ifndef GAME_H    
#define	GAME_H
#include <SDL2/SDL.h>
#include "CSurface.h"
#include "Cursor.h"
#include "Ball.h"
#include "Line.h"
#include <vector>
#include "Definitions.h"
#include "GameText.h"


class Game {
private:
	bool Running;
	bool completebox;
	Uint32 waittime;
	Uint32 framestarttime;
	Sint32 delaytime;
	GAME_STATE GameState;
	int lvl, lives;
	int area;	// Area filled
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* tex_game_title;
	/*SDL_Texture* tex_cursor;*/
	SDL_Texture* tex_ball;
	GameText text_lives;
	TTF_Font* font;
	TTF_Font* font_outline;
	SDL_Event Event;
	Cursor* cursor;
	Ball* ball;
	Line* line;
	SDL_Rect* box;
	SDL_Rect border;
	std::vector<Ball> ballList;
	std::vector<SDL_Rect> boxList;
	void NewGame();
	void DecreaseLives();
	void NextLevel();
	void GameOver();

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
	void OnMouseMove(int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle);
};

#endif