#ifndef GRID_H
#define GRID_H

#include <vector>
#include <cstddef>
/**
 * @brief This class exists to provide easy access to a one dimensional array as if it
 * were a 2-dimensional array.
 */
template <typename T>
class Grid {
    public:
        Grid(){}

        /**
         * @brief Grid copy constructor
         * @param other A grid to copy
         */
        Grid(const Grid<T> & other);

        /**
         * @brief Assignement operator
         * @param rhs Grid to copy
         * @return this Grid object
         */
        Grid<T> & operator=(const Grid<T> & rhs);

        /**
         * @brief Destructor
         */
        ~Grid();

        /**
         * @brief Constructor.  Sets the dimensions of grid.
         * @param[in] xDim the size in the x dimensions
         * @param[in] yDim the size in the y dimensions
         */
        Grid(std::size_t xDim, std::size_t yDim);

        /**
         * @brief Provides access to elements using 2D coordinates.
         * @param[in] x The x coordinate
         * @param[in] y The y coordinate
         */
        T & operator()(std::size_t x, std::size_t y);

        /**
         * @brief Provides access to elements using 2D coordinates.
         * @param[in] x The x coordinate
         * @param[in] y The y coordinate
         */
        const T & operator()(std::size_t x, std::size_t y) const;

        /**
         * @brief Provides access to elements using normal 1D indexing.
         * @param[in] index the index
         */
        T & operator()(std::size_t index);

        /**
         * @brief Provides access to elements using normal 1D indexing.
         * @param[in] index the index
         */
        const T & operator()(std::size_t index) const;

        /**
         * @brief Gets the given value at the given (x,y) position.
         * @param x The x coordinate
         * @param y The y coordinate
         */
        T get(std::size_t x, std::size_t y) const;

        /**
         * @brief Gets the given value at the given index.
         * @param index The index of the array
         */
        T get(std::size_t index) const;

        /**
         * @brief Sets the given value at the given (x,y) position.
         * @param x The x coordinate
         * @param y The y coordinate
         * @param val The value to set
         */
        void set(std::size_t x, std::size_t y, const T & val);

        /**
         * @brief Sets the given value at the given index.
         * @param index The index of the array
         * @param val The value to set
         */
        void set(std::size_t index, const T & val);

        /**
         * @brief Functions to provide direct access to the array.
         */
        T * getArray(void);
        std::size_t getArraySize(void);

        /**
         * @brief Returns the width provided in the constructor.
         */
        std::size_t getWidth(void) const;

        /**
         * @brief Returns the height provided in the constructor.
         */
        std::size_t getHeight(void) const;


    private:
        T * array;
        size_t width;
        size_t height;
        size_t size;

        /**
         * @brief Grid copy helper
         * @param other A grid to copy
         */
        void copy(const Grid<T> & other);

        /**
         * @brief Helper that clears the grid object
         */
        void clear(void);
};

#include "grid.cpp"
#endif
