#pragma once

#include <raylib.h>
#include "Cell.hpp"
#include <vector>



class CellGrid{
    private:
    std::vector<std::vector<Cell>> grid;
    int rows, columns;
    static const int maxRows = 17;
    static const int maxColumns = 31;
    Vector2 origin;

    

    //Private methods
    void ResetGrid();
    
    //TODO add maximum size of maze (around 35*63 probably)

    
    public:
    struct Coin {
        bool exists;
        Vector2 position;

        void Draw(){
            DrawRectangle(position.x+3, position.y+3, 2, 2, YELLOW);
        }
    };

    std::vector<Coin> coins;

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


    //Coins stuff
    bool CoinsCollected();
    void setCoinsLevel();

    //Maze algorithms
    //This one serves no purpose but is funny for now
    void GenerateRandomMaze();
    void GenerateBackTrackingMaze();
    bool isValid(Vector2 position);

    void ResetVisited();



    //Draws to the screen
    void Draw();
};