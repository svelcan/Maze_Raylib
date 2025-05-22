rm a.out
g++ main.cpp Game.cpp Constants.cpp Cell.cpp CellGrid.cpp Player.cpp Menu.cpp ClickableObject.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
./a.out