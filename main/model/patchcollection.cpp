#include "patchcollection.h"

PatchCollection::PatchCollection(const PatchCollection &other) {
    copy(other);
}

PatchCollection::~PatchCollection() {
    clear();
}

PatchCollection & PatchCollection::operator=(const PatchCollection & rhs) {
    if(this != &rhs) {
        clear();
        copy(rhs);
    }
    return *this;
}

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

void PatchCollection::initializePatches(Configuration & config, int newSize) {
    Utility::initArray<int>(pcolor, newSize, 0);

    Utility::initArray<int>(aqa_point, newSize, 0);

    Utility::initArray<int>(pxcor, newSize, 0);
    Utility::initArray<int>(pycor, newSize, 0);
    Utility::initArray<double>(flowX, newSize, 0.0);
    Utility::initArray<double>(flowY, newSize, 0.0);
    Utility::initArray<double>(flowMagnitude, newSize, 0.0);
    Utility::initArray<double>(depth, newSize, 0.0);
    Utility::initArray<bool>(hasWater, newSize, false);

    Utility::initArray<bool>(isInput, newSize, false);
    Utility::initArray<bool>(isOutput, newSize, false);

    Utility::initArray<double>(waterdecomp_doc_prey_limitation, newSize, 0.0);
    Utility::initArray<double>(waterdecomp_poc_prey_limitation, newSize, 0.0);
    Utility::initArray<double>(peri_doc_prey_limitation, newSize, 0.0);
    Utility::initArray<double>(peri_poc_prey_limitation, newSize, 0.0);
    Utility::initArray<double>(seddecomp_detritus_prey_limitation, newSize, 0.0);
    Utility::initArray<double>(herbivore_phyto_prey_limitation, newSize, 0.0);
    Utility::initArray<double>(herbivore_waterdecomp_prey_limitation, newSize, 0.0);
    Utility::initArray<double>(herbivore_peri_prey_limitation, newSize, 0.0);
    Utility::initArray<double>(sedconsumer_seddecomp_prey_limitation, newSize, 0.0);
    Utility::initArray<double>(sedconsumer_peri_prey_limitation, newSize, 0.0);
    Utility::initArray<double>(sedconsumer_detritus_prey_limitation, newSize, 0.0);
    Utility::initArray<double>(consumer_herbivore_prey_limitation, newSize, 0.0);
    Utility::initArray<double>(consumer_sedconsumer_prey_limitation, newSize, 0.0);

    Utility::initArray<double>(peri_space_limitation, newSize, 0.0);
    Utility::initArray<double>(waterdecomp_space_limitation, newSize, 0.0);
    Utility::initArray<double>(seddecomp_space_limitation, newSize, 0.0);
    Utility::initArray<double>(herbivore_space_limitation, newSize, 0.0);
    Utility::initArray<double>(sedconsumer_space_limitation, newSize, 0.0);
    Utility::initArray<double>(consumer_space_limitation, newSize, 0.0);

    Utility::initArray<double>(assimilation, newSize, 0.0);

    Utility::initArray<double>(detritus, newSize, config.detritus);
    Utility::initArray<double>(DOC, newSize, config.doc);
    Utility::initArray<double>(POC, newSize, config.poc);
    Utility::initArray<double>(waterdecomp, newSize, config.decomp);
    Utility::initArray<double>(seddecomp, newSize, config.seddecomp);
    Utility::initArray<double>(macro, newSize, config.macro);
    Utility::initArray<double>(phyto, newSize, config.phyto);
    Utility::initArray<double>(herbivore, newSize, config.herbivore);
    Utility::initArray<double>(sedconsumer, newSize, config.sedconsumer);
    Utility::initArray<double>(consumer, newSize, config.consumer);

    Utility::initArray<double>(peri, newSize, 0.0);
    Utility::initArray<double>(bottom_light, newSize, 0.0);
    Utility::initArray<double>(consumer_consumption, newSize, 0.0);
    Utility::initArray<double>(consumer_ingest_herbivore, newSize, 0.0);
    Utility::initArray<double>(consumer_pred_herbivore, newSize, 0.0);
    Utility::initArray<double>(consumer_ingest_sedconsumer, newSize, 0.0);
    Utility::initArray<double>(consumer_pred_sedconsumer, newSize, 0.0);
    Utility::initArray<double>(consumer_excretion, newSize, 0.0);
    Utility::initArray<double>(consumer_sda, newSize, 0.0);
    Utility::initArray<double>(consumer_senescence, newSize, 0.0);
    Utility::initArray<double>(consumer_respiration, newSize, 0.0);
    Utility::initArray<double>(consumer_growth, newSize, 0.0);
    Utility::initArray<double>(detritus_growth, newSize, 0.0);
    Utility::initArray<double>(detritus_POC_transfer, newSize, 0.0);
    Utility::initArray<double>(seddecomp_pred_detritus, newSize, 0.0);
    Utility::initArray<double>(sedconsumer_pred_detritus, newSize, 0.0);
    Utility::initArray<double>(direction, newSize, 0.0);
    Utility::initArray<double>(DOC_growth, newSize, 0.0);
    Utility::initArray<double>(DOC_pred, newSize, 0.0);
    Utility::initArray<double>(egestion, newSize, 0.0);
    Utility::initArray<double>(excretion, newSize, 0.0);
    Utility::initArray<double>(excretion_phyto, newSize, 0.0);
    Utility::initArray<double>(flocculation, newSize, 0.0);
    Utility::initArray<double>(gross_photo, newSize, 0.0);
    Utility::initArray<double>(gross_photo_macro, newSize, 0.0);
    Utility::initArray<double>(gross_photo_phyto, newSize, 0.0);
    Utility::initArray<double>(growth_herbivore, newSize, 0.0);
    Utility::initArray<double>(growth_detritus, newSize, 0.0);
    Utility::initArray<double>(growth_macro, newSize, 0.0);
    Utility::initArray<double>(growth_sedconsumer, newSize, 0.0);
    Utility::initArray<double>(growth_phyto, newSize, 0.0);
    Utility::initArray<double>(growth_waterdecomp, newSize, 0.0);
    Utility::initArray<double>(herbivore_consumption, newSize, 0.0);
    Utility::initArray<double>(herbivore_ingest_peri, newSize, 0.0);
    Utility::initArray<double>(herbivore_pred_peri, newSize, 0.0);
    Utility::initArray<double>(herbivore_ingest_phyto, newSize, 0.0);
    Utility::initArray<double>(herbivore_pred_phyto, newSize, 0.0);
    Utility::initArray<double>(herbivore_ingest_waterdecomp, newSize, 0.0);
    Utility::initArray<double>(herbivore_pred_waterdecomp, newSize, 0.0);
    Utility::initArray<double>(herbivore_excretion, newSize, 0.0);
    Utility::initArray<double>(herbivore_sda, newSize, 0.0);
    Utility::initArray<double>(herbivore_senescence, newSize, 0.0);
    Utility::initArray<double>(herbivore_respiration, newSize, 0.0);
    Utility::initArray<double>(herbivore_growth, newSize, 0.0);
    Utility::initArray<double>(K, newSize, 0.0);
    Utility::initArray<double>(large_death, newSize, 0.0);
    Utility::initArray<double>(light, newSize, 0.0);
    Utility::initArray<double>(light_k, newSize, 0.0);
    Utility::initArray<double>(macro_death, newSize, 0.0);
    Utility::initArray<double>(macro_exudation, newSize, 0.0);
    Utility::initArray<double>(micro_death, newSize, 0.0);
    Utility::initArray<double>(phyto_maximum_growth_rate, newSize, 0.0);
    Utility::initArray<double>(phyto_pred, newSize, 0.0);
    Utility::initArray<double>(POC_detritus_transfer, newSize, 0.0);
    Utility::initArray<double>(POC_growth, newSize, 0.0);
    Utility::initArray<double>(POC_pred, newSize, 0.0);
    Utility::initArray<double>(phyto_density, newSize, 0.0);
    Utility::initArray<double>(peri_ingest_doc, newSize, 0.0);
    Utility::initArray<double>(peri_pred_doc, newSize, 0.0);
    Utility::initArray<double>(peri_ingest_poc, newSize, 0.0);
    Utility::initArray<double>(peri_pred_poc, newSize, 0.0);
    Utility::initArray<double>(peri_respiration, newSize, 0.0);
    Utility::initArray<double>(peri_excretion, newSize, 0.0);
    Utility::initArray<double>(peri_senescence, newSize, 0.0);
    Utility::initArray<double>(senescence, newSize, 0.0);
    Utility::initArray<double>(scouring, newSize, 0.0);
    Utility::initArray<double>(small_death, newSize, 0.0);
    Utility::initArray<double>(respiration, newSize, 0.0);
    Utility::initArray<double>(respiration_macro, newSize, 0.0);
    Utility::initArray<double>(respiration_phyto, newSize, 0.0);
    Utility::initArray<double>(scouring_macro, newSize, 0.0);
    Utility::initArray<double>(sedconsumer_ingest_peri, newSize, 0.0);
    Utility::initArray<double>(sedconsumer_pred_peri, newSize, 0.0);
    Utility::initArray<double>(senescence_macro, newSize, 0.0);
    Utility::initArray<double>(senescence_phyto, newSize, 0.0);
    Utility::initArray<double>(sedconsumer_consumption, newSize, 0.0);
    Utility::initArray<double>(sedconsumer_ingest_detritus, newSize, 0.0);
    Utility::initArray<double>(sedconsumer_ingest_seddecomp, newSize, 0.0);
    Utility::initArray<double>(sedconsumer_pred_seddecomp, newSize, 0.0);
    Utility::initArray<double>(sedconsumer_excretion, newSize, 0.0);
    Utility::initArray<double>(sedconsumer_egestion, newSize, 0.0);
    Utility::initArray<double>(sedconsumer_senescence, newSize, 0.0);
    Utility::initArray<double>(sedconsumer_respiration, newSize, 0.0);
    Utility::initArray<double>(sedconsumer_growth, newSize, 0.0);
    Utility::initArray<double>(seddecomp_consumption, newSize, 0.0);
    Utility::initArray<double>(seddecomp_ingest_detritus, newSize, 0.0);
    Utility::initArray<double>(seddecomp_excretion, newSize, 0.0);
    Utility::initArray<double>(seddecomp_growth, newSize, 0.0);
    Utility::initArray<double>(seddcomp_ingest_peri, newSize, 0.0);
    Utility::initArray<double>(seddecomp_pred_peri, newSize, 0.0);
    Utility::initArray<double>(seddecomp_respiration, newSize, 0.0);
    Utility::initArray<double>(seddecomp_senescence, newSize, 0.0);
    Utility::initArray<double>(velpoc, newSize, 0.0);
    Utility::initArray<double>(waterdecomp_consumption, newSize, 0.0);
    Utility::initArray<double>(waterdecomp_ingest_doc, newSize, 0.0);
    Utility::initArray<double>(waterdecomp_sda, newSize, 0.0);
    Utility::initArray<double>(waterdecomp_excretion, newSize, 0.0);
    Utility::initArray<double>(waterdecomp_ingest_poc, newSize, 0.0);
    Utility::initArray<double>(waterdecomp_pred_doc, newSize, 0.0);
    Utility::initArray<double>(waterdecomp_pred_poc, newSize, 0.0);
    Utility::initArray<double>(waterdecomp_respiration, newSize, 0.0);
    Utility::initArray<double>(waterdecomp_senescence, newSize, 0.0);
    Utility::initArray<double>(turbidity, newSize, 0.0);
}


void PatchCollection::clear(){
    delete [] pxcor;
    delete [] pycor;
    delete [] flowX;
    delete [] flowY;
    delete [] flowMagnitude;
    delete [] depth;
    delete [] hasWater;

    delete [] isInput;
    delete [] isOutput;

    delete [] pcolor;

    delete [] aqa_point;

    delete [] waterdecomp_doc_prey_limitation;
    delete [] waterdecomp_poc_prey_limitation;
    delete [] peri_doc_prey_limitation;
    delete [] peri_poc_prey_limitation;
    delete [] seddecomp_detritus_prey_limitation;
    delete [] herbivore_phyto_prey_limitation;
    delete [] herbivore_waterdecomp_prey_limitation;
    delete [] herbivore_peri_prey_limitation;
    delete [] sedconsumer_seddecomp_prey_limitation;
    delete [] sedconsumer_peri_prey_limitation;
    delete [] sedconsumer_detritus_prey_limitation;
    delete [] consumer_herbivore_prey_limitation;
    delete [] consumer_sedconsumer_prey_limitation;

    delete [] peri_space_limitation;
    delete [] waterdecomp_space_limitation;
    delete [] seddecomp_space_limitation;
    delete [] herbivore_space_limitation;
    delete [] sedconsumer_space_limitation;
    delete [] consumer_space_limitation;

    delete [] assimilation;
    delete [] detritus;
    delete [] DOC;
    delete [] POC;
    delete [] waterdecomp;
    delete [] seddecomp;
    delete [] macro;
    delete [] phyto;
    delete [] herbivore;
    delete [] sedconsumer;
    delete [] peri;
    delete [] consumer;
    delete [] bottom_light;
    delete [] consumer_consumption;
    delete [] consumer_ingest_herbivore;
    delete [] consumer_pred_herbivore;
    delete [] consumer_ingest_sedconsumer;
    delete [] consumer_pred_sedconsumer;
    delete [] consumer_excretion;
    delete [] consumer_sda;
    delete [] consumer_senescence;
    delete [] consumer_respiration;
    delete [] consumer_growth;
    delete [] detritus_growth;
    delete [] detritus_POC_transfer;
    delete [] seddecomp_pred_detritus;
    delete [] sedconsumer_pred_detritus;
    delete [] direction;
    delete [] DOC_growth;
    delete [] DOC_pred;
    delete [] egestion;
    delete [] excretion;
    delete [] excretion_phyto;
    delete [] flocculation;
    delete [] gross_photo;
    delete [] gross_photo_macro;
    delete [] gross_photo_phyto;
    delete [] growth_herbivore;
    delete [] growth_detritus;
    delete [] growth_macro;
    delete [] growth_sedconsumer;
    delete [] growth_phyto;
    delete [] growth_waterdecomp;
    delete [] herbivore_consumption;
    delete [] herbivore_ingest_peri;
    delete [] herbivore_pred_peri;
    delete [] herbivore_ingest_phyto;
    delete [] herbivore_pred_phyto;
    delete [] herbivore_ingest_waterdecomp;
    delete [] herbivore_pred_waterdecomp;
    delete [] herbivore_excretion;
    delete [] herbivore_sda;
    delete [] herbivore_senescence;
    delete [] herbivore_respiration;
    delete [] herbivore_growth;
    delete [] K;
    delete [] large_death;
    delete [] light;
    delete [] light_k;
    delete [] macro_death;
    delete [] macro_exudation;
    delete [] micro_death;
    delete [] phyto_maximum_growth_rate;
    delete [] phyto_pred;
    delete [] POC_detritus_transfer;
    delete [] POC_growth;
    delete [] POC_pred;
    delete [] phyto_density;
    delete [] peri_ingest_doc;
    delete [] peri_pred_doc;
    delete [] peri_ingest_poc;
    delete [] peri_pred_poc;
    delete [] peri_respiration;
    delete [] peri_excretion;
    delete [] peri_senescence;
    delete [] senescence;
    delete [] scouring;
    delete [] small_death;
    delete [] respiration;
    delete [] respiration_macro;
    delete [] respiration_phyto;
    delete [] scouring_macro;
    delete [] sedconsumer_ingest_peri;
    delete [] sedconsumer_pred_peri;
    delete [] senescence_macro;
    delete [] senescence_phyto;
    delete [] sedconsumer_consumption;
    delete [] sedconsumer_ingest_detritus;
    delete [] sedconsumer_ingest_seddecomp;
    delete [] sedconsumer_pred_seddecomp;
    delete [] sedconsumer_excretion;
    delete [] sedconsumer_egestion;
    delete [] sedconsumer_senescence;
    delete [] sedconsumer_respiration;
    delete [] sedconsumer_growth;
    delete [] seddecomp_consumption;
    delete [] seddecomp_ingest_detritus;
    delete [] seddecomp_excretion;
    delete [] seddecomp_growth;
    delete [] seddcomp_ingest_peri;
    delete [] seddecomp_pred_peri;
    delete [] seddecomp_respiration;
    delete [] seddecomp_senescence;
    delete [] velpoc;
    delete [] waterdecomp_consumption;
    delete [] waterdecomp_ingest_doc;
    delete [] waterdecomp_sda;
    delete [] waterdecomp_excretion;
    delete [] waterdecomp_ingest_poc;
    delete [] waterdecomp_pred_doc;
    delete [] waterdecomp_pred_poc;
    delete [] waterdecomp_respiration;
    delete [] waterdecomp_senescence;
    delete [] turbidity;
}


void PatchCollection::copy(const PatchCollection &other) {
    width = other.width;
    height = other.height;
    size = other.size;
    indexMap = other.indexMap;
    config = other.config;


    pxcor = Utility::copyArray<int>(other.pxcor, other.size);
    pycor = Utility::copyArray<int>(other.pycor, other.size);
    flowX = Utility::copyArray<double>(other.flowX, other.size);
    flowY = Utility::copyArray<double>(other.flowY, other.size);
    flowMagnitude = Utility::copyArray<double>(other.flowMagnitude, other.size);
    depth = Utility::copyArray<double>(other.depth, other.size);
    hasWater = Utility::copyArray<bool>(other.hasWater, other.size);

    isInput = Utility::copyArray<bool>(other.isInput, other.size);
    isOutput = Utility::copyArray<bool>(other.isOutput, other.size);

    pcolor = Utility::copyArray<int>(other.pcolor, other.size);

    aqa_point = Utility::copyArray<int>(other.aqa_point, other.size);

    waterdecomp_doc_prey_limitation = Utility::copyArray<double>(other.waterdecomp_doc_prey_limitation, other.size);
    waterdecomp_poc_prey_limitation = Utility::copyArray<double>(other.waterdecomp_poc_prey_limitation, other.size);
    peri_doc_prey_limitation = Utility::copyArray<double>(other.peri_doc_prey_limitation, other.size);
    peri_poc_prey_limitation = Utility::copyArray<double>(other.peri_poc_prey_limitation, other.size);
    seddecomp_detritus_prey_limitation = Utility::copyArray<double>(other.seddecomp_detritus_prey_limitation, other.size);
    herbivore_phyto_prey_limitation = Utility::copyArray<double>(other.herbivore_phyto_prey_limitation, other.size);
    herbivore_waterdecomp_prey_limitation = Utility::copyArray<double>(other.herbivore_waterdecomp_prey_limitation, other.size);
    herbivore_peri_prey_limitation = Utility::copyArray<double>(other.herbivore_peri_prey_limitation, other.size);
    sedconsumer_seddecomp_prey_limitation = Utility::copyArray<double>(other.sedconsumer_seddecomp_prey_limitation, other.size);
    sedconsumer_peri_prey_limitation = Utility::copyArray<double>(other.sedconsumer_peri_prey_limitation, other.size);
    sedconsumer_detritus_prey_limitation = Utility::copyArray<double>(other.sedconsumer_detritus_prey_limitation, other.size);
    consumer_herbivore_prey_limitation = Utility::copyArray<double>(other.consumer_herbivore_prey_limitation, other.size);
    consumer_sedconsumer_prey_limitation = Utility::copyArray<double>(other.consumer_sedconsumer_prey_limitation, other.size);

    peri_space_limitation = Utility::copyArray<double>(other.peri_space_limitation, other.size);
    waterdecomp_space_limitation = Utility::copyArray<double>(other.waterdecomp_space_limitation, other.size);
    seddecomp_space_limitation = Utility::copyArray<double>(other.seddecomp_space_limitation, other.size);
    herbivore_space_limitation = Utility::copyArray<double>(other.herbivore_space_limitation, other.size);
    sedconsumer_space_limitation = Utility::copyArray<double>(other.sedconsumer_space_limitation, other.size);
    consumer_space_limitation = Utility::copyArray<double>(other.consumer_space_limitation, other.size);

    assimilation = Utility::copyArray<double>(other.assimilation, other.size);
    detritus = Utility::copyArray<double>(other.detritus, other.size);
    DOC = Utility::copyArray<double>(other.DOC, other.size);
    POC = Utility::copyArray<double>(other.POC, other.size);
    waterdecomp = Utility::copyArray<double>(other.waterdecomp, other.size);
    seddecomp = Utility::copyArray<double>(other.seddecomp, other.size);
    macro = Utility::copyArray<double>(other.macro, other.size);
    phyto = Utility::copyArray<double>(other.phyto, other.size);
    herbivore = Utility::copyArray<double>(other.herbivore, other.size);
    sedconsumer = Utility::copyArray<double>(other.sedconsumer, other.size);
    peri = Utility::copyArray<double>(other.peri, other.size);
    consumer = Utility::copyArray<double>(other.consumer, other.size);
    bottom_light = Utility::copyArray<double>(other.bottom_light, other.size);
    consumer = Utility::copyArray<double>(other.consumer, other.size);
    consumer_consumption = Utility::copyArray<double>(other.consumer_consumption, other.size);
    consumer_ingest_herbivore = Utility::copyArray<double>(other.consumer_ingest_herbivore, other.size);
    consumer_pred_herbivore = Utility::copyArray<double>(other.consumer_pred_herbivore, other.size);
    consumer_ingest_sedconsumer = Utility::copyArray<double>(other.consumer_ingest_sedconsumer, other.size);
    consumer_pred_sedconsumer = Utility::copyArray<double>(other.consumer_pred_sedconsumer, other.size);
    consumer_excretion = Utility::copyArray<double>(other.consumer_excretion, other.size);
    consumer_sda = Utility::copyArray<double>(other.consumer_sda, other.size);
    consumer_senescence = Utility::copyArray<double>(other.consumer_senescence, other.size);
    consumer_respiration = Utility::copyArray<double>(other.consumer_respiration, other.size);
    consumer_growth = Utility::copyArray<double>(other.consumer_growth, other.size);
    detritus_growth = Utility::copyArray<double>(other.detritus_growth, other.size);
    detritus_POC_transfer = Utility::copyArray<double>(other.detritus_POC_transfer, other.size);
    seddecomp_pred_detritus = Utility::copyArray<double>(other.seddecomp_pred_detritus, other.size);
    sedconsumer_pred_detritus = Utility::copyArray<double>(other.sedconsumer_pred_detritus, other.size);
    direction = Utility::copyArray<double>(other.direction, other.size);
    DOC_growth = Utility::copyArray<double>(other.DOC_growth, other.size);
    DOC_pred = Utility::copyArray<double>(other.DOC_pred, other.size);
    egestion = Utility::copyArray<double>(other.egestion, other.size);
    excretion = Utility::copyArray<double>(other.excretion, other.size);
    excretion_phyto = Utility::copyArray<double>(other.excretion_phyto, other.size);
    flocculation = Utility::copyArray<double>(other.flocculation, other.size);
    gross_photo = Utility::copyArray<double>(other.gross_photo, other.size);
    gross_photo_macro = Utility::copyArray<double>(other.gross_photo_macro, other.size);
    gross_photo_phyto = Utility::copyArray<double>(other.gross_photo_phyto, other.size);
    growth_herbivore = Utility::copyArray<double>(other.growth_herbivore, other.size);
    growth_detritus = Utility::copyArray<double>(other.growth_detritus, other.size);
    growth_macro = Utility::copyArray<double>(other.growth_macro, other.size);
    growth_sedconsumer = Utility::copyArray<double>(other.growth_sedconsumer, other.size);
    growth_phyto = Utility::copyArray<double>(other.growth_phyto, other.size);
    growth_waterdecomp = Utility::copyArray<double>(other.growth_waterdecomp, other.size);
    herbivore_consumption = Utility::copyArray<double>(other.herbivore_consumption, other.size);
    herbivore_ingest_peri = Utility::copyArray<double>(other.herbivore_ingest_peri, other.size);
    herbivore_pred_peri = Utility::copyArray<double>(other.herbivore_pred_peri, other.size);
    herbivore_ingest_phyto = Utility::copyArray<double>(other.herbivore_ingest_phyto, other.size);
    herbivore_pred_phyto = Utility::copyArray<double>(other.herbivore_pred_phyto, other.size);
    herbivore_ingest_waterdecomp = Utility::copyArray<double>(other.herbivore_ingest_waterdecomp, other.size);
    herbivore_pred_waterdecomp = Utility::copyArray<double>(other.herbivore_pred_waterdecomp, other.size);
    herbivore_excretion = Utility::copyArray<double>(other.herbivore_excretion, other.size);
    herbivore_sda = Utility::copyArray<double>(other.herbivore_sda, other.size);
    herbivore_senescence = Utility::copyArray<double>(other.herbivore_senescence, other.size);
    herbivore_respiration = Utility::copyArray<double>(other.herbivore_respiration, other.size);
    herbivore_growth = Utility::copyArray<double>(other.herbivore_growth, other.size);
    K = Utility::copyArray<double>(other.K, other.size);
    large_death = Utility::copyArray<double>(other.large_death, other.size);
    light = Utility::copyArray<double>(other.light, other.size);
    light_k = Utility::copyArray<double>(other.light_k, other.size);
    macro_death = Utility::copyArray<double>(other.macro_death, other.size);
    macro_exudation = Utility::copyArray<double>(other.macro_exudation, other.size);
    micro_death = Utility::copyArray<double>(other.micro_death, other.size);
    phyto_maximum_growth_rate = Utility::copyArray<double>(other.phyto_maximum_growth_rate, other.size);
    phyto_pred = Utility::copyArray<double>(other.phyto_pred, other.size);
    POC_detritus_transfer = Utility::copyArray<double>(other.POC_detritus_transfer, other.size);
    POC_growth = Utility::copyArray<double>(other.POC_growth, other.size);
    POC_pred = Utility::copyArray<double>(other.POC_pred, other.size);
    phyto_density = Utility::copyArray<double>(other.phyto_density, other.size);
    peri_ingest_doc = Utility::copyArray<double>(other.peri_ingest_doc, other.size);
    peri_pred_doc = Utility::copyArray<double>(other.peri_pred_doc, other.size);
    peri_ingest_poc = Utility::copyArray<double>(other.peri_ingest_poc, other.size);
    peri_pred_poc = Utility::copyArray<double>(other.peri_pred_poc, other.size);
    peri_respiration = Utility::copyArray<double>(other.peri_respiration, other.size);
    peri_excretion = Utility::copyArray<double>(other.peri_excretion, other.size);
    peri_senescence = Utility::copyArray<double>(other.peri_senescence, other.size);
    senescence = Utility::copyArray<double>(other.senescence, other.size);
    scouring = Utility::copyArray<double>(other.scouring, other.size);
    small_death = Utility::copyArray<double>(other.small_death, other.size);
    respiration = Utility::copyArray<double>(other.respiration, other.size);
    respiration_macro = Utility::copyArray<double>(other.respiration_macro, other.size);
    respiration_phyto = Utility::copyArray<double>(other.respiration_phyto, other.size);
    scouring_macro = Utility::copyArray<double>(other.scouring_macro, other.size);
    sedconsumer_ingest_peri = Utility::copyArray<double>(other.sedconsumer_ingest_peri, other.size);
    sedconsumer_pred_peri = Utility::copyArray<double>(other.sedconsumer_pred_peri, other.size);
    senescence_macro = Utility::copyArray<double>(other.senescence_macro, other.size);
    senescence_phyto = Utility::copyArray<double>(other.senescence_phyto, other.size);
    sedconsumer_consumption = Utility::copyArray<double>(other.sedconsumer_consumption, other.size);
    sedconsumer_ingest_detritus = Utility::copyArray<double>(other.sedconsumer_ingest_detritus, other.size);
    sedconsumer_ingest_seddecomp = Utility::copyArray<double>(other.sedconsumer_ingest_seddecomp, other.size);
    sedconsumer_pred_seddecomp = Utility::copyArray<double>(other.sedconsumer_pred_seddecomp, other.size);
    sedconsumer_excretion = Utility::copyArray<double>(other.sedconsumer_excretion, other.size);
    sedconsumer_egestion = Utility::copyArray<double>(other.sedconsumer_egestion, other.size);
    sedconsumer_senescence = Utility::copyArray<double>(other.sedconsumer_senescence, other.size);
    sedconsumer_respiration = Utility::copyArray<double>(other.sedconsumer_respiration, other.size);
    sedconsumer_growth = Utility::copyArray<double>(other.sedconsumer_growth, other.size);
    seddecomp_consumption = Utility::copyArray<double>(other.seddecomp_consumption, other.size);
    seddecomp_ingest_detritus = Utility::copyArray<double>(other.seddecomp_ingest_detritus, other.size);
    seddecomp_excretion = Utility::copyArray<double>(other.seddecomp_excretion, other.size);
    seddecomp_growth = Utility::copyArray<double>(other.seddecomp_growth, other.size);
    seddcomp_ingest_peri = Utility::copyArray<double>(other.seddcomp_ingest_peri, other.size);
    seddecomp_pred_peri = Utility::copyArray<double>(other.seddecomp_pred_peri, other.size);
    seddecomp_respiration = Utility::copyArray<double>(other.seddecomp_respiration, other.size);
    seddecomp_senescence = Utility::copyArray<double>(other.seddecomp_senescence, other.size);
    velpoc = Utility::copyArray<double>(other.velpoc, other.size);
    waterdecomp_consumption = Utility::copyArray<double>(other.waterdecomp_consumption, other.size);
    waterdecomp_ingest_doc = Utility::copyArray<double>(other.waterdecomp_ingest_doc, other.size);
    waterdecomp_sda = Utility::copyArray<double>(other.waterdecomp_sda, other.size);
    waterdecomp_excretion = Utility::copyArray<double>(other.waterdecomp_excretion, other.size);
    waterdecomp_ingest_poc = Utility::copyArray<double>(other.waterdecomp_ingest_poc, other.size);
    waterdecomp_pred_doc = Utility::copyArray<double>(other.waterdecomp_pred_doc, other.size);
    waterdecomp_pred_poc = Utility::copyArray<double>(other.waterdecomp_pred_poc, other.size);
    waterdecomp_respiration = Utility::copyArray<double>(other.waterdecomp_respiration, other.size);
    waterdecomp_senescence = Utility::copyArray<double>(other.waterdecomp_senescence, other.size);
    turbidity = Utility::copyArray<double>(other.turbidity, other.size);
}
