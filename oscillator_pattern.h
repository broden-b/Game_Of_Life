#ifndef OSCILLATOR_PATTERN_H
#define OSCILLATOR_PATTERN_H

#include "game_of_life.h"

bool detectOscillatorPattern(const Board* board);
// Function declaration for detecting oscillator patterns (like Blinker or Toad)
// Takes a const pointer to a Board object, implying it won't modify the board

void runSimulationsBlinkerOrToad(int width, int height, int alive_cells, int steps);
// Function declaration for running simulations to find Blinker or Toad patterns
// Parameters include board dimensions, initial population, and maximum steps

#endif