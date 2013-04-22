#include "patchcomputation.h"

void PatchComputation::updatePatches(PatchCollection & p, const Configuration & config, int currPAR ) {
    #pragma omp for
    for(int i = 0; i < p.getSize(); i++) {
        //Only process patches if they currently contain water
        if(!p.hasWater[i]) {
            continue;
        }



        // From 2011 team's update_patches function

        p.turbidity[i] = ( .29587 + config.tss)
                + (config.kPhyto * (p.phyto[i]/ 900.0) )
                + (config.kMacro * (p.macro[i] / 900.0) );

        if(p.turbidity[i] < 0.0){
            p.turbidity[i] = 0.01;
        }

        //the amount of light that reaches the bottom of a water column
        p.bottom_light[i] = currPAR
                * exp( (-1 * p.depth[i]) * p.turbidity[i] );

        //TODO why is this code altering the config? Config should never be edited by model. -ECP
        //Also these two do not ever get used.  Commenting them out for now.
        //config.periAj = p.macro[i] / 10.0 ;
        //config.periGj = p.macro[i] / 2.0;

        // TODO These config values never get used elsewhere before being overwritten here
        // Is this correct behavior?  Converting to local variables for now. Also moving
        // them to where they are used as p.detritus is not altered before then.
        //config.seddecompAj = p.detritus[i] / 20.0;
        //config.seddecompGj = p.detritus[i] / 5.0;

    }
}

void PatchComputation::macro(PatchCollection & p, const Configuration & config, int currPAR, int currWaterTemp, double currGrowthRate) {
    #pragma omp for
    for(int i = 0; i < p.getSize(); i++) {
        //Only process patches if they currently contain water
        if(!p.hasWater[i]) {
            continue;
        }



        // From 2011 team's go_macro function

        //TODO Ask Kevin what theta is and why it is 1.072.  I want to add
        //it to the constants file but "THETA" is really ambiguous. -ECP
        double Q10 = pow(THETA, (currWaterTemp - config.macroTemp));

        //TODO pull velocity from hydrofile rather than patches
        if(p.flowMagnitude[i] < config.macroVelocityMax) {
            p.K[i] = PATCH_AREA
                    * (config.macroMassMax
                       - (config.macroMassMax  / config.macroVelocityMax)
                       * p.flowMagnitude[i]);
        } else {
            p.K[i] = 0.01;
        }
        //Same at bottom-light
        double macro_light = currPAR * exp( (-1*p.depth[i]) * p.turbidity[i] );

        p.gross_photo_macro[i] = config.macroGross * p.macro[i]
                * ( macro_light / ( macro_light + 10.0)) * Q10
                * ( p.K[i] - p.macro[i]) / p.K[i];

        p.respiration_macro[i] = (config.macroRespiration / HOURS_PER_DAY)
                * p.macro[i] * Q10;

        p.senescence_macro[i] = (config.macroSenescence / HOURS_PER_DAY)
                * (p.macro[i] / HOURS_PER_DAY);

        p.growth_macro[i] = (p.gross_photo_macro[i] - p.respiration_macro[i]
                - p.senescence_macro[i] - p.scouring_macro[i]) * currGrowthRate;

        p.macro[i] += p.growth_macro[i];

        Utility::boundLower(p.macro[i], 0.001);
    }
}

void PatchComputation::phyto(PatchCollection & p, const Configuration & config, int currPAR, int currWaterTemp) {
    #pragma omp for
    for(int i = 0; i < p.getSize(); i++) {
        //Only process patches if they currently contain water
        if(!p.hasWater[i]) {
            continue;
        }



        // From 2011 team's go_phyto function

        //minimum and maximum caps on biomass
        Utility::boundValue(p.phyto[i], 0.001, 900000.0);


        //base temperature for nominal growth
        //TODO What is base temperature and why is it a magic number?
        double base_temperature = 8.0;
        double Q10 = pow(THETA, (currWaterTemp - base_temperature));
        double km = 10; //half saturation constant


        // TODO  Figure out if the following commented light_k lines were lost in translation from netgui
        // It is set but never used. -ECP
        //this is the attenuation coefficient of phytoplank m^2/g of phyto plankton
        //double light_k = 0.4;


        p.respiration_phyto[i] = (config.phytoRespiration / HOURS_PER_DAY) * p.phyto[i] * Q10;

        double pre_ln = 0.01 + currPAR
                * exp(-1 * p.phyto[i] * config.kPhyto * p.depth[i]);
        double be = km + currPAR
                * exp(-1 * p.phyto[i] * config.kPhyto * p.depth[i]);

        //photosynthesis from phytoplankton derived from Huisman Weissing 1994
        p.gross_photo_phyto[i] = fabs(pre_ln / be) * (1.0 / p.depth[i])
                * (p.phyto[i] / p.turbidity[i]) * Q10;
        p.excretion_phyto[i] = (config.phytoExcretion / HOURS_PER_DAY) * p.phyto[i];
        p.senescence_phyto[i] = (config.phytoSenescence / HOURS_PER_DAY) * p.phyto[i];
        p.growth_phyto[i] = p.gross_photo_phyto[i] - p.excretion_phyto[i] -
                p.respiration_phyto[i] - p.senescence_phyto[i];
    }
}

void PatchComputation::herbivore(PatchCollection & p, const Configuration & config) {
    #pragma omp for
    for(int i = 0; i < p.getSize(); i++) {
        //Only process patches if they currently contain water
        if(!p.hasWater[i]) {
            continue;
        }



        // From 2011 team's go_herbivore function

        p.herbivore_phyto_prey_limitation[i] = p.phyto[i]
                / (config.herbivoreAiPhyto - config.herbivoreGiPhyto);
        Utility::boundPercentage(p.herbivore_phyto_prey_limitation[i]);

        p.herbivore_peri_prey_limitation[i] = p.peri[i]
                / (config.herbivoreAiPeri - config.herbivoreGiPeri);
        Utility::boundPercentage(p.herbivore_peri_prey_limitation[i]);

        p.herbivore_waterdecomp_prey_limitation[i] = p.waterdecomp[i]
                / (config.herbivoreAiWaterdecomp - config.herbivoreGiWaterdecomp);
        Utility::boundPercentage(p.herbivore_waterdecomp_prey_limitation[i]);

        p.herbivore_space_limitation[i] = 1.0
                - ((p.herbivore[i] - config.herbivoreAj)
                    / (config.herbivoreGj - config.herbivoreAj));
        Utility::boundPercentage(p.herbivore_space_limitation[i]);

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
    }
}

void PatchComputation::waterDecomp(PatchCollection & p, const Configuration & config) {
    #pragma omp for
    for(int i = 0; i < p.getSize(); i++) {
        //Only process patches if they currently contain water
        if(!p.hasWater[i]) {
            continue;
        }



        // From 2011 team's go_waterdecomp function

        p.waterdecomp_doc_prey_limitation[i] = p.DOC[i]
                / (config.waterdecompAiDoc - config.waterdecompGiDoc);
        Utility::boundPercentage(p.waterdecomp_doc_prey_limitation[i]);

        p.waterdecomp_poc_prey_limitation[i] = p.POC[i]
                / (config.waterdecompAiPoc - config.waterdecompGiPoc);
        Utility::boundPercentage(p.waterdecomp_poc_prey_limitation[i]);

        p.waterdecomp_space_limitation[i] = 1.0
                - ((p.waterdecomp[i] - config.waterdecompAj)
                    / (config.waterdecompGj - config.waterdecompAj));
        Utility::boundPercentage(p.waterdecomp_space_limitation[i]);

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
    }
}

void PatchComputation::sedDecomp(PatchCollection & p, const Configuration & config) {
    #pragma omp for
    for(int i = 0; i < p.getSize(); i++) {
        //Only process patches if they currently contain water
        if(!p.hasWater[i]) {
            continue;
        }



        // From 2011 team's go_seddecomp function

        p.seddecomp_detritus_prey_limitation[i] = p.detritus[i]
                / (config.seddecompAiDetritus - config.seddecompGiDetritus);
        Utility::boundPercentage(p.seddecomp_detritus_prey_limitation[i]);

        double seddecompAj = p.detritus[i] / 20.0;
        double seddecompGj = p.detritus[i] / 5.0;

        //TODO Comparing floats like this is wrong and is likely a bug -ECP
        //TODO Also, why is this calculation different from the others? -ECP
        if( (seddecompGj - seddecompAj) != 0.0 ) {
            p.seddecomp_space_limitation[i] = 1.0
                    - ((p.seddecomp[i] - seddecompAj)
                       / (seddecompGj - seddecompAj));
            Utility::boundPercentage(p.seddecomp_space_limitation[i]);
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
    }
}

void PatchComputation::sedConsumer(PatchCollection & p, const Configuration & config) {
    #pragma omp for
    for(int i = 0; i < p.getSize(); i++) {
        //Only process patches if they currently contain water
        if(!p.hasWater[i]) {
            continue;
        }



        // From 2011 team's go_sedconsumer function

        p.sedconsumer_seddecomp_prey_limitation[i] = p.seddecomp[i]
                / (config.sedconsumerAiSeddecomp - config.sedconsumerGiSeddecomp);
        Utility::boundPercentage(p.sedconsumer_seddecomp_prey_limitation[i]);

        p.sedconsumer_peri_prey_limitation[i] = p.peri[i]
                / (config.sedconsumerAiPeri - config.sedconsumerGiPeri);
        Utility::boundPercentage(p.sedconsumer_peri_prey_limitation[i]);

        p.sedconsumer_detritus_prey_limitation[i] = p.detritus[i]
                / (config.sedconsumerAiDetritus - config.sedconsumerGiDetritus);
        Utility::boundPercentage(p.sedconsumer_detritus_prey_limitation[i]);

        p.sedconsumer_space_limitation[i] = 1.0
                - ((p.sedconsumer[i] - config.sedconsumerAj)
                   / (config.sedconsumerGj - config.sedconsumerAj));
        Utility::boundPercentage(p.sedconsumer_space_limitation[i]);

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
    }
}

void PatchComputation::consumer(PatchCollection & p, const Configuration & config) {

    #pragma omp for
    for(int i = 0; i < p.getSize(); i++) {
        //Only process patches if they currently contain water
        if(!p.hasWater[i]) {
            continue;
        }



        // From 2011 team's go_consumer function

        p.consumer_sedconsumer_prey_limitation[i] = p.sedconsumer[i]
                / (config.consumerAiSedconsumer - config.consumerGiSedconsumer);
        Utility::boundPercentage(p.consumer_sedconsumer_prey_limitation[i]);

        p.consumer_herbivore_prey_limitation[i] = p.herbivore[i]
                / (config.consumerAiHerbivore - config.consumerGiHerbivore);
        Utility::boundPercentage(p.consumer_herbivore_prey_limitation[i]);

        p.consumer_space_limitation[i] = 1.0
                - ((p.consumer[i] - config.consumerAj)
                   / (config.consumerGj - config.consumerAj));
        Utility::boundPercentage(p.consumer_space_limitation[i]);

        p.consumer_pred_herbivore[i] = config.consumerPrefHerbivore
                * (config.consumerMax / HOURS_PER_DAY) * p.consumer[i]
                * p.consumer_space_limitation[i] * p.consumer_herbivore_prey_limitation[i];
        p.consumer_ingest_herbivore[i] = p.consumer_pred_herbivore[i] * (1.0- config.consumerEgestion);

        p.consumer_pred_sedconsumer[i] = config.consumerPrefSedconsumer
                * (config.consumerMax / HOURS_PER_DAY) * p.consumer[i]
                * p.consumer_space_limitation[i] * p.consumer_sedconsumer_prey_limitation[i];
        p.consumer_ingest_sedconsumer[i] = p.consumer_pred_sedconsumer[i] * (1.0 - config.consumerEgestion);

        p.consumer_respiration[i] = (config.consumerRespiration / HOURS_PER_DAY) * p.consumer[i];
        p.consumer_excretion[i] = (config.consumerExcretion / HOURS_PER_DAY) * p.consumer[i];
        p.consumer_senescence[i] = (config.consumerSenescence / HOURS_PER_DAY) * p.consumer[i];
    }
}

void PatchComputation::DOC(PatchCollection & p, const Configuration & config){
    #pragma omp for
    for(int i = 0; i < p.getSize(); i++) {
        //Only process patches if they currently contain water
        if(!p.hasWater[i]) {
            continue;
        }



        // From 2011 team's go_DOC function

        // 4% of photosynthetic gets released into the water column. Wetzel lit.
        p.macro_exudation[i] = config.macroExcretion * p.macro[i];

        // Dead objects < 1um are considered DOC in Wetzel book..
        p.micro_death[i] = p.senescence_macro[i] * .01 + p.senescence_phyto[i] * .01;

        // *need reference
        p.excretion[i] = p.herbivore_excretion[i] + p.waterdecomp_excretion[i] +
                p.seddecomp_excretion[i] + p.sedconsumer_excretion[i] +
                p.consumer_excretion[i] + p.excretion_phyto[i] + p.peri_excretion[i];

        // *need reference
        p.flocculation[i] = .01 * p.DOC[i];

        p.DOC_growth[i] = p.macro_exudation[i] + p.micro_death[i] + p.excretion[i];
    }
}

void PatchComputation::POC(PatchCollection & p) {
    #pragma omp for
    for(int i = 0; i < p.getSize(); i++) {
        //Only process patches if they currently contain water
        if(!p.hasWater[i]) {
            continue;
        }



        // From 2011 team's go_POC function

        if(p.flowMagnitude[i] > 0.0)
        {
            // exchange between POC and detritus determined by an approximation of Stoke's Law
            p.detritus_POC_transfer[i] = p.detritus[i] * (.25 * log10(((p.flowMagnitude[i] / 40.0 ) + .0001) + 1.0));
        }
        // cap at 100%. *need reference
        Utility::boundUpper(p.detritus_POC_transfer[i], 1.0);

        // approximations of the percention of dead objects < 10um that will be in water column; Wetzel Limnology textbook.
        p.small_death[i] = p.senescence_macro[i] * 0.09 + p.senescence_phyto[i] * 0.09 +
                p.scouring_macro[i] * 0.1 + p.waterdecomp_senescence[i] *
                0.7 + 0.3 * p.peri_senescence[i];

        // flocculation, leaching approximation
        p.POC_growth[i] = p.flocculation[i] + p.detritus_POC_transfer[i];
    }
}

void PatchComputation::detritus(PatchCollection & p, const Configuration & config) {
    #pragma omp for
    for(int i = 0; i < p.getSize(); i++) {
        //Only process patches if they currently contain water
        if(!p.hasWater[i]) {
            continue;
        }


        // From 2011 team's go_detritus function

        if(p.flowMagnitude[i] > 0.0) {
            p.POC_detritus_transfer[i] = p.POC[i] * (1.0 - (0.25 * log10((( p.flowMagnitude[i] / 40.0) + 0.0001) + 1.0)));
        }
        Utility::boundLower(p.POC_detritus_transfer[i], 0.0);

        //TODO Comparing a float using equality is super bad and this is probably a bug...
        if(p.flowMagnitude[i] == 0.0) {
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
                p.sedconsumer_senescence[i] + p.consumer_senescence[i] + 0.07 * p.peri_senescence[i];

        p.egestion[i] = config.herbivoreEgestion + p.sedconsumer_egestion[i] + config.consumerEgestion;

        p.detritus_growth[i] = p.large_death[i] + p.POC_detritus_transfer[i] +
                p.egestion[i] + p.macro_death[i];
    }
}


void PatchComputation::predPhyto(PatchCollection & p, int i) {
    // From 2011 team's pred_phyto function
    p.phyto[i] = p.phyto[i] + p.growth_phyto[i] - p.herbivore_pred_phyto[i];
    Utility::boundLower(p.phyto[i], 0.001);
}

void PatchComputation::predHerbivore(PatchCollection & p, int i) {
    // From 2011 team's pred_herbivore function
    p.herbivore[i] = p.herbivore[i] + p.herbivore_ingest_phyto[i]
            + p.herbivore_ingest_peri[i] + p.herbivore_ingest_waterdecomp[i]
            - (p.herbivore_respiration[i] + p.herbivore_excretion[i] + p.herbivore_senescence[i])
            - p.consumer_pred_herbivore[i];
    Utility::boundLower(p.herbivore[i], 0.001);
}

void PatchComputation::predSedDecomp(PatchCollection & p, int i) {
    // From 2011 team's pred_seddecomp function
    p.seddecomp[i] = p.seddecomp[i] + p.seddecomp_ingest_detritus[i]
            - (p.seddecomp_respiration[i] + p.seddecomp_excretion[i] + p.seddecomp_senescence[i])
            - p.sedconsumer_pred_seddecomp[i];
    Utility::boundLower(p.seddecomp[i], 0.001);
}

void PatchComputation::predWaterDecomp(PatchCollection & p, int i) {
    // From 2011 team's pred_waterdecomp function
    p.waterdecomp[i] = p.waterdecomp[i] + p.waterdecomp_ingest_doc[i] + p.waterdecomp_ingest_poc[i]
            - (p.waterdecomp_respiration[i] + p.waterdecomp_excretion[i]
            + p.waterdecomp_senescence[i]) - p.herbivore_pred_waterdecomp[i];
    Utility::boundLower(p.waterdecomp[i], 0.001);
}

void PatchComputation::predSedConsumer(PatchCollection & p, int i) {
    // From 2011 team's pred_sedconsumer function
    p.sedconsumer[i] = p.sedconsumer[i] + p.sedconsumer_ingest_peri[i] + p.sedconsumer_ingest_seddecomp[i]
            - (p.sedconsumer_respiration[i] + p.sedconsumer_excretion[i] + p.sedconsumer_senescence[i])
            - p.consumer_pred_sedconsumer[i];
    Utility::boundLower(p.sedconsumer[i], 0.001);
}

void PatchComputation::predDetritus(PatchCollection & p, int i) {
    // From 2011 team's pred_detritus function
    p.detritus_POC_transfer[i] = p.detritus[i]
            * (0.25 * log10(p.flowMagnitude[i] / 40.0 + 0.01) + 0.5);
    p.detritus[i] = p.detritus[i] + p.detritus_growth[i] - p.seddecomp_pred_detritus[i]
            - p.detritus_POC_transfer[i];
    Utility::boundLower(p.detritus[i], 0.001);
}

void PatchComputation::predDOC(PatchCollection & p, int i) {
    // From 2011 team's pred_DOC function
    p.DOC[i] = p.DOC[i] + p.DOC_growth[i] - p.waterdecomp_pred_doc[i] - p.flocculation[i];
    Utility::boundLower(p.DOC[i], 0.001);
}

void PatchComputation::predPOC(PatchCollection & p, int i) {
    // From 2011 team's pred_POC function
    p.POC[i] = p.POC[i] + p.POC_growth[i] - p.waterdecomp_pred_poc[i] - p.POC_detritus_transfer[i];
    Utility::boundLower(p.POC[i], 0.001);
}

void PatchComputation::predConsum(PatchCollection & p, int i) {
    // From 2011 team's pred_consum function
    p.consumer[i] = p.consumer[i] + p.consumer_ingest_herbivore[i] + p.consumer_ingest_sedconsumer[i]
            - (p.consumer_respiration[i] + p.consumer_excretion[i] + p.consumer_senescence[i]);
    Utility::boundLower(p.consumer[i], 0.001);
}
