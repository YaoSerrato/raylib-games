#include "game.hpp"
#include <iostream>

Game::Game()
{
    // Create desired number of obstacles
    CreateObstacles(4);
    CreateAliens(5, 2);
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
    //std::cout << "Number of active lasers: " << spaceship.lasers.size() << std::endl;
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