#include <SDL.h>

#include <iostream>
#include <string>
#include "constants.hpp"

const int FRAME_RATE_CAP = 60;                 // frames per second
const int FRAME_TIME = 1000 / FRAME_RATE_CAP;  // milliseconds

bool initSDL() {
	std::cout << "Start" << "\n";
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "SDL failed to initialize. SDL_Error: " << SDL_GetError() << "\n";
		return false;
	}
	srand((unsigned)time(NULL));
	return true;
}

void closeSDL() {
	SDL_Quit();
	std::cout << "Close" << "\n";
}

SDL_Surface* loadSurface(std::string path) {
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if (!loadedSurface) {
		std::cout << "Unable to load image" << path.c_str() << "!SDL Error : " << SDL_GetError() << "\n";
	}
	return loadedSurface;
}

void capFrameRate(unsigned int startTime) {
	unsigned int timeElapsed = SDL_GetTicks() - startTime;
	if (timeElapsed < FRAME_TIME) {
		SDL_Delay(FRAME_TIME - timeElapsed);
	}
}
