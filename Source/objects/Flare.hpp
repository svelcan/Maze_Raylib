#pragma once

#include "CellGrid.hpp"
#include <raylib.h>
#include <stack>

class Flare{
    private:
    //Animation stuff
    Vector2 startPosition;
    Vector2 currentPosition = {-100,-100};
    Vector2 targetPosition;
    float moveDuration = 0.2f;
    float moveProgress;
    float timeSinceMoveStart;
    std::stack<Vector2> movementOrder;

    public:

    //Constructor & Destructor
    Flare();

    //Pathfinding stuff
    void ChooseCoin(Vector2 playerPosition, CellGrid& cellGrid);
    void FindShortestPath(CellGrid& grid, Vector2 positionCell, Vector2 destination);
    bool isValid(Vector2 currentPosition, Vector2 nextPosition, Vector2 direction, CellGrid& cellGrid);
    void Reset();

    //Getters & Setters
    bool isMovementOrderEmpty();

    //Update and Draw
    void Update(float deltaTime);
    void Draw();
};