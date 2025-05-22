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
    struct Coin {
        bool exists;
        bool visible;
        Vector2 position;

        void Draw(){
            DrawRectangle(position.x+3, position.y+3, 2, 2, YELLOW);
        }
    };

    Coin coin;
    Coin coint;
    Coin coinp;

    //Constructor & Deconstructor
    CellGrid();
    CellGrid(int rows, int colummns);

    //Getters & Setters
    int getColumns();
    int getRows();
    Vector2 getOrigin();

    Cell& getCell(int row, int col);
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