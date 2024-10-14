#include <iostream>
#include <windows.h>
#include <set>

using namespace std;

class Cell {
public:
    bool isAlive;

    Cell() : isAlive(false) {}

    void setState(bool alive) {
        isAlive = alive;
    }

    char getDisplay() const {
        return isAlive ? 'O' : ' ';
    }
};

class Board {
private:
    Cell** grid;  
    int width;
    int height;

public:
    
    Board(int w, int h) : width(w), height(h) {
        
        grid = new Cell * [height];  
        for (int i = 0; i < height; i++) {
            grid[i] = new Cell[width]; 
        }
    }

    ~Board() {
        for (int i = 0; i < height; i++) {
            delete[] grid[i];  
        }
        delete[] grid;  
    }
   
    bool isAlive(int x, int y) const {
        return grid[y][x].isAlive;
    }

    void setAlive(int x, int y, bool alive) {
        grid[y][x].setState(alive);
    }

    int countLivingNeighbors(int x, int y) const {
        int count = 0;
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (i == 0 && j == 0) continue;  
                int newX = x + i;
                int newY = y + j;
                
                if (newX >= 0 && newX < width && newY >= 0 && newY < height) {
                    if (grid[newY][newX].isAlive) {
                        count++;
                    }
                }
            }
        }
        return count;
    }
   
    void updateBoard() {
        
        Cell** newGrid = new Cell * [height];
        for (int i = 0; i < height; i++) {
            newGrid[i] = new Cell[width];
        }

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int livingNeighbors = countLivingNeighbors(x, y);
                if (grid[y][x].isAlive) {
                    newGrid[y][x].setState(livingNeighbors == 2 || livingNeighbors == 3);
                }
                else {
                    newGrid[y][x].setState(livingNeighbors == 3);
                }
            }
        }

        for (int i = 0; i < height; i++) {
            delete[] grid[i];
        }
        delete[] grid;

        grid = newGrid;
    }

    void display() const {
        for (int y = 0; y < height; y++) {
            cout << ".";
            for (int x = 0; x < width; x++) {
                cout << grid[y][x].getDisplay() << ".";
            }
            cout << endl;
        }
    }
};

int main() {
    srand(time(0));
    int width, height, alive_cells, steps;
   
    cout << "Enter the width of the grid: ";
    cin >> width;
    cout << "Enter the height of the grid: ";
    cin >> height;
    cout << "Enter size of initial population: ";
    cin >> alive_cells;
    cout << "Enter number of steps the simulation will take: ";
    cin >> steps;
    
    Board board(width, height);

    set<pair<int, int>> chosen_cells;
    
    while (chosen_cells.size() < alive_cells) {
        int x = rand() % (width);
        int y = rand() % (height);
        if (chosen_cells.insert({ x, y }).second) {
            board.setAlive(x, y, true);
        }
    }

    for (int i = 0; i < steps; i++) {
        //system("cls");  
        board.display();
        board.updateBoard();  
        cout << "Step: " << i+1 << "\n\n";
        Sleep(500);  
    }

    return 0;
}