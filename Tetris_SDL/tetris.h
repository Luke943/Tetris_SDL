#pragma once
extern "C"
{
#include<SDL.h>
}

#include <string>

#include "globals.h"

class Tetris {
public:

	char playField[PLAY_FIELD_WIDTH * PLAY_FIELD_HEIGHT];
	unsigned int blockCount = 0;
	unsigned int score = 0;
	unsigned int dropTimer = 0;
	unsigned int blockPos = 0;

	Tetris() {
		for (int i = 0; i < PLAY_FIELD_WIDTH * PLAY_FIELD_HEIGHT; i++)
			playField[i] = -1;
	}


	~Tetris() {

	}

	//Tetremino spawnTetremino();
	//bool collisionCheck();
};

