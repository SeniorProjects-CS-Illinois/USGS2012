#include "dump.h"

/**
 * Defining non extern versions from header file...
 */
/* Folder under which we place the data files */
const char* data_path = "./results/data/";
/* Each simulation data file has the name 'map_data_timestamp' */
const char* data_template = "map_data_";
/* file format is .csv */
const char* format = ".csv";



/**
 * The file format is as follows:
 * First line: GUI_VARIABLES separated by a comma
 * Each line represents one coordinate (x,y) in the River and holds the values of the DOCs in a patch.
 * @return 1 on successful completion, 0 indicates failure file could not be created.
 */
int write_data() {
    time_t rawtime;
    struct tm * timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    char buffer[80];
    //strftime(buffer, 80, "%b_%a_%d_%I:%M:%S%p", timeinfo);
    strftime(buffer, 80, "%b_%a_%d_%I_%M_%S", timeinfo);

    char file_name[300]; file_name[0] = '\0';
    size_t len = strlen(data_path);
    strncat(file_name, data_path, len);
    len = strlen(data_template);
    strncat(file_name, data_template, len);
    //len = strlen(asctime(timeinfo));
    //strcat(file_name, asctime(timeinfo), len );
    len = strlen(buffer);
    strncat(file_name, buffer, len);
    len = strlen(format);
    strncat(file_name, format, len);

    file_name[strlen(file_name)] = '\0';
    FILE* f = fopen(file_name, "w");
    if (f == NULL) { 
        printf("file name: %s could not be opened\n", file_name);
        return 0;
    }

    // GUI variables used    
    fprintf(f,"%s\n","# timestep_factor,hydro_group,days_to_run,tss,k_phyto,k_macro,sen_macro_coef,resp_macro_coef,macro_base_temp,macro_mass_max,macro_vel_max,gross_macro_coef,which_stock");
    
    fprintf(f,"%d,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%s\n", g.gui_timestep_factor, g.gui_days_to_run, g.gui_tss, g.gui_k_phyto, g.gui_k_macro, g.gui_sen_macro_coef, g.gui_resp_macro_coef, g.gui_macro_base_temp, g.gui_macro_mass_max, g.gui_macro_vel_max, g.gui_gross_macro_coef, g.which_stock.toStdString().c_str());
    
    fprintf(f,"%s\n","# pxcor,pycor,pcolor,px_vector,py_vector,depth,velocity,assimilation,detritus,DOC,POC,waterdecomp,seddecomp,macro,phyto,herbivore,sedconsumer,peri,consum");

    int x,y;
    int pxcor, pycor, pcolor;
    double px_vector, py_vector;
    double depth;
    double velocity;
    double assimilation;
    double detritus, DOC, POC, waterdecomp, seddecomp, macro, phyto, herbivore, sedconsumer, peri, consum;

    for(x = 0; x < g.MAP_WIDTH; x++) {
        for(y=0;y < g.MAP_HEIGHT; y++) {
            if( patches[x][y].depth > 0.0) {
                pxcor = patches[x][y].pxcor;
                pycor = patches[x][y].pycor;
                pcolor = patches[x][y].pcolor;
                px_vector = patches[x][y].px_vector;
                py_vector = patches[x][y].py_vector;
                depth = patches[x][y].depth;
                velocity = patches[x][y].velocity;
                assimilation = patches[x][y].assimilation;
                detritus = patches[x][y].detritus;
                DOC = patches[x][y].DOC;
                POC = patches[x][y].POC;
                waterdecomp = patches[x][y].waterdecomp;
                seddecomp = patches[x][y].seddecomp;
                macro = patches[x][y].macro;
                phyto = patches[x][y].phyto;
                herbivore = patches[x][y].herbivore;
                sedconsumer = patches[x][y].sedconsumer;
                peri = patches[x][y].peri;
                consum = patches[x][y].consum;


                fprintf(f,"%d,%d,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\n",pxcor,pycor,pcolor,px_vector,py_vector,depth,
                          velocity,assimilation,detritus,DOC,POC,
                          waterdecomp,seddecomp,macro,phyto,herbivore,sedconsumer,peri,consum);
            }
        }
    }
    fclose(f);
    return 1;
}

/**
 * Creates a folder <data_path> and places all the results from running the model into this file.
 * @return 1 on successful completion, 0 indicates failure file could not be created.
 */
int dump_data() {
    return write_data();
}


void output_image(void) {

    QString fileName("output.png");
    QImageWriter writer;
    writer.setFormat("png");

    g.imageMutex.lock();
    for(int i=0; i < g.NUM_STOCKS; i++){
        char* file_name = make_file_name(i);
        QString fileName(file_name);
        writer.setFileName(fileName);
        *g.images[i] = g.images[i]->mirrored(false, true);
        writer.write(*g.images[i]);
    }
    g.imageMutex.unlock();
    return;
}

char* make_file_name(int index) {
    const char* path = "./results/images/";
    char* img_template = g.stock_names[index];
    const char* format = ".png";

    time_t rawtime;
    struct tm * timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    char buffer[100];
    strftime(buffer, 100, "%b_%a_%d_%I_%M_%S", timeinfo);

    char file_name[320]; file_name[0] = '\0';
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

