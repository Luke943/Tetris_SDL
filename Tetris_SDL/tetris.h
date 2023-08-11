#pragma once

#include <SDL.h>
#include <string>

#include "globals.h"

class Tetris {
public:

	std::string playField;
	unsigned int blockCount = 0;
	unsigned int score = 0;
	unsigned int dropTimer = 0;
	unsigned int blockPos = 0;

	Tetris() {
		for (int i = 0; i < PLAY_FIELD_WIDTH * PLAY_FIELD_HEIGHT; i++)
			playField.push_back('.');


	}

	~Tetris() {

	}

	//Tetremino spawnTetremino();
	//bool collisionCheck();
};
