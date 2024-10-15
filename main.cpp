#include <iostream>
#include <windows.h>
#include <set>
#include <fstream>
#include <string>
#include <sstream>

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

    void initializeGrid() {
        grid = new Cell * [height];
        for (int i = 0; i < height; i++) {
            grid[i] = new Cell[width];
        }
    }

    void deleteGrid() {
        if (grid != nullptr) {
            for (int i = 0; i < height; i++) {
                delete[] grid[i];
            }
            delete[] grid;
            grid = nullptr;
        }
    }

public:
    Board(int w, int h) : width(w), height(h), grid(nullptr) {
        initializeGrid();
    }

    ~Board() {
        deleteGrid();
    }

    int getWidth() const {
        return width; 
    }
    int getHeight() const {
        return height;
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

    void saveBoard() {
        ofstream outFile("saved_board.csv");
        outFile << width << "," << height << endl;
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (grid[y][x].isAlive) {
                    outFile << x << "," << y << endl;
                }
            }
        }
        outFile.close();
        cout << "Save successful";
    }

    void loadBoard() {
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
            // Clear the existing grid
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
        cout << "Load successful" << endl;
    }
};

int main() {
    srand(time(0));
    int width, height, alive_cells, steps;
    char save_choice;
    int load_choice;

    cout << "Load grid (0) or New grid (1)?\n";
    cin >> load_choice;

    Board* board;

    if (load_choice == 0) {
        board = new Board(1, 1);
        board->loadBoard();
        cout << "Enter number of additional steps the simulation will take: ";
        cin >> steps;
    }
    else {
        cout << "Enter the width of the grid: ";
        cin >> width;
        cout << "Enter the height of the grid: ";
        cin >> height;
        cout << "Enter size of initial population: ";
        cin >> alive_cells;
        cout << "Enter number of steps the simulation will take: ";
        cin >> steps;

        board = new Board(width, height);

        set<pair<int, int>> chosen_cells;
        while (chosen_cells.size() < alive_cells) {
            int x = rand() % (board->getWidth());
            int y = rand() % (board->getHeight());
            if (chosen_cells.insert({ x, y }).second) {
                board->setAlive(x, y, true);
            }
        }
    }

    for (int i = 0; i < steps; i++) {
        //system("cls");  
        board->display();
        board->updateBoard();
        cout << "Step: " << i + 1 << "\n\n";
        Sleep(500);
    }

    cout << "Save Board? (y/n)\n";
    cin >> save_choice;

    if (save_choice == 'y' || save_choice == 'Y') {
        board->saveBoard();
    }

    delete board;
    return 0;
}