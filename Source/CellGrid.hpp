#pragma once

#include <raylib.h>
#include "Cell.hpp"
#include <vector>



class CellGrid{
    private:
    std::vector<std::vector<Cell>> grid;
    int rows, columns;
    Vector2 origin;

    //Private methods
    void ResetGrid();
    
    //TODO add maximum size of maze (around 35*63 probably)

    public:
    //Constructor & Deconstructor
    CellGrid();
    CellGrid(int rows, int colummns);

    //Getters & Setters
    int getColumns();
    int getRows();
    Vector2 getOrigin();

    Cell& getCell(int row, int col);
    //This might or might not be useful so for the time being I'm leaving it
    Cell& getCellAtPosition(Vector2 pos);

    void setVisibleWalls(bool visible);


    //Draws to the screen
    void Draw();





    //Maze algorithms
    //This serves no purpose but is funny for now
    void GenerateRandomMaze();
    void GenerateBackTrackingMaze();
    bool isValid(Vector2 position);

    void ResetVisited();
};