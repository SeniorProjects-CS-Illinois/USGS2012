#include "color.h"
#include <math.h>


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
        colorValues[stockIndex][x][y] = returnValue;
        return;
    }

    if(value <= minVal || isnan(value)) {
        returnValue = 0.0;
    }
    else if(value >= maxVal) {
        returnValue = 1.0;
    }
    else {
        float rangeValues = fabs(maxVal - minVal);
        returnValue = (value / rangeValues);
    }
    colorValues[stockIndex][x][y] = returnValue;
}


/**
 * Updates the color of the patch
*/
void update_color() {
    int x = 0;
    int y = 0;

    int num_patches = 0;

    //if(strcmp(which_stock, "macro") == 0) {
        hues[MACRO_INDEX] = 120.0 / 360.0;
        for(y = 0; y < MAP_HEIGHT; y++) {
            for(x = 0; x < MAP_WIDTH; x++) {
                if (patches[x][y].depth == 0.0) {
                    colorValues[MACRO_INDEX][x][y] = -1;
                }
                else {
                  scale_color(patches[x][y].macro, MAX_MACRO, 0.0, x, y, MACRO_INDEX);
                }
            }
        }
    //}

    //else if(strcmp(which_stock, "phyto") == 0) {
        hues[PHYTO_INDEX] = 120.0 / 360.0;
        double total_phyto = 0;
        num_patches = 0;
        
        for(y=0; y < MAP_HEIGHT; y++) {
            for(x = 0; x < MAP_WIDTH; x++) {
                if(patches[x][y].depth > 0.0) {
                    total_phyto +=patches[x][y].phyto;
                    num_patches++;
                }
            }
        }
        double AVG_phyto = total_phyto/num_patches;

        for(y = 0; y < MAP_HEIGHT; y++) {
            for(x = 0; x < MAP_WIDTH; x++) {
                if (patches[x][y].depth == 0.0) {
                    colorValues[PHYTO_INDEX][x][y] = -1;
                }
                else {
                  scale_color(patches[x][y].phyto, AVG_phyto, 0.0, x, y, PHYTO_INDEX);
                }
            }
        }
    //}

    //else if(strcmp(which_stock, "waterdecomp") == 0) {
        hues[WATERDECOMP_INDEX] = 120.0 / 360.0;
        double total_waterdecomp = 0;
        num_patches = 0;
        
        for(y=0; y < MAP_HEIGHT; y++) {
          for(x = 0; x < MAP_WIDTH; x++) {
            if(patches[x][y].depth > 0.0) {
              total_waterdecomp +=patches[x][y].waterdecomp;
              num_patches++;
            }
          }
        }
        double AVG_waterdecomp = total_waterdecomp/num_patches;
        for(y = 0; y < MAP_HEIGHT; y++) {
            for(x = 0; x < MAP_WIDTH; x++) {
                if (patches[x][y].depth == 0.0) {
                    colorValues[WATERDECOMP_INDEX][x][y] = -1;
                }
                else {
                    scale_color(patches[x][y].waterdecomp, AVG_waterdecomp, 0.0, x, y, WATERDECOMP_INDEX);
                }
            }
        }
    //}

    //else if(strcmp(which_stock, "POC") == 0) {
        hues[POC_INDEX] = 240.0 / 360.0;
        double total_POC = 0;
        num_patches = 0;
        
        for(y=0; y < MAP_HEIGHT; y++) {
          for(x = 0; x < MAP_WIDTH; x++) {
            if(patches[x][y].depth > 0.0) {
              total_POC +=patches[x][y].POC;
              num_patches++;
            }
          }
        }
        double AVG_POC = total_POC/num_patches;
        for(y = 0; y < MAP_HEIGHT; y++) {
            for(x = 0; x < MAP_WIDTH; x++) {
                if (patches[x][y].depth == 0.0) {
                    colorValues[POC_INDEX][x][y] = -1;
                }
                else {
                    scale_color(patches[x][y].POC, AVG_POC, 0.0, x, y, POC_INDEX);
                }
            }
        }
    //}
    
    //else if(strcmp(which_stock, "detritus") == 0) {
        hues[DETRITUS_INDEX] = 19.6 / 360.0;
        double total_detritus = 0;
        num_patches = 0;
        
        for(y=0; y < MAP_HEIGHT; y++) {
          for(x = 0; x < MAP_WIDTH; x++) {
            if(patches[x][y].depth > 0.0) {
              total_detritus +=patches[x][y].detritus;
              num_patches++;
            }
          }
        }
          double AVG_detritus = total_detritus/num_patches;
          for(y = 0; y < MAP_HEIGHT; y++) {
              for(x = 0; x < MAP_WIDTH; x++) {
                  if (patches[x][y].depth == 0.0) {
                      colorValues[DETRITUS_INDEX][x][y] = -1;
                  }
                  else {
                      scale_color(patches[x][y].detritus, AVG_detritus, 0.0, x, y, DETRITUS_INDEX);
                  }
              }
          }
      //}

      //else if(strcmp(which_stock, "sedconsumer") == 0) {
          hues[SEDCONSUMER_INDEX] = 60.0 / 360.0;
          for(y = 0; y < MAP_HEIGHT; y++) {
              for(x = 0; x < MAP_WIDTH; x++) {
                  if (patches[x][y].depth == 0.0) {
                      colorValues[SEDCONSUMER_INDEX][x][y] = -1;
                  }
                  else {
                      scale_color(patches[x][y].sedconsumer, MAX_SEDCONSUMER, 0.0, x, y, SEDCONSUMER_INDEX);
                  }
              }
          }
      //}

      //else if(strcmp(which_stock, "seddecomp") == 0) {
          hues[SEDDECOMP_INDEX] = 240.0 / 360.0;
          double total_seddecomp = 0;
          num_patches = 0;
          
          for(y=0; y < MAP_HEIGHT; y++) {
            for(x = 0; x < MAP_WIDTH; x++) {
              if(patches[x][y].depth > 0.0) {
                total_seddecomp +=patches[x][y].seddecomp;
                num_patches++;
              }
            }
          }
        double AVG_seddecomp = total_seddecomp/num_patches;
        for(y = 0; y < MAP_HEIGHT; y++) {
            for(x = 0; x < MAP_WIDTH; x++) {
                if(patches[x][y].depth == 0.0) {
                    colorValues[SEDDECOMP_INDEX][x][y] = -1;
				}
                else { //Magic numbers taken from original Netlogo code
                    scale_color(patches[x][y].seddecomp, AVG_seddecomp, 0.0, x, y, SEDDECOMP_INDEX);
			    }
            }
		}
    //}
	
    //else if(strcmp(which_stock, "herbivore") == 0) {
        hues[HERBIVORE_INDEX] = 300.0 / 360.0;
        for(y = 0; y < MAP_HEIGHT; y++) {
            for(x = 0; x < MAP_WIDTH; x++) {
                if(patches[x][y].depth == 0.0) {
                    colorValues[HERBIVORE_INDEX][x][y] = -1;
				}
                else { //Magic numbers taken from original Netlogo code
                    scale_color(patches[x][y].herbivore, MAX_HERBIVORE, 0.0, x, y, HERBIVORE_INDEX);
                }
			}
		}
    //}
	
    //else if(strcmp(which_stock, "consum") == 0) {
        hues[CONSUM_INDEX] = 300.0 / 360.0;
        for(y = 0; y < MAP_HEIGHT; y++) {
            for(x = 0; x < MAP_WIDTH; x++) {
                if(patches[x][y].depth == 0.0) {
                    colorValues[CONSUM_INDEX][x][y] = -1;
				}
                else { //Magic numbers taken from original Netlogo code
                    scale_color(patches[x][y].consum, MAX_CONSUM, 0.0, x, y, CONSUM_INDEX);
                }
			}
		}
    //}
	
    //else if(strcmp(which_stock, "DOC") == 0) {
        hues[DOC_INDEX] = 60.0 / 360.0;
        double total_DOC = 0;
        num_patches = 0;
        
        for(y=0; y < MAP_HEIGHT; y++) {
          for(x = 0; x < MAP_WIDTH; x++) {
            if(patches[x][y].depth > 0.0) {
              total_DOC +=patches[x][y].DOC;
              num_patches++;
            }
          }
        }
        double AVG_DOC = total_DOC/num_patches;
        for(y = 0; y < MAP_HEIGHT; y++) {
            for(x = 0; x < MAP_WIDTH; x++) {
                if(patches[x][y].depth == 0.0) {
                    colorValues[DOC_INDEX][x][y] = -1;
				}
                else { //Magic numbers taken from original Netlogo code
                    scale_color(patches[x][y].DOC, AVG_DOC, 0.0, x, y, DOC_INDEX);
                }
			}
		}
    //}
}
