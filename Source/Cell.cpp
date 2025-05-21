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
    DrawRectangle(position.x, position.y, cellSize-wallSize, cellSize-wallSize, BLUE);

    //Draw bottom wall if it exists AND is visible
    if (wall_bottom.exists && wall_bottom.visible) {
        DrawRectangle(position.x, position.y + cellSize - wallSize, cellSize, wallSize, RED);
    }

    // Draw right wall if it exists AND is visible
    if (wall_right.exists && wall_right.visible) {
        DrawRectangle(position.x + cellSize - wallSize, position.y, wallSize, cellSize, RED);
    }

    // Draw passages (openings) where walls don't exist
    if(!wall_bottom.exists && !wall_right.exists){
        DrawRectangle(position.x, position.y, cellSize, cellSize-wallSize, BLUE);
        DrawRectangle(position.x, position.y, cellSize-wallSize, cellSize, BLUE);
    } else if(!wall_bottom.exists){
        DrawRectangle(position.x, position.y, cellSize-wallSize, cellSize, BLUE);
    } else if(!wall_right.exists){
        DrawRectangle(position.x, position.y, cellSize, cellSize-wallSize, BLUE);
    }
}