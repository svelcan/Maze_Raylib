#include "Flare.hpp"

#include <raylib.h>
#include "Cell.hpp"
#include "CellGrid.hpp"
#include "../core/Constants.hpp"
#include <raymath.h>
#include <stack>

//Choose between going up, down, left or right
//1 up 2 down 3 left 4 right
Vector2 up = {0, -1};
Vector2 down = {0, 1};
Vector2 left = {-1, 0};
Vector2 right = {1, 0};


Flare::Flare(){
}

//Similar to the backtracking algorithm, we explore the maze and If we get to a point where there are no cells
//available then that means that path is a dead end, so we backtrack to the last time we had to make a decision
void Flare::FindShortestPath(CellGrid& cellGrid, Vector2 positionCell, Vector2 destination){
    //TODO when the objective changes to coins this bug catcher will probably be useless
    //This prevents a flare from being thrown if the player is standing in the objective
    if(Vector2Equals(positionCell, Vector2Add({Vector2Scale(destination, cellSize)}, cellGrid.getOrigin()))){
        return;
    }

    cellGrid.ResetVisited();
    Vector2 cellPositionInGrid = Vector2Scale(Vector2Subtract(positionCell, cellGrid.getOrigin()), 1.0f/cellSize);
    Vector2 destinationPosition = Vector2Add(Vector2Scale(destination, cellSize), cellGrid.getOrigin());

    std::stack<Cell> mazeStack;

    mazeStack.push(cellGrid.getCell(cellPositionInGrid.y, cellPositionInGrid.x));
    cellGrid.getCell(cellPositionInGrid.y, cellPositionInGrid.x).visited = true;

    while(true){
        cellPositionInGrid = Vector2Scale((Vector2Subtract(mazeStack.top().getPosition(), cellGrid.getOrigin())), 1.0f/cellSize);
        std::vector<Vector2> options = {up, down, left, right};


        while(!options.empty()){         
               
            Vector2 direction = options[0];

            Vector2 nextPosition = Vector2Add(cellPositionInGrid, direction);

            
            //If the cell is valid, add the current one to the stack, mark it as visited and go to that available cell
            //Also remove walls when moving
            //If the cell isn't valid erase the possibility of that direction and repeat
            if(isValid(cellPositionInGrid, nextPosition, direction, cellGrid)){
                Cell& nextCell = cellGrid.getCell(nextPosition.y, nextPosition.x);

                mazeStack.push(nextCell);
                nextCell.visited = true;
                cellPositionInGrid = nextPosition;
                options = {up, down, left, right};

                

                if(Vector2Equals(mazeStack.top().getPosition(), destinationPosition)){
                    //Placeholder for now so that the animation doesn't end abruptly
                    movementOrder.push({0,0});


                    while(!mazeStack.empty()){
                        movementOrder.push(mazeStack.top().getPosition());
                        mazeStack.pop();
                    }

                    return;
                }

            } else {
                options.erase(options.begin());
            }

        }

        //If there aren't any valid cells then backtrack biatch
        mazeStack.pop();
    }
}

bool Flare::isValid(Vector2 currentPosition, Vector2 nextPosition, Vector2 direction, CellGrid& cellGrid){
    //If out of bounds return false
    if(nextPosition.x < 0
        || nextPosition.y < 0
        || nextPosition.x >= cellGrid.getColumns()
        || nextPosition.y >= cellGrid.getRows()){
        return false;
    } 
    

    //If there is a wall return false
    if(Vector2Equals(direction, right) && cellGrid.getCell(currentPosition.y, currentPosition.x).wall_right.exists){
        return false;
    }
    if(Vector2Equals(direction, down) && cellGrid.getCell(currentPosition.y, currentPosition.x).wall_bottom.exists){
        return false;
    }
    if(Vector2Equals(direction, left) && cellGrid.getCell(nextPosition.y, nextPosition.x).wall_right.exists){
        return false;
    }
    if(Vector2Equals(direction, up) && cellGrid.getCell(nextPosition.y, nextPosition.x).wall_bottom.exists){
        return false;
    }

    //If already visited return false, else true
    return !cellGrid.getCell(nextPosition.y, nextPosition.x).visited;
}

void Flare::ChooseCoin(Vector2 playerPosition, CellGrid& cellGrid){
    unsigned int least = 10000; //Arbitrarily large number (I think the shortest path can be max 17*31 = 527 but I'm not gonna wager on that)
    std::stack<Vector2> movementOrderAuxiliar;

    //This will let live the smallest movementOrder
    for(CellGrid::Coin coin : cellGrid.coins){
        Vector2 coinPositionInGrid = Vector2Scale(Vector2Subtract(coin.position, cellGrid.getOrigin()), 1.0f/cellSize);
        FindShortestPath(cellGrid, playerPosition, coinPositionInGrid);

        if(movementOrder.size() < least){
            least = movementOrder.size();
            movementOrderAuxiliar = movementOrder;
        }
        Reset();
    }
    movementOrder = movementOrderAuxiliar;
}

bool Flare::isMovementOrderEmpty(){
    return movementOrder.empty();
}

void Flare::Reset(){
    while (!movementOrder.empty()) {
        movementOrder.pop();
    }
    currentPosition = {-100, -100};
    moveProgress = 1;
}

void Flare::Update(float deltaTime){

    if (!movementOrder.empty()) {
        // Check if we need a new target
        if (moveProgress >= 1.0f) {
            // Get new target
            targetPosition = movementOrder.top();
            movementOrder.pop();

            if (currentPosition.x == -100 && currentPosition.y == -100) {
                currentPosition = targetPosition;
                startPosition = targetPosition; // Avoid lerping from (-100,-100)
                moveProgress = 1.0f; // Mark movement as complete
            } else {
                // Normal movement setup
                startPosition = currentPosition;
                moveProgress = 0.0f;
                timeSinceMoveStart = 0.0f;
            }
        }

        // Only update if we have a valid duration
        if (moveDuration > 0.0f) {
            // Update movement progress
            timeSinceMoveStart += deltaTime;
            moveProgress = timeSinceMoveStart / moveDuration;

            // Clamp progress to 1.0
            moveProgress = std::min(moveProgress, 1.0f);

            // Interpolate position
            currentPosition = {
                startPosition.x + (targetPosition.x - startPosition.x) * moveProgress,
                startPosition.y + (targetPosition.y - startPosition.y) * moveProgress
            };
        }
    } else {
        currentPosition = {-100, -100};  // Or whatever your "hidden" position should be
        moveProgress = 1.0f;
    }
}

void Flare::Draw(){
    DrawRectangle(currentPosition.x+3, currentPosition.y+3, 2, 2, RED);
}