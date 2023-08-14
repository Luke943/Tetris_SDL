extern "C" {
#include <SDL.h>
}

//#include <cstdlib>
//#include <ctime>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "globals.hpp"

bool initSDL() {
	std::cout << "Start"
		<< "\n";
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "SDL failed to initialize. SDL_Error: " << SDL_GetError() << "\n";
		return false;
	}
	srand((unsigned)time(NULL));
	return true;
}

void closeSDL() {
	SDL_Quit();
	std::cout << "Close"
		<< "\n";
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
		std::this_thread::sleep_for(std::chrono::milliseconds(FRAME_TIME - timeElapsed));
	}
}
