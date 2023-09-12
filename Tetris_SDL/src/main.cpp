#include <fstream>
#include <iostream>

#include "GameEngine.hpp"
#include "utils.hpp"
#include "constants.hpp"

int main(int argc, char* args[]) {
	if (Utils_Init()) {
		GameEngine gameEngine{};
		gameEngine.run();
	}
	Utils_Close();
	return 0;
}
