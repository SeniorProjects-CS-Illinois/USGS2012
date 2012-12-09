#include "cleanup.h"

/**
 * Frees the allocated structures in the application
 */
void cleanup() 
{
    clean_patches();
}

/**
 * Frees up the 2D array of patches
 */
void clean_patches() 
{
    for (int x = 0; x < g.MAP_WIDTH; x++) 
    {
        for (int y = 0; y < g.MAP_HEIGHT; y++) 
        {
            free( patches[x][y].available );
            free( patches[x][y].pxv_list );
            free( patches[x][y].pyv_list );
            free( patches[x][y].depth_list );
            free( patches[x][y].v_list );
        }

        free( patches[x] );
    }

    free( g.covered_area );
    free( g.uncovered_area );
    free( patches );
}

/**
 * Empties structures filled during setup.
 */
void empty_structures(void){
    g.gui_filenames_list.clear();
    g.uniqueHydroFilenames.clear();
    g.gui_days_vector.clear();
    g.hydromap_index_vector.clear();
    g.temperature_data.clear();
    g.photo_radiation_data.clear();
}
