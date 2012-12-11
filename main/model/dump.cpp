#include "dump.h"

/**
 * The file format is as follows:
 * First line: GUI_VARIABLES separated by a comma
 * Each line represents one coordinate (x,y) in the River and holds the values of the DOCs in a patch.
 * @return 1 on successful completion, 0 indicates failure file could not be created.
 */
int write_data() {
    QString file_name = "./results/data/map_data_";
    QDateTime date_time = QDateTime::currentDateTime();
    QString date_time_str = date_time.toString("MMM_d_H_mm_ss");
    file_name.append(date_time_str);
    file_name.append(".csv");

    const char* cfile_name = file_name.toStdString().c_str();
    FILE* f = fopen(cfile_name, "w");
    if (f == NULL) { 
        printf("file name: %s could not be opened\n", cfile_name);
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

    QImageWriter writer;
    writer.setFormat("png");

    g.imageMutex.lock();
    for(int i=0; i < g.NUM_STOCKS; i++){
        QString fileName = make_file_name(i);
        writer.setFileName(fileName);
        *g.images[i] = g.images[i]->mirrored(false, true);
        writer.write(*g.images[i]);
    }
    g.imageMutex.unlock();
    return;
}

QString make_file_name(int index) {
    QString fileName = "./results/images/";
    fileName.append(g.stock_names[index]);
    QDateTime date_time = QDateTime::currentDateTime();
    QString date_time_str = date_time.toString("_MMM_d_H_mm_ss");
    fileName.append(date_time_str);
    fileName.append(".png");

    return fileName;
}

