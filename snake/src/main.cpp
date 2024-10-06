#include <iostream>
#include "main.h"

using namespace std;

double lastUpdateTime = 0;

bool eventTriggered(double interval)
{
    double currentTime = GetTime();

    if(currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}


bool ElementInDeque(Vector2 element, deque<Vector2> dqueue )
{
    for(unsigned int i = 0; i < dqueue.size(); i++)
    {
        if(Vector2Equals(element, dqueue[i]))
        {
            return true;
        }
    }
    return false;
}


class Food
{
public:
    Vector2 position;
    Texture2D texture;

    // constructor: used for initializaing an object when it is created.
    //              automatically called when an instance (object) from the class is created.
    //              used to set the default values of the attributes of the object or to perform
    //              any other setup tasks.
    Food(deque<Vector2> snakeBody)
    {
        // Image image = LoadImage("resources/food.png");
        // texture = LoadTextureFromImage(image);
        // UnloadImage(image);
        position = GenerateRandomPos(snakeBody);
    }

    // destructor:  function when an object is destroyed or goes out of scope.
    //              responsible for releasing any resources the object acquired during its lifetime.
    ~Food()
    {
        // UnloadTexture(texture);
    }

    void Draw()
    {
        DrawRectangle((position.x * CELL_SIZE) + FRAME_OFFSET, (position.y * CELL_SIZE) + FRAME_OFFSET, CELL_SIZE, CELL_SIZE, COLOR_FOOD);
        //DrawTexture(texture, position.x * CELL_SIZE, position.y * CELL_SIZE, WHITE);
    }

    Vector2 GenerateRandomCell()
    {
        SetRandomSeed(time(0));
        float x = GetRandomValue(0, CELL_COUNT - 1);
        float y = GetRandomValue(0, CELL_COUNT - 1);

        return Vector2{x, y};
    }

    Vector2 GenerateRandomPos(deque<Vector2> snakeBody)
    {
        Vector2 position = GenerateRandomCell();

        while(ElementInDeque(position, snakeBody))
        {
            position = GenerateRandomCell();
        }

        return position;
    }
};


class Snake
{
public:
    deque<Vector2> body;
    Vector2 direction;
    bool addSegment;

    Snake()
    {
        body = {Vector2{6,9}, Vector2{5,9}, Vector2{4,9}};   // I was not able do use deque in a separate header file.
        direction = {1,0};
        addSegment = false;
    }

    ~Snake()
    {
    }

    void Draw()
    {
        long long unsigned int i;
        Rectangle this_segment;

        this_segment.width = CELL_SIZE;
        this_segment.height = CELL_SIZE;

        for(i = 0; i < body.size(); i++)
        {
            this_segment.x = (body[i].x * CELL_SIZE) + FRAME_OFFSET;
            this_segment.y = (body[i].y * CELL_SIZE) + FRAME_OFFSET;
            DrawRectangleRounded(this_segment, 0.5f, 6, COLOR_SNAKE);
        }
    }

    void Update()
    {
        body.push_front(Vector2Add(body[0], direction));

        if(addSegment)
        {
            addSegment = false;
        }
        else
        {
            body.pop_back();
        }
    }

    void KeyControl()
    {
        if(IsKeyPressed(KEY_UP) && (direction.y != 1))
        {
            direction = {0, -1};
        }
        else if(IsKeyPressed(KEY_DOWN) && (direction.y != -1))
        {
            direction = {0, 1};
        }
        else if(IsKeyPressed(KEY_RIGHT) && (direction.x != -1))
        {
            direction = {1, 0};
        }
        else if(IsKeyPressed(KEY_LEFT) && (direction.x != 1))
        {
            direction = {-1, 0};
        }
        else
        {
            // no valid movement
        }
    }

    void Reset()
    {
        body = {Vector2{6,9}, Vector2{5,9}, Vector2{4,9}};
        direction = {1,0};
        addSegment = false;
    }
};


class Game
{
public:
    Snake snake = Snake();
    Food food =  Food(snake.body);
    unsigned int score = 0;

    void Draw()
    {
        food.Draw();
        snake.Draw();
    }

    void Update()
    {
        snake.Update();
        CheckCollisionWithFood();
        CheckCollisionWithEdges();
        CheckCollisionWithSnake();
    }

    void CheckCollisionWithFood()
    {
        if(Vector2Equals(snake.body[0], food.position))
        {
            food.position = food.GenerateRandomPos(snake.body);
            snake.addSegment = true;
            score++;
        }
    }

    void CheckCollisionWithEdges()
    {
        if(snake.body[0].x >= CELL_COUNT || snake.body[0].x == -1)
        {
            GameOver();
        }

        if(snake.body[0].y >= CELL_COUNT || snake.body[0].y == -1)
        {
            GameOver();
        }
    }

    void CheckCollisionWithSnake()
    {
        deque<Vector2> headlessBody = snake.body;
        headlessBody.pop_front();

        if(ElementInDeque(snake.body[0], headlessBody))
        {
            GameOver();
        }
    }

    void GameOver()
    {
        snake.Reset();
        food.position = food.GenerateRandomPos(snake.body);
        score = 0;
    }
};


int main()
{
    Game game = Game();

    InitWindow((2 * FRAME_OFFSET) + (CELL_SIZE * CELL_COUNT), (2 * FRAME_OFFSET) + (CELL_SIZE * CELL_COUNT), "Snake Game");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        // update snake position
        if(eventTriggered(0.2))
        {
            game.Update();
        }
        game.snake.KeyControl();

        // drawing
        ClearBackground(COLOR_BACKGROUND);
        DrawRectangleLinesEx(Rectangle{(float)(FRAME_OFFSET - 5), (float)(FRAME_OFFSET - 5), (float)(CELL_SIZE * CELL_COUNT + 10), (float)(CELL_SIZE * CELL_COUNT + 10)}, 5, COLOR_FRAME);
        DrawText("Snake Game", FRAME_OFFSET - 5, 20, 40, COLOR_TEXT);
        DrawText(TextFormat("%i", game.score), CELL_SIZE * CELL_COUNT + FRAME_OFFSET - 25, 20, 40, COLOR_TEXT);

        game.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}