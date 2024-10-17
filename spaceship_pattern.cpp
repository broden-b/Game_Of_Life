#include "spaceship_pattern.h"
#include <iostream>
#include <windows.h>
#include <set>

using namespace std;

bool isIsolatedSpaceship(const Board* board, int x, int y, int width, int height) {
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
// Function to check if a pattern is isolated (surrounded by dead cells)
// Returns true if the pattern is isolated, false otherwise

bool detectGlider(const Board* board, int x, int y) {
    if (y + 2 >= board->getHeight() || x + 2 >= board->getWidth()) return false;

    bool isGlider =
        (board->isAlive(x + 1, y) && board->isAlive(x + 2, y + 1) && board->isAlive(x, y + 2) && board->isAlive(x + 1, y + 2) && board->isAlive(x + 2, y + 2)) ||
        (board->isAlive(x, y) && board->isAlive(x + 2, y + 1) && board->isAlive(x, y + 2) && board->isAlive(x + 1, y + 2) && board->isAlive(x + 2, y + 2)) ||
        (board->isAlive(x, y) && board->isAlive(x + 1, y) && board->isAlive(x + 2, y) && board->isAlive(x + 2, y + 1) && board->isAlive(x + 1, y + 2)) ||
        (board->isAlive(x, y) && board->isAlive(x + 1, y) && board->isAlive(x + 2, y) && board->isAlive(x, y + 1) && board->isAlive(x + 1, y + 2));

    return isGlider && isIsolatedSpaceship(board, x, y, 3, 3);
}
// Function to detect a Glider pattern at a given position
// Checks for all four possible orientations of a Glider
// Returns true if a Glider is found and it's isolated

bool detectLWSS(const Board* board, int x, int y) {
    if (y + 3 >= board->getHeight() || x + 4 >= board->getWidth()) return false;

    bool isLWSS =
        board->isAlive(x + 1, y) && board->isAlive(x + 4, y) &&
        board->isAlive(x, y + 1) &&
        board->isAlive(x, y + 2) && board->isAlive(x + 4, y + 2) &&
        board->isAlive(x, y + 3) && board->isAlive(x + 1, y + 3) && board->isAlive(x + 2, y + 3) && board->isAlive(x + 3, y + 3);

    return isLWSS && isIsolatedSpaceship(board, x, y, 5, 4);
}
// Function to detect a Lightweight Spaceship (LWSS) pattern at a given position
// Checks for the LWSS pattern
// Returns true if an LWSS is found and it's isolated

bool detectSpaceshipPattern(const Board* board, int& patternX, int& patternY, bool& isGlider) {
    for (int y = 0; y < board->getHeight(); y++) {
        for (int x = 0; x < board->getWidth(); x++) {
            if (detectGlider(board, x, y)) {
                patternX = x;
                patternY = y;
                isGlider = true;
                return true;
            }
            if (detectLWSS(board, x, y)) {
                patternX = x;
                patternY = y;
                isGlider = false;
                return true;
            }
        }
    }
    return false;
}
// Function to scan the entire board for Glider or LWSS patterns
// Returns true if either pattern is found, and updates the provided references with pattern information

void initialiseBoardSpaceship(Board& board, int alive_cells) {
    set<pair<int, int>> chosenCells;
    while (chosenCells.size() < alive_cells) {
        int x = rand() % board.getWidth();
        int y = rand() % board.getHeight();
        if (chosenCells.insert({ x, y }).second) {
            board.setAlive(x, y, true);
        }
    }
}
// Function to initialize the board with a random set of alive cells
// Uses a set to ensure each cell is only set alive once

bool hasPatternMoved(const Board* board, int oldX, int oldY, bool isGlider) {
    int newX, newY;
    bool dummy;
    if (!detectSpaceshipPattern(board, newX, newY, dummy)) return false;

    if (isGlider) {
        return (newX != oldX || newY != oldY) &&
            (abs(newX - oldX) <= 1 && abs(newY - oldY) <= 1);
    }
    else {
        return (newX != oldX || newY != oldY) &&
            ((newX - oldX == 2 && newY == oldY) || (newX == oldX && abs(newY - oldY) <= 1));
    }
}
// Function to check if a spaceship pattern has moved
// Returns true if the pattern has moved according to its expected behavior (Glider or LWSS)

void runSimulationsSpaceship(int width, int height, int alive_cells, int steps) {
    int simulationCount = 0;
    unsigned int seed = time(0);

    while (true) {
        simulationCount++;
        cout << "Running simulation #" << simulationCount << "..." << endl;

        Board board(width, height);
        srand(seed);
        initialiseBoardSpaceship(board, alive_cells);

        int patternFoundAtStep = -1;
        int patternX = -1, patternY = -1;
        bool isGlider = false;

        for (int step = 0; step <= steps; step++) {
            if (detectSpaceshipPattern(&board, patternX, patternY, isGlider)) {
                int cycleLength = isGlider ? 4 : 4;
                bool patternMoved = false;

                // Check if pattern completes a full cycle
                for (int i = 0; i < cycleLength; i++) {
                    board.updateBoard();
                    step++;
                    if (hasPatternMoved(&board, patternX, patternY, isGlider)) {
                        patternMoved = true;
                        break;
                    }
                }

                if (patternMoved) {
                    patternFoundAtStep = step;
                    break;
                }
            }
            board.updateBoard();
        }

        if (patternFoundAtStep != -1) {
            cout << (isGlider ? "Glider" : "LWSS") << " pattern found in simulation #" << simulationCount
                << " at step " << patternFoundAtStep << endl;
            cout << "Replaying the simulation..." << endl;
            Sleep(500);

            // Replay the simulation
            Board replayBoard(width, height);
            srand(seed);
            initialiseBoardSpaceship(replayBoard, alive_cells);

            for (int step = 0; step <= patternFoundAtStep + 4; step++) {
                cout << "Simulation #" << simulationCount << ", Step " << step << endl;
                replayBoard.display();
                Sleep(500);
                replayBoard.updateBoard();
            }
            return;
        }
        Sleep(500);
        cout << "No spaceship pattern found in " << steps << " steps." << endl;
        seed = time(0);  // Get a new seed for the next simulation
    }
}
// Function to run multiple simulations to find spaceship patterns
// Creates a new board for each simulation, initializes it randomly, and runs the simulation for a specified number of steps
// If a pattern is found, it confirms the spaceship behavior by checking if it moves correctly
// If confirmed, it replays the simulation to show how the pattern formed and moved