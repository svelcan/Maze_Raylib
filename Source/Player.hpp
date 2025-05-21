#pragma once 

#include <raylib.h>
#include "CellGrid.hpp"

class Player{
    private:
    Vector2 initialPosition;
    Vector2 position;
    Vector2 size = {4,4};
    Texture2D texture;
    

    public:
    //Constructor & Deconstructor
    Player();
    ~Player();

    //Getters & Setters
    void setPosition(Vector2 position);
    Vector2 getPosition();

    void ResetPlayer();
    bool IsThereCell(Vector2 positionCell, CellGrid& cellGrid);

    void Update(CellGrid& cellGrid);
    void Draw();
};