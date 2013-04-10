#ifndef PATCHCOLLECTION_H
#define PATCHCOLLECTION_H

#include <QVector>
#include <QHash>
#include "configuration.h"
#include "hydrofiledict.h"
#include "grid.h"
#include "utility.h"

/**
 * @brief The PatchCollection class provides all patch related data in public QVectors.
 *  Each vector holds the data for one type of value for all patches.  This is done for
 *  data locality and to pave way for future SIMD parallel operations.
 */
class PatchCollection {
    public:
        /**
         * @brief PatchCollection Default constructor
         */
        PatchCollection() {}

        /**
         * @brief PatchCollection Copy Constructor
         * @param other PatchCollection to copy
         */
        PatchCollection(const PatchCollection & other);

        /**
         * @brief operator= Assignment operator
         * @param rhs PatchCollection to copy
         * @return Reference to this object
         */
        PatchCollection & operator=(const PatchCollection & rhs);

        /**
         * @brief Destructor
         */
        ~PatchCollection();



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


        int * pxcor;             ///< the x_coordinate for the patch
        int * pycor;             ///< the y_coordinate for the patch
        double * flowX;          ///< flow vector in the x_direction for hydraulics
        double * flowY;          ///< flow vector in the y_direction for hydraulics
        double * flowMagnitude;  ///< the rate of flow for hydraulics
        double * depth;          ///< depth of the water
        bool * hasWater;         ///< indicates whether or not the patch has water

        int * pcolor;

        int * aqa_point;        ///< biomass estimates of macro from USGS

        double * waterdecomp_doc_prey_limitation;       ///< NOT AVAILABLE
        double * waterdecomp_poc_prey_limitation;       ///< NOT AVAILABLE
        double * peri_doc_prey_limitation;              ///< NOT AVAILABLE
        double * peri_poc_prey_limitation;              ///< NOT AVAILABLE
        double * seddecomp_detritus_prey_limitation;    ///< NOT AVAILABLE
        double * herbivore_phyto_prey_limitation;       ///< NOT AVAILABLE
        double * herbivore_waterdecomp_prey_limitation; ///< NOT AVAILABLE
        double * herbivore_peri_prey_limitation;        ///< NOT AVAILABLE
        double * sedconsumer_seddecomp_prey_limitation; ///< NOT AVAILABLE
        double * sedconsumer_peri_prey_limitation;      ///< NOT AVAILABLE
        double * sedconsumer_detritus_prey_limitation;  ///< NOT AVAILABLE
        double * consumer_herbivore_prey_limitation;      ///< NOT AVAILABLE
        double * consumer_sedconsumer_prey_limitation;    ///< NOT AVAILABLE

        double * peri_space_limitation;           ///< NOT AVAILABLE
        double * waterdecomp_space_limitation;    ///< NOT AVAILABLE
        double * seddecomp_space_limitation;      ///< NOT AVAILABLE
        double * herbivore_space_limitation;      ///< NOT AVAILABLE
        double * sedconsumer_space_limitation;    ///< NOT AVAILABLE
        double * consumer_space_limitation;         ///< NOT AVAILABLE

        double * assimilation;                       ///< NOT AVAILABLE
        double * detritus;                           ///< NOT AVAILABLE
        double * DOC;                                ///< NOT AVAILABLE
        double * POC;                                ///< NOT AVAILABLE
        double * waterdecomp;                        ///< NOT AVAILABLE
        double * seddecomp;                          ///< NOT AVAILABLE
        double * macro;                              ///< NOT AVAILABLE
        double * phyto;                              ///< NOT AVAILABLE
        double * herbivore;                          ///< NOT AVAILABLE
        double * sedconsumer;                        ///< NOT AVAILABLE
        double * peri;                               ///< NOT AVAILABLE
        double * consumer;                           ///< consumers in the water column, such as fish
        double * bottom_light;                    ///< par that reaches the bottom of the river

        double * consumer_consumption;              ///< NOT AVAILABLE
        double * consumer_ingest_herbivore;         ///< NOT AVAILABLE
        double * consumer_pred_herbivore;           ///< NOT AVAILABLE
        double * consumer_ingest_sedconsumer;       ///< NOT AVAILABLE
        double * consumer_pred_sedconsumer;         ///< NOT AVAILABLE
        double * consumer_excretion;                ///< NOT AVAILABLE
        double * consumer_sda;                      ///< NOT AVAILABLE
        double * consumer_senescence;               ///< NOT AVAILABLE
        double * consumer_respiration;              ///< NOT AVAILABLE
        double * consumer_growth;                   ///< NOT AVAILABLE
        double * detritus_growth;                 ///< NOT AVAILABLE
        double * detritus_POC_transfer;           ///< the amount of carbon that transfers from detritus to POC
        double * seddecomp_pred_detritus;         ///< NOT AVAILABLE
        double * sedconsumer_pred_detritus;       ///< NOT AVAILABLE
        double * direction;                       ///< the direction carbon flows
        double * DOC_growth;                      ///< NOT AVAILABLE
        double * DOC_pred;                        ///< NOT AVAILABLE
        double * egestion;                        ///< NOT AVAILABLE
        double * excretion;                       ///< NOT AVAILABLE
        double * excretion_phyto;                 ///< NOT AVAILABLE
        double * flocculation;                    ///< the act of DOC sticking together to create POC
        double * gross_photo;                     ///< NOT AVAILABLE
        double * gross_photo_macro;               ///< photosynthesis of macrophytes
        double * gross_photo_phyto;               ///< photosythesis of phytoplankton
        double * growth_herbivore;                ///< NOT AVAILABLE
        double * growth_detritus;                 ///< NOT AVAILABLE
        double * growth_macro;                    ///< amount of biomass macro gains
        double * growth_sedconsumer;              ///< NOT AVAILABLE
        double * growth_phyto;                    ///< NOT AVAILABLE
        double * growth_waterdecomp;              ///< NOT AVAILABLE
        double * herbivore_consumption;           ///< NOT AVAILABLE
        double * herbivore_ingest_peri;           ///< NOT AVAILABLE
        double * herbivore_pred_peri;             ///< NOT AVAILABLE
        double * herbivore_ingest_phyto;          ///< NOT AVAILABLE
        double * herbivore_pred_phyto;            ///< amount of biomass herbivore "consume" from phyto
        double * herbivore_ingest_waterdecomp;    ///< NOT AVAILABLE
        double * herbivore_pred_waterdecomp;      ///< NOT AVAILABLE
        double * herbivore_excretion;             ///< NOT AVAILABLE
        double * herbivore_sda;                   ///< NOT AVAILABLE
        double * herbivore_senescence;            ///< NOT AVAILABLE
        double * herbivore_respiration;           ///< NOT AVAILABLE
        double * herbivore_growth;                ///< NOT AVAILABLE
        double * K;                               ///< carrying capacity
        double * large_death;                     ///< death of large_sized trophic groups
        double * light;                           ///< NOT AVAILABLE
        double * light_k;                         ///< attenuation coefficient of phytoplankon
        double * macro_death;                     ///< NOT AVAILABLE
        double * macro_exudation;                 ///< amount of photosynthetic material released
        double * micro_death;                     ///< amount of dead plant material that becomes DOC
        double * phyto_maximum_growth_rate;       ///< NOT AVAILABLE
        double * phyto_pred;                      ///< NOT AVAILABLE
        double * POC_detritus_transfer;           ///< the amount of carbon that transfers from detritus to POC
        double * POC_growth;                      ///< NOT AVAILABLE
        double * POC_pred;                        ///< NOT AVAILABLE
        double * phyto_density;                   ///< NOT AVAILABLE
        double * peri_ingest_doc;                 ///< NOT AVAILABLE
        double * peri_pred_doc;                   ///< NOT AVAILABLE
        double * peri_ingest_poc;                 ///< NOT AVAILABLE
        double * peri_pred_poc;                   ///< NOT AVAILABLE
        double * peri_respiration;                ///< NOT AVAILABLE
        double * peri_excretion;                  ///< NOT AVAILABLE
        double * peri_senescence;                 ///< NOT AVAILABLE
        double * senescence;                      ///< death
        double * scouring;                        ///< NOT AVAILABLE
        double * small_death;                     ///< amount of dead plant material that becomes POC
        double * respiration;                     ///< NOT AVAILABLE
        double * respiration_macro;               ///< hourly macrophyte respiration
        double * respiration_phyto;               ///< NOT AVAILABLE
        double * scouring_macro;                  ///< NOT AVAILABLE
        double * sedconsumer_ingest_peri;         ///< NOT AVAILABLE
        double * sedconsumer_pred_peri;           ///< NOT AVAILABLE
        double * senescence_macro;                ///< hourly macrophyte death
        double * senescence_phyto;                ///< NOT AVAILABLE
        double * sedconsumer_consumption;         ///< NOT AVAILABLE
        double * sedconsumer_ingest_detritus;     ///< NOT AVAILABLE
        double * sedconsumer_ingest_seddecomp;    ///< NOT AVAILABLE
        double * sedconsumer_pred_seddecomp;      ///< NOT AVAILABLE
        double * sedconsumer_excretion;           ///< NOT AVAILABLE
        double * sedconsumer_egestion;            ///< NOT AVAILABLE
        double * sedconsumer_senescence;          ///< NOT AVAILABLE
        double * sedconsumer_respiration;         ///< NOT AVAILABLE
        double * sedconsumer_growth;              ///< NOT AVAILABLE
        double * seddecomp_consumption;           ///< NOT AVAILABLE
        double * seddecomp_ingest_detritus;       ///< NOT AVAILABLE
        double * seddecomp_excretion;             ///< NOT AVAILABLE
        double * seddecomp_growth;                ///< NOT AVAILABLE
        double * seddcomp_ingest_peri;            ///< NOT AVAILABLE
        double * seddecomp_pred_peri;             ///< NOT AVAILABLE
        double * seddecomp_respiration;           ///< NOT AVAILABLE
        double * seddecomp_senescence;            ///< NOT AVAILABLE
        double * velpoc;                          ///< velocity used for poc_to_detritus transfer equation
        double * waterdecomp_consumption;         ///< NOT AVAILABLE
        double * waterdecomp_ingest_doc;          ///< NOT AVAILABLE
        double * waterdecomp_sda;                 ///< NOT AVAILABLE
        double * waterdecomp_excretion;           ///< NOT AVAILABLE
        double * waterdecomp_ingest_poc;          ///< NOT AVAILABLE
        double * waterdecomp_pred_doc;            ///< NOT AVAILABLE
        double * waterdecomp_pred_poc;            ///< NOT AVAILABLE
        double * waterdecomp_respiration;         ///< NOT AVAILABLE
        double * waterdecomp_senescence;          ///< NOT AVAILABLE
        double * turbidity;                       ///< metric of suspended solids in water column


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

        /**
         * @brief copy Copy helper
         * @param other Other PatchCollection to copy
         */
        void copy(const PatchCollection & other);

        /**
         * @brief Clears the object's memory
         */
        void clear();
};

#endif // PATCHCOLLECTION_H
