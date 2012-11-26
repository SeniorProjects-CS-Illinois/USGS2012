#include "main.h"
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

//TODO: Unstub this with C/C++ code for image output.
void output_image(void) {

    QString fileName("output.png");
    QImageWriter writer;
    writer.setFormat("png");

    for(int i=0; i < g.NUM_STOCKS; i++){
       /* for(int x=0; x < g.MAP_WIDTH; x++){
            for(int y=0; y < g.MAP_HEIGHT; y++){
                float color = colorValues[i][getIndex(x, y)];
                int red = color && (255 << 16);
                int green = color && (255 << 8);
                int blue = color && 255;
                g.value = qRgb(red, green, blue);
                pixel_map[x][y] = pixel;
                image.setPixel(x, y, value);
            }
        }*/
        char* file_name = make_file_name(i);
        QString fileName(file_name);
        writer.setFileName(fileName);
        writer.write(*g.images[i]);
    }
    return;
}

char* make_file_name(int index) {
    char* path = "./results/images/";
    char* img_template = g.stock_names[index];
    char* format = ".png";

    time_t rawtime;
    struct tm * timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
	char buffer[80];
	strftime(buffer, 80, "%b_%a_%d_%I_%M_%S", timeinfo);
	
    char file_name[300]; file_name[0] = '\0';
    size_t len = strlen(path);
    strncat(file_name, path, len);
    len = strlen(img_template);
    strncat(file_name, img_template, len);
    len = strlen(buffer);
    strncat(file_name, buffer, len);
    len = strlen(format);
    strncat(file_name, format, len);
	
	file_name[strlen(file_name)] = '\0';
    return file_name;
}
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
