#include "game_of_life.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// Cell implementations
Cell::Cell() : m_isAlive(false) {}

void Cell::setState(bool alive) {
    m_isAlive = alive;
}

char Cell::getDisplay() const {
    return m_isAlive ? 'O' : ' ';
}

bool Cell::isAlive() const {
    return m_isAlive;
}

// Board implementations
void Board::initializeGrid() {
    grid = new Cell * [height];
    for (int i = 0; i < height; i++) {
        grid[i] = new Cell[width];
    }
}

void Board::deleteGrid() {
    if (grid != nullptr) {
        for (int i = 0; i < height; i++) {
            delete[] grid[i];
        }
        delete[] grid;
        grid = nullptr;
    }
}

Board::Board(int w, int h) : width(w), height(h), grid(nullptr) {
    initializeGrid();
}

Board::~Board() {
    deleteGrid();
}

int Board::getWidth() const {
    return width;
}

int Board::getHeight() const {
    return height;
}

bool Board::isAlive(int x, int y) const {
    return grid[y][x].isAlive();
}

void Board::setAlive(int x, int y, bool alive) {
    grid[y][x].setState(alive);
}

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

void Board::display() const {
    for (int y = 0; y < height; y++) {
        cout << ".";
        for (int x = 0; x < width; x++) {
            cout << grid[y][x].getDisplay() << ".";
        }
        cout << endl;
    }
}

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