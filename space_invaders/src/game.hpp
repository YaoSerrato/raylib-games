#pragma once // This header file will be included only once in a compilation unit

#include "spaceship.hpp"
#include "obstacle.hpp"

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

        Spaceship spaceship;
        std::vector<Obstacle> obstacles;
};
