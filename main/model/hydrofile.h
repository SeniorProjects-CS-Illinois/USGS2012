#ifndef HYDROFILE_H
#define HYDROFILE_H

#include <QString>
#include <QHash>
#include <QVector2D>
#include <QVector>

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
        double getDepth(int x, int y) const;
        double getVector(int x, int y) const;

        int getMapWidth(void) const;
        int getMapHeight(void) const;



    private:
        struct HydroData {
            QVector2D flowVector;
            double depth;
        };

        CarbonFlowMap * carbonFlowMap;
        int carbonFlowIterations;
        QString hydromapFileName;
        int width;
        int height;
        void setMapSize(QStringList hydroFileData);
        static void zeroHydroData(HydroData[][] hydroData);

        QVector<HydroData> hydroDataSet;
        QHash<int, int> hydroDataSetIndices;
        int getHashKey(int x, int y) const;

        HydroData & getData(int x, int y);

        void copy(HydroFile const & other);
        void clear();
};

#endif
