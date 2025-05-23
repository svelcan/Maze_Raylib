#pragma once

#include <memory>
#include "raylib.h"
#include "../states/GameState.hpp"  // Include the base GameState class

class StateManager {
    std::unique_ptr<GameState> currentState;
    RenderTexture2D target;
    
public:
    StateManager(int gameWidth, int gameHeight);
    ~StateManager();
    
    void UpdateAndDraw();
    bool ShouldExit() const;
};