extern "C" {
#include <SDL.h>
}

#include <iostream>
#include <vector>

#include "Tetremino.hpp"
#include "Tetris.hpp"
#include "globals.hpp"
#include "utils.hpp"

Tetris::Tetris(SDL_Window* appWindow, SDL_Surface* appSurface) {
	window = appWindow;
	screenSurface = appSurface;

	if (!loadAssets()) {
		this->~Tetris();
	}

	playFieldScreenPosRect.x = SCREEN_WIDTH / 2 - playFieldBorder->w / 2;
	playFieldScreenPosRect.y = SCREEN_HEIGHT / 2 - playFieldBorder->h / 2;

	blockScreenPosRect.w = BLOCK_SIZE;
	blockScreenPosRect.h = BLOCK_SIZE;

	blockSelectRect.w = BLOCK_SIZE;
	blockSelectRect.h = BLOCK_SIZE;

	std::vector<char> playFieldRow(PLAY_FIELD_WIDTH, '.');
	for (int i = 0; i < PLAY_FIELD_HEIGHT; i++) {
		playField.push_back(playFieldRow);
	}
	activeTetremino = Tetremino::spawnRandom();

	playTetris();
}

Tetris::~Tetris() {
	SDL_FreeSurface(background);
	background = nullptr;

	SDL_FreeSurface(playFieldBorder);
	background = nullptr;

	SDL_FreeSurface(blocks);
	background = nullptr;
}

bool Tetris::loadAssets() {
	background = loadSurface("background.bmp");
	if (!background) {
		std::cout << "Error loading background.bmp. SDL_Error : " << SDL_GetError() << "\n";
		return false;
	}

	playFieldBorder = loadSurface("playfieldborder.bmp");
	if (!background) {
		std::cout << "Error loading playfieldborder.bmp. SDL_Error : " << SDL_GetError() << "\n";
		return false;
	}

	blocks = loadSurface("blocks.bmp");
	if (!blocks) {
		std::cout << "Error loading blocks.bmp. SDL_Error : " << SDL_GetError() << "\n";
		return false;
	}

	return true;
}

int Tetris::playTetris() {
	dropStartTime = SDL_GetTicks();

	// Core game loop
	while (!gameOver && !quit) {
		frameStartTime = SDL_GetTicks();

		activeCommand = getInput();
		updateGame(activeCommand);
		drawToScreen();

		capFrameRate(frameStartTime);
	}
	return true;
}

GAME_COMMAND Tetris::getInput() {
	SDL_Event e{};
	GAME_COMMAND playerInput{};

	while (SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_QUIT) {
			playerInput = QUIT_GAME;
		}
		else if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym) {
			case SDLK_RIGHT:
				playerInput = MOVE_RIGHT;
				break;
			case SDLK_LEFT:
				playerInput = MOVE_LEFT;
				break;
			case SDLK_DOWN:
				playerInput = MOVE_DOWN;
				break;
			case SDLK_x:
				playerInput = ROTATE_RIGHT;
				break;
			case SDLK_z:
				playerInput = ROTATE_LEFT;
				break;
			default:
				playerInput = NO_COMMAND;
			}
		}
	}
	return playerInput;
}

void Tetris::updateGame(GAME_COMMAND command) {
	// Player input
	switch (activeCommand) {
	case QUIT_GAME:
		quit = true;
		return;
	case MOVE_RIGHT:
		activeTetremino.x += 1;
		if (collisionDetected()) {
			activeTetremino.x -= 1;
		}
		break;
	case MOVE_LEFT:
		activeTetremino.x -= 1;
		if (collisionDetected()) {
			activeTetremino.x += 1;
		}
		break;
	case MOVE_DOWN:
		activeTetremino.y += 1;
		if (collisionDetected()) {
			activeTetremino.y -= 1;
		}
		break;
	case ROTATE_RIGHT:
		activeTetremino.rotateRight();
		if (collisionDetected()) {
			activeTetremino.rotateLeft();
		}
		break;
	case ROTATE_LEFT:
		activeTetremino.rotateLeft();
		if (collisionDetected()) {
			activeTetremino.rotateRight();
		}
		break;
	}

	// Force down
	if (SDL_GetTicks() - dropStartTime > dropInterval) {
		activeTetremino.y += 1;
		if (collisionDetected()) {
			activeTetremino.y -= 1;
			// TODO - lock in place and spawn new tetremino
		}
		dropStartTime = SDL_GetTicks();
	}
}

void Tetris::drawToScreen() {
	SDL_BlitSurface(background, nullptr, screenSurface, nullptr);
	SDL_BlitSurface(playFieldBorder, nullptr, screenSurface, &playFieldScreenPosRect);

	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 4; i++) {
			if (activeTetremino.shape[j][i] != '.') {
				blockScreenPosRect.x = playFieldScreenPosRect.x + (1 + activeTetremino.x + i) * BLOCK_SIZE;
				blockScreenPosRect.y = playFieldScreenPosRect.y + (activeTetremino.y + j) * BLOCK_SIZE;
				blockSelectRect.x = activeTetremino.name * BLOCK_SIZE;
				SDL_BlitSurface(blocks, &blockSelectRect, screenSurface, &blockScreenPosRect);
			}
		}
	}

	SDL_UpdateWindowSurface(window);
}

bool Tetris::collisionDetected() {
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 4; i++) {
			if (activeTetremino.shape[j][i] != '.') {
				int pfx = activeTetremino.x + i;
				int pfy = activeTetremino.y + j;
				if (pfx < 0 || pfx >= PLAY_FIELD_WIDTH) {
					return true; // out of bounds left/right
				}
				else if (pfy >= PLAY_FIELD_HEIGHT) {
					return true; // out of bounds bottom
				}
				else if (playField[pfy][pfx] != '.') {
					return true; // blocks collide
				}
			}
		}
	}
	return false;
}
