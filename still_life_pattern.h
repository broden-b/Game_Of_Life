#ifndef STILL_LIFE_PATTERN_H
#define STILL_LIFE_PATTERN_H

#include "game_of_life.h"

bool detectBlockOrBeehive(const Board* board);
void runSimulationsBlockOrBeehive(int width, int height, int alive_cells, int steps);

#endif