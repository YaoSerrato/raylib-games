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
    int windowWidth = COMMON_WINDOW_WIDTH;
    int windowHeight = COMMON_WINDOW_HEIGHT;

    InitWindow(windowWidth, windowHeight, "Space Invaders");
    SetTargetFPS(COMMON_FPS);

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