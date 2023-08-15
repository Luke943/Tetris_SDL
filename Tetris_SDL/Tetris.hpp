#pragma once

#include <SDL.h>

#include <string>
#include "Tetremino.hpp"

class Tetris {
	enum GAME_COMMAND {
		NO_COMMAND,
		MOVE_LEFT,
		MOVE_RIGHT,
		MOVE_DOWN,
		ROTATE_RIGHT,
		ROTATE_LEFT,
		HARD_DROP,
		PAUSE_GAME,
		QUIT_GAME,
		GAME_COMMANDS_TOTAL
	};
	
	const int ROW_CLEAR_POINTS[5] = { 0, 100, 300, 500, 800 };

	SDL_Window* window = nullptr;
	SDL_Surface* screenSurface = nullptr;
	SDL_Surface* background = nullptr;
	SDL_Surface* playFieldBorder = nullptr;
	SDL_Surface* blocks = nullptr;

	SDL_Rect playFieldScreenPosRect{};
	SDL_Rect blockScreenPosRect{};
	SDL_Rect blockSelectRect{};

	std::vector<std::vector<char>> playField{};

	bool gameOver = false;
	bool quit = false;
	unsigned int lineCount = 0;
	unsigned int score = 0;
	unsigned int level = 1;
	unsigned int dropInterval = 800;
	unsigned int dropStartTime{};
	Tetremino activeTetremino{};

public:
	Tetris(SDL_Window* appWindow = nullptr, SDL_Surface* appSurface = nullptr);
	~Tetris();
	int playGame();

private:
	bool loadAssets();
	GAME_COMMAND getInput();
	void updateGame(GAME_COMMAND command);
	void drawToScreen();

	bool collisionDetected();
	// void tetreminoLock();
	// int lineCheck();
};
