#include <string>
#include "Tetremino.hpp"
#include "globals.hpp"

const std::string tetreminoShapes[7] = { "..X...X...X...X.", "..X..XX..X......",
										".X...XX...X.....", "..XX..XX........",
										"..X..XX...X.....", ".....XX...X...X.",
										".....XX..X...X.." };

Tetremino::Tetremino(TETREMINO_NAME name) {
	this->name = name;
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