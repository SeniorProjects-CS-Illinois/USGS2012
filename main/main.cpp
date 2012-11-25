#include <sys/types.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

#ifdef _WIN32
    #include <direct.h>
#else
    #include <unistd.h>
#endif

#include "model/rivermodel.h"
#include "model/globals.h"

#ifndef NO_GUI
    #include <QtGui/QApplication>
    #include "view/mainwindow.h"
#endif

//TODO: move this function to somewhere more appropriate.
//Adds a location for the images and csv files.
void create_output_dirs();

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


#ifdef NO_GUI
int main(int argc, char *argv[]) {
    initialize_globals();
    create_output_dirs();

    RiverModel model;

    //These values are what was used in the original Python GUI by default.  Hard coding for now.
    //TODO: There should be a configuration method that take a Configuration object.
    model.set_hydro_filenames("1?model/data/HydroSets/100k-new.txt?2?");
    model.set_par_file("model/data/Environmentals/par.txt");
    model.set_timestep(1);
    model.set_temperature_file("model/data/Environmentals/water-temp.txt");
    model.set_whichstock("phyto");
    model.set_TSS(10.0);
    model.set_macro_base_temp(19.7);
    model.set_gross_macro_coef(0.08);
    model.set_resp_macro_coef(0.04);
    model.set_sen_macro_coef(0.08);
    model.set_macro_mass_max(1000.0);
    model.set_macro_vel_max(1.0);
    model.set_k_phyto(0.01);
    model.set_k_macro(0.01);
    model.set_output_frequency(1);
    model.set_flow_corners(0);

    model.run();
    return 0;
}
#else
int main(int argc, char *argv[])
{
    initialize_globals();
    create_output_dirs();

    QApplication a(argc, argv);
    MainWindow w;
    w.setToolTips();
    w.show();

    return a.exec();
}

#endif
