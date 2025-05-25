#include "CellGrid.hpp"
#include "../core/Constants.hpp"
#include <cmath>
#include <raylib.h>
#include <raymath.h>
#include <stack>
#include <algorithm>



//Constructor that sets the size of the maze
CellGrid::CellGrid(int rows, int columns){
    //Adequate size of the maze so that it doesn't go off screen;
    if(rows >= maxRows || columns >= maxColumns){
        rows = maxRows;
        columns = maxColumns;
    }

    this->rows = rows;
    this->columns = columns;
    
    Vector2 totalSizeMaze = {float(columns*cellSize - wallSize), float(rows*cellSize - wallSize)};
    origin = {gameWidth/2.0f - totalSizeMaze.x/2, gameHeight/2.0f - totalSizeMaze.y/2-4};

    

    this->grid = std::vector<std::vector<Cell>>(rows, std::vector<Cell>(columns));
    
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < columns; ++x) {
            grid[y][x] = Cell({float(x * cellSize + origin.x), float(y * cellSize + origin.y)});
        }
    }

    setCoinsLevel();
}

//Returns cell using grid coordinates
Cell& CellGrid::getCell(int row, int col) {
    return grid[row][col];
}

//Returns cell using pixel coordinates
Cell& CellGrid::getCellAtPosition(Vector2 pos) {
    int col = (pos.x - origin.x)/ cellSize;
    int row = (pos.y - origin.y)/ cellSize;
    return grid[row][col];
}
//Returns number of columns
int CellGrid::getColumns(){
    return this->columns;
}

//Returns number of rows
int CellGrid::getRows(){
    return this->rows;
}

//Returns the origin of the maze
Vector2 CellGrid::getOrigin(){
    return this->origin;
}

//Makes the maze visible
void CellGrid::setVisibleWalls(bool visible){
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < columns; ++x) {
            grid[y][x].wall_bottom.visible = visible;
            grid[y][x].wall_right.visible = visible;
        }
    }
}

/*
* COINS ----------------------------------------------------------------------------------------------
*/

//Returns true if all the coins have been collected
bool CellGrid::CoinsCollected(){
    for(Coin coin : coins){
        if(coin.exists){
        }
    }

    //If a coin doesn't exist then delete it
    coins.erase(
    std::remove_if(
        coins.begin(), 
        coins.end(), 
        [](const Coin& coin) { return !coin.exists; }
    ), 
    coins.end()
    );

    //if coins is empty then every coin has been collected
    if(coins.empty()){
        return true;
    }
    return false;
}

//Randomizes the coins positions in the maze
//We didn't account for two or more coins getting the same position
void CellGrid::setCoinsLevel(){
    //Linear Scaling
    int numberCoins = std::floor(rows*columns / 10);

    //Always add a coin in the opposite corner
    Coin coin = {true, getCell((float(rows)-1), float(columns)-1).getPosition()};
    coins.push_back(coin);

    for(int i = 0; i < numberCoins; i++){
        //Randomize coin position and push
        Coin coin = {true, getCell(float(GetRandomValue(0, rows-1)), float(GetRandomValue(0, columns-1))).getPosition()};
        coins.push_back(coin);
    }
}

/*
* MAZE ALGORITHMS ----------------------------------------------------------------------------------------------
*/

//Generates a funny looking unplayable maze
void CellGrid::GenerateRandomMaze(){

    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < columns; ++x) {
            grid[y][x].RandomizeWalls();
        }
    }
}

//Generates a maze using backtracking
void CellGrid::GenerateBackTrackingMaze(){
    ResetGrid();

    std::stack<Cell> mazeStack;

    mazeStack.push(grid[0][0]);
    grid[0][0].visited = true;
    

    //Choose between going up, down, left or right
    //1 up 2 down 3 left 4 right
    Vector2 up = {0, -1};
    Vector2 down = {0, 1};
    Vector2 left = {-1, 0};
    Vector2 right = {1, 0};

    while(!mazeStack.empty()){
        Vector2 cellPositionInGrid = Vector2Divide(Vector2Subtract(mazeStack.top().getPosition(), origin), 
                                                  Vector2{static_cast<float>(cellSize), static_cast<float>(cellSize)});
        std::vector<Vector2> options = {up, down, left, right};
        while(!options.empty()){            
            int randomDirection = GetRandomValue(0, options.size()-1);
            Vector2 direction = options[randomDirection];

            Vector2 nextPosition = Vector2Add(cellPositionInGrid, direction);

            //If the cell is valid, add it to the stack, mark it as visited and go to that available cell
            //Also remove walls when moving
            //If the cell isn't valid erase the possibility of that direction and repeat
            if(isValid(nextPosition)){
                Cell& currentCell = getCell(cellPositionInGrid.y, cellPositionInGrid.x);
                Cell& nextCell = getCell(nextPosition.y, nextPosition.x);

                // Remove walls between currentCell and nextCell
                if (direction.x == 1) { // right
                    currentCell.wall_right.exists = false;
                } else if (direction.x == -1) { // left
                    nextCell.wall_right.exists = false;
                } else if (direction.y == 1) { // down
                    currentCell.wall_bottom.exists = false;
                } else if (direction.y == -1) { // up
                    nextCell.wall_bottom.exists = false;
                }




                mazeStack.push(nextCell);
                nextCell.visited = true;
                cellPositionInGrid = nextPosition;
                options = {up, down, left, right};
            } else {
                options.erase(options.begin() + randomDirection);
            }

        }

        //If there aren't any valid cells then backtrack
        mazeStack.pop();
    }
}


//Check if cell is inside the grid and not visited
bool CellGrid::isValid(Vector2 cellPosition){
    if(cellPosition.x < 0
        || cellPosition.y < 0
        || cellPosition.x >= columns
        || cellPosition.y >= rows){
        return false;
    } 
    return !grid[cellPosition.y][cellPosition.x].visited;
}

//Prepares the grid for generating a new maze
void CellGrid::ResetGrid(){
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < columns; ++x) {
            grid[y][x].wall_bottom.exists = true;
            grid[y][x].wall_right.exists = true;
            grid[y][x].wall_bottom.visible = true;
            grid[y][x].wall_right.visible = true;
            grid[y][x].visited = false;
        }
    }
}

//Marks every cell as unvisited
void CellGrid::ResetVisited(){
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < columns; ++x) {
            grid[y][x].visited = false;
        }
    }
}

/*
* RENDERING ----------------------------------------------------------------------------------------------
*/

//Draw method
void CellGrid::Draw(){
    for (float y = 0; y < rows; ++y) {
        for (float x = 0; x < columns; ++x) {
            grid[y][x].Draw();
        }
    }

    for (Coin coin : coins) {
        coin.Draw();
    }
}