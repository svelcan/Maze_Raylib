#include "Game.hpp"
#include <iostream>
#include <raylib.h>
#include <string>


Game::Game(){
    this->cellGrid = CellGrid({10,10});
    this->player = Player(cellGrid);
    InitAudioDevice();

    //eatSound = LoadSound("Sounds/eat.mp3");
    //wallSound = LoadSound("Sounds/wall.mp3");
}

Game::~Game(){
    //UnloadSound(eatSound);
    //UnloadSound(wallSound);
}

CellGrid& Game::getCellGrid(){
    return this->cellGrid;
}

void Game::setCellGrid(CellGrid cellGrid){
    this->cellGrid = cellGrid;
}

int Game::Update(float deltaTime){
    player.Update(cellGrid, deltaTime);
    if((IsKeyPressed(KEY_R) && levelCleared == false )|| player.score == 0){
        player.ResetPlayer();
        player.allowMovement = false;
        player.score = 10;
        return 0;
    }

    //What to do when the coins have been collected
    if(cellGrid.CoinsCollected()){
        player.allowMovement = false;
        levelCleared = true;
    }

    if(levelCleared){
        if(IsKeyPressed(KEY_R)){
            player.SaveScore();
            player.ResetPlayer();
            player.allowMovement = false;
            player.score = 10;
            levelCleared = false;
        return 0;
        }
        if(IsKeyPressed(KEY_N)){

        }
    }

    return -1;
}

void Game::Draw() {
    if(levelCleared){
        DrawRectangle(5, 50, 310, 100, WHITE);
        DrawText(std::string("You score is " + std::to_string(player.score)).c_str(), 6, 51, 20, BLACK);
        DrawText("Press R to go back and save score", 6, 81, 20, BLACK);
        DrawText("Press N to keep playing", 6, 111, 20, BLACK);
        return;
    }
    cellGrid.Draw();
    player.Draw();
    DrawText(("Score: " + std::to_string(player.score)).c_str(), 1, 170, 10, WHITE);
}

void Game::GameOver(){
}


