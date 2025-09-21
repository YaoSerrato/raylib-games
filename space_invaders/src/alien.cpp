#include "alien.hpp"

Alien::Alien(alienType type, Vector2 position)
{
    this->type = type;
    this->position = position;

    switch(type)
    {
        case ALIEN_TYPE_1:
            image = LoadTexture("../assets/alien_1.png");
            break;
        case ALIEN_TYPE_2:
            image = LoadTexture("../assets/alien_2.png");
            break;
        case ALIEN_TYPE_3:
            image = LoadTexture("../assets/alien_3.png");
            break;
        default:
            image = LoadTexture("../assets/alien_1.png");
            break;
    }
}

void Alien::Update()
{
}

void Alien::Draw()
{
    DrawTextureV(image, position, WHITE);
}

alienType Alien::GetType()
{
    return type;
}