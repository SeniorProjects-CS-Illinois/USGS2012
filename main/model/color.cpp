#include "color.h"
#include <iostream>
using namespace std;

/**
 * Defining non-extern versions of variables in h file
 */

/**
 * Scales the color of the patch
 * @param value The value of the patch
 * @param maxVal the max value for the image
 * @param minVal the min value for the image
 * @param x The x coord of the patch
 * @param y The y coord of the patch
 */
void scale_color(double value, double maxVal, double minVal, int x, int y, int stockIndex) {
    int returnValue = 0xffffff;
    if(maxVal == minVal) {
        returnValue = 0;
        return;
    }

    if(value <= minVal || /*isnan(value)*/ (value != value)) {
        g.value = qRgb(55, 204, 51);
        g.images[stockIndex]->setPixel(x, y, g.value);
    }
    else if(value >= maxVal) {
        g.value = qRgb(0, 0, 0);
        g.images[stockIndex]->setPixel(x, y, g.value);
    }
    else {
        int rangeValues = (int)fabs(maxVal - minVal);
        returnValue = (int)(value * 255 / rangeValues);

        if( minVal > maxVal) {
            returnValue = 255 - returnValue;
        }

        int red =  returnValue & (255 << 16);
        int green = returnValue & (255 << 8);
        int blue = returnValue & 255;
        g.value = qRgb(red, green, blue);
        g.images[stockIndex]->setPixel(x, y, g.value);
    }
}


/**
 * Updates the color of the patch
 */
void update_color() {
    int x = 0;
    int y = 0;

    // calculate all relevant averages
    // TODO: is it safe to only do this calculation once?
    int num_patches = 0;
    double total_phyto = 0;
    double total_waterdecomp = 0;
    double total_POC = 0;
    double total_detritus = 0;
    double total_seddecomp = 0;
    double total_DOC = 0;

    for(x = 0; x < g.MAP_WIDTH; x++)
    {
        for(y=0; y < g.MAP_HEIGHT; y++)
        {
            if(patches[x][y].depth > 0.0)
            {
                total_phyto += patches[x][y].phyto;
                total_waterdecomp += patches[x][y].waterdecomp;
                total_POC += patches[x][y].POC;
                total_detritus += patches[x][y].detritus;
                total_seddecomp += patches[x][y].seddecomp;
                total_DOC += patches[x][y].DOC;
                num_patches++;
            }
        }
    }

    double AVG_phyto = total_phyto/num_patches;
    double AVG_waterdecomp = total_waterdecomp/num_patches;
    double AVG_POC = total_POC/num_patches;
    double AVG_detritus = total_detritus/num_patches;
    double AVG_seddecomp = total_seddecomp/num_patches;
    double AVG_DOC = total_DOC/num_patches;
    // don't do averages for: macro, sedconsumer, herbivore, or consum

    // set color values appropriately
    for(y = 0; y < g.MAP_HEIGHT; y++)
    {
        for(x = 0; x < g.MAP_WIDTH; x++)
        {
            if (patches[x][y].depth == 0.0)
            {
                for(int i = 0; i < g.NUM_STOCKS; i++) {
                    g.value = qRgb(235, 235, 235);
                    g.images[i]->setPixel(x, y, g.value);
                }
            }
            else
            {
                scale_color(patches[x][y].macro, g.MAX_MACRO, 0.0, x, y, g.MACRO_INDEX);
                scale_color(patches[x][y].phyto, AVG_phyto, 0.0, x, y, g.PHYTO_INDEX);
                scale_color(patches[x][y].waterdecomp, AVG_waterdecomp, 0.0, x, y, g.WATERDECOMP_INDEX);
                scale_color(patches[x][y].POC, AVG_POC, 0.0, x, y, g.POC_INDEX);
                scale_color(patches[x][y].detritus, AVG_detritus, 0.0, x, y, g.DETRITUS_INDEX);
                scale_color(patches[x][y].sedconsumer, g.MAX_SEDCONSUMER, 0.0, x, y, g.SEDCONSUMER_INDEX);
                scale_color(patches[x][y].seddecomp, AVG_seddecomp, 0.0, x, y, g.SEDDECOMP_INDEX);
                scale_color(patches[x][y].herbivore, g.MAX_HERBIVORE, 0.0, x, y, g.HERBIVORE_INDEX);
                scale_color(patches[x][y].consum, g.MAX_CONSUM, 0.0, x, y, g.CONSUM_INDEX);
                scale_color(patches[x][y].DOC, AVG_DOC, 0.0, x, y, g.DOC_INDEX);
            }
        }
    }
}

int getIndex(int x, int y) {
    return x + (y * g.MAP_WIDTH);
}
