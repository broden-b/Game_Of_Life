#include <iostream>
#include <windows.h>
#include <set>
#include "game_of_life.h"
#include "still_life_pattern.h"
#include "oscillator_pattern.h"
#include "spaceship_pattern.h"

using namespace std;
// Using the standard namespace to avoid prefixing std:: everywhere

void displayMenu() {
    cout << "Game of Life\n\n1. Create New Simulation\n2. Load Saved Simulation\n3. Experiment To Find Block or Beehive Pattern\n"
        "4. Experiment To Find Blinker or Toad Pattern\n5. Experiment To Find Glider or LWSS\n6. Exit\n" << endl;
}
// Function to display the main menu options

Board* createNewSimulation() {
    int width, height, alive_cells;

    cout << "Enter the width of the grid: ";
    cin >> width;
    cout << "Enter the height of the grid: ";
    cin >> height;
    cout << "Enter size of initial population: ";
    cin >> alive_cells;

    // Prompt user for grid dimensions and initial population size

    Board* board = new Board(width, height);
    // Create a new Board object dynamically

    set<pair<int, int>> chosen_cells;
    while (chosen_cells.size() < alive_cells) {
        int x = rand() % (board->getWidth());
        int y = rand() % (board->getHeight());
        if (chosen_cells.insert({ x, y }).second) {
            board->setAlive(x, y, true);
        }
    }
    // Randomly populate the board with alive cells
    // Using a set to ensure unique cell positions

    return board;
}

Board* loadSavedSimulation() {
    Board* board = new Board(1, 1);  // Temporary dimensions, will be updated in loadBoard
    board->loadBoard();
    return board;
}
// Function to load a saved simulation from a file

void runSimulation(Board* board) {
    int steps;
    cout << "Enter number of steps the simulation will take: ";
    cin >> steps;

    for (int i = 0; i < steps; i++) {
        system("cls");  // Clear the console (Windows-specific)
        board->display();
        board->updateBoard();
        cout << "Step: " << i + 1 << " / " << steps << "\n\n";
        Sleep(500);  // Pause for 500 milliseconds between steps
    }

    int save_choice;
    cout << "Save Board?:\n1. Yes\n2. No\n" << endl;
    cin >> save_choice;

    if (save_choice == 1) {
        board->saveBoard();
    }
}
// Function to run the simulation for a specified number of steps

void runBlockOrBeehiveSimulation() {
    int width, height, alive_cells, steps;

    cout << "Enter grid width: ";
    cin >> width;
    cout << "Enter grid height: ";
    cin >> height;
    cout << "Enter initial population: ";
    cin >> alive_cells;
    cout << "Enter maximum steps per simulation: ";
    cin >> steps;

    runSimulationsStillLife(width, height, alive_cells, steps);
}
// Function to run simulations to find Block or Beehive patterns

void runBlinkerOrToadSimulation() {
    int width, height, alive_cells, steps;

    cout << "Enter grid width: ";
    cin >> width;
    cout << "Enter grid height: ";
    cin >> height;
    cout << "Enter initial population: ";
    cin >> alive_cells;
    cout << "Enter maximum steps per simulation: ";
    cin >> steps;

    runSimulationsBlinkerOrToad(width, height, alive_cells, steps);
}
// Function to run simulations to find Blinker or Toad patterns

void runSpaceshipSimulation() {
    int width, height, alive_cells, steps;

    cout << "Enter grid width: ";
    cin >> width;
    cout << "Enter grid height: ";
    cin >> height;
    cout << "Enter initial population: ";
    cin >> alive_cells;
    cout << "Enter maximum steps per simulation: ";
    cin >> steps;

    runSimulationsSpaceship(width, height, alive_cells, steps);
}
// Function to run simulations to find Glider or LWSS patterns

void runErnSimulation() {
    int width, height, alive_cells, steps;




}

int main() {
    srand(time(0));  // Seed the random number generator with current time

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
            runBlockOrBeehiveSimulation();
            break;
        case 4:
            runBlinkerOrToadSimulation();
            break;
        case 5:
            runSpaceshipSimulation();
            break;
        case 6:
            return 0;
        }
    }

    return 0;
}
// Main function: Displays menu and handles user choices in a loop until exit is chosen