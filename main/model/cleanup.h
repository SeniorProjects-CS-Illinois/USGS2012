#ifndef _CLEANUP
#define _CLEANUP

#include "globals.h"
#include "patch.h"

/**
 * \brief Frees the allocated structures in the application
 */
void cleanup();


/**
 * \brief Frees up the 2D array of patches
 */
void clean_patches();

/**
 * \brief Empties the structures that we filled during model setup.
 */
void empty_structures(void);

#endif
