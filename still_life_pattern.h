#ifndef STILL_LIFE_PATTERN_H
#define STILL_LIFE_PATTERN_H

#include "game_of_life.h"
#include <string>
#include <memory>
#include <vector>

using namespace std;

class StillLifePattern {
public:
    virtual ~StillLifePattern() = default;
    virtual bool detect(const Board* board, int x, int y) const = 0;
    // Pure virtual function for pattern detection

    virtual string getName() const = 0;
    // Pure virtual function to get the pattern name

};
// Abstract base class for still life patterns
// This class defines the interface for all still life patterns

class BlockPattern : public StillLifePattern {
public:
    bool detect(const Board* board, int x, int y) const override;
    // Override the detect function for Block pattern

    string getName() const override { return "Block"; }
    // Override the getName function to return "Block"

};
// Concrete class for Block pattern, derived from StillLifePattern

class BeehivePattern : public StillLifePattern {
public:
    bool detect(const Board* board, int x, int y) const override;
    // Override the getName function to return "Beehive"

    string getName() const override { return "Beehive"; }
    // Override the getName function to return "Beehive"

};
// Concrete class for Beehive pattern, derived from StillLifePattern

bool detectStillLifePattern(const Board* board, string& patternFound);
// Function to detect any still life pattern on the board

void runSimulationsStillLife(int width, int height, int alive_cells, int steps);
// Function to run simulations to find still life patterns

#endif