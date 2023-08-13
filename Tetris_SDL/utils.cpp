extern "C" {
#include <SDL.h>
}

#include <iostream>
#include <string>

bool initSDL() {
  std::cout << "Start"
            << "\n";
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "SDL failed to initialize. SDL_Error: " << SDL_GetError()
              << "\n";
    return false;
  }
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
    std::cout << "Unable to load image" << path.c_str()
              << "!SDL Error : " << SDL_GetError() << "\n";
  }
  return loadedSurface;
}