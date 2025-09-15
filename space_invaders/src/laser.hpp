#pragma once

#include "raylib.h"

#define LASER_BEAM_WIDTH             (4)
#define LASER_BEAM_HEIGTH            (15)
#define LASER_BEAM_COLOR             ((Color){243, 216, 63, 255})
#define LASER_BEAM_SPACESHIP_SPEED   (-6)

class Laser
{
    public:
        Laser(Vector2 position, int speed);
        ~Laser();
        void Update();
        void Draw();
        bool active;

    private:
        Vector2 position;
        int speed;
};