#pragma once

#include <vector>
#include "block.hpp"

class Obstacle
{
    public:
        Obstacle(Vector2 position);
        void Draw();

        Vector2 position;
        std::vector<Block> blocks;
        static std::vector<std::vector<unsigned int>> grid; // 'static' for accessing this attribute without creating an object of this class
                                                            // (needs to be initialized outside the class constructor)

    private:
};