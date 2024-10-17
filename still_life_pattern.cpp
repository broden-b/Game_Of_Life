#include "still_life_pattern.h"
#include <iostream>
#include <windows.h>
#include <set>

using namespace std;

bool isIsolatedStill(const Board* board, int x, int y, int width, int height) {
    for (int dy = -1; dy <= height; dy++) {
        for (int dx = -1; dx <= width; dx++) {
            if (dx >= 0 && dx < width && dy >= 0 && dy < height) continue;
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && nx < board->getWidth() && ny >= 0 && ny < board->getHeight()) {
                if (board->isAlive(nx, ny)) return false;
            }
        }
    }
    return true;
}
// Helper function to check if a pattern is isolated
// Checks the surrounding cells of a potential pattern to ensure it's not part of a larger structure

bool BlockPattern::detect(const Board* board, int x, int y) const {
    if (y + 1 >= board->getHeight() || x + 1 >= board->getWidth()) return false;

    bool isBlock = board->isAlive(x, y) && board->isAlive(x + 1, y) &&
        board->isAlive(x, y + 1) && board->isAlive(x + 1, y + 1);

    return isBlock && isIsolatedStill(board, x, y, 2, 2);
}
// Implementation of the detect function for BlockPattern
// Checks for a 2x2 square of alive cells and ensures it's isolated

bool BeehivePattern::detect(const Board* board, int x, int y) const {
    if (y + 2 >= board->getHeight() || x + 3 >= board->getWidth()) return false;

    bool isBeehive = !board->isAlive(x, y) && board->isAlive(x + 1, y) && board->isAlive(x + 2, y) &&
        board->isAlive(x, y + 1) && !board->isAlive(x + 1, y + 1) && board->isAlive(x + 3, y + 1) &&
        !board->isAlive(x, y + 2) && board->isAlive(x + 1, y + 2) && board->isAlive(x + 2, y + 2);

    return isBeehive && isIsolatedStill(board, x, y, 4, 3);
}
// Implementation of the detect function for BeehivePattern
// Checks for the specific arrangement of alive and dead cells that form a beehive pattern

bool detectStillLifePattern(const Board* board, std::string& patternFound) {
    vector<unique_ptr<StillLifePattern>> patterns;
    patterns.push_back(make_unique<BlockPattern>());
    patterns.push_back(make_unique<BeehivePattern>());

    for (int y = 0; y < board->getHeight(); y++) {
        for (int x = 0; x < board->getWidth(); x++) {
            for (const auto& pattern : patterns) {
                if (pattern->detect(board, x, y)) {
                    patternFound = pattern->getName();
                    return true;
                }
            }
        }
    }
    return false;
}
// Function to detect any still life pattern on the board
// Uses polymorphism to check for different patterns
// Vector of unique pointers to StillLifePattern objects allows for polymorphic behavior and easy addition of new patterns
// Iterates through the board and checks each pattern using polymorphism

void initializeBoardStillLife(Board& board, int alive_cells) {
    set<pair<int, int>> chosenCells;
    while (chosenCells.size() < alive_cells) {
        int x = rand() % board.getWidth();
        int y = rand() % board.getHeight();
        if (chosenCells.insert({ x, y }).second) {
            board.setAlive(x, y, true);
        }
    }
}
// Function to initialize the board with random alive cells
// Uses a set to ensure unique cell positions are chosen

void runSimulationsStillLife(int width, int height, int alive_cells, int steps) {
    int simulationCount = 0;
    unsigned int seed = time(0);

    while (true) {
        simulationCount++;
        cout << "Running simulation #" << simulationCount << "..." << endl;

        Board board(width, height);
        srand(seed);
        initializeBoardStillLife(board, alive_cells);

        int patternFoundAtStep = -1;
        string patternFound;
        for (int step = 0; step <= steps; step++) {
            if (detectStillLifePattern(&board, patternFound)) {
                patternFoundAtStep = step;
                break;
            }
            board.updateBoard();
        }

        if (patternFoundAtStep != -1) {
            cout << patternFound << " pattern found in simulation #" << simulationCount
                << " at step " << patternFoundAtStep << endl;
            cout << "Replaying the simulation..." << endl;
            Sleep(500);

            // Replay the simulation
            Board replayBoard(width, height);
            srand(seed);
            initializeBoardStillLife(replayBoard, alive_cells);

            for (int step = 0; step <= patternFoundAtStep; step++) {
                cout << "Simulation #" << simulationCount << ", Step " << step << endl;
                replayBoard.display();
                Sleep(500);

                if (step < patternFoundAtStep) {
                    replayBoard.updateBoard();
                }
            }
            return;
        }
        Sleep(500);
        cout << "No still life pattern found in " << steps << " steps." << endl;
        seed = time(0);  // Get a new seed for the next simulation
    }
}
// Function to run simulations to find still life patterns
// Continues running simulations until a pattern is found
// When a pattern is found, it replays the simulation to show how the pattern formed
// Uses a random seed for each simulation to explore different initial states