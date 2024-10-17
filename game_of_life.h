#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class Cell {
public:
    Cell();
    void setState(bool alive);
    char getDisplay() const;
    bool isAlive() const;
    // Public interface for Cell class: constructor and methods to manipulate and query cell state

private:
    bool is_alive;
    // Private member to store the cell's state
};
// Cell class represents individual cells in the Game of Life grid

class Board {
private:
    Cell** grid;
    int width;
    int height;
    // Private members: 2D array of Cells, and dimensions of the grid

    void initializeGrid();
    void deleteGrid();
    // Private helper methods for grid management

public:
    Board(int w, int h);
    ~Board();
    // Constructor and destructor

    int getWidth() const;
    int getHeight() const;
    bool isAlive(int x, int y) const;
    void setAlive(int x, int y, bool alive);
    int countLivingNeighbors(int x, int y) const;
    void updateBoard();
    void display() const;
    void saveBoard();
    void loadBoard();
    // Public methods for board operations and game logic
};
// Board class represents the entire Game of Life grid and contains the game logic

#endif