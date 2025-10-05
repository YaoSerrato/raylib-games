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

Rectangle Block::GetRect()
{
    Rectangle rect;
    rect.x = position.x;
    rect.y = position.y;
    rect.width = BLOCK_WIDTH;
    rect.height = BLOCK_HEIGHT;

    return rect;
}
