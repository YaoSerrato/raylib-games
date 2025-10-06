#pragma once // This header file will be included only once in a compilation unit

#include "raylib.h"
#include "laser.hpp"
#include <vector>

class Spaceship
{
    public:
        Spaceship(); // Constructor declaration
        ~Spaceship(); // Destructor declaration

        void Draw();
        void MoveLeft();
        void MoveRight();
        void FireLaser();
        Rectangle GetRect();
        void Reset();

        std::vector<Laser> lasers;

    private:
        Texture2D image;
        Vector2 position;
        double lastFireTime;
};
