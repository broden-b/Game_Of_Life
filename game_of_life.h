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

private:
    bool is_alive;
};

class Board {
private:
    Cell** grid;
    int width;
    int height;

    void initializeGrid();
    void deleteGrid();

public:
    Board(int w, int h);
    ~Board();

    int getWidth() const;
    int getHeight() const;
    bool isAlive(int x, int y) const;
    void setAlive(int x, int y, bool alive);
    int countLivingNeighbors(int x, int y) const;
    void updateBoard();
    void display() const;
    void saveBoard();
    void loadBoard();
};

#endif // GAME_OF_LIFE_H