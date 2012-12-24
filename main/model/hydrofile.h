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

//TODO Replace this type when we start to implement CarbonflowMap related stuff.
typedef int CarbonFlowMap;


class HydroFile {
    public:
        /**
         * Constructor. We need to know the max size of all the hydromaps...
         */
        HydroFile(QString filename);
        ~HydroFile();
        HydroFile const & operator=( HydroFile const & other );

        /**
         * Given an int, precomputes flows for the specified number of iterations using the hydrofile's data.
         * Memoizes and returns a CarbonFlowMap pointer.
         */
        CarbonFlowMap * getCarbonFlowMap(int iterations);

        bool patchExists(int x, int y) const;
        double getDepth(int x, int y);
        QVector2D getVector(int x, int y);

        int getMapWidth(void) const;
        int getMapHeight(void) const;

        QImage generateVisualization(int imageCellSize);

    private:
        struct HydroData {
            int x;
            int y;
            QVector2D flowVector;
            double depth;
        };

        CarbonFlowMap * carbonFlowMap;
        int carbonFlowIterations;
        QString hydroMapFileName;
        int width;
        int height;
        int waterCellCount;
        int maxFlow;
        int maxDepth;
        void setMapSize(QStringList hydroFileData);
        void zeroHydroData(Grid<HydroData> hydroData);

        QVector<HydroData> hydroDataSet;
        QHash<int, int> hydroDataSetIndices;
        int getHashKey(int x, int y) const;

        HydroData & getData(int x, int y);

        void copy(HydroFile const & other);
        void clear();
};

#endif
