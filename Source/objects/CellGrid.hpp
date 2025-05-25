#pragma once

#include <raylib.h>
#include "Cell.hpp"
#include <vector>



class CellGrid{
    private:
    //Variables
    std::vector<std::vector<Cell>> grid;
    int rows, columns;
    static const int maxRows = 17;
    static const int maxColumns = 31;
    Vector2 origin;

    

    //Private methods
    void ResetGrid();

    
    public:
    //Struct for Coin
    struct Coin {
        bool exists;
        Vector2 position;

        void Draw(){
            DrawRectangle(position.x+3, position.y+3, 2, 2, YELLOW);
        }
    };
    //Public variables
    std::vector<Coin> coins;

    //Constructor & Deconstructor
    CellGrid(int rows, int colummns);

    //Getters & Setters
    int getColumns();
    int getRows();
    Vector2 getOrigin();
    Cell& getCell(int row, int col);
    Cell& getCellAtPosition(Vector2 pos);
    void setVisibleWalls(bool visible);


    //Coin stuff
    bool CoinsCollected();
    void setCoinsLevel();

    //Maze algorithms
    void GenerateRandomMaze();
    void GenerateBackTrackingMaze();
    bool isValid(Vector2 position);
    void ResetVisited();


    //Update & Draw
    void Draw();
};