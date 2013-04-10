#include "globals.h"

Globals g;

void initialize_globals(void){

    g.COMPARE_MAX = 0.0; ///< represents the maximum of the x or y vector among all patches, this is used to calculate max step
    g.nan_trigger = 0;  ///< 1 if there is a NaN value in the DOC values 0 otherwise
}
