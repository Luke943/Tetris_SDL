#include <fstream>
#include <iostream>

#include "GameEngine.hpp"
#include "utils.hpp"

int main(int argc, char* args[]) {
	if (initSDL()) {
		GameEngine gameEngine{};
		gameEngine.run();
	}
	closeSDL();
	return 0;
}
