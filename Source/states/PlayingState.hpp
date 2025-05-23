#pragma once

#include "GameState.hpp"
#include "../core/Game.hpp"

class PlayingState : public GameState {
    Game game;

public:
    PlayingState(CellGrid grid);
    
    void Update(float deltaTime) override;
    void Draw() override;
    GameState* GetNextState() override;
};