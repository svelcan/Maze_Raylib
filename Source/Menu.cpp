#include "Menu.hpp"
#include "ClickableObject.hpp"
#include <raylib.h>

Menu::Menu(){
}

void Menu::AddButton(ClickableObject button) {
    buttons.push_back(button);
}

void Menu::ResetButtons(){
    this->buttons.clear();
}

void Menu::CreateMainMenu(){
    ClickableObject startButton = ClickableObject({60, 30},{150, 40},"Singleplayer");
    ClickableObject exitButton = ClickableObject({60, 80},{150, 40},"Exit");
    AddButton(startButton);
    AddButton(exitButton);
}

void Menu::CreateSingleplayerMenu(){
    ClickableObject mazesizeButton = ClickableObject({60, 30},{150, 40},"Maze Size");
    ClickableObject startButton = ClickableObject({60, 80},{150, 40},"Play");
    ClickableObject returnButton = ClickableObject({60, 130},{150, 40},"Return");
    AddButton(mazesizeButton);
    AddButton(startButton);
    AddButton(returnButton);
}

void Menu::CreateMazesizeMenu(){
    ClickableObject fiveButton = ClickableObject({60, 30},{150, 40},"5x5");
    ClickableObject tenButton = ClickableObject({60, 80},{150, 40},"10x10");
    ClickableObject twentyButton = ClickableObject({60, 130},{150, 40},"17x31 (MAX)");
    AddButton(fiveButton);
    AddButton(tenButton);
    AddButton(twentyButton);
}

int Menu::Update(float deltaTime){
    if(IsMouseButtonPressed(0)){
        for (size_t i = 0; i < buttons.size(); i++) {
            if(buttons[i].IsAbove()) {
                return i;
            }
        }
        
    }
    return -1;
}

void Menu::Draw(){
    for (auto& button : buttons) {
        button.Draw();
    }
}