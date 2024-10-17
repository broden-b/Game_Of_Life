#ifndef SPACESHIP_PATTERN_H
#define SPACESHIP_PATTERN_H

#include "game_of_life.h"

bool detectSpaceshipPattern(const Board* board, int& patternX, int& patternY, bool& isGlider);
void runSimulationsSpaceship(int width, int height, int alive_cells, int steps);

#endif