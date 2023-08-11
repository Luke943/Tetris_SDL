#pragma once

#include <string>

#include "globals.h"

enum TETREMINO_NAMES {
	HERO,
	CLEVELAND_Z,
	RHODE_ISLAND_Z,
	SMASHBOY,
	TEEWEE,
	ORANGE_RICKY,
	BLUE_RICKY
};

std::string tetrminoShapes[7] = { "..X...X...X...X.",
								  "..X..XX..X......",
	                              ".X...XX...X.....",
	                              "..XX..XX........",
								  "..X..XX...X.....",
								  ".....XX...X...X.",
								  ".....XX..X...X.." };

class Tetremino {
	std::string shape;
	int name;
	int position;

public:
	Tetremino(TETREMINO_NAMES name) {
		shape = tetrminoShapes[name];
		position = PLAY_FIELD_WIDTH / 2 - 2;
	}

};