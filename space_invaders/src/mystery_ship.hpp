#pragma once

#include <raylib.h>

#define MYSTERY_SHIP_MIN_SPAWN_INTERVAL    10
#define MYSTERY_SHIP_MAX_SPAWN_INTERVAL    20

class MysteryShip
{
    public:
        MysteryShip();
        ~MysteryShip();
        void Update();
        void Draw();
        void Spawn();
        Rectangle GetRect();
        bool alive;

    private:
        Vector2 position;
        Texture2D image;
        int speed;
};