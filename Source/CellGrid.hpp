#pragma once

#include <raylib.h>
#include "Cell.hpp"
#include <vector>
#include <stack>



class CellGrid{
    private:
    std::vector<std::vector<Cell>> grid;
    int rows, columns;
    Vector2 position;
    
    //TODO add maximum size of maze (around 35*63 probably)

    public:
    //Constructor & Deconstructor
    CellGrid();
    CellGrid(int rows, int colummns);

    //Getters & Setters
    Cell& getCell(int row, int col);
    //This might or might not be useful so for the time being I'm leaving it
    Cell& getCellAtPosition(Vector2 pos);


    //Draws to the screen
    void Draw();










    //Maze stuff
    std::stack<Cell> mazeStack;

    //Maze algorithms
    //This serves no purpose but is funny for now
    void GenerateRandomMaze();
};