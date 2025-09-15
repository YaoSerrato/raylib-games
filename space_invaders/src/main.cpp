#include <raylib.h>
#include "game.hpp"


int main()
{
    Color backgroundColor = {29, 29, 27, 255};
    int windowWidth = 750;
    int windowHeight = 750;

    InitWindow(windowWidth, windowHeight, "Space Invaders");
    SetTargetFPS(60);

    Game game;

    while(WindowShouldClose() == false)
    {
        game.HandleInput();
        
        BeginDrawing();
        ClearBackground(backgroundColor);

        game.Draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}