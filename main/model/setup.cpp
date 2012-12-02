#include "setup.h"


/**
 * Calls the helper functions import_hydro and setup_environmentals
 */
void setup() {
    reset_globals();
    get_unique_hydrofiles();
    find_map_sizes();
    init_patches();
    init_color_values();
    import_hydro();
    setup_environmentals();
    setup_stocks();
}

/**
 * Resets all the values in globals.h
 */
void reset_globals() {
    g.MAP_WIDTH = 0;
    g.MAP_HEIGHT = 0;
    g.hours = 0;
    g.COMPARE_MAX = 0.0;

    g.current_file_index = 0;

    g.temp_dif = 0.0;
    g.par_dif = 0.0;

    g.nan_trigger = 0;

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
    g.max_consum = 0.125/24.0;
    g.e_waterdecomp = 0.173/24.0;
    g.e_seddecomp = 0.173/24.0;
    g.e_herbivore = 0.4/24.0;
    g.e_sedconsumer = 0.01/24.0;
    g.sedconsumer_egestion_detritus = 0.9;
    g.e_consum = 0.0032/24.0;
    g.r_waterdecomp = 0.6/24.0;
    g.r_seddecomp = 0.6/24.0;
    g.r_herbivore = 0.08/24.0;
    g.r_sedconsumer = 0.04/24.0;
    g.r_consum = 0.0125/24.0;
    g.s_waterdecomp = 0.05/24.0;
    g.s_seddecomp = 0.05/24.0;
    g.s_herbivore = 0.01/24.0;
    g.s_sedconsumer = 0.01/24.0;
    g.s_consum = 0.002/24.0;
    g.consum_egestion = 0.2;

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

    g.k_herbivore = 0.2;
    g.k_POC = 0.2;

    g.theta = 1.072;

    g.macro_base_temp = 19.7;
    g.gross_macro_coef = 0.08;
    g.resp_macro_coef = 0.04;
    g.sen_macro_coef = 0.08;
    g.macro_mas_max = 1000.0;
    g.macro_vel_max = 1.0;
}

void get_unique_hydrofiles(){
    //Get unique hydrofiles
    g.uniqueHydroFilenames = g.gui_filenames_list;
    g.uniqueHydroFilenames.removeDuplicates();
    g.num_unique_files = g.uniqueHydroFilenames.size();
}

/**
 * Opens the first hydro-map i.e 10k-map and finds the maximum pxcor and
 * the maximum pycor, we assign these values to MAP_WIDTH and MAP_HEIGHT
 */
void find_map_sizes() {
    int max_map_width = 0;
    int max_map_height = 0;

    int index;
    for(index = 0; index < g.uniqueHydroFilenames.size(); index++) {
        FILE* file = fopen(g.uniqueHydroFilenames[index].toStdString().c_str(), "r");
        if (file == NULL) {
            fputs("error opening the hydro map", stderr);
            exit(-1);
        }

        find_map_width_height(file); // find the width and height of the maps
        if(g.MAP_WIDTH > max_map_width) {
            max_map_width = g.MAP_WIDTH;
        }
        if(g.MAP_HEIGHT > max_map_height) {
            max_map_height = g.MAP_HEIGHT;
        }

        fclose(file);
    }

    g.MAP_WIDTH = max_map_width;
    g.MAP_HEIGHT = max_map_height;

    //TODO: Figure out why this is in this function.
    for(int i=0; i < g.NUM_STOCKS; i++) {
        g.images[i] = new QImage(g.MAP_WIDTH, g.MAP_HEIGHT, QImage::Format_RGB444);
    }
}


/**
 * Reads a hydro_file finds the biggest pycor and pxcor and assigns them to MAP_WIDTH and MAP_HEIGHT
 * @param hydro_file the hydrolic file with data regarding patches
 */
void find_map_width_height(FILE* hydro_file) {
    int patch_info_size = 6;    // first line in the file, pxcor/pycor/depth/px-vector/py-vector/velocity
    const int word_size = 100;

    char word[word_size];
    word[0] = '\0';

    int max_x = 0;
    int max_y = 0;
    int counter = 0;
    while(fscanf(hydro_file, "%s", word) != EOF) {
        // pxcor
        if(counter%patch_info_size == 0) {
            int value = atoi(word);
            if(value > max_x) {
                max_x = value;
            }
        }        
        // pycor
        else if(counter%patch_info_size == 1) {
            int value = atoi(word);
            if(value > max_y) {
                max_y = value;
            }
        }
        counter++;
    }

    g.MAP_WIDTH = max_x+1;
    g.MAP_HEIGHT = max_y+1;
}

void init_patch_values(int col, int row) {
    patches[col][row].max_vector = 0.0;
    patches[col][row].pxcor = col;
    patches[col][row].pycor = row;
    patches[col][row].pcolor = 0;
    patches[col][row].current_depth = 0;
    patches[col][row].px_vector = 0.0;
    patches[col][row].py_vector = 0.0;
    patches[col][row].max_vector = 0.0;
    patches[col][row].depth = 0.0;
    patches[col][row].current_depth = 0.0;
    patches[col][row].velocity = 0.0;
    patches[col][row].aqa_point = 0;
    patches[col][row].waterdecomp_doc_prey_limitation = 0.0;
    patches[col][row].waterdecomp_poc_prey_limitation = 0.0;
    patches[col][row].peri_doc_prey_limitation = 0.0;
    patches[col][row].peri_poc_prey_limitation = 0.0;
    patches[col][row].seddecomp_detritus_prey_limitation = 0.0;
    patches[col][row].herbivore_phyto_prey_limitation = 0.0;
    patches[col][row].herbivore_waterdecomp_prey_limitation = 0.0;
    patches[col][row].herbivore_peri_prey_limitation = 0.0;
    patches[col][row].sedconsumer_seddecomp_prey_limitation = 0.0;
    patches[col][row].sedconsumer_peri_prey_limitation = 0.0;
    patches[col][row].sedconsumer_detritus_prey_limitation = 0.0;
    patches[col][row].consum_herbivore_prey_limitation = 0.0;
    patches[col][row].consum_sedconsumer_prey_limitation = 0.0;

    patches[col][row].peri_space_limitation = 0.0;
    patches[col][row].waterdecomp_space_limitation = 0.0;
    patches[col][row].seddecomp_space_limitation = 0.0;
    patches[col][row].herbivore_space_limitation = 0.0;
    patches[col][row].sedconsumer_space_limitation = 0.0;
    patches[col][row].consum_space_limitation = 0.0;
    patches[col][row].assimilation = 0.0;
    patches[col][row].detritus = 0.0;
    patches[col][row].DOC = 0.0;
    patches[col][row].POC = 0.0;
    patches[col][row].waterdecomp = 0.0;
    patches[col][row].seddecomp = 0.0;
    patches[col][row].macro = 0.0;
    patches[col][row].phyto = 0.0;
    patches[col][row].herbivore = 0.0;
    patches[col][row].sedconsumer = 0.0;
    patches[col][row].peri = 0.0;
    patches[col][row].consum = 0.0;
    patches[col][row].bottom_light = 0.0;
    patches[col][row].consumer = 0.0;
    patches[col][row].consum_consumption = 0.0;
    patches[col][row].consum_ingest_herbivore = 0.0;
    patches[col][row].consum_pred_herbivore = 0.0;
    patches[col][row].consum_ingest_sedconsumer = 0.0;
    patches[col][row].consum_pred_sedconsumer = 0.0;
    patches[col][row].consum_excretion = 0.0;
    patches[col][row].consum_sda = 0.0;
    patches[col][row].consum_senescence = 0.0;
    patches[col][row].consum_respiration = 0.0;
    patches[col][row].consum_growth = 0.0;
    patches[col][row].detritus_growth = 0.0;
    patches[col][row].detritus_POC_transfer = 0.0;
    patches[col][row].seddecomp_pred_detritus = 0.0;
    patches[col][row].sedconsumer_pred_detritus = 0.0;
    patches[col][row].direction = 0.0;
    patches[col][row].DOC_growth = 0.0;
    patches[col][row].DOC_pred = 0.0;
    patches[col][row].egestion = 0.0;
    patches[col][row].excretion = 0.0;
    patches[col][row].excretion_phyto = 0.0;
    patches[col][row].flocculation = 0.0;
    patches[col][row].gross_photo = 0.0;
    patches[col][row].gross_photo_macro = 0.0;
    patches[col][row].gross_photo_phyto = 0.0;
    patches[col][row].growth_herbivore = 0.0;
    patches[col][row].growth_detritus = 0.0;
    patches[col][row].growth_macro = 0.0;
    patches[col][row].growth_sedconsumer = 0.0;
    patches[col][row].growth_phyto = 0.0;
    patches[col][row].growth_waterdecomp = 0.0;
    patches[col][row].herbivore_consumption = 0.0;
    patches[col][row].herbivore_ingest_peri = 0.0;
    patches[col][row].herbivore_pred_peri = 0.0;
    patches[col][row].herbivore_ingest_phyto = 0.0;
    patches[col][row].herbivore_pred_phyto = 0.0;
    patches[col][row].herbivore_ingest_waterdecomp = 0.0;
    patches[col][row].herbivore_pred_waterdecomp = 0.0;
    patches[col][row].herbivore_excretion = 0.0;
    patches[col][row].herbivore_sda = 0.0;
    patches[col][row].herbivore_senescence = 0.0;
    patches[col][row].herbivore_respiration = 0.0;
    patches[col][row].herbivore_growth = 0.0;
    patches[col][row].K = 0.0;
    patches[col][row].large_death = 0.0;
    patches[col][row].light = 0.0;
    patches[col][row].light_k = 0.0;
    patches[col][row].macro_death = 0.0;
    patches[col][row].macro_exudation = 0.0;
    patches[col][row].micro_death = 0.0;
    patches[col][row].phyto_maximum_growth_rate = 0.0;
    patches[col][row].phyto_pred = 0.0;
    patches[col][row].POC_detritus_transfer = 0.0;
    patches[col][row].POC_growth = 0.0;
    patches[col][row].POC_pred = 0.0;
    patches[col][row].phyto_density = 0.0;
    patches[col][row].peri_ingest_doc = 0.0;
    patches[col][row].peri_pred_doc = 0.0;
    patches[col][row].peri_ingest_poc = 0.0;
    patches[col][row].peri_pred_poc = 0.0;
    patches[col][row].peri_respiration = 0.0;
    patches[col][row].peri_excretion = 0.0;
    patches[col][row].peri_senescence = 0.0;
    patches[col][row].senescence = 0.0;
    patches[col][row].scouring = 0.0;
    patches[col][row].small_death = 0.0;
    patches[col][row].respiration = 0.0;
    patches[col][row].respiration_macro = 0.0;
    patches[col][row].respiration_phyto = 0.0;
    patches[col][row].scouring_macro = 0.0;
    patches[col][row].sedconsumer_ingest_peri = 0.0;
    patches[col][row].sedconsumer_pred_peri = 0.0;
    patches[col][row].senescence_macro = 0.0;
    patches[col][row].senescence_phyto = 0.0;
    patches[col][row].sedconsumer_consumption = 0.0;
    patches[col][row].sedconsumer_ingest_detritus = 0.0;
    patches[col][row].sedconsumer_ingest_seddecomp = 0.0;
    patches[col][row].sedconsumer_pred_seddecomp = 0.0;
    patches[col][row].sedconsumer_excretion = 0.0;
    patches[col][row].sedconsumer_egestion = 0.0;
    patches[col][row].sedconsumer_senescence = 0.0;
    patches[col][row].sedconsumer_respiration = 0.0;
    patches[col][row].sedconsumer_growth = 0.0;
    patches[col][row].seddecomp_consumption = 0.0;
    patches[col][row].seddecomp_ingest_detritus = 0.0;
    patches[col][row].seddecomp_excretion = 0.0;
    patches[col][row].seddecomp_growth = 0.0;
    patches[col][row].seddcomp_ingest_peri = 0.0;
    patches[col][row].seddecomp_pred_peri = 0.0;
    patches[col][row].seddecomp_respiration = 0.0;
    patches[col][row].seddecomp_senescence = 0.0;
    patches[col][row].velpoc = 0.0;
    patches[col][row].waterdecomp_consumption = 0.0;
    patches[col][row].waterdecomp_ingest_doc = 0.0;
    patches[col][row].waterdecomp_sda = 0.0;
    patches[col][row].waterdecomp_excretion = 0.0;
    patches[col][row].waterdecomp_ingest_poc = 0.0;
    patches[col][row].waterdecomp_pred_doc = 0.0;
    patches[col][row].waterdecomp_pred_poc = 0.0;
    patches[col][row].waterdecomp_respiration = 0.0;
    patches[col][row].waterdecomp_senescence = 0.0;
    patches[col][row].turbidity = 0.0;

    patches[col][row].available = (int *)malloc(g.num_unique_files*sizeof(int));        
    patches[col][row].pxv_list = (double *)malloc(g.num_unique_files*sizeof(double));
    patches[col][row].pyv_list = (double *)malloc(g.num_unique_files*sizeof(double));
    patches[col][row].depth_list = (double *)malloc(g.num_unique_files*sizeof(double));
    patches[col][row].v_list = (double *)malloc(g.num_unique_files*sizeof(double));
    int index;
    for(index = 0; index < g.num_unique_files; index++) {
        patches[col][row].pxv_list[index] = 0.0;
        patches[col][row].available[index] = 0;
        patches[col][row].pyv_list[index] = 0.0;
        patches[col][row].depth_list[index] = 0.0;
        patches[col][row].v_list[index] = 0.0;
    }
}

/**
 * Creates the 2D array of patches
 */
void init_patches() {
    // initialize the patches
    int row = 0;
    int col = 0;

    g.covered_area = (int*)malloc(g.num_unique_files*sizeof(int));
    g.uncovered_area = (int*)malloc(g.num_unique_files*sizeof(int));
    patches = (patch **)malloc(g.MAP_WIDTH*sizeof(patch*));
    for(col = 0; col < g.MAP_WIDTH; col++) {
        patches[col] = (patch *)malloc(g.MAP_HEIGHT*sizeof(patch));
    }

    // initialize the arrays for each patch
    for(col = 0; col < g.MAP_WIDTH; col++) {
        for(row = 0; row < g.MAP_HEIGHT; row++) {
            init_patch_values(col, row);
        }
    }
}

/**
 * Creates the 2D array of colors
 */
void init_color_values() {
    int row = 0;
    int col = 0;
    int i = 0;

    //initialize colors corresponding to each patch
    for (i = 0; i < g.NUM_STOCKS; i++) {
        for( col = 0; col < g.MAP_WIDTH; col++) {
            for(row = 0; row < g.MAP_HEIGHT; row++) {
                g.value = qRgb(235, 235, 235);
                g.images[i]->setPixel(col, row, g.value);
            }
        }
    }
}


/**
 * TODO:  Replace this function and respective variables with a hash table...
 */
std::vector<int> map_hydro_files(QStringList & allHydroFiles, QStringList & uniqueHydroFiles){
    std::vector<int> mappingToUniqueFiles;
    mappingToUniqueFiles.resize( allHydroFiles.size() );
    for(int i = 0; i < allHydroFiles.size(); i++){
        mappingToUniqueFiles[i] = uniqueHydroFiles.indexOf( allHydroFiles[i] );
    }
    return mappingToUniqueFiles;
}

/**
 * Reads the Hydro map files and sets up the proper (x,y) patches
 * Input is in the form of "pxcor pycor depth px-vector py-vector velocity"
 * and this word formation must be the first line in the file.
 */
void import_hydro() {
    g.hydromap_index_vector = map_hydro_files(g.gui_filenames_list, g.uniqueHydroFilenames);

    for(int i = 0;i < g.uniqueHydroFilenames.size(); i++) {
        QFile hydroFile( g.uniqueHydroFilenames[i] );
        if( !hydroFile.open(QIODevice::ReadOnly | QIODevice::Text) ) {
            printf("Failed to open the hydromap");
            exit(1);
        }

        int covered_cells = 0;
        int uncovered_cells = 0;

        QString hydroFileText = hydroFile.readAll();
        QStringList hydroFileData = hydroFileText.split(" ");
        for(int index = 6; index < hydroFileData.size(); index += 6){

            int patch_x             = hydroFileData[index].toInt();
            int patch_y             = hydroFileData[index + 1].toInt();
            double patch_depth      = hydroFileData[index + 2].toDouble();
            double patch_px_vector  = hydroFileData[index + 3].toDouble();
            double patch_py_vector  = hydroFileData[index + 4].toDouble();
            double patch_velocity   = hydroFileData[index + 5].toDouble();

            patches[patch_x][patch_y].available[g.current_file_index] = 1;
            patches[patch_x][patch_y].pxcor = patch_x;
            patches[patch_x][patch_y].pycor = patch_y;
            patches[patch_x][patch_y].pxv_list[g.current_file_index] = patch_px_vector;
            patches[patch_x][patch_y].pyv_list[g.current_file_index] = patch_py_vector;
            patches[patch_x][patch_y].v_list[g.current_file_index] = patch_velocity;
            patches[patch_x][patch_y].aqa_point = -999;
            patches[patch_x][patch_y].depth_list[g.current_file_index] = patch_depth;
            covered_cells++;
        }

        uncovered_cells = g.MAP_WIDTH*g.MAP_HEIGHT - covered_cells;
        g.covered_area[g.current_file_index] = g.max_area*covered_cells;
        g.uncovered_area[g.current_file_index] = g.max_area*uncovered_cells;
        g.current_file_index++;
        hydroFile.close();
    }
}


/**
 * Reads from files the initial discharge (daily) and initial radiation (hourly) values and then imports the maps based on the discharge value
 */
void setup_environmentals() {
    g.temp_dif = 0;
    g.par_dif = 0;
    set_photo_radiation();
    set_temperature();
}

/*
 * Reads the "par.txt" file and initializes the photo_radiation array variables
 */
void set_photo_radiation() {
    char* filename = g.gui_photo_radiation_file;

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror ("Error opening photo_radiation file");
    }

    char line[256];
    int count = 0;

    while (fgets(line, 256, file) != NULL) {// Get number of elements in file
        count++;
    }

    g.photo_radiation_data = (int*)malloc(count * sizeof(int));

    rewind(file);
    count = 0;

    while (fgets(line, 256, file) != NULL) {// Populate discharge array
        int value = atoi(line);
        g.photo_radiation_data[count] = value;
        count++;
    }

    g.photo_radiation_index = 0;	// Initialize photo_radiation index to represent current index
    g.photo_radiation = g.photo_radiation_data[g.photo_radiation_index];	// Assign first value of photo_radiation

    fclose(file);
}


/**
 * Reads the "water-temp.txt" file and initializes the temperature array variable
 */
void set_temperature() {
    char* filename = g.gui_temperature_file;

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror ("Error opening water-temperature file");
    }

    char line[256];
    int count = 0;

    while (fgets(line, 256, file) != NULL) {// Get number of elements in file
        count++;
    }

    g.temperature_data = (double*)malloc(count * sizeof(double));

    rewind(file);

    count = 0;

    while (fgets(line, 256, file) != NULL) {// Populate temperature array
        double value = atof(line);
        g.temperature_data[count] = value;
        count++;
    }

    g.temperature_index = 0;	// Initialize temperature index to represent current index
    g.temperature = g.temperature_data[g.temperature_index];	// Assign first value of temperature

    fclose(file);
}


/**
 * Sets up the 10 stocks, currently has default values
 */
void setup_stocks() {
    set_stocks(1.0, 10.0, 10.0, 1.0, 1.0, 1.0, 10.0, 10.0, 1.0, 0.1);
}

/**
 * Sets up the 10 stocks to input values
 */
void set_stocks(float macro, float phyto, float waterdecomp, float seddecomp,
        float herbivore, float sedconsumer, float doc, float poc,
        float detritus, float consum) {
    int x, y;
    for(x = 0; x < g.MAP_WIDTH; x++) {
        for(y = 0; y < g.MAP_HEIGHT; y++) {
            if(patches[x][y].depth > 0.0) {
                patches[x][y].macro = macro;
                patches[x][y].phyto = phyto;
                patches[x][y].waterdecomp = waterdecomp;
                patches[x][y].seddecomp = seddecomp;
                patches[x][y].herbivore = herbivore;
                patches[x][y].sedconsumer = sedconsumer;
                patches[x][y].DOC = doc;
                patches[x][y].POC = poc;
                patches[x][y].detritus = detritus;
                patches[x][y].consum = consum;
            }
        }
    }
}
