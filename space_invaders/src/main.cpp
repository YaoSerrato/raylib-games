#include <raylib.h>
#include "game.hpp"


int main()
{
    Color backgroundColor = {
                                .r = 29,
                                .g = 29,
                                .b = 27,
                                .a = 255
                            };
    int windowWidth = 750;
    int windowHeight = 750;

    InitWindow(windowWidth, windowHeight, "Space Invaders");
    SetTargetFPS(60);

    Game game;

    while(WindowShouldClose() == false)
    {
        game.HandleInput();
        game.Update();

        BeginDrawing();
        ClearBackground(backgroundColor);

        game.Draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}