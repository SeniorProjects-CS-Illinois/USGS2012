#include "globals.h"

Globals g;

void initialize_globals(void){
    // Model variables
    g.hours = 0;	///< Represents 1 tick (should always be [0, sizeof(long)]
    g.COMPARE_MAX = 0.0; ///< represents the maximum of the x or y vector among all patches, this is used to calculate max step

    // GUI variables
    g.current_day = 0; ///< Keeps track of how often output should be generated
    g.file_extension = "new";
    g.num_hydro_files = 0;
    g.gui_days_to_run = 0;  ///< number of days to run the code

    // GUI input hydro maps and days for each map
    g.num_unique_files = 0;
    g.current_file_index = 0;

    g.hydro_changed = 0;  //boolean stating if the hydro map was changed
    g.temp_dif = 0;	///< The percent difference from 17 degrees Celsius. (Used in update_temp)
    g.par_dif = 0;	///< The percent difference in par. (Used in update_par)

    g.nan_trigger = 0;  ///< 1 if there is a NaN value in the DOC values 0 otherwise

    // convert ft to m from the SMS to .png scaling conversion
    g.patch_length = 30;
    g.max_area = 30*30;

    // max gwr/unit biomass; e- excretion->DOC; r- respiration; s- senecence(natural mortality); -egestion ->POC
    g.MAX_MACRO = 0.0;
    g.MAX_PHYTO = 0.0;
    g.MAX_HERBIVORE = 0.0;
    g.MAX_WATERDECOMP = 0.0;
    g.MAX_SEDDECOMP = 0.0;
    g.MAX_SEDCONSUMER = 0.0;
    g.MAX_CONSUM = 0.0;
    g.MAX_DOC = 0.0;
    g.MAX_POC = 0.0;
    g.MAX_DETRITUS = 0.0;

    // set k-macro .4 -> taken from interface
    // set k-phyto .4 -> taken from interface
    g.k_herbivore = 0.2;
    g.k_POC = 0.2;

    g.theta = 1.072;

    // indices for the array for each stock
    g.MACRO_INDEX = 0;
    g.PHYTO_INDEX = 1;
    g.HERBIVORE_INDEX = 2;
    g.WATERDECOMP_INDEX = 3;
    g.SEDDECOMP_INDEX = 4;
    g.SEDCONSUMER_INDEX = 5;
    g.CONSUM_INDEX = 6;
    g.DOC_INDEX = 7;
    g.POC_INDEX = 8;
    g.DETRITUS_INDEX = 9;
    g.CARBON_INDEX = 10;

    g.stock_names[0] = "macro";
    g.stock_names[1] = "phyto";
    g.stock_names[2] = "herbivore";
    g.stock_names[3] = "waterdecomp";
    g.stock_names[4] = "seddecomp";
    g.stock_names[5] = "sedconsumer";
    g.stock_names[6] = "consum";
    g.stock_names[7] = "doc";
    g.stock_names[8] = "poc";
    g.stock_names[9] = "detritus";
    g.stock_names[10] = "average";

    // number of different stocks
    g.NUM_STOCKS = 11;

    g.hues[0] = 120;
    g.hues[1] = 120;
    g.hues[2] = 300;
    g.hues[3] = 120;
    g.hues[4] = 240;
    g.hues[5] = 60;
    g.hues[6] = 300;
    g.hues[7] = 60;
    g.hues[8] = 240;
    g.hues[9] = 20;
    g.hues[10] = 30;

    g.sum_macro = 0.0;
    g.sum_phyto = 0.0;
    g.sum_herbivore = 0.0;
    g.sum_waterdecomp = 0.0;
    g.sum_seddecomp = 0.0;
    g.sum_sedconsum = 0.0;
    g.sum_consum = 0.0;
    g.sum_DOC = 0.0;
    g.sum_POC = 0.0;
    g.sum_detritus = 0.0;
    g.sum_carbon = 0.0;

    g.total_carbon_csv = "default";

    g.HOURS_PER_DAY = 24;

    g.num_water_squares = 0;
}
