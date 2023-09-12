#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

class GameEngine {
public:
	GameEngine();
	~GameEngine();
	
	void run();

	SDL_Window* window = nullptr;
	SDL_Surface* screenSurface = nullptr;
	TTF_Font* font = nullptr;
	int highScore = 0;

private:
	int getHighScore();
	bool saveHighScore(int score);

	bool initSuccess = false;
	bool play = false;
};

