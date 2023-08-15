#include <SDL.h>

#include <iostream>
#include "MainWindow.hpp"
#include "constants.hpp"
#include "Tetris.hpp"
#include "utils.hpp"

enum MENU_OPTION {
	PLAY = 0,
	// HIGH_SCORE, // TODO
	// CONTROLS, // TODO
	QUIT,
	MENU_OPTIONS_COUNT
};

MainWindow::MainWindow() {
	if (!loadAssets()) {
		this->~MainWindow();
	}

	window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (!window) {
		std::cout << "Error creating window. SDL_Error : " << SDL_GetError() << "\n";
		this->~MainWindow();
	}
	screenSurface = SDL_GetWindowSurface(window);
}

MainWindow::~MainWindow() {
	SDL_FreeSurface(background);
	background = nullptr;

	SDL_FreeSurface(mainMenu);
	mainMenu = nullptr;

	SDL_FreeSurface(cursor);
	cursor = nullptr;

	SDL_FreeSurface(gameOver);
	gameOver = nullptr;

	SDL_DestroyWindow(window);
	window = nullptr;
}

bool MainWindow::loadAssets() {
	background = loadSurface("background.bmp");
	if (!background) {
		std::cout << "Error loading background.bmp. SDL_Error : " << SDL_GetError() << "\n";
		return false;
	}

	mainMenu = loadSurface("mainmenu.bmp");
	if (!mainMenu) {
		std::cout << "Error loading mainmenu.bmp. SDL_Error : " << SDL_GetError() << "\n";
		return false;
	}

	gameOver = loadSurface("gameover.bmp");
	if (!mainMenu) {
		std::cout << "Error loading gameover.bmp. SDL_Error : " << SDL_GetError() << "\n";
		return false;
	}

	cursor = loadSurface("cursor.bmp");
	if (!mainMenu) {
		std::cout << "Error loading cursor.bmp. SDL_Error : " << SDL_GetError() << "\n";
		return false;
	}

	return true;
}

void MainWindow::run() {
	MENU_OPTION cursorPosition = PLAY;
	SDL_Rect cursorRect{};
	cursorRect.x = MAINMENU_X - 30;
	cursorRect.y = MAINMENU_Y;
	SDL_Rect menuRect{};
	SDL_Event e;
	bool mainMenuView = true;
	bool play = false;
	bool quit = false;
	unsigned int frameStartTime{};

	while (!quit) {
		frameStartTime = SDL_GetTicks();

		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
			if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
				case SDLK_DOWN:
					cursorPosition = MENU_OPTION((cursorPosition + 1) % MENU_OPTIONS_COUNT);
					break;
				case SDLK_UP:
					cursorPosition = MENU_OPTION((cursorPosition - 1) % MENU_OPTIONS_COUNT);
					break;
				case SDLK_RETURN:
					if (mainMenuView) {
						switch (cursorPosition) {
						case PLAY:
							play = true;
							break;
						case QUIT:
							quit = true;
							break;
						}
					}
					mainMenuView = !mainMenuView;
					break;
				}
			}
		}
		if (play) {
			Tetris tetris(window, screenSurface);
			int score = tetris.playGame();
			if (score < 0) {
				quit = true;
			}
			else {
				play = false;
				menuRect.x = (SCREEN_WIDTH - gameOver->w) / 2;
				menuRect.y = (SCREEN_HEIGHT - gameOver->h) / 2;
				SDL_BlitSurface(gameOver, nullptr, screenSurface, &menuRect);
			}
		}
		
		if (mainMenuView) {
			SDL_BlitSurface(background, nullptr, screenSurface, nullptr);
			SDL_BlitSurface(mainMenu, nullptr, screenSurface, nullptr);
			cursorRect.y = MAINMENU_Y + cursorPosition * MENU_LINE_SIZE;
			SDL_BlitSurface(cursor, nullptr, screenSurface, &cursorRect);
		}
		
		SDL_UpdateWindowSurface(window);
		capFrameRate(frameStartTime);
	}
}