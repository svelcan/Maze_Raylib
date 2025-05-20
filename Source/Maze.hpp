#pragma once

#include <raylib.h>
#include <list>
#include <stack>
#include <vector>

class Maze{
    private:
    std::list<Cell> maze;
    std::stack<Cell> mazeStack;

    public:
    //Placeholders for now
    Cell currentCell = Cell();
    std::vector<int> options = {1,2,3,4};

    //Constructor & Deconstructor
    Maze();

    //Generates a maze that makes no sense because walls are placed randomly
    void GenerateRandomMaze();

    //Generates a maze using a backtracking algorithm
    void GenerateBackTrackingMaze();
    //Checks thingys
    bool isValid(Cell cell);

    //Draws to the screen
    void Draw();
};