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

Tetremino::Tetremino(TETREMINO_NAME name) {
	colour = BLOCK_COLOUR(name);
	x = PLAY_FIELD_WIDTH / 2 - 2;
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 4; i++) {
			shape[j][i] = tetreminoShapes[name][j * 4 + i];
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

Tetremino Tetremino::spawnRandom() {
	int i = rand() % TETREMINO_NAMES_COUNT;
	return Tetremino(TETREMINO_NAME(i));
}