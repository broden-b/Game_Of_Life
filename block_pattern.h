#ifndef BLOCK_PATTERN_H
#define BLOCK_PATTERN_H

#include "game_of_life.h"

bool detectBlockPattern(const Board* board);
void runSimulationsUntilBlockFound(int width, int height, int alive_cells, int steps);

#endif // BLOCK_FINDER_H