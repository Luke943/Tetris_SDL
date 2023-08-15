#pragma once

#include <string>
#include <vector>

enum TETREMINO_NAME {
	HERO = 0,        // cyan
	CLEVELAND_Z,     // red
	RHODE_ISLAND_Z,  // green
	SMASHBOY,        // yellow
	TEEWEE,          // purple
	ORANGE_RICKY,    // orange
	BLUE_RICKY,      // blue
	TETREMINO_NAMES_COUNT
};

enum BLOCK_COLOUR {
	NO_BLOCK = -1,
	CYAN,
	RED,
	GREEN,
	YELLOW,
	PURPLE,
	ORANGE,
	BLUE,
	WHITE,
	GREY,
	BLOCK_COLOURS_COUNT
};

class Tetremino {
public:
	BLOCK_COLOUR colour;
	int x = 0;
	int y = 0;
	char shape[4][4];

	Tetremino(TETREMINO_NAME = HERO);
	void rotateRight();
	void rotateLeft();
	static Tetremino spawnRandom();
};
