#pragma once

#include <string>
#include <vector>

enum TETREMINO_NAME {
	HERO,            // cyan
	CLEVELAND_Z,     // red
	RHODE_ISLAND_Z,  // green
	SMASHBOY,        // yellow
	TEEWEE,          // purple
	ORANGE_RICKY,    // orange
	BLUE_RICKY,      // blue
	TETREMINO_NAMES_COUNT
};

class Tetremino {
public:
	TETREMINO_NAME name;
	int x = 0;
	int y = 0;
	char shape[4][4];

	Tetremino(TETREMINO_NAME = HERO);
	void rotateRight();
	void rotateLeft();
	static Tetremino spawnRandom();
};
