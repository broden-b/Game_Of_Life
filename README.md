# Game of Life
## Description

John Conway's "Game of Life" is a simulation that follows a set of rules aimed at emulating how populations thrive when given an optimal starting population relative to available space. This is an implementation of that game in C++, with the ability to generate a new simulation, save it to continue after a set amount of steps have passed as well as options to observe a set of patterns that are known to appear in the Game of Life.

## Rules of The Game

- Any live cell with fewer than two live neighbours dies, as if by underpopulation
- Any live cell with two or three live neighbours lives on to the next generation
- Any live cell with more than three live neighbours dies, as if by overpopulation
- Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction

## How To Run

- Unzip the foler
- Open the .sln file in Visual Studio
- Click "Run"
- Select an option from the menu
