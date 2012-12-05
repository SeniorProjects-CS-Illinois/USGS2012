#include "../model/patch_struct.h"
#pragma OPENCL EXTENSION cl_khr_fp64 : enable // Enabling double fp operations

    __kernel void
vector_add_gpu (__global const float* src_a,
        __global const float* src_b,
        __global float* res,
        const int num)
{
    const int idx = get_global_id(0);

    if(idx < num)
    {
        res[idx] = src_a[idx] + src_b[idx];
    }
}

/**
 * Ensures a bound
 * @param value The value to test
 * @param low value must be higher than this value
 * @param high value must be lower than this value
 * @return The bounded value
 */
inline double
assertRange(
        const double value,
        double low,
        const double high
        )
{
    if(value < low)
        return low;
    else if(value > high)
        return high;
    else
        return value;
}


// TODO: DO NOT USE, NOT WORKING!
__kernel void update_patches(__global const patch* inPatches,
        __global patch* outPatches,
        const int y
        )
{
    //    outPatches[y].turbidity = ( .29587 + gui_tss)
    //        + (gui_k_phyto * (inPatches[y].phyto/ 900.0) )
    //        + (gui_k_macro * (inPatches[y].macro / 900.0) );

    if(inPatches[y].turbidity > 30.0){
        outPatches[y].turbidity = 30.0;
    }
    if(inPatches[y].turbidity < 0.0){
        outPatches[y].turbidity = 0.01;
    }

    //the amount of light that reaches the bottom of a water column
    //    inPatches[y].bottom_light = (photo_radiation
    //            * exp( (-1 * inPatches[y].depth) * inPatches[y].turbidity )); 
    //    // These are globals, IDK what to do about them :-(
    //    Aj_peri = inPatches[y].macro / 10.0 ;
    //    Gj_peri = inPatches[y].macro / 2.0;
    //    Aj_seddecomp = inPatches[y].detritus / 20.0;
    //    Gj_seddecomp = inPatches[y].detritus / 5.0;
}

//TODO: DO NOT USE, NOT WORKING!
__kernel void go_macro(__global const patch* inPatches,
        __global patch* outPatches,
        const int y
        )
{
    //    Q10 = pow(theta, (temperature - macro_base_temp));

    //    if(inPatches[y].velocity < macro_vel_max){
    //        outPatches[y].K = max_area * (gui_macro_mass_max -
    //                (gui_macro_mass_max  / gui_macro_vel_max) * inPatches[y].velocity);
    //    }
    //    else{
    //        outPatches[y].K = 0.01;
    //    }
    //Same at bottom-light
    //    double macro_light = photo_radiation * exp( (-1*inPatches[y].depth) * inPatches[y].turbidity );
    //
    //    outPatches[y].gross_photo_macro = (gui_gross_macro_coef * inPatches[y].macro *
    //            ( macro_light / ( macro_light + 10.0)) * Q10 * 
    //            (inPatches[y].K - inPatches[y].macro) / inPatches[y].K);
    //
    //    outPatches[y].respiration_macro = (resp_macro_coef / 24.0) * inPatches[y].macro * Q10;
    //
    //    inPatches[y].senescence_macro = sen_macro_coef * inPatches[y].macro / 24.0;

    outPatches[y].growth_macro = inPatches[y].gross_photo_macro
        - inPatches[y].respiration_macro - inPatches[y].senescence_macro
        - inPatches[y].scouring_macro;

    outPatches[y].macro += inPatches[y].growth_macro;

    if(inPatches[y].macro < 0.001)
        outPatches[y].macro = 0.001; //minimum biomass based on seed bank
}

// NOT WORKING, DO NOT USE!
__kernel void go_phyto(__global const patch* inPatches,
        __global patch* outPatches,
        const int y
        )
{
    //minimum and maximum caps on biomass
    if( inPatches[y].phyto > 900000.0){
        outPatches[y].phyto = 900000.0;
    }
    if( inPatches[y].phyto < 0.001){
        outPatches[y].phyto = 0.001;
    }
    double base_temperature = 8.0; //base temperature for nominal growth
    //    Q10 = pow(theta, (temperature - base_temperature));
    double km = 10; //half saturation constant
    //this is the attenuation coefficient of phytoplank m^2/g of phyto plankton
    double light_k = 0.4;
    //    outPatches[y].respiration_phyto = 0.1 / 24.0 * inPatches[y].phyto * Q10;
    //    double pre_ln = (0.01 + photo_radiation  *
    //            exp(-1*inPatches[y].phyto * gui_k_phyto * inPatches[y].depth));
    //    double be = (km + (photo_radiation *
    //                exp(-1 * inPatches[y].phyto * gui_k_phyto * inPatches[y].depth)));
    //photosynthesis from phytoplankton derived from Huisman Weissing 1994

    //    outPatches[y].gross_photo_phyto = fabs(pre_ln / be) * (1.0 / inPatches[y].depth) * (inPatches[y].phyto / inPatches[y].turbidity) * Q10;
    outPatches[y].excretion_phyto = 0.05 / 24.0 * inPatches[y].phyto;
    outPatches[y].senescence_phyto = 0.02 / 24.0 * inPatches[y].phyto;
    outPatches[y].growth_phyto = inPatches[y].gross_photo_phyto - inPatches[y].excretion_phyto - 
        inPatches[y].respiration_phyto - inPatches[y].senescence_phyto;
}

//TODO: NOT WORKING, DO NOT USE!
__kernel void go_herbivore(__global const patch* inPatches,
        __global patch* outPatches,
        const int y
        )
{
   // outPatches[y].herbivore_phyto_prey_limitation = inPatches[y].phyto /
   //     (Ai_herbivore_phyto - Gi_herbivore_phyto);

   // outPatches[y].herbivore_phyto_prey_limitation =
   //     assertRange(inPatches[y].herbivore_phyto_prey_limitation, 0.0, 1.0);

   // outPatches[y].herbivore_peri_prey_limitation = inPatches[y].peri / (Ai_herbivore_peri - Gi_herbivore_peri);

   // outPatches[y].herbivore_peri_prey_limitation =
   //     assertRange(inPatches[y].herbivore_peri_prey_limitation, 0.0, 1.0);

   // outPatches[y].herbivore_waterdecomp_prey_limitation =
   //     inPatches[y].waterdecomp / (Ai_herbivore_waterdecomp - Gi_herbivore_waterdecomp);

   // outPatches[y].herbivore_waterdecomp_prey_limitation =
   //     assertRange(inPatches[y].herbivore_waterdecomp_prey_limitation, 0.0, 1.0);

   // outPatches[y].herbivore_space_limitation = 1.0 -
   //     ((inPatches[y].herbivore - Aj_herbivore) /(Gj_herbivore - Aj_herbivore));

   // outPatches[y].herbivore_space_limitation = assertRange(inPatches[y].herbivore_space_limitation, 0.0, 1.0);

   // outPatches[y].herbivore_pred_phyto = pref_herbivore_phyto * max_herbivore * inPatches[x].herbivore * 
   //     inPatches[y].herbivore_space_limitation * inPatches[y].herbivore_phyto_prey_limitation;

   // outPatches[y].herbivore_ingest_phyto = inPatches[y].herbivore_pred_phyto * (1.0 - herbivore_egestion);

   // outPatches[y].herbivore_pred_peri = pref_herbivore_peri * max_herbivore * inPatches[y].herbivore
   //     * inPatches[y].herbivore_space_limitation * inPatches[y].herbivore_peri_prey_limitation;

   // outPatches[y].herbivore_ingest_peri = inPatches[y].herbivore_pred_peri * (1.0 - herbivore_egestion);

   // outPatches[y].herbivore_pred_waterdecomp = pref_herbivore_waterdecomp * max_herbivore *
   //     inPatches[y].herbivore * inPatches[y].herbivore_space_limitation *
   //     inPatches[y].herbivore_waterdecomp_prey_limitation;

   // outPatches[y].herbivore_ingest_waterdecomp =
   //     inPatches[y].herbivore_pred_waterdecomp * (1.0 - herbivore_egestion);

   // outPatches[y].herbivore_respiration = r_herbivore * inPatches[y].herbivore;

   // outPatches[y].herbivore_excretion = e_herbivore * inPatches[y].herbivore;

   // outPatches[y].herbivore_senescence = s_herbivore * inPatches[y].herbivore;
}

__kernel void __go_waterdecomp(__global const patch* inPatches,
        __global patch* outPatches,
        const int y
        )
{
   // outPatches[y].waterdecomp_doc_prey_limitation = inPatches[y].DOC / (Ai_waterdecomp_DOC - Gi_waterdecomp_DOC);
   // inPatches[y].waterdecomp_doc_prey_limitation = 
   //     assertRange(inPatches[y].waterdecomp_doc_prey_limitation, 0.0, 1.0);
   // 
   // outPatches[y].waterdecomp_poc_prey_limitation = inPatches[y].POC / (Ai_waterdecomp_POC - Gi_waterdecomp_POC);
   // outPatches[y].waterdecomp_poc_prey_limitation =
   //     assertRange(inPatches[y].waterdecomp_poc_prey_limitation, 0.0, 1.0);

   // outPatches[y].waterdecomp_space_limitation = 1.0
   //     - ((inPatches[y].waterdecomp - Aj_waterdecomp) / (Gj_waterdecomp - Aj_waterdecomp));

   // outPatches[y].waterdecomp_space_limitation =
   //     assertRange(inPatches[y].waterdecomp_space_limitation, 0.0, 1.0);

   // outPatches[y].waterdecomp_pred_doc = (pref_waterdecomp_DOC * max_waterdecomp * inPatches[y].waterdecomp * 
   //         inPatches[y].waterdecomp_space_limitation * inPatches[y].waterdecomp_doc_prey_limitation);

   // outPatches[y].waterdecomp_ingest_doc = inPatches[y].waterdecomp_pred_doc;

   // outPatches[y].waterdecomp_pred_poc = pref_waterdecomp_POC * max_waterdecomp * inPatches[y].waterdecomp * 
   //     inPatches[y].waterdecomp_space_limitation * inPatches[y].waterdecomp_poc_prey_limitation;

   // outPatches[y].waterdecomp_ingest_poc = inPatches[y].waterdecomp_pred_poc;

   // outPatches[y].waterdecomp_respiration = r_waterdecomp * inPatches[y].waterdecomp;

   // outPatches[y].waterdecomp_excretion = e_waterdecomp * inPatches[y].waterdecomp;

   // outPatches[y].waterdecomp_senescence = s_waterdecomp * inPatches[y].waterdecomp;
}

__kernel void go_seddecomp(__global const patch* inPatches,
        __global patch* outPatches,
        const int y
        )
{
}

__kernel void go_sedconsumer(__global const patch* inPatches,
        __global patch* outPatches,
        const int y
        )
{
}

__kernel void go_consum(__global const patch* inPatches,
        __global patch* outPatches,
        const int y
        )
{
}

__kernel void go_DOC(__global const patch* inPatches,
        __global patch* outPatches,
        const int y
        )
{
}

__kernel void go_POC(__global const patch* inPatches,
        __global patch* outPatches,
        const int y
        )
{
}

__kernel void go_detritus(__global const patch* inPatches,
        __global patch* outPatches,
        const int y
        )
{
}

__kernel void __pred_phyto(__global const patch* inPatches,
        __global patch* outPatches
        )
{
    int y = get_global_id(0);
    outPatches[y].phyto = inPatches[y].phyto + inPatches[y].growth_phyto - inPatches[y].herbivore_pred_phyto;

    if (outPatches[y].phyto < 0.001)
    {
        outPatches[y].phyto = 0.001;
    }
}

__kernel void __pred_herbivore(__global const patch* inPatches,
        __global patch* outPatches,
        const int y
        )
{
    outPatches[y].herbivore = inPatches[y].herbivore + inPatches[y].herbivore_ingest_phyto
        + inPatches[y].herbivore_ingest_peri + inPatches[y].herbivore_ingest_waterdecomp 
        - (inPatches[y].herbivore_respiration + inPatches[y].herbivore_excretion
                + inPatches[y].herbivore_senescence) - inPatches[y].consum_pred_herbivore;

    if (outPatches[y].herbivore < 0.001)
    {
        outPatches[y].herbivore = 0.001;
    }
}

__kernel void __pred_seddecomp(__global const patch* inPatches,
        __global patch* outPatches,
        const int y
        )
{
    outPatches[y].seddecomp = inPatches[y].seddecomp + inPatches[y].seddecomp_ingest_detritus
        - (inPatches[y].seddecomp_respiration + inPatches[y].seddecomp_excretion
                + inPatches[y].seddecomp_senescence) - inPatches[y].sedconsumer_pred_seddecomp;

    if (outPatches[y].seddecomp < 0.001)
    {
        outPatches[y].seddecomp = 0.001;
    }
}


__kernel void __pred_waterdecomp(__global const patch* inPatches,
        __global patch* outPatches,
        const int y
        )
{
    outPatches[y].waterdecomp = inPatches[y].waterdecomp + inPatches[y].waterdecomp_ingest_doc
        + inPatches[y].waterdecomp_ingest_poc - (inPatches[y].waterdecomp_respiration
                + inPatches[y].waterdecomp_excretion + inPatches[y].waterdecomp_senescence)
        - inPatches[y].herbivore_pred_waterdecomp;

    if (outPatches[y].waterdecomp < 0.001)
    {
        outPatches[y].waterdecomp = 0.001;
    }
}

__kernel void __pred_sedconsumer(__global const patch* inPatches,
        __global patch* outPatches,
        const int y
        )
{
    outPatches[y].sedconsumer = inPatches[y].sedconsumer + inPatches[y].sedconsumer_ingest_peri
        + inPatches[y].sedconsumer_ingest_seddecomp - (inPatches[y].sedconsumer_respiration
                + inPatches[y].sedconsumer_excretion + inPatches[y].sedconsumer_senescence)
        - inPatches[y].consum_pred_sedconsumer;

    if (outPatches[y].sedconsumer < 0.001)
    {
        outPatches[y].sedconsumer = 0.001;
    }
}

__kernel void __pred_detritus(__global const patch* inPatches,
        __global patch* outPatches,
        const int y
        )
{
    outPatches[y].detritus_POC_transfer = inPatches[y].detritus * 
        (0.25 * log10(inPatches[y].velocity / 40.0 + 0.01) + 0.5);

    outPatches[y].detritus = inPatches[y].detritus + inPatches[y].detritus_growth
        - inPatches[y].seddecomp_pred_detritus - inPatches[y].detritus_POC_transfer;

    if (outPatches[y].detritus < 0.001)
    {
        outPatches[y].detritus = 0.001;
    }
}


__kernel void __pred_DOC(__global const patch* inPatches,
        __global patch* outPatches,
        const int y
        )
{
    outPatches[y].DOC = inPatches[y].DOC + inPatches[y].DOC_growth
        - inPatches[y].waterdecomp_pred_doc - inPatches[y].flocculation;

    if (outPatches[y].DOC < 0.001)
    {
        outPatches[y].DOC = 0.001;
    }
}


__kernel void __pred_POC(__global const patch* inPatches,
        __global patch* outPatches,
        const int y
        )
{
    outPatches[y].POC = inPatches[y].POC + inPatches[y].POC_growth -
        inPatches[y].waterdecomp_pred_poc - inPatches[y].POC_detritus_transfer;

    if (outPatches[y].POC < 0.001)
    {
        outPatches[y].POC = 0.001;
    }
}

__kernel void __pred_consum(__global const patch* inPatches,
        __global patch* outPatches,
        const int y
        )
{
    outPatches[y].consum = inPatches[y].consum + inPatches[y].consum_ingest_herbivore + inPatches[y].consum_ingest_sedconsumer 
        - (inPatches[y].consum_respiration + inPatches[y].consum_excretion + inPatches[y].consum_senescence);

    if (inPatches[y].consum < 0.001)
    {
        outPatches[y].consum = 0.001;
    }
}

__kernel void __goGPU(__global const patch* inPatches,
        __global patch* outPatches
        )
{
    int y = get_global_id(0);

    if(inPatches[y].depth > 0.0){
        //        update_patches(inPatches, outPatches, y);
        //        go_macro(inPatches, outPatches,y);
        //        go_phyto(inPatches, outPatches,y);
        //        go_herbivore(inPatches, outPatches,y);
        //        __go_waterdecomp(inPatches, outPatches,y);
        //        go_seddecomp(inPatches, outPatches,y);
        //        go_sedconsumer(inPatches, outPatches,y);
        //        go_consum(inPatches, outPatches,y);
        //        go_DOC(inPatches, outPatches,y);
        //        go_POC(inPatches, outPatches,y);
        //        go_detritus(inPatches, outPatches,y);

        __pred_phyto(inPatches, outPatches);
        __pred_herbivore(inPatches, outPatches, y);
        __pred_seddecomp(inPatches, outPatches, y);
        __pred_waterdecomp(inPatches, outPatches, y);
        __pred_sedconsumer(inPatches, outPatches, y);
        __pred_detritus(inPatches, outPatches, y);
        __pred_DOC(inPatches, outPatches, y);
        __pred_POC(inPatches, outPatches, y);
        __pred_consum(inPatches, outPatches, y);
    }
}



//void go_seddecomp(int x, int y) {
//
//    // update seddecomp_detritus_prey_limitation
//    patches[x][y].seddecomp_detritus_prey_limitation = patches[x][y].detritus / (Ai_seddecomp_detritus - Gi_seddecomp_detritus);
//
//    if(patches[x][y].seddecomp_detritus_prey_limitation > 1.0)
//        patches[x][y].seddecomp_detritus_prey_limitation = 1.0;
//    else if(patches[x][y].seddecomp_detritus_prey_limitation < 0.0)
//        patches[x][y].seddecomp_detritus_prey_limitation = 0.0;
//
//    // update seddecomp_space_limitation
//    if( (Gj_seddecomp - Aj_seddecomp) != 0.0 ) {
//        patches[x][y].seddecomp_space_limitation = 1.0 - ((patches[x][y].seddecomp - Aj_seddecomp)/(Gj_seddecomp - Aj_seddecomp));
//    } else {
//        patches[x][y].seddecomp_space_limitation = 0.0;
//    }
//
//    if(patches[x][y].seddecomp_space_limitation > 1.0)
//        patches[x][y].seddecomp_space_limitation = 1.0;
//    else if(patches[x][y].seddecomp_space_limitation < 0.0)
//        patches[x][y].seddecomp_space_limitation = 0.0;
//
//    // update seddecomp_pred_detritus
//    patches[x][y].seddecomp_pred_detritus = pref_seddecomp_detritus*max_seddecomp*patches[x][y].seddecomp*
//        patches[x][y].seddecomp_detritus_prey_limitation *
//        patches[x][y].seddecomp_space_limitation;
//
//    // update seddecomp_ingest_detritus
//    patches[x][y].seddecomp_ingest_detritus = patches[x][y].seddecomp_pred_detritus;
//
//    // update seddecomp_respiration
//    patches[x][y].seddecomp_respiration = r_seddecomp * patches[x][y].seddecomp;
//
//    // update seddecomp_excretion
//    patches[x][y].seddecomp_excretion = e_seddecomp * patches[x][y].seddecomp;
//
//    // update seddecomp_senescence
//    patches[x][y].seddecomp_senescence = s_seddecomp * patches[x][y].seddecomp;
//}
//
//void go_sedconsumer(int x, int y) {
//
//    // update sedconsumer_seddecomp_prey_limitation
//    patches[x][y].sedconsumer_seddecomp_prey_limitation = patches[x][y].seddecomp / (Ai_sedconsumer_seddecomp - Gi_sedconsumer_seddecomp);
//
//    if( patches[x][y].sedconsumer_seddecomp_prey_limitation > 1.0 )
//        patches[x][y].sedconsumer_seddecomp_prey_limitation = 1.0;
//    else if ( patches[x][y].sedconsumer_seddecomp_prey_limitation < 0.0 )
//        patches[x][y].sedconsumer_seddecomp_prey_limitation = 0.0;
//
//    // update sedconsumer_peri_prey_limitation
//    patches[x][y].sedconsumer_peri_prey_limitation = patches[x][y].peri / (Ai_sedconsumer_peri - Gi_sedconsumer_peri);
//
//    if( patches[x][y].sedconsumer_peri_prey_limitation > 1.0 )
//        patches[x][y].sedconsumer_peri_prey_limitation = 1.0;
//    else if (patches[x][y].sedconsumer_peri_prey_limitation < 0.0)
//        patches[x][y].sedconsumer_peri_prey_limitation = 0.0;
//
//    // update sedconsumer_detritus_prey_limitation
//    patches[x][y].sedconsumer_detritus_prey_limitation = patches[x][y].detritus / (Ai_sedconsumer_detritus - Gi_sedconsumer_detritus);
//
//    if( patches[x][y].sedconsumer_detritus_prey_limitation > 1.0 )
//        patches[x][y].sedconsumer_detritus_prey_limitation = 1.0;
//    else if ( patches[x][y].sedconsumer_detritus_prey_limitation < 0.0 )
//        patches[x][y].sedconsumer_detritus_prey_limitation = 0.0;
//
//    // update sedconsumer_space_limitation
//    patches[x][y].sedconsumer_space_limitation = 1.0 - ((patches[x][y].sedconsumer - Aj_sedconsumer)/(Gj_sedconsumer - Aj_sedconsumer));
//
//    if( patches[x][y].sedconsumer_space_limitation > 1.0 )
//        patches[x][y].sedconsumer_space_limitation = 1.0;
//    else if ( patches[x][y].sedconsumer_space_limitation < 0.0 )
//        patches[x][y].sedconsumer_space_limitation = 0.0;
//
//    // update sedconsumer_pred_peri
//    patches[x][y].sedconsumer_pred_peri = pref_sedconsumer_peri * max_sedconsumer * patches[x][y].sedconsumer *
//        patches[x][y].sedconsumer_space_limitation * 
//        patches[x][y].sedconsumer_peri_prey_limitation;
//
//    // update sedconsumer_ingest_peri
//    patches[x][y].sedconsumer_ingest_peri = patches[x][y].sedconsumer_pred_peri * (1.0 - sedconsumer_egestion_seddecomp);
//
//    // update sedconsumer_pred_seddecomp
//    patches[x][y].sedconsumer_pred_seddecomp = pref_sedconsumer_seddecomp * max_sedconsumer * patches[x][y].sedconsumer *
//        patches[x][y].sedconsumer_space_limitation *
//        patches[x][y].sedconsumer_seddecomp_prey_limitation;
//
//    // update sedconsumer_ingest_seddecomp
//    patches[x][y].sedconsumer_ingest_seddecomp = patches[x][y].sedconsumer_pred_seddecomp * (1.0 - sedconsumer_egestion_seddecomp);
//
//    // update sedconsumer_pred_detritus
//    patches[x][y].sedconsumer_pred_detritus = pref_sedconsumer_detritus * max_sedconsumer * patches[x][y].sedconsumer *
//        patches[x][y].sedconsumer_space_limitation * 
//        patches[x][y].sedconsumer_detritus_prey_limitation;
//
//    // update sedconsumer_ingest_detritus
//    patches[x][y].sedconsumer_ingest_detritus = patches[x][y].sedconsumer_pred_detritus * (1.0 - sedconsumer_egestion_detritus);
//
//    // update sedconsumer_respiration
//    patches[x][y].sedconsumer_respiration = r_sedconsumer * patches[x][y].sedconsumer;
//
//    // update sedconsumer_excretion
//    patches[x][y].sedconsumer_excretion = e_sedconsumer * patches[x][y].sedconsumer;
//
//    // update sedconsumer_senescence
//    patches[x][y].sedconsumer_senescence = s_sedconsumer * patches[x][y].sedconsumer;
//}
//
//void go_consum(int x,int y) {
//
//    // update consum_sedconsumer_prey_limitation
//    patches[x][y].consum_sedconsumer_prey_limitation = patches[x][y].sedconsumer / (Ai_consum_sedconsumer - Gi_consum_sedconsumer);
//    if( patches[x][y].consum_sedconsumer_prey_limitation > 1.0 )
//        patches[x][y].consum_sedconsumer_prey_limitation = 1.0;
//    else if ( patches[x][y].consum_sedconsumer_prey_limitation < 0.0 )
//        patches[x][y].consum_sedconsumer_prey_limitation = 0.0;
//
//    // update consum_herbivore_prey_limitation
//    patches[x][y].consum_herbivore_prey_limitation = patches[x][y].herbivore / (Ai_consum_herbivore - Gi_consum_herbivore);
//    if( patches[x][y].consum_herbivore_prey_limitation > 1.0 )
//        patches[x][y].consum_herbivore_prey_limitation = 1.0;
//    else if ( patches[x][y].consum_herbivore_prey_limitation < 0.0 )
//        patches[x][y].consum_herbivore_prey_limitation = 0.0;
//
//    // update consum_space_limitation
//    patches[x][y].consum_space_limitation = 1.0 - ((patches[x][y].consum - Aj_consum)/(Gj_consum - Aj_consum));
//    if( patches[x][y].consum_space_limitation > 1.0 )
//        patches[x][y].consum_space_limitation = 1.0;
//    else if ( patches[x][y].consum_space_limitation < 0.0 )
//        patches[x][y].consum_space_limitation = 0.0;
//
//    // update consum_pred_herbivore
//    patches[x][y].consum_pred_herbivore = pref_consum_herbivore * max_consum * patches[x][y].consum *
//        patches[x][y].consum_space_limitation * 
//        patches[x][y].consum_herbivore_prey_limitation;
//
//    // update consum_ingest_herbivore
//    patches[x][y].consum_ingest_herbivore = patches[x][y].consum_pred_herbivore * (1.0- consum_egestion);
//
//    // update consum_pred_sedconsumer
//    patches[x][y].consum_pred_sedconsumer = pref_consum_sedconsumer * max_consum * patches[x][y].consum *
//        patches[x][y].consum_space_limitation *
//        patches[x][y].consum_sedconsumer_prey_limitation;
//
//    // update consum_ingest_sedconsumer
//    patches[x][y].consum_ingest_sedconsumer = patches[x][y].consum_pred_sedconsumer * (1.0 - consum_egestion);
//
//    // update consum_respiration
//    patches[x][y].consum_respiration = r_consum * patches[x][y].consum;
//
//    // update consum_excretion
//    patches[x][y].consum_excretion = e_consum * patches[x][y].consum;
//
//    // update consum_senescence
//    patches[x][y].consum_senescence = s_consum * patches[x][y].consum;
//}
//
//void go_DOC(int x, int y)
//{
//    // 4% of photosynthetic gets released into the water column. Wetzel lit.
//    patches[x][y].macro_exudation = .04 * patches[x][y].macro;
//
//    // Dead objects < 1um are considered DOC in Wetzel book..
//    patches[x][y].micro_death = patches[x][y].senescence_macro * .01 + patches[x][y].senescence_phyto * .01;
//
//    // *need reference
//    patches[x][y].excretion = patches[x][y].herbivore_excretion + patches[x][y].waterdecomp_excretion + 
//        patches[x][y].seddecomp_excretion + patches[x][y].sedconsumer_excretion + 
//        patches[x][y].consum_excretion + patches[x][y].excretion_phyto + patches[x][y].peri_excretion;
//
//    // *need reference
//    patches[x][y].flocculation = .01 * patches[x][y].DOC;
//
//    patches[x][y].DOC_growth = patches[x][y].macro_exudation + patches[x][y].micro_death + patches[x][y].excretion;
//}
//
//void go_POC(int x, int y)
//{
//    if(patches[x][y].velocity > 0.0)
//    {
//        // exchange between POC and detritus determined by an approximation of Stoke's Law
//        patches[x][y].detritus_POC_transfer = patches[x][y].detritus * (.25 * log10(((patches[x][y].velocity / 40.0 ) + .0001) + 1.0));
//    }
//
//    if(patches[x][y].detritus_POC_transfer > 1.0)
//    {
//        // cap at 100%. *need reference
//        patches[x][y].detritus_POC_transfer = 1.0;
//    }
//
//    // approximations of the percention of dead objects < 10um that will be in water column; Wetzel Limnology textbook.
//    patches[x][y].small_death = patches[x][y].senescence_macro * 0.09 + patches[x][y].senescence_phyto * 0.09 + 
//        patches[x][y].scouring_macro * 0.1 + patches[x][y].waterdecomp_senescence * 
//        0.7 + 0.3 * patches[x][y].peri_senescence;
//
//    // flocculation, leaching approximation
//    patches[x][y].POC_growth = patches[x][y].flocculation + patches[x][y].detritus_POC_transfer;
//}
//
//void go_detritus(int x, int y)
//{
//    if(patches[x][y].velocity > 0.0)
//    {
//        patches[x][y].POC_detritus_transfer = patches[x][y].POC * (1.0 - (0.25 * log10((( patches[x][y].velocity / 40.0) + 0.0001) + 1.0)));
//    }
//
//    if(patches[x][y].POC_detritus_transfer < 0.0)
//    {
//        patches[x][y].POC_detritus_transfer = 0.0;
//    }
//
//    if(patches[x][y].velocity == 0.0)
//    {
//        patches[x][y].POC_detritus_transfer = patches[x][y].POC * 0.9; 
//    }
//
//    if(patches[x][y].gross_photo_macro < 0.0)
//    {
//        // to incorporate scoured macrophytes into detritus
//        patches[x][y].macro_death = 0.0 - patches[x][y].gross_photo_macro;
//    }
//
//    // Dead objects > 10um will sink Wetzel book..
//    patches[x][y].large_death = patches[x][y].senescence_macro * 0.9 + patches[x][y].scouring_macro * 0.9 + 
//        patches[x][y].senescence_phyto * 0.9 + patches[x][y].seddecomp_senescence + 
//        patches[x][y].waterdecomp_senescence * 0.3 + patches[x][y].herbivore_senescence + 
//        patches[x][y].sedconsumer_senescence + patches[x][y].consum_senescence + 0.07 * patches[x][y].peri_senescence;
//
//    patches[x][y].egestion = herbivore_egestion + patches[x][y].sedconsumer_egestion + consum_egestion;
//
//    patches[x][y].detritus_growth = patches[x][y].large_death + patches[x][y].POC_detritus_transfer + 
//        patches[x][y].egestion + patches[x][y].macro_death;
//}void go_macro(int x, int y){
//    Q10 = pow(theta, (temperature - macro_base_temp));
//
//    if(patches[x][y].velocity < macro_vel_max){
//        patches[x][y].K = max_area * (gui_macro_mass_max - (gui_macro_mass_max  / gui_macro_vel_max) * patches[x][y].velocity);
//    }
//    else{
//        patches[x][y].K = 0.01;
//    }
//    //Same at bottom-light
//    double macro_light = photo_radiation * exp( (-1*patches[x][y].depth) * patches[x][y].turbidity );
//
//    patches[x][y].gross_photo_macro = (gui_gross_macro_coef * patches[x][y].macro * ( macro_light / ( macro_light + 10.0)) * Q10 * 
//            (patches[x][y].K - patches[x][y].macro) / patches[x][y].K);
//
//    patches[x][y].respiration_macro = (resp_macro_coef / 24.0) * patches[x][y].macro * Q10;
//
//    patches[x][y].senescence_macro = sen_macro_coef * patches[x][y].macro / 24.0;
//
//    patches[x][y].growth_macro = patches[x][y].gross_photo_macro - patches[x][y].respiration_macro - patches[x][y].senescence_macro
//        - patches[x][y].scouring_macro;
//
//    patches[x][y].macro += patches[x][y].growth_macro;
//
//    if(patches[x][y].macro < 0.001)
//        patches[x][y].macro = 0.001; //minimum biomass based on seed bank
//}
