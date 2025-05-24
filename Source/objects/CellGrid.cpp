#include "CellGrid.hpp"
#include "../core/Constants.hpp"
#include <raylib.h>
#include <raymath.h>
#include <stack>



CellGrid::CellGrid(){
}

CellGrid::CellGrid(int rows, int columns){
    Vector2 totalSizeMaze = {float(columns*cellSize - wallSize), float(rows*cellSize - wallSize)};
    origin = {gameWidth/2.0f - totalSizeMaze.x/2, gameHeight/2.0f - totalSizeMaze.y/2-4};

    this->rows = rows;
    this->columns = columns;
    this->grid = std::vector<std::vector<Cell>>(rows, std::vector<Cell>(columns));
    
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < columns; ++x) {
            grid[y][x] = Cell({float(x * cellSize + origin.x), float(y * cellSize + origin.y)});
        }
    }

    coin = {true, true, getCell((float(rows)-1), float(columns)-1).getPosition()};
    coint = {true, true, getCell((float(rows)-1), 0).getPosition()};
    coinp = {true, true, getCell(0, float(columns)-1).getPosition()};
}

Cell& CellGrid::getCell(int row, int col) {
    return grid[row][col];
}

Cell& CellGrid::getCellAtPosition(Vector2 pos) {
    int col = (pos.x - origin.x)/ cellSize;
    int row = (pos.y - origin.y)/ cellSize;
    return grid[row][col];
}

int CellGrid::getColumns(){
    return this->columns;
}

int CellGrid::getRows(){
    return this->rows;
}

Vector2 CellGrid::getOrigin(){
    return this->origin;
}

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

bool CellGrid::CoinsCollected(){
    if(!coin.visible && !coint.visible && !coinp.visible){
        return true;
    }
    return false;
}

/*
* MAZE ALGORITHMS ----------------------------------------------------------------------------------------------
*/
void CellGrid::GenerateRandomMaze(){

    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < columns; ++x) {
            grid[y][x].RandomizeWalls();
        }
    }
}

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

        //If there aren't any valid cells then backtrack biatch
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

void CellGrid::Draw(){
    for (float y = 0; y < rows; ++y) {
        for (float x = 0; x < columns; ++x) {
            grid[y][x].Draw();
        }
    }

    if(coin.visible){
        coin.Draw();
    }
    if(coint.visible){
        coint.Draw();
    }
    if(coinp.visible){
        coinp.Draw();
    }
}