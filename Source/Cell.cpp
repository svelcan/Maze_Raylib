#include "Cell.hpp"
#include <raylib.h>


Cell::Cell(Vector2 position){
    this->position = position;
    this->wall_bottom = GetRandomValue(0, 1);
    this->wall_right = GetRandomValue(0, 1);
}

Cell::~Cell(){
}

void Cell::Draw(){
    DrawRectangle(position.x, position.y, 4, 4, BLUE);
    if(wall_bottom && wall_right){
        DrawRectangle(position.x, position.y, 5, 4, BLUE);
        DrawRectangle(position.x, position.y, 4, 5, BLUE);
    } else if(wall_bottom){
        DrawRectangle(position.x, position.y, 4, 5, BLUE);
    } else if(wall_right){
        DrawRectangle(position.x, position.y, 5, 4, BLUE);
    }
}