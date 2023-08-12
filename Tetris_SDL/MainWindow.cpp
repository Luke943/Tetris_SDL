extern "C" {
#include <SDL.h>
}

#include <iostream>
#include "MainWindow.h"
#include "globals.h"

SDL_Surface* loadSurface(std::string path) {
  SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
  return loadedSurface;
}

MainWindow::MainWindow() {
  if (!loadAssets()) {
    this->~MainWindow();
  }

  window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                            SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (!window) {
    std::cout << "Error creating window. SDL_Error : " << SDL_GetError()
            << "\n";
      this->~MainWindow();
  }
  screenSurface = SDL_GetWindowSurface(window);
  runLoop();
}

MainWindow::~MainWindow() {
  SDL_FreeSurface(background);
  background = nullptr;

  SDL_FreeSurface(playFieldBorder);
  playFieldBorder = nullptr;

  SDL_FreeSurface(redBlock);
  redBlock = nullptr;

  SDL_FreeSurface(mainMenu);
  mainMenu = nullptr;

  SDL_DestroyWindow(window);
  window = nullptr;
}

bool MainWindow::loadAssets() {
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

  mainMenu = loadSurface("mainmenu.bmp");
  if (!mainMenu) {
      std::cout << "Error loading mainmenu.bmp. SDL_Error : " << SDL_GetError()
              << "\n";
      return false;
  }

  return true;
}

bool MainWindow::runLoop() {
  SDL_Event e;
  bool quit = false;
  while (!quit) {
      while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
          quit = true;
        }
        if (e.type == SDL_KEYDOWN) {
          switch (e.key.keysym.sym) {
            case SDLK_RIGHT:;
              break;
            case SDLK_LEFT:;
              break;
            case SDLK_DOWN:;
          }
        }
      }
      SDL_BlitSurface(mainMenu, nullptr, screenSurface, nullptr);
      SDL_UpdateWindowSurface(window);
  }
  return true;
}