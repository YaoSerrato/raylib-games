#include "game.hpp"
#include <iostream>

#define GAME_LIVE_PROGRESSBAR_WIDTH       (300)
#define GAME_LIVE_PROGRESSBAR_HEIGHT      (20)
#define GAME_LIVE_PROGRESSBAR_OFFSET      (20)
#define GAME_LIVE_PROGRESSBAR_SENSITIVITY (9)

#define GAME_FOREGROUND_COLOR             ( (Color){243, 216, 63, 255} ) // Yellow
#define GAME_BACKGROUND_COLOR             ( (Color){70, 70, 70, 255} ) // Dark gray
#define GAME_TEXT_FONT_SIZE               (25)

#define GAME_SCORE_ALIEN_HIT              (10)
#define GAME_SCORE_MYSTERYSHIP_HIT        (50)

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

    // Initialize live counter and score
    liveCounter = GAME_LIVE_PROGRESSBAR_WIDTH;
    score = 0;
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

    // Draw score
    DrawScore();
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
        obstacles.push_back( Obstacle((Vector2){offset_x, (float)(COMMON_PLAY_AREA_OBSTACLES)}) );
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
                score += GAME_SCORE_ALIEN_HIT;
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
            score += GAME_SCORE_MYSTERYSHIP_HIT;
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
            if(liveCounter > 0)
            {
                liveCounter -= GAME_LIVE_PROGRESSBAR_SENSITIVITY;
                if(liveCounter < 0)
                {
                    liveCounter = 0;
                    GameOver();
                }
            }
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
            GameOver();
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

void Game::DrawScore()
{
    // Draw play area boundary lines
    DrawLine(5, COMMON_PLAY_AREA_TOP, GetScreenWidth() - 5, COMMON_PLAY_AREA_TOP, GAME_FOREGROUND_COLOR);
    DrawLine(5, COMMON_PLAY_AREA_BOTTOM, GetScreenWidth() - 5, COMMON_PLAY_AREA_BOTTOM, GAME_FOREGROUND_COLOR);

    // Draw live progress bar
    DrawRectangle(GAME_LIVE_PROGRESSBAR_OFFSET,
                  COMMON_WINDOW_HEIGHT - GAME_LIVE_PROGRESSBAR_OFFSET - GAME_LIVE_PROGRESSBAR_HEIGHT,
                  GAME_LIVE_PROGRESSBAR_WIDTH,
                  GAME_LIVE_PROGRESSBAR_HEIGHT,
                  GAME_BACKGROUND_COLOR);
    
    DrawRectangle(GAME_LIVE_PROGRESSBAR_OFFSET,
                  COMMON_WINDOW_HEIGHT - GAME_LIVE_PROGRESSBAR_OFFSET - GAME_LIVE_PROGRESSBAR_HEIGHT,
                  liveCounter,
                  GAME_LIVE_PROGRESSBAR_HEIGHT,
                  GAME_FOREGROUND_COLOR);

    float percent = ((float)liveCounter / (float)GAME_LIVE_PROGRESSBAR_WIDTH) * 100.0f;
    DrawText( TextFormat("%.0f%%", percent),
              2*GAME_LIVE_PROGRESSBAR_OFFSET + GAME_LIVE_PROGRESSBAR_WIDTH,
              COMMON_WINDOW_HEIGHT - GAME_LIVE_PROGRESSBAR_OFFSET - GAME_LIVE_PROGRESSBAR_HEIGHT,
              GAME_TEXT_FONT_SIZE,
              GAME_FOREGROUND_COLOR);
    
    // Draw current score
    DrawText( TextFormat("SCORE: %d", score),
              GAME_LIVE_PROGRESSBAR_OFFSET,
              COMMON_PLAY_AREA_TOP - 2*GAME_LIVE_PROGRESSBAR_OFFSET,
              GAME_TEXT_FONT_SIZE,
              GAME_FOREGROUND_COLOR);
}

void Game::GameOver()
{
}