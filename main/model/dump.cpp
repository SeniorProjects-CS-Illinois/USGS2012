#include "dump.h"

/**
 * The file format is as follows:
 * First line: GUI_VARIABLES separated by a comma
 * Each line represents one coordinate (x,y) in the River and holds the values of the DOCs in a patch.
 * @return 1 on successful completion, 0 indicates failure file could not be created.
 */
int write_data(const Configuration & config) {
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
    
    fprintf(f,"%d,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%s\n",
            config.timestep, g.gui_days_to_run, config.tss,
            config.kPhyto, config.kMacro, config.macroSenescence,
            config.macroRespiration, config.macroTemp, config.macroMassMax,
            config.macroVelocityMax, config.macroGross, config.whichStock.toStdString().c_str());
    
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
int dump_data(const Configuration & config) {
    return write_data(config);
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

void average_carbon(int day) {
    QString file_name;
    FILE* f;
    if(g.total_carbon_csv == "default"){
        file_name = "./results/data/carbon_avgs_";
        QDateTime date_time = QDateTime::currentDateTime();
        QString date_time_str = date_time.toString("MMM_d_H_mm_ss");
        file_name.append(date_time_str);
        file_name.append(".csv");

        g.total_carbon_csv = file_name;

        const char* cfile_name = file_name.toStdString().c_str();
        f = fopen(cfile_name, "w");
        if (f == NULL) {
            printf("file name: %s could not be opened\n", cfile_name);
        }
        fprintf(f,"%s\n","Day,Macro,Phyto,Waterdecomp,Seddecomp,Sedconsumer,Consumer,DOC,POC,Herbivore,Detritus,Total");
        fclose(f);
    }
    else {
        file_name = g.total_carbon_csv;

    }

    const char* cfile_name = file_name.toStdString().c_str();
    f = fopen(cfile_name, "a");
    if (f == NULL) {
        printf("file name: %s could not be opened\n", cfile_name);
    }
    fprintf(f,"%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\n", day, g.sum_macro/g.num_water_squares, g.sum_phyto/g.num_water_squares, g.sum_waterdecomp/g.num_water_squares, g.sum_seddecomp/g.num_water_squares, g.sum_sedconsum/g.num_water_squares, g.sum_consum/g.num_water_squares, g.sum_DOC/g.num_water_squares, g.sum_POC/g.num_water_squares, g.sum_herbivore/g.num_water_squares, g.sum_detritus/g.num_water_squares, g.sum_carbon/g.num_water_squares);
    fclose(f);

    g.sum_macro = 0.0;
    g.sum_phyto = 0.0;
    g.sum_herbivore = 0.0;
    g.sum_waterdecomp = 0.0;
    g.sum_seddecomp = 0.0;
    g.sum_sedconsum = 0.0;
    g.sum_consum = 0.0;
    g.sum_DOC = 0.0;
    g.sum_POC = 0.0;
    g.sum_detritus = 0.0;
    g.sum_carbon = 0.0;

}

