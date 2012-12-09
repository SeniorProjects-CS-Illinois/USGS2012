#ifndef _CLEANUP
#define _CLEANUP

#include "globals.h"
#include "patch.h"

/**
 * Frees the allocated structures in the application
*/
void cleanup();


/**
 * Frees up the 2D array of patches
 */
void clean_patches();

/**
 * Empties the structures that we filled during model setup.
 */
void empty_structures(void);

#endif
