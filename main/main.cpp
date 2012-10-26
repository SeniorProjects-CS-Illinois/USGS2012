#include "main.h"
#include <stdio.h>
#include "model/setup.cpp"
#include "model/go.cpp"
#include "model/patch.cpp"
#include "model/dump.cpp"
#include "model/cleanup.cpp"
#include "model/globals.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <QtGui/QApplication>
#include "view/mainwindow.h"

#ifdef NO_GUI
int main(int argc, char *argv[])
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
        if(strcmp(gui_filenames_array[i], gui_filenames_array[index]) == 0)
        return;
    }
    num_unique_files++;
}

void set_hydro_filenames(const char * filenames) {
    char * filenames_writable_copy = strdup(filenames); 
    char* filename;
    int index = 0;
    num_unique_files = 0;

    // First value howmany files the use selected in the GUI
    filename = strtok(filenames_writable_copy, "?");
    int fileSize = atoi(filename);
    gui_filenames_filesize = fileSize;
    num_hydro_files = fileSize;
    gui_filenames_array = (char**)malloc(fileSize*sizeof(char*));
    gui_days_array = (int*)malloc(fileSize*sizeof(int));
    hydromap_index_array = (int*)malloc(fileSize*sizeof(int));

    // Parse the file name if one exists
    while((filename = strtok(NULL, "?")) != NULL)
    {
        gui_filenames_array[index] = (char*)malloc((strlen(filename)+1)*sizeof(char));
        strcpy(gui_filenames_array[index],filename);
        count_unique_files(index);
        filename = strtok(NULL, "?");
        gui_days_array[index] = atoi(filename); //Parse howmany days to run current file
        index++;
    }
    check_filenames_array = (char**)malloc(num_unique_files*sizeof(char*));
    free(filenames_writable_copy);
}


void set_par_file(const char * filename) {
    strcpy(gui_photo_radiation_file, filename);
}

void set_timestep(int timestep) {
    gui_timestep_factor = timestep;
}

void set_temperature_file(const char * filename) {
    strcpy(gui_temperature_file, filename);
}


//TODO: Unstub this with c code for image output.
void output_image(void){
    return;
}

/**
 * Creates ./results/data and ./results/images if they don't exist.
 */
void create_output_dirs(void) {
    struct stat st = {0};

    if (stat("./results", &st) == -1) {
        #ifdef _WIN32
        mkdir("./results");
        #else
        mkdir("./results", 0775);
        #endif
    }
    if (stat("./results/data", &st) == -1) {
        #ifdef _WIN32
        mkdir("./results/data");
        #else
        mkdir("./results/data", 0775);
        #endif
    }
    if (stat("./results/images", &st) == -1) {
        #ifdef _WIN32
        mkdir("./results/images");
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

    gui_days_to_run = 0;
    for(index = 0; index < gui_filenames_filesize; index++)
    {
        printf("RUNNING FILE: %s FOR %d DAYS\n", gui_filenames_array[index], gui_days_array[index]);
        gui_days_to_run += gui_days_array[index];  //Set howmany days to run the new hydromap
        hydro_group = (hydromap_index_array[index] + 1); //Set the new hydromap that will run
        hydro_changed = 1;  //Confirm that a new hydro map has been loaded

        while( (day = (hours / 24)) < gui_days_to_run)
        {
            printf("Day: %d - Hour: %ld\n", (day+1), (hours)%24);
            go();
        }
    }

    cleanup();

    printf("\nPROCESSING COMPLETE\n");
}

void set_whichstock(const char * stock_name)
{
    strcpy(which_stock, stock_name);
}

void set_TSS(double tss)
{
    gui_tss = tss;
}

void set_macro_base_temp(double macro_base_temp)
{
    gui_macro_base_temp = macro_base_temp;
}



void set_gross_macro_coef(double gross_macro_coef)
{
    gui_gross_macro_coef = gross_macro_coef;
}

void set_resp_macro_coef(double resp_macro_coef)
{
    gui_resp_macro_coef = resp_macro_coef;
}

void set_sen_macro_coef(double sen_macro_coef)
{
    gui_sen_macro_coef = sen_macro_coef;
}

void set_macro_mass_max(double macro_mass_max)
{
    gui_macro_mass_max = macro_mass_max;
}

void set_macro_vel_max(double macro_vel_max)
{
    gui_macro_vel_max = macro_vel_max;
}

void set_k_phyto(double k_phyto)
{
    gui_k_phyto = k_phyto;
}
void set_k_macro(double k_macro)
{
    gui_k_macro = k_macro;
}


void set_output_frequency(int new_output_frequency)
{
    output_frequency = new_output_frequency;
}

void set_flow_corners(int flow_corners_only)
{
    gui_flow_corners_only = flow_corners_only;
}
