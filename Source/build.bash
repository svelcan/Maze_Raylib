rm a.out
g++ main.cpp core/Game.cpp core/Constants.cpp objects/Cell.cpp objects/CellGrid.cpp objects/Player.cpp states/Menu.cpp objects/ClickableObject.cpp objects/Flare.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
./a.out