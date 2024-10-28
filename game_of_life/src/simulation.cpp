#include <vector>
#include <utility>
#include <ctime>
#include <raylib.h>
#include <raymath.h>
#include "simulation.hpp"


void Simulation::simulationDraw()
{
    grid.gridDraw();
}

void Simulation::simulationSetCellValue(unsigned int r, unsigned int c, unsigned int v)
{
    grid.gridSetValue(r, c, v);
}

int Simulation::simulationCountLiveNeighbors(unsigned int r, unsigned int c)
{
    int liveNeighbors = 0;
    int nr;
    int nc;

    std::vector<std::pair<int, int>> neighborOffsets = 
    {
        {-1, 0},
        {1, 0},
        {0, -1},
        {0, 1},
        {-1, -1},
        {-1, 1},
        {1, -1},
        {1, 1}
    };

    for(const auto& offset : neighborOffsets)
    {
        nr = (r + offset.first + grid.gridGetRows()) % grid.gridGetRows();
        nc = (c + offset.second + grid.gridGetColumns()) % grid.gridGetColumns();
        liveNeighbors += grid.gridGetValue(nr, nc);
    }

    return liveNeighbors;
}

void Simulation::simulationUpdate()
{
    int liveNeighbors = 0;
    int cellvalue = 0;

    if(simulationIsRunning())
    {
        for(unsigned int row = 0 ; row < grid.gridGetRows() ; row++)
        {
            for(unsigned int column = 0 ;  column < grid.gridGetColumns() ; column++)
            {
                liveNeighbors = simulationCountLiveNeighbors(row, column);
                cellvalue = grid.gridGetValue(row, column);

                if(cellvalue == 1)
                {
                    if(liveNeighbors > 3 || liveNeighbors < 2)
                    {
                        temp_grid.gridSetValue(row, column, 0);
                    }
                    else
                    {
                        temp_grid.gridSetValue(row, column, 1);
                    }
                }
                else
                {
                    if(liveNeighbors == 3)
                    {
                        temp_grid.gridSetValue(row, column, 1);
                    }
                    else
                    {
                        temp_grid.gridSetValue(row, column, 0);
                    }
                }
            }
        }

        grid = temp_grid;
    }
}

void Simulation::simulationSetInitialStateRandom()
{
    if(!simulationIsRunning())
    {
        grid.gridFillRandom();
    }
    else
    {
    }
}

void Simulation::simulationClearGrid()
{
    if(!simulationIsRunning())
    {
        grid.gridClear();
    }
    else
    {
    }
}

void Simulation::simulationToggleGridCell(unsigned int r, unsigned int c)
{
    if(!simulationIsRunning())
    {
        grid.gridCellToggle(r, c);
    }
    else
    {
    }
}
