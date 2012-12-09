#ifndef HYDROFILE_H
#define HYDROFILE_H

#include <QString>
#include "grid.h"


class HydroFile {
    public:
        /**
         * Constructor. We need to know the max size of all the hydromaps...
         */
        HydroFile(QString filename, int max_map_width, int max_map_height);

    private:
        struct HydroData {
            bool available;
            //TODO: Don't think these two ints are needed...
            int pxcor;
            int pycor;
            double px_vector;
            double py_vector;
            double velocity;
            double depth;
        };

        QString hydromapFileName;
        int width;
        int height;
        Grid<HydroData> HydroDataSet;
};

#endif
