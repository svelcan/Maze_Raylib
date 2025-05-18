#include "Player.hpp"
#include <raylib.h>


Player::Player(){
    position = {2,2};
}

Player::~Player(){

}

void Player::setPosition(Vector2 position){
    this->position = position;
}

void Player::Update(){
    if(IsKeyPressed(KEY_RIGHT)){
        position.x += 5;
    }
    if(IsKeyPressed(KEY_LEFT)){
        position.x -= 5;
    }
    if(IsKeyPressed(KEY_DOWN)){
        position.y += 5;
    }
    if(IsKeyPressed(KEY_UP)){
        position.y -= 5;
    }
}

void Player::Draw(){
    DrawRectangle(position.x, position.y, 2, 2, RED);
}