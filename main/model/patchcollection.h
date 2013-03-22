#ifndef PATCHCOLLECTION_H
#define PATCHCOLLECTION_H

#include <QVector>
#include <QHash>
#include "configuration.h"
#include "hydrofiledict.h"
#include "grid.h"

/**
 * @brief The PatchCollection class provides all patch related data in public QVectors.
 *  Each vector holds the data for one type of value for all patches.  This is done for
 *  data locality and to pave way for future SIMD parallel operations.
 */
class PatchCollection {
    public:

        /**
         * @brief Constructor that initializes all patches for the river
         * @param newConfig The config being used by the river.
         * @param hydroDict The collection of hydrofiles used in this simulation.
         */
        PatchCollection(const Configuration & newConfig, HydroFileDict & hydroDict);

        /**
         * @brief Provides an index to a patch given an x and y coordinate
         * @param x The x coordinate
         * @param y The y coordinate
         * @return A positive integer if the index exists, -1 otherwise.
         */
        int getIndex(int x, int y) const;

        /**
         * @brief Indicates whether or not a patch exists at the given coordinates
         * @param x The x coordinate
         * @param y The y coordinate
         * @return True if the patch exists, false otherwise
         */
        bool patchExists(int x, int y) const;

        /**
         * @brief Provides the number of patches
         * @return An int representing the size of the collection
         */
        int getSize() const;


        QVector<int> pxcor;             ///< the x_coordinate for the patch
        QVector<int> pycor;             ///< the y_coordinate for the patch
        QVector<double> flowX;          ///< flow vector in the x_direction for hydraulics
        QVector<double> flowY;          ///< flow vector in the y_direction for hydraulics
        QVector<double> flowMagnitude;  ///< the rate of flow for hydraulics
        QVector<double> depth;          ///< depth of the water
        QVector<bool> hasWater;         ///< indicates whether or not the patch has water

        QVector<int> pcolor;

        QVector<int> aqa_point;        ///< biomass estimates of macro from USGS

        QVector<double> waterdecomp_doc_prey_limitation;       ///< NOT AVAILABLE
        QVector<double> waterdecomp_poc_prey_limitation;       ///< NOT AVAILABLE
        QVector<double> peri_doc_prey_limitation;              ///< NOT AVAILABLE
        QVector<double> peri_poc_prey_limitation;              ///< NOT AVAILABLE
        QVector<double> seddecomp_detritus_prey_limitation;    ///< NOT AVAILABLE
        QVector<double> herbivore_phyto_prey_limitation;       ///< NOT AVAILABLE
        QVector<double> herbivore_waterdecomp_prey_limitation; ///< NOT AVAILABLE
        QVector<double> herbivore_peri_prey_limitation;        ///< NOT AVAILABLE
        QVector<double> sedconsumer_seddecomp_prey_limitation; ///< NOT AVAILABLE
        QVector<double> sedconsumer_peri_prey_limitation;      ///< NOT AVAILABLE
        QVector<double> sedconsumer_detritus_prey_limitation;  ///< NOT AVAILABLE
        QVector<double> consum_herbivore_prey_limitation;      ///< NOT AVAILABLE
        QVector<double> consum_sedconsumer_prey_limitation;    ///< NOT AVAILABLE

        QVector<double> peri_space_limitation;           ///< NOT AVAILABLE
        QVector<double> waterdecomp_space_limitation;    ///< NOT AVAILABLE
        QVector<double> seddecomp_space_limitation;      ///< NOT AVAILABLE
        QVector<double> herbivore_space_limitation;      ///< NOT AVAILABLE
        QVector<double> sedconsumer_space_limitation;    ///< NOT AVAILABLE
        QVector<double> consum_space_limitation;         ///< NOT AVAILABLE

        QVector<double> assimilation;                       ///< NOT AVAILABLE
        QVector<double> detritus;                           ///< NOT AVAILABLE
        QVector<double> DOC;                                ///< NOT AVAILABLE
        QVector<double> POC;                                ///< NOT AVAILABLE
        QVector<double> waterdecomp;                        ///< NOT AVAILABLE
        QVector<double> seddecomp;                          ///< NOT AVAILABLE
        QVector<double> macro;                              ///< NOT AVAILABLE
        QVector<double> phyto;                              ///< NOT AVAILABLE
        QVector<double> herbivore;                          ///< NOT AVAILABLE
        QVector<double> sedconsumer;                        ///< NOT AVAILABLE
        QVector<double> peri;                               ///< NOT AVAILABLE
        QVector<double> consum;                             ///< NOT AVAILABLE
        QVector<double> bottom_light;                    ///< par that reaches the bottom of the river
        QVector<double> consumer;                           ///< consumers in the water column, such as fish
        QVector<double> consum_consumption;              ///< NOT AVAILABLE
        QVector<double> consum_ingest_herbivore;         ///< NOT AVAILABLE
        QVector<double> consum_pred_herbivore;           ///< NOT AVAILABLE
        QVector<double> consum_ingest_sedconsumer;       ///< NOT AVAILABLE
        QVector<double> consum_pred_sedconsumer;         ///< NOT AVAILABLE
        QVector<double> consum_excretion;                ///< NOT AVAILABLE
        QVector<double> consum_sda;                      ///< NOT AVAILABLE
        QVector<double> consum_senescence;               ///< NOT AVAILABLE
        QVector<double> consum_respiration;              ///< NOT AVAILABLE
        QVector<double> consum_growth;                   ///< NOT AVAILABLE
        QVector<double> detritus_growth;                 ///< NOT AVAILABLE
        QVector<double> detritus_POC_transfer;           ///< the amount of carbon that transfers from detritus to POC
        QVector<double> seddecomp_pred_detritus;         ///< NOT AVAILABLE
        QVector<double> sedconsumer_pred_detritus;       ///< NOT AVAILABLE
        QVector<double> direction;                       ///< the direction carbon flows
        QVector<double> DOC_growth;                      ///< NOT AVAILABLE
        QVector<double> DOC_pred;                        ///< NOT AVAILABLE
        QVector<double> egestion;                        ///< NOT AVAILABLE
        QVector<double> excretion;                       ///< NOT AVAILABLE
        QVector<double> excretion_phyto;                 ///< NOT AVAILABLE
        QVector<double> flocculation;                    ///< the act of DOC sticking together to create POC
        QVector<double> gross_photo;                     ///< NOT AVAILABLE
        QVector<double> gross_photo_macro;               ///< photosynthesis of macrophytes
        QVector<double> gross_photo_phyto;               ///< photosythesis of phytoplankton
        QVector<double> growth_herbivore;                ///< NOT AVAILABLE
        QVector<double> growth_detritus;                 ///< NOT AVAILABLE
        QVector<double> growth_macro;                    ///< amount of biomass macro gains
        QVector<double> growth_sedconsumer;              ///< NOT AVAILABLE
        QVector<double> growth_phyto;                    ///< NOT AVAILABLE
        QVector<double> growth_waterdecomp;              ///< NOT AVAILABLE
        QVector<double> herbivore_consumption;           ///< NOT AVAILABLE
        QVector<double> herbivore_ingest_peri;           ///< NOT AVAILABLE
        QVector<double> herbivore_pred_peri;             ///< NOT AVAILABLE
        QVector<double> herbivore_ingest_phyto;          ///< NOT AVAILABLE
        QVector<double> herbivore_pred_phyto;            ///< amount of biomass herbivore "consume" from phyto
        QVector<double> herbivore_ingest_waterdecomp;    ///< NOT AVAILABLE
        QVector<double> herbivore_pred_waterdecomp;      ///< NOT AVAILABLE
        QVector<double> herbivore_excretion;             ///< NOT AVAILABLE
        QVector<double> herbivore_sda;                   ///< NOT AVAILABLE
        QVector<double> herbivore_senescence;            ///< NOT AVAILABLE
        QVector<double> herbivore_respiration;           ///< NOT AVAILABLE
        QVector<double> herbivore_growth;                ///< NOT AVAILABLE
        QVector<double> K;                               ///< carrying capacity
        QVector<double> large_death;                     ///< death of large_sized trophic groups
        QVector<double> light;                           ///< NOT AVAILABLE
        QVector<double> light_k;                         ///< attenuation coefficient of phytoplankon
        QVector<double> macro_death;                     ///< NOT AVAILABLE
        QVector<double> macro_exudation;                 ///< amount of photosynthetic material released
        QVector<double> micro_death;                     ///< amount of dead plant material that becomes DOC
        QVector<double> phyto_maximum_growth_rate;       ///< NOT AVAILABLE
        QVector<double> phyto_pred;                      ///< NOT AVAILABLE
        QVector<double> POC_detritus_transfer;           ///< the amount of carbon that transfers from detritus to POC
        QVector<double> POC_growth;                      ///< NOT AVAILABLE
        QVector<double> POC_pred;                        ///< NOT AVAILABLE
        QVector<double> phyto_density;                   ///< NOT AVAILABLE
        QVector<double> peri_ingest_doc;                 ///< NOT AVAILABLE
        QVector<double> peri_pred_doc;                   ///< NOT AVAILABLE
        QVector<double> peri_ingest_poc;                 ///< NOT AVAILABLE
        QVector<double> peri_pred_poc;                   ///< NOT AVAILABLE
        QVector<double> peri_respiration;                ///< NOT AVAILABLE
        QVector<double> peri_excretion;                  ///< NOT AVAILABLE
        QVector<double> peri_senescence;                 ///< NOT AVAILABLE
        QVector<double> senescence;                      ///< death
        QVector<double> scouring;                        ///< NOT AVAILABLE
        QVector<double> small_death;                     ///< amount of dead plant material that becomes POC
        QVector<double> respiration;                     ///< NOT AVAILABLE
        QVector<double> respiration_macro;               ///< hourly macrophyte respiration
        QVector<double> respiration_phyto;               ///< NOT AVAILABLE
        QVector<double> scouring_macro;                  ///< NOT AVAILABLE
        QVector<double> sedconsumer_ingest_peri;         ///< NOT AVAILABLE
        QVector<double> sedconsumer_pred_peri;           ///< NOT AVAILABLE
        QVector<double> senescence_macro;                ///< hourly macrophyte death
        QVector<double> senescence_phyto;                ///< NOT AVAILABLE
        QVector<double> sedconsumer_consumption;         ///< NOT AVAILABLE
        QVector<double> sedconsumer_ingest_detritus;     ///< NOT AVAILABLE
        QVector<double> sedconsumer_ingest_seddecomp;    ///< NOT AVAILABLE
        QVector<double> sedconsumer_pred_seddecomp;      ///< NOT AVAILABLE
        QVector<double> sedconsumer_excretion;           ///< NOT AVAILABLE
        QVector<double> sedconsumer_egestion;            ///< NOT AVAILABLE
        QVector<double> sedconsumer_senescence;          ///< NOT AVAILABLE
        QVector<double> sedconsumer_respiration;         ///< NOT AVAILABLE
        QVector<double> sedconsumer_growth;              ///< NOT AVAILABLE
        QVector<double> seddecomp_consumption;           ///< NOT AVAILABLE
        QVector<double> seddecomp_ingest_detritus;       ///< NOT AVAILABLE
        QVector<double> seddecomp_excretion;             ///< NOT AVAILABLE
        QVector<double> seddecomp_growth;                ///< NOT AVAILABLE
        QVector<double> seddcomp_ingest_peri;            ///< NOT AVAILABLE
        QVector<double> seddecomp_pred_peri;             ///< NOT AVAILABLE
        QVector<double> seddecomp_respiration;           ///< NOT AVAILABLE
        QVector<double> seddecomp_senescence;            ///< NOT AVAILABLE
        QVector<double> velpoc;                          ///< velocity used for poc_to_detritus transfer equation
        QVector<double> waterdecomp_consumption;         ///< NOT AVAILABLE
        QVector<double> waterdecomp_ingest_doc;          ///< NOT AVAILABLE
        QVector<double> waterdecomp_sda;                 ///< NOT AVAILABLE
        QVector<double> waterdecomp_excretion;           ///< NOT AVAILABLE
        QVector<double> waterdecomp_ingest_poc;          ///< NOT AVAILABLE
        QVector<double> waterdecomp_pred_doc;            ///< NOT AVAILABLE
        QVector<double> waterdecomp_pred_poc;            ///< NOT AVAILABLE
        QVector<double> waterdecomp_respiration;         ///< NOT AVAILABLE
        QVector<double> waterdecomp_senescence;          ///< NOT AVAILABLE
        QVector<double> turbidity;                       ///< metric of suspended solids in water column


    private:
        /**
         * @brief Creates a new patch by adding default values to the appropriate QVectors
         * @return The index of the new patch in the QVectors
         */
        void initializePatches(Configuration & config, int newSize);

        /**
         * @brief Provides a key to use with the index map given an x and y coordinate
         * @param x The x coordinate
         * @param y The y coordinate
         * @return The key for the indexMap
         */
        int getIndexMapKey(int x, int y) const;

        int size;
        int width;
        int height;
        QHash<int,int> indexMap;
        Configuration config;
};

#endif // PATCHCOLLECTION_H
