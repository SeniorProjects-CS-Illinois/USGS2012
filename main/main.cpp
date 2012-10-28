#include "main.h"
//#include <direct.h>
//#include <unistd.h>

#ifdef NO_GUI
int main(int argc, char *argv[]) {
    initialize_globals();

    //These values are what was used in the original Python GUI by default.  Hard coding for now.
    set_hydro_filenames("1?model/data/HydroSets/100k-new.txt?2?");
    set_par_file("model/data/Environmentals/par.txt");
    set_timestep(1);
    set_temperature_file("model/data/Environmentals/water-temp.txt");
    set_whichstock("phyto");
    set_TSS(10.0);
    set_macro_base_temp(19.7);
    set_gross_macro_coef(0.08);
    set_resp_macro_coef(0.04);
    set_sen_macro_coef(0.08);
    set_macro_mass_max(1000.0);
    set_macro_vel_max(1.0);
    set_k_phyto(0.01);
    set_k_macro(0.01);
    set_output_frequency(1);
    set_flow_corners(0);

    create_output_dirs();

    go_command();
    return 0;
}
#else
//TODO: Program entry point for QT GUI goes here.
int main(int argc, char *argv[])
{
    initialize_globals();

    QApplication a(argc, argv);
    MainWindow w;
    w.setToolTips();
    w.show();

    return a.exec();
}

#endif


void count_unique_files(int index)
{
    int i;
    for(i = 0; i < index; i++)
    {
        if(strcmp(g.gui_filenames_array[i], g.gui_filenames_array[index]) == 0)
        return;
    }
    g.num_unique_files++;
}


//TODO: Re-write this function to use C++ strings
//TODO: Replace strtok with an equivilent C++ function of our design
void set_hydro_filenames(const char * filenames)
{
    size_t filenames_len = strlen(filenames);
    char * filenames_writable_copy = (char *)malloc(filenames_len * sizeof(char));
    strncpy(filenames_writable_copy, filenames, filenames_len);
    char* filename;
    int index = 0;
    g.num_unique_files = 0;

    // First value howmany files the use selected in the GUI
    filename = strtok(filenames_writable_copy, "?");
    int fileSize = atoi(filename);
    g.gui_filenames_filesize = fileSize;
    g.num_hydro_files = fileSize;
    g.gui_filenames_array = (char**)malloc(fileSize*sizeof(char*));
    g.gui_days_array = (int*)malloc(fileSize*sizeof(int));
    g.hydromap_index_array = (int*)malloc(fileSize*sizeof(int));

    // Parse the file name if one exists
    while((filename = strtok(NULL, "?")) != NULL)
    {
        size_t len = (strlen(filename)+1);
        g.gui_filenames_array[index] = (char*)malloc(len*sizeof(char));
        strncpy(g.gui_filenames_array[index], filename, len);
        count_unique_files(index);
        filename = strtok(NULL, "?");
        g.gui_days_array[index] = atoi(filename); //Parse howmany days to run current file
        index++;
    }
    g.check_filenames_array = (char**)malloc(g.num_unique_files*sizeof(char*));
    free(filenames_writable_copy);
}


void set_par_file(const char * filename)
{
    size_t len = strlen(filename) + 1;
    strncpy(g.gui_photo_radiation_file, filename, len);
}

void set_timestep(int timestep)
{
    g.gui_timestep_factor = timestep;
}

void set_temperature_file(const char * filename)
{
    size_t len = strlen(filename) + 1;
    strncpy(g.gui_temperature_file, filename, len);
}


//TODO: Unstub this with C/C++ code for image output.
void output_image(void)
{
    return;
}

/**
 * Creates ./results/data and ./results/images if they don't exist.
 */
void create_output_dirs(void) {
    struct stat st = {0};

    if (stat("./results", &st) == -1) {
        #ifdef _WIN32
        _mkdir("./results");
        #else
        mkdir("./results", 0775);
        #endif
    }
    if (stat("./results/data", &st) == -1) {
        #ifdef _WIN32
        _mkdir("./results/data");
        #else
        mkdir("./results/data", 0775);
        #endif
    }
    if (stat("./results/images", &st) == -1) {
        #ifdef _WIN32
        _mkdir("./results/images");
        #else
        mkdir("./results/images", 0775);
        #endif
    }
}

//XXX: Not sure what the now removed build_data function
//     was doing aside from creating output dirs.
void go_command(void) {
    int day;
    int index;
    setup();

    g.gui_days_to_run = 0;
    for(index = 0; index < g.gui_filenames_filesize; index++)
    {
        printf("RUNNING FILE: %s FOR %d DAYS\n", g.gui_filenames_array[index], g.gui_days_array[index]);
        g.gui_days_to_run += g.gui_days_array[index];  //Set howmany days to run the new hydromap
        g.hydro_group = (g.hydromap_index_array[index] + 1); //Set the new hydromap that will run
        g.hydro_changed = 1;  //Confirm that a new hydro map has been loaded

        while( (day = (g.hours / 24)) < g.gui_days_to_run)
        {
            printf("Day: %d - Hour: %ld\n", (day+1), (g.hours)%24);
            go();
        }
    }

    cleanup();

    printf("\nPROCESSING COMPLETE\n");
}

void set_whichstock(const char * stock_name)
{
    size_t len = strlen(stock_name);
    strncpy(g.which_stock, stock_name, len);
}

void set_TSS(double tss)
{
    g.gui_tss = tss;
}

void set_macro_base_temp(double macro_base_temp)
{
    g.gui_macro_base_temp = macro_base_temp;
}



void set_gross_macro_coef(double gross_macro_coef)
{
    g.gui_gross_macro_coef = gross_macro_coef;
}

void set_resp_macro_coef(double resp_macro_coef)
{
    g.gui_resp_macro_coef = resp_macro_coef;
}

void set_sen_macro_coef(double sen_macro_coef)
{
    g.gui_sen_macro_coef = sen_macro_coef;
}

void set_macro_mass_max(double macro_mass_max)
{
    g.gui_macro_mass_max = macro_mass_max;
}

void set_macro_vel_max(double macro_vel_max)
{
    g.gui_macro_vel_max = macro_vel_max;
}

void set_k_phyto(double k_phyto)
{
    g.gui_k_phyto = k_phyto;
}
void set_k_macro(double k_macro)
{
    g.gui_k_macro = k_macro;
}


void set_output_frequency(int new_output_frequency)
{
    g.output_frequency = new_output_frequency;
}

void set_flow_corners(int flow_corners_only)
{
    g.gui_flow_corners_only = flow_corners_only;
}
