#pragma once

extern "C" {
#include <SDL.h>
}

class MainWindow {
	SDL_Window* window = nullptr;
	SDL_Surface* screenSurface = nullptr;
	SDL_Surface* redBlock = nullptr;
	SDL_Surface* background = nullptr;
	SDL_Surface* playFieldBorder = nullptr;
	SDL_Surface* mainMenu = nullptr;
	SDL_Surface* cursor = nullptr;

public:
	MainWindow();
	~MainWindow();

private:
	bool loadAssets();
	bool mainMenuLoop();

};
