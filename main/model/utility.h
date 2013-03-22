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
}

#endif // UTILITY_H
