#pragma once
#include <string>
#include <functional>
#include <SDL2/SDL.h>
class GameText
{
public:
	GameText();
	GameText(std::function<SDL_Texture* (SDL_Rect& rect)>);
	void Init(std::function<SDL_Texture* (SDL_Rect& rect)>textfunc, SDL_Rect rect);
	void SetTextFunc(std::function< SDL_Texture* (SDL_Rect& rect)> textfunc);
	void Update();
	void Draw(SDL_Renderer* renderer);
	~GameText();
	SDL_Rect rect;
	SDL_Texture* texture;
	std::function<SDL_Texture* (SDL_Rect& rect)> _update;
	std::string text;
};