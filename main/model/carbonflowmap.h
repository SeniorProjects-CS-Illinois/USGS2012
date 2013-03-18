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

        void initializeCarbonCollection(Grid<CarbonSourceCollection> & source);
        void pushCarbon(Grid<CarbonSourceCollection> & source, Grid<CarbonSourceCollection> & dest);
        QVector<CarbonSource> * getFlowTargets(int x, int y);

};

#endif
