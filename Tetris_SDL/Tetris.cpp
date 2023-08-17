#include <SDL.h>
#include <SDL_ttf.h>

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

#include "Tetremino.hpp"
#include "Tetris.hpp"
#include "constants.hpp"
#include "utils.hpp"

Tetris::Tetris(SDL_Window* appWindow, SDL_Surface* appWindowSurface, TTF_Font* appFont) {
	window = appWindow;
	screenSurface = appWindowSurface;
	font = appFont;

	if (!loadAssets()) {
		std::cout << "Failed to load game assets.\n";
		this->~Tetris();
	}
	
	playFieldScreenPosRect.x = SCREEN_WIDTH / 2 - playFieldBorder->w / 2;
	playFieldScreenPosRect.y = SCREEN_HEIGHT / 2 - playFieldBorder->h / 2;
	playFieldScreenPosRect.w = playFieldBorder->w;
	playFieldScreenPosRect.h = playFieldBorder->h;

	blockScreenPosRect.w = BLOCK_SIZE;
	blockScreenPosRect.h = BLOCK_SIZE;

	blockSelectRect.w = BLOCK_SIZE;
	blockSelectRect.h = BLOCK_SIZE;

	highScorePos = { playFieldScreenPosRect.x - 7 * FONT_SIZE , playFieldScreenPosRect.y + 11 * BLOCK_SIZE };
	scorePos = { playFieldScreenPosRect.x + playFieldScreenPosRect.w + BLOCK_SIZE , playFieldScreenPosRect.y + 6 * BLOCK_SIZE };
	levelPos = { playFieldScreenPosRect.x + playFieldScreenPosRect.w + BLOCK_SIZE , playFieldScreenPosRect.y + 14 * BLOCK_SIZE };

	bool success = true;
	success &= drawTextToSurface("High Score", background, highScorePos.first, highScorePos.second - FONT_SIZE);
	success &= drawTextToSurface("Score", background, scorePos.first, scorePos.second - FONT_SIZE);
	success &= drawTextToSurface("Level", background, levelPos.first, levelPos.second - FONT_SIZE);
	if (!success) {
		std::cout << "Error drawing text to background\n";
		this->~Tetris();
	}

	std::vector<BLOCK_COLOUR> playFieldRow(PLAY_FIELD_WIDTH, NO_BLOCK);
	for (int i = 0; i < PLAY_FIELD_HEIGHT; i++) {
		playField.push_back(playFieldRow);
	}

}

Tetris::~Tetris() {
	SDL_FreeSurface(background);
	background = nullptr;

	SDL_FreeSurface(playFieldBorder);
	playFieldBorder = nullptr;

	SDL_FreeSurface(blocks);
	blocks = nullptr;
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

bool Tetris::drawTextToSurface(std::string text, SDL_Surface* dst, int xPos, int yPos) {
	SDL_Surface* tmpSurface = TTF_RenderUTF8_Solid_Wrapped(font, text.c_str(), textColour, 0);
	if (!tmpSurface) {
		return false;
	}
	SDL_Rect tmpRect{};
	tmpRect.y = yPos;
	tmpRect.x = xPos;
	SDL_BlitSurface(tmpSurface, nullptr, dst, &tmpRect);
	SDL_FreeSurface(tmpSurface);
	tmpSurface = nullptr;
	return true;
}

int Tetris::playGame() {
	unsigned int frameStartTime{};
	GAME_COMMAND activeCommand{};
	spawnTetremino();
	dropStartTime = SDL_GetTicks();

	// Core game loop
	while (!gameOver && !quit) {
		frameStartTime = SDL_GetTicks();

		activeCommand = getInput();
		updateGame(activeCommand);
		drawToScreen();

		capFrameRate(frameStartTime);
	}

	if (gameOver) {
		if (gameOverAnimation()) {
			return score;
		}
	}

	return -1;
}

Tetris::GAME_COMMAND Tetris::getInput() {
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
			case SDLK_SPACE:
				playerInput = HARD_DROP;
				break;
			case SDLK_RETURN:
				playerInput = PAUSE_GAME;
				break;
			default:
				playerInput = NO_COMMAND;
			}
		}
	}
	if (!pause) {
		return playerInput;
	}
	else {
		return (playerInput == QUIT_GAME || playerInput == PAUSE_GAME) ? playerInput : NO_COMMAND;
	}
}

void Tetris::updateGame(GAME_COMMAND command) {
	bool lockPiece = false;
	
	// Player input
	switch (command) {
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
		else {
			score += 1;
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
	case HARD_DROP:
		do {
			activeTetremino.y += 1;
			score += 2;
		} while (!collisionDetected());
		activeTetremino.y -= 1;
		score -= 2;
		lockPiece = true;
		break;
	case PAUSE_GAME:
		pause = !pause;
		break;
	}

	if (pause) {
		return;
	}

	// Force down
	if (SDL_GetTicks() - dropStartTime > dropInterval) {
		activeTetremino.y += 1;
		if (collisionDetected()) {
			activeTetremino.y -= 1;
			lockPiece = true;
		}
		dropStartTime = SDL_GetTicks();
	}

	if (lockPiece) {
		for (int j = 0; j < 4; j++) {
			for (int i = 0; i < 4; i++) {
				if (activeTetremino.shape[j][i] != '.' && activeTetremino.y + j >= 0) {
					playField[activeTetremino.y + j][activeTetremino.x + i] = activeTetremino.colour;
				}
			}
		}

		int lineCountCurrent = 0;
		for (int j = 0; j < PLAY_FIELD_HEIGHT; j++) {
			if (std::find(playField[j].begin(), playField[j].end(), NO_BLOCK) == playField[j].end()) {
				lineCountCurrent++;
				for (int i = 0; i < PLAY_FIELD_WIDTH; i++) {
					playField[j][i] = WHITE;
				}
			}
		}

		score += ROW_CLEAR_POINTS[lineCountCurrent] * level;
		lineCount += lineCountCurrent;
		if (lineCount >= 10) {
			level++;
			dropInterval = (dropInterval * 7) / 8;
			lineCount -= 10;
		}

		if (lineCountCurrent) {
			drawToScreen(); // A bit hacky to call this here
			SDL_Delay(dropInterval);
			int offset = 0;
			for (int j = PLAY_FIELD_HEIGHT - 1; j >= 0; j--) {
				if (playField[j][0] == WHITE) {
					offset++;
				}
				else {
					playField[j + offset] = playField[j];
				}
			}
			for (int j = 0; j < lineCountCurrent; j++) {
				for (int i = 0; i < PLAY_FIELD_WIDTH; i++) {
					playField[j][i] = NO_BLOCK;
				}
			}
		}

		spawnTetremino();
		if (collisionDetected()) {
			gameOver = true;
			std::cout << "Game over\n";
		}
	}
}

void Tetris::drawToScreen() {
	SDL_BlitSurface(background, nullptr, screenSurface, nullptr);
	SDL_BlitSurface(playFieldBorder, nullptr, screenSurface, &playFieldScreenPosRect);
	
	// scores
	drawTextToSurface("xxxxxxx", screenSurface, highScorePos.first, highScorePos.second);
	drawTextToSurface(std::to_string(score), screenSurface, scorePos.first, scorePos.second);
	drawTextToSurface(std::to_string(level), screenSurface, levelPos.first, levelPos.second);

	// activeTetremino
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 4; i++) {
			if (activeTetremino.shape[j][i] != '.' && activeTetremino.y + j >= 0) {
				drawBlock(activeTetremino.x + i, activeTetremino.y + j, activeTetremino.colour);
			}
		}
	}

	// playField
	for (int j = 0; j < PLAY_FIELD_HEIGHT; j++) {
		for (int i = 0; i < PLAY_FIELD_WIDTH; i++) {
			if (playField[j][i] != NO_BLOCK) {
				drawBlock(i, j, playField[j][i]);
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
				if (pfy < 0) {
					continue;
				}
				if (pfx < 0 || pfx >= PLAY_FIELD_WIDTH) {
					return true;
				}
				else if (pfy >= PLAY_FIELD_HEIGHT) {
					return true;
				}
				else if (playField[pfy][pfx] != NO_BLOCK) {
					return true;
				}
			}
		}
	}
	return false;
}

void Tetris::drawBlock(int xPos, int yPos, BLOCK_COLOUR colour) {
	blockScreenPosRect.x = playFieldScreenPosRect.x + (1 + xPos) * BLOCK_SIZE;
	blockScreenPosRect.y = playFieldScreenPosRect.y + yPos * BLOCK_SIZE;
	blockSelectRect.x = colour * BLOCK_SIZE;
	SDL_BlitSurface(blocks, &blockSelectRect, screenSurface, &blockScreenPosRect);
}

bool Tetris::gameOverAnimation() {
	for (int j = PLAY_FIELD_HEIGHT - 1; j >= 0; j--) {
		if (getInput() == QUIT_GAME) {
			return false;
		}
		for (int i = 0; i < PLAY_FIELD_WIDTH; i++) {
			drawBlock(i, j, GREY);
		}
		SDL_UpdateWindowSurface(window);
		SDL_Delay(j * j);
	}

	SDL_Surface* textSurface = TTF_RenderUTF8_Solid_Wrapped(font, "Game Over", textColour, 0);
	SDL_Surface* scoreSurface = TTF_RenderUTF8_Solid_Wrapped(font, std::string("Score: ").append(std::to_string(score)).c_str(), textColour, 0);
	SDL_Surface* tmpBackground = SDL_CreateRGBSurface(0, std::max(textSurface->w, scoreSurface->w) + FONT_SIZE, textSurface->h + scoreSurface->h + FONT_SIZE, 32, 0, 0, 0, 255);
	SDL_FillRect(tmpBackground, NULL, SDL_MapRGB(tmpBackground->format, 0, 0, 0));
	
	SDL_Rect tmpRect{};
	tmpRect.x = (SCREEN_WIDTH - tmpBackground->w) / 2;
	tmpRect.y = (SCREEN_HEIGHT - tmpBackground->h) / 2;
	SDL_BlitSurface(tmpBackground, nullptr, screenSurface, &tmpRect);
	SDL_FreeSurface(tmpBackground);
	tmpRect.x = (SCREEN_WIDTH - textSurface->w) / 2;
	tmpRect.y = SCREEN_HEIGHT / 2 - textSurface->h;
	SDL_BlitSurface(textSurface, nullptr, screenSurface, &tmpRect);
	SDL_FreeSurface(textSurface);
	tmpRect.x = (SCREEN_WIDTH - scoreSurface->w) / 2;
	tmpRect.y = SCREEN_HEIGHT / 2;
	SDL_BlitSurface(scoreSurface, nullptr, screenSurface, &tmpRect);
	SDL_FreeSurface(scoreSurface);

	SDL_UpdateWindowSurface(window);

	GAME_COMMAND command = NO_COMMAND;
	while (command == NO_COMMAND) { 
		command = getInput();
		if (command == QUIT_GAME) {
			return false;
		}
	}

	return true;
}

void Tetris::spawnTetremino() {
	activeTetremino = Tetremino(rand());
	activeTetremino.x = PLAY_FIELD_WIDTH / 2 - 2;
	activeTetremino.y = -2;
}