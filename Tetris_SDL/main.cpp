#include "MainWindow.hpp"
#include "utils.hpp"

int main(int argc, char* args[]) {
	if (initSDL()) {
		MainWindow mainWindow{};
		if (mainWindow.loadAssets()) {
			mainWindow.run();
		}
	}
	closeSDL();
	return 0;
}
