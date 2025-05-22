#pragma once 

#include <raylib.h>
#include "CellGrid.hpp"
#include "Flare.hpp"

class Player{
    private:
    Vector2 initialPosition;
    Vector2 position;
    Vector2 size = {4,4};
    Texture2D texture;

    Vector2 lastKnownMazeSize = {10,10};

    Flare flare = Flare();
    

    public:
    bool allowMovement = false;
    int score = 10;
    
    //Constructor & Deconstructor
    Player();
    Player(CellGrid& cellGrid);
    ~Player();

    //Getters & Setters
    void setPosition(Vector2 position);
    Vector2 getPosition();

    void ResetPlayer();
    void ResetScore();
    bool IsThereCell(Vector2 positionCell, CellGrid& cellGrid);

    void Update(CellGrid& cellGrid, float deltaTime);
    void Draw();
};