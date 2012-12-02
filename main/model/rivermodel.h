#ifndef RIVERMODEL_H
#define RIVERMODEL_H

#include <sys/types.h>
#include <stdlib.h>
//#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>

#include "status.h"
#include "globals.h"
#include "setup.h"
#include "patch.h"
#include "go.h"
#include "dump.h"
#include "cleanup.h"

#include <QString>
#include <QStringList>
#include <vector>

using std::cout;
using std::endl;

class RiverModel {
    public:
        //void count_unique_files(int index);

        //Functions for configuring the model
        void set_hydro_filenames(QString filenames);
        void set_par_file(const char * filename);
        void set_timestep(int timestep);
        void set_temperature_file(const char * filename);
        void set_whichstock(const char * stock_name);
        void set_TSS(double tss);
        void set_macro_base_temp(double macro_base_temp);
        void set_gross_macro_coef(double gross_macro_coef);
        void set_resp_macro_coef(double resp_macro_coef);
        void set_sen_macro_coef(double sen_macro_coef);
        void set_macro_mass_max(double macro_mass_max);
        void set_macro_vel_max(double macro_vel_max);
        void set_k_phyto(double k_phyto);
        void set_k_macro(double k_macro);
        void set_output_frequency(int new_output_frequency);
        void set_flow_corners(int flow_corners_only);

        void set_ai_waterdecomp_doc(double ai_waterdecomp_doc);
        void set_ai_waterdecomp_poc(double ai_waterdecomp_poc);
        void set_ai_peri_doc(double ai_peri_doc);
        void set_ai_peri_poc(double ai_peri_poc);
        void set_ai_seddecomp_detritus(double ai_seddecomp_detritus);
        void set_ai_herbivore_phyto(double ai_herbivore_phyto);
        void set_ai_herbivore_waterdecomp(double ai_herbivore_waterdecomp);
        void set_ai_herbivore_peri(double ai_herbivore_peri);
        void set_ai_sedconsumer_seddecomp(double ai_sedconsumer_seddecomp);
        void set_ai_sedconsumer_peri(double ai_sedconsumer_peri);
        void set_ai_sedconsumer_detritus(double ai_sedconsumer_detritus);
        void set_ai_consum_herbivore(double ai_consum_herbivore);
        void set_ai_consum_sedconsumer(double ai_consum_sedconsumer);

        void set_gi_waterdecomp_doc(double gi_waterdecomp_doc);
        void set_gi_waterdecomp_poc(double gi_waterdecomp_poc);
        void set_gi_peri_doc(double gi_peri_doc);
        void set_gi_peri_poc(double gi_peri_poc);
        void set_gi_seddecomp_detritus(double gi_seddecomp_detritus);
        void set_gi_herbivore_phyto(double gi_herbivore_phyto);
        void set_gi_herbivore_waterdecomp(double gi_herbivore_waterdecomp);
        void set_gi_herbivore_peri(double gi_herbivore_peri);
        void set_gi_sedconsumer_seddecomp(double gi_sedconsumer_seddecomp);
        void set_gi_sedconsumer_peri(double gi_sedconsumer_peri);
        void set_gi_sedconsumer_detritus(double gi_sedconsumer_detritus);
        void set_gi_consum_herbivore(double gi_consum_herbivore);
        void set_gi_consum_sedconsumer(double gi_consum_sedconsumer);

        void set_pref_waterdecomp_doc(double pref_waterdecomp_doc);
        void set_pref_waterdecomp_poc(double pref_waterdecomp_poc);
        void set_pref_peri_doc(double pref_peri_doc);
        void set_pref_peri_poc(double pref_peri_poc);
        void set_pref_seddecomp_detritus(double pref_seddecomp_detritus);
        void set_pref_herbivore_phyto(double pref_herbivore_phyto);
        void set_pref_herbivore_waterdecomp(double pref_herbivore_waterdecomp);
        void set_pref_herbivore_peri(double pref_herbivore_peri);
        void set_pref_sedconsumer_seddecomp(double pref_sedconsumer_seddecomp);
        void set_pref_sedconsumer_peri(double pref_sedconsumer_peri);
        void set_pref_sedconsumer_detritus(double pref_sedconsumer_detritus);
        void set_pref_consum_herbivore(double pref_consum_herbivore);
        void set_pref_consum_sedconsumer(double pref_consum_sedconsumer);

        void set_aj_phyto(double aj_phyto);
        void set_aj_waterdecomp(double aj_waterdecomp);
        void set_aj_seddecomp(double aj_seddecomp);
        void set_aj_herbivore(double aj_herbivore);
        void set_aj_sedconsumer(double aj_sedconsumer);
        void set_aj_consum(double aj_consum);
        void set_aj_peri(double aj_peri);

        void set_gj_phyto(double gj_phyto);
        void set_gj_waterdecomp(double gj_waterdecomp);
        void set_gj_seddecomp(double gj_seddecomp);
        void set_gj_herbivore(double gj_herbivore);
        void set_gj_sedconsumer(double gj_sedconsumer);
        void set_gj_consum(double gj_consum);
        void set_gj_peri(double gj_peri);

        void set_max_waterdecomp(double max_waterdecomp);
        void set_max_seddecomp(double max_seddecomp);
        void set_max_herbivore(double max_herbivore);
        void set_max_sedconsumer(double max_sedconsumer);
        void set_max_consum(double max_consum);

        void set_excretion_macro(double excretion_macro);
        void set_excretion_phyto(double excretion_phyto);
        void set_excretion_waterdecomp(double excretion_waterdecomp);
        void set_excretion_seddecomp(double excretion_seddecomp);
        void set_excretion_herbivore(double excretion_herbivore);
        void set_excretion_sedconsumer(double excretion_sedconsumer);
        void set_excretion_consum(double excretion_consum);

        void set_respiration_phyto(double respiration_phyto);
        void set_respiration_waterdecomp(double respiration_waterdecomp);
        void set_respiration_seddecomp(double respiration_seddecomp);
        void set_respiration_herbivore(double respiration_herbivore);
        void set_respiration_sedconsumer(double respiration_sedconsumer);
        void set_respiration_consum(double respiration_consum);

        void set_senescence_phyto(double senescence_phyto);
        void set_senescence_waterdecomp(double senescence_waterdecomp);
        void set_senescence_seddecomp(double senescence_seddecomp);
        void set_senescence_herbivore(double senescence_herbivore);
        void set_senescence_sedconsumer(double senescence_sedconsumer);
        void set_senescence_consum(double senescence_consum);

        void set_herbivore_egestion(double herbivore_egestion);
        void set_consum_egestion(double consum_egestion);

        //double sedconsumer_egestion_seddecomp;
        //double sedconsumer_egestion_detritus;

        //Runs the model
        void run(void);

        Status getStatus(void);

    private:
        Status modelStatus;
};
#endif
