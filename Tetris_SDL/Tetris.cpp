extern "C" {
#include <SDL.h>
}

#include <iostream>

#include "globals.h"
#include "tetris.h"
#include "utils.h"

Tetris::Tetris(SDL_Window* appWindow, SDL_Surface* appSurface) {
  window = appWindow;
  screenSurface = appSurface;
  if (!loadAssets()) {
    this->~Tetris();
  }
  playTetris();
}

Tetris::~Tetris() {
  SDL_FreeSurface(background);
  background = nullptr;

  SDL_FreeSurface(playFieldBorder);
  background = nullptr;

  SDL_FreeSurface(redBlock);
  background = nullptr;
}

bool Tetris::loadAssets() {
  background = loadSurface("background.bmp");
  if (!background) {
    std::cout << "Error loading background.bmp. SDL_Error : " << SDL_GetError()
              << "\n";
    return false;
  }

  playFieldBorder = loadSurface("playfieldborder.bmp");
  if (!background) {
    std::cout << "Error loading playfieldborder.bmp. SDL_Error : "
              << SDL_GetError() << "\n";
    return false;
  }

  redBlock = loadSurface("red.bmp");
  if (!redBlock) {
    std::cout << "Error loading red.bmp. SDL_Error : " << SDL_GetError()
              << "\n";
    return false;
  }

  return true;
}

int Tetris::playTetris() {
  // Setup
  SDL_Rect playFieldRect{};
  playFieldRect.x = SCREEN_WIDTH / 2 - playFieldBorder->w / 2;
  playFieldRect.y = SCREEN_HEIGHT / 2 - playFieldBorder->h / 2;
  bool gameOver = false;
  bool quit = false;
  SDL_Event e;
  GAME_COMMAND currentCommand = NO_GAME_COMMAND;
  unsigned int dropInterval = 1000;
  unsigned int dropTimer = SDL_GetTicks();

  while (!gameOver && !quit) {
    // Get input
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        currentCommand = QUIT_GAME;
        quit = true;
      } else if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
          case SDLK_RIGHT:
            currentCommand = MOVE_RIGHT;
            break;
          case SDLK_LEFT:
            currentCommand = MOVE_LEFT;
            break;
          case SDLK_DOWN:
            currentCommand = MOVE_DOWN;
            break;
        }
      }
    }

    // Update game
    if (SDL_GetTicks() - dropTimer > gDropInterval) {
      ;
      dropTimer = SDL_GetTicks();
    }

    // Display
    SDL_BlitSurface(background, nullptr, screenSurface, nullptr);
    SDL_BlitSurface(playFieldBorder, nullptr, screenSurface, &playFieldRect);
    SDL_BlitSurface(redBlock, nullptr, screenSurface, nullptr);
    SDL_UpdateWindowSurface(window);
  }
  return true;
}
