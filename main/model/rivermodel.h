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
#include "globals.h"
#include "hydrofile.h"
#include "hydrofiledict.h"
#include "river.h"
#include "status.h"

using std::cout;
using std::endl;

class RiverModel {
    public:
        RiverModel();

        /**
         * Runs the model.
         */
        void run(void);

        /**
         * Set the configuration for the river model.
         * @brief setConfiguration
         * @param configuration the configuration for this model
         */
        void setConfiguration(const Configuration & configuration);

        /**
         * Get the status of the current river model.
         * @brief getStatus
         * @return the status of the model
         */
        Status getStatus(void);

        /**
         * \brief Returns an image of the currently selected stock.
         */
        QImage getImage(void);

        /**
         * \brief Returns the stock requested.
         */
        QImage getImage(QString stockName);

        /**
         * Change the main stock.
         * @brief setWhichStock
         * @param stockName the new stock name
         */
        void setWhichStock(QString stockName);

    private:
        void printHourlyMessage(int daysElapsed, int hourOfDay);

        void initializeModel(const Configuration & config);

        /**
         * Initialize the status for the model.
         */
        void initializeModelStatus(int daysToRun);

        void initializeImageVector(HydroFileDict & hydroFileDict);

        void initializeStockNames();

        void initializeHydroMaps(const Configuration & config);

        void initializeWaterTemps(const Configuration & config);

        void initializePARValues(const Configuration & config);

        void initializeTempGrids(HydroFileDict & hydroFileDict);
        void deleteTempGrids();

        int getDaysToRun(const Configuration & config);

        void saveAverages(Statistics & stats, int daysElapsed);


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

        Grid<FlowData> * source;
        Grid<FlowData> * dest;
};
#endif
