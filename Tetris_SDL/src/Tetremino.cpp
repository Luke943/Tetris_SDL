#include <string>

#include "Tetremino.hpp"
#include "constants.hpp"

const std::string tetreminoShapes[7] = { "..X...X...X...X.", // HERO
										 "..X..XX..X......", // CLEVELAND_Z
										 ".X...XX...X.....", // RHODE_ISLAND_Z
										 ".....XX..XX.....", // SMASHBOY
										 "..X..XX...X.....", // TEEWEE
										 ".....XX...X...X.", // ORANGE_RICKY
										 ".....XX..X...X.."  // BLUE_RICKY
};

Tetremino::Tetremino(int i) {
	colour = BLOCK_COLOUR(i % 7);
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 4; i++) {
			shape[j][i] = tetreminoShapes[colour][j * 4 + i];
		}
	}
}

void Tetremino::rotateRight() {
	char tmp[4][4]{};
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 4; i++) tmp[i][3 - j] = shape[j][i];
	}
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 4; i++) shape[j][i] = tmp[j][i];
	}
}

void Tetremino::rotateLeft() {
	char tmp[4][4]{};
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 4; i++) tmp[j][i] = shape[i][3 - j];
	}
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 4; i++) shape[j][i] = tmp[j][i];
	}
}
