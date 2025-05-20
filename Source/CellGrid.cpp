#include "CellGrid.hpp"
#include "Constants.hpp"
#include <raylib.h>
#include <raymath.h>



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


void CellGrid::GenerateRandomMaze(){

    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < columns; ++x) {
            grid[y][x].RandomizeWalls();
        }
    }
}







void CellGrid::Draw(){
    for (float y = 0; y < rows; ++y) {
        for (float x = 0; x < columns; ++x) {
            grid[y][x].Draw();
        }
    }
}