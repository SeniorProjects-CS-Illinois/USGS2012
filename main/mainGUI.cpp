#include <QDir>

#include "model/rivermodel.h"
#include "model/globals.h"

#include <QtWidgets/QApplication>
#include "view/mainwindow.h"

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


int main(int argc, char *argv[])
{
    initialize_globals();
    create_output_dirs();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
