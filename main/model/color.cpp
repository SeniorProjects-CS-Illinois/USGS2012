#include "color.h"

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
int to_rgb(int hue, float saturation, float value){

    int red, green, blue;
    float huePrime = hue/60.0;
    float chroma = value * saturation;
    float tempVal = chroma*(1-fabs((int)huePrime%2-1));

    cout << "hi\n";

    switch((int)floor(huePrime)) {
        case 0: red = chroma, green = tempVal, blue = 0; break;
        case 1: red = tempVal, green = chroma, blue = 0; break;
        case 2: red = 0, green = chroma, blue = tempVal; break;
        case 3: red = 0, green = tempVal, blue = chroma; break;
        case 4: red = tempVal, green = 0, blue = chroma; break;
        case 5: red = chroma, green = 0, blue = tempVal; break;
        default: red = 0, green = 0, blue = 0;
    }

    int returnValue = (red + (value-chroma));
    returnValue = (returnValue << 8) + (green + (value-chroma));
    returnValue = (returnValue << 8) + (blue + (value-chroma));

    return returnValue;
}

void scale_color(double value, double maxVal, double minVal, int x, int y, int stockIndex) {
    int rgb;
    float returnValue;
    if(maxVal == minVal) {
        returnValue = 0.0;
        rgb = to_rgb(g.hues[stockIndex], returnValue, 255);
        g.images[stockIndex]->setPixel(x, y, rgb);
        cout << "hi-equal\n";
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

    cout << "hii-scale\n";
    rgb = to_rgb(g.hues[stockIndex], returnValue, 255);
    g.images[stockIndex]->setPixel(x, y, rgb);

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
                cout << "here i am\n";
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
