#pragma once
#include <raylib.h>



class Cell{
    private:
    bool wall_bottom;
    bool wall_right;

    Vector2 position;

    

    public:
    //Constructor & Deconstructor
    Cell(Vector2 position);
    ~Cell();

    void Draw();
};