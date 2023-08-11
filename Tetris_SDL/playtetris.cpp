#include <SDL.h>

#include "tetris.h"
#include "globals.h"

enum GAME_COMMAND {
	NO_GAME_COMMAND,
	MOVE_LEFT,
	MOVE_RIGHT,
	MOVE_DOWN,
	QUIT_GAME,
	// PAUSE_GAME
	// HARD_DROP
	GAME_COMMANDS_TOTAL
};

bool playTetris() {

	// Setup
	bool gameOver = false;
	bool quit = false;
	Tetris gameWorld{};
	gameWorld.dropTimer = SDL_GetTicks();
	SDL_Event e;
	GAME_COMMAND currentCommand = NO_GAME_COMMAND;

	while (!gameOver && !quit) {

		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
			{
				currentCommand = QUIT_GAME;
				quit = true;
			}
			else if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
				case SDLK_RIGHT:
					currentCommand = MOVE_RIGHT;
					break;
				case SDLK_LEFT:
					currentCommand = MOVE_LEFT;
					break;
				case SDLK_DOWN:
					currentCommand = MOVE_DOWN;
					break;
				}
			}
		}


		if (SDL_GetTicks() - gameWorld.dropTimer > gDropInterval) {
			;
			gameWorld.dropTimer = SDL_GetTicks();
		}


	}

	
	
}
