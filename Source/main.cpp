#include "raylib.h"
#include "Game.hpp"
#include "Constants.hpp"

#include <math.h>
#include <time.h>




int main()
{

    InitWindow(screenWidth, screenHeight, "Magic_Maze");

    SetRandomSeed(time(NULL));

    Game game = Game();

    // Create a render texture at the game's internal resolution
    RenderTexture2D target = LoadRenderTexture(gameWidth, gameHeight);

    while (!WindowShouldClose())
    {
        //Framerate
        float deltaTime = GetFrameTime();

        //Updating
        game.Update(deltaTime);


        // Draw everything to the low-res render texture
        BeginTextureMode(target);
            ClearBackground(BLACK);

            // Your low-res game drawing goes here:
            game.Draw();
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
