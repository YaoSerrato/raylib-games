#pragma once // This header file will be included only once in a compilation unit

#include "common.hpp"
#include "spaceship.hpp"
#include "obstacle.hpp"
#include "alien.hpp"
#include "mystery_ship.hpp"

typedef enum
{
    GAME_IDLE,
    GAME_LOST,
    GAME_WON
} gameOverType;

typedef struct
{
    bool run;
    gameOverType status;
} gameStatus;


class Game
{
    public:
        Game(); // Constructor declaration
        ~Game(); // Destructor declaration
        void Draw();
        void Update();
        void HandleInput();

        gameStatus currentStatus;

    private:
        void DeleteInactiveLasers();
        void CreateObstacles(unsigned int numberOfObstacles);
        void CreateAliens(unsigned int numberOfAliensPerRow, unsigned int numberOfRows);
        void MoveAliens();
        void MoveAliensVertical(unsigned int distance);
        void AlienShootLaser();
        void CheckCollisions();
        void DrawScore();
        void GameOver(gameOverType type);
        void Reset();
        void InitGame();
        void DrawGameOverMessage();
        void CheckGameWon();

        Spaceship spaceship;
        std::vector<Obstacle> obstacles;
        std::vector<Alien> aliens;
        int aliensDirection;
        std::vector<Laser> aliensLasers;
        double lastFireTimeAlien;
        MysteryShip mysteryShip;
        double lastMysteryShipSpawnTime;
        double mysteryShipSpawnInterval;
        int liveCounter;
        unsigned int score;
        double lastGameOverMessageTime;
        double intervalGameOverMessage;
        bool toogleGameOverMessage;
};
