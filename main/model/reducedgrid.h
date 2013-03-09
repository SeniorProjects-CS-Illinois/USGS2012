#include "grid.h"
#include <QVector>
#include <QHash>
#include <iostream>

/** \brief Grid that only keeps memory regions that are being used.
 * This structure allows much more efficient access if you have a NxM grid 
 * that that only uses certain parts of the grid contiguously.
 */
template <typename T>
class ReducedGrid
{
    public:
        /** \brief Construct a new NxM grid
         * \param[in] width The width of the grid
         * \param[in] height The height of the grid
         */
        ReducedGrid(int width, int height);
           
        /** \brief Returns if the location exists in the reduced grid
         * \param[in] x The x coordinate
         * \param[in] y The y coordinate
         */
        bool locationExists(int x, int y);

        /** \brief Add an item to the reduced grid, should not be called after compressing */
        void addItem(T data, int x, int y);

        /** \brief Returns the data associated with the ith location in the reduced grid
         * \param[in] i The ith position in the reduced grid
         */
        T get(int i);

        /** \brief Returns the data associated with the (x,y) coordinate
         * \param[in] x The x coordinate
         * \param[in] y The y coordinate
         */
        T get(int x, int y);

        /** \brief Compresses the reduced grid based on the cells currently in use
         * \return The success status of the compression operation
         */
        void compress();

        /** \brief Returns the width of the reduced grid
         */
        int getWidth();

        /** \brief Returns the height of the reduced grid
         */
        int getHeight();

        /** \brief Performs a deep copy of the reduced grid
         * \param[in] other The other reduced grid to copy into this grid
         */
        void copy(ReducedGrid const & other);

        /** \brief Erases the contents of the reduced grid
         */
        void clear();

        /** \brief Get the hash key for indexing into the dataset
         * \param[in] x The x coordinate
         * \param[out] y The y coordinate
         */
        int getHashKey(int x, int y);

    private:
        /** \brief Contains true of the reduced grid has been compressed */
        bool compressed;
        /** \brief Grid that contains wether or not a location actually has a data element */
        Grid<bool> hasData;
        /** \brief Contains the indicies into the data */
        QHash<int, int> indiciesHash;   
        /** \brief The compressed vector containing the final data */
        QVector<T> dataset;

        int width, height;

        /*\brief Sturct to hold coordinates and data*/
        typedef struct DataStruct
        {
            int x, y;
            T data;
        } DataStruct_t;

        /** \brief Temporary structure to hold data before compressing */
        QVector<DataStruct> tempData;

};
