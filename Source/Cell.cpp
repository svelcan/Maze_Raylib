#include "Cell.hpp"
#include "Constants.hpp"
#include <raylib.h>


Cell::Cell(){
    this->position = {0,0};
}

Cell::Cell(Vector2 position){
    this->position = position;    
}

Cell::~Cell(){
}

void Cell::RandomizeWalls(){
    this->wall_bottom = GetRandomValue(0, 1);
    this->wall_right = GetRandomValue(0, 1);
}

Vector2 Cell::getPosition(){
    return this->position;
}

void Cell::setPosition(Vector2 position){
    this->position = position;
}

void Cell::Draw(){
    DrawRectangle(position.x, position.y, cellSize-wallSize, cellSize-wallSize, BLUE);
    if(!wall_bottom && !wall_right){
        DrawRectangle(position.x, position.y, cellSize, cellSize-wallSize, BLUE);
        DrawRectangle(position.x, position.y, cellSize-wallSize, cellSize, BLUE);
    } else if(!wall_bottom){
        DrawRectangle(position.x, position.y, cellSize-wallSize, cellSize, BLUE);
    } else if(!wall_right){
        DrawRectangle(position.x, position.y, cellSize, cellSize-wallSize, BLUE);
    }
}