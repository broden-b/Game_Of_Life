#ifndef OSCILLATOR_PATTERN_H
#define OSCILLATOR_PATTERN_H

#include "game_of_life.h"

bool detectOscillatorPattern(const Board* board);
void runSimulationsBlinkerOrToad(int width, int height, int alive_cells, int steps);

#endif