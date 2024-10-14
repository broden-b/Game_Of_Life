#include <iostream>
#include <windows.h>

using namespace std;

// The Cell class represents a single cell in the Game of Life grid
class Cell {
public:
    bool isAlive;

    Cell() : isAlive(false) {}

    void setState(bool alive) {
        isAlive = alive;
    }

    char getDisplay() const {
        return isAlive ? 'O' : '.';
    }
};

// The Board class manages the game grid and its evolution
class Board {
private:
    Cell** grid;  // Pointer to pointer, allows for 2D dynamic array
    int width;
    int height;

public:
    // Constructor: Initializes the board with user-defined dimensions
    Board(int w, int h) : width(w), height(h) {
        // Allocate memory for the 2D grid
        grid = new Cell * [height];  // Allocate an array of pointers
        for (int i = 0; i < height; i++) {
            grid[i] = new Cell[width];  // Allocate each row
        }
        // Note: This approach allows for a grid of any size, limited only by available memory
    }

    // Destructor: Properly deallocates the dynamically allocated memory
    ~Board() {
        for (int i = 0; i < height; i++) {
            delete[] grid[i];  // Delete each row
        }
        delete[] grid;  // Delete the array of pointers
    }

    // Check if a cell at given coordinates is alive
    bool isAlive(int x, int y) const {
        return grid[y][x].isAlive;
    }

    // Set the state of a cell at given coordinates
    void setAlive(int x, int y, bool alive) {
        grid[y][x].setState(alive);
    }

    // Count the number of living neighbors for a cell
    int countLivingNeighbors(int x, int y) const {
        int count = 0;
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (i == 0 && j == 0) continue;  // Skip the cell itself
                int newX = x + i;
                int newY = y + j;
                // Check bounds before accessing the cell
                if (newX >= 0 && newX < width && newY >= 0 && newY < height) {
                    if (grid[newY][newX].isAlive) {
                        count++;
                    }
                }
            }
        }
        return count;
    }

    // Update the board for the next generation
    void updateBoard() {
        // Create a new grid for the next generation
        Cell** newGrid = new Cell * [height];
        for (int i = 0; i < height; i++) {
            newGrid[i] = new Cell[width];
        }

        // Apply Game of Life rules to each cell
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int livingNeighbors = countLivingNeighbors(x, y);
                if (grid[y][x].isAlive) {
                    // Any live cell with 2 or 3 live neighbors survives
                    newGrid[y][x].setState(livingNeighbors == 2 || livingNeighbors == 3);
                }
                else {
                    // Any dead cell with exactly 3 live neighbors becomes a live cell
                    newGrid[y][x].setState(livingNeighbors == 3);
                }
            }
        }

        // Delete the old grid
        for (int i = 0; i < height; i++) {
            delete[] grid[i];
        }
        delete[] grid;

        // Replace the old grid with the new one
        grid = newGrid;
    }

    // Display the current state of the board
    void display() const {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                cout << grid[y][x].getDisplay();
            }
            cout << endl;
        }
    }
};

int main() {
    int width, height, aliveCells, steps;

    // Get user input for grid dimensions
    cout << "Enter the width of the grid: ";
    cin >> width;
    cout << "Enter the height of the grid: ";
    cin >> height;
    cout << "Enter size of initial population: ";
    cin >> aliveCells;
    cout << "Enter number of steps the simulation will take: ";
    cin >> steps;

    // Creates board
    Board board(width, height);

    // Randomly distributes alive cells
    for (int i = 0; i < aliveCells; i++) {
        int x = rand() % (width);
        int y = rand() % (height);
        board.setAlive(x, y, true);
    }

    // Main game loop
    for (int i = 0; i < steps; i++) {
        //system("cls");  // Clear the console
        board.display();  // Show the current state
        board.updateBoard();  // Evolve to the next generation
        cout << "Step: " << i+1 << "\n\n";
        Sleep(500);  // Pause for 500 milliseconds
    }

    return 0;
}