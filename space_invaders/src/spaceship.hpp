#pragma once // This header file will be included only once in a compilation unit

#include "raylib.h"

class Spaceship
{
    public:
        Spaceship(); // Constructor declaration
        ~Spaceship(); // Destructor declaration

        void Draw();
        void MoveLeft();
        void MoveRight();
        void FireLaser();

    private:
        Texture2D image;
        Vector2 position;
};
