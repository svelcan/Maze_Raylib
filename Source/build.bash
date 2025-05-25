rm -f InvisibleMaze
g++ main.cpp core/Game.cpp core/Constants.cpp objects/Cell.cpp objects/CellGrid.cpp objects/Player.cpp states/Menu.cpp states/ClickableObject.cpp objects/Flare.cpp -o InvisibleMaze -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Wl,-rpath='$ORIGIN'
./InvisibleMaze
