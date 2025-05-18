#include "CellGrid.hpp"
#include "Constants.hpp"
#include <raylib.h>


CellGrid::CellGrid(){
    this->size = {5,5};
    GenerateGrid();
}

CellGrid::CellGrid(Vector2 size){
    this->size = size;
    GenerateGrid();
}

void CellGrid::Draw(){
    for (Cell cell : maze) {
        cell.Draw();
    }
}

void CellGrid::GenerateGrid(){
    maze.clear();

    for(float i = 0; i < size.x; i++){
        for(float j = 0; j < size.y; j++){
            Cell cell = Cell({j*cellSize+1,i*cellSize+1});
            maze.push_back(cell);
        }
    }
}

void CellGrid::GenerateRandomGrid(){
    maze.clear();

    for(float i = 0; i < size.x; i++){
        for(float j = 0; j < size.y; j++){
            Cell cell = Cell({j*cellSize+1,i*cellSize+1});
            cell.RandomizeWalls();
            maze.push_back(cell);
        }
    }
}