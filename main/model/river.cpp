#include "river.h"


//TODO Move these bounding functions somewhere more appropriate.


void boundLower(double & value, double lowerBound) {
    if(value < lowerBound) {
        value = lowerBound;
    }
}

void boundUpper(double & value, double upperBound) {
    if (value > upperBound) {
        value = upperBound;
    }
}

void boundValue(double & value, double lowerBound, double upperBound) {
    if(value < lowerBound) {
        value = lowerBound;
    } else if (value > upperBound) {
        value = upperBound;
    }
}

void boundPercentage(double & value) {
    boundValue(value, 0.0, 1.0);
}


River::River(Configuration & newConfig, HydroFileDict & hydroFileDict)
    : p(newConfig,hydroFileDict)
{

    config = newConfig;

    currHydroFile = NULL;
    currWaterTemp = -1.0;
    currPAR = -1;

    width = hydroFileDict.getMaxWidth();
    height = hydroFileDict.getMaxHeight();
}


void River::setCurrentHydroFile(HydroFile *newHydroFile) {
    // TODO Get rid of max_vector and g.COMPARE_MAX
    double max_vector = 0.0;
    double max_vector_component = 0.0;
    int x, y;

    //TODO Iterate over patches rather than (x,y) coordinates
    for (x = 0; x < width; x++) {
        for (y = 0; y < height; y++) {
            //Nothing to do at this (x,y) if no patch exists.
            if (!p.patchExists(x,y)) {
                continue;
            }
            int patchIndex = p.getIndex(x,y);

            // if the hydro maps contained information about this patch
            // get maximum component length of it's flow vector.
            if (newHydroFile->patchExists(x,y)) {
                QVector2D flowVector = newHydroFile->getVector(x,y);

                if (fabs(flowVector.x()) > fabs(flowVector.y())) {
                    max_vector_component = fabs(flowVector.x());
                } else {
                    max_vector_component = fabs(flowVector.y());
                }
            } else {
                max_vector_component = 0.0;
            }
            if (max_vector < max_vector_component) {
                max_vector = max_vector_component;
            }


            if(currHydroFile == NULL) {
                //We are configuring the first hydromap.  Zeroize all land.
                if(!newHydroFile->patchExists(x,y)){
                    p.detritus[patchIndex] *= 0.0;
                    p.DOC[patchIndex] = 0.0;
                    p.POC[patchIndex] = 0.0;
                    p.phyto[patchIndex] = 0.0;
                    p.macro[patchIndex] = 0.0;
                    p.waterdecomp[patchIndex] = 0.0;
                    p.seddecomp[patchIndex] = 0.0;
                    p.herbivore[patchIndex] = 0.0;
                    p.sedconsumer[patchIndex] = 0.0;
                    p.consum[patchIndex] = 0.0;
                }
            } else {
                double currentDepth = 0.0;
                if (currHydroFile->patchExists(x,y)) {
                    currentDepth = currHydroFile->getDepth(x,y);
                }

                double newDepth = 0.0;
                if (newHydroFile->patchExists(x,y)) {
                    newDepth = newHydroFile->getDepth(x,y);
                }

                //patch was previously water and is now land
                //TODO Comparing floats with == is bad and probably a bug -ECP
                if (currentDepth > 0.0 && newDepth == 0.0) {
                    p.detritus[patchIndex] += p.DOC[patchIndex] + p.POC[patchIndex]
                            + p.phyto[patchIndex] + p.macro[patchIndex]
                            + p.waterdecomp[patchIndex] + p.seddecomp[patchIndex]
                            + p.herbivore[patchIndex] + p.sedconsumer[patchIndex]
                            + p.consum[patchIndex];

                    p.DOC[patchIndex] = 0.0;
                    p.POC[patchIndex] = 0.0;
                    p.phyto[patchIndex] = 0.0;
                    p.macro[patchIndex] = 0.0;
                    p.waterdecomp[patchIndex] = 0.0;
                    p.seddecomp[patchIndex] = 0.0;
                    p.herbivore[patchIndex] = 0.0;
                    p.sedconsumer[patchIndex] = 0.0;
                    p.consum[patchIndex] = 0.0;
                }

                //patch was previously land and is now water
                //TODO Comparing floats with == is bad and probably a bug -ECP
                if (currentDepth == 0.0 && newDepth > 0.0) {
                    //TODO Check with Kevin to make sure these detritus calculations make sense
                    // in the transition from land->water and water->land. (i.e. should it decay
                    // further for multiple days that it is a land patch? -ECP
                    p.detritus[patchIndex] *= 0.5;
                }
            }
        }// endfor y
    }// endfor x

    // update the maximum vector for the timestep
    g.COMPARE_MAX = max_vector;

    currHydroFile = newHydroFile;
}

void River::setCurrentWaterTemperature(double newTemp) {
    /*
     * TODO I don't know what this calculation is doing...
     * Is it really the "temperature" anymore after this?
     * If not, my member variable's name should change. -ECP
     *
     * Edit: temp_dif is only assigned a value of 0...  Removing for now. Something
     * to ask Kevin I suppose... -ECP
     *
     * Here is original 2011 team's function:
     *
     * g.temperature_index++;
     * g.temperature = g.temperature_data[g.temperature_index];
     * g.temperature = g.temperature - ((g.temperature - 17.0) * g.temp_dif);
     */

    currWaterTemp = newTemp;// - ((newTemp - 17.0) * g.temp_dif);
}

void River::setCurrentPAR(int newPAR) {
    /*
     * TODO I don't know what this calculation is doing...
     * Is it really the "PAR" anymore after this?
     * If not, my member variable's name should change.
     * Also, is integer truncation the right thing to do or should it round? -ECP
     *
     * Edit: par_dif is only assigned a value of 0...  Removing for now. Something
     * to ask Kevin I suppose... -ECP
     *
     * Here is original 2011 team's function:
     *
     * g.photo_radiation_index++;
     * g.photo_radiation = g.photo_radiation_data[g.photo_radiation_index];
     * g.photo_radiation = g.photo_radiation - (int)(g.photo_radiation * g.par_dif);
     */

    currPAR = newPAR;// - (int)(newPAR * g.par_dif);
}

void River::flow() {
    //TODO Replace with CarbonFlowMap stuff

    Grid<FlowData> * source = new Grid<FlowData>(width, height);
    Grid<FlowData> * dest = new Grid<FlowData>(width, height);
    copyFlowData(*dest);
    *source = *dest;

    int max_time = 60/config.timestep;
    //TODO other usages of nan_trigger should be booleans as it is here.
    g.nan_trigger = false;
    for (int t = 0; t < max_time; t++)
    {
        std::swap(source, dest);
        flowSingleTimestep(*source, *dest, config);
        if (g.nan_trigger) {
            break;
        }
    }

    storeFlowData(*dest);
    delete source;
    delete dest;
}

void River::copyFlowData(Grid<FlowData> & flowData) {
    for(int x = 0; x < width; x++) {
        for(int y = 0; y < height; y++) {
            if(!p.patchExists(x,y)) {
                continue;
            }
            int index = p.getIndex(x,y);
            flowData(x,y).DOC         = p.DOC[index];
            flowData(x,y).POC         = p.POC[index];
            flowData(x,y).phyto       = p.phyto[index];
            flowData(x,y).waterdecomp = p.waterdecomp[index];
        }
    }
}

void River::storeFlowData(Grid<FlowData> & flowData) {
    for(int x = 0; x < width; x++) {
        for(int y = 0; y < height; y++) {
            if(!p.patchExists(x,y)) {
                continue;
            }
            int index = p.getIndex(x,y);
            p.DOC[index] = flowData(x,y).DOC;
            p.POC[index] = flowData(x,y).POC;
            p.phyto[index] = flowData(x,y).phyto;
            p.waterdecomp[index] = flowData(x,y).waterdecomp;
        }
    }
}

bool River::is_calc_nan(int x, int y, double move_factor, Grid<FlowData> &dst) {
    if ( /*isnan( dst(x,y).DOC + dst(x,y).DOC*move_factor )*/
        dst(x,y).DOC + dst(x,y).DOC*move_factor
            != dst(x,y).DOC + dst(x,y).DOC*move_factor)
    {
        return true;
    }
    if ( /*isnan( dst(x,y).POC + dst(x,y).POC*move_factor )*/
            dst(x,y).POC + dst(x,y).POC*move_factor
                != dst(x,y).POC + dst(x,y).POC*move_factor)
    {
        return true;
    }
    if ( /*isnan( dst(x,y).phyto + dst(x,y).phyto*move_factor )*/
            dst(x,y).phyto + dst(x,y).phyto*move_factor
                != dst(x,y).phyto + dst(x,y).phyto*move_factor)
    {
        return true;
    }
    if ( /*isnan( dst(x,y).waterdecomp + dst(x,y).waterdecomp*move_factor )*/
            dst(x,y).waterdecomp + dst(x,y).waterdecomp*move_factor
                != dst(x,y).waterdecomp + dst(x,y).waterdecomp*move_factor)
    {
        return true;
    }
    return false;
}

double River::getMaxTimestep() {
    if (g.COMPARE_MAX == 0.0)
    {
        return 1.0;
    }
    return (((double)g.patch_length)/((double)g.COMPARE_MAX));
}

void River::flowSingleTimestep(Grid<FlowData> &source, Grid<FlowData> &dest, Configuration &config) {
    for(int x = 0; x < width; x++) {
        for(int y = 0; y < height; y++) {
            if( !currHydroFile->patchExists(x,y) ) {
                continue;
            }

            double depth = currHydroFile->getDepth(x,y);
            QVector2D flowVector = currHydroFile->getVector(x,y);
            double velocity = flowVector.length();

            if( depth <= 0.0 || velocity <= 0.0 ) {
                continue;
            }

            double px_vector = flowVector.x();
            double py_vector = flowVector.y();

            double corner_patch = fabs( py_vector * px_vector )/g.max_area;
            double tb_patch = fabs( py_vector*( g.patch_length - fabs(px_vector) ) )/g.max_area;
            double rl_patch = fabs( px_vector*( g.patch_length - fabs(py_vector) ) )/g.max_area;

            // if a neighbor patch is dry, the carbon does not move in that direction
            double max_timestep = getMaxTimestep();
            bool tb_moved = false;
            bool corner_moved = false;
            bool rl_moved = false;

            int px = (int)(max_timestep * px_vector);
            int py = (int)(max_timestep * py_vector);

            // is this the opposite of what is waned?
            if (config.adjacent) {
                if (px >= 1) {
                    px = 1;
                } else if (px <= -1) {
                    px = -1;
                } else {
                    px = 0;
                }

                if (py >= 1) {
                    py = 1;
                } else if (py <= -1) {
                    py = -1;
                } else {
                    py = 0;
                }
            }

            // flow carbon to the top/bottom patches
            if ( p.patchExists(x, y+py) && (py!=0) ) {
                if (is_calc_nan(x,y+py,tb_patch, dest)) {
                    g.nan_trigger = true;
                } else {
                    dest(x, y+py).DOC += source(x,y).DOC*tb_patch;
                    dest(x, y+py).POC += source(x,y).POC*tb_patch;
                    dest(x, y+py).phyto += source(x,y).phyto*tb_patch;
                    dest(x, y+py).waterdecomp += source(x,y).waterdecomp*tb_patch;
                    tb_moved = true;
                }
            }

            // flow carbon to the corner patch
            if ( p.patchExists(x+px, y+py) && (px!=0) && (py!=0)) {
                if (is_calc_nan(x+px,y+py,corner_patch, dest)) {
                    g.nan_trigger = true;
                } else {
                    dest(x+px, y+py).DOC += source(x,y).DOC*corner_patch;
                    dest(x+px, y+py).POC += source(x,y).POC*corner_patch;
                    dest(x+px, y+py).phyto += source(x,y).phyto*corner_patch;
                    dest(x+px, y+py).waterdecomp += source(x,y).waterdecomp*corner_patch;
                    corner_moved = true;
                }
            }

            // flow carbon to the left/right patches
            //TODO code pushes carbon onto land patches...
            if ( p.patchExists(x+px, y) && (px!=0) ) {
                if ( is_calc_nan(x+px,y,rl_patch, dest) ) {
                    g.nan_trigger = true;
                } else {
                    dest(x+px, y).DOC += source(x,y).DOC*rl_patch;
                    dest(x+px, y).POC += source(x,y).POC*rl_patch;
                    dest(x+px, y).phyto += source(x,y).phyto*rl_patch;
                    dest(x+px, y).waterdecomp += source(x,y).waterdecomp*rl_patch;
                    rl_moved = true;
                }
            }

            // how much components did we loose
            double patch_loss = tb_patch*tb_moved + corner_patch*corner_moved + rl_patch*rl_moved;
            dest(x,y).DOC = source(x,y).DOC - source(x,y).DOC*patch_loss;
            dest(x,y).POC = source(x,y).POC - source(x,y).POC*patch_loss;
            dest(x,y).phyto = source(x,y).phyto - source(x,y).phyto*patch_loss;
            dest(x,y).waterdecomp = source(x,y).waterdecomp - source(x,y).waterdecomp*patch_loss;

        }
    }
}

int River::saveCSV() const {
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
            config.kPhyto, config.kMacro, (config.macroSenescence/24),
            (config.macroRespiration/24), config.macroTemp, config.macroMassMax,
            config.macroVelocityMax, config.macroGross, config.whichStock.toStdString().c_str());

    fprintf(f,"%s\n","# pxcor,pycor,pcolor,px_vector,py_vector,depth,velocity,assimilation,detritus,DOC,POC,waterdecomp,seddecomp,macro,phyto,herbivore,sedconsumer,peri,consum");

    int x,y;
    int pxcor, pycor, pcolor;
    double px_vector, py_vector;
    double depth;
    double velocity;
    double assimilation;
    double detritus, DOC, POC, waterdecomp, seddecomp, macro, phyto, herbivore, sedconsumer, peri, consum;

    for(x = 0; x < width; x++) {
        for(y=0;y < height; y++) {
            //Skip if cell doesn't exist or is land
            if( !currHydroFile->patchExists(x,y) || currHydroFile->getDepth(x,y) <= 0.0 ) {
                continue;
            }

            depth = currHydroFile->getDepth(x,y);

            QVector2D flowVector = currHydroFile->getVector(x,y);
            velocity = flowVector.length();

            int i = p.getIndex(x,y);
            pxcor = p.pxcor[i];
            pycor = p.pycor[i];
            pcolor = p.pcolor[i];
            px_vector = flowVector.x();
            py_vector = flowVector.y();
            assimilation = p.assimilation[i];
            detritus = p.detritus[i];
            DOC = p.DOC[i];
            POC = p.POC[i];
            waterdecomp = p.waterdecomp[i];
            seddecomp = p.seddecomp[i];
            macro = p.macro[i];
            phyto = p.phyto[i];
            herbivore = p.herbivore[i];
            sedconsumer = p.sedconsumer[i];
            peri = p.peri[i];
            consum = p.consum[i];


            fprintf(f,"%d,%d,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\n",pxcor,pycor,pcolor,px_vector,py_vector,depth,
                      velocity,assimilation,detritus,DOC,POC,
                      waterdecomp,seddecomp,macro,phyto,herbivore,sedconsumer,peri,consum);
        }
    }
    fclose(f);
    return 1;
}



void River::processPatches() {
    //TODO refactor this massive function into smaller functions
    int patchCount = p.getSize();

    #pragma omp parallel for
    for(int i = 0; i < patchCount; i++) {

        int patchX = p.pxcor[i];
        int patchY = p.pycor[i];

        //Only process patches if they exist in the currHydroFile
        if(!currHydroFile->patchExists(patchX,patchY)) {
            continue;
        }

        double depth = currHydroFile->getDepth(patchX, patchY);

        //Don't process patches that are currently land
        if(depth <= 0.0)
            continue;

        QVector2D flowVector = currHydroFile->getVector(patchX, patchY);
        double velocity = flowVector.length();

        ///////////////////////////////////////////
        //
        // From 2011 team's update_patches function
        //
        ///////////////////////////////////////////
        p.turbidity[i] = ( .29587 + config.tss)
                + (config.kPhyto * (p.phyto[i]/ 900.0) )
                + (config.kMacro * (p.macro[i] / 900.0) );

        if(p.turbidity[i] < 0.0){
            p.turbidity[i] = 0.01;
        }

        //the amount of light that reaches the bottom of a water column
        p.bottom_light[i] = currPAR
                * exp( (-1 * depth) * p.turbidity[i] );

        //TODO why is this code altering the config? Config should never be edited by model. -ECP
        //Also these two do not ever get used.  Commenting them out for now.
        //config.periAj = p.macro[i] / 10.0 ;
        //config.periGj = p.macro[i] / 2.0;

        //TODO These config values never gets used before being overwritten here
        //Is this correct behavior?  Converting to local variables for now.
        //config.seddecompAj = p.detritus[i] / 20.0;
        //config.seddecompGj = p.detritus[i] / 5.0;
        double seddecompAj = p.detritus[i] / 20.0;
        double seddecompGj = p.detritus[i] / 5.0;

        ///////////////////////////////////////////
        //
        // From 2011 team's go_macro function
        //
        ///////////////////////////////////////////

        //Converting to local variable
        //Q10 = pow(g.theta, (g.temperature - config.macroTemp));
        double Q10;

        //TODO Ask Kevin what theta is and why it is 1.072.  I want to add
        //it to the constants file but "THETA" is really ambiguous. -ECP
        Q10 = pow(g.theta, (currWaterTemp - config.macroTemp));

        //TODO pull velocity from hydrofile rather than patches
        if(velocity < config.macroVelocityMax) {
            p.K[i] = g.max_area
                    * (config.macroMassMax
                       - (config.macroMassMax  / config.macroVelocityMax)
                       * velocity);
        } else {
            p.K[i] = 0.01;
        }
        //Same at bottom-light
        double macro_light = currPAR * exp( (-1*depth) * p.turbidity[i] );

        p.gross_photo_macro[i] = config.macroGross * p.macro[i]
                * ( macro_light / ( macro_light + 10.0)) * Q10
                * ( p.K[i] - p.macro[i]) / p.K[i];

        p.respiration_macro[i] = (config.macroRespiration / HOURS_PER_DAY)
                * p.macro[i] * Q10;

        p.senescence_macro[i] = (config.macroSenescence / HOURS_PER_DAY)
                * (p.macro[i] / HOURS_PER_DAY);

        p.growth_macro[i] = p.gross_photo_macro[i] - p.respiration_macro[i]
                - p.senescence_macro[i] - p.scouring_macro[i];

        p.macro[i] += p.growth_macro[i];

        boundLower(p.macro[i], 0.001);

        ///////////////////////////////////////////
        //
        // From 2011 team's go_phyto function
        //
        ///////////////////////////////////////////

        //TODO write a bounding function.

        //minimum and maximum caps on biomass
        boundValue(p.phyto[i], 0.001, 900000.0);


        //base temperature for nominal growth
        //TODO What is base temperature and why is it a magic number?
        double base_temperature = 8.0;
        Q10 = pow(g.theta, (currWaterTemp - base_temperature));
        double km = 10; //half saturation constant


        // TODO  Figure out if the following commented light_k lines were lost in translation from netgui
        // It is set but never used. -ECP
        //this is the attenuation coefficient of phytoplank m^2/g of phyto plankton
        //double light_k = 0.4;


        p.respiration_phyto[i] = (config.phytoRespiration / HOURS_PER_DAY) * p.phyto[i] * Q10;

        double pre_ln = 0.01 + currPAR
                * exp(-1 * p.phyto[i] * config.kPhyto * depth);
        double be = km + currPAR
                * exp(-1 * p.phyto[i] * config.kPhyto * depth);

        //photosynthesis from phytoplankton derived from Huisman Weissing 1994
        p.gross_photo_phyto[i] = fabs(pre_ln / be) * (1.0 / depth)
                * (p.phyto[i] / p.turbidity[i]) * Q10;
        p.excretion_phyto[i] = (config.phytoExcretion / HOURS_PER_DAY) * p.phyto[i];
        p.senescence_phyto[i] = (config.phytoSenescence / HOURS_PER_DAY) * p.phyto[i];
        p.growth_phyto[i] = p.gross_photo_phyto[i] - p.excretion_phyto[i] -
                p.respiration_phyto[i] - p.senescence_phyto[i];

        ///////////////////////////////////////////
        //
        // From 2011 team's go_herbivore function
        //
        ///////////////////////////////////////////

        p.herbivore_phyto_prey_limitation[i] = p.phyto[i]
                / (config.herbivoreAiPhyto - config.herbivoreGiPhyto);
        boundPercentage(p.herbivore_phyto_prey_limitation[i]);

        p.herbivore_peri_prey_limitation[i] = p.peri[i]
                / (config.herbivoreAiPeri - config.herbivoreGiPeri);
        boundPercentage(p.herbivore_peri_prey_limitation[i]);

        p.herbivore_waterdecomp_prey_limitation[i] = p.waterdecomp[i]
                / (config.herbivoreAiWaterdecomp - config.herbivoreGiWaterdecomp);
        boundPercentage(p.herbivore_waterdecomp_prey_limitation[i]);

        p.herbivore_space_limitation[i] = 1.0
                - ((p.herbivore[i] - config.herbivoreAj)
                    / (config.herbivoreGj - config.herbivoreAj));
        boundPercentage(p.herbivore_space_limitation[i]);

        p.herbivore_pred_phyto[i] = config.herbivorePrefPhyto
                * (config.herbivoreMax / HOURS_PER_DAY) * p.herbivore[i]
                * p.herbivore_space_limitation[i] * p.herbivore_phyto_prey_limitation[i];
        p.herbivore_ingest_phyto[i] = p.herbivore_pred_phyto[i] * (1.0 - config.herbivoreEgestion);

        p.herbivore_pred_peri[i] = config.herbivorePrefPeri
                * (config.herbivoreMax / HOURS_PER_DAY) * p.herbivore[i]
                * p.herbivore_space_limitation[i] * p.herbivore_peri_prey_limitation[i];
        p.herbivore_ingest_peri[i] = p.herbivore_pred_peri[i] * (1.0 - config.herbivoreEgestion);

        p.herbivore_pred_waterdecomp[i] = config.herbivorePrefWaterdecomp
                * (config.herbivoreMax / HOURS_PER_DAY) * p.herbivore[i]
                * p.herbivore_space_limitation[i] * p.herbivore_waterdecomp_prey_limitation[i];
        p.herbivore_ingest_waterdecomp[i] = p.herbivore_pred_waterdecomp[i] * (1.0 - config.herbivoreEgestion);

        p.herbivore_respiration[i] = (config.herbivoreRespiration / HOURS_PER_DAY) * p.herbivore[i];
        p.herbivore_excretion[i] = (config.herbivoreExcretion / HOURS_PER_DAY) * p.herbivore[i];
        p.herbivore_senescence[i] = (config.herbivoreSenescence / HOURS_PER_DAY) * p.herbivore[i];

        ///////////////////////////////////////////
        //
        // From 2011 team's go_waterdecomp function
        //
        ///////////////////////////////////////////

        p.waterdecomp_doc_prey_limitation[i] = p.DOC[i]
                / (config.waterdecompAiDoc - config.waterdecompGiDoc);
        boundPercentage(p.waterdecomp_doc_prey_limitation[i]);

        p.waterdecomp_poc_prey_limitation[i] = p.POC[i]
                / (config.waterdecompAiPoc - config.waterdecompGiPoc);
        boundPercentage(p.waterdecomp_poc_prey_limitation[i]);

        p.waterdecomp_space_limitation[i] = 1.0
                - ((p.waterdecomp[i] - config.waterdecompAj)
                    / (config.waterdecompGj - config.waterdecompAj));
        boundPercentage(p.waterdecomp_space_limitation[i]);

        p.waterdecomp_pred_doc[i] = config.waterdecompPrefDoc
                * (config.waterdecompMax / HOURS_PER_DAY) * p.waterdecomp[i]
                * p.waterdecomp_space_limitation[i] * p.waterdecomp_doc_prey_limitation[i];
        p.waterdecomp_ingest_doc[i] = p.waterdecomp_pred_doc[i];

        p.waterdecomp_pred_poc[i] = config.waterdecompPrefPoc
                * (config.waterdecompMax / HOURS_PER_DAY) * p.waterdecomp[i]
                * p.waterdecomp_space_limitation[i] * p.waterdecomp_poc_prey_limitation[i];
        p.waterdecomp_ingest_poc[i] = p.waterdecomp_pred_poc[i];

        p.waterdecomp_respiration[i] = (config.waterdecompRespiration / HOURS_PER_DAY) * p.waterdecomp[i];
        p.waterdecomp_excretion[i] = (config.waterdecompExcretion / HOURS_PER_DAY) * p.waterdecomp[i];
        p.waterdecomp_senescence[i] = (config.waterdecompSenescence / HOURS_PER_DAY) * p.waterdecomp[i];


        ///////////////////////////////////////////
        //
        // From 2011 team's go_seddecomp function
        //
        ///////////////////////////////////////////

        p.seddecomp_detritus_prey_limitation[i] = p.detritus[i]
                / (config.seddecompAiDetritus - config.seddecompGiDetritus);
        boundPercentage(p.seddecomp_detritus_prey_limitation[i]);

        //TODO Comparing floats like this is wrong and is likely a bug -ECP
        //TODO Also, why is this calculation different from the others? -ECP
        if( (seddecompGj - seddecompAj) != 0.0 ) {
            p.seddecomp_space_limitation[i] = 1.0
                    - ((p.seddecomp[i] - seddecompAj)
                       / (seddecompGj - seddecompAj));
            boundPercentage(p.seddecomp_space_limitation[i]);
        } else {
            p.seddecomp_space_limitation[i] = 0.0;
        }

        p.seddecomp_pred_detritus[i] = config.seddecompPrefDetritus
                * (config.seddecompMax / HOURS_PER_DAY) * p.seddecomp[i]
                * p.seddecomp_detritus_prey_limitation[i] * p.seddecomp_space_limitation[i];
        p.seddecomp_ingest_detritus[i] = p.seddecomp_pred_detritus[i];

        p.seddecomp_respiration[i] = (config.seddecompRespiration / HOURS_PER_DAY) * p.seddecomp[i];
        p.seddecomp_excretion[i] = (config.seddecompExcretion / HOURS_PER_DAY) * p.seddecomp[i];
        p.seddecomp_senescence[i] = (config.seddecompSenescence / HOURS_PER_DAY) * p.seddecomp[i];


        ///////////////////////////////////////////
        //
        // From 2011 team's go_sedconsumer function
        //
        ///////////////////////////////////////////

        p.sedconsumer_seddecomp_prey_limitation[i] = p.seddecomp[i]
                / (config.sedconsumerAiSeddecomp - config.sedconsumerGiSeddecomp);
        boundPercentage(p.sedconsumer_seddecomp_prey_limitation[i]);

        p.sedconsumer_peri_prey_limitation[i] = p.peri[i]
                / (config.sedconsumerAiPeri - config.sedconsumerGiPeri);
        boundPercentage(p.sedconsumer_peri_prey_limitation[i]);

        p.sedconsumer_detritus_prey_limitation[i] = p.detritus[i]
                / (config.sedconsumerAiDetritus - config.sedconsumerGiDetritus);
        boundPercentage(p.sedconsumer_detritus_prey_limitation[i]);

        p.sedconsumer_space_limitation[i] = 1.0
                - ((p.sedconsumer[i] - config.sedconsumerAj)
                   / (config.sedconsumerGj - config.sedconsumerAj));
        boundPercentage(p.sedconsumer_space_limitation[i]);

        p.sedconsumer_pred_peri[i] = config.sedconsumerPrefPeri
                * (config.sedconsumerMax / HOURS_PER_DAY) * p.sedconsumer[i]
                * p.sedconsumer_space_limitation[i] * p.sedconsumer_peri_prey_limitation[i];
        // TODO is it weird there is no peri version for this? -Bill
        p.sedconsumer_ingest_peri[i] = p.sedconsumer_pred_peri[i] * (1.0 - config.sedconsumerEgestionSeddecomp);

        p.sedconsumer_pred_seddecomp[i] = config.sedconsumerPrefSeddecomp
                * (config.sedconsumerMax / HOURS_PER_DAY) * p.sedconsumer[i]
                * p.sedconsumer_space_limitation[i] * p.sedconsumer_seddecomp_prey_limitation[i];
        p.sedconsumer_ingest_seddecomp[i] = p.sedconsumer_pred_seddecomp[i] * (1.0 - config.sedconsumerEgestionSeddecomp);

        p.sedconsumer_pred_detritus[i] = config.sedconsumerPrefDetritus
                * (config.sedconsumerMax / HOURS_PER_DAY) * p.sedconsumer[i]
                * p.sedconsumer_space_limitation[i] * p.sedconsumer_detritus_prey_limitation[i];
        p.sedconsumer_ingest_detritus[i] = p.sedconsumer_pred_detritus[i] * (1.0 - config.sedconsumerEgestionDetritus);

        p.sedconsumer_respiration[i] = (config.sedconsumerRespiration / HOURS_PER_DAY) * p.sedconsumer[i];
        p.sedconsumer_excretion[i] = (config.sedconsumerExcretion / HOURS_PER_DAY) * p.sedconsumer[i];
        p.sedconsumer_senescence[i] = (config.sedconsumerSenescence / HOURS_PER_DAY) * p.sedconsumer[i];


        ///////////////////////////////////////////
        //
        // From 2011 team's go_consum function
        //
        ///////////////////////////////////////////

        p.consum_sedconsumer_prey_limitation[i] = p.sedconsumer[i]
                / (config.consumerAiSedconsumer - config.consumerGiSedconsumer);
        boundPercentage(p.consum_sedconsumer_prey_limitation[i]);

        p.consum_herbivore_prey_limitation[i] = p.herbivore[i]
                / (config.consumerAiHerbivore - config.consumerGiHerbivore);
        boundPercentage(p.consum_herbivore_prey_limitation[i]);

        p.consum_space_limitation[i] = 1.0
                - ((p.consum[i] - config.consumerAj)
                   / (config.consumerGj - config.consumerAj));
        boundPercentage(p.consum_space_limitation[i]);

        p.consum_pred_herbivore[i] = config.consumerPrefHerbivore
                * (config.consumerMax / HOURS_PER_DAY) * p.consum[i]
                * p.consum_space_limitation[i] * p.consum_herbivore_prey_limitation[i];
        p.consum_ingest_herbivore[i] = p.consum_pred_herbivore[i] * (1.0- config.consumerEgestion);

        p.consum_pred_sedconsumer[i] = config.consumerPrefSedconsumer
                * (config.consumerMax / HOURS_PER_DAY) * p.consum[i]
                * p.consum_space_limitation[i] * p.consum_sedconsumer_prey_limitation[i];
        p.consum_ingest_sedconsumer[i] = p.consum_pred_sedconsumer[i] * (1.0 - config.consumerEgestion);

        p.consum_respiration[i] = (config.consumerRespiration / HOURS_PER_DAY) * p.consum[i];
        p.consum_excretion[i] = (config.consumerExcretion / HOURS_PER_DAY) * p.consum[i];
        p.consum_senescence[i] = (config.consumerSenescence / HOURS_PER_DAY) * p.consum[i];


        ///////////////////////////////////////////
        //
        // From 2011 team's go_DOC function
        //
        ///////////////////////////////////////////

        // 4% of photosynthetic gets released into the water column. Wetzel lit.
        p.macro_exudation[i] = config.macroExcretion * p.macro[i];

        // Dead objects < 1um are considered DOC in Wetzel book..
        p.micro_death[i] = p.senescence_macro[i] * .01 + p.senescence_phyto[i] * .01;

        // *need reference
        p.excretion[i] = p.herbivore_excretion[i] + p.waterdecomp_excretion[i] +
                p.seddecomp_excretion[i] + p.sedconsumer_excretion[i] +
                p.consum_excretion[i] + p.excretion_phyto[i] + p.peri_excretion[i];

        // *need reference
        p.flocculation[i] = .01 * p.DOC[i];

        p.DOC_growth[i] = p.macro_exudation[i] + p.micro_death[i] + p.excretion[i];


        ///////////////////////////////////////////
        //
        // From 2011 team's go_POC function
        //
        ///////////////////////////////////////////

        //TODO: get velocity from hydrofile

        if(velocity > 0.0)
        {
            // exchange between POC and detritus determined by an approximation of Stoke's Law
            p.detritus_POC_transfer[i] = p.detritus[i] * (.25 * log10(((velocity / 40.0 ) + .0001) + 1.0));
        }
        // cap at 100%. *need reference
        boundUpper(p.detritus_POC_transfer[i], 1.0);

        // approximations of the percention of dead objects < 10um that will be in water column; Wetzel Limnology textbook.
        p.small_death[i] = p.senescence_macro[i] * 0.09 + p.senescence_phyto[i] * 0.09 +
                p.scouring_macro[i] * 0.1 + p.waterdecomp_senescence[i] *
                0.7 + 0.3 * p.peri_senescence[i];

        // flocculation, leaching approximation
        p.POC_growth[i] = p.flocculation[i] + p.detritus_POC_transfer[i];


        ///////////////////////////////////////////
        //
        // From 2011 team's go_detritus function
        //
        ///////////////////////////////////////////

        //TODO get velocity from hydroFile
        if(velocity > 0.0) {
            p.POC_detritus_transfer[i] = p.POC[i] * (1.0 - (0.25 * log10((( velocity / 40.0) + 0.0001) + 1.0)));
        }
        boundLower(p.POC_detritus_transfer[i], 0.0);

        //TODO Comparing a float using equality is super bad and this is probably a bug...
        if(velocity == 0.0) {
            p.POC_detritus_transfer[i] = p.POC[i] * 0.9;
        }

        if(p.gross_photo_macro[i] < 0.0) {
            // to incorporate scoured macrophytes into detritus
            p.macro_death[i] = 0.0 - p.gross_photo_macro[i];
        }

        // Dead objects > 10um will sink Wetzel book..
        p.large_death[i] = p.senescence_macro[i] * 0.9 + p.scouring_macro[i] * 0.9 +
                p.senescence_phyto[i] * 0.9 + p.seddecomp_senescence[i] +
                p.waterdecomp_senescence[i] * 0.3 + p.herbivore_senescence[i] +
                p.sedconsumer_senescence[i] + p.consum_senescence[i] + 0.07 * p.peri_senescence[i];

        p.egestion[i] = config.herbivoreEgestion + p.sedconsumer_egestion[i] + config.consumerEgestion;

        p.detritus_growth[i] = p.large_death[i] + p.POC_detritus_transfer[i] +
                p.egestion[i] + p.macro_death[i];


        ///////////////////////////////////////////
        //
        // From 2011 team's pred_phyto function
        //
        ///////////////////////////////////////////
        p.phyto[i] = p.phyto[i] + p.growth_phyto[i] - p.herbivore_pred_phyto[i];
        boundLower(p.phyto[i], 0.001);


        ///////////////////////////////////////////
        //
        // From 2011 team's pred_herbivore function
        //
        ///////////////////////////////////////////
        p.herbivore[i] = p.herbivore[i] + p.herbivore_ingest_phyto[i]
                + p.herbivore_ingest_peri[i] + p.herbivore_ingest_waterdecomp[i]
                - (p.herbivore_respiration[i] + p.herbivore_excretion[i] + p.herbivore_senescence[i])
                - p.consum_pred_herbivore[i];
        boundLower(p.herbivore[i], 0.001);


        ///////////////////////////////////////////
        //
        // From 2011 team's pred_seddecomp function
        //
        ///////////////////////////////////////////
        p.seddecomp[i] = p.seddecomp[i] + p.seddecomp_ingest_detritus[i]
                - (p.seddecomp_respiration[i] + p.seddecomp_excretion[i] + p.seddecomp_senescence[i])
                - p.sedconsumer_pred_seddecomp[i];
        boundLower(p.seddecomp[i], 0.001);


        ///////////////////////////////////////////
        //
        // From 2011 team's pred_waterdecomp function
        //
        ///////////////////////////////////////////
        p.waterdecomp[i] = p.waterdecomp[i] + p.waterdecomp_ingest_doc[i] + p.waterdecomp_ingest_poc[i]
                - (p.waterdecomp_respiration[i] + p.waterdecomp_excretion[i]
                + p.waterdecomp_senescence[i]) - p.herbivore_pred_waterdecomp[i];
        boundLower(p.waterdecomp[i], 0.001);


        ///////////////////////////////////////////
        //
        // From 2011 team's pred_sedconsumer function
        //
        ///////////////////////////////////////////
        p.sedconsumer[i] = p.sedconsumer[i] + p.sedconsumer_ingest_peri[i] + p.sedconsumer_ingest_seddecomp[i]
                - (p.sedconsumer_respiration[i] + p.sedconsumer_excretion[i] + p.sedconsumer_senescence[i])
                - p.consum_pred_sedconsumer[i];
        boundLower(p.sedconsumer[i], 0.001);


        ///////////////////////////////////////////
        //
        // From 2011 team's pred_detritus function
        //
        ///////////////////////////////////////////
        p.detritus_POC_transfer[i] = p.detritus[i]
                * (0.25 * log10(velocity / 40.0 + 0.01) + 0.5);
        p.detritus[i] = p.detritus[i] + p.detritus_growth[i] - p.seddecomp_pred_detritus[i]
                - p.detritus_POC_transfer[i];
        boundLower(p.detritus[i], 0.001);


        ///////////////////////////////////////////
        //
        // From 2011 team's pred_DOC function
        //
        ///////////////////////////////////////////
        p.DOC[i] = p.DOC[i] + p.DOC_growth[i] - p.waterdecomp_pred_doc[i] - p.flocculation[i];
        boundLower(p.DOC[i], 0.001);


        ///////////////////////////////////////////
        //
        // From 2011 team's pred_POC function
        //
        ///////////////////////////////////////////
        p.POC[i] = p.POC[i] + p.POC_growth[i] - p.waterdecomp_pred_poc[i] - p.POC_detritus_transfer[i];
        boundLower(p.POC[i], 0.001);


        ///////////////////////////////////////////
        //
        // From 2011 team's pred_consum function
        //
        ///////////////////////////////////////////
        p.consum[i] = p.consum[i] + p.consum_ingest_herbivore[i] + p.consum_ingest_sedconsumer[i]
                - (p.consum_respiration[i] + p.consum_excretion[i] + p.consum_senescence[i]);
        boundLower(p.consum[i], 0.001);
    }
}



