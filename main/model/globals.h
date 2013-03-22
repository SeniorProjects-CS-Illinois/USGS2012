#ifndef _GLOBALS
#define _GLOBALS

typedef struct {
    // Model variables
    double COMPARE_MAX; ///< represents the maximum of the x or y vector among all patches, this is used to calculate max step
    int nan_trigger;  ///< 1 if there is a NaN value in the DOC values 0 otherwise

    // convert ft to m from the SMS to .png scaling conversion
    //TODO add these three values as constants
    int patch_length;
    int max_area;
    double theta;
} Globals;

extern Globals g;

void initialize_globals(void);

#endif
