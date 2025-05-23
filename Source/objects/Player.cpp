#include "Player.hpp"
#include "Cell.hpp"
#include "CellGrid.hpp"
#include "../core/Constants.hpp"
#include <raylib.h>


Player::Player(){

}
Player::Player(CellGrid& cellGrid){
    initialPosition = {cellGrid.getCell(0, 0).getPosition().x + wallSize, cellGrid.getCell(0, 0).getPosition().y + wallSize};
    position = initialPosition;

}

Player::~Player(){

}

void Player::setPosition(Vector2 position){
    this->position = position;
}

void Player::Update(CellGrid& cellGrid, float deltaTime){
    //Update Player's initial position based on the new maze
    if(lastKnownMazeSize.x != cellGrid.getColumns() || lastKnownMazeSize.y != cellGrid.getRows()){
        initialPosition = {cellGrid.getCell(0, 0).getPosition().x + wallSize, cellGrid.getCell(0, 0).getPosition().y + wallSize};
        position = initialPosition;

        lastKnownMazeSize = {float(cellGrid.getColumns()), float(cellGrid.getRows())};
    }

    flare.Update(deltaTime);

    if(IsKeyPressed(KEY_V)){
        //Start moving player, make cells invisible
        cellGrid.setVisibleWalls(false);
        allowMovement = true;
    }
    
    if(!allowMovement){
        return;
    }

    //If the player wants to move we check if there is a wall, if there is then reset player and show wall
    if(IsKeyPressed(KEY_RIGHT)){
        if(cellGrid.getCellAtPosition({position.x - wallSize, position.y - wallSize}).wall_right.exists){
            cellGrid.getCellAtPosition({position.x - wallSize, position.y - wallSize}).wall_right.visible = true;
            score--;
        } else {
            position.x += cellSize;
        }
    }
    if(IsKeyPressed(KEY_LEFT)){
        if(IsThereCell({(position.x - wallSize - cellGrid.getOrigin().x - cellSize)/cellSize, (position.y - wallSize - cellGrid.getOrigin().y)/cellSize}, cellGrid)){
            if(cellGrid.getCellAtPosition({position.x - wallSize - cellSize, position.y - wallSize}).wall_right.exists){
                cellGrid.getCellAtPosition({position.x - wallSize - cellSize, position.y - wallSize}).wall_right.visible = true;
                score--;
                //ResetPlayer();
            } else {
               position.x -= cellSize;
            }
        } 
    }
    if(IsKeyPressed(KEY_DOWN)){
        if(cellGrid.getCellAtPosition({position.x - wallSize, position.y - wallSize}).wall_bottom.exists){
            cellGrid.getCellAtPosition({position.x - wallSize, position.y - wallSize}).wall_bottom.visible = true;
            score--;
            //ResetPlayer();
        } else {
            position.y += cellSize;
        }
    }
    if(IsKeyPressed(KEY_UP)){
        if(IsThereCell({(position.x - wallSize - cellGrid.getOrigin().x)/cellSize, (position.y - wallSize - cellGrid.getOrigin().y - cellSize)/cellSize}, cellGrid)){
            if(cellGrid.getCellAtPosition({position.x - wallSize, position.y - wallSize - cellSize}).wall_bottom.exists){
                cellGrid.getCellAtPosition({position.x - wallSize, position.y - wallSize - cellSize}).wall_bottom.visible = true;
                score--;
                //ResetPlayer();
            } else {
               position.y -= cellSize;
            }
        }
    }

    if(IsKeyPressed(KEY_SPACE)){
        flare.FindShortestPath(cellGrid, {position.x - wallSize, position.y - wallSize}, {float(cellGrid.getColumns())-1, float(cellGrid.getRows())-1});
    }

    if(score < 0){score = 0;}
}

void Player::ResetPlayer(){
    this->position = this->initialPosition;
}

void Player::ResetScore(){
    this->score = 10;
}

bool Player::IsThereCell(Vector2 cellPosition, CellGrid& cellGrid){
    if(cellPosition.x < 0
        || cellPosition.y < 0
        || cellPosition.x >= cellGrid.getColumns()
        || cellPosition.y >= cellGrid.getRows()){
        return false;
    } 
    return true;
}

//TODO kill the flare instead of continuously Drawing it
void Player::Draw(){
    flare.Draw();
    DrawRectangle(position.x, position.y, size.x, size.y, PINK);
}