/* ----------------------------------------------------------------------- */
/* INCLUDES */
/* ----------------------------------------------------------------------- */
#include <raylib.h>
#include "ball.h"
#include "paddle.h"


/* ----------------------------------------------------------------------- */
/* DEFINES */
/* ----------------------------------------------------------------------- */
#define BACKGROUND_COLOR    (BLACK)

#define PADDLE_WIDTH        (25)
#define PADDLE_HEIGHT       (120)
#define PADDLE_COLOR        (WHITE)
#define PADDLE_EDGE_OFFSET  (10)
#define PADDLE_SPEED_PLAYER (6)
#define PADDLE_SPEED_CPU    (8)

#define BALL_RADIUS         (15)
#define BALL_COLOR          (WHITE)
#define BALL_SPEED          (7)

#define LINE_COLOR          (WHITE)

#define SCORE_TEXT_FONTSIZE (80)
#define SCORE_TEXT_COLOR    (WHITE)


/* ----------------------------------------------------------------------- */
/* main */
/* ----------------------------------------------------------------------- */
int main()
{
    const int window_width = 1280;
    const int window_height = 800;
    Color green = Color{38, 185, 154, 255};
    Color dark_green = Color{20, 160, 133, 255};
    Color yellow = Color{243, 213, 91, 255};
    Ball ball;
    Paddle paddle_player;
    CPUPaddle paddle_cpu;

    // draw window
    InitWindow(window_width, window_height, "Pong Game");
    SetTargetFPS(60);

    // init ball object
    ball.x = window_width / 2;
    ball.y = window_height / 2;
    ball.radius = BALL_RADIUS;
    ball.color = yellow;
    ball.speed_x = BALL_SPEED;
    ball.speed_y = BALL_SPEED;
    ball.cpu_score = 0;
    ball.player_score = 0;

    // init paddle player object
    paddle_player.width = PADDLE_WIDTH;
    paddle_player.height = PADDLE_HEIGHT;
    paddle_player.color = PADDLE_COLOR;
    paddle_player.x = window_width - paddle_player.width - PADDLE_EDGE_OFFSET;
    paddle_player.y = (window_height / 2) - (paddle_player.height / 2);
    paddle_player.speed = PADDLE_SPEED_PLAYER;

    // init paddle cpu object
    paddle_cpu.width = PADDLE_WIDTH;
    paddle_cpu.height = PADDLE_HEIGHT;
    paddle_cpu.color = PADDLE_COLOR;
    paddle_cpu.x = PADDLE_EDGE_OFFSET;
    paddle_cpu.y = (window_height / 2) - (paddle_cpu.height / 2);
    paddle_cpu.speed = PADDLE_SPEED_CPU;


    while(!WindowShouldClose())
    {
        BeginDrawing();

        // update positions
        ball.Update();
        paddle_player.Update();
        paddle_cpu.Update(ball.y);

        // check for collisions
        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y},
                                    ball.radius,
                                    Rectangle{paddle_player.x, paddle_player.y, paddle_player.width, paddle_player.height}))
        {
            ball.speed_x *= -1;
        }

        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y},
                                    ball.radius,
                                    Rectangle{paddle_cpu.x, paddle_cpu.y, paddle_cpu.width, paddle_cpu.height}))
        {
            ball.speed_x *= -1;
        }

        // draw elements
        ClearBackground(dark_green);
        DrawRectangle(window_width/2, 0, window_width/2, window_height, green);
        DrawLine(window_width / 2, 0, window_width / 2, window_height, LINE_COLOR);

        ball.Draw();
        paddle_player.Draw();
        paddle_cpu.Draw();
        DrawText(TextFormat("%i", ball.cpu_score), window_width/4 - 20, 20, SCORE_TEXT_FONTSIZE, SCORE_TEXT_COLOR);
        DrawText(TextFormat("%i", ball.player_score), 3 * window_width/4 - 20, 20, SCORE_TEXT_FONTSIZE, SCORE_TEXT_COLOR);

        EndDrawing();
    }

    // close window
    CloseWindow();

    return 0;
}