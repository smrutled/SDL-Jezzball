#define _USE_MATH_DEFINES
#include <cmath>
#include "Game.h"

void Game::NewGame()
{
	boxList.clear();
	ballList.clear();
	area = 0;
	lvl = 1;
	lives = 5;
	ballList.insert(ballList.end(), std::move(Ball(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, rand() % 4 + 6, rand() % 4 + 6, tex_ball)));
	text_lives.Update();
	cursor->SetState(CURSOR_STATE::DIRECTION);
	GameState = GAME_STATE::PLAY;
}

void Game::DecreaseLives()
{
	lives--;
	text_lives.Update();
}

void Game::NextLevel()
{
	lvl += 1; // Increase lvl
	area = 0;
	boxList.clear(); // Remove box fills
	//Add another ball
	ballList.insert(ballList.end(), std::move(Ball(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 2, rand() % 4 + 6, rand() % 4 + 6, tex_ball)));
}

void Game::GameOver()
{
	boxList.clear();
	ballList.clear();
	area = 0;
	lvl = 1;
	lives = 5;
	cursor->SetState(CURSOR_STATE::ARROW);
	GameState = GAME_STATE::MENU;
}

Game::Game() {
	window = nullptr;
	Running = true;
	waittime = 1000.0f / FPS;
	framestarttime = 0;
	GameState = GAME_STATE::MENU;
	lvl = 1;
	lives = 5;
	area = 0;
	line = nullptr;
	completebox = false;
}

//Game loop
int Game::Start() {


	while (Running) {
		Loop();
	}

	OnCleanup();
	return 0;
}

//Init SDL stuff
bool Game::Init() {

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL_Init failed\n");
		return false;
	}

	if (TTF_Init() == -1)
	{
		printf("TTF_Init failed\n");
		return false;
	}

	if ((window = SDL_CreateWindow("JezzBall", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN)) == nullptr) {
		printf("SDL_CreateWindow failed\n");
		return false;
	}
	if ((renderer = SDL_CreateRenderer(window, -1,
		SDL_RENDERER_ACCELERATED)) == nullptr) {
		printf("SDL_CreateRenderer failed\n");
		return false;
	}

	if ((tex_game_title = CSurface::load_image((char*)"assets/jezzball.png", renderer)) == nullptr) {
		printf("load_image assets/jezzball.png failed\n");
		return false;
	}
	/*if ((tex_cursor = CSurface::load_image((char*)"assets/arrow.png", renderer)) == nullptr) {
		printf("load_image assets/arrow.png failed\n");
		return false;
	}*/
	if ((tex_ball = CSurface::load_image((char*)"assets/ball.png", renderer)) == nullptr) {
		printf("load_image assets/ball.png failed\n");
		return false;
	}

	if ((font = TTF_OpenFont("assets/arial.ttf", 20)) == nullptr)
	{
		printf("TTF_OpenFont assets/arial.ttf failed\n");
		return false;
	}
	if ((font_outline = TTF_OpenFont("assets/arial.ttf", 20)) == nullptr)
	{
		printf("TTF_OpenFont assets/arial.ttf failed\n");
		return false;
	}

	text_lives.SetTextFunc([this](SDL_Rect& rect) {
		TTF_SetFontOutline(font_outline, 2);
		SDL_Color white = { 255, 255, 255 };
		SDL_Color black = { 0, 0, 0 };
		std::string str = "Lives: " + std::to_string(lives);
		SDL_Surface* bg_surface = TTF_RenderText_Blended(font_outline, str.c_str(), black);
		SDL_Surface* fg_surface = TTF_RenderText_Blended(font, str.c_str(), white);
		rect.x = 2;
		rect.y = 2;
		rect.h = fg_surface->h;
		rect.w = fg_surface->w;
		SDL_SetSurfaceBlendMode(fg_surface, SDL_BLENDMODE_BLEND);
		SDL_BlitSurface(fg_surface, NULL, bg_surface, &rect);
		auto texture =  SDL_CreateTextureFromSurface(renderer, bg_surface);
		SDL_FreeSurface(fg_surface);
		SDL_FreeSurface(bg_surface);
		return texture;
	});
	
	border.x = 0;
	border.y = 0;
	border.h = SCREEN_HEIGHT;
	border.w = SCREEN_WIDTH;

	SDL_ShowCursor(0);
	cursor = new Cursor();
	

	return true;
}

void Game::Loop()
{
	while (SDL_PollEvent(&Event)) {
		Input(&Event);
	}
	Update();
	OnRender();
	delaytime = waittime - (SDL_GetTicks() - framestarttime);
	if (delaytime > 0)
		SDL_Delay((Uint32)delaytime);
	framestarttime = SDL_GetTicks();
}

void Game::OnExit() {
	Running = false;
}

void Game::Update() {
	//Used to switch between gamestates
	switch (GameState)
	{
	case GAME_STATE::MENU:
		break;
	case GAME_STATE::INIT:
		NewGame();
		break;
	case GAME_STATE::PLAY:

		//Handles all ball movement and collision
		for (int i = 0; i < ballList.size(); i++)
			ballList[i].Move(boxList);
		for (int i = 0; i < ballList.size(); i++) {
			for (int j = 1 + i; j < ballList.size() - i; j++)
			{
				if (Collision::CircleCollision(ballList[i].c, ballList[j].c)) {
					if (ballList[i].c.x <= ballList[j].c.x + ballList[j].c.r * cos((float)45 * M_PI / 180) && ballList[i].c.x >= ballList[j].c.x + ballList[j].c.r * cos((float)135 * M_PI / 180)) {
						ballList[i].vy += ballList[j].vy;
						ballList[j].vy = ballList[i].vy - ballList[j].vy;
						ballList[i].vy -= ballList[j].vy;
					}
					else {
						ballList[i].vx += ballList[j].vx;
						ballList[j].vx = ballList[i].vx - ballList[j].vx;
						ballList[i].vx -= ballList[j].vx;
					}
				}
			}
		}


		//Handles updating the line when it exists
		if (line != NULL)
		{
			line->Move();
			line->CheckBoxCollision(boxList);
			for (int i = 0; i < ballList.size(); i++)
				line->CheckBallCollision(ballList[i].c);
			if (line->CheckDestroyed())
			{
				delete line;
				line = NULL;
				DecreaseLives();
			}
			if (line != NULL)
				if (line->CheckCompleted())
				{
					box = new SDL_Rect();
					if (line->getDirection()) {
						box->x = line->Rect1.x;
						box->y = line->Rect1.y;
						box->w = line->Rect2.x + line->Rect2.w - line->Rect1.x;
						box->h = line->Rect1.h;
						switch (DetermineBoxFill())
						{
						case 0:break;
						case 1:
							while (box->y > 0 && !completebox)
							{
								box->y -= 2;
								box->h += 2;
								for (int i = 0; i < boxList.size(); i++)
								{
									if (Collision::BoxCollision(*box, boxList[i]))
									{
										box->h -= boxList[i].y + boxList[i].h - box->y;
										box->y = boxList[i].y + boxList[i].h;
										completebox = true;
									}
								}
							}
							break;
						case 2:
							while (box->y + box->h < SCREEN_HEIGHT && !completebox)
							{
								box->h += 2;
								for (int i = 0; i < boxList.size(); i++)
								{
									if (Collision::BoxCollision(*box, boxList[i]))
									{
										box->h = boxList[i].y - box->y;
										completebox = true;
									}
								}
							}
							break;
						}
					}
					else
					{
						box->x = line->Rect1.x;
						box->y = line->Rect1.y;
						box->w = line->Rect1.w;
						box->h = line->Rect2.y + line->Rect2.h - line->Rect1.y;

						switch (DetermineBoxFill())
						{
						case 0: break;
						case 1:
							while (box->x > 0 && !completebox)
							{
								box->x -= 2;
								box->w += 2;
								for (int i = 0; i < boxList.size(); i++)
								{
									if (Collision::BoxCollision(*box, boxList[i]))
									{
										box->w -= boxList[i].x + boxList[i].w - box->x;
										box->x = boxList[i].x + boxList[i].w;
										completebox = true;
									}
								}
							}
							break;
						case 2:
							while (box->x + box->w < SCREEN_WIDTH && !completebox)
							{
								box->w += 2;
								for (int i = 0; i < boxList.size(); i++)
								{
									if (Collision::BoxCollision(*box, boxList[i]))
									{
										box->w = boxList[i].x - box->x;
										completebox = true;
									}
								}
							}
							break;
						}
					}


					area += box->h * box->w;
					boxList.insert(boxList.end(), *box);
					delete box;
					delete line;
					line = NULL;
					completebox = false;
				}

		}
		//Checks if the total area of black squares is 85% of the screen
		if (area >= .85 * SCREEN_WIDTH * SCREEN_HEIGHT)
		{
			NextLevel();
			
		}

		//Checks to see if life is zero
		if (lives <= 0) {
			GameOver();
		}


		break;
	case GAME_STATE::PAUSE:
		break;
	}
}

//Draws surfaces to screen
void Game::OnRender() {
	//Clear screen
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &border);
	switch (GameState)
	{
	case GAME_STATE::MENU:
		CSurface::OnDraw(renderer, tex_game_title, SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 200, 200, 400);
		break;
	case GAME_STATE::INIT:
		break;
	case GAME_STATE::PLAY:
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		for (int i = 0; i < boxList.size(); i++)
			SDL_RenderFillRect(renderer, &boxList[i]);
		for (int i = 0; i < ballList.size(); i++)
			ballList[i].Draw(renderer);
		cursor->Draw(renderer);
		if (line != NULL)
		{
			line->Draw(renderer);
		}
		text_lives.Draw(renderer);
		break;
	case GAME_STATE::PAUSE:
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		for (int i = 0; i < boxList.size(); i++)
			SDL_RenderFillRect(renderer, &boxList[i]);
		for (int i = 0; i < ballList.size(); i++)
			ballList[i].Draw(renderer);
		cursor->Draw(renderer);
		if (line != NULL)
		{
			line->Draw(renderer);
		}
		break;
	}
	SDL_RenderPresent(renderer);
}

void Game::OnCleanup() {
	TTF_Quit();
	SDL_Quit();
}




//Determines which rectangle to fill when line is complete
int Game::DetermineBoxFill() {
	bool middle1 = false;
	bool middle2 = false;
	bool collided1 = false;
	bool collided2 = false;
	int x = 0;
	int y = 0;
	if (line->getDirection()) {

		for (int i = 0; i < ballList.size(); i++)
		{
			x = box->x + box->w / 2;
			y = box->y;
			if (ballList[i].c.x >= box->x && ballList[i].c.x <= box->x + box->w) {
				if (ballList[i].c.y < box->y) {
					while (y > 0 && !collided1) {
						y -= 1;
						if (Collision::PointBoxCollision(x, y, boxList)) {
							if (y < ballList[i].c.y)
								collided1 = true;
							break;
						}
					}
					if (y <= 0)
						collided1 = true;
				}
				else {
					while (y < SCREEN_HEIGHT && !collided2) {
						y += 1;
						if (Collision::PointBoxCollision(x, y, boxList)) {
							if (y > ballList[i].c.y)
								collided2 = true;
							break;
						}
					}
					if (y >= SCREEN_HEIGHT)
						collided2 = true;
				}

			}
		}

	}
	else {

		for (int i = 0; i < ballList.size(); i++)
		{
			x = box->x;
			y = box->y + box->h / 2;
			if (ballList[i].c.y >= box->y && ballList[i].c.y <= box->y + box->h) {
				if (ballList[i].c.x < box->x) {
					while (x > 0 && !collided1) {
						x -= 1;
						if (Collision::PointBoxCollision(x, y, boxList)) {
							if (x < ballList[i].c.x)
								collided1 = true;
							break;
						}
					}
					if (x <= 0)
						collided1 = true;
				}
				else {
					while (x < SCREEN_WIDTH && !collided2) {
						x += 1;
						if (Collision::PointBoxCollision(x, y, boxList)) {
							if (x > ballList[i].c.x)
								collided2 = true;
							break;

						}
					}
					if (x >= SCREEN_WIDTH)
						collided2 = true;
				}
			}
		}
	}

	if (collided1)
		middle1 = true;
	if (collided2)
		middle2 = true;


	if (middle1 && middle2)
		return 0;
	if (!middle1 && middle2)
		return 1;
	if (middle1 && !middle2)
		return 2;
	return 0;
}


