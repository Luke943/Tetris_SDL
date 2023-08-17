#include "MainMenu.hpp"
#include "utils.hpp"

int main(int argc, char* args[]) {
	if (initSDL()) {
		MainMenu mainMenu{};
		if (mainMenu.loadAssets()) {
			mainMenu.run();
		}
	}
	closeSDL();
	return 0;
}
