#include "still_life_pattern.h"
#include <iostream>
#include <windows.h>
#include <set>

using namespace std;

bool detectBlockOrBeehive(const Board* board) {
    for (int y = 0; y < board->getHeight() - 1; y++) {
        for (int x = 0; x < board->getWidth() - 1; x++) {
            // Check for 2x2 block pattern
            if (board->isAlive(x, y) && board->isAlive(x + 1, y) &&
                board->isAlive(x, y + 1) && board->isAlive(x + 1, y + 1)) {

                // Check if the 2x2 block is isolated
                bool isIsolated = true;
                for (int dy = -1; dy <= 2 && isIsolated; dy++) {
                    for (int dx = -1; dx <= 2 && isIsolated; dx++) {
                        if ((dx == 0 || dx == 1) && (dy == 0 || dy == 1)) continue;
                        int nx = x + dx;
                        int ny = y + dy;
                        if (nx >= 0 && nx < board->getWidth() && ny >= 0 && ny < board->getHeight()) {
                            if (board->isAlive(nx, ny)) {
                                isIsolated = false;
                                break;
                            }
                        }
                    }
                }
                if (isIsolated) return true;
            }

            // Check for beehive pattern
            if (y < board->getHeight() - 2 && x < board->getWidth() - 3) {
                if (!board->isAlive(x, y) && board->isAlive(x + 1, y) && board->isAlive(x + 2, y) &&
                    board->isAlive(x, y + 1) && !board->isAlive(x + 1, y + 1) && board->isAlive(x + 3, y + 1) &&
                    !board->isAlive(x, y + 2) && board->isAlive(x + 1, y + 2) && board->isAlive(x + 2, y + 2)) {

                    // Check if the beehive is isolated
                    bool isIsolated = true;
                    for (int dy = -1; dy <= 3 && isIsolated; dy++) {
                        for (int dx = -1; dx <= 4 && isIsolated; dx++) {
                            if ((dx >= 0 && dx <= 3) && (dy >= 0 && dy <= 2)) continue;
                            int nx = x + dx;
                            int ny = y + dy;
                            if (nx >= 0 && nx < board->getWidth() && ny >= 0 && ny < board->getHeight()) {
                                if (board->isAlive(nx, ny)) {
                                    isIsolated = false;
                                    break;
                                }
                            }
                        }
                    }
                    if (isIsolated) return true;
                }
            }
        }
    }
    return false;
}

void initialiseBoardStill(Board& board, int alive_cells) {
    set<pair<int, int>> chosenCells;
    while (chosenCells.size() < alive_cells) {
        int x = rand() % board.getWidth();
        int y = rand() % board.getHeight();
        if (chosenCells.insert({ x, y }).second) {
            board.setAlive(x, y, true);
        }
    }
}

void runSimulationsBlockOrBeehive(int width, int height, int alive_cells, int steps) {
    int simulationCount = 0;
    unsigned int seed = time(0);

    while (true) {
        simulationCount++;
        cout << "Running simulation #" << simulationCount << "..." << endl;

        Board board(width, height);
        srand(time(0));  // Set the seed for this simulation
        initialiseBoardStill(board, alive_cells);

        int blockFoundAtStep = -1;
        for (int step = 0; step <= steps; step++) {
            if (detectBlockOrBeehive(&board)) {
                blockFoundAtStep = step;
                break;
            }
            board.updateBoard();
        }

        if (blockFoundAtStep != -1) {
            cout << "Pattern found in simulation #" << simulationCount
                << " at step " << blockFoundAtStep << endl;
            cout << "Replaying the simulation..." << endl;
            Sleep(500);

            // Replay the simulation
            Board replayBoard(width, height);
            srand(time(0));  // Reset the seed to get the same initial state
            initialiseBoardStill(replayBoard, alive_cells);

            for (int step = 0; step <= blockFoundAtStep; step++) {
                //system("cls");
                cout << "Simulation #" << simulationCount << ", Step " << step << endl;
                replayBoard.display();
                Sleep(500);

                if (step < blockFoundAtStep) {
                    replayBoard.updateBoard();
                }
            }
            return;
        }
        Sleep(500);
        cout << "No pattern found in " << steps << " steps." << endl;
        seed = time(0);  // Get a new seed for the next simulation
    }
}