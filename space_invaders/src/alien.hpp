#pragma once

#include "raylib.h"

#define ALIEN_ARMY_INITIAL_POSITION_Y   100

#define ALIEN_ARMY_LATERAL_LIMIT        5
#define ALIEN_ARMY_ALIEN_CELLSIZE       55

#define ALIEN_ARMY_MAX_ROWS             5
#define ALIEN_ARMY_MAX_PER_ROW          11

typedef enum alienType
{
    ALIEN_TYPE_1 = 0,
    ALIEN_TYPE_2 = 1,
    ALIEN_TYPE_3 = 2,
    ALIEN_TYPE_MAX
} alienType;

class Alien
{
    public:
        Alien(alienType type, Vector2 position);
        void Update();
        void Draw();
        alienType GetType();

        Texture2D image;
        alienType type;
        Vector2 position;

    private:
};