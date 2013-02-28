#ifndef COLOR_H
#define COLOR_H

#include <math.h>
#include <string.h>

#include "globals.h"


    /**
     * \brief Reports a shade of color proportional to number.
     *
     * If range1 is less than range2, then the larger the number,
     * the lighter the shade of color.
     * But if range2 is less than range1, the color scaling is inverted.
     *
     * If number is less than range1, then the darkest shade of color
     * is chosen.
     *
     * If number is greater than range2, then the lightest shade of color
     * is chosen.
     */
    int to_rgb(int hue, float saturation, float value);
    
    void scale_color( double carbonValue, double maxVal, double minVal, int x, int y, int stockIndex, int colorIndex);


	/**
     * \brief Updates the color of the patch
     */
    void update_color();

    /**
     * \brief Returns the bigger number
     * \param[in] x The x coordinate
     * \param[in] y The y coordinate
     */
    double getMax(double max, double contender);

    /**
     * \brief Turn a 2D index into a 1D index
     */
    int getIndex(int x, int y);


#endif
