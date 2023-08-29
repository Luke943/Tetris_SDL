#include "MainMenu.hpp"
#include "utils.hpp"

int main(int argc, char* args[]) {
	if (initSDL()) {
		GameEngine gameEngine{};
		gameEngine.run();
	}
	closeSDL();
	return 0;
}
