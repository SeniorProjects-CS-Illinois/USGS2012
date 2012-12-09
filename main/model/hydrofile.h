#ifndef HYDROFILE_H
#define HYDROFILE_H

#include <QString>
#include <QHash>

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
        double getXVector(int x, int y) const;
        double getYVector(int x, int y) const;
        double getVelocity(int x, int y) const;
        double getDepth(int x, int y) const;

        int getMapWidth(void) const;
        int getMapHeight(void) const;



    private:
        struct HydroData {
            bool available;
            //TODO: Don't think these two ints are needed...
            int xCor;
            int yCor;
            double xVector;
            double yVector;
            double velocity;
            double depth;
        };

        CarbonFlowMap * carbonFlowMap;
        int carbonFlowIterations;
        QString hydromapFileName;
        int width;
        int height;

        std::vector<HydroData> hydroDataSet;
        QHash<int, int> hydroDataSetIndices;
        int getHashKey(int x, int y) const;

        void copy(HydroFile const & other);
        void clear();
};

#endif
