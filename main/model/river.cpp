#include "river.h"

River::River(Configuration & newConfig, HydroFileDict & hydroFileDict)
    : p(newConfig,hydroFileDict)
{

    config = newConfig;

    currHydroFile = NULL;
    currWaterTemp = -1.0;
    currPAR = -1;
}


void River::setCurrentHydroFile(HydroFile *newHydroFile) {
    // TODO Read over 2011 code to make sure we handle everything
    // in hyrdofile transitions -ECP

    currHydroFile = newHydroFile;
}

void River::setCurrentWaterTemperature(double newTemp) {
    /*
     * TODO I don't know what this calculation is doing...
     * Is it really the "temperature" anymore after this?
     * If not, my member variable's name should change. -ECP
     *
     * Edit: temp_dif is only assigned a value of 0...  Removing for now. Something
     * to ask Kevin I suppose... -ECP
     *
     * Here is original 2011 team's function:
     *
     * g.temperature_index++;
     * g.temperature = g.temperature_data[g.temperature_index];
     * g.temperature = g.temperature - ((g.temperature - 17.0) * g.temp_dif);
     */

    currWaterTemp = newTemp;// - ((newTemp - 17.0) * g.temp_dif);
}

void River::setCurrentPAR(int newPAR) {
    /*
     * TODO I don't know what this calculation is doing...
     * Is it really the "PAR" anymore after this?
     * If not, my member variable's name should change.
     * Also, is integer truncation the right thing to do or should it round? -ECP
     *
     * Edit: par_dif is only assigned a value of 0...  Removing for now. Something
     * to ask Kevin I suppose... -ECP
     *
     * Here is original 2011 team's function:
     *
     * g.photo_radiation_index++;
     * g.photo_radiation = g.photo_radiation_data[g.photo_radiation_index];
     * g.photo_radiation = g.photo_radiation - (int)(g.photo_radiation * g.par_dif);
     */

    currPAR = newPAR;// - (int)(newPAR * g.par_dif);
}


void processPatches() {
    //TODO Iterate over patch collection and perform computations
}



