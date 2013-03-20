#include <sys/types.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <QDir>

#include "model/rivermodel.h"
#include "model/configuration.h"
#include "model/globals.h"

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

int main(int argc, char *argv[]) {
    initialize_globals();
    create_output_dirs();

    RiverModel model;
    Configuration config;
    config.read("./data/testconfig.conf");

    model.setConfiguration(config);

    model.newRun();
    return 0;
}
