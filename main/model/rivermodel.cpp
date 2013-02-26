#include "rivermodel.h"

Status RiverModel::getStatus(void){
    Status modelStatusGUI = modelStatus;

    //After we get a copy for the GUI, reset the new image flag.
    modelStatus.hasNewImage(false);
    return modelStatusGUI;
}

/**
 * Returns an image of the currently selected stock.
 */
QImage RiverModel::getImage(void){
    return getImage(g.which_stock);
}

/**
 * Returns the stock requested.
 */
QImage RiverModel::getImage(QString stockName){
    stockName = stockName.toLower();
    QImage stockImage;

    g.imageMutex.lock();
    for(int i = 0; i < g.NUM_STOCKS; i++){
        if(g.stock_names[i] == stockName){
            stockImage = *(g.images[i]);
            break;
        }
    }
    g.imageMutex.unlock();

    return stockImage;
}

void RiverModel::set_hydro_filenames(QString hydromap, int days)
{
    g.gui_filenames_list.append( hydromap);
    g.gui_days_vector.push_back(days);
    modelStatus.addWorkUnitsToProcess(days * 24);
}


void RiverModel::set_par_file(QString filename)
{
    g.gui_photo_radiation_file = filename;
}

void RiverModel::set_timestep(int timestep)
{
    g.gui_timestep_factor = timestep;
}

void RiverModel::set_temperature_file(QString filename)
{
    g.gui_temperature_file = filename;
}

//     was doing aside from creating output dirs.
void RiverModel::run(void) {
    setup();

    //TODO: Once we configure using a Configuration object, move the following line to the proper place.
    modelStatus.setState(Status::READY);

    modelStatus.setState(Status::RUNNING);


    g.gui_days_to_run = 0;
    for(int index = 0; index < g.gui_filenames_list.size(); index++)
    {
        cout << "RUNNING FILE: " << g.gui_filenames_list[index].toStdString();
        cout << " FOR " << g.gui_days_vector[index] << " DAYS" << endl;

        g.gui_days_to_run += g.gui_days_vector[index];  //Set howmany days to run the new hydromap
        g.hydro_group = (g.hydromap_index_vector[index] + 1); //Set the new hydromap that will run
        g.hydro_changed = 1;  //Confirm that a new hydro map has been loaded

        int day;
        while( (day = (g.hours / 24)) < g.gui_days_to_run)
        {
            cout << "Day: " << (day+1) << " - Hour: " << ((g.hours)%24) \
                << " | Progress: " << (int)(modelStatus.getProgress()*100) \
                << "% - Time Elapsed/Remaining (sec): " << modelStatus.getTimeElapsed() \
                << " / " << modelStatus.getTimeRemaining() << endl;
            go();
            modelStatus.updateProgress();
            if (day > 0 && g.current_day % g.output_frequency == 0)
            {
                modelStatus.hasNewImage(true);
            }
        }
    }

    cleanup();

    cout << endl << "PROCESSING COMPLETE" << endl;
    modelStatus.setState(Status::COMPLETE);
}

void RiverModel::set_whichstock(QString stock_name)
{
    if (stock_name == "Average")
    {
        stock_name = "allCarbon";
    }
    g.which_stock = stock_name;
}

void RiverModel::set_macro_base_temp(double macro_base_temp) { g.gui_macro_base_temp = macro_base_temp; }
void RiverModel::set_gross_macro_coef(double gross_macro_coef) { g.gui_gross_macro_coef = gross_macro_coef; }
void RiverModel::set_resp_macro_coef(double resp_macro_coef) { g.gui_resp_macro_coef = resp_macro_coef; }
void RiverModel::set_sen_macro_coef(double sen_macro_coef) { g.gui_sen_macro_coef = sen_macro_coef; }
void RiverModel::set_macro_mass_max(double macro_mass_max) { g.gui_macro_mass_max = macro_mass_max; }
void RiverModel::set_macro_vel_max(double macro_vel_max) { g.gui_macro_vel_max = macro_vel_max; }

void RiverModel::set_TSS(double tss) { g.gui_tss = tss; }
void RiverModel::set_k_phyto(double k_phyto) { g.gui_k_phyto = k_phyto; }
void RiverModel::set_k_macro(double k_macro) { g.gui_k_macro = k_macro; }

void RiverModel::set_output_frequency(int new_output_frequency) { g.output_frequency = new_output_frequency; }

void RiverModel::set_flow_corners(int flow_corners_only) { g.gui_flow_corners_only = flow_corners_only; }

void RiverModel::set_ai_waterdecomp_doc(double ai_waterdecomp_doc) { g.Ai_waterdecomp_DOC = ai_waterdecomp_doc; }
void RiverModel::set_ai_waterdecomp_poc(double ai_waterdecomp_poc) { g.Ai_waterdecomp_POC = ai_waterdecomp_poc; }
void RiverModel::set_ai_peri_doc(double ai_peri_doc) { g.Ai_Peri_DOC = ai_peri_doc; }
void RiverModel::set_ai_peri_poc(double ai_peri_poc) { g.Ai_Peri_POC = ai_peri_poc; }
void RiverModel::set_ai_seddecomp_detritus(double ai_seddecomp_detritus) { g.Ai_seddecomp_detritus = ai_seddecomp_detritus; }
void RiverModel::set_ai_herbivore_phyto(double ai_herbivore_phyto) { g.Ai_herbivore_phyto = ai_herbivore_phyto; }
void RiverModel::set_ai_herbivore_waterdecomp(double ai_herbivore_waterdecomp) { g.Ai_herbivore_waterdecomp = ai_herbivore_waterdecomp; }
void RiverModel::set_ai_herbivore_peri(double ai_herbivore_peri) { g.Ai_herbivore_peri = ai_herbivore_peri; }
void RiverModel::set_ai_sedconsumer_seddecomp(double ai_sedconsumer_seddecomp) { g.Ai_sedconsumer_seddecomp = ai_sedconsumer_seddecomp; }
void RiverModel::set_ai_sedconsumer_peri(double ai_sedconsumer_peri) { g.Ai_sedconsumer_peri = ai_sedconsumer_peri; }
void RiverModel::set_ai_sedconsumer_detritus(double ai_sedconsumer_detritus) { g.Ai_sedconsumer_detritus = ai_sedconsumer_detritus; }
void RiverModel::set_ai_consum_herbivore(double ai_consum_herbivore) { g.Ai_consum_herbivore = ai_consum_herbivore; }
void RiverModel::set_ai_consum_sedconsumer(double ai_consum_sedconsumer) { g.Ai_consum_sedconsumer = ai_consum_sedconsumer; }

void RiverModel::set_gi_waterdecomp_doc(double gi_waterdecomp_doc) { g.Gi_waterdecomp_DOC = gi_waterdecomp_doc; }
void RiverModel::set_gi_waterdecomp_poc(double gi_waterdecomp_poc) { g.Gi_waterdecomp_POC = gi_waterdecomp_poc; }
void RiverModel::set_gi_peri_doc(double gi_peri_doc) { g.Gi_Peri_DOC = gi_peri_doc; }
void RiverModel::set_gi_peri_poc(double gi_peri_poc) { g.Gi_Peri_POC = gi_peri_poc; }
void RiverModel::set_gi_seddecomp_detritus(double gi_seddecomp_detritus) { g.Gi_seddecomp_detritus = gi_seddecomp_detritus; }
void RiverModel::set_gi_herbivore_phyto(double gi_herbivore_phyto) { g.Gi_herbivore_phyto = gi_herbivore_phyto; }
void RiverModel::set_gi_herbivore_waterdecomp(double gi_herbivore_waterdecomp) { g.Gi_herbivore_waterdecomp = gi_herbivore_waterdecomp; }
void RiverModel::set_gi_herbivore_peri(double gi_herbivore_peri) { g.Gi_herbivore_peri = gi_herbivore_peri; }
void RiverModel::set_gi_sedconsumer_seddecomp(double gi_sedconsumer_seddecomp) { g.Gi_sedconsumer_seddecomp = gi_sedconsumer_seddecomp; }
void RiverModel::set_gi_sedconsumer_peri(double gi_sedconsumer_peri) { g.Gi_sedconsumer_peri = gi_sedconsumer_peri; }
void RiverModel::set_gi_sedconsumer_detritus(double gi_sedconsumer_detritus) { g.Gi_sedconsumer_detritus = gi_sedconsumer_detritus; }
void RiverModel::set_gi_consum_herbivore(double gi_consum_herbivore) { g.Gi_consum_herbivore = gi_consum_herbivore; }
void RiverModel::set_gi_consum_sedconsumer(double gi_consum_sedconsumer) { g.Gi_consum_sedconsumer = gi_consum_sedconsumer; }

void RiverModel::set_pref_waterdecomp_doc(double pref_waterdecomp_doc) { g.pref_waterdecomp_DOC = pref_waterdecomp_doc; }
void RiverModel::set_pref_waterdecomp_poc(double pref_waterdecomp_poc) { g.pref_waterdecomp_POC = pref_waterdecomp_poc; }
void RiverModel::set_pref_peri_doc(double pref_peri_doc) { g.pref_Peri_DOC = pref_peri_doc; }
void RiverModel::set_pref_peri_poc(double pref_peri_poc) { g.pref_Peri_POC = pref_peri_poc; }
void RiverModel::set_pref_seddecomp_detritus(double pref_seddecomp_detritus) { g.pref_seddecomp_detritus = pref_seddecomp_detritus; }
void RiverModel::set_pref_herbivore_phyto(double pref_herbivore_phyto) { g.pref_herbivore_phyto = pref_herbivore_phyto; }
void RiverModel::set_pref_herbivore_waterdecomp(double pref_herbivore_waterdecomp) { g.pref_herbivore_waterdecomp = pref_herbivore_waterdecomp; }
void RiverModel::set_pref_herbivore_peri(double pref_herbivore_peri) { g.pref_herbivore_peri = pref_herbivore_peri; }
void RiverModel::set_pref_sedconsumer_seddecomp(double pref_sedconsumer_seddecomp) { g.pref_sedconsumer_seddecomp = pref_sedconsumer_seddecomp; }
void RiverModel::set_pref_sedconsumer_peri(double pref_sedconsumer_peri) { g.pref_sedconsumer_peri = pref_sedconsumer_peri; }
void RiverModel::set_pref_sedconsumer_detritus(double pref_sedconsumer_detritus) { g.pref_sedconsumer_detritus = pref_sedconsumer_detritus; }
void RiverModel::set_pref_consum_herbivore(double pref_consum_herbivore) { g.pref_consum_herbivore = pref_consum_herbivore; }
void RiverModel::set_pref_consum_sedconsumer(double pref_consum_sedconsumer) { g.pref_consum_sedconsumer = pref_consum_sedconsumer; }

void RiverModel::set_aj_phyto(double aj_phyto) { g.Aj_phyto = aj_phyto; }
void RiverModel::set_aj_waterdecomp(double aj_waterdecomp) { g.Aj_waterdecomp = aj_waterdecomp; }
void RiverModel::set_aj_seddecomp(double aj_seddecomp) { g.Aj_seddecomp = aj_seddecomp; }
void RiverModel::set_aj_herbivore(double aj_herbivore) { g.Aj_herbivore = aj_herbivore; }
void RiverModel::set_aj_sedconsumer(double aj_sedconsumer) { g.Aj_sedconsumer = aj_sedconsumer; }
void RiverModel::set_aj_consum(double aj_consum) { g.Aj_consum = aj_consum; }
void RiverModel::set_aj_peri(double aj_peri) { g.Aj_peri = aj_peri; }

void RiverModel::set_gj_phyto(double gj_phyto) { g.Gj_phyto = gj_phyto; }
void RiverModel::set_gj_waterdecomp(double gj_waterdecomp) { g.Gj_waterdecomp = gj_waterdecomp; }
void RiverModel::set_gj_seddecomp(double gj_seddecomp) { g.Gj_seddecomp = gj_seddecomp; }
void RiverModel::set_gj_herbivore(double gj_herbivore) { g.Gj_herbivore = gj_herbivore; }
void RiverModel::set_gj_sedconsumer(double gj_sedconsumer) { g.Gj_sedconsumer = gj_sedconsumer; }
void RiverModel::set_gj_consum(double gj_consum) { g.Gj_consum = gj_consum; }
void RiverModel::set_gj_peri(double gj_peri) { g.Gj_peri = gj_peri; }

void RiverModel::set_max_waterdecomp(double max_waterdecomp) { g.max_waterdecomp = max_waterdecomp; }
void RiverModel::set_max_seddecomp(double max_seddecomp) { g.max_seddecomp = max_seddecomp; }
void RiverModel::set_max_herbivore(double max_herbivore) { g.max_herbivore = max_herbivore; }
void RiverModel::set_max_sedconsumer(double max_sedconsumer) { g.max_sedconsumer = max_sedconsumer; }
void RiverModel::set_max_consum(double max_consum) { g.max_consum = max_consum; }

void RiverModel::set_excretion_macro(double excretion_macro) { g.e_macro = excretion_macro; }
void RiverModel::set_excretion_phyto(double excretion_phyto) { g.e_phyto = excretion_phyto; }
void RiverModel::set_excretion_waterdecomp(double excretion_waterdecomp) { g.e_waterdecomp = excretion_waterdecomp; }
void RiverModel::set_excretion_seddecomp(double excretion_seddecomp) { g.e_seddecomp = excretion_seddecomp; }
void RiverModel::set_excretion_herbivore(double excretion_herbivore) { g.e_herbivore = excretion_herbivore; }
void RiverModel::set_excretion_sedconsumer(double excretion_sedconsumer) { g.e_sedconsumer = excretion_sedconsumer; }
void RiverModel::set_excretion_consum(double excretion_consum) { g.e_consum = excretion_consum; }

void RiverModel::set_respiration_phyto(double respiration_phyto) { g.r_phyto = respiration_phyto; }
void RiverModel::set_respiration_waterdecomp(double respiration_waterdecomp) { g.r_waterdecomp = respiration_waterdecomp; }
void RiverModel::set_respiration_seddecomp(double respiration_seddecomp) { g.r_seddecomp = respiration_seddecomp; }
void RiverModel::set_respiration_herbivore(double respiration_herbivore) { g.r_herbivore = respiration_herbivore; }
void RiverModel::set_respiration_sedconsumer(double respiration_sedconsumer) { g.r_sedconsumer = respiration_sedconsumer; }
void RiverModel::set_respiration_consum(double respiration_consum) { g.r_consum = respiration_consum; }

void RiverModel::set_senescence_phyto(double senescence_phyt) { g.s_phyto = senescence_phyt; }
void RiverModel::set_senescence_waterdecomp(double senescence_waterdecomp) { g.s_waterdecomp = senescence_waterdecomp; }
void RiverModel::set_senescence_seddecomp(double senescence_seddecomp) { g.s_seddecomp = senescence_seddecomp; }
void RiverModel::set_senescence_herbivore(double senescence_herbivore) { g.s_herbivore = senescence_herbivore; }
void RiverModel::set_senescence_sedconsumer(double senescence_sedconsumer) { g.s_sedconsumer = senescence_sedconsumer; }
void RiverModel::set_senescence_consum(double senescence_consum) { g.s_consum = senescence_consum; }

void RiverModel::set_herbivore_egestion(double herbivore_egestion) { g.herbivore_egestion = herbivore_egestion; }
void RiverModel::set_consum_egestion(double consum_egestion) { g.consum_egestion = consum_egestion; }
