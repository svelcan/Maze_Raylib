#include "Player.hpp"
#include "CellGrid.hpp"
#include "Constants.hpp"
#include <raylib.h>


Player::Player(){
    initialPosition = {3,3};
    position = {3,3};
}

Player::~Player(){

}

void Player::setPosition(Vector2 position){
    this->position = position;
}

void Player::Update(CellGrid& cellGrid){

    //If the player wants to move we check if there is a wall, if there is then reset player and show wall

    if(IsKeyPressed(KEY_RIGHT)){
        if(cellGrid.getCellAtPosition({position.x - wallSize, position.y - wallSize}).wall_right.exists){
            cellGrid.getCellAtPosition({position.x - wallSize, position.y - wallSize}).wall_right.visible = true;
            ResetPlayer();
        } else {
            position.x += cellSize;
        }
    }
    if(IsKeyPressed(KEY_LEFT)){
        if(IsThereCell({(position.x - wallSize - cellGrid.getOrigin().x - cellSize)/cellSize, (position.y - wallSize - cellGrid.getOrigin().y)/cellSize}, cellGrid)){
            if(cellGrid.getCellAtPosition({position.x - wallSize - cellSize, position.y - wallSize}).wall_right.exists){
                cellGrid.getCellAtPosition({position.x - wallSize - cellSize, position.y - wallSize}).wall_right.visible = true;
                ResetPlayer();
            } else {
               position.x -= cellSize;
            }
        } 
    }
    if(IsKeyPressed(KEY_DOWN)){
        if(cellGrid.getCellAtPosition({position.x - wallSize, position.y - wallSize}).wall_bottom.exists){
            cellGrid.getCellAtPosition({position.x - wallSize, position.y - wallSize}).wall_bottom.visible = true;
            ResetPlayer();
        } else {
            position.y += cellSize;
        }
    }
    if(IsKeyPressed(KEY_UP)){
        if(IsThereCell({(position.x - wallSize - cellGrid.getOrigin().x)/cellSize, (position.y - wallSize - cellGrid.getOrigin().y - cellSize)/cellSize}, cellGrid)){
            if(cellGrid.getCellAtPosition({position.x - wallSize, position.y - wallSize - cellSize}).wall_bottom.exists){
                cellGrid.getCellAtPosition({position.x - wallSize, position.y - wallSize - cellSize}).wall_bottom.visible = true;
                ResetPlayer();
            } else {
               position.y -= cellSize;
            }
        }
    }
}

void Player::ResetPlayer(){
    this->position = this->initialPosition;
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

void Player::Draw(){
    DrawRectangle(position.x, position.y, size.x, size.y, RED);
}