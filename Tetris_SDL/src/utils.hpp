#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include <string>

bool Utils_Init();
void Utils_Close();
SDL_Surface* LoadSurface(std::string path);
TTF_Font* LoadFont(std::string path);
void CapFrameRate(unsigned int startTime);
