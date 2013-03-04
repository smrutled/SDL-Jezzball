#include "Game.h"

void Game::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {
	switch(sym) {
		case SDLK_p: {
			switch(GameState)
			{
			case GAME_PLAY:
				SDL_ShowCursor(1);
				GameState=GAME_PAUSE;
				break;
			case GAME_PAUSE:
				SDL_ShowCursor(0);
				GameState=GAME_PLAY;
				break;
			}
			break;
		}

		case SDLK_RIGHT: {
			break;
		}

		case SDLK_SPACE: {
		    break;
		}

		default: {
		}
	}
}

void Game::OnLButtonDown(int mX, int mY){
switch(GameState)
	{
	case GAME_MENU:
		if(mX>100 && mX<500 && mY>100 && mY<300)
		{
			GameState=GAME_INIT;
		}
	break;
	case GAME_PLAY:
		if(!Collision::PointBoxCollision(mX,mY,boxList)){
		if(line==NULL)
			line=new Line(mX-5,mY-5,gamecursor->direction);
		else
		{
			delete line;
			line=new Line(mX,mY,gamecursor->direction);
		}
		}
	break;
	case GAME_PAUSE:
	break;
	}
}

void Game::OnRButtonDown(int mX, int mY){
switch(GameState)
	{
	case GAME_MENU:
		if(mX>100 && mX<500 && mY>100 && mY<300)
			GameState=GAME_PLAY;
	break;
	case GAME_PLAY:
	gamecursor->direction= gamecursor->direction? false:true;
	break;
	case GAME_PAUSE:
	break;
	}
}

void Game::OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle){
switch(GameState)
	{
	case GAME_MENU:
	break;
	case GAME_PLAY:
		gamecursor->x=mX;
		gamecursor->y=mY;
	break;
	case GAME_PAUSE:
	break;
	}
}