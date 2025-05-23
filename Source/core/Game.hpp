#pragma once

#include "../objects/CellGrid.hpp"
#include "../objects/Player.hpp"
#include <raylib.h>



class Game{
    private:
    //Sound eatSound;
    //Sound wallSound;

    Player player;
    CellGrid cellGrid;

    bool levelCleared = false;
    

    public:
    //Constructor & Deconstructor
    Game();
    ~Game();

    CellGrid& getCellGrid();
    void setCellGrid(CellGrid cellGrid);
    void GameOver();

    void Draw();
    int Update(float deltaTime);
};