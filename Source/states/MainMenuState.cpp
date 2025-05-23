#include "MainMenuState.hpp"

MainMenuState::MainMenuState() {
    menu.CreateMainMenu();
}

GameState* MainMenuState::GetNextState(){
        switch(menu.GetLastSelection()) {
            case 0: return new SingleplayerMenuState();
            case 1: return new ExitState();
            case 2: return new HowToPlayState();
            default: return nullptr;
        }
}

void MainMenuState::Update(float deltaTime){
    menu.Update(deltaTime);
}

void MainMenuState::Draw(){
    menu.Draw();
}