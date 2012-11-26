#include "go.h"
#include <algorithm>

/**
 * This function runs the model
 */
void go()
{
        update_environmentals();

        // Ask patches
    for(int x = 0; x < g.MAP_WIDTH; x++) {
        for(int y = 0; y < g.MAP_HEIGHT; y++) {
            if(patches[x][y].depth > 0.0){
                update_patches(x,y);
                go_macro(x,y);
                go_phyto(x,y);
                go_herbivore(x,y);
                go_waterdecomp(x,y);
                go_seddecomp(x,y);
                go_sedconsumer(x,y);
                go_consum(x,y);
                go_DOC(x,y);
                go_POC(x,y);
                go_detritus(x,y);

                pred_phyto(x,y);
                pred_herbivore(x,y);
                pred_seddecomp(x,y);
                pred_waterdecomp(x,y);
                pred_sedconsumer(x,y);
                pred_detritus(x,y);
                pred_DOC(x,y);
                pred_POC(x,y);
                pred_consum(x,y);
            }
        }
    }

    Grid<FlowData> * source = new Grid<FlowData>(g.MAP_WIDTH, g.MAP_HEIGHT);
    Grid<FlowData> * dest = new Grid<FlowData>(g.MAP_WIDTH, g.MAP_HEIGHT);
    copyFlowData(*dest);

    // flow carbon
    int max_time = 60/g.gui_timestep_factor;
    g.nan_trigger = 0;      // set nan to false
    for (int t = 0; t < max_time; t++)
    {
        std::swap(source, dest);
        flow_carbon(*source, *dest);
        if (g.nan_trigger) {
            break;
        }
    }

    storeFlowData(*dest);
    delete source;
    delete dest;

    //Update max values
    for (int x = 0; x < g.MAP_WIDTH; x++)
    {
        for (int y = 0; y < g.MAP_HEIGHT; y++)
        {
            update_max(x,y);
        }
    }

    // increment tick
    g.hours++;

    int day = g.hours%24;
    if (day == 0)
    {
        update_color();
        g.current_day++;
        if(g.current_day == g.output_frequency)
        {
        output_image();
            dump_data();
                        g.current_day = 0;
                }
        }
}


/**
 * Updates the environmental variables (Primary macrophyte routine)
 */
void update_environmentals()
{
        if ((g.hours % 24) == 0)  // Updates daily
        {
                if (g.hydro_changed == 1)
                {
                        update_hydro_map();     // Updates a new hydro map based on the discharge
                    g.hydro_changed = 0;
        }
        }

        if ((g.hours % 168) == 0) // Updates weekly
        {
                update_temp();  // Updates to a new water temperature
        }

        update_par();   // Updates hourly to a new photosynthetic radiation value
}


/**
 * Iterates through all the patches and sets the different components
 * inside the patch, it also computes the maximum_vector in the river and sets it to COMPARE_MAX 
 */
void update_hydro_map()
{
    double max_vector = 0;
    int x, y;

    for (x = 0; x < g.MAP_WIDTH; x++)
    {
        for (y = 0; y < g.MAP_HEIGHT; y++)
        {
            // the hydro maps contained information about this patch
            // set the values of px_vector, py_vector, depth and velocity
            if (patches[x][y].available[g.hydro_group-1])
            {
                patches[x][y].px_vector = patches[x][y].pxv_list[g.hydro_group-1];
                patches[x][y].py_vector = patches[x][y].pyv_list[g.hydro_group-1];
                patches[x][y].depth = patches[x][y].depth_list[g.hydro_group-1];
                patches[x][y].velocity = patches[x][y].v_list[g.hydro_group-1];

                if (fabs(patches[x][y].px_vector) > fabs(patches[x][y].py_vector))
                {
                    patches[x][y].max_vector = fabs(patches[x][y].px_vector);
                }
                else
                {
                    patches[x][y].max_vector = fabs(patches[x][y].py_vector);
                }
            }
            else
            {
                patches[x][y].px_vector = 0.0;
                patches[x][y].py_vector = 0.0;
                patches[x][y].depth = 0.0;
                patches[x][y].velocity = 0.0;
                patches[x][y].max_vector = 0.0;
            }
            // update miscellanous variables inside the patch
            if ((patches[x][y].current_depth > 0.0) && (patches[x][y].depth == 0.0))
            {
                patches[x][y].detritus += patches[x][y].DOC + patches[x][y].POC + patches[x][y].phyto + 
                                          patches[x][y].macro + patches[x][y].waterdecomp +
                                          patches[x][y].seddecomp + patches[x][y].herbivore + patches[x][y].sedconsumer + patches[x][y].consum;

                patches[x][y].DOC = 0.0;
                patches[x][y].POC = 0.0;
                patches[x][y].phyto = 0.0;
                patches[x][y].macro = 0.0;
                patches[x][y].waterdecomp = 0.0;
                patches[x][y].seddecomp = 0.0;
                patches[x][y].herbivore = 0.0;
                patches[x][y].sedconsumer = 0.0;
                patches[x][y].consum = 0.0;
            }
            if ((patches[x][y].current_depth == 0.0) && (patches[x][y].depth > 0.0))
            {
                patches[x][y].detritus *= 0.5;
            }
            patches[x][y].current_depth = patches[x][y].depth;

            // update the max_vector value
            if (patches[x][y].max_vector > max_vector)
            {
                max_vector = patches[x][y].max_vector;
            }
        }// endfor y
    }// endfor x

    // update the maximum vector for the timestep
    g.COMPARE_MAX = max_vector;
}


/**
 * Updates the temperature variable
 */
void update_temp()
{
        g.temperature_index++;
        g.temperature = g.temperature_data[g.temperature_index];
        g.temperature = g.temperature - ((g.temperature - 17.0) * g.temp_dif);
}

/**
 * Updates the photosynthetic radiation variable
 */
void update_par()
{
    g.photo_radiation_index++;
    g.photo_radiation = g.photo_radiation_data[g.photo_radiation_index];
    g.photo_radiation = g.photo_radiation - (int)(g.photo_radiation * g.par_dif);
}

/**
 * @return the max_timestep based on the greatest x-y vector
 */
double get_timestep()
{
    if (g.COMPARE_MAX == 0.0)
    {
        return 1.0;
    }
    return (((double)g.patch_length)/((double)g.COMPARE_MAX));
}

int is_nan(int x, int y, double move_factor)
{
    if ( /*isnan( patches[x][y].DOC + patches[x][y].DOC*move_factor )*/ 
        patches[x][y].DOC + patches[x][y].DOC*move_factor 
            != patches[x][y].DOC + patches[x][y].DOC*move_factor)
    {
        return 1;
    }
    if ( /*isnan( patches[x][y].POC + patches[x][y].POC*move_factor )*/ 
            patches[x][y].POC + patches[x][y].POC*move_factor 
                != patches[x][y].POC + patches[x][y].POC*move_factor)
    {
        return 1;
    }
    if ( /*isnan( patches[x][y].phyto + patches[x][y].phyto*move_factor )*/ 
            patches[x][y].phyto + patches[x][y].phyto*move_factor 
                != patches[x][y].phyto + patches[x][y].phyto*move_factor)
    {
        return 1;
    }
    if ( /*isnan( patches[x][y].waterdecomp + patches[x][y].waterdecomp*move_factor )*/ 
            patches[x][y].waterdecomp + patches[x][y].waterdecomp*move_factor 
                != patches[x][y].waterdecomp + patches[x][y].waterdecomp*move_factor)
    {
        return 1;
    }
    return 0;
}

int is_nan(int x, int y, double move_factor, Grid<FlowData> & dst)
{
    if ( /*isnan( dst(x,y).DOC + dst(x,y).DOC*move_factor )*/ 
        dst(x,y).DOC + dst(x,y).DOC*move_factor 
            != dst(x,y).DOC + dst(x,y).DOC*move_factor)
    {
        return 1;
    }
    if ( /*isnan( dst(x,y).POC + dst(x,y).POC*move_factor )*/ 
            dst(x,y).POC + dst(x,y).POC*move_factor 
                != dst(x,y).POC + dst(x,y).POC*move_factor)
    {
        return 1;
    }
    if ( /*isnan( dst(x,y).phyto + dst(x,y).phyto*move_factor )*/ 
            dst(x,y).phyto + dst(x,y).phyto*move_factor 
                != dst(x,y).phyto + dst(x,y).phyto*move_factor)
    {
        return 1;
    }
    if ( /*isnan( dst(x,y).waterdecomp + dst(x,y).waterdecomp*move_factor )*/ 
            dst(x,y).waterdecomp + dst(x,y).waterdecomp*move_factor 
                != dst(x,y).waterdecomp + dst(x,y).waterdecomp*move_factor)
    {
        return 1;
    }
    return 0;
}

/**
 * Flow each cell's flowable stocks to neighbor cells based on flow vectors
 */
void flow_carbon(Grid<FlowData> & source, Grid<FlowData> & dest)
{
    for(int x = 0; x < g.MAP_WIDTH; x++)
    {
        for(int y = 0; y < g.MAP_HEIGHT; y++)
        {
            if( (source(x,y).depth > 0.0) && (source(x,y).velocity > 0.0) )
            {
                double corner_patch = fabs( source(x,y).py_vector * source(x,y).px_vector )/g.max_area;
                double tb_patch = fabs( source(x,y).py_vector*( g.patch_length - fabs(source(x,y).px_vector) ) )/g.max_area;
                double rl_patch = fabs( source(x,y).px_vector*( g.patch_length - fabs(source(x,y).py_vector) ) )/g.max_area;

                // if a neighbor patch is dry, the carbon does not move in that direction
                double max_timestep = get_timestep();
                int tb_moved = 0, corner_moved = 0, rl_moved = 0;

                int px = (int)(max_timestep * source(x,y).px_vector);
                int py = (int)(max_timestep * source(x,y).py_vector);

                if (g.gui_flow_corners_only)
                {
                    if (px >= 1) px = 1;
                    else if (px <= -1) px = -1;
                    else px = 0;

                    if (py >= 1) py = 1;
                    else if (py <= -1) py = -1;
                    else py = 0;
                }

                // flow carbon to the top/bottom patches
                if ( is_valid_patch(x, y+py) && (py!=0) )
                {
                    if (is_nan(x,y+py,tb_patch, dest)) {
                        g.nan_trigger = 1;  
                    }
                    else
                    {
                        dest(x, y+py).DOC += source(x,y).DOC*tb_patch;
                        dest(x, y+py).POC += source(x,y).POC*tb_patch;
                        dest(x, y+py).phyto += source(x,y).phyto*tb_patch;
                        dest(x, y+py).waterdecomp += source(x,y).waterdecomp*tb_patch;
                        tb_moved = 1;
                    }
                }

                // flow carbon to the corner patch
                if ( is_valid_patch(x+px, y+py) && (px!=0) && (py!=0))
                {
                    if (is_nan(x+px,y+py,corner_patch)) {
                        g.nan_trigger = 1;
                    }
                    else
                    {
                        dest(x+px, y+py).DOC += source(x,y).DOC*corner_patch;
                        dest(x+px, y+py).POC += source(x,y).POC*corner_patch;
                        dest(x+px, y+py).phyto += source(x,y).phyto*corner_patch;
                        dest(x+px, y+py).waterdecomp += source(x,y).waterdecomp*corner_patch;
                        corner_moved = 1;
                    }
                }

                // flow carbon to the left/right patches
                if ( is_valid_patch(x+px, y) && (px!=0) ) 
                {
                    if ( is_nan(x+px,y,rl_patch) ) {
                        g.nan_trigger = 1;
                    }
                    else
                    {
                        dest(x+px, y).DOC += source(x,y).DOC*rl_patch;
                        dest(x+px, y).POC += source(x,y).POC*rl_patch;
                        dest(x+px, y).phyto += source(x,y).phyto*rl_patch;
                        dest(x+px, y).waterdecomp += source(x,y).waterdecomp*rl_patch;
                        rl_moved = 1;
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
}


/**
 * Checks if the x, y values for the patch is within boundaries of the map
 * @param x: the x-coordinate of the patch
 * @param y: the y-coordinate of the patch
 * @return 1 if valid, 0 otherwise
 */
int is_valid_patch(int x, int y) {
    if (x <0 || y < 0) return 0;
    if (x >= g.MAP_WIDTH || y>= g.MAP_HEIGHT) return 0;
    return 1;
}

/**
 * @return the number of days that have passed since the start of the code
 */
int get_day() {
    return g.hours/24;
}


/**
 * Updates the global variables for the stocks
 * @param x: the x-coordinate of the patch
 * @param y: the y-coordinate of the patch
 */
void update_max(int x, int y) {

    if ( patches[x][y].macro > g.MAX_MACRO ) {
        g.MAX_MACRO = patches[x][y].macro;
    }
    if ( patches[x][y].phyto > g.MAX_PHYTO ) {
        g.MAX_PHYTO = patches[x][y].phyto;
    }
    if ( patches[x][y].herbivore > g.MAX_HERBIVORE ) {
        g.MAX_HERBIVORE = patches[x][y].herbivore;
    }
    if ( patches[x][y].waterdecomp > g.MAX_WATERDECOMP ) {
        g.MAX_WATERDECOMP = patches[x][y].waterdecomp;
    }
    if ( patches[x][y].seddecomp > g.MAX_SEDDECOMP ) {
        g.MAX_SEDDECOMP = patches[x][y].seddecomp;
    }
    if ( patches[x][y].sedconsumer > g.MAX_SEDCONSUMER ) {
        g.MAX_SEDCONSUMER = patches[x][y].sedconsumer;
    }
    if ( patches[x][y].consum > g.MAX_CONSUM ) {
        g.MAX_CONSUM = patches[x][y].consum;
    }
    if ( patches[x][y].DOC > g.MAX_DOC ) {
        g.MAX_DOC = patches[x][y].DOC;
    }
    if ( patches[x][y].POC > g.MAX_POC ) {
        g.MAX_POC = patches[x][y].POC;
    }
    if ( patches[x][y].detritus > g.MAX_DETRITUS ) {
        g.MAX_DETRITUS = patches[x][y].detritus;
    }
}

void copyFlowData(Grid<FlowData> & flowData)
{
    for(int x = 0; x < g.MAP_WIDTH; x++)
    {
        for(int y = 0; y < g.MAP_HEIGHT; y++)
        {
            flowData(x,y).depth       = patches[x][y].depth;
            flowData(x,y).velocity    = patches[x][y].velocity;
            flowData(x,y).py_vector   = patches[x][y].py_vector;
            flowData(x,y).px_vector   = patches[x][y].px_vector;
            flowData(x,y).DOC         = patches[x][y].DOC;
            flowData(x,y).POC         = patches[x][y].POC;
            flowData(x,y).phyto       = patches[x][y].phyto;
            flowData(x,y).waterdecomp = patches[x][y].waterdecomp;
        }
    }
}

void storeFlowData(Grid<FlowData> & flowData)
{
    for(int x = 0; x < g.MAP_WIDTH; x++)
    {
        for(int y = 0; y < g.MAP_HEIGHT; y++)
        {
            patches[x][y].depth = flowData(x,y).depth;
            patches[x][y].velocity = flowData(x,y).velocity;
            patches[x][y].py_vector = flowData(x,y).py_vector;
            patches[x][y].px_vector = flowData(x,y).px_vector;
            patches[x][y].DOC = flowData(x,y).DOC;
            patches[x][y].POC = flowData(x,y).POC;
            patches[x][y].phyto = flowData(x,y).phyto;
            patches[x][y].waterdecomp = flowData(x,y).waterdecomp;
        }
    }

}
