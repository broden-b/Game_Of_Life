#include "block_pattern.h"
#include <iostream>
#include <windows.h>
#include <set>
#include <vector>

using namespace std;

bool detectBlockPattern(const Board* board) {
    for (int y = 0; y < board->getHeight() - 1; y++) {
        for (int x = 0; x < board->getWidth() - 1; x++) {
            // Check if there's a 2x2 block of living cells
            if (board->isAlive(x, y) && board->isAlive(x + 1, y) &&
                board->isAlive(x, y + 1) && board->isAlive(x + 1, y + 1)) {

                // Check surrounding cells (including diagonals)
                bool isIsolated = true;
                for (int dy = -1; dy <= 2 && isIsolated; dy++) {
                    for (int dx = -1; dx <= 2 && isIsolated; dx++) {
                        // Skip the cells of the block itself
                        if ((dx == 0 || dx == 1) && (dy == 0 || dy == 1)) continue;

                        int nx = x + dx;
                        int ny = y + dy;

                        // Check if the cell is within the board and alive
                        if (nx >= 0 && nx < board->getWidth() && ny >= 0 && ny < board->getHeight()) {
                            if (board->isAlive(nx, ny)) {
                                isIsolated = false; // Found a living cell outside the block
                                break;
                            }
                        }
                    }
                }

                if (isIsolated) {
                    return true; // Found an isolated block
                }
            }
        }
    }
    return false; // No isolated block found
}

void initialiseBoard(Board& board, int alive_cells) {
    set<pair<int, int>> chosenCells;
    while (chosenCells.size() < alive_cells) {
        int x = rand() % board.getWidth();
        int y = rand() % board.getHeight();
        if (chosenCells.insert({ x, y }).second) {
            board.setAlive(x, y, true);
        }
    }
}

void runSimulationsUntilBlockFound(int width, int height, int alive_cells, int steps) {
    int simulationCount = 0;
    unsigned int seed = time(0);

    while (true) {
        simulationCount++;
        cout << "Running simulation #" << simulationCount << "..." << endl;

        Board board(width, height);
        srand(time(0));  // Set the seed for this simulation
        initialiseBoard(board, alive_cells);

        int blockFoundAtStep = -1;
        for (int step = 0; step <= steps; step++) {
            if (detectBlockPattern(&board)) {
                blockFoundAtStep = step;
                break;
            }
            board.updateBoard();
        }

        if (blockFoundAtStep != -1) {
            cout << "Isolated block pattern found in simulation #" << simulationCount
                << " at step " << blockFoundAtStep << endl;
            cout << "Replaying the simulation..." << endl;
            Sleep(500);

            // Replay the simulation
            Board replayBoard(width, height);
            srand(time(0));  // Reset the seed to get the same initial state
            initialiseBoard(replayBoard, alive_cells);

            for (int step = 0; step <= blockFoundAtStep; step++) {
                system("cls");
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
        cout << "No isolated block pattern found in " << steps << " steps." << endl;
        seed = time(0);  // Get a new seed for the next simulation
    }
}