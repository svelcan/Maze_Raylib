#pragma once

#include <raylib.h>
#include "Cell.hpp"
#include <list>
#include <stack>
#include <vector>


class Maze{
    private:
    std::vector<std::vector<Cell>> grid;
    int rows, colummns;
    
    //TODO add maximum size of maze (around 35*63 probably)
    std::list<Cell> maze;
    std::stack<Cell> mazeStack;

    public:
    //Placeholders for now
    Cell currentCell = Cell();
    std::vector<int> options = {1,2,3,4};

    //Constructor & Deconstructor
    Maze();

    //Generates a maze that has every wall placed
    void GenerateGrid();

    //Generates a maze that makes no sense because walls are placed randomly
    void GenerateRandomGrid();

    //Generates a maze using a backtracking algorithm
    void GenerateBackTrackingGrid();
    //Checks thingys
    bool isValid(Cell cell);

    //Draws to the screen
    void Draw();
};