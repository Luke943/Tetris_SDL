extern "C" {
#include <SDL.h>
}

#include <iostream>
#include "MainWindow.h"
#include "globals.h"
#include "Tetris.h"
#include "utils.h"

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
  if (mainMenuLoop()) Tetris(window, screenSurface);
}

MainWindow::~MainWindow() {
  SDL_FreeSurface(background);
  background = nullptr;

  SDL_FreeSurface(mainMenu);
  mainMenu = nullptr;

  SDL_FreeSurface(cursor);
  cursor = nullptr;

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

  mainMenu = loadSurface("mainmenu.bmp");
  if (!mainMenu) {
      std::cout << "Error loading mainmenu.bmp. SDL_Error : " << SDL_GetError()
              << "\n";
      return false;
  }

   cursor = loadSurface("cursor.bmp");
  if (!mainMenu) {
      std::cout << "Error loading cursor.bmp. SDL_Error : " << SDL_GetError()
                << "\n";
      return false;
  }

  return true;
}

bool MainWindow::mainMenuLoop() {
  int cursorIndex = 0;
  SDL_Rect cursorRect{};
  cursorRect.x = MAINMENU_X - 30;
  cursorRect.y = MAINMENU_Y;
  SDL_Event e;
  bool quit = false;
  bool playTetris = false;

  while (!quit) {
      while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
          quit = true;
        }
        if (e.type == SDL_KEYDOWN) {
          switch (e.key.keysym.sym) {
            case SDLK_DOWN:
            case SDLK_UP:
              cursorIndex = 1 - cursorIndex;
              cursorRect.y = MAINMENU_Y + cursorIndex * MENU_LINE_SIZE;
              break;
            case SDLK_RETURN:
              if (cursorIndex == 0) playTetris = true;
              quit = true;
              break;
          }
        }
      }

      SDL_BlitSurface(mainMenu, nullptr, screenSurface, nullptr);
      SDL_BlitSurface(cursor, nullptr, screenSurface, &cursorRect);
      SDL_UpdateWindowSurface(window);
  }

  return playTetris;
}