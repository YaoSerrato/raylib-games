#pragma once // This header file will be included only once in a compilation unit

#include "spaceship.hpp"

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

        Spaceship spaceship;
};
