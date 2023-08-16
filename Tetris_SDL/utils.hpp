#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include <string>

bool initSDL();
void closeSDL();
SDL_Surface* loadSurface(std::string path);
TTF_Font* loadFont(std::string path);
void capFrameRate(unsigned int startTime);
