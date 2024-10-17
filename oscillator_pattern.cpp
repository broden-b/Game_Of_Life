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

bool detectOscillatorPattern(const Board* board) {
    for (int y = 0; y < board->getHeight(); y++) {
        for (int x = 0; x < board->getWidth(); x++) {
            if (detectBlinker(board, x, y) || detectToad(board, x, y)) {
                return true;
            }
        }
    }
    return false;
}

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
        for (int step = 0; step <= steps; step++) {
            if (detectOscillatorPattern(&board)) {
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
            cout << "Oscillator pattern found in simulation #" << simulationCount
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