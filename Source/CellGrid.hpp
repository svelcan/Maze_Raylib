#pragma once

#include <raylib.h>
#include "Cell.hpp"
#include <list>



class CellGrid{
    private:
    //TODO add maximum size of maze (around 35*63 probably)
    Vector2 size;
    std::list<Cell> maze;

    public:
    //Constructor & Deconstructor
    CellGrid();
    CellGrid(Vector2 size);

    void GenerateGrid();
    void Draw();
};