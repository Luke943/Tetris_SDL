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
  BLUE_RICKY,
  TETREMINO_NAMES_COUNT
};

std::string tetreminoShapes[7] = {"..X...X...X...X.", "..X..XX..X......",
                                  ".X...XX...X.....", "..XX..XX........",
                                  "..X..XX...X.....", ".....XX...X...X.",
                                  ".....XX..X...X.."};

class Tetremino {
  int name;

 public:
  int posX = PLAY_FIELD_WIDTH / 2 - 2;
  int posY = 0;
  int rotation = 0;

  Tetremino(TETREMINO_NAMES name) { this->name = name; }

  void rotate() {}
};