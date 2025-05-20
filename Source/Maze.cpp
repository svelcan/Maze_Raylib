#include "Maze.hpp"
#include "Constants.hpp"

void Maze::GenerateGrid(){
    maze.clear();

    //TODO this is a horrible placeholder for when I finally center everything by myself
    //TODO I'm just lazy, this shouldn't take a lot of time
    for(float i = 14; i < size.x+14; i++){
        for(float j = 5; j < size.y+5; j++){
            Cell cell = Cell({i*cellSize,j*cellSize});
            maze.push_back(cell);
        }
    }
}

void Maze::GenerateRandomGrid(){
    maze.clear();

    for(float i = 0; i < size.x; i++){
        for(float j = 0; j < size.y; j++){
            Cell cell = Cell({j*cellSize,i*cellSize});
            cell.RandomizeWalls();
            maze.push_back(cell);
        }
    }
}


//TODO fix return statement
void Maze::GenerateBackTrackingGrid(){

    currentCell = Cell({5.0f*cellSize, 5.0f*cellSize});
    mazeStack.push(currentCell);
    currentCell.visited = true;

    //Choose between going up, down, left or right
    //1 up 2 down 3 left 4 right
    Vector2 up = {0, float(-cellSize)};
    Vector2 down = {0, float(cellSize)};
    Vector2 left = {float(-cellSize), 0};
    Vector2 right = {float(cellSize), 0};


    //Check if the cell chosen is valid aka there is no wall or limit
    //If valid go there, add position to the stack of visited cells and repeat process
    while(!mazeStack.empty()){
        while(!options.empty()){
            int randomDirection = GetRandomValue(1, options.size());
            Vector2 direction;

            switch (options[randomDirection - 1]) {
                case 1: direction = up; break;
                case 2: direction = down; break;
                case 3: direction = left; break;
                case 4: direction = right; break;
            }

            Vector2 nextPosition = Vector2Add(currentCell.getPosition(), direction);

            if(isValid(Cell(nextPosition))){
                currentCell.visited = true;
                options = {1,2,3,4};
                //mazeStack.push(cell);
                //currentCell = cell;
            }

        }

        //If there aren't any valid cells then backtrack biatch
        if(options.empty()){
            //Draw the cell before backtracking
            currentCell.wall_bottom = 1;
            currentCell.wall_right = 1;
            currentCell.Draw();
            mazeStack.pop();
            currentCell = mazeStack.top();
        }
    }
    std::cout << "please work";
}

//Check if cell is inside the grid and not visited
bool Maze::isValid(Cell cell){
    if(cell.visited || cell.getPosition().x < 0 || cell.getPosition().y < 0 || cell.getPosition().x > size.x || cell.getPosition().y > size.y){
        return false;
    }
    return true;
}