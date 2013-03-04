#include "Game.h"

Game::Game() {
	Display = NULL;
	Running=true;
	waittime = 1000.0f/FPS;
	framestarttime = 0;
	GameState=GAME_MENU;
	lvl=1;
	life=5;
	area=0;
	line=NULL;
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
	
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		return false;
	}
	  if( TTF_Init() == -1 )
    {
        return false;    
	}
	if((Display = SDL_SetVideoMode(SCREENWIDTH, SCREENHEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
		return false;
	}

	if(( Game_Title= CSurface::OnLoad("jezzball.png")) == NULL) {
		return false;
	}

	
	return true;
}

//Input handler
void Game::Input(SDL_Event* Event) {
	CEvent::Input(Event);
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
	gamecursor= new Cursor();
	ball=new Ball(SCREENWIDTH/2,SCREENHEIGHT/2,rand()%4+6,rand()%4+6);
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
			while(box->y+box->h<SCREENHEIGHT && !completebox)
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
			while(box->x+box->w<SCREENWIDTH && !completebox)
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
	if(area>=.85*SCREENWIDTH*SCREENHEIGHT)
	{
		lvl+=1;
		area=0;
		boxList.clear();
		ball=new Ball(SCREENWIDTH/3,SCREENHEIGHT/2,rand()%4+6,rand()%4+6);
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
	SDL_Rect Rect;
	Rect.x = 0;
	Rect.y = 0;
	Rect.w = SCREENWIDTH;
	Rect.h = SCREENHEIGHT;

	SDL_FillRect(Display, &Rect, SDL_MapRGB(Display->format, 255, 255, 255));
	
	switch(GameState)
	{
	case GAME_MENU:
	CSurface::OnDraw(Display, Game_Title, 100, 100);
	break;
	case GAME_INIT:
	break;
	case GAME_PLAY:
	for( int i = 0; i < boxList.size(); i++ )
		SDL_FillRect(Display, &boxList[i],0);
	for( int i = 0; i < ballList.size(); i++ )
		ballList[i].Draw(Display);
	gamecursor->Draw(Display);
	if(line!=NULL)
	{
		line->Draw(Display);
	}
	break;
	case GAME_PAUSE:
	for( int i = 0; i < boxList.size(); i++ )
		SDL_FillRect(Display, &boxList[i],0);
	for( int i = 0; i < ballList.size(); i++ )
		ballList[i].Draw(Display);
	gamecursor->Draw(Display);
	if(line!=NULL)
	{
		line->Draw(Display);
	}
	break;
	}
	SDL_Flip(Display);
}

void Game::OnCleanup() {
	SDL_FreeSurface(Game_Title);
	SDL_FreeSurface(Display);
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
				while(y<SCREENHEIGHT && !collided2){
					y+=1;
					if(Collision::PointBoxCollision(x,y,boxList)){
						if(y>ballList[i].c.y)
							collided2=true;
						break;
					}
				}
				if(y>=SCREENHEIGHT)
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
					while(x<SCREENWIDTH && !collided2){
					x+=1;
					if(Collision::PointBoxCollision(x,y,boxList)){
						if(x>ballList[i].c.x)
							collided2=true;
						break;
						
					}
					}
					if(x>=SCREENWIDTH)
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


