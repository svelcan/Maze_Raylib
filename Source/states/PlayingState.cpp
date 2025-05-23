#include "PlayingState.hpp"
#include "MainMenuState.hpp"

/*PlayingState::PlayingState(CellGrid grid) : game(grid) {
    game.getCellGrid().GenerateBackTrackingMaze();
}*/

void PlayingState::Update(float deltaTime) {
    game.Update(deltaTime);
}

void PlayingState::Draw() {
    game.Draw();
}
/*
GameState* PlayingState::GetNextState() {
    if (game.ShouldReturnToMenu()) {
        return new MainMenuState();
    }
    return nullptr;
}*/