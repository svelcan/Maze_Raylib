#include "Game.hpp"
#include "CellGrid.hpp"
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


void Game::Draw() {
    cellGrid.Draw();
    player.Draw();
    DrawText(("Score: " + std::to_string(player.score)).c_str(), 1, 170, 10, WHITE);
}

int Game::Update(float deltaTime){
    player.Update(cellGrid, deltaTime);
    if(IsKeyPressed(KEY_R)){
        player.ResetPlayer();
        player.allowMovement = false;
        return 0;
    }
    return -1;
}

void Game::GameOver(){
}


