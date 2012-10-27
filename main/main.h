#ifndef MAIN_H
#define MAIN_H

#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <QtGui/QApplication>

#include "model/globals.h"
#include "model/setup.h"
#include "model/patch.h"
#include "model/go.h"
#include "model/dump.h"
#include "model/cleanup.h"
#include "view/mainwindow.h"

/* Outputs an image */
void output_image();

void count_unique_files(int index);

//Functions for configuring the model
void set_hydro_filenames(const char * filenames);
void set_par_file(const char * filename);
void set_timestep(int timestep);
void set_temperature_file(const char * filename);
void set_whichstock(const char * stock_name);
void set_TSS(double tss);
void set_macro_base_temp(double macro_base_temp);
void set_gross_macro_coef(double gross_macro_coef);
void set_resp_macro_coef(double resp_macro_coef);
void set_sen_macro_coef(double sen_macro_coef);
void set_macro_mass_max(double macro_mass_max);
void set_macro_vel_max(double macro_vel_max);
void set_k_phyto(double k_phyto);
void set_k_macro(double k_macro);
void set_output_frequency(int new_output_frequency);
void set_flow_corners(int flow_corners_only);

//Adds a location for the images and csv files.
void create_output_dirs();

//Runs the model
void go_command(void);

#endif
