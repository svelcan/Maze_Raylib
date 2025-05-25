#include "Player.hpp"
#include "Cell.hpp"
#include "CellGrid.hpp"
#include "../core/Constants.hpp"
#include <iostream>
#include <raylib.h>
#include <raymath.h>

#include <fstream>
#include <vector>
#include <algorithm>
#include <string>


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

    if(IsKeyPressed(KEY_V)){
        //Start moving player, make cells invisible
        cellGrid.setVisibleWalls(false);
        allowMovement = true;
    }
    
    if(!allowMovement){
        return;
    }

    //If you touch a coin it dissappears
    for (CellGrid::Coin& coin : cellGrid.coins) {
        if(Vector2Equals(coin.position, Vector2Subtract(this->position, {float(wallSize), float(wallSize)}))){
            score +=5;
            coin.exists = false;           
        }
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

    //Shoots a flare
    if(IsKeyPressed(KEY_SPACE) && flare.isMovementOrderEmpty()){
        //The flare will go to the closest coin
        flare.ChooseCoin({position.x - wallSize, position.y - wallSize}, cellGrid);
        score -= 6;
    }

    flare.Update(deltaTime);


    if(score < 0){score = 0;}
}

void Player::ResetPlayer(){
    this->position = this->initialPosition;
}

void Player::ResetScore(){
    this->score = 10;
}

void Player::SaveScore() {
    const std::string filename = "scores.txt";
    std::vector<int> scores;

    // 1. Read existing scores
    std::ifstream inFile(filename);
    if (inFile.is_open()) {
        int currentScore;
        while (inFile >> currentScore) {
            scores.push_back(currentScore);
        }
        inFile.close();
    }

    // 2. Add the new score
    scores.push_back(score);

    // 3. Sort in descending order
    std::sort(scores.begin(), scores.end(), std::greater<int>());

    // 4. Keep only top 5
    if (scores.size() > 5) {
        scores.resize(5);
    }

    // 5. Write back to file
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        for (int s : scores) {
            outFile << s << "\n";
        }
        outFile.close();
    }
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
    flare.Draw();
    DrawRectangle(position.x, position.y, size.x, size.y, PINK);
}