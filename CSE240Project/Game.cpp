#define _USE_MATH_DEFINES
#include <cmath>
#include "Game.h"

Game::Game() {
	window = nullptr;
	Running=true;
	waittime = 1000.0f/FPS;
	framestarttime = 0;
	GameState=GAME_MENU;
	lvl=1;
	life=5;
	area=0;
	line=nullptr;
	completebox=false;
}

//Game loop
int Game::Start(){
	if(Init() == false){
	return -1;
	}

	SDL_Event Event;
	while(Running){
		while(SDL_PollEvent(&Event)) {
			Input(&Event);
		}
		Update();
		OnRender();
		delaytime = waittime - (SDL_GetTicks() - framestarttime);
		if(delaytime > 0)
			SDL_Delay((Uint32)delaytime);
		framestarttime = SDL_GetTicks();

	}

	OnCleanup();
	return 0;
}

//Init SDL stuff
bool Game::Init() {
	
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return false;

	if (TTF_Init() == -1)
		return false;

	if ((window = SDL_CreateWindow("JezzBall", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN)) == nullptr){
		return false;
	}
	if ((renderer = SDL_CreateRenderer(window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC))==nullptr){
		return false;
	}

	if ((tex_game_title = CSurface::load_image("jezzball.png", renderer)) == nullptr) {
		return false;
	}
	if ((tex_cursor = CSurface::load_image("arrow.png", renderer)) == nullptr) {
		return false;
	}
	if ((tex_ball = CSurface::load_image("ball.png", renderer)) == nullptr) {
		return false;
	}

	
	return true;
}

void Game::OnExit() {    
	Running = false;
}

void Game::Update() {
	//Used to switch between gamestates
	switch(GameState)
	{
	case GAME_MENU:
	break;
	case GAME_INIT:
	SDL_ShowCursor(0);
	cursor= new Cursor(tex_cursor);
	ball=new Ball(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,rand()%4+6,rand()%4+6,tex_ball);
	ballList.insert(ballList.end(), *ball);
	delete ball;
	GameState=GAME_PLAY;
	break;
	case GAME_PLAY:
		
		//Handles all ball movement and collision
		for( int i = 0; i < ballList.size(); i++ )
			ballList[i].Move(boxList);
		for( int i = 0; i < ballList.size(); i++ ){
			for( int j = 1+i; j < ballList.size()-i; j++ )
			{
				if(Collision::CircleCollision(ballList[i].c,ballList[j].c)){
					if(ballList[i].c.x<=ballList[j].c.x+ballList[j].c.r*cos((float)45*M_PI/180) && ballList[i].c.x>=ballList[j].c.x+ballList[j].c.r*cos((float)135*M_PI/180)){
						ballList[i].vy+=ballList[j].vy;
						ballList[j].vy=ballList[i].vy-ballList[j].vy;
						ballList[i].vy-=ballList[j].vy;
					}
					else{
						ballList[i].vx+=ballList[j].vx;
						ballList[j].vx=ballList[i].vx-ballList[j].vx;
						ballList[i].vx-=ballList[j].vx;
					}
				}
			}
		}

					
//Handles updating the line when it exists
	if(line!=NULL)
	{
		line->Move();
		line->CheckBoxCollision(boxList);
		for( int i = 0; i < ballList.size(); i++ )
			line->CheckBallCollision(ballList[i].c);
		if(line->CheckDestroyed())
		{
			delete line;
			line=NULL;
			life--;
		}
		if(line!=NULL)
		if(line->CheckCompleted())
		{
			box=new SDL_Rect();
			if(line->getDirection()){
			box->x=line->Rect1.x;
			box->y=line->Rect1.y;
			box->w=line->Rect2.x+line->Rect2.w-line->Rect1.x;
			box->h=line->Rect1.h;
			switch(DetermineBoxFill())
			{
			case 0:break;
			case 1:
			while(box->y>0 && !completebox)
			{
			box->y-=2;
			box->h+=2;
			for( int i = 0; i < boxList.size(); i++ )
			{
				if(Collision::BoxCollision(*box,boxList[i]))
				{
					box->h-=boxList[i].y+boxList[i].h-box->y;
					box->y=boxList[i].y+boxList[i].h;
					completebox=true;
				}
			}
			}
			break;
			case 2:
			while(box->y+box->h<SCREEN_HEIGHT && !completebox)
			{
			box->h+=2;
			for( int i = 0; i < boxList.size(); i++ )
			{
				if(Collision::BoxCollision(*box,boxList[i]))
				{
					box->h=boxList[i].y-box->y;
					completebox=true;
				}
			}
			}
			break;
			}
		}
			else
			{
			box->x=line->Rect1.x;
			box->y=line->Rect1.y;
			box->w=line->Rect1.w;
			box->h=line->Rect2.y+line->Rect2.h-line->Rect1.y;

			switch(DetermineBoxFill())
			{
			case 0: break;
			case 1:
			while(box->x>0 && !completebox)
			{
			box->x-=2;
			box->w+=2;
			for( int i = 0; i < boxList.size(); i++ )
			{
				if(Collision::BoxCollision(*box,boxList[i]))
				{
					box->w-=boxList[i].x+boxList[i].w-box->x;
					box->x=boxList[i].x+boxList[i].w;
					completebox=true;
				}
			}
			}
			break;
			case 2:
			while(box->x+box->w<SCREEN_WIDTH && !completebox)
			{
			box->w+=2;
			for( int i = 0; i < boxList.size(); i++ )
			{
				if(Collision::BoxCollision(*box,boxList[i]))
				{
					box->w=boxList[i].x-box->x;
					completebox=true;
				}
			}
			}
			break;
			}
			}


			area+=box->h*box->w;
			boxList.insert(boxList.end(),*box);
			delete box;
			delete line;
			line=NULL;
			completebox=false;
		}

	}
	//Checks if the total area of black squares is 85% of the screen
	if(area>=.85*SCREEN_WIDTH*SCREEN_HEIGHT)
	{
		lvl+=1;
		area=0;
		boxList.clear();
		ball=new Ball(SCREEN_WIDTH/3,SCREEN_HEIGHT/2,rand()%4+6,rand()%4+6,tex_ball);
		ballList.insert(ballList.end(),*ball);
		delete ball;
	}

	//Checks to see if life is zero
	if(life<=0){
		boxList.clear();
		ballList.clear();
		area=0;
		lvl=1;
		life=5;
		SDL_ShowCursor(1);
		GameState=GAME_MENU;
	}


	break;
	case GAME_PAUSE:
	break;
	}
}

//Draws surfaces to screen
void Game::OnRender() {
	//Clear screen
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	switch(GameState)
	{
	case GAME_MENU:
	CSurface::OnDraw(renderer, tex_game_title, SCREEN_WIDTH/2-100,SCREEN_HEIGHT/2-200,200,400);
	break;
	case GAME_INIT:
	break;
	case GAME_PLAY:
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	for( int i = 0; i < boxList.size(); i++ )
		SDL_RenderFillRect(renderer, &boxList[i]);
	for( int i = 0; i < ballList.size(); i++ )
		ballList[i].Draw(renderer);
	cursor->Draw(renderer);
	if(line!=NULL)
	{
		line->Draw(renderer);
	}
	break;
	case GAME_PAUSE:
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	for( int i = 0; i < boxList.size(); i++ )
		SDL_RenderFillRect(renderer, &boxList[i]);
	for( int i = 0; i < ballList.size(); i++ )
		ballList[i].Draw(renderer);
	cursor->Draw(renderer);
	if(line!=NULL)
	{
		line->Draw(renderer);
	}
	break;
	}
	SDL_RenderPresent(renderer);
}

void Game::OnCleanup() {
	TTF_Quit();
	SDL_Quit();}




//Determines which rectangle to fill when line is complete
int Game::DetermineBoxFill(){
	bool middle1=false;
	bool middle2=false;
	bool collided1=false;
	bool collided2=false;
	int x=0;
	int y=0;
	if(line->getDirection()){
		
		for( int i = 0; i < ballList.size(); i++ )
		{
			x=box->x+box->w/2;
			y=box->y;
			if(ballList[i].c.x>=box->x && ballList[i].c.x<=box->x+box->w){
				if(ballList[i].c.y<box->y){
				while(y>0 && !collided1){
					y-=1;
					if(Collision::PointBoxCollision(x,y,boxList)){
						if(y<ballList[i].c.y)
							collided1=true;
						break;
					}
				}
				if(y<=0)
					collided1=true;
				}
				else{
				while(y<SCREEN_HEIGHT && !collided2){
					y+=1;
					if(Collision::PointBoxCollision(x,y,boxList)){
						if(y>ballList[i].c.y)
							collided2=true;
						break;
					}
				}
				if(y>=SCREEN_HEIGHT)
					collided2=true;
				}
			
			}
		}

	}
	else{
		
		for( int i = 0; i < ballList.size(); i++ )
		{
			x=box->x;
			y=box->y+box->h/2;
			if(ballList[i].c.y>=box->y && ballList[i].c.y<=box->y+box->h){
				if(ballList[i].c.x<box->x){
				while(x>0 && !collided1){
					x-=1;
					if(Collision::PointBoxCollision(x,y,boxList)){
						if(x<ballList[i].c.x)
							collided1=true;
						break;
					}
				}
				if(x<=0)
					collided1=true;
				}
				else{
					while(x<SCREEN_WIDTH && !collided2){
					x+=1;
					if(Collision::PointBoxCollision(x,y,boxList)){
						if(x>ballList[i].c.x)
							collided2=true;
						break;
						
					}
					}
					if(x>=SCREEN_WIDTH)
						collided2=true;
				}
			}
		}
	}

	if(collided1)
		middle1=true;
	if(collided2)
		middle2=true;


	if(middle1 && middle2)
		return 0;
	if(!middle1 && middle2)
		return 1;
	if(middle1 && !middle2)
		return 2;
}


