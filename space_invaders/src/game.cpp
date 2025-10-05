#include "game.hpp"
#include <iostream>

Game::Game()
{
    // Create desired number of obstacles
    CreateObstacles(4);

    // Create aliens
    CreateAliens(11, 5);
    aliensDirection = ALIEN_ARMY_HORIZONTAL_DIRECTION;
    lastFireTimeAlien = 0.0;

    // Initialize mystery ship spawn timer
    lastMysteryShipSpawnTime = 0.0;
    mysteryShipSpawnInterval = GetRandomValue(MYSTERY_SHIP_MIN_SPAWN_INTERVAL, MYSTERY_SHIP_MAX_SPAWN_INTERVAL);
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

    // Draw all alien lasers
    for(auto& single_laser: aliensLasers)
    {
        single_laser.Draw();
    }

    // Draw mystery ship
    mysteryShip.Draw();
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

    // Spawn mystery ship
    mysteryShip.Update();
    if(mysteryShip.alive == false)  // Only spawn a new mystery ship if there is not one already active
    {
        if( (GetTime() - lastMysteryShipSpawnTime) >= mysteryShipSpawnInterval )
        {
            mysteryShip.Spawn();
            lastMysteryShipSpawnTime = GetTime();
            mysteryShipSpawnInterval = GetRandomValue(MYSTERY_SHIP_MIN_SPAWN_INTERVAL, MYSTERY_SHIP_MAX_SPAWN_INTERVAL);
        }
    }

    // Check for collisions
    CheckCollisions();
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

void Game::CheckCollisions()
{
    // Collisions between spaceship lasers and other elements
    for(auto& spaceship_laser: spaceship.lasers)
    {
        // Collisions between spaceship lasers and aliens
        auto it = aliens.begin();
        while (it != aliens.end())
        {
            if(CheckCollisionRecs(spaceship_laser.GetRect(), it->GetRect()))
            {
                // There is a collision between a spaceship laser and an alien
                it = aliens.erase(it); // Remove the alien from the vector
                spaceship_laser.active = false;
                std::cout << "Alien hit!" << std::endl;
            }
            else
            {
                ++it;
            }
        }

        // Collisions between spaceship lasers and obstacles
        for(auto& this_obstacle: obstacles)
        {
            auto it = this_obstacle.blocks.begin();
            while(it != this_obstacle.blocks.end())
            {
                if(CheckCollisionRecs(spaceship_laser.GetRect(), it->GetRect()))
                {
                    // There is a collision between a spaceship laser and an obstacle block
                    it = this_obstacle.blocks.erase(it); // Remove the block from the vector
                    spaceship_laser.active = false;
                    std::cout << "Obstacle damage!" << std::endl;
                }
                else
                {
                    ++it;
                }
            }
        }

        // Collisions between spaceship lasers and mystery ship
        if(CheckCollisionRecs(spaceship_laser.GetRect(), mysteryShip.GetRect()))
        {
            // There is a collision between a spaceship laser and the mystery ship
            mysteryShip.alive = false;
            spaceship_laser.active = false;
            std::cout << "Mystery ship hit!" << std::endl;
        }
    }

    // Collisions between aliens lasers and other elements
    for(auto& alien_laser: aliensLasers)
    {
        // Collisions between alien lasers and the spaceship
        if(CheckCollisionRecs(alien_laser.GetRect(), spaceship.GetRect()))
        {
            // There is a collision between an alien laser and the spaceship
            alien_laser.active = false;
            std::cout << "Spaceship hit!" << std::endl;
        }

        // Collisions between alien lasers and obstacles
        for(auto& this_obstacle: obstacles)
        {
            auto it = this_obstacle.blocks.begin();
            while(it != this_obstacle.blocks.end())
            {
                if(CheckCollisionRecs(alien_laser.GetRect(), it->GetRect()))
                {
                    // There is a collision between an alien laser and an obstacle block
                    it = this_obstacle.blocks.erase(it); // Remove the block from the vector
                    alien_laser.active = false;
                    std::cout << "Obstacle damage!" << std::endl;
                }
                else
                {
                    ++it;
                }
            }
        }
    }

    // Collisions between aliens and other elements
    for(auto& this_alien: aliens)
    {
        // Collision between aliens and the spaceship
        if(CheckCollisionRecs(this_alien.GetRect(), spaceship.GetRect()))
        {
            // There is a collision between an alien and the spaceship
            std::cout << "Spaceship hit by alien!" << std::endl;
        }

        // Collisions between aliens and obstacles
        for(auto& this_obstacle: obstacles)
        {
            auto it = this_obstacle.blocks.begin();
            while(it != this_obstacle.blocks.end())
            {
                if(CheckCollisionRecs(this_alien.GetRect(), it->GetRect()))
                {
                    // There is a collision between an alien and an obstacle block
                    it = this_obstacle.blocks.erase(it); // Remove the block from the vector
                    std::cout << "Obstacle damage by alien!" << std::endl;
                }
                else
                {
                    ++it;
                }
            }
        }
    }
}
