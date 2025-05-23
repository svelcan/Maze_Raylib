#pragma once

#include "CellGrid.hpp"
#include <raylib.h>
#include <stack>

class Flare{
    private:
    std::stack<Vector2> movementOrder;

    Vector2 startPosition;
    Vector2 currentPosition;
    Vector2 targetPosition;

    float moveDuration = 0.2f;
    float moveProgress;
    float timeSinceMoveStart;

    public:
    Flare();

    void FindShortestPath(CellGrid& grid, Vector2 positionCell, Vector2 destination);
    bool isValid(Vector2 currentPosition, Vector2 nextPosition, Vector2 direction, CellGrid& cellGrid);

    void Update(float deltaTime);
    void Draw();
};