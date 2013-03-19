#ifndef RIVER_H
#define RIVER_H
#include "globals.h"
#include "configuration.h"
#include "hydrofiledict.h"
#include "hydrofile.h"


class River {
    public:
        River(Configuration & newConfig, HydroFileDict & hydroFileDict);


        /**
         * \brief Sets the hydromap to use in future calculations
         * \param currHydroFile HydroFile to use
         */
        void setCurrentHydroFile(HydroFile * newHydroFile);

        /**
         * \brief Sets the current water temp to use in future calculations
         * \param newTemp New temp to use.
         */
        void setCurrentWaterTemperature(double newTemp);

        /**
         * @brief Sets the current PAR to use in future calculations
         * @param newPAR New PAR to use.
         */
        void setCurrentPAR(double newPAR);

        /**
         * @brief Iterates over the river and performs calculations on each patch
         */
        void processPatches();

    private:
        Configuration config;

        HydroFile * currHydroFile;
        double currWaterTemp;
        int currPAR;




};

#endif // RIVER_H
