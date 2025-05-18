#pragma once

#include "CellGrid.hpp"
#include "Player.hpp"
#include <raylib.h>



class Game{
    private:

    //Sound eatSound;
    //Sound wallSound;

    Player player;
    CellGrid cellGrid;
    

    public:
    //Constructor & Deconstructor
    Game();
    ~Game();

    void GameOver();

    void Draw();
    void Update(float deltaTime);
};