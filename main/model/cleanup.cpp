#include "cleanup.h"

/**
 * Frees the allocated structures in the application
*/
void cleanup() 
{
    clean_patches();
    clean_temperature_data();
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

	free( g.covered_area );
	free( g.uncovered_area );
    free( patches );
}

/**
 * Frees the temperature_data array
 */
void clean_temperature_data() {
    free( g.temperature_data );
}
