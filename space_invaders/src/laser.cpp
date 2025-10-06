#include "laser.hpp"
#include <iostream>

Laser::Laser(Vector2 position, int speed)
{
    // YS NOTE: why are we using here the arrow (->) operator?
    this->position = position;
    this->speed = speed;
    active = true;
}

Laser::~Laser()
{
}

void Laser::Update()
{
    position.y += speed;
    if(active)
    {
        if( (position.y >= (COMMON_PLAY_AREA_BOTTOM - LASER_BEAM_HEIGTH)) || (position.y <= COMMON_PLAY_AREA_TOP) )
        {
            active = false;
        }
    }
}

void Laser::Draw()
{
    if(active)
    {
        DrawRectangle(position.x, position.y, LASER_BEAM_WIDTH, LASER_BEAM_HEIGTH, LASER_BEAM_COLOR);
    }
}

Rectangle Laser::GetRect()
{
    Rectangle rect;
    rect.x = position.x;
    rect.y = position.y;
    rect.width = LASER_BEAM_WIDTH;
    rect.height = LASER_BEAM_HEIGTH;

    return rect;
}
