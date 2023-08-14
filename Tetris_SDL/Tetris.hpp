#pragma once
extern "C" {
#include <SDL.h>
}

#include <string>
#include "globals.hpp"
#include "Tetremino.hpp"

enum GAME_COMMAND {
	NO_COMMAND,
	MOVE_LEFT,
	MOVE_RIGHT,
	MOVE_DOWN,
	ROTATE_RIGHT,
	ROTATE_LEFT,
	QUIT_GAME,
	// PAUSE_GAME,
	// HARD_DROP,
	GAME_COMMANDS_TOTAL
};

class Tetris {
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
	unsigned int pieceCount = 0;
	unsigned int dropInterval = 1000;
	unsigned int dropStartTime{};
	unsigned int frameStartTime{};
	GAME_COMMAND activeCommand{};
	Tetremino activeTetremino{};

public:
	Tetris(SDL_Window* appWindow = nullptr, SDL_Surface* appSurface = nullptr);
	~Tetris();

private:
	bool loadAssets();
	int playTetris();
	GAME_COMMAND getInput();
	void updateGame(GAME_COMMAND command);
	void drawToScreen();

	bool collisionDetected();
	// void tetreminoLock();
	// int lineCheck();
};
