#ifndef _PRED
#define _PRED

#include "globals.h"
#include "setup.h"
#include "patch.h"

/**
 * \brief Predicts the new phyto value in the patch
 * \param x The x coord of the patch
 * \param y The y coord of the patch
 */
void pred_phyto(int x, int y);


/**
 * \brief Predicts the new herbivore value in the patch
 * \param x The x coord of the patch
 * \param y The y coord of the patch
 */
void pred_herbivore(int x, int y);


/**
 * \brief Predicts the new seddecomp value in the patch
 * \param x The x coord of the patch
 * \param y The y coord of the patch
 */
void pred_seddecomp(int x, int y);


/**
 * \brief Predicts the new waterdecomp value in the patch
 * \param x The x coord of the patch
 * \param y The y coord of the patch
 */
void pred_waterdecomp(int x, int y);


/**
 * \brief Predicts the new sedconsumer of the patch
 * \param x The x coord of the patch
 * \param y The y coord of the patch
 */
void pred_sedconsumer(int x, int y);


/**
 * \brief Predicts the new detritus value in the patch
 * \param x The x coord of the patch
 * \param y The y coord of the patch
 */
void pred_detritus(int x, int y);


/**
 * \brief Predicts the new DOC value in the patch
 * \param x The x coord of the patch
 * \param y The y coord of the patch
 */
void pred_DOC(int x, int y);


/**
 * \brief Predicts the new POC value in the patch
 * \param x The x coord of the patch
 * \param y The y coord of the patch
 */
void pred_POC(int x, int y);


/**
 * \brief Predicts the new consum value in the patch
 * \param x The x coord of the patch
 * \param y The y coord of the patch
 */
void pred_consum(int x, int y);
#endif
