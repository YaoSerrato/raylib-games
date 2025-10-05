#include "mystery_ship.hpp"

#define MYSTERY_SHIP_POSITION_Y    40
#define MYSTERY_SHIP_SPEED         3

MysteryShip::MysteryShip()
{
    image = LoadTexture("../assets/mystery.png");
    alive = false;
}

MysteryShip::~MysteryShip()
{
    UnloadTexture(image);
}

void MysteryShip::Update()
{
    if (alive)
    {
        position.x += speed;

        if( (position.x > GetScreenWidth() - image.width) || (position.x < 0) )
        {
            alive = false;
        }
    }
}

void MysteryShip::Draw()
{
    if (alive)
    {
        DrawTextureV(image, position, WHITE);
    }
}

void MysteryShip::Spawn()
{
    position.y = MYSTERY_SHIP_POSITION_Y;
    unsigned int side = GetRandomValue(0, 1);

    if(side == 0)
    {
        position.x = 0;
        speed = MYSTERY_SHIP_SPEED;
    }
    else
    {
        position.x = GetScreenWidth() - image.width;
        speed = MYSTERY_SHIP_SPEED * (-1);
    }

    alive = true;
}
