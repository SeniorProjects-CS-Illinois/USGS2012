#ifndef UTILITY_H
#define UTILITY_H

namespace Utility {
    void boundLower(double & value, double lowerBound);
    void boundUpper(double & value, double upperBound);
    void boundValue(double & value, double lowerBound, double upperBound);
    void boundPercentage(double & value);
}

#endif // UTILITY_H
