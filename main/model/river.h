#ifndef RIVER_H
#define RIVER_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <omp.h>
#include <QColor>
#include <QDateTime>
#include <QImage>
#include <QImageWriter>
#include <QMutex>
#include <QString>
#include <QVector2D>

#include "configuration.h"
#include "constants.h"
#include "flowdata.h"
#include "hydrofile.h"
#include "hydrofiledict.h"
#include "patchcollection.h"
#include "patchcomputation.h"
#include "statistics.h"

using std::ofstream;
using std::cout;
using std::endl;
using std::max;


class River {
    public:

        /**
         * @brief Constructor that initializes PatchCollection and default values
         * @param newConfig Config used by the model
         * @param hydroFileDict Collection of hydrofiles used in this simulation
         */
        River(Configuration & newConfig, HydroFileDict & hydroFileDict);


        /**
         * @brief Sets the hydromap to use in future calculations
         * @param currHydroFile HydroFile to use
         */
        void setCurrentHydroData(HydroData * newHydroData);

        /**
         * @brief Sets the current water temp to use in future calculations
         * @param newTemp New temp to use.
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
        void flow(Grid<FlowData> * source, Grid<FlowData> * dest);


        /**
         * @brief Outputs the patch data to a csv file
         * @param outputPath Location to save the file
         * @param filenamePrefix Prefix for filename
         */
        void saveCSV(QString displayedStock, int daysElapsed) const;

        /**
         * @brief Produces a visualization of the river at the current point in the
         * simulation and saves the images to disk.
         * @param images QVector to store the produced images in
         * @param stockNames QVector of stock names used for file naming
         * @param imageMutex Mutex to lock when writing the images in memory
         * @param stats A collection of statistics collected about the river for color scaling
         */
        void generateImages(QVector<QImage> & images, QVector<QString> & stockNames,
                           QMutex & imageMutex, Statistics & stats);

        /**
         * @brief Collects various facts about the river and places them in a Statistics struct
         * @return A collection of stats about the river
         */
        Statistics generateStatistics();


    private:
        /**
         * @brief Helper function for flow that handles flowing fow a single timestep
         */
        void flowSingleTimestep(Grid<FlowData> & source, Grid<FlowData> & dest, Configuration & config);

        //Temp functions, will be replaced in move to carbonFlowMap
        void copyFlowData(Grid<FlowData> & flowData);
        void storeFlowData(Grid<FlowData> & flowData);
        bool is_valid_patch(int x, int y);

        /**
         * @brief Computes the color to draw based on the patch's
         *        value compared to all other patches.  Resulting image
         *        will be a heat map.
         * @param value The current patch's value
         * @param avgValue The average of the value across the map
         * @param maxValue The max of the value across the map
         * @return A QColor object containing the color to draw in an image
         */
        QColor getHeatMapColor(double value, double avgValue, double maxValue);


        PatchCollection p;
        Configuration config;

        HydroData * currHydroData;
        double currWaterTemp;
        int currPAR;

        int width;
        int height;
};

#endif // RIVER_H
