#include "Cell.hpp"
#include "Constants.hpp"
#include <raylib.h>


Cell::Cell(Vector2 position){
    this->position = position;    
}

Cell::~Cell(){
}

void Cell::RandomizeWalls(){
    this->wall_bottom = GetRandomValue(0, 1);
    this->wall_right = GetRandomValue(0, 1);
}

void Cell::Draw(){
    DrawRectangle(position.x, position.y, cellSize-1, cellSize-1, BLUE);
    if(wall_bottom && wall_right){
        DrawRectangle(position.x, position.y, cellSize, cellSize-1, BLUE);
        DrawRectangle(position.x, position.y, cellSize-1, cellSize, BLUE);
    } else if(wall_bottom){
        DrawRectangle(position.x, position.y, cellSize-1, cellSize, BLUE);
    } else if(wall_right){
        DrawRectangle(position.x, position.y, cellSize, cellSize-1, BLUE);
    }
}