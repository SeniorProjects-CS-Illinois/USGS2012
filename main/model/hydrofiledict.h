#ifndef __HYDROFILEDICT_H__
#define __HYDROFILEDICT_H__

#include <QHash>
#include <QString>
#include <QStringList>
#include "hydrofile.h"
#include "grid.h"

class HydroFileDict
{

    public:
        HydroFileDict(QStringList newFilenames);
        HydroFileDict();
        ~HydroFileDict();

        HydroFile * & operator[](const QString filename);
        const HydroFile * operator[](const QString filename) const;

        int getMaxWidth() const;
        int getMaxHeight() const;

        /**
         * @brief Iterates through all cells of all maps to find all patches used
         * @return A Grid of booleans indicating the existance of a patch.
         */
        const Grid<bool> getPatchUsageGrid() const;

    private:
        QStringList filenames;
        QHash<QString, HydroFile *> dict;

};



#endif
