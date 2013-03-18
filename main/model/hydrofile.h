#ifndef HYDROFILE_H
#define HYDROFILE_H

#include <QColor>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QHash>
#include <QImage>
#include <QRgb>
#include <QVector2D>
#include <QVector>
#include "grid.h"


class HydroFile {
    public:
        /**
         * \brief Constructor. We need to know the max size of all the hydromaps...
         */
        HydroFile(QString filename);
        HydroFile();
        //~HydroFile();
        //HydroFile const & operator=( HydroFile const & other );

        /**
         * \brief Loads the current hydroFile using a file, only if not previously initialized.
         * Otherwise, this function does nothing.
         * \param[in] filename The name of the file to load
         */
        void loadFromFile(QString filename);

        /**
         * \brief Checks if a water cell exists at the given (x,y) coordinate
         * \param[in] x The x coordinate
         * \param[in] y The y coordinate
         */
        bool patchExists(int x, int y) const;

        /**
         * \brief Gets the depth of the cell at the given (x,y) coordinate
         * \param[in] x The x coordinate
         * \param[in] y The y coordinate
         */
        double getDepth(int x, int y);

        /**
         * \brief Returns the 2D flow vector for the cell at the given (x,y) coordinate
         * \param[in] x The x coordinate
         * \param[in] y The y coordinate
         */
        const QVector2D & getVector(int x, int y);

        /**
         * \brief Returns the map's width
         */
        int getMapWidth(void) const;

        /**
         * \brief Returns the map's depth
         */
        int getMapHeight(void) const;

        /**
         * \brief Generates a QImage representation of the hydromap.
         */
        // TODO: Refactor this function. (low priority)
        QImage generateVisualization(int imageCellSize);

    private:
        struct HydroData {
            int x;
            int y;
            QVector2D flowVector;
            double depth;
        };

        bool hydroFileLoaded;
        QString hydroMapFileName;
        int width;
        int height;
        int waterCellCount;
        int maxFlow;
        int maxDepth;



        /**
         * \brief Reads the datafile to determine the dimension of the map.
         */
        void setMapSize(QStringList & hydroFileData);

        /**
         * \brief Initializes the input grid with default (zeroized) data.
         */
        void zeroHydroData(Grid<HydroData> & hydroData);

        QVector<HydroData> hydroDataSet;
        QHash<int, int> hydroDataSetIndices;
        int getHashKey(int x, int y) const;

        /**
         * \brief Returns an entire cell's data at the given (x,y) coordinate.
         */
        HydroData & getData(int x, int y);
};

#endif
