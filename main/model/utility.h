#ifndef UTILITY_H
#define UTILITY_H

namespace Utility {
    /**
     * @brief Adjusts the value so that it is no lower than the lower bound
     * @param value The value to adjust
     * @param lowerBound The lower bound
     */
    void boundLower(double & value, double lowerBound);

    /**
     * @brief Adjusts the value so that it is no higher than the upper bound
     * @param value The value to adjust
     * @param upperBound The upper bound
     */
    void boundUpper(double & value, double upperBound);

    /**
     * @brief Adjust the value so that it is between the lower and upper bounds.
     * @param value The value to adjust
     * @param lowerBound The lower bound
     * @param upperBound The upper bound
     */
    void boundValue(double & value, double lowerBound, double upperBound);

    /**
     * @brief Adjusts the value so that it is between 0.0 and 1.0
     * @param value The percentage to adjust
     */
    void boundPercentage(double & value);

    /**
     * @brief Initializes an array to the provided size and default values
     * @param array Pointer to initialize
     * @param size Size of resulting array
     * @param initialValue Value to fill in the array
     */
    template <typename T>
    void initArray(T * & array, int size, T initialValue);

    /**
     * @brief Copies the provided array up to the provided number of elements
     * @param other The array to copy
     * @param size The number of elements to copy
     * @return A pointer to the resulting array
     */
    template <typename T>
    T * copyArray(T * other, int size);

}

#include "utility_templates.cpp"

#endif // UTILITY_H
