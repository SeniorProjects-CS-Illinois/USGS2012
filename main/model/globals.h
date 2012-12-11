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
    int output_frequency;
    int current_day; ///< Keeps track of how often output should be generated
    const char* file_extension;

    QString gui_photo_radiation_file;
    QString gui_temperature_file;

    int gui_flow_corners_only;
    int gui_timestep_factor;    // By how much are we speeding up the code? Increasing the factor will reduce the number of iterations required
    int gui_days_to_run;  // number of days to run the code
    double gui_tss;  // TSS
    double gui_k_phyto;  // k-phyto
    double gui_k_macro; // k-macro
    double gui_sen_macro_coef; // sen-macro-coef
    double gui_resp_macro_coef; // resp-macro-coef
    double gui_macro_base_temp; // macro-base-temp
    double gui_macro_mass_max; // macro-mass-max
    double gui_macro_vel_max; // macro-vel-max
    double gui_gross_macro_coef; // gross-macro-coef
    QString which_stock; // which-stock?

    // GUI input hydro maps and days for each map
    QStringList gui_filenames_list;
    QStringList uniqueHydroFilenames;
    std::vector<int> gui_days_vector;
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

    double max_waterdecomp;
    double max_seddecomp;
    double max_herbivore;
    double herbivore_egestion;
    double max_sedconsumer;
    double sedconsumer_egestion_seddecomp;
    double max_consum;
    double e_macro;
    double e_phyto;
    double e_waterdecomp;
    double e_seddecomp;
    double e_herbivore;
    double e_sedconsumer;
    double sedconsumer_egestion_detritus;
    double e_consum;
    double r_phyto;
    double r_waterdecomp;
    double r_seddecomp;
    double r_herbivore;
    double r_sedconsumer;
    double r_consum;
    double s_phyto;
    double s_waterdecomp;
    double s_seddecomp;
    double s_herbivore;
    double s_sedconsumer;
    double s_consum;
    double consum_egestion;

    // below variables are ripe for sensitivity analysis
    // prey parameters - Ai and Gi, coded 1 -> 0
    double Ai_waterdecomp_DOC;
    double Ai_waterdecomp_POC;
    double Ai_Peri_DOC;
    double Ai_Peri_POC;
    double Ai_seddecomp_detritus;
    double Ai_herbivore_phyto;
    double Ai_herbivore_waterdecomp;
    double Ai_herbivore_peri;
    double Ai_sedconsumer_seddecomp;
    double Ai_sedconsumer_peri;
    double Ai_sedconsumer_detritus;
    double Ai_consum_herbivore;
    double Ai_consum_sedconsumer;
    double Gi_waterdecomp_DOC;
    double Gi_waterdecomp_POC;
    double Gi_Peri_DOC;
    double Gi_Peri_POC;
    double Gi_seddecomp_detritus;
    double Gi_herbivore_phyto;
    double Gi_herbivore_waterdecomp;
    double Gi_herbivore_peri;
    double Gi_sedconsumer_seddecomp;
    double Gi_sedconsumer_peri;
    double Gi_sedconsumer_detritus;
    double Gi_consum_herbivore;
    double Gi_consum_sedconsumer;
    double pref_waterdecomp_DOC;
    double pref_waterdecomp_POC;
    double pref_Peri_DOC;
    double pref_Peri_POC;
    double pref_seddecomp_detritus;
    double pref_herbivore_phyto;
    double pref_herbivore_waterdecomp;
    double pref_herbivore_peri;
    double pref_sedconsumer_seddecomp;
    double pref_sedconsumer_peri;
    double pref_sedconsumer_detritus;
    double pref_consum_herbivore;
    double pref_consum_sedconsumer;

    // peri updated every timestep based on macro density  
    // density dependent crowding effects on linear scale - capped at Aj and Gj - coded 1->0  
    double Aj_phyto;
    double Aj_waterdecomp;
    double Aj_seddecomp;
    double Aj_herbivore;
    double Aj_sedconsumer;
    double Aj_consum;
    double Aj_peri;
    double Gj_phyto;
    double Gj_waterdecomp;
    double Gj_seddecomp;
    double Gj_herbivore;
    double Gj_sedconsumer;
    double Gj_consum;
    double Gj_peri;

    // set k-macro .4 -> taken from interface
    // set k-phyto .4 -> taken from interface
    double k_herbivore;
    double k_POC;

    double theta;

    //temperatue dependent coefficient for aquatic plants
    double Q10;
    //Slider variables
    double macro_base_temp;
    double gross_macro_coef;
    double resp_macro_coef;
    double sen_macro_coef;
    double macro_mas_max;
    double macro_vel_max;

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

    QString stock_names[10];
    QMutex imageMutex;
    QImage* images[10];

    QImageWriter * writer;

    QRgb value;
    // number of different stocks
    int NUM_STOCKS;

    int hues[10];
} Globals;

extern Globals g;

void initialize_globals(void);

#endif
