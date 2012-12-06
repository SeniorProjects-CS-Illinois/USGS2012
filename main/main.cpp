#include <sys/types.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <QDir>

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
    QDir path;
    path.mkpath("./results/data");
    path.mkpath("./results/images");
}


#ifdef NO_GUI
int main(int argc, char *argv[]) {
    initialize_globals();
    create_output_dirs();

    RiverModel model;

    //These values are what was used in the original Python GUI by default.  Hard coding for now.
    //TODO: There should be a configuration method that take a Configuration object.
    model.set_hydro_filenames("1?model/data/HydroSets/100k-new.txt?20?");
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
    w.show();

    return a.exec();
}

#endif
