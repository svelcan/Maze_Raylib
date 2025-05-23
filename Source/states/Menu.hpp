#pragma once

#include <vector>
#include "../objects/ClickableObject.hpp"

class Menu{
    private:
    std::vector<ClickableObject> buttons;

    public:
    //Constructors & Destructor
    Menu();

    void AddButton(ClickableObject button);
    void ResetButtons();

    //Every menu I will use
    void CreateMainMenu();
    void CreateMultiplayerMenu();
    void CreateSingleplayerMenu();
    void CreateMazesizeMenu();
    void CreatePositionresetMenu();
    void CreateHowtoplayMenu();

    //Updating and Drawing
    int Update(float deltaTime);
    void Draw();
};
