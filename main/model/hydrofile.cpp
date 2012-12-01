#include "hydrofile.h"

HydroFile::HydroFile(QString filename, int max_map_width, int max_map_height){
    hydroMapFileName = filename;
    width = max_map_width;
    height = max_map_height;

    //TODO Give the grid class a default constructor and allow it to
    //     resize.  Then read hydromap and populate data.

}
