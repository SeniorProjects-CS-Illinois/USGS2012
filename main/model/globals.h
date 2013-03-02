#ifndef _GLOBALS
#define _GLOBALS

#include "patch.h"
#include <QString>
#include <QStringList>
#include <vector>
#include <QImage>
#include <QImageWriter>
#include <QMutex>

/**
 *  Improve parameters
 *      - better/uniform naming
 *      - floats?
 */
typedef struct {
    // Model variables
    int MAP_WIDTH;  ///< the map's width
    int MAP_HEIGHT; ///< the map's height
    long hours;    ///< Represents 1 tick (should always be [0, sizeof(long)]
    double COMPARE_MAX; ///< represents the maximum of the x or y vector among all patches, this is used to calculate max step

    // GUI variables
    int current_day; ///< Keeps track of how often output should be generated
    const char* file_extension;

    int gui_days_to_run;  // number of days to run the code

    // GUI input hydro maps and days for each map
    QStringList uniqueHydroFilenames;
    int num_unique_files;
    int gui_filenames_filesize;
    int num_hydro_files;

    //Maps each hydromapfile to a the unique index of a hydromapfile
    //i.e. current_map = uniqueHydroFilenames[ hydromap_index_vector[current_day] ]
    std::vector<int> hydromap_index_vector;

    int current_file_index;

    // Environmental globals
    std::vector<double> temperature_data;  ///< temp array which holds data that temp indexes
    std::vector<int> photo_radiation_data; // vector which holds data that photo_radiation indexes
    int* covered_area;      ///< Area of land covered by water
    int* uncovered_area;    ///< Area of land not covered by water

    int temperature_index; ///< The index of the current temperature value
    int photo_radiation_index; ///< The index of the current photo_radiation value

    double temperature;    ///< temp
    int photo_radiation;   ///< photo_radiation

    int hydro_group;   ///< hydro-group
    int hydro_changed;  //boolean stating if the hydro map was changed
    double temp_dif;   ///< The percent difference from 17 degrees Celsius. (Used in update_temp)
    double par_dif;    ///< The percent difference in par. (Used in update_par)

    int nan_trigger;  ///< 1 if there is a NaN value in the DOC values 0 otherwise

    // convert ft to m from the SMS to .png scaling conversion
    int patch_length;
    int max_area;

    // max gwr/unit biomass; e- excretion->DOC; r- respiration; s- senecence(natural mortality); -egestion ->POC
    double MAX_MACRO;
    double MAX_PHYTO;
    double MAX_HERBIVORE;
    double MAX_WATERDECOMP;
    double MAX_SEDDECOMP;
    double MAX_SEDCONSUMER;
    double MAX_CONSUM;
    double MAX_DOC;
    double MAX_POC;
    double MAX_DETRITUS;

    // set k-macro .4 -> taken from interface
    // set k-phyto .4 -> taken from interface
    double k_herbivore;
    double k_POC;

    double theta;

    //temperatue dependent coefficient for aquatic plants
    double Q10;

    // indices for the array for each stock
    int MACRO_INDEX;
    int PHYTO_INDEX;
    int HERBIVORE_INDEX;
    int WATERDECOMP_INDEX;
    int SEDDECOMP_INDEX;
    int SEDCONSUMER_INDEX;
    int CONSUM_INDEX;
    int DOC_INDEX;
    int POC_INDEX;
    int DETRITUS_INDEX;
    int CARBON_INDEX;

    QString stock_names[11];
    QMutex imageMutex;
    QImage* images[11];

    QImageWriter * writer;

    QRgb value;
    // number of different stocks
    int NUM_STOCKS;

    int hues[11];

    double sum_macro;
    double sum_phyto;
    double sum_herbivore;
    double sum_waterdecomp;
    double sum_seddecomp;
    double sum_sedconsum;
    double sum_consum;
    double sum_DOC;
    double sum_POC;
    double sum_detritus;
    double sum_carbon;

    int num_water_squares;

    QString total_carbon_csv;

} Globals;

extern Globals g;

void initialize_globals(void);

#endif
