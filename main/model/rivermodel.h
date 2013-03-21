#ifndef RIVERMODEL_H
#define RIVERMODEL_H

#include <sys/types.h>
#include <stdlib.h>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <vector>

#include "status.h"
#include "globals.h"
#include "setup.h"
#include "patch.h"
#include "go.h"
#include "dump.h"
#include "cleanup.h"
#include "configuration.h"
#include "hydrofiledict.h"
#include "hydrofile.h"
#include "river.h"

using std::cout;
using std::endl;

class RiverModel {
    public:



        /**
         * Runs the model.
         */
        void run(void);

        /**
         * Runs the refactored model.
         */
        void newRun(void);

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


        /**
         * Initialize the status for the model.
         */
        void initializeModelStatus(int daysToRun);


        void initializeHydroMaps(const Configuration & config);

        void initializeWaterTemps(const Configuration & config);

        void initializePARValues(const Configuration & config);

        int getDaysToRun(const Configuration & config);


        Status modelStatus;
        Configuration modelConfig;
        HydroFileDict hydroFileDict;
        QVector<double> waterTemps;
        QVector<int> parValues;

        QString displayedStock;

};
#endif
