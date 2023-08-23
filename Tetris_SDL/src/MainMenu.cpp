#include <SDL.h>
#include <SDL_ttf.h>

#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include "MainMenu.hpp"
#include "constants.hpp"
#include "Tetris.hpp"
#include "utils.hpp"

MainMenu::MainMenu() {
	
	highScore = getHighScore();

	if (!loadAssets()) {
		return;
	}

	window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (!window) {
		std::cout << "Error creating window. SDL_Error : " << SDL_GetError() << "\n";
		return;
	}
	screenSurface = SDL_GetWindowSurface(window);
	initSuccess = true;
}

MainMenu::~MainMenu() {
	SDL_FreeSurface(background);
	background = nullptr;

	for (int i = 0; i < MENUS_COUNT; i++) {
		SDL_FreeSurface(menuScreens[i]);
		menuScreens[i] = nullptr;
	}

	SDL_FreeSurface(cursor);
	cursor = nullptr;

	SDL_DestroyWindow(window);
	window = nullptr;
}

bool MainMenu::loadAssets() {
	background = loadSurface(IMAGE_PATH + std::string("menubackground.bmp"));
	if (!background) {
		return false;
	}
	
	cursor = loadSurface(IMAGE_PATH + std::string("cursor.bmp"));
	if (!cursor) {
		return false;
	}

	font = loadFont(FONT_NAME);
	if (!font) {
		return false;
	}

	menuScreens[MAIN_MENU] = TTF_RenderUTF8_Solid_Wrapped(font, "PLAY\nHIGH SCORE\nCONTROLS\nQUIT", textColour, 0);
	updateHighScoreMenu();
	menuScreens[CONTROLS_MENU] = TTF_RenderUTF8_Solid_Wrapped(
		font,
		"              CONTROLS\n\n"
		"Left arrow:     Move left\n"
		"Right arrow:   Move right\n"
		"Down arrow:  Force down\n"
		"Spacebar:       Hard drop\n"
		"Z:                       Rotate left\n"
		"X:                       Rotate right\n"
		"Return:            Pause game",
		textColour, 0
	);

	return true;
}


void MainMenu::run() {
	std::cout << "Running MainMenu.\n";
	MAIN_MENU_OPTION cursorPosition = PLAY;
	SDL_Rect cursorRect{};
	cursorRect.x = (SCREEN_WIDTH - menuScreens[MAIN_MENU]->w) / 2 - 30;
	cursorRect.y = (SCREEN_HEIGHT - menuScreens[MAIN_MENU]->h) / 2;
	SDL_Event e;
	bool quit = false;
	unsigned int frameStartTime{};
	MENU activeMenu = MAIN_MENU;

	while (!quit) {
		frameStartTime = SDL_GetTicks();

		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
			if (e.type == SDL_KEYDOWN) {
				if (activeMenu != MAIN_MENU) {
					activeMenu = MAIN_MENU;
				}
				else {
					switch (e.key.keysym.sym) {
					case SDLK_DOWN:
						cursorPosition = MAIN_MENU_OPTION((cursorPosition + 1) % MAIN_MENU_OPTIONS_COUNT);
						break;
					case SDLK_UP:
						cursorPosition = MAIN_MENU_OPTION((cursorPosition - 1 + MAIN_MENU_OPTIONS_COUNT) % MAIN_MENU_OPTIONS_COUNT);
						break;
					case SDLK_RETURN:
						switch (cursorPosition) {
						case PLAY:
							quit = !playGame();
							activeMenu = MAIN_MENU;
							break;
						case HIGH_SCORES:
							activeMenu = HIGHSCORE_MENU;
							break;
						case CONTROLS:
							activeMenu = CONTROLS_MENU;
							break;
						case QUIT:
							quit = true;
							break;
						}
					}
				}
			}
		}
	
		SDL_BlitSurface(background, nullptr, screenSurface, nullptr);
		displayMenu(activeMenu);
		if (activeMenu == MAIN_MENU) {
			cursorRect.y = (SCREEN_HEIGHT - menuScreens[MAIN_MENU]->h) / 2 + cursorPosition * FONT_SIZE;
			SDL_BlitSurface(cursor, nullptr, screenSurface, &cursorRect);
		}	
		SDL_UpdateWindowSurface(window);
		
		capFrameRate(frameStartTime);
	}
}

void MainMenu::displayMenu(MENU menu) {
	menuRect.x = (SCREEN_WIDTH - menuScreens[menu]->w) / 2;
	menuRect.y = (SCREEN_HEIGHT - menuScreens[menu]->h) / 2;
	SDL_BlitSurface(menuScreens[menu], nullptr, screenSurface, &menuRect);
}

int MainMenu::getHighScore() {
	int highScore{};
	std::ifstream file(SAVE_FILE);
	if (file.is_open()) {
		file >> highScore;
		file.close();
		std::cout << "High score found\n";
		return highScore;
	}
	std::cout << "High score not found\n";
	return 1000;
}

void MainMenu::updateHighScoreMenu() {
	std::string highScoreString = "HIGH SCORE\n\n" + std::to_string(highScore);
	menuScreens[HIGHSCORE_MENU] = TTF_RenderUTF8_Solid_Wrapped(font, highScoreString.c_str(), textColour, 0);
}

bool MainMenu::saveHighScore(int score) {
	std::ofstream file(SAVE_FILE);
	if (file.is_open()) {
		file << std::to_string(score);
		file.close();
		std::cout << "High score saved\n";
		return true;
	}
	std::cout << "Failed to save high score\n";
	return false;
}


bool MainMenu::playGame() {
	std::cout << "Starting game.\n";
	Tetris tetris(window, screenSurface, font, highScore);
	if (!tetris.initSuccess) {
		return false;
	}
	int	score = tetris.playGame();
	tetris.~Tetris();
	if (score < 0) {
		return false;
	}
	else if (score > highScore) {
		highScore = score;
		saveHighScore(score);
		updateHighScoreMenu();
		return true;
	}
}
