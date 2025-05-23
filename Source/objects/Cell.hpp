#pragma once

#include <raylib.h>



class Cell{
    private:
    

    Vector2 position;

    

    public:

    //Struct for Wall
    struct Wall {
        bool exists;
        bool visible;
    };

    Wall wall_bottom;
    Wall wall_right;
    bool visited = false;

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