#ifndef CARBONFLOWMAP_H
#define CARBONFLOWMAP_H

#include <algorithm>
#include <cmath>

#include "constants.h"
#include "hydrofile.h"
#include "grid.h"
#include "carbonsources.h"

struct SourceArrays {
    int totalSources;
    Grid<int> * offsets;
    Grid<int> * sizes;
    int * x;
    int * y;
    double * amount;

    int getOffset(int x, int y) { return (*offsets)(x,y); }
    int getSize(int x, int y) {return (*sizes)(x,y); }
};

/**
 * @brief The CarbonFlowMap class is used to determine where a cell retrieves its
 *        carbon.  
 * 
 *        For example, normally to simulate an hour of the river flowing we
 *        would "push" the carbon from a cell to destination cells based on the flow vector
 *        in the hydroFile class.  However, it is possible that two cells could push to the
 *        same location.  This results in a race condition and prevents us from easily
 *        parallelizing the flow.  To solve this problem, the carbonFlowMap was created.
 *        Instead of "pushing" carbon, we now "pull" carbon.  At the end of carbonFlowMap's
 *        initialization it will store information about from where each cell got its
 *        carbon.  For example, if in one iteration of pushing carbon a cell receives 20%
 *        of another cell's carbon, then the carbon flow map would indicate this.  Finally
 *        we can precompute like this for multiple iterations.  The number of iterations that
 *        we can precompute is relatively small because the memory requirements is exponential,
 *        however, even just 4 iterations of precomputation allows us to reduce the number of
 *        iterations of the main flow loop from 60 to 15, which is significant.  An important
 *        thing to note is that the number of iterations must be a factor of 60 and the number
 *        of main flow iterations must be (60 / numPreComputedIterations).
 */
class CarbonFlowMap {
    public:
        /**
         * @brief Default constructor, does nothing
         */
        CarbonFlowMap();

        /**
         * @brief Primary construtor that properly initializes object
         * @param hydroFile The hydroFile to do preprocessing on
         * @param iterations The number of iterations to precompute flows.
         */
        CarbonFlowMap(HydroFile * hydroFile, int iterations);

        //Big 3
        CarbonFlowMap(const CarbonFlowMap & other);
        ~CarbonFlowMap();
        CarbonFlowMap & operator=(const CarbonFlowMap & rhs);

        /**
         * @brief Returns the arrays holding the carbonFlowMap's data
         *        Note: This carbonFlowMap should not be deleted while the client holds
         *          this data.
         * @return The SourceArray that holds pointers to this CarbonFlowMap's data
         */
        const SourceArrays getSourceArrays() const;
        void printDebug();

    private:
        //False if not initialized, true otherwise
        bool initialized;

        //Pointer to externally created hydroFile object.  Should exist for duration of simulation
        HydroFile * hydroFile;
        //Number of iterations pre-computed
        int iterations;
        //Collection of arrays and grids that store the carbonFlowMap data.
        SourceArrays sourceData;

        /**
         * @brief Initializes all CarbonSourceCollections within the grid passed as parameter
         * @param source A grid containing uninitialized CarbonSourceCollection Objects
         */
        void initializeCarbonCollection(Grid<CarbonSourceCollection> & source);

        /**
         * @brief Precomputes flows for a single iteration
         * @param source Grid where data is pulled from
         * @param dest Grid where calculations are placed
         */
        void pushCarbon(Grid<CarbonSourceCollection> & source, Grid<CarbonSourceCollection> & dest);

        /**
         * @brief Returns a vector of carbonSources that specifiy to where and how much of
         *        the specified (x,y) cell's carbon will be transfered
         * @param x Source cell's x coord
         * @param y Source cell's y coord
         * @return A QVector of Carbon sources.
         */
        QVector<CarbonSource> * getFlowTargets(int x, int y);

        void copy(const CarbonFlowMap &other);
        void clear();
};

#endif
