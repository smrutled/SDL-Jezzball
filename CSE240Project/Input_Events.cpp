#include "Game.h"


//Input handler
void Game::Input(SDL_Event* Event) {
	switch(Event->type) {
		case SDL_KEYDOWN: {
			OnKeyDown(Event->key.keysym.sym, (SDL_Keymod) Event->key.keysym.mod);
			break;
		}
		case SDL_KEYUP: {
			break;
		}
        case SDL_MOUSEMOTION: {
            OnMouseMove(Event->motion.x,Event->motion.y,Event->motion.xrel,Event->motion.yrel,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_LEFT))!=0,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_RIGHT))!=0,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_MIDDLE))!=0);
            break;
        }
 
        case SDL_MOUSEBUTTONDOWN: {
            switch(Event->button.button) {
                case SDL_BUTTON_LEFT: {
                    OnLButtonDown(Event->button.x,Event->button.y);
                    break;
                }
                case SDL_BUTTON_RIGHT: {
                    OnRButtonDown(Event->button.x,Event->button.y);
                    break;
                }
                case SDL_BUTTON_MIDDLE: {
                    break;
                }
            }
            break;
        }
 
        case SDL_MOUSEBUTTONUP:    {
            switch(Event->button.button) {
                case SDL_BUTTON_LEFT: {
                    break;
                }
                case SDL_BUTTON_RIGHT: {
                    break;
                }
                case SDL_BUTTON_MIDDLE: {
                    break;
                }
            }
            break;
        }
 
        case SDL_QUIT: {
            OnExit();
            break;
        }

    }
}



void Game::OnKeyDown(SDL_Keycode sym, SDL_Keymod mod) {
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
			line=new Line(mX-5,mY-5,cursor->direction);
		else
		{
			delete line;
			line=new Line(mX,mY,cursor->direction);
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
	cursor->direction= cursor->direction? false:true;
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
		cursor->x=mX;
		cursor->y=mY;
	break;
	case GAME_PAUSE:
	break;
	}
}