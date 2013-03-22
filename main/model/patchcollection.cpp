#include "patchcollection.h"


PatchCollection::PatchCollection(const Configuration & newConfig, HydroFileDict & hydroDict) {
    config = newConfig;

    const Grid<bool> patchUsage = hydroDict.getPatchUsageGrid();
    width = patchUsage.getWidth();
    height = patchUsage.getHeight();

    int patchesNeeded = 0;
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            if( patchUsage.get(x,y) ) {
                patchesNeeded++;
            }
        }
    }

    size = patchesNeeded;
    initializePatches(config, size);

    int index = 0;
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            if( patchUsage.get(x,y) ) {
                pxcor[index] = x;
                pycor[index] = y;

                int key = getIndexMapKey(x, y);
                indexMap.insert(key, index);
                index++;
            }
        }
    }

}

int PatchCollection::getIndexMapKey(int x, int y) const {
    return x*height + y;
}

int PatchCollection::getIndex(int x, int y) const {
    int key = getIndexMapKey(x, y);
    return indexMap.value(key, -1);
}

bool PatchCollection::patchExists(int x, int y) const {
    int key = getIndexMapKey(x, y);
    return indexMap.contains(key);
}

int PatchCollection::getSize() const {
    return size;
}


/*
 * TODO  Should patches be initialized via config values?  For now
 * I'm not sure why, but the following 2011 functions don't actually
 * set the patches with initial values... If I make my code set the
 * values passed via set_stocks as below, the program output changes quite a
 * bit (At least after only a single simulated day of running...) -ECP
 *
 * void setup_stocks() {
 *     set_stocks(1.0f, 10.0f, 10.0f, 1.0f, 1.0f, 1.0f, 10.0f, 10.0f, 1.0f, 0.1f);
 * }
 *
 * void set_stocks(float macro, float phyto, float waterdecomp, float seddecomp,
 *     float herbivore, float sedconsumer, float doc, float poc,
 *     float detritus, float consum)
 * {
 *     //Code that sets each water patch here
 * }
 */
void PatchCollection::initializePatches(Configuration & config, int newSize) {
    pcolor.fill(0, newSize);

    aqa_point.fill(0, newSize);

    pxcor.fill(0, newSize);
    pycor.fill(0, newSize);
    flowX.fill(0.0, newSize);
    flowY.fill(0.0, newSize);
    flowMagnitude.fill(0.0, newSize);
    depth.fill(0.0, newSize);
    hasWater.fill(false, newSize);

    waterdecomp_doc_prey_limitation.fill(0.0, newSize);
    waterdecomp_poc_prey_limitation.fill(0.0, newSize);
    peri_doc_prey_limitation.fill(0.0, newSize);
    peri_poc_prey_limitation.fill(0.0, newSize);
    seddecomp_detritus_prey_limitation.fill(0.0, newSize);
    herbivore_phyto_prey_limitation.fill(0.0, newSize);
    herbivore_waterdecomp_prey_limitation.fill(0.0, newSize);
    herbivore_peri_prey_limitation.fill(0.0, newSize);
    sedconsumer_seddecomp_prey_limitation.fill(0.0, newSize);
    sedconsumer_peri_prey_limitation.fill(0.0, newSize);
    sedconsumer_detritus_prey_limitation.fill(0.0, newSize);
    consum_herbivore_prey_limitation.fill(0.0, newSize);
    consum_sedconsumer_prey_limitation.fill(0.0, newSize);

    peri_space_limitation.fill(0.0, newSize);
    waterdecomp_space_limitation.fill(0.0, newSize);
    seddecomp_space_limitation.fill(0.0, newSize);
    herbivore_space_limitation.fill(0.0, newSize);
    sedconsumer_space_limitation.fill(0.0, newSize);
    consum_space_limitation.fill(0.0, newSize);

    assimilation.fill(0.0, newSize);

    /*
     * TODO Should this block be initialized using the config or even used?
     * Until I know, I'm commenting it out so I match the output of the original
     * code so I know my calculations are the same and not broken.  -ECP
     */
    /*
    detritus.fill(1.0, newSize);
    DOC.fill(10.0, newSize);
    POC.fill(10.0, newSize);
    waterdecomp.fill(10.0, newSize);
    seddecomp.fill(1.0, newSize);
    macro.fill(1.0, newSize);
    phyto.fill(10.0, newSize);
    herbivore.fill(1.0, newSize);
    sedconsumer.fill(1.0, newSize);
    peri.fill(0.0, newSize);
    consum.fill(0.1, newSize);*/

    detritus.fill(0.0, newSize);
    DOC.fill(0.0, newSize);
    POC.fill(0.0, newSize);
    waterdecomp.fill(0.0, newSize);
    seddecomp.fill(0.0, newSize);
    macro.fill(0.0, newSize);
    phyto.fill(0.0, newSize);
    herbivore.fill(0.0, newSize);
    sedconsumer.fill(0.0, newSize);
    peri.fill(0.0, newSize);
    consum.fill(0.0, newSize);

    bottom_light.fill(0.0, newSize);
    consumer.fill(0.0, newSize);
    consum_consumption.fill(0.0, newSize);
    consum_ingest_herbivore.fill(0.0, newSize);
    consum_pred_herbivore.fill(0.0, newSize);
    consum_ingest_sedconsumer.fill(0.0, newSize);
    consum_pred_sedconsumer.fill(0.0, newSize);
    consum_excretion.fill(0.0, newSize);
    consum_sda.fill(0.0, newSize);
    consum_senescence.fill(0.0, newSize);
    consum_respiration.fill(0.0, newSize);
    consum_growth.fill(0.0, newSize);
    detritus_growth.fill(0.0, newSize);
    detritus_POC_transfer.fill(0.0, newSize);
    seddecomp_pred_detritus.fill(0.0, newSize);
    sedconsumer_pred_detritus.fill(0.0, newSize);
    direction.fill(0.0, newSize);
    DOC_growth.fill(0.0, newSize);
    DOC_pred.fill(0.0, newSize);
    egestion.fill(0.0, newSize);
    excretion.fill(0.0, newSize);
    excretion_phyto.fill(0.0, newSize);
    flocculation.fill(0.0, newSize);
    gross_photo.fill(0.0, newSize);
    gross_photo_macro.fill(0.0, newSize);
    gross_photo_phyto.fill(0.0, newSize);
    growth_herbivore.fill(0.0, newSize);
    growth_detritus.fill(0.0, newSize);
    growth_macro.fill(0.0, newSize);
    growth_sedconsumer.fill(0.0, newSize);
    growth_phyto.fill(0.0, newSize);
    growth_waterdecomp.fill(0.0, newSize);
    herbivore_consumption.fill(0.0, newSize);
    herbivore_ingest_peri.fill(0.0, newSize);
    herbivore_pred_peri.fill(0.0, newSize);
    herbivore_ingest_phyto.fill(0.0, newSize);
    herbivore_pred_phyto.fill(0.0, newSize);
    herbivore_ingest_waterdecomp.fill(0.0, newSize);
    herbivore_pred_waterdecomp.fill(0.0, newSize);
    herbivore_excretion.fill(0.0, newSize);
    herbivore_sda.fill(0.0, newSize);
    herbivore_senescence.fill(0.0, newSize);
    herbivore_respiration.fill(0.0, newSize);
    herbivore_growth.fill(0.0, newSize);
    K.fill(0.0, newSize);
    large_death.fill(0.0, newSize);
    light.fill(0.0, newSize);
    light_k.fill(0.0, newSize);
    macro_death.fill(0.0, newSize);
    macro_exudation.fill(0.0, newSize);
    micro_death.fill(0.0, newSize);
    phyto_maximum_growth_rate.fill(0.0, newSize);
    phyto_pred.fill(0.0, newSize);
    POC_detritus_transfer.fill(0.0, newSize);
    POC_growth.fill(0.0, newSize);
    POC_pred.fill(0.0, newSize);
    phyto_density.fill(0.0, newSize);
    peri_ingest_doc.fill(0.0, newSize);
    peri_pred_doc.fill(0.0, newSize);
    peri_ingest_poc.fill(0.0, newSize);
    peri_pred_poc.fill(0.0, newSize);
    peri_respiration.fill(0.0, newSize);
    peri_excretion.fill(0.0, newSize);
    peri_senescence.fill(0.0, newSize);
    senescence.fill(0.0, newSize);
    scouring.fill(0.0, newSize);
    small_death.fill(0.0, newSize);
    respiration.fill(0.0, newSize);
    respiration_macro.fill(0.0, newSize);
    respiration_phyto.fill(0.0, newSize);
    scouring_macro.fill(0.0, newSize);
    sedconsumer_ingest_peri.fill(0.0, newSize);
    sedconsumer_pred_peri.fill(0.0, newSize);
    senescence_macro.fill(0.0, newSize);
    senescence_phyto.fill(0.0, newSize);
    sedconsumer_consumption.fill(0.0, newSize);
    sedconsumer_ingest_detritus.fill(0.0, newSize);
    sedconsumer_ingest_seddecomp.fill(0.0, newSize);
    sedconsumer_pred_seddecomp.fill(0.0, newSize);
    sedconsumer_excretion.fill(0.0, newSize);
    sedconsumer_egestion.fill(0.0, newSize);
    sedconsumer_senescence.fill(0.0, newSize);
    sedconsumer_respiration.fill(0.0, newSize);
    sedconsumer_growth.fill(0.0, newSize);
    seddecomp_consumption.fill(0.0, newSize);
    seddecomp_ingest_detritus.fill(0.0, newSize);
    seddecomp_excretion.fill(0.0, newSize);
    seddecomp_growth.fill(0.0, newSize);
    seddcomp_ingest_peri.fill(0.0, newSize);
    seddecomp_pred_peri.fill(0.0, newSize);
    seddecomp_respiration.fill(0.0, newSize);
    seddecomp_senescence.fill(0.0, newSize);
    velpoc.fill(0.0, newSize);
    waterdecomp_consumption.fill(0.0, newSize);
    waterdecomp_ingest_doc.fill(0.0, newSize);
    waterdecomp_sda.fill(0.0, newSize);
    waterdecomp_excretion.fill(0.0, newSize);
    waterdecomp_ingest_poc.fill(0.0, newSize);
    waterdecomp_pred_doc.fill(0.0, newSize);
    waterdecomp_pred_poc.fill(0.0, newSize);
    waterdecomp_respiration.fill(0.0, newSize);
    waterdecomp_senescence.fill(0.0, newSize);
    turbidity.fill(0.0, newSize);
}
