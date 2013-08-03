#ifndef __HYDROFILEDICT_H__
#define __HYDROFILEDICT_H__

#include <QDir>
#include <QHash>
#include <QString>
#include <QStringList>
#include "hydrofile.h"
#include "carbonflowmap.h"
#include "hydrodata.h"
#include "grid.h"
#include "riveriofile.h"

class HydroFileDict
{

    public:

        /**
         * @brief Constructor that initializes the unique set of hydrofiles and carbonFlowMaps
         *    referenced in the QStringList
         * @param newFilenames A complete list of hydrofiles used in this simulation.
         */
        HydroFileDict(QStringList newFilenames);

        /**
         * @brief Default constructor.  Does nothing.
         */
        HydroFileDict();

        /**
         * @brief Copy constructor
         * @param other HydroFileDict to copy
         */
        HydroFileDict(const HydroFileDict & other);

        /**
         * @brief Assignment operator
         * @param rhs HydroFileDict to copy
         * @return a reference to ourselves
         */
        HydroFileDict & operator=(const HydroFileDict &rhs);

        /**
         * @brief Destructor
         */
        ~HydroFileDict();

        /**
         * @brief operator [] Retrieves and stores hydroData pointers
         * @param filename A string indicating the hydrodata to access
         * @return A pointer to the referenced hydrodata
         */
        HydroData * & operator[](const QString filename);

        /**
         * @brief Const version of operator[]
         * @param filename A string indicating the hydrodata to access
         * @return A const pointer to the referenced hydrodata
         */
        const HydroData * operator[](const QString filename) const;

        /**
         * @brief Returns the max width of all the hydrofiles
         * @return max width of widest hydrofile
         */
        int getMaxWidth() const;

        /**
         * @brief Returns the max height of all the hydrofiles
         * @return max height of tallest hydrofile
         */
        int getMaxHeight() const;

        /**
         * @brief Iterates through all cells of all maps to find all patches used
         * @return A Grid of booleans indicating the existance of a patch.
         */
        const Grid<bool> getPatchUsageGrid() const;

    private:
        QStringList filenames;
        QHash<QString, HydroData *> dict;
        int maxWidth;
        int maxHeight;

        /**
         * @brief copy constructor helper
         * @param rhs HydroFileDict to copy
         */
        void copy(const HydroFileDict &rhs);

        /**
         * @brief Destructor helper
         */
        void clear();

        /**
         * @brief computeMaxWidth
         * @return The max width of all the hydroFiles.
         */
        int computeMaxWidth() const;

        /**
         * @brief computeMaxHeight
         * @return The max height of all the hydroFiles
         */
        int computeMaxHeight() const;

};



#endif
