#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

class MainMenu {
	enum MAIN_MENU_OPTION {
		PLAY = 0,
		HIGH_SCORES,
		CONTROLS,
		QUIT,
		MAIN_MENU_OPTIONS_COUNT
	};

	enum MENU {
		MAIN_MENU = 0,
		HIGHSCORE_MENU,
		CONTROLS_MENU,
		MENUS_COUNT
	};
	
	SDL_Window* window = nullptr;
	SDL_Surface* screenSurface = nullptr;
	SDL_Surface* background = nullptr;
	TTF_Font* font = nullptr;
	SDL_Surface* menuScreens[MENUS_COUNT]{};
	SDL_Surface* cursor = nullptr;
	SDL_Color textColour = { 0xff, 0xff, 0xff };
	SDL_Rect menuRect{};

	int highScore{};

public:
	bool initSuccess = false;

	MainMenu();
	~MainMenu();
	void run();

private:
	bool loadAssets();
	void displayMenu(MENU menu);
	int getHighScore();
	bool saveHighScore(int score);
	void updateHighScoreMenu();
	bool playGame();
};
