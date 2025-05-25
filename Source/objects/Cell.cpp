#include "Cell.hpp"
#include "../core/Constants.hpp"
#include <raylib.h>

//Constructor for cell
Cell::Cell(){
    this->position = {0,0};
    this->wall_bottom = {true, true};
    this->wall_right = {true, true}; 
}

//Constructor for cell specifying position
Cell::Cell(Vector2 position){
    this->position = position;    
    this->wall_bottom = {true, true};
    this->wall_right = {true, true}; 
}

//Randomizes the Walls
void Cell::RandomizeWalls(){
    this->wall_bottom.exists = GetRandomValue(0, 1);
    this->wall_right.exists = GetRandomValue(0, 1);
}

//Returns position
Vector2 Cell::getPosition(){
    return this->position;
}

//Sets position
void Cell::setPosition(Vector2 position){
    this->position = position;
}

//Draw method
void Cell::Draw(){
    //Draw the cell's main area
    DrawRectangle(position.x, position.y, cellSize, cellSize, BLUE);
    //Remember to draw the wall that always exists
    DrawRectangle(position.x + cellSize - wallSize, position.y + cellSize - wallSize, wallSize, wallSize, BLACK);

    //Draw bottom wall if it exists AND is visible
    if (wall_bottom.exists && wall_bottom.visible) {
        DrawRectangle(position.x, position.y + cellSize - wallSize, cellSize, wallSize, BLACK);
    }

    // Draw right wall if it exists AND is visible
    if (wall_right.exists && wall_right.visible) {
        DrawRectangle(position.x + cellSize - wallSize, position.y, wallSize, cellSize, BLACK);
    }
}