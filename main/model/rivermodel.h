#ifndef RIVERMODEL_H
#define RIVERMODEL_H

#include <iostream>
#include <QFile>
#include <QImage>
#include <QMutex>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QVector>

#include "configuration.h"
#include "constants.h"
#include "hydrofile.h"
#include "hydrofiledict.h"
#include "river.h"
#include "status.h"

using std::cout;
using std::endl;

class RiverModel {
    public:
        /**
         * @brief Default constructor.  Does nothing.
         */
        RiverModel();

        //Big 3, Regardless, copies should not be made during a running simulation.
        RiverModel(const RiverModel & other);
        ~RiverModel();
        RiverModel & operator=(const RiverModel & rhs);

        /**
         * @brief Starts the simulation
         */
        void run(void);

        /**
         * @brief Set the configuration for the river model.
         * @param configuration The config object for this model
         */
        void setConfiguration(const Configuration & configuration);

        /**
         * @brief Get the status of the current river model.
         * @return the status of the model
         */
        Status getStatus(void);

        /**
         * @brief Returns an image of the currently selected stock.
         */
        QImage getImage(void);

        /**
         * @brief Returns the specific stock requested.
         */
        QImage getImage(QString stockName);

        /**
         * @brief Change the current stock of interest.
         * @param stockName the new stock name
         */
        void setWhichStock(QString stockName);

    private:
        Status modelStatus;
        Configuration modelConfig;
        HydroFileDict hydroFileDict;
        QVector<double> waterTemps;
        QVector<int> parValues;

        QString displayedStock;
        QVector<QString> stockNames;

        QString averagesFilename;

        QVector<QImage> images;
        QMutex imageMutex;
        QMutex statusMutex;

        Grid<FlowData> * source;
        Grid<FlowData> * dest;


        /**
         * @brief Writes a status message to a terminal window every simulated hour
         * @param daysElapsed The days elapsed in the simulation
         * @param hourOfDay The hour of the currect day in the simulation
         */
        void printHourlyMessage(int currentDay, int hourOfDay);

        /**
         * @brief Initializes entire model
         * @param config Config used by the model
         */
        void initializeModel(const Configuration & config);

        /**
         * @brief Initializes the model's status object with the ammount of work to be done
         * @param daysToRun The number of days to simulate
         */
        void initializeModelStatus(int daysToRun);

        /**
         * @brief Populates the image array with images
         * @param hydroFileDict Hydrofiles so we can set the width and height of images
         */
        void initializeImageVector(HydroFileDict & hydroFileDict);

        /**
         * @brief Populates a QVector with string names of each stock
         *        The ordering must match the stocks enum in constants.h
         */
        void initializeStockNames();

        /**
         * @brief Initializes the hydromaps used by the simulation
         * @param config Config used by the model
         */
        void initializeHydroMaps(const Configuration & config);

        /**
         * @brief Initializes a QVector of water temperatures from file
         * @param config Config used by the model
         */
        void initializeWaterTemps(const Configuration & config);

        /**
         * @brief Initializes a QVector of PAR values from file
         * @param config Config used by the model
         */
        void initializePARValues(const Configuration & config);

        /**
         * @brief Initializes temp Grids of flowdata structs for the River's flow routine
         * @param hydroFileDict Hydrofiles so we know the width and height to use
         */
        void initializeTempGrids(HydroFileDict & hydroFileDict);


        /**
         * @brief Calculates the number of days the the simulation will run
         * @param config Config used by the model
         * @return The number of days the simulation with run
         */
        int getDaysToRun(const Configuration & config);

        /**
         * @brief Writes the average of each stock to file
         * @param stats Source of the averages to write
         * @param daysElapsed Days Elapsed to write
         */
        void saveAverages(Statistics & stats, int currentDay);

        /**
         * @brief Sets the modelStatus object's message.  Thread safe.
         * @param message The message to set
         */
        void setStatusMessage(QString message);

        void copy(const RiverModel & other);
        void clear();

};
#endif
