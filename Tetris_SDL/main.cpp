#include "MainMenu.hpp"
#include "utils.hpp"

int main(int argc, char* args[]) {
	if (initSDL()) {
		MainMenu mainMenu{};
		mainMenu.run();
	}
	closeSDL();
	return 0;
}
