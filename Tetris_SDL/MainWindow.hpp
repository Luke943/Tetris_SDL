#pragma once

#include <SDL.h>

class MainWindow {
	enum MENU_OPTION {
		PLAY = 0,
		// HIGH_SCORE, // TODO
		// CONTROLS, // TODO
		QUIT,
		MENU_OPTIONS_COUNT
	};

	SDL_Window* window = nullptr;
	SDL_Surface* screenSurface = nullptr;
	SDL_Surface* background = nullptr;
	SDL_Surface* mainMenu = nullptr;
	SDL_Surface* cursor = nullptr;
	SDL_Surface* gameOver = nullptr;

public:
	MainWindow();
	~MainWindow();
	bool loadAssets();
	void run();
};
