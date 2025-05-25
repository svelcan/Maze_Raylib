#pragma once

#include <raylib.h>



class Cell{
    private:
    //Variables
    Vector2 position;

    public:

    //Struct for Wall
    struct Wall {
        bool exists;
        bool visible;
    };

    //Public variables
    Wall wall_bottom;
    Wall wall_right;
    bool visited = false;

    //Constructor & Deconstructor
    Cell();
    Cell(Vector2 position);

    //Getters & Setters
    void setPosition(Vector2 position);
    Vector2 getPosition();


    //This method is never used but it was a fun way to see if the code worked in the beggining
    void RandomizeWalls();

    //Update & Draw
    void Draw();
};