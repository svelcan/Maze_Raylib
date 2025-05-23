#pragma once 

#include <raylib.h>
#include <string>

class ClickableObject{
    private:
    Vector2 position = {0,0};
    Vector2 size;
    std::string text = "";


    public:
    //Constructor & Deconstructor
    ClickableObject(Vector2 position, Vector2 size, std::string text);
    ~ClickableObject();

    //Getters & Setters
    Vector2 getPosition();
    void setPosition(Vector2 position);

    void setText(std::string text){
        this->text = text;
    }

    //Important methods
    bool IsAbove();

    //General methods
    void Draw();
};