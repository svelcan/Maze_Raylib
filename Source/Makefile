# Compiler
CXX = g++

# Flags
CXXFLAGS = -std=c++11 -Wall

# Libraries
LIBS = -Llib -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Wl,-rpath=\$$ORIGIN

# Source files (adjust paths as needed)
SOURCES = main.cpp core/Game.cpp core/Constants.cpp objects/Cell.cpp objects/CellGrid.cpp objects/Player.cpp objects/Flare.cpp states/Menu.cpp states/ClickableObject.cpp

# Output executable
EXECUTABLE = InvisibleMaze

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(EXECUTABLE) $(LIBS)

clean:
	rm -f $(EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE)