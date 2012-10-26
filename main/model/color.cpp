#include "color.h"

/**
 * Scales the color of the patch
 * @param value The value of the patch
 * @param maxVal the max value for the image
 * @param minVal the min value for the image
 * @param x The x coord of the patch
 * @param y The y coord of the patch
*/
void scale_color(double value, double maxVal, double minVal, int x, int y, int stockIndex) {
    float returnValue;
    if(maxVal == minVal) {
        returnValue = 0.0;
        colorValues[stockIndex][getIndex(x, y)] = returnValue;
        return;
    }

    if(value <= minVal || /*isnan(value)*/ (value != value)) {
        returnValue = 0.0;
    }
    else if(value >= maxVal) {
        returnValue = 1.0;
    }
    else {
        float rangeValues = (float)fabs(maxVal - minVal);
        returnValue = (float)(value / rangeValues);
    }
    colorValues[stockIndex][getIndex(x, y)] = returnValue;
}


/**
 * Updates the color of the patch
*/
void update_color() {
    int x = 0;
    int y = 0;

    // set hue values for each stock (magic numbers?)
    hues[MACRO_INDEX] = (float)(120.0 / 360.0);
    hues[PHYTO_INDEX] = (float)(120.0 / 360.0);
    hues[WATERDECOMP_INDEX] = (float)(120.0 / 360.0);
    hues[POC_INDEX] = (float)(240.0 / 360.0);
    hues[DETRITUS_INDEX] = (float)(19.6 / 360.0);
    hues[SEDCONSUMER_INDEX] = (float)(60.0 / 360.0);
    hues[SEDDECOMP_INDEX] = (float)(240.0 / 360.0);
    hues[HERBIVORE_INDEX] = (float)(300.0 / 360.0);
    hues[CONSUM_INDEX] = (float)(300.0 / 360.0);
    hues[DOC_INDEX] = (float)(60.0 / 360.0);

    // calculate all relevant averages
    // TODO: is it safe to only do this calculation once?
    int num_patches = 0;
    double total_phyto = 0;
    double total_waterdecomp = 0;
    double total_POC = 0;
    double total_detritus = 0;
    double total_seddecomp = 0;
    double total_DOC = 0;

    for(x = 0; x < MAP_WIDTH; x++)
    {
        for(y=0; y < MAP_HEIGHT; y++)
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
    for(y = 0; y < MAP_HEIGHT; y++)
    {
        for(x = 0; x < MAP_WIDTH; x++)
        {
            if (patches[x][y].depth == 0.0)
            {
                colorValues[MACRO_INDEX][getIndex(x, y)] = -1;
                colorValues[PHYTO_INDEX][getIndex(x, y)] = -1;
                colorValues[WATERDECOMP_INDEX][getIndex(x, y)] = -1;
                colorValues[POC_INDEX][getIndex(x, y)] = -1;
                colorValues[DETRITUS_INDEX][getIndex(x, y)] = -1;
                colorValues[SEDCONSUMER_INDEX][getIndex(x, y)] = -1;
                colorValues[SEDDECOMP_INDEX][getIndex(x, y)] = -1;
                colorValues[HERBIVORE_INDEX][getIndex(x, y)] = -1;
                colorValues[CONSUM_INDEX][getIndex(x, y)] = -1;
                colorValues[DOC_INDEX][getIndex(x, y)] = -1;
            }
            else
            {
                scale_color(patches[x][y].macro, MAX_MACRO, 0.0, x, y, MACRO_INDEX);
                scale_color(patches[x][y].phyto, AVG_phyto, 0.0, x, y, PHYTO_INDEX);
                scale_color(patches[x][y].waterdecomp, AVG_waterdecomp, 0.0, x, y, WATERDECOMP_INDEX);
                scale_color(patches[x][y].POC, AVG_POC, 0.0, x, y, POC_INDEX);
                scale_color(patches[x][y].detritus, AVG_detritus, 0.0, x, y, DETRITUS_INDEX);
                scale_color(patches[x][y].sedconsumer, MAX_SEDCONSUMER, 0.0, x, y, SEDCONSUMER_INDEX);
                scale_color(patches[x][y].seddecomp, AVG_seddecomp, 0.0, x, y, SEDDECOMP_INDEX);
                scale_color(patches[x][y].herbivore, MAX_HERBIVORE, 0.0, x, y, HERBIVORE_INDEX);
                scale_color(patches[x][y].consum, MAX_CONSUM, 0.0, x, y, CONSUM_INDEX);
                scale_color(patches[x][y].DOC, AVG_DOC, 0.0, x, y, DOC_INDEX);
            }
        }
    }
}
