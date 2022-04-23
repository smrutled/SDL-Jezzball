#include "GameText.h"

GameText::GameText()
{
}

GameText::GameText(std::function<SDL_Texture* (SDL_Rect& rect)>textfunc)
{
	_update = textfunc;
}

void GameText::Init(std::function<SDL_Texture* (SDL_Rect& rect)>textfunc, SDL_Rect rect)
{
	_update = textfunc;
	this->rect = rect;
}

void GameText::SetTextFunc(std::function<SDL_Texture*(SDL_Rect& rect)> textfunc)
{
	_update = textfunc;
}

void GameText::Draw(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}


GameText::~GameText()
{
}

void GameText::Update()
{
	if(texture)
		SDL_DestroyTexture(texture);
	texture=_update(rect);
}
