#pragma once

#include "raylib.h"

#define BLOCK_WIDTH           (3)
#define BLOCK_HEIGHT          (3)

class Block
{
    public:
        Block(Vector2 position);
        void Draw();
        Rectangle GetRect();

    private:
        Vector2 position;
};