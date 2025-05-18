#include "Game.hpp"


Game::Game(){
    this->cellGrid = CellGrid({35,63});
    this->player = Player();
    InitAudioDevice();

    //eatSound = LoadSound("Sounds/eat.mp3");
    //wallSound = LoadSound("Sounds/wall.mp3");
}

Game::~Game(){
    //UnloadSound(eatSound);
    //UnloadSound(wallSound);
}



void Game::Draw() {
    cellGrid.Draw();
    player.Draw();
}

void Game::Update(float deltaTime){
    player.Update();
}

void Game::GameOver(){
}


