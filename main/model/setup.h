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
#include <QTextStream>

#include <iostream>

/**
 * \brief Calls the helper functions import_hydro and setup_environmentals
 */
void setup();

/**
 * TODO This is a temp function until references the globals begin set can be eliminated.
 *
 * \brief Sets the number of hydrofiles.
 */
void set_num_hydrofiles(void);

/**
 * \brief Resets all the values in globals.h
 */
void reset_globals();

/**
 * \brief Determines the unique hydrofiles.
 */
void get_unique_hydrofiles();

/**
 * \brief Opens the first hydro-map i.e 10k-map and finds the maximum pxcor and
 * the maximum pycor, we assign these values to MAP_WIDTH and MAP_HEIGHT
 */
void find_map_sizes();

/**
 * \brief Reads a hydro_file finds the biggest pycor and pxcor and assigns them to MAP_WIDTH and MAP_HEIGHT
 * \param[in] hydro_file the hydro file
 */
void find_map_width_height(QFile * hydro_file);

/**
 * \brief Initializes every value in the specified patch
 * \param[in] col
 * \param[in] row
 */
void init_patch_values(int col, int row);

/**
 * \brief Creates the 2D array of patches
 */
void init_patches();

/**
 * \brief Creates the 2D array of colors
 */
void init_color_values();

/**
 * \brief Map's each hydrofile to the index of its unique hydrofile.
 */
std::vector<int> map_hydro_files(QStringList & allHydroFiles, QStringList & uniqueHydroFiles);

/**
 * \brief Reads the Hydo map files and sets up the proper (x,y) patches
 * Input in the form of "pxcor pycor depth px-vector py-vector velocity"
 * and this must be the first line in the file.
 */
void import_hydro();

/**
 * \brief Reads from files the initial discharge (daily) and initial radiation
 * (hourly) values and then imports the maps based on the discharge value
 */
void setup_environmentals();

/**
 * \brief Reads the "par.txt" file and initializes the photo_radiation array variables
 */
void set_photo_radiation();

/**
 * \brief Reads the "water-temp.txt" file and initializes the temperature array variable
 */
void set_temperature();

/**
 * \brief Sets up the 10 stocks, currently has default values
 */
void setup_stocks();

/**
 * \brief Sets up the 10 stocks to input values
 */
void set_stocks(float macro, float phyto, float waterdecomp, float seddecomp, float herbivore,
        float sedconsumer, float doc, float poc, float detritus, float consum);
#endif
