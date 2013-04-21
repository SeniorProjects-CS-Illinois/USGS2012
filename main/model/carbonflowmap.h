#ifndef CARBONFLOWMAP_H
#define CARBONFLOWMAP_H

#include <algorithm>
#include <cmath>

#include "constants.h"
#include "hydrofile.h"
#include "grid.h"
#include "carbonsources.h"

struct SourceArrays {
    int totalSources;
    Grid<int> * offsets;
    Grid<int> * sizes;
    int * x;
    int * y;
    double * amount;
};


class CarbonFlowMap {
    public:
        CarbonFlowMap();
        CarbonFlowMap(HydroFile * hydroFile, int iterations);
        const SourceArrays getSourceArrays() const;

        void printDebug();

    private:
        HydroFile * hydroFile;
        int iterations;

        void initializeCarbonCollection(Grid<CarbonSourceCollection> & source);
        void pushCarbon(Grid<CarbonSourceCollection> & source, Grid<CarbonSourceCollection> & dest);
        QVector<CarbonSource> * getFlowTargets(int x, int y);

        SourceArrays sourceData;
};

#endif
