#include "patch.h"

patch** patches;

/**
 * Updates the patches
 * @param x the X coord of the patch
 * @param y the Y coord of the patch
*/
void update_patches(int x, int y){

        patches[x][y].turbidity = ( .29587 + g.gui_tss) + (g.gui_k_phyto * (patches[x][y].phyto/ 900.0) ) + (g.gui_k_macro * (patches[x][y].macro / 900.0) );

        if(patches[x][y].turbidity > 30.0){
                patches[x][y].turbidity = 30.0;
        }
        if(patches[x][y].turbidity < 0.0){
                patches[x][y].turbidity = 0.01;
        }

        //the amount of light that reaches the bottom of a water column
        patches[x][y].bottom_light = (g.photo_radiation * exp( (-1*patches[x][y].depth)*patches[x][y].turbidity )); 
        g.Aj_peri = patches[x][y].macro / 10.0 ;
        g.Gj_peri = patches[x][y].macro / 2.0;
        g.Aj_seddecomp = patches[x][y].detritus / 20.0;
        g.Gj_seddecomp = patches[x][y].detritus / 5.0;
}


/**
 * Ensures a bound
 * @param value The value to test
 * @param low value must be higher than this value
 * @param high value must be lower than this value
 * @return The bounded value
*/
double assertRange(double value, double low, double high){
    if(value < low)
        return low;
    else if(value > high)
        return high;
    else
        return value;
}

void go_macro(int x, int y){
        g.Q10 = pow(g.theta, (g.temperature - g.macro_base_temp));

        if(patches[x][y].velocity < g.macro_vel_max){
                patches[x][y].K = g.max_area * (g.gui_macro_mass_max - (g.gui_macro_mass_max  / g.gui_macro_vel_max) * patches[x][y].velocity);
        }
        else{
                patches[x][y].K = 0.01;
        }
        //Same at bottom-light
        double macro_light = g.photo_radiation * exp( (-1*patches[x][y].depth) * patches[x][y].turbidity );
        
        patches[x][y].gross_photo_macro = (g.gui_gross_macro_coef * patches[x][y].macro * ( macro_light / ( macro_light + 10.0)) * g.Q10 * 
                                               (patches[x][y].K - patches[x][y].macro) / patches[x][y].K);

        patches[x][y].respiration_macro = (g.resp_macro_coef / 24.0) * patches[x][y].macro * g.Q10;

        patches[x][y].senescence_macro = g.sen_macro_coef * patches[x][y].macro / 24.0;

        patches[x][y].growth_macro = patches[x][y].gross_photo_macro - patches[x][y].respiration_macro - patches[x][y].senescence_macro
                                          - patches[x][y].scouring_macro;

        patches[x][y].macro += patches[x][y].growth_macro;

        if(patches[x][y].macro < 0.001)
                patches[x][y].macro = 0.001; //minimum biomass based on seed bank
}

void go_phyto(int x,int y){ 
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


        patches[x][y].respiration_phyto = g.r_phyto * patches[x][y].phyto * g.Q10;
        double pre_ln = (0.01 + g.photo_radiation  * exp(-1*patches[x][y].phyto * g.gui_k_phyto * patches[x][y].depth));
        double be = (km + (g.photo_radiation * exp(-1 * patches[x][y].phyto * g.gui_k_phyto * patches[x][y].depth)));
        //photosynthesis from phytoplankton derived from Huisman Weissing 1994

        patches[x][y].gross_photo_phyto = fabs(pre_ln / be) * (1.0 / patches[x][y].depth) * (patches[x][y].phyto / patches[x][y].turbidity) * g.Q10;
        patches[x][y].excretion_phyto = g.e_phyto * patches[x][y].phyto;
        patches[x][y].senescence_phyto = g.s_phyto * patches[x][y].phyto;
        patches[x][y].growth_phyto = patches[x][y].gross_photo_phyto - patches[x][y].excretion_phyto - 
                                 patches[x][y].respiration_phyto - patches[x][y].senescence_phyto;
}

void go_herbivore(int x, int y){

        patches[x][y].herbivore_phyto_prey_limitation = patches[x][y].phyto / (g.Ai_herbivore_phyto - g.Gi_herbivore_phyto);
        patches[x][y].herbivore_phyto_prey_limitation = assertRange(patches[x][y].herbivore_phyto_prey_limitation, 0.0, 1.0);

    patches[x][y].herbivore_peri_prey_limitation = patches[x][y].peri / (g.Ai_herbivore_peri - g.Gi_herbivore_peri);
    patches[x][y].herbivore_peri_prey_limitation = assertRange( patches[x][y].herbivore_peri_prey_limitation, 0.0, 1.0);

    patches[x][y].herbivore_waterdecomp_prey_limitation = patches[x][y].waterdecomp / (g.Ai_herbivore_waterdecomp - g.Gi_herbivore_waterdecomp);
    patches[x][y].herbivore_waterdecomp_prey_limitation = assertRange(patches[x][y].herbivore_waterdecomp_prey_limitation, 0.0, 1.0);

    patches[x][y].herbivore_space_limitation = 1.0 - ((patches[x][y].herbivore - g.Aj_herbivore) /(g.Gj_herbivore - g.Aj_herbivore));
    patches[x][y].herbivore_space_limitation = assertRange(patches[x][y].herbivore_space_limitation, 0.0, 1.0);

    patches[x][y].herbivore_pred_phyto = g.pref_herbivore_phyto * g.max_herbivore * patches[x][y].herbivore * 
                                         patches[x][y].herbivore_space_limitation * patches[x][y].herbivore_phyto_prey_limitation;

    patches[x][y].herbivore_ingest_phyto = patches[x][y].herbivore_pred_phyto * (1.0 - g.herbivore_egestion);

    patches[x][y].herbivore_pred_peri = g.pref_herbivore_peri * g.max_herbivore * patches[x][y].herbivore
                                        * patches[x][y].herbivore_space_limitation * patches[x][y].herbivore_peri_prey_limitation;

    patches[x][y].herbivore_ingest_peri = patches[x][y].herbivore_pred_peri * (1.0 - g.herbivore_egestion);

    patches[x][y].herbivore_pred_waterdecomp = g.pref_herbivore_waterdecomp * g.max_herbivore *
                                               patches[x][y].herbivore * patches[x][y].herbivore_space_limitation * patches[x][y].herbivore_waterdecomp_prey_limitation;

    patches[x][y].herbivore_ingest_waterdecomp = patches[x][y].herbivore_pred_waterdecomp * (1.0 - g.herbivore_egestion);

    patches[x][y].herbivore_respiration = g.r_herbivore * patches[x][y].herbivore;

    patches[x][y].herbivore_excretion = g.e_herbivore * patches[x][y].herbivore;

    patches[x][y].herbivore_senescence = g.s_herbivore * patches[x][y].herbivore;
}

void go_waterdecomp(int x, int y){

    patches[x][y].waterdecomp_doc_prey_limitation = patches[x][y].DOC / (g.Ai_waterdecomp_DOC - g.Gi_waterdecomp_DOC);
    patches[x][y].waterdecomp_doc_prey_limitation = assertRange(patches[x][y].waterdecomp_doc_prey_limitation, 0.0, 1.0);

    patches[x][y].waterdecomp_poc_prey_limitation = patches[x][y].POC / (g.Ai_waterdecomp_POC - g.Gi_waterdecomp_POC);
    patches[x][y].waterdecomp_poc_prey_limitation = assertRange(patches[x][y].waterdecomp_poc_prey_limitation, 0.0, 1.0);

    patches[x][y].waterdecomp_space_limitation = 1.0 - ((patches[x][y].waterdecomp - g.Aj_waterdecomp) / (g.Gj_waterdecomp - g.Aj_waterdecomp));
    patches[x][y].waterdecomp_space_limitation = assertRange(patches[x][y].waterdecomp_space_limitation, 0.0, 1.0);

    patches[x][y].waterdecomp_pred_doc = (g.pref_waterdecomp_DOC * g.max_waterdecomp * patches[x][y].waterdecomp * 
                                          patches[x][y].waterdecomp_space_limitation * patches[x][y].waterdecomp_doc_prey_limitation);

    patches[x][y].waterdecomp_ingest_doc = patches[x][y].waterdecomp_pred_doc;

    patches[x][y].waterdecomp_pred_poc = g.pref_waterdecomp_POC * g.max_waterdecomp * patches[x][y].waterdecomp * 
                                         patches[x][y].waterdecomp_space_limitation * patches[x][y].waterdecomp_poc_prey_limitation;

    patches[x][y].waterdecomp_ingest_poc = patches[x][y].waterdecomp_pred_poc;

    patches[x][y].waterdecomp_respiration = g.r_waterdecomp * patches[x][y].waterdecomp;

    patches[x][y].waterdecomp_excretion = g.e_waterdecomp * patches[x][y].waterdecomp;

    patches[x][y].waterdecomp_senescence = g.s_waterdecomp * patches[x][y].waterdecomp;
}


void go_seddecomp(int x, int y) {
    
    // update seddecomp_detritus_prey_limitation
    patches[x][y].seddecomp_detritus_prey_limitation = patches[x][y].detritus / (g.Ai_seddecomp_detritus - g.Gi_seddecomp_detritus);

    if(patches[x][y].seddecomp_detritus_prey_limitation > 1.0)
        patches[x][y].seddecomp_detritus_prey_limitation = 1.0;
    else if(patches[x][y].seddecomp_detritus_prey_limitation < 0.0)
        patches[x][y].seddecomp_detritus_prey_limitation = 0.0;

    // update seddecomp_space_limitation
    if( (g.Gj_seddecomp - g.Aj_seddecomp) != 0.0 ) {
        patches[x][y].seddecomp_space_limitation = 1.0 - ((patches[x][y].seddecomp - g.Aj_seddecomp)/(g.Gj_seddecomp - g.Aj_seddecomp));
    } else {
        patches[x][y].seddecomp_space_limitation = 0.0;
    }

    if(patches[x][y].seddecomp_space_limitation > 1.0)
        patches[x][y].seddecomp_space_limitation = 1.0;
    else if(patches[x][y].seddecomp_space_limitation < 0.0)
        patches[x][y].seddecomp_space_limitation = 0.0;

    // update seddecomp_pred_detritus
    patches[x][y].seddecomp_pred_detritus = g.pref_seddecomp_detritus*g.max_seddecomp*patches[x][y].seddecomp*
                                            patches[x][y].seddecomp_detritus_prey_limitation *
                                            patches[x][y].seddecomp_space_limitation;

    // update seddecomp_ingest_detritus
    patches[x][y].seddecomp_ingest_detritus = patches[x][y].seddecomp_pred_detritus;

    // update seddecomp_respiration
    patches[x][y].seddecomp_respiration = g.r_seddecomp * patches[x][y].seddecomp;

    // update seddecomp_excretion
    patches[x][y].seddecomp_excretion = g.e_seddecomp * patches[x][y].seddecomp;

    // update seddecomp_senescence
    patches[x][y].seddecomp_senescence = g.s_seddecomp * patches[x][y].seddecomp;
}

void go_sedconsumer(int x, int y) {
    
    // update sedconsumer_seddecomp_prey_limitation
    patches[x][y].sedconsumer_seddecomp_prey_limitation = patches[x][y].seddecomp / (g.Ai_sedconsumer_seddecomp - g.Gi_sedconsumer_seddecomp);

    if( patches[x][y].sedconsumer_seddecomp_prey_limitation > 1.0 )
        patches[x][y].sedconsumer_seddecomp_prey_limitation = 1.0;
    else if ( patches[x][y].sedconsumer_seddecomp_prey_limitation < 0.0 )
        patches[x][y].sedconsumer_seddecomp_prey_limitation = 0.0;

    // update sedconsumer_peri_prey_limitation
    patches[x][y].sedconsumer_peri_prey_limitation = patches[x][y].peri / (g.Ai_sedconsumer_peri - g.Gi_sedconsumer_peri);

    if( patches[x][y].sedconsumer_peri_prey_limitation > 1.0 )
        patches[x][y].sedconsumer_peri_prey_limitation = 1.0;
    else if (patches[x][y].sedconsumer_peri_prey_limitation < 0.0)
        patches[x][y].sedconsumer_peri_prey_limitation = 0.0;

    // update sedconsumer_detritus_prey_limitation
    patches[x][y].sedconsumer_detritus_prey_limitation = patches[x][y].detritus / (g.Ai_sedconsumer_detritus - g.Gi_sedconsumer_detritus);

    if( patches[x][y].sedconsumer_detritus_prey_limitation > 1.0 )
        patches[x][y].sedconsumer_detritus_prey_limitation = 1.0;
    else if ( patches[x][y].sedconsumer_detritus_prey_limitation < 0.0 )
        patches[x][y].sedconsumer_detritus_prey_limitation = 0.0;

    // update sedconsumer_space_limitation
    patches[x][y].sedconsumer_space_limitation = 1.0 - ((patches[x][y].sedconsumer - g.Aj_sedconsumer)/(g.Gj_sedconsumer - g.Aj_sedconsumer));

    if( patches[x][y].sedconsumer_space_limitation > 1.0 )
        patches[x][y].sedconsumer_space_limitation = 1.0;
    else if ( patches[x][y].sedconsumer_space_limitation < 0.0 )
        patches[x][y].sedconsumer_space_limitation = 0.0;

    // update sedconsumer_pred_peri
    patches[x][y].sedconsumer_pred_peri = g.pref_sedconsumer_peri * g.max_sedconsumer * patches[x][y].sedconsumer *
                                          patches[x][y].sedconsumer_space_limitation * 
                                          patches[x][y].sedconsumer_peri_prey_limitation;

    // update sedconsumer_ingest_peri
    patches[x][y].sedconsumer_ingest_peri = patches[x][y].sedconsumer_pred_peri * (1.0 - g.sedconsumer_egestion_seddecomp);

    // update sedconsumer_pred_seddecomp
    patches[x][y].sedconsumer_pred_seddecomp = g.pref_sedconsumer_seddecomp * g.max_sedconsumer * patches[x][y].sedconsumer *
                                               patches[x][y].sedconsumer_space_limitation *
                                               patches[x][y].sedconsumer_seddecomp_prey_limitation;

    // update sedconsumer_ingest_seddecomp
    patches[x][y].sedconsumer_ingest_seddecomp = patches[x][y].sedconsumer_pred_seddecomp * (1.0 - g.sedconsumer_egestion_seddecomp);

    // update sedconsumer_pred_detritus
    patches[x][y].sedconsumer_pred_detritus = g.pref_sedconsumer_detritus * g.max_sedconsumer * patches[x][y].sedconsumer *
                                              patches[x][y].sedconsumer_space_limitation * 
                                              patches[x][y].sedconsumer_detritus_prey_limitation;

    // update sedconsumer_ingest_detritus
    patches[x][y].sedconsumer_ingest_detritus = patches[x][y].sedconsumer_pred_detritus * (1.0 - g.sedconsumer_egestion_detritus);

    // update sedconsumer_respiration
    patches[x][y].sedconsumer_respiration = g.r_sedconsumer * patches[x][y].sedconsumer;

    // update sedconsumer_excretion
    patches[x][y].sedconsumer_excretion = g.e_sedconsumer * patches[x][y].sedconsumer;

    // update sedconsumer_senescence
    patches[x][y].sedconsumer_senescence = g.s_sedconsumer * patches[x][y].sedconsumer;
}

void go_consum(int x,int y) {

    // update consum_sedconsumer_prey_limitation
    patches[x][y].consum_sedconsumer_prey_limitation = patches[x][y].sedconsumer / (g.Ai_consum_sedconsumer - g.Gi_consum_sedconsumer);
    if( patches[x][y].consum_sedconsumer_prey_limitation > 1.0 )
        patches[x][y].consum_sedconsumer_prey_limitation = 1.0;
    else if ( patches[x][y].consum_sedconsumer_prey_limitation < 0.0 )
        patches[x][y].consum_sedconsumer_prey_limitation = 0.0;

    // update consum_herbivore_prey_limitation
    patches[x][y].consum_herbivore_prey_limitation = patches[x][y].herbivore / (g.Ai_consum_herbivore - g.Gi_consum_herbivore);
    if( patches[x][y].consum_herbivore_prey_limitation > 1.0 )
        patches[x][y].consum_herbivore_prey_limitation = 1.0;
    else if ( patches[x][y].consum_herbivore_prey_limitation < 0.0 )
        patches[x][y].consum_herbivore_prey_limitation = 0.0;

    // update consum_space_limitation
    patches[x][y].consum_space_limitation = 1.0 - ((patches[x][y].consum - g.Aj_consum)/(g.Gj_consum - g.Aj_consum));
    if( patches[x][y].consum_space_limitation > 1.0 )
        patches[x][y].consum_space_limitation = 1.0;
    else if ( patches[x][y].consum_space_limitation < 0.0 )
        patches[x][y].consum_space_limitation = 0.0;

    // update consum_pred_herbivore
    patches[x][y].consum_pred_herbivore = g.pref_consum_herbivore * g.max_consum * patches[x][y].consum *
                                          patches[x][y].consum_space_limitation * 
                                          patches[x][y].consum_herbivore_prey_limitation;

    // update consum_ingest_herbivore
    patches[x][y].consum_ingest_herbivore = patches[x][y].consum_pred_herbivore * (1.0- g.consum_egestion);

    // update consum_pred_sedconsumer
    patches[x][y].consum_pred_sedconsumer = g.pref_consum_sedconsumer * g.max_consum * patches[x][y].consum *
                                            patches[x][y].consum_space_limitation *
                                            patches[x][y].consum_sedconsumer_prey_limitation;

    // update consum_ingest_sedconsumer
    patches[x][y].consum_ingest_sedconsumer = patches[x][y].consum_pred_sedconsumer * (1.0 - g.consum_egestion);

    // update consum_respiration
    patches[x][y].consum_respiration = g.r_consum * patches[x][y].consum;

    // update consum_excretion
    patches[x][y].consum_excretion = g.e_consum * patches[x][y].consum;

    // update consum_senescence
    patches[x][y].consum_senescence = g.s_consum * patches[x][y].consum;
}

void go_DOC(int x, int y)
{
    // 4% of photosynthetic gets released into the water column. Wetzel lit.
    patches[x][y].macro_exudation = g.e_macro * patches[x][y].macro;

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

void go_POC(int x, int y)
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

void go_detritus(int x, int y)
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

    patches[x][y].egestion = g.herbivore_egestion + patches[x][y].sedconsumer_egestion + g.consum_egestion;

    patches[x][y].detritus_growth = patches[x][y].large_death + patches[x][y].POC_detritus_transfer + 
                                    patches[x][y].egestion + patches[x][y].macro_death;
}
