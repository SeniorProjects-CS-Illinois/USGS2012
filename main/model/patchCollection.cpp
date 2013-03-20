#include "patchCollection.h"


PatchCollection::PatchCollection(const Configuration & newConfig, HydroFileDict & hydroDict) {
    config = newConfig;
    size = 0;

    const Grid<bool> patchUsage = hydroDict.getPatchUsageGrid();
    width = patchUsage.getWidth();
    height = patchUsage.getHeight();

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            if( patchUsage.get(x,y) ) {
                int newIndex = pxcor.size();

                pxcor.append(x);
                pycor.append(y);

                int key = getIndexMapKey(x, y);
                indexMap.insert(key, newIndex);
            }
        }
    }
    size = pxcor.size();
    initializePatches(config);
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
 * I'm setting the following based on the following 2011 code.  -ECP
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
void PatchCollection::initializePatches(Configuration & config) {
    pcolor.fill(0, size);

    aqa_point.fill(0, size);

    waterdecomp_doc_prey_limitation.fill(0.0, size);
    waterdecomp_poc_prey_limitation.fill(0.0, size);
    peri_doc_prey_limitation.fill(0.0, size);
    peri_poc_prey_limitation.fill(0.0, size);
    seddecomp_detritus_prey_limitation.fill(0.0, size);
    herbivore_phyto_prey_limitation.fill(0.0, size);
    herbivore_waterdecomp_prey_limitation.fill(0.0, size);
    herbivore_peri_prey_limitation.fill(0.0, size);
    sedconsumer_seddecomp_prey_limitation.fill(0.0, size);
    sedconsumer_peri_prey_limitation.fill(0.0, size);
    sedconsumer_detritus_prey_limitation.fill(0.0, size);
    consum_herbivore_prey_limitation.fill(0.0, size);
    consum_sedconsumer_prey_limitation.fill(0.0, size);

    peri_space_limitation.fill(0.0, size);
    waterdecomp_space_limitation.fill(0.0, size);
    seddecomp_space_limitation.fill(0.0, size);
    herbivore_space_limitation.fill(0.0, size);
    sedconsumer_space_limitation.fill(0.0, size);
    consum_space_limitation.fill(0.0, size);

    assimilation.fill(0.0, size);

    //TODO Should this block be initialized using the config? -ECP
    detritus.fill(1.0, size);
    DOC.fill(10.0, size);
    POC.fill(10.0, size);
    waterdecomp.fill(10.0, size);
    seddecomp.fill(1.0, size);
    macro.fill(1.0, size);
    phyto.fill(10.0, size);
    herbivore.fill(1.0, size);
    sedconsumer.fill(1.0, size);
    peri.fill(0.0, size);
    consum.fill(0.1, size);

    bottom_light.fill(0.0, size);
    consumer.fill(0.0, size);
    consum_consumption.fill(0.0, size);
    consum_ingest_herbivore.fill(0.0, size);
    consum_pred_herbivore.fill(0.0, size);
    consum_ingest_sedconsumer.fill(0.0, size);
    consum_pred_sedconsumer.fill(0.0, size);
    consum_excretion.fill(0.0, size);
    consum_sda.fill(0.0, size);
    consum_senescence.fill(0.0, size);
    consum_respiration.fill(0.0, size);
    consum_growth.fill(0.0, size);
    detritus_growth.fill(0.0, size);
    detritus_POC_transfer.fill(0.0, size);
    seddecomp_pred_detritus.fill(0.0, size);
    sedconsumer_pred_detritus.fill(0.0, size);
    direction.fill(0.0, size);
    DOC_growth.fill(0.0, size);
    DOC_pred.fill(0.0, size);
    egestion.fill(0.0, size);
    excretion.fill(0.0, size);
    excretion_phyto.fill(0.0, size);
    flocculation.fill(0.0, size);
    gross_photo.fill(0.0, size);
    gross_photo_macro.fill(0.0, size);
    gross_photo_phyto.fill(0.0, size);
    growth_herbivore.fill(0.0, size);
    growth_detritus.fill(0.0, size);
    growth_macro.fill(0.0, size);
    growth_sedconsumer.fill(0.0, size);
    growth_phyto.fill(0.0, size);
    growth_waterdecomp.fill(0.0, size);
    herbivore_consumption.fill(0.0, size);
    herbivore_ingest_peri.fill(0.0, size);
    herbivore_pred_peri.fill(0.0, size);
    herbivore_ingest_phyto.fill(0.0, size);
    herbivore_pred_phyto.fill(0.0, size);
    herbivore_ingest_waterdecomp.fill(0.0, size);
    herbivore_pred_waterdecomp.fill(0.0, size);
    herbivore_excretion.fill(0.0, size);
    herbivore_sda.fill(0.0, size);
    herbivore_senescence.fill(0.0, size);
    herbivore_respiration.fill(0.0, size);
    herbivore_growth.fill(0.0, size);
    K.fill(0.0, size);
    large_death.fill(0.0, size);
    light.fill(0.0, size);
    light_k.fill(0.0, size);
    macro_death.fill(0.0, size);
    macro_exudation.fill(0.0, size);
    micro_death.fill(0.0, size);
    phyto_maximum_growth_rate.fill(0.0, size);
    phyto_pred.fill(0.0, size);
    POC_detritus_transfer.fill(0.0, size);
    POC_growth.fill(0.0, size);
    POC_pred.fill(0.0, size);
    phyto_density.fill(0.0, size);
    peri_ingest_doc.fill(0.0, size);
    peri_pred_doc.fill(0.0, size);
    peri_ingest_poc.fill(0.0, size);
    peri_pred_poc.fill(0.0, size);
    peri_respiration.fill(0.0, size);
    peri_excretion.fill(0.0, size);
    peri_senescence.fill(0.0, size);
    senescence.fill(0.0, size);
    scouring.fill(0.0, size);
    small_death.fill(0.0, size);
    respiration.fill(0.0, size);
    respiration_macro.fill(0.0, size);
    respiration_phyto.fill(0.0, size);
    scouring_macro.fill(0.0, size);
    sedconsumer_ingest_peri.fill(0.0, size);
    sedconsumer_pred_peri.fill(0.0, size);
    senescence_macro.fill(0.0, size);
    senescence_phyto.fill(0.0, size);
    sedconsumer_consumption.fill(0.0, size);
    sedconsumer_ingest_detritus.fill(0.0, size);
    sedconsumer_ingest_seddecomp.fill(0.0, size);
    sedconsumer_pred_seddecomp.fill(0.0, size);
    sedconsumer_excretion.fill(0.0, size);
    sedconsumer_egestion.fill(0.0, size);
    sedconsumer_senescence.fill(0.0, size);
    sedconsumer_respiration.fill(0.0, size);
    sedconsumer_growth.fill(0.0, size);
    seddecomp_consumption.fill(0.0, size);
    seddecomp_ingest_detritus.fill(0.0, size);
    seddecomp_excretion.fill(0.0, size);
    seddecomp_growth.fill(0.0, size);
    seddcomp_ingest_peri.fill(0.0, size);
    seddecomp_pred_peri.fill(0.0, size);
    seddecomp_respiration.fill(0.0, size);
    seddecomp_senescence.fill(0.0, size);
    velpoc.fill(0.0, size);
    waterdecomp_consumption.fill(0.0, size);
    waterdecomp_ingest_doc.fill(0.0, size);
    waterdecomp_sda.fill(0.0, size);
    waterdecomp_excretion.fill(0.0, size);
    waterdecomp_ingest_poc.fill(0.0, size);
    waterdecomp_pred_doc.fill(0.0, size);
    waterdecomp_pred_poc.fill(0.0, size);
    waterdecomp_respiration.fill(0.0, size);
    waterdecomp_senescence.fill(0.0, size);
    turbidity.fill(0.0, size);
}
