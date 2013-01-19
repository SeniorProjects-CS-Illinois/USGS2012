#include "hydrofiledict.h"

HydroFileDict::HydroFileDict(QStringList filenames)
{
    this.filenames = filenames;
    dict = new QHash<QString, HydroFile>();

    for(int i = 0; i < filenames.size(); i++)
    {
        QString filename = filenames[i];
        if( !dict.contains(filename) ) {
            dict.insert(filename, HydroFile(filename));
        }
    }
}

HydroFileDict::~HydroFileDict()
{
    for(int i = 0; i < filenames.size(); i++)
    {
        QString filename = filenames[i];
        dict[filename].~HydroFile();
    }
    delete dict;
}

HydroFile & HydroFileDict::operator[](const Qstring filename)
{
    return dict[filename];
}

const HydroFile & HydroFileDict::operator[](const Qstring filename) const
{
    return dict[filename];
}

int HydroFileDict::getMaxWidth()
{
    int maxWidth = 0
    for(int i = 0; i < filenames.size(); i++)
    {
        QString filename = filenames[i];
        int mapWidth = dict[filename].getMapWidth();
        if(mapWidth > maxWidth)
        {
            maxWidth = mapWidth;
        }
    }
    return maxWidth;
}

int HydroFileDict::getMaxHeight()
{
    int maxHeight = 0
    for(int i = 0; i < filenames.size(); i++)
    {
        QString filename = filenames[i];
        int mapHeight = dict[filename].getMapHeight();
        if(mapHeight > maxHeight)
        {
            maxHeight = mapHeight;
        }
    }
    return maxHeight;
}
