#ifndef RIVER_H
#define RIVER_H
#include <omp.h>
#include <QString>
#include <QDateTime>
#include <QFile>
#include <QVector2D>
#include "constants.h"
#include "globals.h"
#include "configuration.h"
#include "hydrofiledict.h"
#include "hydrofile.h"
#include "patchCollection.h"
#include "flowdata.h"


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
        void setCurrentPAR(int newPAR);

        /**
         * @brief Iterates over the river and performs calculations on each patch
         */
        void processPatches();

        /**
         * @brief Makes the river flow for a simulated hour
         */
        void flow();


        /**
         * @brief Outputs the patch data to a csv file
         * @param outputPath Location to save the file
         * @param filenamePrefix Prefix for filename
         */
        int saveCSV() const;

    private:
        /**
         * @brief Helper function for flow that handles flowing fow a single timestep
         */
        void flowSingleTimestep(Grid<FlowData> & source, Grid<FlowData> & dest, Configuration & config);

        //Temp functions, will be replaced in move to carbonFlowMap
        void copyFlowData(Grid<FlowData> & flowData);
        void storeFlowData(Grid<FlowData> & flowData);
        bool is_calc_nan(int x, int y, double move_factor, Grid<FlowData> & dst);
        double getMaxTimestep();



        PatchCollection p;
        Configuration config;

        HydroFile * currHydroFile;
        double currWaterTemp;
        int currPAR;

        int width;
        int height;
};

#endif // RIVER_H
