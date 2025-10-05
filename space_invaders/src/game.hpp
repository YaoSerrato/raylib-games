#pragma once // This header file will be included only once in a compilation unit

#include "spaceship.hpp"
#include "obstacle.hpp"
#include "alien.hpp"

class Game
{
    public:
        Game(); // Constructor declaration
        ~Game(); // Destructor declaration
        void Draw();
        void Update();
        void HandleInput();

    private:
        void DeleteInactiveLasers();
        void CreateObstacles(unsigned int numberOfObstacles);
        void CreateAliens(unsigned int numberOfAliensPerRow, unsigned int numberOfRows);
        void MoveAliens();
        void MoveAliensVertical(unsigned int distance);
        void AlienShootLaser();

        Spaceship spaceship;
        std::vector<Obstacle> obstacles;
        std::vector<Alien> aliens;
        int aliensDirection;
        std::vector<Laser> aliensLasers;
        double lastFireTimeAlien;
};
