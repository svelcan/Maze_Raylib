#include "raylib.h"
#include "core/Game.hpp"
#include "core/Constants.hpp"
#include "states/Menu.hpp"

#include <math.h>
#include <time.h>

#include <iostream>
#include <fstream>
#include <string>




int main()
{
    //DEBUG



    //Initiate window and random seed
    InitWindow(screenWidth, screenHeight, "Magic_Maze");
    SetRandomSeed(time(NULL));

    //Create menus BAD WAY TO DO ALL OF THIS BUT AT LEAST IT WORKS
    Menu mainMenu = Menu();
    mainMenu.CreateMainMenu();

    Menu singleplayerMenu = Menu();
    singleplayerMenu.CreateSingleplayerMenu();

    Menu mazesizeMenu = Menu();
    mazesizeMenu.CreateMazesizeMenu();

    Menu howtoplayMenu = Menu();
    howtoplayMenu.CreateHowtoplayMenu();

    Menu scoresMenu = Menu();
    scoresMenu.CreateScoresMenu();


    Game game = Game();

    //Game state management
    enum class GameState{ MAIN_MENU, PLAYING, EXITING, MULTIPLAYER_MENU, SINGLEPLAYER_MENU, MAZESIZE_MENU, POSITIONRESET_MENU, HOWTOPLAY_MENU, SCORES_MENU};
    GameState currentState = GameState::MAIN_MENU;

    // Create a render texture at the game's internal resolution
    RenderTexture2D target = LoadRenderTexture(gameWidth, gameHeight);

    while (!WindowShouldClose())
    {
        //Framerate
        float deltaTime = GetFrameTime();
        
        //State-based Updating
        switch (currentState)
        {
            case GameState::EXITING:
                CloseWindow();
                return 0;
                break;
                
            case GameState::PLAYING:
                switch (game.Update(deltaTime)) {
                    case -1:
                        currentState = GameState::PLAYING;
                        break;
                    case 0:
                        currentState = GameState::MAIN_MENU;
                        break;
                }
                break;
            case GameState::MAIN_MENU:
                switch (mainMenu.Update(deltaTime)) {
                    case -1:
                        currentState = GameState::MAIN_MENU;
                        break;
                    case 0:
                        currentState = GameState::SINGLEPLAYER_MENU;
                        break;
                    case 1:
                        currentState = GameState::EXITING;
                        break;
                    case 2:
                        currentState = GameState::HOWTOPLAY_MENU;
                    case 3:
                        currentState = GameState::SCORES_MENU;
                        break;
                }
                break;
                
            case GameState::SINGLEPLAYER_MENU:
                switch (singleplayerMenu.Update(deltaTime)) {
                    case -1: 
                        currentState = GameState::SINGLEPLAYER_MENU; 
                        break;
                    case 0: 
                        currentState = GameState::MAZESIZE_MENU; 
                        break;
                    case 1: 
                        game.getCellGrid().GenerateBackTrackingMaze();
                        currentState = GameState::PLAYING; 
                        break;
                    case 2: 
                        currentState = GameState::MAIN_MENU; 
                        break;
                }
                break;

            case GameState::MAZESIZE_MENU:
                switch (singleplayerMenu.Update(deltaTime)) {
                    case -1: 
                        currentState = GameState::MAZESIZE_MENU; 
                        break;
                    case 0:
                        game.setCellGrid(CellGrid({5,5}));
                        currentState = GameState::SINGLEPLAYER_MENU; 
                        break;
                    case 1:
                        game.setCellGrid(CellGrid({10,10}));
                        currentState = GameState::SINGLEPLAYER_MENU; 
                        break;
                    case 2:
                        game.setCellGrid(CellGrid({17,31}));
                        currentState = GameState::SINGLEPLAYER_MENU; 
                        break;
                }
                break;

            case GameState::HOWTOPLAY_MENU:
                if(howtoplayMenu.Update(deltaTime) == 0){
                    currentState = GameState::MAIN_MENU; 
                }
                break;

            case GameState::SCORES_MENU:
                if(scoresMenu.Update(deltaTime) == 0){
                    currentState = GameState::MAIN_MENU; 
                }
                break;

            default:
                break;
        }


        // Draw everything to the low-res render texture
        BeginTextureMode(target);
            ClearBackground(BLACK);

            // Your low-res game drawing goes here:
            // State-based drawing
            switch (currentState)
            {
                case GameState::MAIN_MENU:
                    mainMenu.Draw();
                    break;
                case GameState::PLAYING:
                    game.Draw();
                    break;
                case GameState::MAZESIZE_MENU:
                    mazesizeMenu.Draw();
                    break;
                case GameState::SINGLEPLAYER_MENU:
                    singleplayerMenu.Draw();
                    break;
                case GameState::MULTIPLAYER_MENU:
                    //singleplayerMenu.Draw();
                    break;
                case GameState::HOWTOPLAY_MENU:
                    howtoplayMenu.Draw();
                    DrawText("Movement: Arrow keys, wasd \n Return: R \n Start playing: V", 1, 1, 10, WHITE);
                    break;
                case GameState::SCORES_MENU:
                {
                    scoresMenu.Draw();
                    // Open the file
                    std::ifstream file("scores.txt");

                    // Check if the file opened successfully
                    if (!file.is_open()) {
                        std::cerr << "Error opening file" << std::endl;
                        return 1;
                    }

                    std::string line;

                    // Read file line by line
                    for (int i = 0; std::getline(file, line); i++) {
                        std::string text = std::to_string(i+1) + ".- " + line;
                        DrawText(text.c_str(), 140, 20 + i*10, 10, WHITE);
                    }
    
                    // Close the file
                    file.close();
                    break;
                }

                default:
                    break;
            }
        EndTextureMode();


        // Now draw the scaled texture to the screen
        BeginDrawing();
            ClearBackground(BLACK);

            // Draw the render texture scaled to the full screen
            DrawTexturePro(
                target.texture,
                (Rectangle){ 0, 0, (float)target.texture.width, -(float)target.texture.height },
                (Rectangle){ 0, 0, (float)screenWidth, (float)screenHeight },
                (Vector2){ 0, 0 },
                0.0f,
                WHITE
            );

        EndDrawing();
    }

    UnloadRenderTexture(target);
    CloseWindow();

    return 0;
}
