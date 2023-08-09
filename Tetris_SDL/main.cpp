#include <SDL.h>

#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
bool loadImages();
void close();
SDL_Surface* loadSurface(std::string path);

Uint32 gDropInterval = 1000;

SDL_Window* gWindow = nullptr;
SDL_Surface* gScreenSurface = nullptr;
SDL_Surface* gRedBlock = nullptr;
SDL_Surface* gBackground = nullptr;


int main(int argc, char* args[]) {
	// Start up SDL and create window
	if (init()) {
		if (loadImages()) {
			bool quit = false;
			SDL_Event e;
			SDL_Rect redRect{};
			redRect.x = SCREEN_WIDTH / 2 - gRedBlock->w / 2;
			redRect.y = 0;

			unsigned int startTime = SDL_GetTicks();

			while (!quit) {
				while (SDL_PollEvent(&e)) {
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					else if (e.type == SDL_KEYDOWN) {
						switch (e.key.keysym.sym) {
						case SDLK_RIGHT:
							redRect.x += gRedBlock->w;
							break;
						case SDLK_LEFT:
							redRect.x -= gRedBlock->w;
							break;
						}
					}
				}
				if (SDL_GetTicks() - startTime > gDropInterval) {
					redRect.y += gRedBlock->h;
					startTime = SDL_GetTicks();
				}

				SDL_BlitSurface(gBackground, nullptr, gScreenSurface, nullptr);
				SDL_BlitSurface(gRedBlock, nullptr, gScreenSurface, &redRect);
				SDL_UpdateWindowSurface(gWindow);
			}
		}
	}

	close();
	return 0;
}

bool init() {
	
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "SDL failed to initialize. SDL_Error: " << SDL_GetError() << "\n";
		return false;
	}

	gWindow = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (!gWindow) {
		std::cout << "Window not created. SDL_Error: " << SDL_GetError() << "\n";
		return false;
	}

	gScreenSurface = SDL_GetWindowSurface(gWindow);

	SDL_FillRect(gScreenSurface, NULL,
		SDL_MapRGB(gScreenSurface->format, 0x00, 0x88, 0xFF));

	SDL_UpdateWindowSurface(gWindow);

	return true;
}

bool loadImages() {
	gBackground = loadSurface("background.bmp");
	if (!gBackground) {
		return false;
	}

	gRedBlock = loadSurface("red.bmp");
	if (!gRedBlock) {
		return false;
	}
	return true;
}

void close() {

	SDL_FreeSurface(gRedBlock);
	gRedBlock = nullptr;

	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;

	SDL_Quit();
}

SDL_Surface* loadSurface(std::string path) {
	// Load image at specified path
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if (!loadedSurface) {
		std::cout << "Unable to load image" << path.c_str() << "!SDL Error : " << SDL_GetError() << "\n";
	}

	return loadedSurface;
}
