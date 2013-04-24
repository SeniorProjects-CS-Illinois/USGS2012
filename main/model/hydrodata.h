#ifndef HYDRODATA_H
#define HYDRODATA_H

#include "hydrofile.h"
#include "carbonflowmap.h"

struct HydroData {
    HydroFile hydroFile;
    CarbonFlowMap carbonFlowMap;
};

#endif // HYDRODATA_H
