#pragma once

#include <vector>
#include "ClickableObject.hpp"

class Menu{
    private:
    //Variables
    std::vector<ClickableObject> buttons;

    public:
    //Constructors & Destructor
    Menu();

    //Menu studd
    void AddButton(ClickableObject button);
    void ResetButtons();

    //Every menu, we know this isn't the best approach but at least it works
    void CreateMainMenu();
    void CreateSingleplayerMenu();
    void CreateMazesizeMenu();
    void CreateHowtoplayMenu();
    void CreateScoresMenu();

    //Updating and Drawing
    int Update(float deltaTime);
    void Draw();
};
