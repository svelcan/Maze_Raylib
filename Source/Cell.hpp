#pragma once

#include <raylib.h>



class Cell{
    private:
    bool wall_bottom = 0;
    bool wall_right = 0;

    Vector2 position;

    

    public:
    //int cellSize = 5;
    //Constructor & Deconstructor
    Cell(Vector2 position);
    ~Cell();

    void RandomizeWalls();
    void Draw();
};