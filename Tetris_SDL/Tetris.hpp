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
	const int PLAY_FIELD_WIDTH = 10;
	const int PLAY_FIELD_HEIGHT = 20;

	SDL_Window* window = nullptr;
	SDL_Surface* screenSurface = nullptr;
	SDL_Surface* background = nullptr;
	SDL_Surface* playFieldBorder = nullptr;
	SDL_Surface* blocks = nullptr;

	SDL_Rect playFieldScreenPosRect{};
	SDL_Rect blockScreenPosRect{};
	SDL_Rect blockSelectRect{};

	std::vector<std::vector<BLOCK_COLOUR>> playField{};

	bool gameOver = false;
	bool quit = false;
	bool pause = false;
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

	void drawBlock(int xPos, int yPos, BLOCK_COLOUR colour);
	bool gameOverAnimation();
};
