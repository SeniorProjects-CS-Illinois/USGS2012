#ifndef _CLEANUP
#define _CLEANUP

#include <stdio.h>
#include <stdlib.h>

#include "globals.h"
#include "patch.h"
#include "color.h"

/**
 * Frees the allocated structures in the application
*/
void cleanup();


/**
 * Frees up the 2D array of patches
 */
void clean_patches();


/**
 * Frees the temperature_data array
 */
void clean_temperature_data();


#endif
