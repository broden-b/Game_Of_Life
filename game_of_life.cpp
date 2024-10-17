#include "game_of_life.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// Cell class implementation

Cell::Cell() : is_alive(false) {}
// Constructor initializes cell as dead

void Cell::setState(bool alive) {
    is_alive = alive;
}
// Set the state of the cell

char Cell::getDisplay() const {
    return is_alive ? 'O' : ' ';
}
// Return 'O' for live cell, space for dead cell

bool Cell::isAlive() const {
    return is_alive;
}
// Return the current state of the cell

// Board class implementation

void Board::initializeGrid() {
    grid = new Cell * [height];
    for (int i = 0; i < height; i++) {
        grid[i] = new Cell[width];
    }
}
// Dynamically allocate 2D array of Cells

void Board::deleteGrid() {
    if (grid != nullptr) {
        for (int i = 0; i < height; i++) {
            delete[] grid[i];
        }
        delete[] grid;
        grid = nullptr;
    }
}
// Properly delete the dynamically allocated grid

Board::Board(int w, int h) : width(w), height(h), grid(nullptr) {
    initializeGrid();
}
// Constructor initializes dimensions and creates the grid

Board::~Board() {
    deleteGrid();
}
// Destructor ensures proper cleanup of dynamically allocated memory

int Board::getWidth() const {
    return width;
}

int Board::getHeight() const {
    return height;
}
// Getter methods for board dimensions

bool Board::isAlive(int x, int y) const {
    return grid[y][x].isAlive();
}
// Check if cell at given coordinates is alive

void Board::setAlive(int x, int y, bool alive) {
    grid[y][x].setState(alive);
}
// Set state of cell at given coordinates

int Board::countLivingNeighbors(int x, int y) const {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            int newX = x + i;
            int newY = y + j;

            if (newX >= 0 && newX < width && newY >= 0 && newY < height) {
                if (grid[newY][newX].isAlive()) {
                    count++;
                }
            }
        }
    }
    return count;
}
// Count living neighbors of a cell, handling edge cases

void Board::updateBoard() {
    Cell** newGrid = new Cell * [height];
    for (int i = 0; i < height; i++) {
        newGrid[i] = new Cell[width];
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int livingNeighbors = countLivingNeighbors(x, y);
            if (grid[y][x].isAlive()) {
                newGrid[y][x].setState(livingNeighbors == 2 || livingNeighbors == 3);
            }
            else {
                newGrid[y][x].setState(livingNeighbors == 3);
            }
        }
    }

    deleteGrid();
    grid = newGrid;
}
// Update board state based on Game of Life rules

void Board::display() const {
    for (int y = 0; y < height; y++) {
        cout << ".";
        for (int x = 0; x < width; x++) {
            cout << grid[y][x].getDisplay() << ".";
        }
        cout << endl;
    }
}
// Display current board state

void Board::saveBoard() {
    ofstream outFile("saved_board.csv");
    outFile << width << "," << height << endl;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (grid[y][x].isAlive()) {
                outFile << x << "," << y << endl;
            }
        }
    }
    outFile.close();
    cout << "Save successful";
}
// Save current board state to a CSV file

void Board::loadBoard() {
    ifstream inFile("saved_board.csv");

    string line;
    getline(inFile, line);
    stringstream ss(line);
    string widthStr, heightStr;
    getline(ss, widthStr, ',');
    getline(ss, heightStr);

    int newWidth = stoi(widthStr);
    int newHeight = stoi(heightStr);

    if (newWidth != width || newHeight != height) {
        deleteGrid();
        width = newWidth;
        height = newHeight;
        initializeGrid();
    }
    else {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                grid[y][x].setState(false);
            }
        }
    }

    while (getline(inFile, line)) {
        stringstream ss(line);
        string xStr, yStr;
        getline(ss, xStr, ',');
        getline(ss, yStr);
        int x = stoi(xStr);
        int y = stoi(yStr);
        setAlive(x, y, true);
    }

    inFile.close();
    cout << "Load successful\n" << endl;
    display();
}
// Load board state from a CSV file