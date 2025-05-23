#include "ClickableObject.hpp"
#include "../core/Constants.hpp"
#include <raylib.h>

//Constructors & Destructors
ClickableObject::ClickableObject(Vector2 position, Vector2 size, std::string text){
    this->size = size;
    this->position = position;
    this->text = text;
}

ClickableObject::~ClickableObject(){

}


//Getters & Setters
void ClickableObject::setPosition(Vector2 position){
    this->position = position;
}




bool ClickableObject::IsAbove(){
    if(GetMousePosition().x > position.x * GetScreenWidth()/gameWidth &&
                GetMousePosition().x < (position.x + size.x) * GetScreenWidth()/gameWidth &&
                GetMousePosition().y > position.y * GetScreenHeight()/gameHeight &&
                GetMousePosition().y < (position.y + size.y) * GetScreenHeight()/gameHeight ){
                    return true;
    }
    return false;
}



void ClickableObject::Draw(){
    DrawRectangle(this->position.x, this->position.y, this->size.x, this->size.y, WHITE);
    DrawText(text.c_str(), position.x, position.y, 20, BLACK);
}
