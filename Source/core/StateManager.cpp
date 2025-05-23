#include "StateManager.hpp"
#include "../states/MainMenuState.hpp"  // Include for the initial state

StateManager::StateManager(int gameWidth, int gameHeight) {
    target = LoadRenderTexture(gameWidth, gameHeight);
    currentState = std::make_unique<MainMenuState>();
}

StateManager::~StateManager() {
    UnloadRenderTexture(target);
}

void StateManager::UpdateAndDraw() {
    float deltaTime = GetFrameTime();
    
    // Update current state
    currentState->Update(deltaTime);
    
    // Check for state transition
    GameState* nextState = currentState->GetNextState();
    if(nextState) {
        currentState.reset(nextState);
    }
    
    // Draw to render texture
    BeginTextureMode(target);
        ClearBackground(BLACK);
        currentState->Draw();
    EndTextureMode();
    
    // Draw to screen
    BeginDrawing();
        ClearBackground(BLACK);
        DrawTexturePro(
            target.texture,
            {0, 0, (float)target.texture.width, -(float)target.texture.height},
            {0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()},
            {0, 0},
            0.0f,
            WHITE
        );
    EndDrawing();
}

bool StateManager::ShouldExit() const {
    return currentState->ShouldExit();
}