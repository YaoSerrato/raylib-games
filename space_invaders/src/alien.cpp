#include "alien.hpp"

Texture2D Alien::alienImages[ALIEN_TYPE_MAX] = {0};

Alien::Alien(alienType type, Vector2 position)
{
    this->type = type;
    this->position = position;

    if(alienImages[type].id == 0)
    {
        switch(type)
        {
            case ALIEN_TYPE_1:
                alienImages[ALIEN_TYPE_1] = LoadTexture("../assets/alien_1.png");
                break;
            case ALIEN_TYPE_2:
                alienImages[ALIEN_TYPE_2] = LoadTexture("../assets/alien_2.png");
                break;
            case ALIEN_TYPE_3:
                alienImages[ALIEN_TYPE_3] = LoadTexture("../assets/alien_3.png");
                break;
            default:
                alienImages[ALIEN_TYPE_1] = LoadTexture("../assets/alien_1.png");
                break;
        }
    }
}

void Alien::Update(int direction)
{
    position.x += direction;
}

void Alien::Draw()
{
    DrawTextureV(alienImages[type], position, WHITE);
}

alienType Alien::GetType()
{
    return type;
}

void Alien::UnloadImages()
{
    for(unsigned int i = 0; i < ALIEN_TYPE_MAX; ++i)
    {
        UnloadTexture(alienImages[i]);
    }
}