#pragma once

#include "grid.hpp"

class Simulation
{
    public:
        Simulation(unsigned int _width, unsigned int _height, unsigned int _cellsize)
        : grid(_width, _height, _cellsize), temp_grid(_width, _height, _cellsize), run(false) {};
        void simulationDraw();
        void simulationSetCellValue(unsigned int r, unsigned int c, unsigned int v);
        int simulationCountLiveNeighbors(unsigned int r, unsigned int c);
        void simulationUpdate();
        void simulationSetInitialStateRandom();
        bool simulationIsRunning() {return run;}
        void simulationStart() {run = true;}
        void simulationStop() {run = false;}
        void simulationClearGrid();
        void simulationToggleGridCell(unsigned int r, unsigned int c);

    private:
        Grid grid;
        Grid temp_grid;
        bool run;
};