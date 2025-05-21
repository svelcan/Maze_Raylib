#include "Cell.hpp"
#include "Constants.hpp"
#include <raylib.h>


Cell::Cell(){
    this->position = {0,0};
    this->wall_bottom = {true, false};
    this->wall_right = {true, false}; 
}

Cell::Cell(Vector2 position){
    this->position = position;    
    this->wall_bottom = {true, false};
    this->wall_right = {true, false}; 
}

Cell::~Cell(){
}

void Cell::RandomizeWalls(){
    this->wall_bottom.exists = GetRandomValue(0, 1);
    this->wall_right.exists = GetRandomValue(0, 1);
}

Vector2 Cell::getPosition(){
    return this->position;
}

void Cell::setPosition(Vector2 position){
    this->position = position;
}

void Cell::Draw(){
    //Draw the cell's main area
    DrawRectangle(position.x, position.y, cellSize, cellSize, BLUE);
    //Remember to draw the wall that always exists
    DrawRectangle(position.x + cellSize - wallSize, position.y + cellSize - wallSize, wallSize, wallSize, RED);

    //Draw bottom wall if it exists AND is visible
    if (wall_bottom.exists && wall_bottom.visible) {
        DrawRectangle(position.x, position.y + cellSize - wallSize, cellSize, wallSize, RED);
    }

    // Draw right wall if it exists AND is visible
    if (wall_right.exists && wall_right.visible) {
        DrawRectangle(position.x + cellSize - wallSize, position.y, wallSize, cellSize, RED);
    }
}