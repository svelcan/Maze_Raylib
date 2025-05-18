#include "Game.hpp"


Game::Game(){
    cellGrid = CellGrid({35,63});
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
}

void Game::Update(float deltaTime){
}

void Game::GameOver(){
}


