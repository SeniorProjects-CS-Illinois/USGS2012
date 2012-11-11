#include "cleanup.h"

/**
 * Frees the allocated structures in the application
*/
void cleanup() 
{
    clean_patches();
    clean_photo_radiation_data();
    clean_temperature_data();
    clean_gui_filenames_and_days();
    clean_hydromap_index_array();
    clean_check_filenames_array();
}

/**
 * Frees up the 2D array of patches
 */
void clean_patches() 
{
    int x,y,stock;
    for (x = 0; x < g.MAP_WIDTH; x++) 
	{
        for (y = 0; y < g.MAP_HEIGHT; y++) 
		{
            free( patches[x][y].available );
            free( patches[x][y].pxv_list );
            free( patches[x][y].pyv_list );
            free( patches[x][y].depth_list );
            free( patches[x][y].v_list );
        }

        free( patches[x] );
    }
    for (stock = 0; stock < g.NUM_STOCKS; stock++) {
        free(colorValues[stock]);
    }

	free( g.covered_area );
	free( g.uncovered_area );
    free( patches );
    free( colorValues );
}


/**
 * Frees the filenames and days to run array
*/
void clean_gui_filenames_and_days() 
{
    int index;
    for(index = 0; index < g.gui_filenames_filesize; index++)
	{
        free(g.gui_filenames_array[index]);
    }
    free(g.gui_filenames_array);
    free(g.gui_days_array);
}


/**
 * Frees the hydromap index array
*/
void clean_hydromap_index_array() 
{
	free(g.hydromap_index_array);
}


/** 
 * Frees the check filenames array
*/
void clean_check_filenames_array() {
  int index;
  for(index = 0; index < g.num_unique_files; index++){
    free(g.check_filenames_array[index]);
  }
  free(g.check_filenames_array);
}


/**
 * Frees the photo_radiation_data array
*/
void clean_photo_radiation_data() {
    free( g.photo_radiation_data );
}

/**
 * Frees the temperature_data array
 */
void clean_temperature_data() {
    free( g.temperature_data );
}
