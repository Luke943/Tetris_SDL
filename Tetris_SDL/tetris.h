#pragma once
extern "C" {
#include <SDL.h>
}

#include <string>

#include "globals.h"

enum GAME_COMMAND {
  NO_GAME_COMMAND,
  MOVE_LEFT,
  MOVE_RIGHT,
  MOVE_DOWN,
  QUIT_GAME,
  // PAUSE_GAME
  // HARD_DROP
  GAME_COMMANDS_TOTAL
};

class Tetris {
  SDL_Window* window = nullptr;
  SDL_Surface* screenSurface = nullptr;
  SDL_Surface* background = nullptr;
  SDL_Surface* playFieldBorder = nullptr;
  SDL_Surface* redBlock = nullptr;

 public:
  Tetris(SDL_Window* appWindow = nullptr, SDL_Surface* appSurface = nullptr);
  ~Tetris();

 private:
  bool loadAssets();
  int playTetris();

  // Tetremino spawnTetremino();
  // bool collisionCheck();
};
