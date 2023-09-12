#include <SDL.h>
#include <SDL_ttf.h>

#include <iostream>
#include <string>

#include "constants.hpp"
#include "Logging.hpp"

const int FRAME_RATE_CAP = 60;                 // frames per second
const int FRAME_TIME = 1000 / FRAME_RATE_CAP;  // milliseconds

bool Utils_Init() {
	Logging::Get().setFilename(LOG_FILENAME);
	
	LOGFILE << "Start...";
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		CERR << "SDL failed to initialize. SDL_Error: " << SDL_GetError();
		return false;
	}

	if (TTF_Init() == -1)
	{
		CERR << "SDL_ttf could not initialize. SDL_ttf Error: " << TTF_GetError();
		return false;
	}

	srand((unsigned)time(NULL));
	return true;
}

void Utils_Close() {
	TTF_Quit();
	SDL_Quit();
	LOGFILE << "Close.";
}

SDL_Surface* LoadSurface(std::string path) {
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if (!loadedSurface) {
		CERR << "Unable to load image " << path.c_str() << ". SDL Error: " << SDL_GetError() << "\n";
	}
	return loadedSurface;
}

TTF_Font* LoadFont(std::string path) {
	TTF_Font* loadedFont = TTF_OpenFont(path.c_str(), FONT_SIZE);
	if (!loadedFont) {
		CERR << "Unable to load font " << path.c_str() << ". TTF Error: " << TTF_GetError() << "\n";
	}
	return loadedFont;
}

void CapFrameRate(unsigned int startTime) {
	unsigned int timeElapsed = SDL_GetTicks() - startTime;
	if (timeElapsed < FRAME_TIME) {
		SDL_Delay(FRAME_TIME - timeElapsed);
	}
}
