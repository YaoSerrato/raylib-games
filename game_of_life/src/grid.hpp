#pragma once
// '#pragma once' instruction ensures that this header file is only included once in a compilation unit, to avoid duplicate definitions.

// https://en.cppreference.com/w/cpp/container/vector
#include <vector>

class Grid
{
    public:
        // cells(rows, std::vector<unsigned int>(columns, 0)) --- which means: 'cells' is a vector initialized to 'rows' number of vectors which
        // are themselves initialized to 'columns' number of unsigned integers initialized to zeros.
        // The constructor body is empty which indicates that all initializations were done in the initializer list.
        Grid(unsigned int _width, unsigned int _height, unsigned int _cellsize)
        : gridRows(_height / _cellsize), gridColumns(_width / _cellsize), gridCellsize(_cellsize), gridCells(gridRows, std::vector<unsigned int>(gridColumns, 0)) {};

        void gridDraw();
        void gridSetValue(unsigned int r, unsigned int c, unsigned int v);
        int gridGetValue(unsigned int r, unsigned int c);
        unsigned int gridGetRows() {return gridRows;}
        unsigned int gridGetColumns() {return gridColumns;}
        void gridFillRandom();
        void gridClear();
        void gridCellToggle(unsigned int r, unsigned int c);

    private:
        unsigned int gridRows;
        unsigned int gridColumns;
        unsigned int gridCellsize;
        std::vector<std::vector<unsigned int>> gridCells;

        bool IsWithinBounds(unsigned int r, unsigned int c);
};