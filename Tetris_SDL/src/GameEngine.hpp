#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

class GameEngine {
	bool initSuccess = false;
	bool play = false;

public:
	SDL_Window* window = nullptr;
	SDL_Surface* screenSurface = nullptr;
	TTF_Font* font = nullptr;
	int highScore = 0;

	GameEngine();
	~GameEngine();

	void run();

private:
	// void setLogFile(); TODO
	int getHighScore();
	bool saveHighScore(int score);

};

