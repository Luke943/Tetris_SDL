extern "C" {
#include <SDL.h>
}

#include <iostream>

#include "globals.h"
#include "MainWindow.h"
#include "utils.h"

int main(int argc, char* args[]) {
  if (initSDL()) {
    MainWindow mainWindow{};
  }
  closeSDL();
  return 0;
}
