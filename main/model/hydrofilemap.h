#ifndef __HYDROFILEMAP_H__
#define __HYDROFILEMAP_H__

#include <QHash>
#include "hydrofile.h"

class HydroFileMap
{

    public:
    HydroFileMap(QStringList filenames);
    HydroFileMap();

    HydroFile & HydroFileMap::operator[](const Qstring filename);
    const HydroFile & HydroFileMap::operator[](const Qstring filename) const;

    int getMaxWidth();
    int getMaxHeight();

    private:
    QStringList filenames;
    QHash * map;

}



#endif
