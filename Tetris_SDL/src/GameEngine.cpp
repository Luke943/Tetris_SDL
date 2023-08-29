#include <SDL.h>
#include <SDL_ttf.h>

#include <iostream>
#include <fstream>

#include "GameEngine.hpp"
#include "MainMenu.hpp"
#include "Tetris.hpp"
#include "constants.hpp"
#include "utils.hpp"

GameEngine::GameEngine() {
	window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (!window) {
		std::cout << "Error creating window. SDL_Error : " << SDL_GetError() << "\n";
		return;
	}
	screenSurface = SDL_GetWindowSurface(window);
	font = loadFont(FONT_NAME);
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
	std::ifstream file(SAVE_FILE);
	if (file.is_open()) {
		file >> highScore;
		file.close();
		std::cout << "High score " << highScore << " found\n";
		return highScore;
	}
	std::cout << "High score not found\n";
	return 0;
}

bool GameEngine::saveHighScore(int score) {
	std::ofstream file(SAVE_FILE);
	if (file.is_open()) {
		file << std::to_string(score);
		file.close();
		std::cout << "High score " << score << " saved\n";
		return true;
	}
	std::cout << "Failed to save high score\n";
	return false;
}