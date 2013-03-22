#include "globals.h"

Globals g;

void initialize_globals(void){

    g.COMPARE_MAX = 0.0; ///< represents the maximum of the x or y vector among all patches, this is used to calculate max step
    g.nan_trigger = 0;  ///< 1 if there is a NaN value in the DOC values 0 otherwise

    // convert ft to m from the SMS to .png scaling conversion
    g.patch_length = 30;
    g.max_area = 30*30;
    g.theta = 1.072;
}
