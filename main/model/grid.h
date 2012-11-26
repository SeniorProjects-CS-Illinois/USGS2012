#ifndef GRID_H
#define GRID_H

#include <vector>
#include <cstddef>
/**
 * This class exists to provide easy access to a one dimensional array as if it
 * were a 2-dimensional array.
 */
template <typename T>
class Grid {
    public:
        /**
         * Constructor.  Sets the dimensions of grid.
         */
        Grid(std::size_t xDim, std::size_t yDim);

        /**
         * Provides access to elements using 2D coordinates.
         */
        T & operator()(std::size_t x, std::size_t y);
        T const & operator()(std::size_t x, std::size_t y) const;

        /**
         * Provides access to elements using normal 1D indexing.
         */
        T & operator()(std::size_t index);
        T const & operator()(std::size_t index) const;

        /**
         * Functions to provide direct access to the array.  (For openCL stuff)
         */
        T * getArray(void);
        std::size_t getArraySize(void);

        /**
         * Returns the dimensions provided in the constructor.  Useful for loops.
         */
        std::size_t getXDim(void);
        std::size_t getYDim(void);


    private:
        std::vector<T> array;
        size_t numCol;
        size_t numRow;
};

#include "grid.cpp"
#endif
