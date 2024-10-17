#ifndef SPACESHIP_PATTERN_H
#define SPACESHIP_PATTERN_H

#include "game_of_life.h"

bool detectSpaceshipPattern(const Board* board, int& patternX, int& patternY, bool& isGlider);
// Function declaration for detecting spaceship patterns (Glider or LWSS)
// Takes a const pointer to a Board object, and references to store pattern information
// Returns true if a spaceship pattern is found, and updates the provided references

void runSimulationsSpaceship(int width, int height, int alive_cells, int steps);
// Function declaration for running simulations to find spaceship patterns
// Parameters include board dimensions, initial population, and maximum steps

#endif