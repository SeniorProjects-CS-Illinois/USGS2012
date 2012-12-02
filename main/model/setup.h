#ifndef _SETUP
#define _SETUP

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "globals.h"
#include "go.h"
#include "color.h"

#include <QString>
#include <QStringList>
#include <QDir>
#include <QFile>

#include <iostream>

/**
 * Calls the helper functions import_hydro and setup_environmentals
 */
void setup();

/**
 * Resets all the values in globals.h
 */
void reset_globals();

/**
 * Determines the unique hydrofiles.
 */
void get_unique_hydrofiles();

/**
 * Opens the first hydro-map i.e 10k-map and finds the maximum pxcor and
 * the maximum pycor, we assign these values to MAP_WIDTH and MAP_HEIGHT
 */
void find_map_sizes();

/**
 * Reads a hydro_file finds the biggest pycor and pxcor and assigns them to MAP_WIDTH and MAP_HEIGHT
 * @param hydro_file
 */
void find_map_width_height(FILE* hydro_file);

/**
 * Initializes every value in the specified patch
 * @param col
 * @param row
 */
void init_patch_values(int col, int row);

/**
 * Creates the 2D array of patches
 */
void init_patches();

/**
 * Creates the 2D array of colors
 */
void init_color_values();

/**
 * Map's each hydrofile to the index of its unique hydrofile.
 */
std::vector<int> map_hydro_files(QStringList & allHydroFiles, QStringList & uniqueHydroFiles);

/**
 * Reads the Hydo map files and sets up the proper (x,y) patches
 * Input in the form of "pxcor pycor depth px-vector py-vector velocity"
 * and this must be the first line in the file.
 */
void import_hydro();

/**
 * Reads from files the initial discharge (daily) and initial radiation (hourly) values and then imports the maps based on the discharge value
 */
void setup_environmentals();

/**
 * Reads the "par.txt" file and initializes the photo_radiation array variables
 */
void set_photo_radiation();

/**
 * Reads the "water-temp.txt" file and initializes the temperature array variable
 */
void set_temperature();

/**
 * Sets up the 10 stocks, currently has default values
 */
void setup_stocks();

/**
 * Sets up the 10 stocks to input values
 */
void set_stocks(float macro, float phyto, float waterdecomp, float seddecomp, float herbivore,
        float sedconsumer, float doc, float poc, float detritus, float consum);
#endif
