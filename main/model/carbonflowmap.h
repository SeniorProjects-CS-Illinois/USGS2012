#ifndef CARBONFLOWMAP_H
#define CARBONFLOWMAP_H

#include "hydrofile.h"
#include "grid.h"
#include "carbonsources.h"
#include "globals.h"

class CarbonFlowMap {
    public:
        CarbonFlowMap(HydroFile * hydroFile, int iterations);

    private:
        HydroFile * hydroFile;
        int iterations;

        void initializeCarbonSources(Grid<CarbonSources> & source);
        void pushCarbon(Grid<CarbonSources> & source, Grid<CarbonSources> & dest);
        QVector<CarbonSource> getFlowTargets(int x, int y);

};

#endif
