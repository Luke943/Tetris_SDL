#pragma once

#include <string>
#include <vector>

enum BLOCK_COLOUR {
	NO_BLOCK = -1,
	CYAN,     // HERO
	RED,      // CLEVELAND_Z
	GREEN,    // RHODE_ISLAND_Z
	YELLOW,   // SMASHBOY
	PURPLE,   // TEEWEE
	ORANGE,   // ORANGE_RICKY
	BLUE,     // BLUE_RICKY
	WHITE,    // LINE COMPLETE
	GREY,     // GAME OVER
	BLOCK_COLOURS_COUNT
};

class Tetremino {
public:
	Tetremino(int i = 0);
	void rotateRight();
	void rotateLeft();

	BLOCK_COLOUR colour;
	int x = 0;
	int y = 0;
	char shape[4][4];
};
