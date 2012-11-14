#include "globals.h"

Globals g;

void initialize_globals(void){
    // Model variables
    g.hours = 0;	///< Represents 1 tick (should always be [0, sizeof(long)]
    g.COMPARE_MAX = 0.0; ///< represents the maximum of the x or y vector among all patches, this is used to calculate max step

    // GUI variables
    g.output_frequency = 0;
    g.current_day = 0; ///< Keeps track of how often output should be generated
    g.file_extension = "new";
    g.num_hydro_files = 0;
    g.gui_flow_corners_only = 0;
    g.gui_timestep_factor = 60;    ///< By how much are we speeding up the code? Increasing the factor will reduce the number of iterations required
    g.gui_days_to_run = 0;  ///< number of days to run the code
    g.gui_tss = 0.0;  ///< TSS
    g.gui_k_phyto = 0.4;  ///< k-phyto
    g.gui_k_macro = 0.4; ///< k-macro
    g.gui_sen_macro_coef = 0.08; ///< sen-macro-coef
    g.gui_resp_macro_coef = 0.04; ///< resp-macro-coef
    g.gui_macro_base_temp = 19.7; ///< macro-base-temp
    g.gui_macro_mass_max = 1000; ///< macro-mass-max
    g.gui_macro_vel_max = 1.0; ///< macro-vel-max
    g.gui_gross_macro_coef = 0.08; // gross-macro-coef

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


    g.max_waterdecomp = 6.26/24.0;
    g.max_seddecomp = 6.26/24.0;
    g.max_herbivore = 1.0/24.0;
    g.herbivore_egestion = 0.2;
    g.max_sedconsumer = 0.55/24.0;
    g.sedconsumer_egestion_seddecomp = 0.35;
    g.max_consum = 0.125/24;
    g.e_waterdecomp = 0.173/24;
    g.e_seddecomp = 0.173/24;
    g.e_herbivore = 0.4/24;
    g.e_sedconsumer = 0.01/24;
    g.sedconsumer_egestion_detritus = 0.9;
    g.e_consum = 0.0032/24;
    g.r_waterdecomp = 0.6/24;
    g.r_seddecomp = 0.6/24;
    g.r_herbivore = 0.08/24;
    g.r_sedconsumer = 0.04/24;
    g.r_consum = 0.0125/24;
    g.s_waterdecomp = 0.05/24;
    g.s_seddecomp = 0.05/24;
    g.s_herbivore = 0.01/24;
    g.s_sedconsumer = 0.01/24;
    g.s_consum = 0.002/24;
    g.consum_egestion = 0.2;

    // below variables are ripe for sensitivity analysis
    // prey parameters - Ai and Gi, coded 1 -> 0
    g.Ai_waterdecomp_DOC = 30.0;
    g.Ai_waterdecomp_POC = 30.0;
    g.Ai_Peri_DOC = 30.0;
    g.Ai_Peri_POC = 30.0;
    g.Ai_seddecomp_detritus = 0.6;
    g.Ai_herbivore_phyto = 20;
    g.Ai_herbivore_waterdecomp = 3.0;
    g.Ai_herbivore_peri = 3.0;
    g.Ai_sedconsumer_seddecomp = 3.0;
    g.Ai_sedconsumer_peri = 2.0;
    g.Ai_sedconsumer_detritus = 3.5;
    g.Ai_consum_herbivore = 3.5;
    g.Ai_consum_sedconsumer = 4.0;
    g.Gi_waterdecomp_DOC = 0.05;
    g.Gi_waterdecomp_POC = 0.05;
    g.Gi_Peri_DOC = 0.05;
    g.Gi_Peri_POC = 0.05;
    g.Gi_seddecomp_detritus = 0.005;
    g.Gi_herbivore_phyto = 0.01;
    g.Gi_herbivore_waterdecomp = 0.01;
    g.Gi_herbivore_peri = 0.01;
    g.Gi_sedconsumer_seddecomp = 0.02;
    g.Gi_sedconsumer_peri = 0.02;
    g.Gi_sedconsumer_detritus = 0.02;
    g.Gi_consum_herbivore = 0.025;
    g.Gi_consum_sedconsumer = 0.04;
    g.pref_waterdecomp_DOC = 0.5;
    g.pref_waterdecomp_POC = 0.5;
    g.pref_Peri_DOC = 0.5;
    g.pref_Peri_POC = 0.5;
    g.pref_seddecomp_detritus = 1.0;
    g.pref_herbivore_phyto = 0.7;
    g.pref_herbivore_waterdecomp = 0.15;
    g.pref_herbivore_peri = 0.15;
    g.pref_sedconsumer_seddecomp = 0.5;
    g.pref_sedconsumer_peri = 0.4;
    g.pref_sedconsumer_detritus = 0.1;
    g.pref_consum_herbivore = 0.7;
    g.pref_consum_sedconsumer = 0.3;

    // peri updated every timestep based on macro density  
    // density dependent crowding effects on linear scale - capped at Aj and Gj - coded 1->0  
    g.Aj_phyto = 10.0;
    g.Aj_waterdecomp = 1.2;
    g.Aj_seddecomp = 0.2;
    g.Aj_herbivore = 2.4;
    g.Aj_sedconsumer = 2.0;
    g.Aj_consum = 0.65;
    g.Gj_phyto = 100.0;
    g.Gj_waterdecomp = 20.0;
    g.Gj_seddecomp = 120.0;
    g.Gj_herbivore = 108.0;
    g.Gj_sedconsumer = 20.0;
    g.Gj_consum = 6.5;

    // set k-macro .4 -> taken from interface
    // set k-phyto .4 -> taken from interface
    g.k_herbivore = 0.2;
    g.k_POC = 0.2;

    g.theta = 1.072;

    //Slider variables
    g.macro_base_temp = 19.7;
    g.gross_macro_coef = 0.08;
    g.resp_macro_coef = 0.04;
    g.sen_macro_coef = 0.08;
    g.macro_mas_max = 1000.0;
    g.macro_vel_max = 1.0;

    // indices for the colorValues array for each stock
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

    g.stock_name[0] = "macro";
    g.stock_name[1] = "phyto";
    g.stock_name[2] = "herbivore";
    g.stock_name[3] = "waterdecomp";
    g.stock_name[4] = "seddecomp";
    g.stock_name[5] = "sedconsumer";
    g.stock_name[6] = "consum";
    g.stock_name[7] = "doc";
    g.stock_name[8] = "poc";
    g.stock_name[9] = "detritus";

    // number of different stocks
    g.NUM_STOCKS = 10;

}
