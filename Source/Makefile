# Compiler
CXX = g++

# Flags
CXXFLAGS = -std=c++11 -Wall

# Libraries
LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Source files (adjust paths as needed)
SOURCES = main.cpp core/Game.cpp core/Constants.cpp objects/Cell.cpp objects/CellGrid.cpp objects/Player.cpp states/Menu.cpp objects/ClickableObject.cpp objects/Flare.cpp

# Output executable
EXECUTABLE = a.out

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(EXECUTABLE) $(LIBS)

clean:
	rm -f $(EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE)