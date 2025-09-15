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
        if( (position.y > GetScreenHeight()) || (position.y < 0) )
        {
            active = false;
            std::cout << "Laser deactivated" << std::endl;
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
