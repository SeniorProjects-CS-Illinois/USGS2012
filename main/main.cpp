#include <QDir>

#include "model/rivermodel.h"
#include "model/configuration.h"

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

int main(void) {
    create_output_dirs();

    RiverModel model;
    Configuration config;
    config.read("./data/testconfig.conf");

    model.setConfiguration(config);

    model.run();
    return 0;
}
