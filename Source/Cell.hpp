#pragma once

#include <raylib.h>



class Cell{
    private:
    

    Vector2 position;

    

    public:
    //TODO Walls should be private probably
    bool visited = false;
    bool wall_bottom = 1;
    bool wall_right = 1;

    //Constructor & Deconstructor
    Cell();
    Cell(Vector2 position);
    ~Cell();

    //Getters & Setters
    void setPosition(Vector2 position);
    Vector2 getPosition();


    void RandomizeWalls();
    void Draw();
};