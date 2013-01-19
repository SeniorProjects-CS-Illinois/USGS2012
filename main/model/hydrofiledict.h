#ifndef __HYDROFILEDICT_H__
#define __HYDROFILEDICT_H__

#include <QHash>
#include "hydrofile.h"

class HydroFileDict
{

    public:
    HydroFileDict(QStringList filenames);
    HydroFileDict();

    HydroFile & HydroFileDict::operator[](const Qstring filename);
    const HydroFile & HydroFileDict::operator[](const Qstring filename) const;

    int getMaxWidth();
    int getMaxHeight();

    private:
    QStringList filenames;
    QHash * map;

}



#endif
