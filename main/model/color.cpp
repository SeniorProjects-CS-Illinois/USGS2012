#include "color.h"
#include <QColor>

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
void scale_color(double carbonValue, double maxVal, double minVal, int x, int y, int stockIndex) {

    float saturation;

    if(carbonValue > maxVal) {
        carbonValue = maxVal;
    }
    else if(carbonValue < minVal) {
        carbonValue = minVal;
    }

    saturation = (carbonValue-minVal)/(maxVal-minVal)*255;

    //Checking for NaN
    //TODO: what is making NaN values?
    if(saturation != saturation) {
        g.images[stockIndex]->setPixel(x, y, QColor::fromHsv(g.hues[stockIndex], 0, 255).rgb());
    }
    else {
        g.images[stockIndex]->setPixel(x, y, QColor::fromHsv(g.hues[stockIndex], saturation, 255).rgb());
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
                double MAX = 0.0;
                MAX = getMax(MAX, getMax(g.MAX_MACRO, getMax(AVG_phyto, getMax(AVG_waterdecomp, getMax(AVG_POC,
                                        getMax(AVG_detritus, getMax(g.MAX_SEDCONSUMER, getMax(AVG_seddecomp,
                                        getMax(g.MAX_HERBIVORE, getMax(g.MAX_CONSUM, AVG_DOC))))))))));

                double carbon = patches[x][y].macro + patches[x][y].phyto + patches[x][y].waterdecomp + patches[x][y].POC
                    + patches[x][y].detritus + patches[x][y].sedconsumer + patches[x][y].herbivore
                    + patches[x][y].consum + patches[x][y].DOC + patches[x][y].seddecomp;

                scale_color(patches[x][y].macro, g.MAX_MACRO, 0.0, x, y, g.MACRO_INDEX);
                g.sum_macro += patches[x][y].macro;

                scale_color(patches[x][y].phyto, AVG_phyto, 0.0, x, y, g.PHYTO_INDEX);
                g.sum_phyto += patches[x][y].phyto;

                scale_color(patches[x][y].herbivore, g.MAX_HERBIVORE, 0.0, x, y, g.HERBIVORE_INDEX);
                g.sum_herbivore += patches[x][y].herbivore;

                scale_color(patches[x][y].waterdecomp, AVG_waterdecomp, 0.0, x, y, g.WATERDECOMP_INDEX);
                g.sum_waterdecomp += patches[x][y].waterdecomp;

                scale_color(patches[x][y].seddecomp, AVG_seddecomp, 0.0, x, y, g.SEDDECOMP_INDEX);
                g.sum_seddecomp += patches[x][y].seddecomp;

                scale_color(patches[x][y].sedconsumer, g.MAX_SEDCONSUMER, 0.0, x, y, g.SEDCONSUMER_INDEX);
                g.sum_sedconsum += patches[x][y].sedconsumer;

                scale_color(patches[x][y].consum, g.MAX_CONSUM, 0.0, x, y, g.CONSUM_INDEX);
                g.sum_consum += patches[x][y].consum;

                scale_color(patches[x][y].DOC, AVG_DOC, 0.0, x, y, g.DOC_INDEX);
                g.sum_DOC += patches[x][y].DOC;

                scale_color(patches[x][y].POC, AVG_POC, 0.0, x, y, g.POC_INDEX);
                g.sum_POC += patches[x][y].POC;

                scale_color(patches[x][y].detritus, AVG_detritus, 0.0, x, y, g.DETRITUS_INDEX);
                g.sum_detritus += patches[x][y].detritus;

                scale_color(carbon, MAX, 0.0, x, y, g.CARBON_INDEX);
                g.sum_carbon += carbon;

                g.num_water_squares += 1;
            }
        }
    }
}

double getMax(double max, double contender) {
    if(contender > max){
        return contender;
    }
    else {
        return max;
    }
}

int getIndex(int x, int y) {
    return x + (y * g.MAP_WIDTH);
}
