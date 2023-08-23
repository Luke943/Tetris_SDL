#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include <string>
#include <utility>
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

	enum TEXT_BOXES {
		SCORE_BOX,
		LEVEL_BOX,
		HIGHSCORE_BOX,
		PAUSE_BOX,
		TEXT_BOXES_TOTAL
	};
	
	const int ROW_CLEAR_POINTS[5] = { 0, 100, 300, 500, 800 };
	const int PLAY_FIELD_WIDTH = 10;
	const int PLAY_FIELD_HEIGHT = 20;

	SDL_Window* window = nullptr;
	SDL_Surface* screenSurface = nullptr;
	TTF_Font* font = nullptr;
	SDL_Surface* background = nullptr;
	SDL_Surface* playFieldBorder = nullptr;
	SDL_Surface* blocks = nullptr;
	SDL_Surface* pauseSurface = nullptr;

	SDL_Color textColour = { 0xff, 0xff, 0xff };

	SDL_Rect playFieldScreenPosRect{};
	SDL_Rect blockScreenPosRect{};
	SDL_Rect blockSelectRect{};
	SDL_Rect textBoxRect[TEXT_BOXES_TOTAL];

	std::vector<std::vector<BLOCK_COLOUR>> playField{};

	int highScore = 0;
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
	bool initSuccess = false;

	Tetris(SDL_Window* appWindow = nullptr, SDL_Surface* appWindowSurface = nullptr, TTF_Font* appFont = nullptr, int appHighscore = 0);
	~Tetris();
	int playGame();

private:
	bool loadAssets();
	bool createTextBoxes();
	bool drawTextToSurface(std::string srcText, SDL_Surface* dst, SDL_Rect* dstRect);

	GAME_COMMAND getInput();
	void updateGame(GAME_COMMAND command);
	void drawToScreen();

	void spawnTetremino();
	bool collisionDetected();

	void drawBlock(int xPos, int yPos, BLOCK_COLOUR colour);
	bool gameOverAnimation();
};
