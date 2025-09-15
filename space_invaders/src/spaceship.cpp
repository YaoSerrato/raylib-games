#include "spaceship.hpp"

#define SPACESHIP_SPEED        (7)
#define SPACESHIP_FIRE_RATE    ((double)(0.35))

Spaceship::Spaceship()
{
    image = LoadTexture("../assets/spaceship.png");
    position.x = (GetScreenWidth() - image.width) / 2;
    position.y = GetScreenHeight() - image.height;
    lastFireTime = 0.0;
}

Spaceship::~Spaceship()
{
    UnloadTexture(image);
}

void Spaceship::Draw()
{
    DrawTextureV(image, position, WHITE);
}

void Spaceship::MoveLeft()
{
    position.x -= SPACESHIP_SPEED;
    if(position.x < 0)
    {
        position.x = 0;
    }
}

void Spaceship::MoveRight()
{
    position.x += SPACESHIP_SPEED;
    if(position.x > (GetScreenWidth() - image.width))
    {
        position.x = GetScreenWidth() - image.width;
    }
}

void Spaceship::FireLaser()
{
    if( (GetTime() - lastFireTime) >= SPACESHIP_FIRE_RATE )
    {
        lasers.push_back( Laser((Vector2){position.x + image.width/2 - LASER_BEAM_WIDTH/2, position.y}, LASER_BEAM_SPACESHIP_SPEED) );
        lastFireTime = GetTime();
    }
}
