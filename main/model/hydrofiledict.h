#ifndef __HYDROFILEDICT_H__
#define __HYDROFILEDICT_H__

#include <QHash>
#include <QString>
#include <QStringList>
#include "hydrofile.h"

class HydroFileDict
{

    public:
        HydroFileDict(QStringList newFilenames);
        HydroFileDict();
        ~HydroFileDict();

        HydroFile * & operator[](const QString filename);
        const HydroFile * operator[](const QString filename) const;

        int getMaxWidth();
        int getMaxHeight();

    private:
        QStringList filenames;
        QHash<QString, HydroFile *> dict;

};



#endif
