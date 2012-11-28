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
 * Frees the hydromap_index_array
 */
void clean_hydromap_index_array();


/**
 * Frees the chek_filenames_array;
 */
void clean_check_filenames_array();


/**
 * Frees the gui_filenames_arrau and days_array
 */
 void clean_gui_filenames_and_days();


 /**
 * Frees the photo_radiation_data array
 */
void clean_photo_radiation_data();


/**
 * Frees the temperature_data array
 */
void clean_temperature_data();


#endif
