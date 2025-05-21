#include "CellGrid.hpp"
#include "Cell.hpp"
#include "Constants.hpp"
#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <stack>



CellGrid::CellGrid(){
}

CellGrid::CellGrid(int rows, int columns){
    //TODO Find an efficient way to center the maze depending on size
    this->position = {50, 30};

    this->rows = rows;
    this->columns = columns;
    this->grid = std::vector<std::vector<Cell>>(rows, std::vector<Cell>(columns));
    
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < columns; ++x) {
            grid[y][x] = Cell({float(x * cellSize + position.x), float(y * cellSize + position.y)});
        }
    }
}

Cell& CellGrid::getCell(int row, int col) {
    return grid[row][col];
}

Cell& CellGrid::getCellAtPosition(Vector2 pos) {
    int col = pos.x / cellSize;
    int row = pos.y / cellSize;
    return grid[row][col];
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

    std::stack<Cell> mazeStack;
    Vector2 cellPositionInGrid = {3,3};

    mazeStack.push(grid[cellPositionInGrid.y][cellPositionInGrid.x]);
    

    //Choose between going up, down, left or right
    //1 up 2 down 3 left 4 right
    Vector2 up = {0, -1};
    Vector2 down = {0, 1};
    Vector2 left = {-1, 0};
    Vector2 right = {1, 0};

    std::cout << "First Check" << std::endl;
    while(!mazeStack.empty()){
        std::vector<Vector2> options = {up, down, left, right};
        while(!options.empty()){
            std::cout << "Second Check" << std::endl;
            std::cout << options.size();
            
            int randomDirection = GetRandomValue(0, options.size()-1);
            Vector2 direction = options[randomDirection];

            Vector2 nextPosition = Vector2Add(cellPositionInGrid, direction);

            //If the cell is valid, add it to the stack, mark it as visited and go to that available cell
            //If the cell isn't valid erase the possibility of that direction and repeat
            if(isValid(nextPosition)){
                mazeStack.push(getCell(nextPosition.y, nextPosition.x));
                getCell(nextPosition.y, nextPosition.x).visited = true;
                cellPositionInGrid = nextPosition;
            } else {
                options.erase(options.begin() + randomDirection);
            }

        }

        std::cout << "Third check" << std::endl;
        
        //If there aren't any valid cells then backtrack biatch

        getCellAtPosition(mazeStack.top().getPosition()).wall_bottom = 0;
        getCellAtPosition(mazeStack.top().getPosition()).wall_right = 1;
        mazeStack.pop();
    }
    std::cout << "The one piece is real!!!";
}


//Check if cell is inside the grid and not visited
bool CellGrid::isValid(Vector2 cellPosition){
    if(cellPosition.x < 0
        || cellPosition.y < 0
        || cellPosition.x > columns
        || cellPosition.y > rows){
        return false;
    } 
    return !grid[cellPosition.y][cellPosition.x].visited;
}





void CellGrid::Draw(){
    for (float y = 0; y < rows; ++y) {
        for (float x = 0; x < columns; ++x) {
            grid[y][x].Draw();
        }
    }
}