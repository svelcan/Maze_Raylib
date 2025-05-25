#pragma once 

#include <raylib.h>
#include "CellGrid.hpp"
#include "Flare.hpp"

class Player{
    private:
    //Variables
    Vector2 initialPosition;
    Vector2 position;
    Vector2 size = {4,4};
    Texture2D texture;
    Vector2 lastKnownMazeSize = {10,10};
    

    public:
    //Public variables
    bool allowMovement = false;
    int score = 10;
    Flare flare = Flare();
    
    //Constructor & Deconstructor
    Player(CellGrid& cellGrid);

    //Getters & Setters
    void setPosition(Vector2 position);
    Vector2 getPosition();

    //Player specific methods
    void ResetPlayer();
    void ResetScore();
    void SaveScore();
    bool IsThereCell(Vector2 positionCell, CellGrid& cellGrid);
    

    //Update & Draw
    void Update(CellGrid& cellGrid, float deltaTime);
    void Draw();
};