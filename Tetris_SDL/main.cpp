extern "C" {
#include <SDL.h>
}

#include <iostream>

#include "globals.hpp"
#include "MainWindow.hpp"
#include "utils.hpp"

int main(int argc, char* args[]) {
	if (initSDL()) {
		MainWindow mainWindow{};
	}
	closeSDL();
	return 0;
}
