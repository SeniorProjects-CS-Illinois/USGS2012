#include "patch.h"
#include "constants.h"

patch** patches;

/**
 * Updates the patches
 * @param x the X coord of the patch
 * @param y the Y coord of the patch
*/
void update_patches(int x, int y, Configuration & config)
{

        patches[x][y].turbidity = ( .29587 + config.tss) + (config.kPhyto * (patches[x][y].phyto/ 900.0) ) + (config.kMacro * (patches[x][y].macro / 900.0) );

        if(patches[x][y].turbidity < 0.0){
                patches[x][y].turbidity = 0.01;
        }

        //the amount of light that reaches the bottom of a water column
        patches[x][y].bottom_light = (g.photo_radiation * exp( (-1*patches[x][y].depth)*patches[x][y].turbidity )); 
        config.periAj = patches[x][y].macro / 10.0 ;
        config.periGj = patches[x][y].macro / 2.0;
        config.seddecompAj = patches[x][y].detritus / 20.0;
        config.seddecompGj = patches[x][y].detritus / 5.0;
}


/**
 * Ensures a bound
 * @param value The value to test
 * @param low value must be higher than this value
 * @param high value must be lower than this value
 * @return The bounded value
*/
double assertRange(double value, double low, double high)
{
    if(value < low)
        return low;
    else if(value > high)
        return high;
    else
        return value;
}

void go_macro(int x, int y, const Configuration & config)
{
        g.Q10 = pow(g.theta, (g.temperature - config.macroTemp));

        if(patches[x][y].velocity < config.macroVelocityMax){
                patches[x][y].K = g.max_area * (config.macroMassMax - (config.macroMassMax  / config.macroVelocityMax) * patches[x][y].velocity);
        }
        else{
                patches[x][y].K = 0.01;
        }
        //Same at bottom-light
        double macro_light = g.photo_radiation * exp( (-1*patches[x][y].depth) * patches[x][y].turbidity );
        
        patches[x][y].gross_photo_macro = (config.macroGross * patches[x][y].macro * ( macro_light / ( macro_light + 10.0)) * g.Q10 *
                                               (patches[x][y].K - patches[x][y].macro) / patches[x][y].K);

        patches[x][y].respiration_macro = (config.macroRespiration / HOURS_PER_DAY) * patches[x][y].macro * g.Q10;

        patches[x][y].senescence_macro = (config.macroSenescence / HOURS_PER_DAY) * (patches[x][y].macro / HOURS_PER_DAY);

        patches[x][y].growth_macro = patches[x][y].gross_photo_macro - patches[x][y].respiration_macro - patches[x][y].senescence_macro
                                          - patches[x][y].scouring_macro;

        patches[x][y].macro += patches[x][y].growth_macro;

        if(patches[x][y].macro < 0.001)
                patches[x][y].macro = 0.001; //minimum biomass based on seed bank
}

void go_phyto(int x, int y, const Configuration & config)
{
        //minimum and maximum caps on biomass
        if( patches[x][y].phyto > 900000.0){
                patches[x][y].phyto = 900000.0;
        }
        if( patches[x][y].phyto < 0.001){
                patches[x][y].phyto = 0.001;
        }
        double base_temperature = 8.0; //base temperature for nominal growth
        g.Q10 = pow(g.theta, (g.temperature - base_temperature));
        double km = 10; //half saturation constant

        //this is the attenuation coefficient of phytoplank m^2/g of phyto plankton
        //TODO  Figure out if the uncommented light_k line was lost in translation from netgui
        //double light_k = 0.4;


        patches[x][y].respiration_phyto = (config.phytoRespiration / HOURS_PER_DAY) * patches[x][y].phyto * g.Q10;
        double pre_ln = (0.01 + g.photo_radiation  * exp(-1*patches[x][y].phyto * config.kPhyto * patches[x][y].depth));
        double be = (km + (g.photo_radiation * exp(-1 * patches[x][y].phyto * config.kPhyto * patches[x][y].depth)));
        //photosynthesis from phytoplankton derived from Huisman Weissing 1994

        patches[x][y].gross_photo_phyto = fabs(pre_ln / be) * (1.0 / patches[x][y].depth) * (patches[x][y].phyto / patches[x][y].turbidity) * g.Q10;
        patches[x][y].excretion_phyto = (config.phytoExcretion / HOURS_PER_DAY) * patches[x][y].phyto;
        patches[x][y].senescence_phyto = (config.phytoSenescence / HOURS_PER_DAY) * patches[x][y].phyto;
        patches[x][y].growth_phyto = patches[x][y].gross_photo_phyto - patches[x][y].excretion_phyto - 
                                 patches[x][y].respiration_phyto - patches[x][y].senescence_phyto;
}

void go_herbivore(int x, int y, const Configuration & config)
{
    patches[x][y].herbivore_phyto_prey_limitation = patches[x][y].phyto / (config.herbivoreAiPhyto - config.herbivoreGiPhyto);
    patches[x][y].herbivore_phyto_prey_limitation = assertRange(patches[x][y].herbivore_phyto_prey_limitation, 0.0, 1.0);

    patches[x][y].herbivore_peri_prey_limitation = patches[x][y].peri / (config.herbivoreAiPeri - config.herbivoreGiPeri);
    patches[x][y].herbivore_peri_prey_limitation = assertRange( patches[x][y].herbivore_peri_prey_limitation, 0.0, 1.0);

    patches[x][y].herbivore_waterdecomp_prey_limitation = patches[x][y].waterdecomp / (config.herbivoreAiWaterdecomp - config.herbivoreGiWaterdecomp);
    patches[x][y].herbivore_waterdecomp_prey_limitation = assertRange(patches[x][y].herbivore_waterdecomp_prey_limitation, 0.0, 1.0);

    patches[x][y].herbivore_space_limitation = 1.0 - ((patches[x][y].herbivore - config.herbivoreAj) /(config.herbivoreGj - config.herbivoreAj));
    patches[x][y].herbivore_space_limitation = assertRange(patches[x][y].herbivore_space_limitation, 0.0, 1.0);

    patches[x][y].herbivore_pred_phyto = config.herbivorePrefPhyto * (config.herbivoreMax / HOURS_PER_DAY) * patches[x][y].herbivore *
                                         patches[x][y].herbivore_space_limitation * patches[x][y].herbivore_phyto_prey_limitation;

    patches[x][y].herbivore_ingest_phyto = patches[x][y].herbivore_pred_phyto * (1.0 - config.herbivoreEgestion);

    patches[x][y].herbivore_pred_peri = config.herbivorePrefPeri * (config.herbivoreMax / HOURS_PER_DAY) * patches[x][y].herbivore
                                        * patches[x][y].herbivore_space_limitation * patches[x][y].herbivore_peri_prey_limitation;

    patches[x][y].herbivore_ingest_peri = patches[x][y].herbivore_pred_peri * (1.0 - config.herbivoreEgestion);

    patches[x][y].herbivore_pred_waterdecomp = config.herbivorePrefWaterdecomp * (config.herbivoreMax / HOURS_PER_DAY) *
                                               patches[x][y].herbivore * patches[x][y].herbivore_space_limitation * patches[x][y].herbivore_waterdecomp_prey_limitation;

    patches[x][y].herbivore_ingest_waterdecomp = patches[x][y].herbivore_pred_waterdecomp * (1.0 - config.herbivoreEgestion);

    patches[x][y].herbivore_respiration = (config.herbivoreRespiration / HOURS_PER_DAY) * patches[x][y].herbivore;

    patches[x][y].herbivore_excretion = (config.herbivoreExcretion / HOURS_PER_DAY) * patches[x][y].herbivore;

    patches[x][y].herbivore_senescence = (config.herbivoreSenescence / HOURS_PER_DAY) * patches[x][y].herbivore;
}

void go_waterdecomp(int x, int y, const Configuration &config)
{
    patches[x][y].waterdecomp_doc_prey_limitation = patches[x][y].DOC / (config.waterdecompAiDoc - config.waterdecompGiDoc);
    patches[x][y].waterdecomp_doc_prey_limitation = assertRange(patches[x][y].waterdecomp_doc_prey_limitation, 0.0, 1.0);

    patches[x][y].waterdecomp_poc_prey_limitation = patches[x][y].POC / (config.waterdecompAiPoc - config.waterdecompGiPoc);
    patches[x][y].waterdecomp_poc_prey_limitation = assertRange(patches[x][y].waterdecomp_poc_prey_limitation, 0.0, 1.0);

    patches[x][y].waterdecomp_space_limitation = 1.0 - ((patches[x][y].waterdecomp - config.waterdecompAj) / (config.waterdecompGj - config.waterdecompAj));
    patches[x][y].waterdecomp_space_limitation = assertRange(patches[x][y].waterdecomp_space_limitation, 0.0, 1.0);

    patches[x][y].waterdecomp_pred_doc = (config.waterdecompPrefDoc * (config.waterdecompMax / HOURS_PER_DAY) * patches[x][y].waterdecomp *
                                          patches[x][y].waterdecomp_space_limitation * patches[x][y].waterdecomp_doc_prey_limitation);

    patches[x][y].waterdecomp_ingest_doc = patches[x][y].waterdecomp_pred_doc;

    patches[x][y].waterdecomp_pred_poc = config.waterdecompPrefPoc * (config.waterdecompMax / HOURS_PER_DAY) * patches[x][y].waterdecomp *
                                         patches[x][y].waterdecomp_space_limitation * patches[x][y].waterdecomp_poc_prey_limitation;

    patches[x][y].waterdecomp_ingest_poc = patches[x][y].waterdecomp_pred_poc;

    patches[x][y].waterdecomp_respiration = (config.waterdecompRespiration / HOURS_PER_DAY) * patches[x][y].waterdecomp;

    patches[x][y].waterdecomp_excretion = (config.waterdecompExcretion / HOURS_PER_DAY) * patches[x][y].waterdecomp;

    patches[x][y].waterdecomp_senescence = (config.waterdecompSenescence / HOURS_PER_DAY) * patches[x][y].waterdecomp;
}


void go_seddecomp(int x, int y, const Configuration & config)
{
    patches[x][y].seddecomp_detritus_prey_limitation = patches[x][y].detritus / (config.seddecompAiDetritus - config.seddecompGiDetritus);

    if(patches[x][y].seddecomp_detritus_prey_limitation > 1.0)
        patches[x][y].seddecomp_detritus_prey_limitation = 1.0;
    else if(patches[x][y].seddecomp_detritus_prey_limitation < 0.0)
        patches[x][y].seddecomp_detritus_prey_limitation = 0.0;

    if( (config.seddecompGj - config.seddecompAj) != 0.0 ) {
        patches[x][y].seddecomp_space_limitation = 1.0 - ((patches[x][y].seddecomp - config.seddecompAj)/(config.seddecompGj - config.seddecompAj));
    } else {
        patches[x][y].seddecomp_space_limitation = 0.0;
    }

    if(patches[x][y].seddecomp_space_limitation > 1.0)
        patches[x][y].seddecomp_space_limitation = 1.0;
    else if(patches[x][y].seddecomp_space_limitation < 0.0)
        patches[x][y].seddecomp_space_limitation = 0.0;

    patches[x][y].seddecomp_pred_detritus = config.seddecompPrefDetritus * (config.seddecompMax / HOURS_PER_DAY) * patches[x][y].seddecomp *
                                            patches[x][y].seddecomp_detritus_prey_limitation *
                                            patches[x][y].seddecomp_space_limitation;

    patches[x][y].seddecomp_ingest_detritus = patches[x][y].seddecomp_pred_detritus;

    patches[x][y].seddecomp_respiration = (config.seddecompRespiration / HOURS_PER_DAY) * patches[x][y].seddecomp;

    patches[x][y].seddecomp_excretion = (config.seddecompExcretion / HOURS_PER_DAY) * patches[x][y].seddecomp;

    patches[x][y].seddecomp_senescence = (config.seddecompSenescence / HOURS_PER_DAY) * patches[x][y].seddecomp;
}

void go_sedconsumer(int x, int y, const Configuration & config)
{
    patches[x][y].sedconsumer_seddecomp_prey_limitation = patches[x][y].seddecomp / (config.sedconsumerAiSeddecomp - config.sedconsumerGiSeddecomp);

    if( patches[x][y].sedconsumer_seddecomp_prey_limitation > 1.0 )
        patches[x][y].sedconsumer_seddecomp_prey_limitation = 1.0;
    else if ( patches[x][y].sedconsumer_seddecomp_prey_limitation < 0.0 )
        patches[x][y].sedconsumer_seddecomp_prey_limitation = 0.0;

    patches[x][y].sedconsumer_peri_prey_limitation = patches[x][y].peri / (config.sedconsumerAiPeri - config.sedconsumerGiPeri);

    if( patches[x][y].sedconsumer_peri_prey_limitation > 1.0 )
        patches[x][y].sedconsumer_peri_prey_limitation = 1.0;
    else if (patches[x][y].sedconsumer_peri_prey_limitation < 0.0)
        patches[x][y].sedconsumer_peri_prey_limitation = 0.0;

    patches[x][y].sedconsumer_detritus_prey_limitation = patches[x][y].detritus / (config.sedconsumerAiDetritus - config.sedconsumerGiDetritus);

    if( patches[x][y].sedconsumer_detritus_prey_limitation > 1.0 )
        patches[x][y].sedconsumer_detritus_prey_limitation = 1.0;
    else if ( patches[x][y].sedconsumer_detritus_prey_limitation < 0.0 )
        patches[x][y].sedconsumer_detritus_prey_limitation = 0.0;

    patches[x][y].sedconsumer_space_limitation = 1.0 - ((patches[x][y].sedconsumer - config.sedconsumerAj)/(config.sedconsumerGj - config.sedconsumerAj));

    if( patches[x][y].sedconsumer_space_limitation > 1.0 )
        patches[x][y].sedconsumer_space_limitation = 1.0;
    else if ( patches[x][y].sedconsumer_space_limitation < 0.0 )
        patches[x][y].sedconsumer_space_limitation = 0.0;

    patches[x][y].sedconsumer_pred_peri = config.sedconsumerPrefPeri * (config.sedconsumerMax / HOURS_PER_DAY) * patches[x][y].sedconsumer *
                                          patches[x][y].sedconsumer_space_limitation * 
                                          patches[x][y].sedconsumer_peri_prey_limitation;

    patches[x][y].sedconsumer_ingest_peri = patches[x][y].sedconsumer_pred_peri * (1.0 - config.sedconsumerEgestionSeddecomp); // is it weird there is no peri version for this?

    patches[x][y].sedconsumer_pred_seddecomp = config.sedconsumerPrefSeddecomp * (config.sedconsumerMax / HOURS_PER_DAY) * patches[x][y].sedconsumer *
                                               patches[x][y].sedconsumer_space_limitation *
                                               patches[x][y].sedconsumer_seddecomp_prey_limitation;

    patches[x][y].sedconsumer_ingest_seddecomp = patches[x][y].sedconsumer_pred_seddecomp * (1.0 - config.sedconsumerEgestionSeddecomp);

    patches[x][y].sedconsumer_pred_detritus = config.sedconsumerPrefDetritus * (config.sedconsumerMax / HOURS_PER_DAY) * patches[x][y].sedconsumer *
                                              patches[x][y].sedconsumer_space_limitation * 
                                              patches[x][y].sedconsumer_detritus_prey_limitation;

    patches[x][y].sedconsumer_ingest_detritus = patches[x][y].sedconsumer_pred_detritus * (1.0 - config.sedconsumerEgestionDetritus);

    patches[x][y].sedconsumer_respiration = (config.sedconsumerRespiration / HOURS_PER_DAY) * patches[x][y].sedconsumer;

    patches[x][y].sedconsumer_excretion = (config.sedconsumerExcretion / HOURS_PER_DAY) * patches[x][y].sedconsumer;

    patches[x][y].sedconsumer_senescence = (config.sedconsumerSenescence / HOURS_PER_DAY) * patches[x][y].sedconsumer;
}

void go_consum(int x, int y, const Configuration & config)
{
    patches[x][y].consum_sedconsumer_prey_limitation = patches[x][y].sedconsumer / (config.consumerAiSedconsumer - config.consumerGiSedconsumer);
    if( patches[x][y].consum_sedconsumer_prey_limitation > 1.0 )
        patches[x][y].consum_sedconsumer_prey_limitation = 1.0;
    else if ( patches[x][y].consum_sedconsumer_prey_limitation < 0.0 )
        patches[x][y].consum_sedconsumer_prey_limitation = 0.0;

    patches[x][y].consum_herbivore_prey_limitation = patches[x][y].herbivore / (config.consumerAiHerbivore - config.consumerGiHerbivore);
    if( patches[x][y].consum_herbivore_prey_limitation > 1.0 )
        patches[x][y].consum_herbivore_prey_limitation = 1.0;
    else if ( patches[x][y].consum_herbivore_prey_limitation < 0.0 )
        patches[x][y].consum_herbivore_prey_limitation = 0.0;

    patches[x][y].consum_space_limitation = 1.0 - ((patches[x][y].consum - config.consumerAj)/(config.consumerGj - config.consumerAj));
    if( patches[x][y].consum_space_limitation > 1.0 )
        patches[x][y].consum_space_limitation = 1.0;
    else if ( patches[x][y].consum_space_limitation < 0.0 )
        patches[x][y].consum_space_limitation = 0.0;

    patches[x][y].consum_pred_herbivore = config.consumerPrefHerbivore * (config.consumerMax / HOURS_PER_DAY) * patches[x][y].consum *
                                          patches[x][y].consum_space_limitation * 
                                          patches[x][y].consum_herbivore_prey_limitation;

    patches[x][y].consum_ingest_herbivore = patches[x][y].consum_pred_herbivore * (1.0- config.consumerEgestion);

    patches[x][y].consum_pred_sedconsumer = config.consumerPrefSedconsumer * (config.consumerMax / HOURS_PER_DAY) * patches[x][y].consum *
                                            patches[x][y].consum_space_limitation *
                                            patches[x][y].consum_sedconsumer_prey_limitation;

    patches[x][y].consum_ingest_sedconsumer = patches[x][y].consum_pred_sedconsumer * (1.0 - config.consumerEgestion);

    patches[x][y].consum_respiration = (config.consumerRespiration / HOURS_PER_DAY) * patches[x][y].consum;

    patches[x][y].consum_excretion = (config.consumerExcretion / HOURS_PER_DAY) * patches[x][y].consum;

    patches[x][y].consum_senescence = (config.consumerSenescence / HOURS_PER_DAY) * patches[x][y].consum;
}

void go_DOC(int x, int y, const Configuration & config)
{
    // 4% of photosynthetic gets released into the water column. Wetzel lit.
    patches[x][y].macro_exudation = config.macroExcretion * patches[x][y].macro;

    // Dead objects < 1um are considered DOC in Wetzel book..
    patches[x][y].micro_death = patches[x][y].senescence_macro * .01 + patches[x][y].senescence_phyto * .01;

    // *need reference
    patches[x][y].excretion = patches[x][y].herbivore_excretion + patches[x][y].waterdecomp_excretion + 
                              patches[x][y].seddecomp_excretion + patches[x][y].sedconsumer_excretion + 
                              patches[x][y].consum_excretion + patches[x][y].excretion_phyto + patches[x][y].peri_excretion;

    // *need reference
    patches[x][y].flocculation = .01 * patches[x][y].DOC;

    patches[x][y].DOC_growth = patches[x][y].macro_exudation + patches[x][y].micro_death + patches[x][y].excretion;
}

void go_POC(int x, int y, const Configuration & config)
{
    if(patches[x][y].velocity > 0.0)
    {
        // exchange between POC and detritus determined by an approximation of Stoke's Law
        patches[x][y].detritus_POC_transfer = patches[x][y].detritus * (.25 * log10(((patches[x][y].velocity / 40.0 ) + .0001) + 1.0));
    }

    if(patches[x][y].detritus_POC_transfer > 1.0)
    {
        // cap at 100%. *need reference
        patches[x][y].detritus_POC_transfer = 1.0;
    }

    // approximations of the percention of dead objects < 10um that will be in water column; Wetzel Limnology textbook.
    patches[x][y].small_death = patches[x][y].senescence_macro * 0.09 + patches[x][y].senescence_phyto * 0.09 + 
                                patches[x][y].scouring_macro * 0.1 + patches[x][y].waterdecomp_senescence * 
                                0.7 + 0.3 * patches[x][y].peri_senescence;

    // flocculation, leaching approximation
    patches[x][y].POC_growth = patches[x][y].flocculation + patches[x][y].detritus_POC_transfer;
}

void go_detritus(int x, int y, const Configuration & config)
{
    if(patches[x][y].velocity > 0.0)
    {
        patches[x][y].POC_detritus_transfer = patches[x][y].POC * (1.0 - (0.25 * log10((( patches[x][y].velocity / 40.0) + 0.0001) + 1.0)));
    }

    if(patches[x][y].POC_detritus_transfer < 0.0)
    {
        patches[x][y].POC_detritus_transfer = 0.0;
    }

    if(patches[x][y].velocity == 0.0)
    {
        patches[x][y].POC_detritus_transfer = patches[x][y].POC * 0.9; 
    }

    if(patches[x][y].gross_photo_macro < 0.0)
    {
        // to incorporate scoured macrophytes into detritus
        patches[x][y].macro_death = 0.0 - patches[x][y].gross_photo_macro;
    }

    // Dead objects > 10um will sink Wetzel book..
    patches[x][y].large_death = patches[x][y].senescence_macro * 0.9 + patches[x][y].scouring_macro * 0.9 + 
                                patches[x][y].senescence_phyto * 0.9 + patches[x][y].seddecomp_senescence + 
                                patches[x][y].waterdecomp_senescence * 0.3 + patches[x][y].herbivore_senescence + 
                                patches[x][y].sedconsumer_senescence + patches[x][y].consum_senescence + 0.07 * patches[x][y].peri_senescence;

    patches[x][y].egestion = config.herbivoreEgestion + patches[x][y].sedconsumer_egestion + config.consumerEgestion;

    patches[x][y].detritus_growth = patches[x][y].large_death + patches[x][y].POC_detritus_transfer + 
                                    patches[x][y].egestion + patches[x][y].macro_death;
}
