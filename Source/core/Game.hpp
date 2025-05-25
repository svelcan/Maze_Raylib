#pragma once

#include "../objects/CellGrid.hpp"
#include "../objects/Player.hpp"
#include <raylib.h>



class Game{
    private:
    //Variables
    CellGrid cellGrid;
    Player player;
    bool levelCleared = false;
    

    public:
    //Constructor & Deconstructor
    Game();

    //Getters & Setters
    CellGrid& getCellGrid();
    void setCellGrid(CellGrid cellGrid);

    //Draw & Update
    void Draw();
    int Update(float deltaTime);
};