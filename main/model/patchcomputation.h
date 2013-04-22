#ifndef PATCHCOMPUTATION_H
#define PATCHCOMPUTATION_H
#include <cmath>
#include <omp.h>
#include "constants.h"
#include "globals.h"
#include "patchcollection.h"
#include "configuration.h"
#include "utility.h"

/**
 * @brief A collection of all the processing functions.
 */
namespace PatchComputation {

    void updatePatches(PatchCollection & p, const Configuration & config, int currPAR);
    void macro(PatchCollection & p, const Configuration & config, int currPAR, int currWaterTemp, double currGrowthRate);
    void phyto(PatchCollection & p, const Configuration & config, int currPAR, int currWaterTemp);
    void herbivore(PatchCollection & p, const Configuration & config);
    void waterDecomp(PatchCollection & p, const Configuration & config);
    void sedDecomp(PatchCollection & p, const Configuration & config);
    void sedConsumer(PatchCollection & p, const Configuration & config);
    void consumer(PatchCollection & p, const Configuration & config);
    void DOC(PatchCollection & p, const Configuration & config);
    void POC(PatchCollection & p);
    void detritus(PatchCollection & p, const Configuration & config);

    void predPhyto(PatchCollection & p, int i);
    void predHerbivore(PatchCollection & p, int i);
    void predSedDecomp(PatchCollection & p, int i);
    void predWaterDecomp(PatchCollection & p, int i);
    void predSedConsumer(PatchCollection & p, int i);
    void predDetritus(PatchCollection & p, int i);
    void predDOC(PatchCollection & p, int i);
    void predPOC(PatchCollection & p, int i);
    void predConsum(PatchCollection & p, int i);

}

#endif // PATCHCOMPUTATION_H
