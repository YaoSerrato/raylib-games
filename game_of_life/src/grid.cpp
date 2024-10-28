#include <ctime>
#include <raylib.h>
#include "grid.hpp"

void Grid::gridDraw()
{
    Color this_color;

    for(unsigned int this_row = 0 ; this_row < gridRows ; this_row++)
    {
        for(unsigned int this_column = 0 ; this_column < gridColumns ; this_column++)
        {
            this_color = gridCells[this_row][this_column] ? Color{0, 255, 0, 255} : Color{55, 55, 55, 255};
            DrawRectangle( (this_column * gridCellsize) + 1, (this_row * gridCellsize) + 1, gridCellsize - 2, gridCellsize - 2, this_color);
        }
    }
}

void Grid::gridSetValue(unsigned int r, unsigned int c, unsigned int v)
{
    if(IsWithinBounds(r, c))
    {
        gridCells[r][c] = v;
    }
}

int Grid::gridGetValue(unsigned int r, unsigned int c)
{
    if(IsWithinBounds(r, c))
    {
        return gridCells[r][c];
    }

    return 0;
}

void Grid::gridFillRandom()
{
    int random_cell_value;

    for(unsigned int row = 0 ; row < gridRows ; row++)
    {
        for(unsigned int column = 0 ;  column < gridColumns ; column++)
        {
            random_cell_value = GetRandomValue(0, 4);
            gridCells[row][column] = (random_cell_value == 4) ? 1 : 0;
            // random_cell_value = GetRandomValue(0, 1);
            // gridCells[row][column] = random_cell_value;
        }
    }
}

void Grid::gridClear()
{
    for(unsigned int row = 0 ; row < gridRows ; row++)
    {
        for(unsigned int column = 0 ;  column < gridColumns ; column++)
        {
            gridCells[row][column] = 0;
        }
    }
}

void Grid::gridCellToggle(unsigned int r, unsigned int c)
{
    if(IsWithinBounds(r, c))
    {
        gridCells[r][c] =  !gridCells[r][c];
    }
}

bool Grid::IsWithinBounds(unsigned int r, unsigned int c)
{
    return ( (r >= 0 && r < gridRows) && (c >= 0 && c < gridColumns) );
}
