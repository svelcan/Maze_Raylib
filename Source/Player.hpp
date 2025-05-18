#include <raylib.h>

class Player{
    private:
    Vector2 position;
    Texture2D texture;
    

    public:
    //Constructor & Deconstructor
    Player();
    ~Player();

    //Getters & Setters
    void setPosition(Vector2 position);
    Vector2 getPosition();

    void Update();
    void Draw();
};