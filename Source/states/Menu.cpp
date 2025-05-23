#include "Menu.hpp"
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
    ClickableObject howtoplayButton = ClickableObject({60, 130},{150, 40},"How to Play");
    ClickableObject scoresButton = ClickableObject({230, 110},{80, 50},"Highest\nScores");
    AddButton(startButton);
    AddButton(exitButton);
    AddButton(howtoplayButton);
    AddButton(scoresButton);
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

void Menu::CreateHowtoplayMenu(){
    ClickableObject returnButton = ClickableObject({60, 130},{150, 40},"Return");
    AddButton(returnButton);
}

void Menu::CreateScoresMenu(){
    ClickableObject returnButton = ClickableObject({60, 130},{150, 40},"Return");
    AddButton(returnButton);
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