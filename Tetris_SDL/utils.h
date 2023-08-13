#pragma once

extern "C" {
#include <SDL.h>
}

#include <string>

bool initSDL();
void closeSDL();
SDL_Surface* loadSurface(std::string path);
