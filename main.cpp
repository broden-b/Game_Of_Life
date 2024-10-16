#include <iostream>
#include <windows.h>
#include <set>
#include "game_of_life.h"
#include "block_pattern.h"

using namespace std;

void displayMenu() {
    system("cls");
    cout << "Game of Life\n\n1. Create New Simulation\n2. Load Saved Simulation\n3. Experiment To Find Block Pattern\n4. Exit\n" << endl;
}

Board* createNewSimulation() {
    int width, height, alive_cells;

    cout << "Enter the width of the grid: ";
    cin >> width;
    cout << "Enter the height of the grid: ";
    cin >> height;
    cout << "Enter size of initial population: ";
    cin >> alive_cells;

    Board* board = new Board(width, height);

    set<pair<int, int>> chosen_cells;
    while (chosen_cells.size() < alive_cells) {
        int x = rand() % (board->getWidth());
        int y = rand() % (board->getHeight());
        if (chosen_cells.insert({ x, y }).second) {
            board->setAlive(x, y, true);
        }
    }

    return board;
}

Board* loadSavedSimulation() {
    Board* board = new Board(1, 1);  // Temporary dimensions, will be updated in loadBoard
    board->loadBoard();
    return board;
}

void runSimulation(Board* board) {
    int steps;
    cout << "Enter number of steps the simulation will take: ";
    cin >> steps;

    for (int i = 0; i < steps; i++) {
        system("cls");
        board->display();
        board->updateBoard();
        cout << "Step: " << i + 1 << " / " << steps << "\n\n";
        Sleep(500);
    }

    int save_choice;
    cout << "Save Board?:\n1. Yes\n2. No\n" << endl;
    cin >> save_choice;

    if (save_choice == 1) {
        board->saveBoard();
    }
}

void runBlockFinderSimulation() {
    int width, height, alive_cells, maxSteps;

    cout << "Enter grid width: ";
    cin >> width;
    cout << "Enter grid height: ";
    cin >> height;
    cout << "Enter initial population: ";
    cin >> alive_cells;
    cout << "Enter maximum steps per simulation: ";
    cin >> maxSteps;

    runSimulationsUntilBlockFound(width, height, alive_cells, maxSteps);
}

int main() {
    srand(time(0));

    while (true) {
        displayMenu();
        int choice;
        cin >> choice;

        Board* board = nullptr;

        switch (choice) {
        case 1:
            board = createNewSimulation();
            runSimulation(board);
            delete board;
            break;
        case 2:
            board = loadSavedSimulation();
            runSimulation(board);
            delete board;
            break;
        case 3:
            runBlockFinderSimulation();
        case 4:
            return 0;
        }
    }

    return 0;
}