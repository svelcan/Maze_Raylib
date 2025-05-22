#include "Game.hpp"
#include "CellGrid.hpp"
#include <raylib.h>


Game::Game(){
    this->cellGrid = CellGrid({10,10});
    this->player = Player();
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
}

int Game::Update(float deltaTime){
    player.Update(cellGrid);
    if(IsKeyPressed(KEY_SPACE)){
        cellGrid.GenerateBackTrackingMaze();
    }
    if(IsKeyPressed(KEY_R)){
        return 0;
    }
    return -1;
}

void Game::GameOver(){
}


