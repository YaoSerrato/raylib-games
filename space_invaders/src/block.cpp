#include "block.hpp"

#define BLOCK_COLOR_ACTIVE    ((Color){243, 216, 63, 255})

Block::Block(Vector2 position)
{
    this->position = position;
}

void Block::Draw()
{
    DrawRectangle(position.x, position.y, BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_COLOR_ACTIVE);
}
