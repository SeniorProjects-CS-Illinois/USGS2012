#include "utility.h"

void Utility::boundLower(double & value, double lowerBound) {
    if(value < lowerBound) {
        value = lowerBound;
    }
}

void Utility::boundUpper(double & value, double upperBound) {
    if (value > upperBound) {
        value = upperBound;
    }
}

void Utility::boundValue(double & value, double lowerBound, double upperBound) {
    if(value < lowerBound) {
        value = lowerBound;
    } else if (value > upperBound) {
        value = upperBound;
    }
}

void Utility::boundPercentage(double & value) {
    boundValue(value, 0.0, 1.0);
}
