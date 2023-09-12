#include <SDL.h>
#include <SDL_ttf.h>

#include <iostream>
#include <fstream>

#include "GameEngine.hpp"
#include "MainMenu.hpp"
#include "Tetris.hpp"
#include "constants.hpp"
#include "utils.hpp"
#include "Logging.hpp"

GameEngine::GameEngine() {
	window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (!window) {
		CERR << "Error creating window. SDL_Error : " << SDL_GetError();
		return;
	}
	screenSurface = SDL_GetWindowSurface(window);
	font = LoadFont(FONT_FILENAME);
	highScore = getHighScore();
	initSuccess = true;
}

GameEngine::~GameEngine() {
	SDL_DestroyWindow(window);
	window = nullptr;

	TTF_CloseFont(font);
	font = nullptr;
}

void GameEngine::run() {
	if (!initSuccess) {
		return;
	}
	while (true) {
		if (play) {
			Tetris tetris(this);
			int score = tetris.run();
			if (score < 0) return;
			if (score > highScore) saveHighScore(score);
			play = false;
		} else {
			MainMenu mainMenu(this);
			int status = mainMenu.run();
			if (status == -1) return;
			if (status == 1) play = true;
		}
	}
}

int GameEngine::getHighScore() {
	int highScore{};
	std::ifstream file(SAVE_FILENAME);
	if (file.is_open()) {
		file >> highScore;
		file.close();
		LOGFILE << "High score " << highScore << " found.";
		return highScore;
	}
	LOGFILE << "High score not found";
	return 0;
}

bool GameEngine::saveHighScore(int score) {
	std::ofstream file(SAVE_FILENAME);
	if (file.is_open()) {
		file << std::to_string(score);
		file.close();
		LOGFILE << "High score " << score << " saved.";
		return true;
	}
	CERR << "Failed to save high score.";
	return false;
}