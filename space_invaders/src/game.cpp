#include "game.hpp"
#include <iostream>

Game::Game()
{
    // Create desired number of obstacles
    CreateObstacles(4);
    CreateAliens(2, 5);

    aliensDirection = ALIEN_ARMY_HORIZONTAL_DIRECTION;
    lastFireTimeAlien = 0.0;
}

Game::~Game()
{
    Alien::UnloadImages();
}

void Game::Draw()
{
    // Draw the spaceship
    spaceship.Draw();

    // Draw all active lasers (this is a range based for loop in C++)
    for(auto& single_laser: spaceship.lasers)
    {
        single_laser.Draw();
    }

    // Draw all obstacles
    for(auto& single_obstacle: obstacles)
    {
        single_obstacle.Draw();
    }

    // Draw all aliens
    for(auto& single_alien: aliens)
    {
        single_alien.Draw();
    }

    //Draw all alien lasers
    for(auto& single_laser: aliensLasers)
    {
        single_laser.Draw();
    }
}

void Game::Update()
{
    // Update position of all active lasers
    for(auto& single_laser: spaceship.lasers)
    {
        single_laser.Update();
    }

    // Removing all inactive lasers from the vector
    DeleteInactiveLasers();

    // Update position of all aliens
    MoveAliens();

    // Manage alien lasers
    AlienShootLaser();
    for(auto& single_laser: aliensLasers)
    {
        single_laser.Update();
    }
}

void Game::HandleInput()
{
    if(IsKeyDown(KEY_LEFT))
    {
        spaceship.MoveLeft();
    }
    else if(IsKeyDown(KEY_RIGHT))
    {
        spaceship.MoveRight();
    }
    else if(IsKeyDown(KEY_SPACE))
    {
        spaceship.FireLaser();
    }
}

void Game::DeleteInactiveLasers()
{
    // Removing the laser from the vector actually kills the object (we do not need to kill them manually)
    // Making use of iterators in C++
    for(auto it = spaceship.lasers.begin(); it != spaceship.lasers.end(); )
    {
        if(!(it->active))
        {
            it = spaceship.lasers.erase(it);
        }
        else
        {
            ++it;
        }
    }

    for(auto it = aliensLasers.begin(); it != aliensLasers.end(); )
    {
        if(!(it->active))
        {
            it = aliensLasers.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void Game::CreateObstacles(unsigned int numberOfObstacles)
{
    // YS NOTE: add support for edge cases, for example, to limit the number of obstacles one can create
    // depending on the screen width and the obstacle width

    unsigned int obstacleWidth = Obstacle::grid[0].size() * BLOCK_WIDTH;
    //unsigned int obstacleWidth = 23 * BLOCK_WIDTH;
    unsigned int obstacleGap = (GetScreenWidth() - (numberOfObstacles * obstacleWidth))/(numberOfObstacles + 1);

    for(unsigned int i = 0; i < numberOfObstacles; ++i)
    {
        float offset_x = (obstacleGap * (i + 1)) + (obstacleWidth * (i));
        obstacles.push_back( Obstacle((Vector2){offset_x, (float)(GetScreenHeight() - 100)}) );
    }
}

void Game::CreateAliens(unsigned int numberOfAliensPerRow, unsigned int numberOfRows)
{
    if( (numberOfRows <= 0) || (numberOfRows > ALIEN_ARMY_MAX_ROWS) )
    {
        numberOfRows = ALIEN_ARMY_MAX_ROWS;
    }

    if( (numberOfAliensPerRow <= 0) || (numberOfAliensPerRow > ALIEN_ARMY_MAX_PER_ROW) )
    {
        numberOfAliensPerRow = ALIEN_ARMY_MAX_PER_ROW;
    }

    unsigned int this_type = 0;
    unsigned int initial_x = (GetScreenWidth() - (numberOfAliensPerRow * ALIEN_ARMY_ALIEN_CELLSIZE)) / 2;

    for(unsigned int row = 0; row < numberOfRows; ++row)
    {
        if(this_type >= ALIEN_TYPE_MAX)
        {
            this_type = ALIEN_TYPE_1;
        }

        for(unsigned int col = 0; col < numberOfAliensPerRow; ++col)
        {
            float x = initial_x + col * ALIEN_ARMY_ALIEN_CELLSIZE;
            float y = ALIEN_ARMY_INITIAL_POSITION_Y + row * ALIEN_ARMY_ALIEN_CELLSIZE;
            aliens.push_back( Alien( (alienType)this_type, (Vector2){x, y} ) );
        }

        this_type++;
    }
}

void Game::MoveAliens()
{
    // Update position of all aliens
    for(auto& single_alien: aliens)
    {
        single_alien.Update(aliensDirection);
    }

    // Check if any alien has reached the edge of the screen
    unsigned int left_limit = ALIEN_ARMY_LATERAL_OFFSET;
    unsigned int right_limit = GetScreenWidth() - ALIEN_ARMY_LATERAL_OFFSET;
    bool change_direction = false;

    for(auto& single_alien: aliens)
    {
        if( (single_alien.position.x <= left_limit) || (single_alien.position.x >= right_limit - ALIEN_ARMY_ALIEN_CELLSIZE) )
        {
            change_direction = true;
            break;
        }
    }

    if (change_direction)
    {
        aliensDirection *= -1; // Reverse direction

        // Move all aliens down by a certain amount
        MoveAliensVertical(ALIEN_ARMY_VERTICAL_DIRECTION);

        change_direction = false;
    }
    
}

void Game::MoveAliensVertical(unsigned int distance)
{
    for(auto& single_alien: aliens)
    {
        single_alien.position.y += distance;
    }
}

void Game::AlienShootLaser()
{
    if( ((GetTime() - lastFireTimeAlien) >= ALIEN_ARMY_FIRE_RATE) && (!aliens.empty()) )
    {
        unsigned int random_alien_index = GetRandomValue(0, aliens.size() - 1);
        Alien& shooting_alien = aliens[random_alien_index];

        aliensLasers.push_back(Laser( (Vector2){shooting_alien.position.x + shooting_alien.alienImages[shooting_alien.type].width/2,
                                                shooting_alien.position.y + shooting_alien.alienImages[shooting_alien.type].height},
                                                LASER_BEAM_ALIEN_SPEED));
        lastFireTimeAlien = GetTime();
    }
}
