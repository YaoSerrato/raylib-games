#include <raylib.h>

int main()
{
    signed int ball_x = 400;
    signed int ball_y = 400;
    Color green = {20, 160, 133, 255};

    InitWindow(800, 800, "Keyboard-controlled ball!");
    SetTargetFPS(60);

    while(WindowShouldClose() == false)
    {
        /* Event handling */
        if(IsKeyDown(KEY_RIGHT))
        {
            ball_x += 3;
        }
        else if(IsKeyDown(KEY_LEFT))
        {
            ball_x -= 3;
        }
        else if(IsKeyDown(KEY_UP))
        {
            ball_y -= 3;
        }
        else if(IsKeyDown(KEY_DOWN))
        {
            ball_y += 3;
        }
        else
        {
        }

        /* Drawing objects */
        BeginDrawing();
        
        ClearBackground(green);
        DrawCircle(ball_x, ball_y, 15, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}