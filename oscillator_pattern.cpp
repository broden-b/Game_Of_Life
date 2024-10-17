#include "oscillator_pattern.h"
#include <iostream>
#include <windows.h>
#include <set>

using namespace std;

bool detectBlinker(const Board* board, int x, int y) {
    if (y + 2 >= board->getHeight() || x + 2 >= board->getWidth()) return false;

    // Vertical blinker
    if (board->isAlive(x, y) && board->isAlive(x, y + 1) && board->isAlive(x, y + 2) &&
        !board->isAlive(x - 1, y + 1) && !board->isAlive(x + 1, y + 1)) {
        return true;
    }

    // Horizontal blinker
    if (board->isAlive(x, y) && board->isAlive(x + 1, y) && board->isAlive(x + 2, y) &&
        !board->isAlive(x + 1, y - 1) && !board->isAlive(x + 1, y + 1)) {
        return true;
    }

    return false;
}
// Function to detect a Blinker pattern at a given position
// Checks for both vertical and horizontal orientations
// Ensures the pattern is isolated (surrounded by dead cells in key positions)

bool detectToad(const Board* board, int x, int y) {
    if (y + 2 >= board->getHeight() || x + 3 >= board->getWidth()) return false;

    // First toad state
    if (!board->isAlive(x, y) && board->isAlive(x + 1, y) && board->isAlive(x + 2, y) && board->isAlive(x + 3, y) &&
        board->isAlive(x, y + 1) && board->isAlive(x + 1, y + 1) && board->isAlive(x + 2, y + 1) && !board->isAlive(x + 3, y + 1)) {
        return true;
    }

    // Second toad state
    if (board->isAlive(x + 1, y) && board->isAlive(x + 2, y) &&
        board->isAlive(x, y + 1) && !board->isAlive(x + 3, y + 1) &&
        board->isAlive(x, y + 2) && board->isAlive(x + 3, y + 2)) {
        return true;
    }

    return false;
}
// Function to detect a Toad pattern at a given position
// Checks for both states of the Toad oscillator

bool detectOscillatorPattern(const Board* board, string& patternFound) {
    for (int y = 0; y < board->getHeight(); y++) {
        for (int x = 0; x < board->getWidth(); x++) {
            if (detectBlinker(board, x, y)) {
                patternFound = "Blinker";
                return true;
            }
            if (detectToad(board, x, y)) {
                patternFound = "Toad";
                return true;
            }
        }
    }
    return false;
}
// Function to scan the entire board for Blinker or Toad patterns
// Returns true if either pattern is found, and sets the patternFound string accordingly

void initialiseBoardOsc(Board& board, int alive_cells) {
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

void runSimulationsBlinkerOrToad(int width, int height, int alive_cells, int steps) {
    int simulationCount = 0;
    unsigned int seed = time(0);

    while (true) {
        simulationCount++;
        cout << "Running simulation #" << simulationCount << "..." << endl;

        Board board(width, height);
        srand(seed);  // Set the seed for this simulation
        initialiseBoardOsc(board, alive_cells);

        int patternFoundAtStep = -1;
        bool patternFound = false;
        string oscillatorType;
        for (int step = 0; step <= steps; step++) {
            if (detectOscillatorPattern(&board, oscillatorType)) {
                if (patternFoundAtStep == -1) {
                    patternFoundAtStep = step;
                }
                else if (step > patternFoundAtStep + 1) {
                    patternFound = true;
                    break;
                }
            }
            board.updateBoard();
        }

        if (patternFound) {
            cout << oscillatorType << " pattern found in simulation #" << simulationCount
                << " at step " << patternFoundAtStep << endl;
            cout << "Replaying the simulation..." << endl;
            Sleep(500);

            // Replay the simulation
            Board replayBoard(width, height);
            srand(seed);  // Reset the seed to get the same initial state
            initialiseBoardOsc(replayBoard, alive_cells);

            for (int step = 0; step <= patternFoundAtStep + 2; step++) {
                cout << "Simulation #" << simulationCount << ", Step " << step << endl;
                replayBoard.display();
                Sleep(500);
                replayBoard.updateBoard();
            }
            return;
        }
        Sleep(500);
        cout << "No oscillator pattern found in " << steps << " steps." << endl;
        seed = time(0);  // Get a new seed for the next simulation
    }
}
// Function to run multiple simulations to find Blinker or Toad patterns
// Creates a new board for each simulation, initializes it randomly, and runs the simulation for a specified number of steps
// If a pattern is found, it confirms the oscillation by checking if it persists for more than one step
// If confirmed, it replays the simulation to show how the pattern formed
// Continues running new simulations with different random seeds until a pattern is found
// Uses Sleep() to provide visual pauses between steps and simulations for better user experience