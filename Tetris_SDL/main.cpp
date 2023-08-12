extern "C" {
#include <SDL.h>
}

#include <iostream>

#include "MainWindow.h"
#include "globals.h"

bool init();
void close();

int main(int argc, char* args[]) {
  std::cout << "Start" << "\n";
  if (init()) {
    MainWindow mainWindow{};
  }
  close();
  return 0;
}

bool init() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "SDL failed to initialize. SDL_Error: " << SDL_GetError()
              << "\n";
    return false;
  }
  return true;
}

void close() {
  SDL_Quit();
  std::cout << "Close" << "\n";
}
